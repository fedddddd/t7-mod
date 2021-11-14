#include <std_include.hpp>
#include "loader/component_loader.hpp"

#include "game/game.hpp"

#include "command.hpp"
#include "scheduler.hpp"
#include "scripting.hpp"

#include "game/scripting/event.hpp"
#include "game/scripting/functions.hpp"
#include "game/scripting/execution.hpp"
#include "game/scripting/lua/engine.hpp"

#include <utils/hook.hpp>

namespace scripting
{
	std::unordered_map<int, std::unordered_map<std::string, int>> fields_table;
	std::unordered_map<int, std::unordered_map<game::scr_string_t, int>> fields_table_id;
	std::unordered_map<std::string, std::unordered_map<std::string, const char*>> script_function_table;

	namespace
	{
		utils::hook::detour vm_notify_hook;

		utils::hook::detour g_shutdown_game_hook;
		utils::hook::detour scr_load_level_hook;

		utils::hook::detour scr_add_class_field_hook;

		std::string current_file;
		std::unordered_set<std::string> notify_names;

		void vm_notify_stub(int inst, const unsigned int notify_list_owner_id, const game::scr_string_t string_value,
		                    game::VariableValue* top)
		{
			const auto* string = game::SL_LookupCanonicalString(string_value);
			if (string)
			{
				event e;
				e.name = string;
				e.string_value = string_value;
				e.entity = notify_list_owner_id;

				for (auto* value = top; value->type != game::SCRIPT_END; --value)
				{
					e.arguments.emplace_back(*value);
				}

				lua::engine::notify(e);
			}

			vm_notify_hook.invoke<void>(inst, notify_list_owner_id, string_value, top);
		}

		void scr_load_level_stub()
		{
			scr_load_level_hook.invoke<void>();
			lua::engine::start();
		}

		void g_shutdown_game_stub(const int free_scripts)
		{
			lua::engine::stop();
			g_shutdown_game_hook.invoke<void>(free_scripts);
		}
	
		void scr_add_class_field_stub(int inst, unsigned int classnum, game::scr_string_t _name, unsigned int offset)
		{
			const auto name = game::SL_LookupCanonicalString(_name);

			if (fields_table[classnum].find(name) == fields_table[classnum].end())
			{
				fields_table[classnum][name] = offset;
			}

			if (fields_table_id[classnum].find(_name) == fields_table_id[classnum].end())
			{
				fields_table_id[classnum][_name] = offset;
			}

			scr_add_class_field_hook.invoke<void>(inst, classnum, _name, offset);
		}
	}

	class component final : public component_interface
	{
	public:
		void post_unpack() override
		{
			vm_notify_hook.create(0x14015F800, vm_notify_stub);

			g_shutdown_game_hook.create(0x1402ADD70, g_shutdown_game_stub);
			scr_load_level_hook.create(0x1402EA3D0, scr_load_level_stub);

			scr_add_class_field_hook.create(0x1401652B0, scr_add_class_field_stub);

			scheduler::loop([]()
			{
				lua::engine::run_frame();
			}, scheduler::pipeline::server);

			for (const auto& name : function_names)
			{
				const auto hash = game::Dvar_GenerateHash(name.data());
				auto _ = 0;
				const auto function = utils::hook::invoke<script_function>(0x1402E9850, hash, &_, &_, &_);
				if (function)
				{
					function_map[name] = function;
				}
			}

			for (const auto& name : method_names)
			{
				const auto hash = game::Dvar_GenerateHash(name.data());
				auto _ = 0;
				const auto function = utils::hook::invoke<script_function>(0x1402E99E0, hash, &_, &_, &_);
				if (function)
				{
					method_map[name] = function;
				}
			}
		}
	};
}

REGISTER_COMPONENT(scripting::component)

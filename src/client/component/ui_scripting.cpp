#include <std_include.hpp>
#include "loader/component_loader.hpp"

#include "game/game.hpp"
#include "game/dvars.hpp"

#include "scheduler.hpp"
#include "ui_scripting.hpp"

#include "game/ui_scripting/lua/engine.hpp"
#include "game/ui_scripting/execution.hpp"
#include "game/ui_scripting/lua/error.hpp"

#include <utils/hook.hpp>

namespace ui_scripting
{
	namespace
	{
		std::unordered_map<game::hks::cclosure*, sol::protected_function> converted_functions;

		utils::hook::detour startup_hook;
		utils::hook::detour startup2_hook;
		utils::hook::detour error_shutdown_hook;
		utils::hook::detour hksi_lual_error_hook;

		bool error_hook_enabled = false;

		void hksi_lual_error_stub(game::hks::lua_State* s, const char* fmt, ...)
		{
			char va_buffer[0x200] = { 0 };

			va_list ap;
			va_start(ap, fmt);
			vsprintf_s(va_buffer, fmt, ap);
			va_end(ap);

			const auto formatted = std::string(va_buffer);

			if (!error_hook_enabled)
			{
				return hksi_lual_error_hook.invoke<void>(s, formatted.data());
			}
			else
			{
				throw std::runtime_error(formatted);
			}
		}

		void startup_stub()
		{
			printf("[LobbyVM] Starting up...\n");
			startup_hook.invoke<void>();
			lua::engine::start();
		}

		void startup2_stub()
		{
			printf("[LobbyVM] Restarting...\n");
			startup_hook.invoke<void>();
			lua::engine::start();
		}

		void error_shutdown_stub()
		{
			printf("[LobbyVM] Shutting down...\n");
			error_shutdown_hook.invoke<void>();
			lua::engine::stop();
		}
	}

	int main_function_handler(game::hks::lua_State* state)
	{
		const auto value = state->m_apistack.base[-1];
		if (value.t != game::hks::TCFUNCTION)
		{
			return 0;
		}

		const auto closure = value.v.cClosure;
		if (converted_functions.find(closure) == converted_functions.end())
		{
			return 0;
		}

		const auto function = converted_functions[closure];
		const auto count = static_cast<int>(state->m_apistack.top - state->m_apistack.base);
		const auto arguments = get_return_values(count);
		const auto s = function.lua_state();

		std::vector<sol::lua_value> converted_args;

		for (const auto& argument : arguments)
		{
			converted_args.push_back(lua::convert(s, argument));
		}

		const auto results = function(sol::as_args(converted_args));
		lua::handle_error(results);

		for (const auto& result : results)
		{
			push_value(lua::convert({s, result}));
		}

		return results.return_count();
	}

	void add_converted_function(game::hks::cclosure* closure, const sol::protected_function& function)
	{
		converted_functions[closure] = function;
	}

	void clear_converted_functions()
	{
		converted_functions.clear();
	}

	void enable_error_hook()
	{
		error_hook_enabled = true;
	}

	void disable_error_hook()
	{
		error_hook_enabled = false;
	}

	class component final : public component_interface
	{
	public:

		void post_unpack() override
		{
			startup_hook.create(0x1404A0A50, startup_stub);
			startup2_hook.create(0x1404A1F50, startup2_stub);
			error_shutdown_hook.create(0x1404A1280, error_shutdown_stub);
			hksi_lual_error_hook.create(0x1403F5BA0, hksi_lual_error_stub);

			scheduler::loop(lua::engine::run_frame, scheduler::pipeline::main);
		}
	};
}

REGISTER_COMPONENT(ui_scripting::component)

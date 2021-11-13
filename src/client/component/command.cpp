#include <std_include.hpp>
#include "loader/component_loader.hpp"

#include "game/game.hpp"
#include "game/dvars.hpp"

#include "command.hpp"

#include <utils/hook.hpp>
#include <utils/string.hpp>
#include <utils/memory.hpp>

namespace command
{
	namespace
	{
		utils::hook::detour dvar_command_hook;

		std::unordered_map<std::string, std::function<void(params&)>> handlers;

		void main_handler()
		{
			params params = {};

			const auto command = utils::string::to_lower(params[0]);
			if (handlers.find(command) != handlers.end())
			{
				handlers[command](params);
			}
		}
	}

	params::params()
		: nesting_(game::cmd_args->nesting)
	{
	}

	int params::size() const
	{
		return game::cmd_args->argc[this->nesting_];
	}

	const char* params::get(const int index) const
	{
		if (index >= this->size())
		{
			return "";
		}

		return game::cmd_args->argv[this->nesting_][index];
	}

	std::string params::join(const int index) const
	{
		std::string result = {};

		for (auto i = index; i < this->size(); i++)
		{
			if (i > index) result.append(" ");
			result.append(this->get(i));
		}
		return result;
	}

	void add_raw(const char* name, void (*callback)())
	{
		game::Cmd_AddCommandInternal(name, callback, utils::memory::get_allocator()->allocate<game::cmd_function_s>());
	}

	void add(const char* name, const std::function<void(const params&)>& callback)
	{
		const auto command = utils::string::to_lower(name);

		if (handlers.find(command) == handlers.end())
			add_raw(name, main_handler);

		handlers[command] = callback;
	}

	void add(const char* name, const std::function<void()>& callback)
	{
		add(name, [callback](const params&)
		{
			callback();
		});
	}

	void execute(std::string command, const bool sync)
	{
		command += "\n";

		if (sync)
		{
			game::Cmd_ExecuteSingleCommand(0, 0, command.data(), 0);
		}
		else
		{
			game::Cbuf_AddText(0, command.data());
		}
	}

	class component final : public component_interface
	{
	public:
		void post_unpack() override
		{

		}
	};
}

REGISTER_COMPONENT(command::component)

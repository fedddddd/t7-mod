#include <std_include.hpp>
#include "game.hpp"

namespace game
{
	CmdArgs* cmd_args_t::operator->() const
	{
		return game::Sys_GetTLS()->cmdArgs;
	}

	cmd_args_t cmd_args;
}
#include <std_include.hpp>
#include "loader/component_loader.hpp"

#include "game/game.hpp"
#include "game/dvars.hpp"

#include "scheduler.hpp"

#include <utils/hook.hpp>
#include <utils/string.hpp>
#include <utils/io.hpp>

namespace logfile
{
	namespace
	{
		game::dvar_t* g_log;
		utils::hook::detour g_log_printf_hook;

		void g_log_printf_stub(const char* fmt, ...)
		{
			char va_buffer[0x400] = { 0 };

			va_list ap;
			va_start(ap, fmt);
			vsprintf_s(va_buffer, fmt, ap);
			va_end(ap);

			const auto file = g_log->current.string;
			utils::io::write_file(file, utils::string::va("%3i:%i%i %s",
				*game::level_time / 1000 / 60,
				*game::level_time / 1000 % 60 / 10,
				*game::level_time / 1000 % 60 % 10,
				va_buffer
			), true);
		}

		game::dvar_t* register_g_log_stub()
		{
			g_log = dvars::register_string("g_log", "games_mp.log", game::DvarFlags::DVAR_FLAG_NONE, "Log file path");
			return g_log;
		}
	}

	class component final : public component_interface
	{
	public:
		void post_unpack() override
		{
			g_log_printf_hook.create(0x1402A7BB0, g_log_printf_stub);
			utils::hook::call(0x1402A82D6, register_g_log_stub);
			utils::hook::jump(0x1402AC00E, 0x1402AC061, true);
		}
	};
}

REGISTER_COMPONENT(logfile::component)

#include <std_include.hpp>
#include "loader/component_loader.hpp"

#include "command.hpp"

#include <utils/thread.hpp>
#include <utils/hook.hpp>

namespace console
{
	namespace
	{
		std::thread console_thread;

		utils::hook::detour com_printf_hook;
		void com_printf_stub(int channel, int label, const char* fmt, ...)
		{
			char va_buffer[0x200] = { 0 };

			va_list ap;
			va_start(ap, fmt);
			vsprintf_s(va_buffer, fmt, ap);
			va_end(ap);

			printf(va_buffer);
		}
	}

	class component final : public component_interface
	{
	public:

		void post_unpack() override
		{
			utils::hook::jump(0x140505630, com_printf_stub, true);

			// Don't create native console window
			utils::hook::nop(0x140595BD6, 5);
			utils::hook::nop(0x140597E59, 5);

			ShowWindow(GetConsoleWindow(), SW_SHOW);
			SetConsoleTitle("T7 Dedicated Server");

			console_thread = utils::thread::create_named_thread("Console", []()
			{
				std::string cmd;
				while (true)
				{
					std::getline(std::cin, cmd);
					command::execute(cmd.data(), false);
				}
			});
		}
	};
}

REGISTER_COMPONENT(console::component)

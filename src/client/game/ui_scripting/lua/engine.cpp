#include <std_include.hpp>
#include "engine.hpp"
#include "context.hpp"

#include "../../../component/ui_scripting.hpp"

#include <utils/io.hpp>

namespace ui_scripting::lua::engine
{
	namespace
	{
		auto& get_scripts()
		{
			static std::vector<std::unique_ptr<context>> scripts{};
			return scripts;
		}

		void load_scripts(const std::string& script_dir)
		{
			if (!utils::io::directory_exists(script_dir))
			{
				return;
			}

			const auto scripts = utils::io::list_files(script_dir);

			for (const auto& script : scripts)
			{
				if (std::filesystem::is_directory(script) && utils::io::file_exists(script + "/__init__.lua"))
				{
					get_scripts().push_back(std::make_unique<context>(script));
				}
			}
		}
	}

	void start()
	{
		clear_converted_functions();
		get_scripts().clear();
		load_scripts("ui_scripts/");
		load_scripts("lobby_scripts/");
		load_scripts("hks_scripts/");
	}

	void stop()
	{
		clear_converted_functions();
		get_scripts().clear();
	}

	void run_frame()
	{
		for (auto& script : get_scripts())
		{
			script->run_frame();
		}
	}
}

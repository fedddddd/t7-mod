#pragma once

namespace scripting
{
	extern std::unordered_map<int, std::unordered_map<std::string, int>> fields_table;
	extern std::unordered_map<int, std::unordered_map<game::scr_string_t, int>> fields_table_id;
	extern std::unordered_map<std::string, std::unordered_map<std::string, const char*>> script_function_table;
}
#pragma once
#include "game/game.hpp"

namespace scripting
{
	using script_function = void(*)(int, game::scr_entref_t);

	extern std::unordered_map<std::string, script_function> method_map;
	extern std::unordered_map<std::string, script_function> function_map;

	extern std::unordered_set<std::string> function_names;
	extern std::unordered_set<std::string> method_names;

	script_function find_function(const std::string& name, const bool prefer_global);
}

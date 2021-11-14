#pragma once
#include "script_value.hpp"
#include "entity.hpp"

namespace scripting
{
	struct event
	{
		std::string name;
		game::scr_string_t string_value;
		entity entity{};
		std::vector<script_value> arguments;
	};
}

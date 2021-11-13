#pragma once
#include "game/game.hpp"
#include "types.hpp"
#include "script_value.hpp"

namespace ui_scripting
{
	void push_value(const script_value& value);
	script_value get_return_value(int offset);
	arguments get_return_values(int count);

	arguments call_script_function(const function& function, const arguments& arguments);

	script_value get_field(const userdata& self, const script_value& key);
	script_value get_field(const table& self, const script_value& key);
	void set_field(const userdata& self, const script_value& key, const script_value& value);
	void set_field(const table& self, const script_value& key, const script_value& value);
}

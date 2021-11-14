#include <std_include.hpp>
#include "value_conversion.hpp"
#include "../functions.hpp"
#include "../execution.hpp"

namespace scripting::lua
{
	namespace
	{
		bool is_istring(const sol::lua_value& value)
		{
			if (!value.is<std::string>())
			{
				return false;
			}

			const auto str = value.as<std::string>();

			return str[0] == '&';
		}

		script_value string_to_istring(const sol::lua_value& value)
		{
			const auto str = value.as<std::string>().erase(0, 1);
			const auto string_value = game::SL_GetString(str.data(), 0, 23);

			game::VariableValue variable{};
			variable.type = game::SCRIPT_ISTRING;
			variable.u.uintValue = string_value;

			const auto _ = gsl::finally([&variable]()
			{
				game::RemoveRefToValue(0, &variable);
			});

			return script_value(variable);
		}
	}

	script_value convert(const sol::lua_value& value)
	{
		if (value.is<int>())
		{
			return {value.as<int>()};
		}

		if (value.is<unsigned int>())
		{
			return {value.as<unsigned int>()};
		}

		if (value.is<bool>())
		{
			return {value.as<bool>()};
		}

		if (value.is<double>())
		{
			return {value.as<double>()};
		}

		if (value.is<float>())
		{
			return {value.as<float>()};
		}

		if (is_istring(value))
		{
			return string_to_istring(value);
		}

		if (value.is<std::string>())
		{
			return {value.as<std::string>()};
		}

		if (value.is<entity>())
		{
			return {value.as<entity>()};
		}

		if (value.is<vector>())
		{
			return {value.as<vector>()};
		}

		return {};
	}

	sol::lua_value convert(lua_State* state, const script_value& value)
	{
		if (value.is<int>())
		{
			return {state, value.as<int>()};
		}

		if (value.is<float>())
		{
			return {state, value.as<float>()};
		}

		if (value.is<std::string>())
		{
			return {state, value.as<std::string>()};
		}
		
		if (value.is<entity>())
		{
			return {state, value.as<entity>()};
		}

		if (value.is<vector>())
		{
			return {state, value.as<vector>()};
		}

		return {state, sol::lua_nil};
	}
}

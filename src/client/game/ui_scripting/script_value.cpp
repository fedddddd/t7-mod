#include <std_include.hpp>
#include "execution.hpp"
#include "types.hpp"
#include "script_value.hpp"

namespace ui_scripting
{
	/***************************************************************
	 * Constructors
	 **************************************************************/

	script_value::script_value(const game::hks::HksObject& value)
		: value_(value)
	{
	}

	script_value::script_value(const int value)
	{
		game::hks::HksObject obj{};
		obj.t = game::hks::TNUMBER;
		obj.v.number = static_cast<float>(value);

		this->value_ = obj;
	}

	script_value::script_value(const unsigned int value)
	{
		game::hks::HksObject obj{};
		obj.t = game::hks::TNUMBER;
		obj.v.number = static_cast<float>(value);

		this->value_ = obj;
	}

	script_value::script_value(const bool value)
	{
		game::hks::HksObject obj{};
		obj.t = game::hks::TBOOLEAN;
		obj.v.boolean = value;

		this->value_ = obj;
	}

	script_value::script_value(const float value)
	{
		game::hks::HksObject obj{};
		obj.t = game::hks::TNUMBER;
		obj.v.number = static_cast<float>(value);

		this->value_ = obj;
	}

	script_value::script_value(const double value)
		: script_value(static_cast<float>(value))
	{
	}

	script_value::script_value(const char* value)
	{
		game::hks::HksObject obj{};

		const auto state = *game::hks::lua_state;
		state->m_apistack.top = state->m_apistack.base;

		game::hks::hksi_lua_pushlstring(state, value, (unsigned int)strlen(value));
		obj = state->m_apistack.top[-1];

		this->value_ = obj;
	}

	script_value::script_value(const std::string& value)
		: script_value(value.data())
	{
	}

	script_value::script_value(const lightuserdata& value)
	{
		this->value_.t = game::hks::TLIGHTUSERDATA;
		this->value_.v.ptr = value.ptr;
	}

	script_value::script_value(const userdata& value)
	{
		this->value_.t = game::hks::TUSERDATA;
		this->value_.v.ptr = value.ptr;
	}

	script_value::script_value(const table& value)
	{
		this->value_.t = game::hks::TTABLE;
		this->value_.v.ptr = value.ptr;
	}

	script_value::script_value(const function& value)
	{
		this->value_.t = value.type;
		this->value_.v.ptr = value.ptr;
	}

	/***************************************************************
	 * Integer
	 **************************************************************/

	template <>
	bool script_value::is<int>() const
	{
		const auto number = this->get_raw().v.number;
		return this->get_raw().t == game::hks::TNUMBER && static_cast<int>(number) == number;
	}

	template <>
	bool script_value::is<unsigned int>() const
	{
		return this->is<int>();
	}

	template <>
	int script_value::get() const
	{
		return static_cast<int>(this->get_raw().v.number);
	}

	template <>
	unsigned int script_value::get() const
	{
		return static_cast<unsigned int>(this->get_raw().v.number);
	}

	/***************************************************************
	 * Boolean
	 **************************************************************/

	template <>
	bool script_value::is<bool>() const
	{
		return this->get_raw().t == game::hks::TBOOLEAN;
	}

	template <>
	bool script_value::get() const
	{
		return this->get_raw().v.boolean;
	}

	/***************************************************************
	 * Float
	 **************************************************************/

	template <>
	bool script_value::is<float>() const
	{
		return this->get_raw().t == game::hks::TNUMBER;
	}

	template <>
	bool script_value::is<double>() const
	{
		return this->is<float>();
	}

	template <>
	float script_value::get() const
	{
		return this->get_raw().v.number;
	}

	template <>
	double script_value::get() const
	{
		return static_cast<double>(this->get_raw().v.number);
	}

	/***************************************************************
	 * String
	 **************************************************************/

	template <>
	bool script_value::is<const char*>() const
	{
		return this->get_raw().t == game::hks::TSTRING;
	}

	template <>
	bool script_value::is<std::string>() const
	{
		return this->is<const char*>();
	}

	template <>
	const char* script_value::get() const
	{
		return this->get_raw().v.str->m_data;
	}

	template <>
	std::string script_value::get() const
	{
		return this->get<const char*>();
	}

	/***************************************************************
	 * Lightuserdata
	 **************************************************************/

	template <>
	bool script_value::is<lightuserdata>() const
	{
		return this->get_raw().t == game::hks::TLIGHTUSERDATA;
	}

	template <>
	lightuserdata script_value::get() const
	{
		return this->get_raw().v.ptr;
	}

	/***************************************************************
	 * Userdata
	 **************************************************************/

	template <>
	bool script_value::is<userdata>() const
	{
		return this->get_raw().t == game::hks::TUSERDATA;
	}

	template <>
	userdata script_value::get() const
	{
		return this->get_raw().v.ptr;
	}

	/***************************************************************
	 * Table
	 **************************************************************/

	template <>
	bool script_value::is<table>() const
	{
		return this->get_raw().t == game::hks::TTABLE;
	}

	template <>
	table script_value::get() const
	{
		return this->get_raw().v.table;
	}

	/***************************************************************
	 * Function
	 **************************************************************/

	template <>
	bool script_value::is<function>() const
	{
		return this->get_raw().t == game::hks::TIFUNCTION
			|| this->get_raw().t == game::hks::TCFUNCTION;
	}

	template <>
	function script_value::get() const
	{
		return {this->get_raw().v.cClosure, this->get_raw().t};
	}

	/***************************************************************
	 *
	 **************************************************************/

	const game::hks::HksObject& script_value::get_raw() const
	{
		return this->value_;
	}
}

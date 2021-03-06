#include <std_include.hpp>
#include "script_value.hpp"
#include "entity.hpp"

namespace scripting
{
	/***************************************************************
	 * Constructors
	 **************************************************************/

	script_value::script_value(const game::VariableValue& value)
		: value_(value)
	{
	}

	script_value::script_value(const int value)
	{
		game::VariableValue variable{};
		variable.type = game::SCRIPT_INTEGER;
		variable.u.intValue = value;

		this->value_ = variable;
	}

	script_value::script_value(const unsigned int value)
	{
		game::VariableValue variable{};
		variable.type = game::SCRIPT_INTEGER;
		variable.u.uintValue = value;

		this->value_ = variable;
	}

	script_value::script_value(const bool value)
		: script_value(static_cast<unsigned>(value))
	{
	}

	script_value::script_value(const float value)
	{
		game::VariableValue variable{};
		variable.type = game::SCRIPT_FLOAT;
		variable.u.floatValue = value;

		this->value_ = variable;
	}

	script_value::script_value(const double value)
		: script_value(static_cast<float>(value))
	{
	}

	script_value::script_value(const char* value)
	{
		game::VariableValue variable{};
		variable.type = game::SCRIPT_STRING;
		variable.u.stringValue = game::SL_GetString(value, 0, 23);

		const auto _ = gsl::finally([&variable]()
		{
			game::RemoveRefToValue(0, &variable);
		});

		this->value_ = variable;
	}

	script_value::script_value(const std::string& value)
		: script_value(value.data())
	{
	}

	script_value::script_value(const entity& value)
	{
		game::VariableValue variable{};
		variable.type = game::SCRIPT_OBJECT;
		variable.u.pointerValue = value.get_entity_id();

		this->value_ = variable;
	}

	script_value::script_value(const vector& value)
	{
		game::VariableValue variable{};
		variable.type = game::SCRIPT_VECTOR;
		variable.u.vectorValue = game::Scr_AllocVector(0, value);

		const auto _ = gsl::finally([&variable]()
		{
			game::RemoveRefToValue(0, &variable);
		});

		this->value_ = variable;
	}

	/***************************************************************
	 * Integer
	 **************************************************************/

	template <>
	bool script_value::is<int>() const
	{
		return this->get_raw().type == game::SCRIPT_INTEGER;
	}

	template <>
	bool script_value::is<unsigned int>() const
	{
		return this->is<int>();
	}

	template <>
	bool script_value::is<bool>() const
	{
		return this->is<int>();
	}

	template <>
	int script_value::get() const
	{
		return this->get_raw().u.intValue;
	}

	template <>
	unsigned int script_value::get() const
	{
		return this->get_raw().u.uintValue;
	}

	template <>
	bool script_value::get() const
	{
		return this->get_raw().u.uintValue != 0;
	}

	/***************************************************************
	 * Float
	 **************************************************************/

	template <>
	bool script_value::is<float>() const
	{
		return this->get_raw().type == game::SCRIPT_FLOAT;
	}

	template <>
	bool script_value::is<double>() const
	{
		return this->is<float>();
	}

	template <>
	float script_value::get() const
	{
		return this->get_raw().u.floatValue;
	}

	template <>
	double script_value::get() const
	{
		return static_cast<double>(this->get_raw().u.floatValue);
	}

	/***************************************************************
	 * String
	 **************************************************************/

	template <>
	bool script_value::is<const char*>() const
	{
		return this->get_raw().type == game::SCRIPT_STRING;
	}

	template <>
	bool script_value::is<std::string>() const
	{
		return this->is<const char*>();
	}

	template <>
	const char* script_value::get() const
	{
		return game::SL_ConvertToString(static_cast<game::scr_string_t>(this->get_raw().u.stringValue));
	}

	template <>
	std::string script_value::get() const
	{
		return this->get<const char*>();
	}

	/***************************************************************
	 * Entity
	 **************************************************************/

	template <>
	bool script_value::is<entity>() const
	{
		return this->get_raw().type == game::SCRIPT_OBJECT;
	}

	template <>
	entity script_value::get() const
	{
		return entity(this->get_raw().u.pointerValue);
	}

	/***************************************************************
	 * Vector
	 **************************************************************/

	template <>
	bool script_value::is<vector>() const
	{
		return this->get_raw().type == game::SCRIPT_VECTOR;
	}

	template <>
	vector script_value::get() const
	{
		return this->get_raw().u.vectorValue;
	}

	/***************************************************************
	 *
	 **************************************************************/

	const game::VariableValue& script_value::get_raw() const
	{
		return this->value_.get();
	}
}

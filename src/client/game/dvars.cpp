#include <std_include.hpp>
#include <utils/string.hpp>

#include "game.hpp"

namespace dvars
{
	game::dvar_t* cg_legacyCrashHandling;

	std::string dvar_get_vector_domain(const int components, const game::DvarLimits& domain)
	{
		if (domain.vector.min == -FLT_MAX)
		{
			if (domain.vector.max == FLT_MAX)
			{
				return utils::string::va("Domain is any %iD vector", components);
			}
			else
			{
				return utils::string::va("Domain is any %iD vector with components %g or smaller", components,
				                         domain.vector.max);
			}
		}
		else if (domain.vector.max == FLT_MAX)
		{
			return utils::string::va("Domain is any %iD vector with components %g or bigger", components,
			                         domain.vector.min);
		}
		else
		{
			return utils::string::va("Domain is any %iD vector with components from %g to %g", components,
			                         domain.vector.min, domain.vector.max);
		}
	}

	std::string dvar_get_domain(const game::dvarType_t type, const game::DvarLimits& domain)
	{
		std::string str;

		switch (type)
		{
		case game::dvarType_t::DVAR_TYPE_BOOL:
			return "Domain is 0 or 1"s;

		case game::dvarType_t::DVAR_TYPE_FLOAT:
			if (domain.value.min == -FLT_MAX)
			{
				if (domain.value.max == FLT_MAX)
				{
					return "Domain is any number"s;
				}

				return utils::string::va("Domain is any number %g or smaller", domain.value.max);
			}

			if (domain.value.max == FLT_MAX)
			{
				return utils::string::va("Domain is any number %g or bigger", domain.value.min);
			}

			return utils::string::va("Domain is any number from %g to %g", domain.value.min, domain.value.max);

		case game::dvarType_t::DVAR_TYPE_FLOAT_2:
			return dvar_get_vector_domain(2, domain);

		case game::dvarType_t::DVAR_TYPE_LINEAR_COLOR_RGB:
		case game::dvarType_t::DVAR_TYPE_FLOAT_3:
			return dvar_get_vector_domain(3, domain);

		case game::dvarType_t::DVAR_TYPE_FLOAT_4:
			return dvar_get_vector_domain(4, domain);

		case game::dvarType_t::DVAR_TYPE_INT:
			if (domain.enumeration.stringCount == INT_MIN)
			{
				if (domain.integer.max == INT_MAX)
				{
					return "Domain is any integer"s;
				}

				return utils::string::va("Domain is any integer %i or smaller", domain.integer.max);
			}

			if (domain.integer.max == INT_MAX)
			{
				return utils::string::va("Domain is any integer %i or bigger", domain.integer.min);
			}

			return utils::string::va("Domain is any integer from %i to %i", domain.integer.min, domain.integer.max);

		case game::dvarType_t::DVAR_TYPE_COLOR:
			return "Domain is any 4-component color, in RGBA format"s;

		case game::dvarType_t::DVAR_TYPE_ENUM:
			str = "Domain is one of the following:"s;

			for (auto string_index = 0; string_index < domain.enumeration.stringCount; ++string_index)
			{
				str += utils::string::va("\n  %2i: %s", string_index, domain.enumeration.strings[string_index]);
			}

			return str;

		case game::dvarType_t::DVAR_TYPE_STRING:
			return "Domain is any text"s;

		default:
			return utils::string::va("unhandled dvar type '%i'", type);
		}
	}

	game::dvar_t* register_int(const std::string& name, int value, int min, int max, 
		game::DvarFlags flags, const std::string& description)
	{
		const auto hash = game::Dvar_GenerateHash(name.data());
		return game::Dvar_RegisterInt(hash, "", value, min, max, flags, description.data());
	}

	game::dvar_t* register_bool(const std::string& name, bool value, 
		game::DvarFlags flags, const std::string& description)
	{
		const auto hash = game::Dvar_GenerateHash(name.data());
		return game::Dvar_RegisterBool(hash, "", value, flags, description.data());
	}

	game::dvar_t* register_string(const std::string& name, const std::string& value,
		game::DvarFlags flags, const std::string& description)
	{
		const auto hash = game::Dvar_GenerateHash(name.data());
		return game::Dvar_RegisterString(hash, "", value.data(), flags, description.data());
	}

	game::dvar_t* register_float(const std::string& name, float value, float min, 
		float max, game::DvarFlags flags, const std::string& description)
	{
		const auto hash = game::Dvar_GenerateHash(name.data());
		return game::Dvar_RegisterFloat(hash, "", value, min, max, flags, description.data());
	}
}

#pragma once

#include "game.hpp"
#include "structs.hpp"
#include <string>

namespace dvars
{
	std::string dvar_get_vector_domain(const int components, const game::DvarLimits& domain);
	std::string dvar_get_domain(const game::dvarType_t type, const game::DvarLimits& domain);

	game::dvar_t* register_int(const std::string& name, int value, int min, int max, game::DvarFlags flags);
	game::dvar_t* register_bool(const std::string& name, bool value, game::DvarFlags flags);
	game::dvar_t* register_float(const std::string& name, float value, float min, float max, game::DvarFlags flags);
}

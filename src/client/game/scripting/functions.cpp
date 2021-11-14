#include <std_include.hpp>
#include "functions.hpp"

#include <utils/string.hpp>

namespace scripting
{
	namespace
	{
		std::unordered_map<std::string, script_function> lowercase_map(
			const std::unordered_map<std::string, script_function>& old_map)
		{
			std::unordered_map<std::string, script_function> new_map{};
			for (auto& entry : old_map)
			{
				new_map[utils::string::to_lower(entry.first)] = entry.second;
			}

			return new_map;
		}

		const std::unordered_map<std::string, script_function>& get_methods()
		{
			static auto methods = lowercase_map(method_map);
			return methods;
		}

		const std::unordered_map<std::string, script_function>& get_functions()
		{
			static auto function = lowercase_map(function_map);
			return function;
		}
	}

	script_function find_function(const std::string& name, const bool prefer_global)
		{
			const auto target = utils::string::to_lower(name);

			const auto& primary_map = prefer_global
				                          ? get_functions()
				                          : get_methods();
			const auto& secondary_map = !prefer_global
				                            ? get_functions()
				                            : get_methods();

			auto function_entry = primary_map.find(target);
			if (function_entry != primary_map.end())
			{
				return function_entry->second;
			}

			function_entry = secondary_map.find(target);
			if (function_entry != secondary_map.end())
			{
				return function_entry->second;
			}

			return 0;
		}
}

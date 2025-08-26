#pragma once
#include <string>
#include <variant>

namespace shovel
{
	struct Event
	{
		using id_t = std::string;
		using data_t = std::variant<int, bool, std::string, vec2, vec3, float>;

		id_t id;
		data_t data;


		Event(const id_t& id, data_t data) :
			id{id},
			data{ data }
		{ }
	};
}
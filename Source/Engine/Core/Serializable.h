#pragma once
#include "Json.h"

namespace shovel
{
	class Serializable
	{
	public:
		virtual ~Serializable() = default;

		virtual void Read(const json::value_t& value)= 0;
	};
}

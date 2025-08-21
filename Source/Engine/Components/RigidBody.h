#pragma once
#include "../Framework/Component.h"

namespace shovel
{
	class RigidBody : public Component
	{
	public:
		CLASS_PROTOTYPE(RigidBody)
		vec2 velocity;
		float damping{ 0 };
	public:
		void Update(float dt);
		void Read(const json::value_t& value) override;
	};
}
#pragma once
#include "../Framework/Component.h"

namespace shovel
{
	class RigidBody : public Component
	{
	public:
		vec2 velocity;
		float damping{ 0 };
	public:
		void Update(float dt);
	};
}
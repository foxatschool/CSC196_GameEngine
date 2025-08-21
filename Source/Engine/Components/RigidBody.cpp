#include "RigidBody.h"

namespace shovel
{
	FACTORY_REGISTER(RigidBody)

	void shovel::RigidBody::Update(float dt)
	{


		owner->transform.position += velocity * dt; // Update position based on velocity
		velocity += (1.0f / (1.0f + (damping * dt))); // Apply damping to velocity
	}

	void RigidBody::Read(const json::value_t& value)
	{
		Object::Read(value);

		JSON_READ(value, damping);
		JSON_READ(value, velocity);
	}

}

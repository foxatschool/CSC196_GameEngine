#include "RigidBody.h"

void shovel::RigidBody::Update(float dt)
{
	owner->transform.position += velocity * dt; // Update position based on velocity
	velocity += (1.0f / (1.0f + (damping * dt))); // Apply damping to velocity
}

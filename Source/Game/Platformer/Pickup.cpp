#include "Pickup.h"

FACTORY_REGISTER(Pickup)

void Pickup::Start()
{
	m_rigidBody = owner->GetComponent<shovel::RigidBody>();
}
void Pickup::Update(float dt)
{
	//
}
void Pickup::Read(const shovel::json::value_t& value)
{
}

void Pickup::OnCollision(class shovel::Actor* other)
{
	if (shovel::equalsIgnoreCase(other->tag, "player"))
	{
		owner->destroyed = true;
	}
}
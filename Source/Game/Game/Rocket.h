#pragma once
#include "Framework/Component.h"
#include <iostream>



class Rocket : public shovel::Component, public shovel::ICollidable
{
public:
	float speed = 200;

	shovel::RigidBody* m_rigidbody{ nullptr };

public:
	CLASS_PROTOTYPE(Rocket)

	Rocket() = default;

	// Inherited via Actor
	void Update(float dt) override;

	// Inherited via Actor
	void OnCollision(class shovel::Actor* other) override;
};


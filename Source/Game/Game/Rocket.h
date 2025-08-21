#pragma once
#include "Framework/Component.h"
#include <iostream>



class Rocket : public shovel::Component
{
public:
	float speed = 200;

public:
	CLASS_PROTOTYPE(Rocket)

	Rocket() = default;
	/*Rocket(const shovel::Transform transform) :
		Actor{ transform }
	{}*/

	// Inherited via Actor
	void Update(float dt) override;

	// Inherited via Actor
	void OnColission(class shovel::Actor* other);
};


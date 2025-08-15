#pragma once
#include "Framework/Actor.h"
#include <iostream>

class Rocket : public shovel::Actor
{
public:
	float speed = 200;

public:

	Rocket() = default;
	Rocket(const shovel::Transform transform) :
		Actor{ transform }
	{}

	// Inherited via Actor
	void Update(float dt) override;

	// Inherited via Actor
	void OnColission(Actor* other) override;
};


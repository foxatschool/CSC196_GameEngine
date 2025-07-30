#pragma once
#include "Framework/Actor.h"
#include <iostream>

class Rocket : public shovel::Actor
{
public:
	float speed = 200;

public:

	Rocket() = default;
	Rocket(const shovel::Transform transform, std::shared_ptr<class shovel::Model> model) :
		Actor{ transform, model }
	{}

	// Inherited via Actor
	void Update(float dt) override;

	// Inherited via Actor
	void OnColission(Actor* other) override;
};


#pragma once
#include "Framework/Actor.h"

class Enemy : public shovel::Actor
{
public:
	float speed{ 0 };
	float fireTimer = 0;
	float fireTime = 3.0f; // Time between shots
public:
	Enemy() = default;
	Enemy(const shovel::Transform transform) :
		Actor{ transform }
	{}

	void Update(float dt) override;



private:

	// Inherited via Actor
	void OnColission(Actor* other) override;
};


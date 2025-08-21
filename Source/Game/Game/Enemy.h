#pragma once
#include "Framework/Component.h"



class Enemy : public shovel::Component
{
public:
	float speed{ 0 };
	float fireTimer = 0;
	float fireTime = 3.0f; // Time between shots
public:
	Enemy() = default;
	void Update(float dt) override;
	CLASS_PROTOTYPE(Enemy)



private:

	// Inherited via Actor
	void OnColission(class shovel::Actor* other) ;
};


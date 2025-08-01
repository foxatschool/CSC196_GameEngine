#pragma once
#include "Framework/Actor.h"

class Player : public shovel::Actor
{
public:
	float speed = 200;
	float rotationRate = 180; // degrees per second
	float fireTime = 0.2f; // rate of fire in seconds
	float fireTimer = 0.0f;
	int bulletCount = 5;

public:
	Player() = default;
	Player(const shovel::Transform& transform, std::shared_ptr<shovel::Model> model) :
		Actor{ transform, model }
	{}

	void Shoot();


	void Update(float dt) override;

private:

	// Inherited via Actor
	void OnColission(Actor* other) override;
	bool reloded = true;
	float ReloadTimer = 5.0f;
	void reload();
};
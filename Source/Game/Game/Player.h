#pragma once
#include "Framework/Component.h"
//#include "Core/Json.h"

class Player : public shovel::Component, public shovel::ICollidable
{
public:
	float speed = 200;
	float rotationRate = 180; // degrees per second
	float fireTime = 0.2f; // rate of fire in seconds
	float fireTimer = 0.0f;
	int bulletCount = 5;

public:
	Player() = default;
	CLASS_PROTOTYPE(Player)

	void Shoot();


	void Update(float dt) override;
	void Read(const shovel::json::value_t& value) override;
private:

	void OnCollision(class shovel::Actor* other) override;
	bool reloded = true;
	float ReloadTimer = 5.0f;
}; 
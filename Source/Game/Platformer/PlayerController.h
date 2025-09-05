#pragma once
#include "../GamePCH.h"
#include "Framework/Component.h"
//#include "Core/Json.h"

class PlayerController : public shovel::Component, public shovel::ICollidable
{
public:
	float speed = 200;
	float maxSpeed = 180; // degrees per second
	float jump = 20;
	float attackTime = 0.2f; // rate of fire in seconds
	int bulletCount = 5;
	bool attacking = false;

	shovel::RigidBody* attackBox{ nullptr };

	enum class CollisonTag
	{
		Ground,
		Noting
	};
	CollisonTag collisionTag = CollisonTag::Noting;

	shovel::RigidBody* m_rigidBody{ nullptr };

public:
	PlayerController() = default;
	CLASS_PROTOTYPE(PlayerController)

	void Start() override;
	void Update(float dt) override;
	void Read(const shovel::json::value_t& value) override;
	void OnCollision(class shovel::Actor* other) override;
	void slash();

private:
	int lives = 3;
};
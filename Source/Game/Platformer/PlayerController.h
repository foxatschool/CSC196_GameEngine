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
	float fireTime = 0.2f; // rate of fire in seconds
	float fireTimer = 0.0f;
	int bulletCount = 5;

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


private:

};
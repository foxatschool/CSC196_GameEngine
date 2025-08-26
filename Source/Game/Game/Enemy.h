#pragma once
#include "Framework/Component.h"

class Enemy : public shovel::Component, public shovel::ICollidable, public shovel::IObserver
{
public:
	float speed{ 0 };
	float fireTimer = 0;
	float fireTime = 3.0f; // Time between shots

	shovel::RigidBody* m_rigidBody;

public:
	Enemy() = default;
	CLASS_PROTOTYPE(Enemy)

	void Start() override;
	void Update(float dt) override;
	//void OnCollision(class shovel::Actor* other) override;
	void Read(const shovel::json::value_t& value) override;

	void OnCollision(shovel::Actor* other) override;
	void OnNotify(const shovel::Event& event) override;
};


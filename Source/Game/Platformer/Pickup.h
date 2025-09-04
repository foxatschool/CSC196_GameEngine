#pragma once
#include "../GamePCH.h"
#include "Framework/Component.h"
//#include "Core/Json.h"

class Pickup : public shovel::Component, public shovel::ICollidable
{
public:

	shovel::RigidBody* m_rigidBody{ nullptr };

public:
	Pickup() = default;
	CLASS_PROTOTYPE(Pickup)

	void Start() override;
	void Update(float dt) override;
	void Read(const shovel::json::value_t& value) override;
	void OnCollision(class shovel::Actor* other) override;


private:

};
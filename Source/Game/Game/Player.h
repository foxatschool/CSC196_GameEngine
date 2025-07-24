#pragma once
#include "Framework/Actor.h"

class Player : public shovel::Actor
{
public:
	float speed = 200;
	float rotationRate = 180; // degrees per second
public:
	Player() = default;
	Player(const shovel::Transform& transform, std::shared_ptr<shovel::Model> model) :
		Actor{ transform, model }
	{}


	void Update(float dt) override;
	

private:
};
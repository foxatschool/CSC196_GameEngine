#pragma once
#include "../Actor.h"

class Player : public shovel::Actor
{
public:
	Player() = default;
	Player(const shovel::Transform& transform, std::shared_ptr<shovel::Model> model) :
		Actor{ transform, model }
	{}


	void Update(float dt) override;
	

private:
};
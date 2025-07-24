#pragma once
#include "Framework/Actor.h"

class Enemy : public shovel::Actor
{
public:
	Enemy() = default;
	Enemy(shovel::Transform transform, std::shared_ptr<class shovel::Model> model) :
		Actor{ transform, model }
	{
	}




	void Update(float dt) override;


private:
};
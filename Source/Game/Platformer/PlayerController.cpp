#include "PlayerController.h"

FACTORY_REGISTER(PlayerController)

void PlayerController::Start()
{
	m_rigidBody = owner->GetComponent<shovel::RigidBody>();
	
}
void PlayerController::Update(float dt)
{
	collisionTag = CollisonTag::Noting;
	float dir = 0;
	

	if (shovel::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_A))
	{
		dir = -1;
		owner->GetComponent<shovel::Animator>()->Play("run");
	}
		
	if (shovel::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_D)) 
	{
		dir = +1;
		owner->GetComponent<shovel::Animator>()->Play("run");
	}

	if (dir != 0)
	{
		m_rigidBody->ApplyForce(shovel::vec2{1,0} * dir * 400);
	}
	else if (dir == 0 && collisionTag == CollisonTag::Ground)
	{
		owner->GetComponent<shovel::Animator>()->Play("idle");
	}

	if (shovel::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE))
	{
		m_rigidBody->ApplyForce(shovel::vec2{ 0,-1 } * 20000);
	}
	if (collisionTag != CollisonTag::Ground && shovel::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE))
	{
		owner->GetComponent<shovel::Animator>()->Play("jump");
	}


	auto spriterenderer = owner->GetComponent<shovel::SpriteRenderer>();
	if (spriterenderer)
	{
		if (shovel::math::fabs(m_rigidBody->velocity.x) > 0.1f)
		{ 
			spriterenderer->flipH = (m_rigidBody->velocity.x < 0 );
		}
	}
}
void PlayerController::Read(const shovel::json::value_t& value)
{
	Object::Read(value);

	JSON_READ(value, speed);
	JSON_READ(value, maxSpeed);
	JSON_READ(value, jump);
	JSON_READ(value, fireTime);

}

void PlayerController::OnCollision(class shovel::Actor* other)
{
	//std::cout << other->name << std::endl;
	if (other->tag == "ground")
	{
		collisionTag = CollisonTag::Ground;
	}
}
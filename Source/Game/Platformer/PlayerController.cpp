#include "PlayerController.h"

FACTORY_REGISTER(PlayerController)

void PlayerController::Start()
{
	m_rigidBody = owner->GetComponent<shovel::RigidBody>();
}
void PlayerController::Update(float dt)
{
	float dir = 0;
	if (shovel::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_A)) dir = -1;
	if (shovel::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_D)) dir = +1;

	if (dir != 0)
	{
		m_rigidBody->ApplyForce(shovel::vec2{0,1} * dir * 1000);
	}

	if (shovel::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE))
	{
		m_rigidBody->ApplyForce(shovel::vec2{ 1,0 } * 1000000);
	}
}
void PlayerController::Read(const shovel::json::value_t& value)
{
	JSON_READ(value, speed);
	JSON_READ(value, maxSpeed);
	JSON_READ(value, jump);
	JSON_READ(value, fireTime);
}

void PlayerController::OnCollision(class shovel::Actor* other)
{

}
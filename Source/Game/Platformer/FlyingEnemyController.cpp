#include "FlyingEnemyController.h"

FACTORY_REGISTER(FlyingEnemyController)

void FlyingEnemyController::Start()
{
	m_rigidBody = owner->GetComponent<shovel::RigidBody>();
}
void FlyingEnemyController::Update(float dt)
{
	float dir = 0;
	auto player = owner->scene->GetActorByName<shovel::Actor>("PlatformPlayer");
	if (player) 
	{
		shovel::vec2 direction = player->transform.position - owner->transform.position;
		m_rigidBody->ApplyForce(direction);
	}
	//else dir = 1;

	m_rigidBody->ApplyForce(shovel::vec2{ 0,1 } *dir * 1000);
}
void FlyingEnemyController::Read(const shovel::json::value_t& value)
{
	JSON_READ(value, speed);
	JSON_READ(value, maxSpeed);
	JSON_READ(value, jump);
	JSON_READ(value, fireTime);
}

void FlyingEnemyController::OnCollision(class shovel::Actor* other)
{

}
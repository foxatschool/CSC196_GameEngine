#include "EnemyController.h"

FACTORY_REGISTER(EnemyController)

void EnemyController::Start()
{
	m_rigidBody = owner->GetComponent<shovel::RigidBody>();
}
void EnemyController::Update(float dt)
{
	float dir = 0;
	auto player = owner->scene->GetActorByName<shovel::Actor>("PlatformPlayer");
	if (player->transform.position.x < owner->transform.position.x) dir = -1;
	else dir = 1;

	m_rigidBody->ApplyForce(shovel::vec2{ 0,1 } * dir * 1000);
}
void EnemyController::Read(const shovel::json::value_t& value)
{
	JSON_READ(value, speed);
	JSON_READ(value, maxSpeed);
	JSON_READ(value, jump);
	JSON_READ(value, fireTime);
}

void EnemyController::OnCollision(class shovel::Actor* other)
{

}
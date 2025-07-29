#include "Player.h"
#include "Enemy.h"
#include "Engine.h"
#include "Framework/Scene.h"
#include "Renderer/Renderer.h"

void Enemy::Update(float dt)
{
	// Set the speed and direction of the enemy
    float speed = 200;
    shovel::vec2 direction{ 0,0 };
	// Get the player actor from the scene & calculate direction towards the player
    Actor* player = scene->GetActorByName<Player>("Player");
    if (player)
    {
        shovel::vec2 direction{ 0,0 };
        direction = player->transform.position - transform.position;
        direction = direction.Normalized();
    }
    shovel::vec2 force = shovel::vec2{1,0}.Rotate(shovel::math::degTorad(transform.rotation)) * speed;

	// Update the transform position based on the direction of the player
    transform.rotation = shovel::math::radToDeg(direction.Angle());

	// Apply the force to the enemy's velocity using the delta time
    velocity += force * dt;

    Actor::Update(dt);
}

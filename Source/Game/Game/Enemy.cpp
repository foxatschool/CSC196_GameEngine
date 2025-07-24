#include "Enemy.h"
#include "Engine.h"
#include "Framework/Scene.h"
#include "Renderer/Renderer.h"

void Enemy::Update(float dt)
{
    float speed = 200;
    shovel::vec2 direction{ 0,0 };
    Actor* player = scene->GetActorByName("Player");
    if (player)
    {
        shovel::vec2 direction{ 0,0 };
        direction = player->transform.position - transform.position;
        direction = direction.Normalized();
    }
    shovel::vec2 force = shovel::vec2{1,0}.Rotate(shovel::math::degTorad(transform.rotation)) * speed;

    transform.rotation = shovel::math::radToDeg(direction.Angle());


    velocity += force * dt;

    Actor::Update(dt);
}

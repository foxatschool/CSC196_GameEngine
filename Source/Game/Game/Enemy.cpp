#include "Player.h"
#include "Enemy.h"
#include "Engine.h"
#include "Core/Random.h"
#include "Framework/Scene.h"
#include "Framework/Game.h"
#include "Renderer/Renderer.h"
#include "Renderer/ParticalSystem.h"
#include "Renderer/Model.h"
#include "Math/Math.h"
#include "Math/Vector2.h"
#include "../GameData.h"
#include "Rocket.h"

void Enemy::Update(float dt)
{
	bool playerseen = false;
    // Set the speed and direction of the enemy
    float speed = 200;
    shovel::vec2 direction{ 0,0 };
    // Get the player actor from the scene & calculate direction towards the player
    Actor* player = scene->GetActorByName<Player>("Player");
    if (player)
    {
        shovel::vec2 direction{ 1,0 };
        direction = player->transform.position - transform.position;

        direction = direction.Normalized();
        shovel::vec2 forward = shovel::vec2{ 1,0 }.Rotate(shovel::math::degTorad(transform.rotation));
		float angle = shovel::vec2::SignedAngleBetween(direction, forward);
        angle = shovel::math::sign(angle);
        transform.rotation += shovel::math::radToDeg(angle * 5 * dt);

		angle = shovel::math::radToDeg(shovel::vec2::AngleBetween(direction, forward));
        playerseen = angle < 30;
    }
    shovel::vec2 force = shovel::vec2{ 1,0 }.Rotate(shovel::math::degTorad(transform.rotation)) * speed;

	velocity += force * dt; // Apply the force to the enemy's velocity


    transform.position.x = shovel::math::wrap(transform.position.x, 0.0f, (float)shovel::GetEngine().GetRenderer().GetWidth());
    transform.position.y = shovel::math::wrap(transform.position.y, 0.0f, (float)shovel::GetEngine().GetRenderer().GetWidth());

	fireTimer -= dt;
	if (fireTimer <= 0 && playerseen)
	{
		fireTimer = fireTime; // Reset the fire timer
        // Apply the force to the enemy's velocity using the delta time
        velocity += force * dt;
        std::shared_ptr<shovel::Model> playerModel = std::make_shared<shovel::Model>(GameData::ShipPoint, shovel::vec3{ 1.0,0.0,0.0 });
        shovel::Transform transform{ this->transform.position, this->transform.rotation, 2.5 };
        auto rocket = std::make_unique<Rocket>(transform, playerModel);
        rocket->speed = 500.0f;
        rocket->lifespan = 1.5f;
        rocket->name = "Rocket";
        rocket->tag = "Enemy";
        scene->AddActor(std::move(rocket));
	}

    Actor::Update(dt);
}
void Enemy::OnColission(Actor* other)
{
    if (tag != other->tag)
    {
        destroyed = true;
		scene->GetGame()->AddPoints(500);
        for (int i = 0; i < 100; i++)
        {
            shovel::Particle particle;
            particle.position = transform.position;
			particle.velocity = shovel::random::onUnitCircle() * shovel::random::getReal(10.0f, 200.0f);
            particle.velocity = shovel::vec2{ shovel::random::getReal(-200.0f, 200.0f), shovel::random::getReal(-200.0f, 200.0f) };
            particle.color = shovel::vec3{ 1, 1, 1 };
            particle.lifetime = 2;
        }
    }
}

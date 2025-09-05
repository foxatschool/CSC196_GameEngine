#include "../Game/GamePCH.h"
#include "Player.h"
#include "Enemy.h"
#include "Engine.h"
#include "Core/Random.h"
#include "Framework/Scene.h"
#include "Framework/Game.h"
#include "Renderer/Renderer.h"
#include "Math/Math.h"
#include "Math/Vector2.h"
#include "../GameData.h"
#include "Renderer/ParticleSystem.h"
#include "Renderer/Mesh.h"
#include "Components/RigidBody.h"
#include "Components/CircleCollider2D.h"
#include "Components/SpriteRenderer.h"
#include "Rocket.h"
#include "Core/Logger.h"

FACTORY_REGISTER(Enemy)

void Enemy::Update(float dt)
{
	bool playerseen = false;
    // Set the speed and direction of the enemy
    float speed = 200;
    shovel::vec2 direction{ 0,0 };
    // Get the player actor from the scene & calculate direction towards the player
    shovel::Actor* player = owner->scene->GetActorByName<shovel::Actor>("Player");
    if (player)
    {
        shovel::vec2 direction{ 1,0 };
        direction = player->transform.position - owner->transform.position;

        direction = direction.Normalized();
        shovel::vec2 forward = shovel::vec2{ 1,0 }.Rotate(shovel::math::degTorad(owner->transform.rotation));
		float angle = shovel::vec2::SignedAngleBetween(direction, forward);
        angle = shovel::math::sign(angle);

        m_rigidBody->ApplyTorque(angle * 5);
        //owner->transform.rotation += shovel::math::radToDeg(angle * 5 * dt);

		angle = shovel::math::radToDeg(shovel::vec2::AngleBetween(direction, forward));
        playerseen = angle < 30;
    }
    shovel::vec2 force = shovel::vec2{ 1,0 }.Rotate(shovel::math::degTorad(owner->transform.rotation)) * speed;

	//velocity += force * dt; // Apply the force to the enemy's velocity
    auto* rb = owner->GetComponent<shovel::RigidBody>();
    if (rb)
    {
        rb->ApplyForce(force);

    }

    owner->transform.position.x = shovel::math::wrap(owner->transform.position.x, 0.0f, (float)shovel::GetEngine().GetRenderer().GetWidth());
    owner->transform.position.y = shovel::math::wrap(owner->transform.position.y, 0.0f, (float)shovel::GetEngine().GetRenderer().GetWidth());

//	fireTimer -= dt;
//	if (fireTimer <= 0 && playerseen)
//	{
//		fireTimer = fireTime; // Reset the fire timer
//        // Apply the force to the enemy's velocity using the delta time
//        owner->velocity += force * dt;
//        std::shared_ptr<shovel::Mesh> playerModel = std::make_shared<shovel::Mesh>(GameData::ShipPoint, shovel::vec3{ 1.0,0.0,0.0 });
//        shovel::Transform transform{ this->owner->transform.position, this->owner->transform.rotation, 2.5 };
//        auto rocket = std::make_unique<Actor>(transform);//, playerModel);
//        rocket->speed = 500.0f;
//        rocket->owner->lifespan = 1.5f;
//        rocket->name = "Rocket";
//        rocket->owner->tag = "Enemy";
//
//		auto spriteRenderer = std::make_unique<shovel::SpriteRenderer>();
//		spriteRenderer->textureName = "Rocket"; // todo "put texture location here"
//
//        rocket->owner->AddComponent(std::move(spriteRenderer));
//
//        auto rb = std::make_unique<shovel::RigidBody>();
//        rocket->AddComponent(std::move(rb));
//
//        auto collider = std::make_unique<shovel::CircleCollider2D>();
//        collider->radius = 60;
//        rocket->AddComponent(std::move(collider));
//
//        scene->AddActor(std::move(rocket));
//	}
//
//    Actor::Update(dt);
}
void Enemy::Start()
{
    shovel::EventManager::Instance().AddObserver("player_dead", *this);

	m_rigidBody = owner->GetComponent<shovel::RigidBody>();
	fireTimer = fireTime;
}

void Enemy::Read(const shovel::json::value_t& value)
{
    Object::Read(value);

    JSON_READ(value, speed);
    JSON_READ(value, fireTime);
}
void Enemy::OnNotify(const shovel::Event& event)
{


    if (shovel::equalsIgnoreCase(event.id, "player_dead"))
    {
        owner->destroyed = true;
    }
}
void Enemy::OnCollision(shovel::Actor* other)
{
    if (owner->tag != other->tag)
    {
        shovel::Logger::Debug("Enemy Hit");
        owner->destroyed = true;
        EVENT_NOTIFY_DATA(add_points, 100);
        for (int i = 0; i < 100; i++)
        {
            shovel::Particle particle;
            particle.position = owner->transform.position;
			particle.velocity = shovel::random::onUnitCircle() * shovel::random::getReal(10.0f, 200.0f);
            particle.velocity = shovel::vec2{ shovel::random::getReal(-200.0f, 200.0f), shovel::random::getReal(-200.0f, 200.0f) };
            particle.color = shovel::vec3{ 1, 1, 1 };
            particle.lifetime = 2;
        }
    }
}

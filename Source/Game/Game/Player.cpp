#include "../Game/GamePCH.h"
#include "Player.h"
#include "Engine.h"
#include "Rocket.h"
#include "SpaceGame.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Math/Math.h"
#include "Math/Vector3.h"
#include "../GameData.h"
#include "Framework/Scene.h"
#include "Renderer/Mesh.h"
#include "Renderer/ParticleSystem.h"
#include "Core/Random.h"
#include "Components/SpriteRenderer.h"
#include "Components/RigidBody.h"
#include "Components/CircleCollider2D.h"
#include "Components/SpriteRenderer.h"
#include "Resources/ResourceManager.h"

#include "SDL3/SDL.h"

FACTORY_REGISTER(Player)

void Player::Shoot()
{
 	reloded = bulletCount <= 0;
	if (!reloded)
	{
		bulletCount--;

		auto rocket = shovel::Instantiate("rocket", owner->transform);
		owner->scene->AddActor(std::move(rocket));
	}
	else
	{
		owner->scene->GetGame()->SubtractPoints(100);
	}
}



void Player::Start()
{
	m_rigidBody = owner->GetComponent<shovel::RigidBody>();
	fireTimer = fireTime;
}

void Player::Update(float dt)
{
	shovel::Particle particle;
	particle.position = owner->transform.position + shovel::vec2{ -50, 0 }.Rotate(shovel::math::degTorad(owner->transform.rotation));
	particle.velocity = shovel::vec2(shovel::random::getReal()  * -50, shovel::random::getReal() * 100);// change to random
	particle.color = shovel::vec3(1, 1, 1);// change to random
	particle.lifetime = .5;
	shovel::GetEngine().GetPS().AddParticle(particle);

	// Update the transform rotation based on input
    float rotate = 0;
    if (shovel::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_A)) rotate = -1;
    if (shovel::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_D)) rotate = +1;

    m_rigidBody->ApplyTorque(rotate * rotationRate);

	// Update the transform position based on input and speed
	float thrust = 0;
	if (shovel::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_W)) thrust = + 1;
	if (shovel::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_S)) thrust = -.5;

	// Calculate the direction vector based on the current rotation
    shovel::vec2 direction{ 1,0 };
    shovel::vec2 force = direction.Rotate(shovel::math::degTorad(owner->transform.rotation)) * thrust * speed;
    
	// Apply the force to the player's velocity using the delta time
	auto* rb = owner->GetComponent<shovel::RigidBody>();
	if (rb)
	{
		rb->ApplyForce(force);
	}

	owner->transform.position.x = shovel::math::wrap(owner->transform.position.x, 0.0f, (float)shovel::GetEngine().GetRenderer().GetWidth());
	owner->transform.position.y = shovel::math::wrap(owner->transform.position.y, 0.0f, (float)shovel::GetEngine().GetRenderer().GetHeight());


	if (bulletCount <= 0)
	{
		reloded = true;
		ReloadTimer -= dt;
		if (ReloadTimer <= 0.0f)
		{
			bulletCount = 5;
			ReloadTimer = 5.0f;
			reloded = false;
		}
	}

	fireTimer -= dt;
	if (shovel::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_SPACE) && fireTimer <=0 )
	{
		
		Shoot();
		fireTimer = fireTime;
	}
}

void Player::OnCollision(shovel::Actor* other)
{


	if (owner->tag != other->tag)
	{
		owner->destroyed = true;
		EVENT_NOTIFY(player_dead);

		shovel::EventManager::Instance().Notify(shovel::Event("player_dead", true));
		dynamic_cast<SpaceGame*>(owner->scene->GetGame())->OnPlayerDeath();
	}
}

void Player::Read(const shovel::json::value_t& value)
{
	Object::Read(value);

	JSON_READ(value, speed);
	JSON_READ(value, rotationRate);
	JSON_READ(value, fireTime);
}

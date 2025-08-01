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
#include "Renderer/Model.h"
#include "Renderer/ParticalSystem.h"
#include "Core/Random.h"

#include "SDL3/SDL.h"

void Player::Shoot()
{
	reloded = bulletCount <= 0;
	if (!reloded)
	{
		bulletCount--;
		std::shared_ptr<shovel::Model> bulletModel = std::make_shared<shovel::Model>(GameData::BulletPoints, shovel::vec3{ 1.0,1.0,1.0 });
		shovel::Transform transform{ this->transform.position, this->transform.rotation, 2.5 };
		auto rocket = std::make_unique<Rocket>(transform, bulletModel);
		rocket->speed = 500.0f;
		rocket->lifespan = 1.5f;
		rocket->name = "Rocket";
		rocket->tag = "Player";

		scene->AddActor(std::move(rocket));
		
	}
	else
	{
		scene->GetGame()->SubtractPoints(100);
		ReloadTimer -= shovel::GetEngine().GetTime().GetDeltaTime();
		if (ReloadTimer <= 0.0f)
		{
			bulletCount = 5;
			ReloadTimer = 15;
		}
	}
}

void Player::Update(float dt)
{
	shovel::Particle particle;
	particle.position = transform.position + shovel::vec2{ -50, 0 }.Rotate(shovel::math::degTorad(transform.rotation));
	particle.velocity = shovel::vec2(shovel::random::getReal()  * -50, shovel::random::getReal() * 10);// change to random
	particle.color = shovel::vec3(1, 1, 1);// change to random
	particle.lifetime = 2;
	shovel::GetEngine().GetPS().AddParticle(particle);

	// Update the transform rotation based on input
    float rotate = 0;
    if (shovel::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_A)) rotate = -1;
    if (shovel::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_D)) rotate = +1;

    transform.rotation += (rotate * rotationRate) * dt;

	// Update the transform position based on input and speed
	float thrust = 0;
	if (shovel::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_W)) thrust = +1;
	if (shovel::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_S)) thrust = -.5;

	// Calculate the direction vector based on the current rotation
    shovel::vec2 direction{ 1,0 };
    shovel::vec2 force = direction.Rotate(shovel::math::degTorad(transform.rotation)) * thrust * speed;
    
	// Apply the force to the player's velocity using the delta time
    velocity += force * dt;

	transform.position.x = shovel::math::wrap(transform.position.x, 0.0f, (float)shovel::GetEngine().GetRenderer().GetWidth());
	transform.position.y = shovel::math::wrap(transform.position.y, 0.0f, (float)shovel::GetEngine().GetRenderer().GetHeight());

	fireTimer -= dt;
	if (shovel::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_SPACE) && fireTimer <=0 )
	{
		
		Shoot();
		fireTimer = fireTime;
	}
	// Call the base class update method

	Actor::Update(dt);
}

void Player::OnColission(Actor* other)
{
	if (tag != other->tag)
	{
		destroyed = true;
		dynamic_cast<SpaceGame*>(scene->GetGame())->OnPlayerDeath();
	}
}

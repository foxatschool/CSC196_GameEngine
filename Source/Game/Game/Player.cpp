#include "Player.h"
#include "Engine.h"
#include "Rocket.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Math/Math.h"
#include "Math/Vector3.h"
#include "../GameData.h"
#include "Framework/Scene.h"
#include "Renderer/Model.h"

#include "SDL3/SDL.h"

void Player::Shoot()
{
	std::shared_ptr<shovel::Model> playerModel = std::make_shared<shovel::Model>(GameData::ShipPoint, shovel::vec3{ 1.0,1.0,1.0 });
	shovel::Transform transform{ this->transform.position, this->transform.rotation, 2.5 };
	auto rocket = std::make_unique<Rocket>(transform, playerModel);
	rocket->speed = 500.0f;
	rocket->lifespan = 1.5f;
	rocket->name = "Rocket";
	rocket->tag = "Player";

	scene->AddActor(std::move(rocket));
}

void Player::Update(float dt)
{
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
	}
}

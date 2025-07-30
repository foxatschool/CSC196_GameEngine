#include "Rocket.h"

#include "Engine.h"
#include "Player.h"
#include "Framework/Scene.h"
#include "Renderer/Renderer.h"


void Rocket::Update(float dt)
{
	// Update the transform rotation based on input
	shovel::vec2 force = shovel::vec2{ 1, 0 }.Rotate(shovel::math::degTorad(transform.rotation)) * speed;

	velocity = force;

	transform.position.x = shovel::math::wrap(transform.position.x, 0.0f, (float)shovel::GetEngine().GetRenderer().GetWidth());
	transform.position.y = shovel::math::wrap(transform.position.y, 0.0f, (float)shovel::GetEngine().GetRenderer().GetHeight());

	Actor::Update(dt);
}

void Rocket::OnColission(Actor* other)
{
	if (tag != other->tag)
	{
		destroyed = true;
	}
	std::cout << other->tag << std::endl;
}
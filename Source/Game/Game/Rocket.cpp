#include "../Game/GamePCH.h"
#include "Rocket.h"
#include "Core/Random.h"
#include "Renderer/ParticleSystem.h"
#include "Engine.h"
#include "Player.h"
#include "Framework/Scene.h"
#include "Renderer/Renderer.h"


FACTORY_REGISTER(Rocket)

void Rocket::Update(float dt)
{
//	// Update the transform rotation based on input
//	shovel::vec2 force = shovel::vec2{ 1, 0 }.Rotate(shovel::math::degTorad(transform.rotation)) * speed;
//
//	//velocity = force;
//	auto rb = GetComponent<shovel::RigidBody>();
//	if (rb)
//	{
//		rb->velocity = force;
//	}
//
//	transform.position.x = shovel::math::wrap(transform.position.x, 0.0f, (float)shovel::GetEngine().GetRenderer().GetWidth());
//	transform.position.y = shovel::math::wrap(transform.position.y, 0.0f, (float)shovel::GetEngine().GetRenderer().GetHeight());
//
//	float angle = transform.rotation + shovel::random::getReal(-60.0f, 60.0f);
//	shovel::vec2 velocity = shovel::vec2{ 1, 0 }.Rotate(shovel::math::degTorad(transform.rotation));
//	velocity *= shovel::random::getReal(100.0f, 200.0f);
//
//	shovel::Particle particle;
//	particle.position = transform.position;
//	particle.velocity = shovel::random::onUnitCircle() * shovel::random::getReal(10.0f, 200.0f);
//	particle.velocity = shovel::vec2{ shovel::random::getReal(-200.0f, 200.0f), shovel::random::getReal(-200.0f, 200.0f) };
//	particle.color = shovel::vec3{ 1, 1, 0 };
//	particle.lifetime = shovel::random::getReal(0.15f, 0.3f);
//
//	Actor::Update(dt);
}

void Rocket::OnCollision(shovel::Actor* other)
{
	if (owner->tag != other->tag)
	{
		owner->destroyed = true;
	}
	std::cout << other->tag << std::endl;
}
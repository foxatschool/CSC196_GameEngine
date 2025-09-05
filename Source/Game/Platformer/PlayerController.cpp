#include "PlayerController.h"

FACTORY_REGISTER(PlayerController)

void PlayerController::Start()
{
	m_rigidBody = owner->GetComponent<shovel::RigidBody>();
	collisionTag = CollisonTag::Noting;

	// create attack box
	

	for (float i = 0; i < lives; i++)
	{
		auto lifeIcon = shovel::Instantiate("lifeIcon");
		lifeIcon->transform.position = shovel::vec2{ 50.0f + (i * 50.0f), 50.0f };
		owner->scene->AddActor(std::move(lifeIcon));
	}
}

void PlayerController::Update(float dt)
{
	float dir = 0;
	auto spriterenderer = owner->GetComponent<shovel::SpriteRenderer>();

	if (shovel::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_A) && !attacking)
	{
		dir = -1;
		owner->GetComponent<shovel::Animator>()->Play("run");
		spriterenderer->flipH = true;
	}
		
	if (shovel::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_D) && !attacking)
	{
		dir = +1;
		owner->GetComponent<shovel::Animator>()->Play("run");
		spriterenderer->flipH = false;
	}

	if (dir != 0)
	{
		m_rigidBody->ApplyForce(shovel::vec2{1,0} * dir * 100);
	}
	else if (dir == 0 && collisionTag == CollisonTag::Ground && !attacking)
	{
		owner->GetComponent<shovel::Animator>()->Play("idle");
	}

	if (collisionTag == CollisonTag::Ground && shovel::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE) && !attacking)
	{
		m_rigidBody->ApplyForce(shovel::vec2{ 0,-1 } * 20000);
		owner->GetComponent<shovel::Animator>()->Play("jump");
		collisionTag = CollisonTag::Noting;
	}

	if (shovel::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_E))
	{
		slash();
	}
	if (attacking)
	{
		if (dir == 1)
		{
			if (attackBox)
			{
				auto autoattackBox = shovel::Instantiate("AttackBox");
				attackBox->owner->transform.position = owner->transform.position + shovel::vec2{ 20,0 };
				owner->scene->AddActor(std::move(autoattackBox));
			}
		}
		else if (dir == -1)
		{
			if (attackBox)
			{
				auto autoattackBox = shovel::Instantiate("AttackBox");
				attackBox->owner->transform.position = owner->transform.position + shovel::vec2{ -20,0 };
				owner->scene->AddActor(std::move(autoattackBox));
			}
		}
	}

	if (owner->GetComponent<shovel::Animator>()->frame == owner->GetComponent<shovel::Animator>()->GetEndFrame())
	{
		attacking = false;
	}


	/*auto spriterenderer = owner->GetComponent<shovel::SpriteRenderer>();
	if (spriterenderer)
	{
		if (shovel::math::fabs(m_rigidBody->velocity.x) > 0.1f)
		{ 
			spriterenderer->flipH = (m_rigidBody->velocity.x < 0 );
		}
	}*/
}
void PlayerController::Read(const shovel::json::value_t& value)
{
	Object::Read(value);

	JSON_READ(value, speed);
	JSON_READ(value, maxSpeed);
	JSON_READ(value, jump);
	JSON_READ(value, attackTime);

}

void PlayerController::OnCollision(class shovel::Actor* other)
{
	//std::cout << other->name << std::endl;
	// if colliding with ground
	if (other->tag == "ground")
	{
		collisionTag = CollisonTag::Ground;
	}
	// if colliding with enemy
	if (shovel::equalsIgnoreCase(other->tag, "enemy")) 
	{
		lives--;
		std::cout << lives << std::endl;
		if (lives == 0) {
			owner->destroyed = true;
		}
		owner->scene->RemoveAllActors("lifeIcon");
	}
}

void PlayerController::slash()
{
	attacking = true;
	owner->GetComponent<shovel::Animator>()->Play("attack");
}

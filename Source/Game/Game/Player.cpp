#include "Player.h"
#include "Engine.h"
#include "Input/InputSystem.h"
#include "Math/Math.h"

#include "SDL3/SDL.h"

void Player::Update(float dt)
{
    float speed = 200;
    float rotationRate = 180;

	// rotation
    float rotate = 0;
    if (shovel::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_A)) rotate = -1;
    if (shovel::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_D)) rotate = +1;

    m_transform.rotation += (rotate * rotationRate) * dt;

    // thrust
	float thrust = 0;
	if (shovel::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_W)) thrust = +1;
	if (shovel::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_S)) thrust = -.5;


    shovel::vec2 direction{ 1,0 };
    shovel::vec2 force = direction.Rotate(shovel::math::degTorad(m_transform.rotation)) * thrust * speed;
    velocity += force * dt;

	Actor::Update(dt);
}

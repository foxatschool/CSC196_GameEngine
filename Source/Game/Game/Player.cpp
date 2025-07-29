#include "Player.h"
#include "Engine.h"
#include "Input/InputSystem.h"
#include "Math/Math.h"

#include "SDL3/SDL.h"

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

	Actor::Update(dt);
}

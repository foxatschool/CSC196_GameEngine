#include <SDL3/SDL.h>
#include "../Engine/Core/Random.h"
#include <iostream>
#include "Renderer\Renderer.h"
#include "Math\Vector2.h"
#include "Core/Time.h"
#include "Input\InputSystem.h"
#include <vector>

int main(int argc, char* argv[]) {
	bool stop = false;
	shovel::Time time;

    shovel::Renderer renderer;
    shovel::InputSystem input;

    renderer.init();
	renderer.CreateWindow("Shovel Engine", 1280, 1024);
    input.Initialize();

    SDL_Event e;
    bool quit = false;

    // Define a rectangle
    SDL_FRect greenSquare{ 270, 190, 200, 200 };

    //Create Stars
    std::vector<shovel::vec2> stars;
    for (int i = 0; i < 100; i++)
    {
        stars.push_back(shovel::vec2{ shovel::random::getRandomFloat() * 1280, shovel::random::getRandomFloat() * 1024 });
    }
    shovel::vec2 v(30, 40);

    //Main loop
    while (!quit) 
    {
		time.Tick();
        while (SDL_PollEvent(&e)) 
        {
            if (e.type == SDL_EVENT_QUIT) 
            {
                quit = true;
            }
        }
		input.Update();

        if (input.GetKeyHeld(SDL_SCANCODE_A)) 
        {
			std::cout << "A key pressed!" << std::endl;
        }

        shovel::vec2 mouse = input.GetMousePosition();
		std::cout << "Mouse Position: " << mouse.x << ", " << mouse.y << std::endl;

		renderer.setColor(0, 0, 0);
		renderer.Clear();

        shovel::vec2 speed{ 40.0f, 0.0f };
        float lenght = speed.Length();
        for (shovel::vec2& star : stars)
        {
			star += speed * time.GetDeltaTime();
			if (star[0] > 1280) star[0] = 0;
            renderer.setColor(shovel::random::getRandomInt(255), shovel::random::getRandomInt(255), shovel::random::getRandomInt(255), shovel::random::getRandomInt(255));
			renderer.drawPoint(star.x, star.y);
        }
        renderer.present(); // Render the screen
    }
	renderer.shutDown();

    return 0;
}
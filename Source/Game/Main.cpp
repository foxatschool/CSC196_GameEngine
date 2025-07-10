#include <SDL3/SDL.h>
#include "../Engine/Core/Random.h"
#include <iostream>
#include "Renderer\Renderer.h"
#include "Math\Vector2.h"
#include "Core/Time.h"
#include "Input\InputSystem.h"
#include <vector>
#include <fmod.hpp>

int main(int argc, char* argv[]) {
	bool stop = false;
	shovel::Time time;

    shovel::Renderer renderer;
    shovel::InputSystem input;
    std::vector<shovel::vec2> points;

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
        // Update engine systems
		input.Update();

        //Get Input
        
        if (input.GetMouseButtonPresed(shovel::InputSystem::MouseButton::LEFT))
        {
            points.push_back(input.GetMousePosition());
        }

        if (input.GetMouseButtonDown(shovel::InputSystem::MouseButton::LEFT)) {
            shovel::vec2 position = input.GetMousePosition();
            if (points.size() == 0) points.push_back(position);
            else if ((position - points.back()).Length() > 10) points.push_back(position);
        }

        shovel::vec2 mouse = input.GetMousePosition();

        renderer.setColor(0, 0, 0);
        renderer.Clear();

        // Draw
        for (int i = 0; i < (int)points.size() - 1; i++) 
        {
            // set color or random color
            renderer.setColor(255, 255, 255);
            renderer.drawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
        }

        


        renderer.present(); // Render the screen
    }
	renderer.shutDown();

    return 0;
}
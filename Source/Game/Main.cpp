#include <SDL3/SDL.h>
#include "../Engine/Core/Random.h"
#include <iostream>
#include "Renderer\Renderer.h"
#include "Math\Vector2.h"

int main(int argc, char* argv[]) {
	bool stop = false;

    shovel::Renderer renderer;

    renderer.init();
	renderer.CreateWindow("Shovel Engine", 1280, 1024);

    SDL_Event e;
    bool quit = false;

    // Define a rectangle
    SDL_FRect greenSquare{ 270, 190, 200, 200 };

    vec2 v(30, 40);

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }
		renderer.setColor(0, 0, 0);
		renderer.Clear();

		renderer.setColor(shovel::random::getRandomInt(255), shovel::random::getRandomInt(255), shovel::random::getRandomInt(255), shovel::random::getRandomInt(255));
        if (!stop)
        {
            for (int i = 0; i < 10; i++)
            {
                float x1 = shovel::random::getRandomInt(1280);
                float y1 = shovel::random::getRandomInt(1024);
                float x2 = shovel::random::getRandomInt(1280);
                float y2 = shovel::random::getRandomInt(1024);

                float x = shovel::random::getRandomInt(1280);
                float y = shovel::random::getRandomInt(1024);

                renderer.setColor(shovel::random::getRandomInt(255), shovel::random::getRandomInt(255), shovel::random::getRandomInt(255), shovel::random::getRandomInt(255)); // Set the draw color to black
                renderer.drawLine(x1, y1, x2, y2);

                renderer.drawPoint(v.x, v.y);
                renderer.drawPoint(x + 5, y + 10);

				stop = true; // Stop after the first iteration
            }

            renderer.present(); // Render the screen
        }
    }
	renderer.shutDown();

    return 0;
}
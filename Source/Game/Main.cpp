#include <SDL3/SDL.h>
#include "../Engine/Core/Random.h"
#include <iostream>

int main(int argc, char* argv[]) {
	bool stop = false;

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("SDL3 Project", 1280, 1024, 0);
    if (window == nullptr) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);
    if (renderer == nullptr) {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Event e;
    bool quit = false;

    // Define a rectangle
    SDL_FRect greenSquare{ 270, 190, 200, 200 };

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }
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

                SDL_SetRenderDrawColor(renderer, shovel::random::getRandomInt(255), shovel::random::getRandomInt(255), shovel::random::getRandomInt(255), shovel::random::getRandomInt(255)); // Set the draw color to black
                SDL_RenderLine(renderer, x1, y1, x2, y2);

                SDL_RenderPoint(renderer, x, y);
                SDL_RenderPoint(renderer, x + 5, y + 10);

				stop = true; // Stop after the first iteration
            }

            SDL_RenderPresent(renderer); // Render the screen
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
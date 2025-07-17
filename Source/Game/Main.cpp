#include "../Engine/Core/Random.h"
#include "Renderer\Renderer.h"
#include "Math\Vector2.h"
#include "Math\Vector3.h"
#include "Core/Time.h"
#include "Input\InputSystem.h"
#include "AudioSystem\AudioSystem.h"
#include "Renderer\Model.h"
#include "Math\Transform.h"
#include "../Game/Actor.h"


#include <SDL3/SDL.h>
#include <iostream>
#include <vector>
#include <fmod.hpp>

int main(int argc, char* argv[]) {
    union delta_t
    {
        bool b;
        int i;
        double d;
    };

	bool stop = false;
	shovel::Time time;

    shovel::Renderer renderer;
    renderer.init();
    renderer.CreateWindow("Shovel Engine", 1280, 1024);

    shovel::InputSystem input;
    input.Initialize();
    //std::vector<shovel::vec2> points;
    std::vector<FMOD::Sound*> sounds;


    // create audio system
	shovel::AudioSystem audioSystem;
	audioSystem.Init();
    FMOD::Sound* sound = nullptr;

	// Initialize Sounds
	audioSystem.AddSound("bass.wav", "bass");
	audioSystem.AddSound("snare.wav", "snare");
    audioSystem.AddSound("close-hat.wav", "chihat");
    audioSystem.AddSound("open-hat.wav", "ohihat");
    audioSystem.AddSound("clap.wav", "clap");
    audioSystem.AddSound("cowbell.wav", "cowbell");
    audioSystem.AddSound("snare.wav", "snare");


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
    shovel::ivec2 v(30, 40);

    std::vector<shovel::vec2> points
    {
        {-5, -5},
        {5, -5},
        {5, 5},
        {-5, 5}
    };

    shovel::Model* model = new shovel::Model{ points, {0,0, 1} };

    std::vector<shovel::Actor> actors;
    for (int i = 0; i < 15; i++)
    {
        shovel::Transform transform{ shovel::vec2{shovel::random::getRandomFloat() * 1280, shovel::random::getRandomFloat() * 1024}, 0, 20};
        shovel::Actor actor{ transform, model };
        actors.push_back(actor);
    }

    //shovel::Model model{ points, {0, 0, 1} };

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

        if (input.GetKeyPressed(SDL_SCANCODE_ESCAPE)) quit = true;

        // Update engine systems
		input.Update();
		audioSystem.Update();

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

        float zero = 0;

        renderer.setColor(1.0f, 0.0f, 1.0f);
        renderer.Clear();

        //model.Draw(renderer, input.GetMousePosition(), shovel::math::halfPi * 0.5f, 10.0f);
        for (auto actor : actors)
        {
            actor.Draw(renderer);
        }
        

        //if (input.GetKeyDown(SDL_SCANCODE_A)) transform.rotation += shovel::math::degTorad(90 * time.GetDeltaTime());
        //if (input.GetKeyDown(SDL_SCANCODE_D)) transform.rotation -= shovel::math::degTorad(90 * time.GetDeltaTime());

        float Tspeed = 100;

        shovel::vec2 direction{ 0,0 };
        if (input.GetKeyDown(SDL_SCANCODE_W)) direction.y = - 1 * time.GetDeltaTime();
        if (input.GetKeyDown(SDL_SCANCODE_A)) direction.y = 1 * time.GetDeltaTime();
        if (input.GetKeyDown(SDL_SCANCODE_S)) direction.x = -1 * time.GetDeltaTime();
        if (input.GetKeyDown(SDL_SCANCODE_D)) direction.x = 1 * time.GetDeltaTime();

        if (direction.LengthSqr() > 0)
        {
            direction = direction.Normalized();
            for (auto actor : actors)
            {
                actor.GetTransform().position += (direction * Tspeed) * time.GetDeltaTime();
            }
        }

        // Draw
        shovel::vec3 color{ 1,0,0 };


        renderer.setColor(color.r, color.g, color.b);

        for (int i = 0; i < (int)points.size() - 1; i++) 
        {
            // set color or random color
            renderer.setColor((uint8_t)255, 255, 255);
            renderer.drawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
        }


        //Audio system
        if (input.GetKeyDown(SDL_SCANCODE_Q) && !input.GetPreviousKeyDown(SDL_SCANCODE_Q))
        {
            // play bass sound, vector elements can be accessed like an array with [#]
			audioSystem.PlaySound("bass");
        }

        if (input.GetKeyDown(SDL_SCANCODE_W) && !input.GetPreviousKeyDown(SDL_SCANCODE_W))
        {
            // play bass sound, vector elements can be accessed like an array with [#]
			audioSystem.PlaySound("snare");
        }

        if (input.GetKeyDown(SDL_SCANCODE_E) && !input.GetPreviousKeyDown(SDL_SCANCODE_E))
        {
            // play bass sound, vector elements can be accessed like an array with [#]
			audioSystem.PlaySound("hihat");
        }

        renderer.present(); // Render the screen
    }
	renderer.shutDown();

    return 0;
}
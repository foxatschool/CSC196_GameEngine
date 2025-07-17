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
#include "../Game/Scene.h"

#include "Game/Player.h"


#include <SDL3/SDL.h>
#include <iostream>
#include <vector>
#include <fmod.hpp>
#include <memory>

int main(int argc, char* argv[]) {
    union delta_t
    {
        bool b;
        int i;
        double d;
    };

	bool stop = false;
	shovel::Time time;

    std::unique_ptr<shovel::Renderer> renderer = std::make_unique<shovel::Renderer>();
    renderer->Init();
    renderer->CreateWindow("Shovel Engine", 1280, 1024);

    std::unique_ptr<shovel::InputSystem> input = std::make_unique<shovel::InputSystem>();
    input->Initialize();
    //std::vector<shovel::vec2> points;
    std::vector<FMOD::Sound*> sounds;


    // create audio system
	std::unique_ptr<shovel::AudioSystem> audioSystem = std::make_unique<shovel::AudioSystem>();
	audioSystem->Init();
    FMOD::Sound* sound = nullptr;

	// Initialize Sounds
	/*
    audioSystem->AddSound("bass.wav", "bass");
	audioSystem->AddSound("snare.wav", "snare");
    audioSystem->AddSound("close-hat.wav", "chihat");
    audioSystem->AddSound("open-hat.wav", "ohihat");
    audioSystem->AddSound("clap.wav", "clap");
    audioSystem->AddSound("cowbell.wav", "cowbell");
    */


    SDL_Event e;
    bool quit = false;


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
        {-5, 5},
        {-5, -5}
    };

    std::shared_ptr<shovel::Model> model = std::make_shared<shovel::Model>(points, shovel::vec3{ 0,0, 1 });

    shovel::Scene scene;
    for (int i = 0; i < 15; i++)
    {
        shovel::Transform transform{ shovel::vec2{shovel::random::getRandomFloat() * 1280, shovel::random::getRandomFloat() * 1024}, 0, 20};
        std::unique_ptr<Player> player = std::make_unique<Player>(transform, model);
        scene.AddActor(std::move(player));
    }

    //Main loop\\

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

        if (input->GetKeyPressed(SDL_SCANCODE_ESCAPE)) quit = true;

        // Update engine systems
		input->Update();
		audioSystem->Update();

        //Get Input//
        shovel::vec2 mouse = input->GetMousePosition();

        /*for (auto& actor : actors)
        {
            actor->Draw(*renderer);
        }
        */

        //Movement
        float Tspeed = 100;

        shovel::vec2 direction{ 0,0 };
        if (input->GetKeyDown(SDL_SCANCODE_W)) direction.y = - 1 * time.GetDeltaTime();
        if (input->GetKeyDown(SDL_SCANCODE_A)) direction.y = 1 * time.GetDeltaTime();
        if (input->GetKeyDown(SDL_SCANCODE_S)) direction.x = -1 * time.GetDeltaTime();
        if (input->GetKeyDown(SDL_SCANCODE_D)) direction.x = 1 * time.GetDeltaTime();

        if (direction.LengthSqr() > 0)
        {
            direction = direction.Normalized();
            /*for (auto& actor : actors)
            {
                actor->GetTransform().position += (direction * Tspeed) * time.GetDeltaTime();
            }*/
        }

        //SetBackground color
        shovel::vec3 color{ 0,0,0 };
        renderer->SetColor(color.r, color.g, color.b);
        renderer->Clear();
        

        //for (int i = 0; i < (int)points.size() - 1; i++) 
        //{
        //    // set color or random color
        //    renderer.setColor((uint8_t)255, 255, 255);
        //    renderer.drawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
        //}
        

        // How to do Audio system \\

        /*
        if (input->GetKeyDown(SDL_SCANCODE_Q) && !input->GetPreviousKeyDown(SDL_SCANCODE_Q))
        {
            // play bass sound, vector elements can be accessed like an array with [#]
			audioSystem->PlaySound("bass");
        }
        */
        //Draw
           for (int i = 0; i < (int)stars.size(); i++) 
        {
            // set color or random color
            renderer->SetColor((uint8_t)shovel::random::getRandomFloat() * 255, shovel::random::getRandomFloat() * 255, shovel::random::getRandomFloat() * 255);
            renderer->DrawPoint(stars[i].x, stars[i].y);
        }

        scene.Draw(*renderer);

        renderer->Present(); // Render the screen
    }
    //Shut evrything down
	renderer->ShutDown();
    audioSystem->ShutDown();
    input->Shutdown();

    return 0;
}
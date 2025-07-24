#include "../Engine/Core/Random.h"
#include "Renderer\Renderer.h"
#include "Math\Vector2.h"
#include "Math\Vector3.h"
#include "Core/Time.h"
#include "Input\InputSystem.h"
#include "AudioSystem\AudioSystem.h"
#include "Renderer\Model.h"
#include "Math\Transform.h"
#include "Framework/Actor.h"
#include "Framework/Scene.h"
#include "Engine.h"

#include "Game/Player.h"
#include "Game/SpaceGame.h"

#include <SDL3/SDL.h>
#include <iostream>
#include <vector>
#include <fmod.hpp>
#include <memory>


int main(int argc, char* argv[]) {

	shovel::GetEngine().Initialize();

    // Iinitalize Game
	std::unique_ptr<SpaceGame> game = std::make_unique<SpaceGame>();
    game->Initialize();

    union delta_t
    {
        bool b;
        int i;
        double d;
    };

	bool stop = false;
	
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


   
    //Main loop\\

    while (!quit) 
    {
        while (SDL_PollEvent(&e)) 
        {
            if (e.type == SDL_EVENT_QUIT) 
            {
                quit = true;
            }
        }

        shovel::GetEngine().Update();
		game->Update();
		

        if (shovel::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_ESCAPE)) quit = true;

        //SetBackground color
        shovel::vec3 color{ 0,0,0 };
        shovel::GetEngine().GetRenderer().SetColor(color.r, color.g, color.b);
        shovel::GetEngine().GetRenderer().Clear();

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
		game->Draw();
           

        

        shovel::GetEngine().GetRenderer().Present(); // Render the screen
    }
    //Shut evrything down
    shovel::GetEngine().Shutdown();

    return 0;
}
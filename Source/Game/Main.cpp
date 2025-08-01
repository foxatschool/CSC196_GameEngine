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
#include "Renderer/Text.h"
#include "Renderer/Font.h"
#include "Core/File.h"

#include "Game/Player.h"
#include "Game/SpaceGame.h"

#include <SDL3/SDL.h>
#include <iostream>
#include <vector>
#include <fmod.hpp>
#include <memory>


int main(int argc, char* argv[]) {
    shovel::file::SetCurrentDirectory("Assets");

	// Initialize Evrything
	shovel::GetEngine().Initialize();


	//font = new shovel::Font();
    //font->Load("Eight-Bit Madness.ttf", 20);

    //shovel::Text* text = new shovel::Text(font);
    //text->Create(shovel::GetEngine().GetRenderer(), "Hello World", shovel::vec3{1.0f, 1.0f, 1.0f});


    // Iinitalize Game
	std::unique_ptr<SpaceGame> game = std::make_unique<SpaceGame>();
    game->Initialize();
	
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


		// Update the game and engine
        shovel::GetEngine().Update();
		game->Update(shovel::GetEngine().GetTime().GetDeltaTime());
		
		// Check for exit imput
        if (shovel::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_ESCAPE)) quit = true;

        //SetBackground color
        shovel::vec3 color{ 0,0,0 };
        shovel::GetEngine().GetRenderer().SetColor(color.r, color.g, color.b);
        shovel::GetEngine().GetRenderer().Clear();

		// Draw the game
        
        // How to do Audio system \\

        /*
        if (input->GetKeyDown(SDL_SCANCODE_Q) && !input->GetPreviousKeyDown(SDL_SCANCODE_Q))
        {
            // play bass sound, vector elements can be accessed like an array with [#]
			audioSystem->PlaySound("bass");
        }
        */

		//Draw the game scene
		game->Draw(shovel::GetEngine().GetRenderer());
           

        // Render the screen
        shovel::GetEngine().GetRenderer().Present();
    }
    //Shut evrything down
	game->ShutDown();
    game.release();
    shovel::GetEngine().Shutdown();

    return 0;
}
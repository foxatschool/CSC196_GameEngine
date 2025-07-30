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


    // Get current directory path
    std::cout << "Directory Operations:\n";
    std::cout << "Current directory: " << shovel::file::GetCurrentDirectory() << "\n";

    // Set current directory path (current path + "Assets")
    std::cout << "Setting directory to 'Assets'...\n";
    shovel::file::SetCurrentDirectory("Assets");
    std::cout << "New directory: " << shovel::file::GetCurrentDirectory() << "\n\n";

    // Get filenames in the current directory
    std::cout << "Files in Directory:\n";
    auto filenames = shovel::file::GetFilesInDirectory(shovel::file::GetCurrentDirectory());
    for (const auto& filename : filenames) {
        std::cout << filename << "\n";
    }
    std::cout << "\n";

    // Get filename (filename.extension) only
    if (!filenames.empty()) {
        std::cout << "Path Analysis:\n";
        std::string filename = shovel::file::GetFilename(filenames[0]);
        std::cout << "Filename only: " << filename << "\n";

        // Get extension only
        std::string ext = shovel::file::GetExtension(filenames[0]);
        std::cout << "Extension: " << ext << "\n\n";
    }

    // Read and display text file
    std::cout << "Text File Reading:\n";
    std::string str;
    bool success = shovel::file::ReadTextFile("test.txt", str);
    if (success) {
        std::cout << "Contents of test.txt:\n";
        std::cout << str << "\n";
    }
    else {
        std::cout << "Failed to read test.txt\n";
    }

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
        //text->Draw(shovel::GetEngine().GetRenderer(), 40.0f, 40.0f);
        

        // How to do Audio system \\

        /*
        if (input->GetKeyDown(SDL_SCANCODE_Q) && !input->GetPreviousKeyDown(SDL_SCANCODE_Q))
        {
            // play bass sound, vector elements can be accessed like an array with [#]
			audioSystem->PlaySound("bass");
        }
        */

		//Draw the game scene
		game->Draw();
           

        // Render the screen
        shovel::GetEngine().GetRenderer().Present();
    }
    //Shut evrything down
	game->ShutDown();
    game.release();
    shovel::GetEngine().Shutdown();

    return 0;
}
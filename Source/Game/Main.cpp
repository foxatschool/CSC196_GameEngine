#include "Game/SpaceGame.h"
#include "Platformer/PlatformerGame.h"

int main(int argc, char* argv[]) {
    shovel::file::SetCurrentDirectory("Assets/Platformer");

	// Initialize Evrything
	shovel::GetEngine().Initialize();
    shovel::Logger::Info("Initalizing Engine .  .   .");

    // Iinitalize Game
	//std::unique_ptr<PlatformerGame> game = std::make_unique<PlatformerGame>();
	std::unique_ptr<PlatformerGame> game = std::make_unique<PlatformerGame>();
    game->Initialize();

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

/*
**** How-To's ****
* Animation
* Switching Animation: owner->GetComponent<shovel::Animator>()->Play("<animation name>");
-------------------------------------
* Pickups
* auto varname = shovel::Instantiate("<name of thing in json>");
* m_scene->AddActor(std::move(varname));
-------------------------------------
* 
*/
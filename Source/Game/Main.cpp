#include "Game/SpaceGame.h"
class A
{
public:
    A() = default;
	A(int size) : size{ size } {
        buffer = new int[size];
		for (int i = 0; i < size; ++i) buffer[i] = i;
    }
    A(const A& other) : 
        size{ other.size }
    {
        buffer = new int[other.size];
        for (int i = 0; i < size; ++i) buffer[i] = i;
    }// copy constructor

    A& operator = (const A& other)
    {
		size = other.size;
        buffer = other.buffer;
        return *this;
    } // copy assignment operator
	~A() = default;


public:
    int size{ 0 };
	int* buffer{ nullptr };
};


int main(int argc, char* argv[]) {
    A a1{ 4 };
	std::cout << a1.size << std::endl;

	A a2{ a1 };// copy constructor
	std::cout << a2.size << std::endl;

    A a3;
	a3 = a1; // assignment operator
	std::cout << a3.size << std::endl;
    return 0;

    shovel::file::SetCurrentDirectory("Assets");
    
    // command line arguments
    std::cout << argc << std::endl;
	for (int i = 0; i < argc; ++i) 
    {
        // c - string;
		shovel::Logger::Debug("arg {}: {}", i, argv[i]);
	}

    //file streams
    std::fstream stream("test.txt");
    if (!stream)
    {
		std::cout << "Failed to open file!" << std::endl;
    }
  //  else
  //  {
		//std::cout << stream.rdbuf() << std::endl; // read the file
  //  }
	std::string line;
    
    while (std::getline(stream, line))
    {
		std::cout << line << std::endl; // print each line
    }

    // basic / built in
    //int, float, double, bool, short, long

    // user data type streams
	//vec2, vec3, texture
	shovel::vec2 v{ 34.5f, 65.5f };
	std::cout << v << std::endl;

    shovel::vec3 v3{ 34.5f, 65.5f, 55.6f };
    std::cout << v3 << std::endl;

    std::string vstr("{ 23.4 , 35.7 }");
    std::stringstream vstream(vstr);

	shovel::vec2 v2;
    vstream >> v2;

    std::cout << v2 << std::endl;

    return 0;

	// Initialize Evrything
	shovel::GetEngine().Initialize();
    shovel::Logger::Info("Initalizing Engine .  .   .");

    // create texture, using shared_ptr so texture can be shared
    //std::shared_ptr<shovel::Texture> texture = std::make_shared<shovel::Texture>();
    //texture->Load(...texture filename..., renderer);
    
	//auto texture = shovel::Resources().Get<shovel::Texture>("texture.png", shovel::GetEngine().GetRenderer());

	//font = new shovel::Font();
    //font->Load("Eight-Bit Madness.ttf", 20);

    //shovel::Text* text = new shovel::Text(font);
    //text->Create(shovel::GetEngine().GetRenderer(), "Hello World", shovel::vec3{1.0f, 1.0f, 1.0f});


    // Iinitalize Game
	std::unique_ptr<SpaceGame> game = std::make_unique<SpaceGame>();
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
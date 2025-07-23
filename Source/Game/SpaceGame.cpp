#include "SpaceGame.h"

#include "Framework/Scene.h"
#include "Math/Vector2.h"
#include "Renderer/Model.h"
#include "Game/Player.h"
#include "Core/Random.h"
#include "Engine.h"
#include "Renderer/Renderer.h"



bool SpaceGame::Initialize()
{
	m_scene = std::make_unique<shovel::Scene>();

    //Create Stars
    std::vector<shovel::vec2> stars;
    for (int i = 0; i < 100; i++)
    {
        stars.push_back(shovel::vec2{ shovel::random::getRandomFloat() * 1280, shovel::random::getRandomFloat() * 1024 });
    }
    shovel::ivec2 v(30, 40);

    for (int i = 0; i < (int)stars.size(); i++)
    {
        // set color or random color
        shovel::GetEngine().GetRenderer().SetColor((uint8_t)shovel::random::getRandomFloat() * 255, shovel::random::getRandomFloat() * 255, shovel::random::getRandomFloat() * 255);
        shovel::GetEngine().GetRenderer().DrawPoint(stars[i].x, stars[i].y);
    }

    // Set up Object to draw
    std::vector<shovel::vec2> points
    {
        {2,12},
        {2,6},
        {4,6},
        {4,4},
        {5,4},
        {5,0},
        {6,-3},
        {6,-4},
        {7,-10},
        {7,-12},
        {5,-12},
        {4,-13},
        {1,-13},
        {0,-12},
        {-1,-13},
        {-4,-13},
        {-5,-12},
        {-7,-12},
        {-7,-10},
        {-6,-4},
        {-6,-3},
        {-5,0},
        {-5,4},
        {-4,4},
        {-4,6},
        {-2,6},
        {-2,12},
        {2,12}
    };

    std::shared_ptr<shovel::Model> model = std::make_shared<shovel::Model>(points, shovel::vec3{ 0,0, 1 });

    shovel::Transform transform{ shovel::vec2{shovel::GetEngine().GetRenderer().GetWidth() * 0.5f, shovel::GetEngine().GetRenderer().GetHeight() * 0.5f}, 0, 20};
    std::unique_ptr<Player> player = std::make_unique<Player>(transform, model);
    m_scene->AddActor(std::move(player));


    /*
    for (int i = 0; i < 15; i++)
    {
        shovel::Transform transform{ shovel::vec2{shovel::random::getRandomFloat() * 1280, shovel::random::getRandomFloat() * 1024}, 0, 20 };
        std::unique_ptr<Player> player = std::make_unique<Player>(transform, model);
        m_scene->AddActor(std::move(player));
    }
    */

    

    return false;
}

void SpaceGame::Update()
{
    m_scene->Update(shovel::GetEngine().GetTime().GetDeltaTime());
}

void SpaceGame::Draw()
{
    m_scene->Draw(shovel::GetEngine().GetRenderer());
}

void SpaceGame::ShutDown()
{
}

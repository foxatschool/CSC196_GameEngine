#include "SpaceGame.h"

#include "Framework/Scene.h"
#include "Math/Vector2.h"
#include "Renderer/Model.h"
#include "Player.h"
#include "Enemy.h"
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
        shovel::GetEngine().GetRenderer().SetColor(shovel::random::getRandomFloat(), shovel::random::getRandomFloat(), shovel::random::getRandomFloat());
        shovel::GetEngine().GetRenderer().DrawPoint(stars[i].x, stars[i].y);
    }

    // Set up Object to draw
    std::vector<shovel::vec2> points
    {
        { 9, 1 },
        { 5, 1 },
        { 5, 2 },
        { 1, 2 },
        { 2, 2 },
        { 1, 3 },
        { -4, 3 },
        { -5, 2 },
        { -4, 2 },
        { -5, 1 },
        { -5, -1 },
        { -4, -2 },
        { -5, -2 },
        { -4, -3 },
        { 1, -3 },
        { 2, -2 },
        { 1, -2 },
        { 5, -2 },
        { 5, -1 },
        { 9, -1 },
        { 9, 1 },
    };

    std::shared_ptr<shovel::Model> model = std::make_shared<shovel::Model>(points, shovel::vec3{ 0,0, 1 });
    //create player
    shovel::Transform transform{ shovel::vec2{shovel::GetEngine().GetRenderer().GetWidth() * 0.5f, shovel::GetEngine().GetRenderer().GetHeight() * 0.5f}, 0, 8};
    std::unique_ptr<Player> player = std::make_unique<Player>(transform, model);
	player->damping = 0.5f;
	player->speed = 500.0f;
	player->damping = 0.1f; 
    player->name = "Player";
    m_scene->AddActor(std::move(player));

    std::shared_ptr<shovel::Model> enemyModel = std::make_shared<shovel::Model>(points, shovel::vec3{ 1, 0, 0 });
    //create enemy
    for (int i = 0; i < 10; i++)
    {
		shovel::Transform transform{ shovel::vec2{shovel::random::getRandomFloat() * 1280, shovel::random::getRandomFloat() * 1024}, 0, 20 };
		std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(transform, enemyModel);
		enemy->velocity = shovel::vec2{ shovel::random::getRandomFloat() * 100 - 50, shovel::random::getRandomFloat() * 100 - 50 };
        enemy->damping = 1.5f;
		m_scene->AddActor(std::move(enemy));
    }

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

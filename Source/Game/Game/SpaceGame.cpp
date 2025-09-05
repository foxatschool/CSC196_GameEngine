#include "SpaceGame.h"
#include "../Game/GamePCH.h"

#include "Framework/Scene.h"
#include "Math/Vector2.h"
#include "Renderer/Mesh.h"
#include "Player.h"
#include "Enemy.h"
#include "Core/Random.h"
#include "Engine.h"
#include "Renderer/Renderer.h"
#include "Input/InputSystem.h"
#include "Renderer/ParticleSystem.h"
#include "Framework/Scene.h"
#include "../GameData.h"
#include "Resources/ResourceManager.h"
#include "Core/Json.h"
#include "Event/Observer.h"



bool SpaceGame::Initialize()
{

    OBSERVER_ADD("player_dead");
    OBSERVER_ADD("add_points");


    shovel::EventManager::Instance().AddObserver("player_dead", *this);
    shovel::EventManager::Instance().AddObserver("add_points", *this);

	m_scene = std::make_unique<shovel::Scene>(this);
	m_scene->Load("scene.json");

	m_titleText = std::make_unique<shovel::Text>(shovel::Resources().GetWithID<shovel::Font>("title_font", "Eight-Bit Madness.ttf", 128.0f));
	m_scoreText = std::make_unique<shovel::Text>(shovel::Resources().GetWithID<shovel::Font>("ui_font", "Eight-Bit Madness.ttf", 48.0f));
	m_livesText = std::make_unique<shovel::Text>(shovel::Resources().GetWithID<shovel::Font>("ui_font", "Eight-Bit Madness.ttf", 48.0f));
    m_bulletText = std::make_unique<shovel::Text>(shovel::Resources().GetWithID<shovel::Font>("ui_font", "Eight-Bit Madness.ttf", 48.0f));

    m_bulletModel = std::make_unique<shovel::Mesh>(GameData::BulletPoints, shovel::vec3{ 1.0,1.0,1.0 });
    return true;
}

void SpaceGame::Update(float dt)
{
	// Update the game state and move to diffrent states as needed.
    switch (m_gameState)
    {
    case SpaceGame::GameState::Initalize:
		m_gameState = SpaceGame::GameState::Title;
        break;
    case SpaceGame::GameState::Title:
		if (shovel::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE))
		{
			m_gameState = SpaceGame::GameState::StartGame;
		}
        break;
    case SpaceGame::GameState::StartGame:
    {
		m_score = 0;
		m_lives = 3;
		m_gameState = SpaceGame::GameState::StartRound;
    }
        break;
    case SpaceGame::GameState::Game:
        m_enemySpawnTimer -= dt;
		if (m_enemySpawnTimer <= 0)
		{
			m_enemySpawnTimer = 4; // Reset timer
			// Spawn an enemy
			SpawnEnemy();

		}
        break;
    case SpaceGame::GameState::StartRound:
    {
        m_scene->RemoveAllActors();

        auto player = shovel::Factory::Instance().Create<shovel::Actor>("player");
		m_scene->AddActor(std::move(player));

        m_gameState = GameState::Game;
    }
        break;
    case SpaceGame::GameState::PlayerDead:
        m_stateTimer -= dt;
		if (m_stateTimer <= 0.0f)
		{
            m_lives--;
        
            if (m_lives == 0)
            {
                GameState::GameOver;
                break;
            }
            else
            {
			    m_gameState = GameState::StartRound;
            }
			m_stateTimer = 2.0f; // Reset the timer for the next round
		}
        break;
    case SpaceGame::GameState::GameOver:
        m_gameState = GameState::Title;
        break;
    default:
        break;

    }
	if (shovel::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_Q))
	{
		shovel::GetEngine().GetTime().setTimeScale(0.5f);
    }
    else
    {
		shovel::GetEngine().GetTime().setTimeScale(1.0f);
    }

    m_scene->Update(shovel::GetEngine().GetTime().GetDeltaTime());
}

void SpaceGame::Draw(shovel::Renderer& renderer)
{
    m_scene->Draw(renderer);

    if (m_gameState == SpaceGame::GameState::Title)
    {
        m_titleText->Create(renderer, "SPACE CADETS", shovel::vec3(1, 1, 0));
        m_titleText->Draw(renderer, 400, 400);
    }
    if (m_gameState == SpaceGame::GameState::GameOver)
    {
        m_titleText->Create(renderer, "GameOver", shovel::vec3(1, 1, 0));
        m_titleText->Draw(renderer, 400, 400);
    }
    m_scoreText->Create(renderer, "SCORE: " + std::to_string(m_score), {1,1,1});
	m_scoreText->Draw(renderer, 10, 10);

    if (m_scene->GetActorByName<Player>("Player"))
    {
	    for (int i = 0; i < (m_scene->GetActorByName<Player>("Player"))->bulletCount; i++)
	    {
            m_bulletModel->Draw(renderer, { (10.0f + ((i + 10.0f) * 50.0f)), 30.0f }, 270, 10);
	    }
    }
	m_livesText->Create(renderer, "LIVES: " + std::to_string(m_lives), { 1,1,1 });
	m_livesText->Draw(renderer, (float)renderer.GetWidth() - 300, (float)30);


	shovel::GetEngine().GetPS().Draw(renderer);
}
void SpaceGame::SpawnEnemy()
{
	shovel::Actor* player = m_scene->GetActorByName<shovel::Actor>("player");
    if (player)
    {
        //spawn enemy at a random position around the player
        shovel::vec2 position = player->transform.position + shovel::random::onUnitCircle() * shovel::random::getReal(200.0f, 500.0f);
        shovel::Transform transform{ position, shovel::random::getReal<float>(0.0f, 360.0f), 0.2f };

        auto enemy = shovel::Instantiate("enemy", transform);
        m_scene->AddActor(std::move(enemy));
    }
}

void SpaceGame::ShutDown()
{
}

void SpaceGame::OnNotify(const shovel::Event& event)
{
    if (shovel::equalsIgnoreCase(event.id, "player_dead"))
    {
        OnPlayerDeath();
    }
    else if (shovel::equalsIgnoreCase(event.id, "add_points"))
    {
        AddPoints(std::get<int>(event.data));
    }
}

void SpaceGame::OnPlayerDeath()
{
    m_gameState = GameState::PlayerDead;
	m_stateTimer = 2.0f; // Wait for 2 seconds before restarting
}

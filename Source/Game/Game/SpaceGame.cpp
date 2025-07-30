#include "SpaceGame.h"

#include "Framework/Scene.h"
#include "Math/Vector2.h"
#include "Renderer/Model.h"
#include "Player.h"
#include "Enemy.h"
#include "Core/Random.h"
#include "Engine.h"
#include "Renderer/Renderer.h"
#include "Input/InputSystem.h"
#include "../GameData.h"



bool SpaceGame::Initialize()
{
	m_scene = std::make_unique<shovel::Scene>(this);

	m_titleFont = std::make_shared<shovel::Font>();
	m_titleFont->Load("Eight-Bit Madness.ttf", 128);

	m_uiFont = std::make_shared<shovel::Font>();
	m_uiFont->Load("Eight-Bit Madness.ttf", 48);

	m_titleText = std::make_unique<shovel::Text>(m_titleFont);
	m_scoreText = std::make_unique<shovel::Text>(m_uiFont);
	m_livesText = std::make_unique<shovel::Text>(m_uiFont);

    return true;
}

void SpaceGame::Update(float dt)
{
	// Update the game state and move to diffrent states as needed.
    switch (m_gameState)
    {
    case SpaceGame::GameState::Initalize:
		m_gameState = SpaceGame::GameState::StartGame;
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
			std::shared_ptr<shovel::Model> enemyModel = std::make_shared<shovel::Model>(GameData::ShipPoint, shovel::vec3{0,1,0});
			shovel::Transform transform{ shovel::vec2{shovel::random::getReal() * 1280, shovel::random::getReal() * 1024}, 0, 8 };
			std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(transform, enemyModel);
			enemy->velocity = shovel::vec2{ shovel::random::getReal() * 100 - 50, shovel::random::getReal() * 100 - 50 };
			enemy->damping = 1.5f;
			enemy->name = "Enemy";
			enemy->speed = 0;
			m_scene->AddActor(std::move(enemy));

		}
        break;
    case SpaceGame::GameState::StartRound:
    {
        //Create player.
        std::shared_ptr<shovel::Model> playerModel = std::make_shared<shovel::Model>(GameData::ShipPoint, shovel::vec3{ 0,1,0 });
        shovel::Transform transform{ shovel::vec2{shovel::GetEngine().GetRenderer().GetWidth() * 0.5f, shovel::GetEngine().GetRenderer().GetHeight() * 0.5f}, 0, 8 };
        auto player = std::make_unique<Player>(transform, playerModel);
        player->damping = 0.5f;
        player->speed = 500.0f;
        player->damping = 0.1f;
        player->name = "Player";
        player->tag = "Player";
        m_scene->AddActor(std::move(player));
        m_gameState = SpaceGame::GameState::Game;
    }
        break;
    case SpaceGame::GameState::PlayerDead:
        m_lives--;
        if (m_lives == 0) GameState::GameOver;
        else
        {
			m_gameState = GameState::StartRound;
        }
        break;
    case SpaceGame::GameState::GameOver:
        break;
    default:
        break;

    }
    m_scene->Update(shovel::GetEngine().GetTime().GetDeltaTime());
}

void SpaceGame::Draw()
{
    m_scene->Draw(shovel::GetEngine().GetRenderer());
}

void SpaceGame::ShutDown()
{
}

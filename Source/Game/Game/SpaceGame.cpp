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
#include "Renderer/ParticalSystem.h"
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
        //Create player.
        std::shared_ptr<shovel::Model> playerModel = std::make_shared<shovel::Model>(GameData::ShipPoint, shovel::vec3{ 0,1,0 });
        shovel::Transform transform{ shovel::vec2{shovel::GetEngine().GetRenderer().GetWidth() * 0.5f, shovel::GetEngine().GetRenderer().GetHeight() * 0.5f}, 0, 8 };
        auto player = std::make_unique<Player>(transform, playerModel);
        player->damping = 1.5f;
        player->speed = 500.0f;
        player->name = "Player";
        player->tag = "Player";
        m_scene->AddActor(std::move(player));
        m_gameState = SpaceGame::GameState::Game;
    }
        break;
    case SpaceGame::GameState::PlayerDead:
        m_stateTimer -= dt;
		if (m_stateTimer <= 0.0f)
		{
            m_lives--;
        
            if (m_lives == 0) GameState::GameOver;
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

	for (int i = 0; i < (m_scene->GetActorByName("Player")).bulletCount; i++)
	{
		renderer.DrawLine();
	}
	m_livesText->Create(renderer, "LIVES: " + std::to_string(m_lives), { 1,1,1 });
	m_livesText->Draw(renderer, (float)renderer.GetWidth() - 300, (float)30);

    m_scene->Draw(renderer);

	shovel::GetEngine().GetPS().Draw(renderer);
}

void SpaceGame::ShutDown()
{
}

void SpaceGame::OnPlayerDeath()
{
    m_gameState = GameState::PlayerDead;
	m_stateTimer = 2.0f; // Wait for 2 seconds before restarting
}

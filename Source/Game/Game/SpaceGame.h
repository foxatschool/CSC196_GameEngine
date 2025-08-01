#pragma once
#include "Framework/Game.h"
#include "Renderer/Text.h"
#include "Renderer/Font.h"
#include "../GameData.h"
#include "Framework/Scene.h"
#include "../Engine/Core/Random.h"
#include "Player.h"
#include "Enemy.h"

class SpaceGame : public shovel::Game
{
public:
	enum class GameState 
	{
		Initalize,
		Title,
		StartGame,
		StartRound,
		Game,
		PlayerDead,
		GameOver,
	};
public:
	SpaceGame() = default;

	// Inherited via Game
	bool Initialize() override;
	void Update(float dt) override;
	void Draw(class shovel::Renderer& renderer) override;
	void ShutDown() override;



	void OnPlayerDeath();

private:
	void SpawnEnemy()
	{
		Player* player = m_scene->GetActorByName<Player>("Player");
		if (player)
		{
			std::shared_ptr<shovel::Model> enemyModel = std::make_shared<shovel::Model>(GameData::ShipPoint, shovel::vec3{ 1,1,1 });

			//spawn enemy at a random position around the player
			shovel::vec2 position = player->transform.position + shovel::random::onUnitCircle() * shovel::random::getReal(200.0f, 500.0f);
			shovel::Transform transform{ position, shovel::random::getReal<float>(0.0f, 360.0f), 8};

			// Create a new enemy actor
			std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(transform, enemyModel);
			enemy->velocity = shovel::vec2{ shovel::random::getReal() * 100 - 50, shovel::random::getReal() * 100 - 50 };
			enemy->damping = 1.5f;
			enemy->fireTimer = 3.0f; // Time between shots
			enemy->name = "Enemy";
			enemy->tag = "Enemy";
			enemy->speed = 100;
			m_scene->AddActor(std::move(enemy));
		}


	}

	GameState m_gameState = GameState::Initalize;
	float m_enemySpawnTimer{ 0 };
	float m_stateTimer{ 0 };

	std::shared_ptr<shovel::Font> m_titleFont;
	std::shared_ptr<shovel::Font> m_uiFont;

	std::unique_ptr<shovel::Text> m_titleText;
	std::unique_ptr<shovel::Text> m_scoreText;
	std::unique_ptr<shovel::Text> m_livesText;

};

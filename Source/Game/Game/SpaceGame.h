#pragma once
#include "Framework/Game.h"
#include "Renderer/Text.h"
#include "Renderer/Font.h"
#include "../GameData.h"
#include "Renderer/Mesh.h"

#include "../Engine/Core/Random.h"
#include "Player.h"
#include "Enemy.h"

class SpaceGame : public shovel::Game, public shovel::IObserver
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

	void OnNotify(const shovel::Event& event) override;

	// Inherited via Game
	bool Initialize() override;
	void Update(float dt) override;
	void Draw(class shovel::Renderer& renderer) override;
	void ShutDown() override;



	void OnPlayerDeath();
	void SpawnEnemy();

private:


	GameState m_gameState = GameState::Initalize;
	float m_enemySpawnTimer{ 0 };
	float m_stateTimer{ 0 };


	std::unique_ptr<shovel::Text> m_titleText;
	std::unique_ptr<shovel::Text> m_scoreText;
	std::unique_ptr<shovel::Text> m_livesText;
	std::unique_ptr<shovel::Text> m_bulletText;

	std::unique_ptr<shovel::Mesh> m_bulletModel;

};

#pragma once
#include "Framework/Game.h"

class SpaceGame : public shovel::Game
{
public:
	enum class GameState 
	{
		Initalize,
		Title,
		StartGame,
		Game,
		StartRound,
		PlayerDead,
		GomeOver,
	};
public:
	SpaceGame() = default;

	// Inherited via Game
	bool Initialize() override;
	void Update(float dt) override;
	void ShutDown() override;
	void Draw() override;


private:
	GameState m_gameState = GameState::Initalize;
	float m_enemySpawnTimer{ 0 };
};

#pragma once
#include "Framework/Game.h"
#include "Renderer/Text.h"
#include "Renderer/Font.h"

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
	void Draw() override;
	void ShutDown() override;


private:
	GameState m_gameState = GameState::Initalize;
	float m_enemySpawnTimer{ 0 };

	std::shared_ptr<shovel::Font> m_titleFont;
	std::shared_ptr<shovel::Font> m_uiFont;

	std::unique_ptr<shovel::Text> m_titleText;
	std::unique_ptr<shovel::Text> m_scoreText;
	std::unique_ptr<shovel::Text> m_livesText;

};

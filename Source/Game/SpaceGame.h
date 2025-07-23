#pragma once
#include "Framework/Game.h"

class SpaceGame : public shovel::Game
{
public:
	SpaceGame() = default;

	// Inherited via Game
	bool Initialize() override;
	void Update() override;
	void ShutDown() override;
	void Draw() override;


private:

};

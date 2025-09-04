#include "PlatformerGame.h"
#include "EnginePCH.h"
#include "Engine.h"



bool PlatformerGame::Initialize() 
{
    OBSERVER_ADD("player_dead");
    OBSERVER_ADD("add_points");

    m_scene = std::make_unique<shovel::Scene>(this);
    m_scene->Load("Scenes/prototype.json");
    m_scene->Load("Scenes/level.json");
    
    return false;
}

void PlatformerGame::Update(float dt) 
{
    switch (m_gameState)
    {
    case PlatformerGame::GameState::Initalize:
    {
        m_gameState = GameState::StartRound;

    }
        break;
    case PlatformerGame::GameState::Title:
    {

    }
        break;
    case PlatformerGame::GameState::StartGame:
    {

    }
        break;
    case PlatformerGame::GameState::StartRound:
    {
        SpawnPlayer();
        m_gameState = GameState::Game;
    }
        break;
    case PlatformerGame::GameState::Game:
    {
		m_enemySpawnTimer += dt;
		if (m_enemySpawnTimer >= 2.0f)
		{
			m_enemySpawnTimer = 0;
			SpawnEnemy();
		}
    }
        break;
    case PlatformerGame::GameState::PlayerDead:
    {

    }
        break;
    case PlatformerGame::GameState::GameOver:
    {

    }
        break;
    default:
        break;
    }

    m_scene->Update(shovel::GetEngine().GetTime().GetDeltaTime());
}

void PlatformerGame::Draw(class shovel::Renderer& renderer) 
{
    m_scene->Draw(renderer);
    shovel::GetEngine().GetPS().Draw(renderer);
}

void PlatformerGame::OnPlayerDeath() 
{

}

void PlatformerGame::OnNotify(const shovel::Event& event) 
{

}

void PlatformerGame::ShutDown() 
{

}

void PlatformerGame::SpawnEnemy() 
{
    auto bat = shovel::Instantiate("bat");
    switch (shovel::random::getInt(1, 4))
    {
	case 1:
		bat->transform.position = shovel::vec2{ 0, 0 };
		break;
	case 2:
		bat->transform.position = shovel::vec2{ 1000, 500 };
		break;
	case 3:
		bat->transform.position = shovel::vec2{ 1000, 0 };
		break;
	case 4:
		bat->transform.position = shovel::vec2{ 500, 500 };
		break;
    default:
        break;
    }
    m_scene->AddActor(std::move(bat));
}

void PlatformerGame::SpawnPlayer()
{
    auto player = shovel::Instantiate("platformPlayer");
    //player->transform.position = shovel::vec2{shovel::random::getReal(0, 1000), }, 
    m_scene->AddActor(std::move(player));
}

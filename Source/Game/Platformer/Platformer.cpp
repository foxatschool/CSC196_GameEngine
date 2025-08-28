#include "PlatformerGame.h"


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
        m_gameState = GameState::StartRound;
        break;
    case PlatformerGame::GameState::Title:
        break;
    case PlatformerGame::GameState::StartGame:
        break;
    case PlatformerGame::GameState::StartRound:
        SpawnPlayer();
        m_gameState = GameState::Game;
        break;
    case PlatformerGame::GameState::Game:
        break;
    case PlatformerGame::GameState::PlayerDead:
        break;
    case PlatformerGame::GameState::GameOver:
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

}

void PlatformerGame::SpawnPlayer()
{
    auto player = shovel::Instantiate("player");
    //player->transform.position = shovel::vec2{shovel::random::getReal(0, 1000), }, 
    m_scene->AddActor(std::move(player));
}

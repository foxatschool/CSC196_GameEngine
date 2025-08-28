#include "Engine.h"
#include "Renderer/Renderer.h"
#include "Input/InputSystem.h"
#include "AudioSystem/AudioSystem.h"
#include "Renderer/ParticleSystem.h"

namespace shovel
{


	bool Engine::Initialize()
	{
		m_renderer = std::make_unique<shovel::Renderer>();
		m_renderer->Init();
		m_renderer->CreateWindow("Shovel Engine", 1280, 1024, false);

		m_input = std::make_unique<shovel::InputSystem>();
		m_input->Initialize();


		m_audio = std::make_unique<shovel::AudioSystem>();
		m_audio->Init();

		m_particleSystem = std::make_unique<shovel::ParticleSystem>();
		m_particleSystem->Initialize();

		m_physics = std::make_unique<Physics>();
		m_physics->Initialize();

		return true;
	}

	void Engine::Update()
	{
		m_particleSystem->Update(m_time.GetDeltaTime());
		m_time.Tick();
		m_input->Update();
		m_audio->Update();
		m_physics->Update(m_time.GetDeltaTime());
	}

	void Engine::Shutdown()
	{
		//Release resouces from resource manager
		Resources().Clear();
		Factory::Instance().RemoveAll();
		EventManager::Instance().RemoveAll();

		// Shut down engine systems
		m_particleSystem->ShutDown();
		m_renderer->ShutDown();
		m_input->Shutdown();
		m_audio->ShutDown();
		m_physics->Shutdown();
	}

	void Engine::Draw()
	{
		//
	}

}

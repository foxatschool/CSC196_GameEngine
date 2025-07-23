#include "Engine.h"
#include "Renderer/Renderer.h"
#include "Input/InputSystem.h"
#include "AudioSystem/AudioSystem.h"

namespace shovel
{

	Engine& GetEngine()
	{
		static Engine engine;
		return engine;
	}

	bool Engine::Initialize()
	{
		m_renderer = std::make_unique<shovel::Renderer>();
		m_renderer->Init();
		m_renderer->CreateWindow("Shovel Engine", 1280, 1024);

		m_input = std::make_unique<shovel::InputSystem>();
		m_input->Initialize();


		m_audio = std::make_unique<shovel::AudioSystem>();
		m_audio->Init();
		return true;
	}

	void Engine::Update()
	{
		m_time.Tick();
		m_input->Update();
		m_audio->Update();
	}

	void Engine::Shutdown()
	{
		m_renderer->ShutDown();
		m_input->Shutdown();
		m_audio->ShutDown();
	}

	void Engine::Draw()
	{

	}

}

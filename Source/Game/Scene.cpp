#include "Scene.h"
#include "Actor.h"
#include "../Engine/Renderer/Renderer.h"

namespace shovel
{
	
	void Scene::Update(float dt)
	{
		for (auto& actor : m_actors)
		{
			actor->Update(dt);
		}
	}

	void Scene::Draw(Renderer& renderer)
	{
		for (auto& actor : m_actors)
		{
			actor->Draw(renderer);
		}
	}

	void Scene::AddActor(std::unique_ptr<Actor> actor)
	{
		m_actors.push_back(std::move(actor));
	}

}
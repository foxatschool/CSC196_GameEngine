#include "Scene.h"
#include "Actor.h"
#include "../Renderer/Renderer.h"
#include "../Core/StringHelper.h"

namespace shovel {
	
	// Update all actors in the scene
	void Scene::Update(float dt) {
		for (auto& actor : m_actors) {
			actor->Update(dt);
		}
	}

	// Draw all actors in the scene
	void Scene::Draw(Renderer& renderer) {
		for (auto& actor : m_actors) {
			actor->Draw(renderer);
		}
	}

	// Add an actor to the scene
	void Scene::AddActor(std::unique_ptr<class Actor> actor) 
	{
		actor->scene = this;
		m_actors.push_back(std::move(actor));
	}

	// Remove all actors from the scene
	void Scene::RemoveAllActors()
	{
		m_actors.clear();
	}
}
#include "Scene.h"
#include "Actor.h"
#include "../Renderer/Renderer.h"
#include "../Core/StringHelper.h"

namespace shovel {
	
	// Update all actors in the scene
	void Scene::Update(float dt) {
		for (auto& actor : m_actors) 
		{
			actor->Update(dt);
		}

		// Remove actors that are marked as destroyed
		for (auto iter = m_actors.begin(); iter != m_actors.end();)
		{
			if ((*iter)->destroyed)
			{
				iter = m_actors.erase(iter); // Remove the actor if it is marked as destroyed
			}
			else
			{
				++iter; // Move to the next actor
			}
		}

		for (auto& actorA : m_actors)
		{
			for (auto& actorB : m_actors)
			{
				if (actorA == actorB || (actorA->destroyed || actorB->destroyed)) continue;

				float distnce = (actorA->transform.position - actorB->transform.position).Length();
				if (distnce <= (actorA->GetRadius() + actorB->GetRadius()))
				{
					actorA->OnColission(actorB.get());
					actorB->OnColission(actorA.get());
				}
			}
		}
	}

	// Draw all actors in the scene
	void Scene::Draw(Renderer& renderer) 
	{
		for (auto& actor : m_actors) 
		{
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
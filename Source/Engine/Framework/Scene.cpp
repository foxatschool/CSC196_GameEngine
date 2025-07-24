#include "Scene.h"
#include "Actor.h"
#include "../Renderer/Renderer.h"
#include "../Core/StringHelper.h"

namespace shovel {
	/// <summary>
	/// 
	/// </summary>
	/// <param name="dt"></param>
	void Scene::Update(float dt) {
		for (auto& actor : m_actors) {
			actor->Update(dt);
		}
	}

	/// <summary>
	/// 
	/// </summary>
	/// <param name="renderer"></param>
	void Scene::Draw(Renderer& renderer) {
		for (auto& actor : m_actors) {
			actor->Draw(renderer);
		}
	}

	/// <summary>
	/// 
	/// </summary>
	/// <param name="actor"></param>
	void Scene::AddActor(std::unique_ptr<class Actor> actor) 
	{
		actor->scene = this;
		m_actors.push_back(std::move(actor));
	}

	Actor* Scene::GetActorByName(const std::string& name)
	{
		for (auto& actor : m_actors)
			if (actor->name == toLower(name))
			{
				return actor.get();
			}
		return nullptr;
	}
}
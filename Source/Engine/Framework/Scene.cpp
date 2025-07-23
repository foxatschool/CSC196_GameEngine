#include "Scene.h"
#include "Actor.h"
#include "../Renderer/Renderer.h"

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
	void Scene::AddActor(std::unique_ptr<class Actor> actor) {
		m_actors.push_back(std::move(actor));
	}
}
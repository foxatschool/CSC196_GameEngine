#pragma once

#include "../Core/StringHelper.h"
#include <vector>
#include <memory>
#include <string>

namespace shovel {
	class Scene {
	public:
		Scene() = default;

		void Update(float dt);
		void Draw(class Renderer& renderer);

		void AddActor(std::unique_ptr < class Actor >);
		void RemoveAllActors();

		template<typename T = Actor>
		T* GetActorByName(const std::string& name);

		template<typename T = Actor>
		std::vector<T*> GetActorsByTag(const std::string& tag);
		
	private:
		std::vector < std::unique_ptr < class Actor >> m_actors;
	};

	// This function returns a pointer to an actor of type T with the specified name.
	template<typename T>
	inline T* Scene::GetActorByName(const std::string& name)
	{
		for (auto& actor : m_actors)
		{
			if (shovel::toLower(actor->name) == shovel::toLower(name))
			{
				T* object = dynamic_cast<T*>(actor.get());
				if (object)
				{
					return object;
				}
			}
		}

		return nullptr;
	}
	// This function returns a vector of actors of type T that have the specified tag.
	template<typename T>
	inline std::vector<T*> Scene::GetActorsByTag(const std::string& tag)
	{
		std::vector<T*> results;
		for (auto& actor : m_actors)
		{
			if (shovel::toLower(actor->tag) == shovel::toLower(tag))
			{
				T* object = dynamic_cast<T*>(actor);
				if (object)
				{
					results.push_back(object);
				}
			}
		}

		return results;
	}
}
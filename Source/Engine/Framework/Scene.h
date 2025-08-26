#pragma once
#include "../Core/Serializable.h"
#include "../Core/StringHelper.h"
#include <vector>
#include <memory>
#include <string>
#include <list>

namespace shovel {
	class Game;
	class Scene : public ISerializable {
	public:
		Scene(Game* game) : m_game{ game } {};

		bool Load(const std::string& sceneName);
		void Update(float dt);
		void Draw(class Renderer& renderer);

		void AddActor(std::unique_ptr < class Actor >, bool start = true);
		void RemoveAllActors(bool force = false);

		template<typename T = Actor>
		T* GetActorByName(const std::string& name);

		template<typename T = Actor>
		std::vector<T*> GetActorsByTag(const std::string& tag);

		void Read(const json::value_t& value) override;
		
		class Game* GetGame() const { return m_game; }

	private:
		class Game* m_game{ nullptr };
		std::list <std::unique_ptr <class Actor>> m_actors;

		// Inherited via Serializable
		
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
				T* object = dynamic_cast<T*>(actor.get()) ;
				if (object)
				{
					results.push_back(object);
				}
			}
		}

		return results;
	}
}
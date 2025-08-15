#pragma once
#include "../Math/Transform.h"
#include "Object.h"
#include "Component.h"

#include <vector>
#include <string>
#include <memory>

namespace shovel {
	class Actor : public Object {
	public:
		std::string tag;

		vec2 velocity{ 0, 0 };
		float damping{ 0.2f };

		bool destroyed{ false };
		float lifespan{ 0 };

		Transform transform;

		class Scene* scene{ nullptr };
	public:
		Actor() = default;
		Actor(const Transform& transform) :
			transform{transform}
		{}

		virtual void Update(float dt);
		virtual void Draw(class Renderer& renderer);

		virtual void OnColission(Actor* other) = 0;

		// components
		void AddComponent(std::unique_ptr<Component> component);
		
		template<typename T>
		T* GetComponent();

		template<typename T>
		std::vector<T*> GetComponents();


	protected:
		std::vector<std::unique_ptr<Component>> m_components;
	};
	template<typename T>
	inline T* Actor::GetComponent()
	{
		for (auto& component : m_components)
		{
			auto result = dynamic_cast<T*>(component.get());
			if (result)
			{
				return result; // Return the first component of type T found
			}
		}
		return nullptr;
	}
	template<typename T>
	inline std::vector<T*> Actor::GetComponents()
	{
		std::vector<T*> results;
		for (auto& component : m_components)
		{
			auto result = dynamic_cast<T*>(component.get());
			if (result)
			{
				results.push_back(result); // Return a vector containing the component of type T
			}
		}
		return results;
	}
}
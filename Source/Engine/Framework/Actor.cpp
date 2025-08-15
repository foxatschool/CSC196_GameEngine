#include "Actor.h"
#include "../Renderer/Model.h"
#include "../Components/RendererComponent.h"

namespace shovel {
	void Actor::Update(float dt) 
	{
		if (destroyed) return;
		
		if (lifespan > 0)
		{
			lifespan -= dt;
			if (lifespan <= 0)
			{
				destroyed = true;
				return;
			}
		}

		for (auto& component : m_components) 
		{
			if (component->active)
			{
				component->Update(dt);
			}
		}

		// Update the position based on velocity and damping
		for (auto& component : m_components)
		{
			if (component->active) component->Update(dt);
		}
	}

	void Actor::Draw(Renderer& renderer) 
	{
		if (destroyed) return;
		// Draw the model with the current transform
		m_model->Draw(renderer, transform);

		for (auto& component : m_components)
		{
			if (component->active)
			{
				auto rendererComponent = dynamic_cast<RendererComponent*>(component.get());
				if (rendererComponent)
				{
					component->Draw(renderer);
				}
			}
		}
	}

	void Actor::AddComponent(std::unique_ptr<Component> component)
	{
		component->owner = this;
		m_components.push_back(std::move(component));
	}

}


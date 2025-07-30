#include "Actor.h"
#include "../Renderer/Model.h"

namespace shovel {
	void Actor::Update(float dt) 
	{
		if (destroyed) return;
		
		if (lifespan != 0)
		{
			lifespan -= dt;
			destroyed = lifespan <= 0;
		}

		// Update the position based on velocity and damping
		transform.position += velocity * dt;
		velocity *= (1.0f / (1.0f + (damping * dt))); // Dampen velocity
	}

	void Actor::Draw(Renderer& renderer) 
	{
		if (destroyed) return;
		// Draw the model with the current transform
		m_model->Draw(renderer, transform);
	}

	float Actor::GetRadius()
	{
		return (m_model) ? m_model->GetRadius() * transform.scale: 0;
	}

}


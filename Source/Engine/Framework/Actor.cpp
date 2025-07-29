#include "Actor.h"
#include "../Renderer/Model.h"

namespace shovel {
	void Actor::Update(float dt) 
	{
		// Update the position based on velocity and damping
		transform.position += velocity * dt;
		velocity *= (1.0f / (1.0f + (damping * dt))); // Dampen velocity
	}

	void Actor::Draw(Renderer& renderer) 
	{
		// Draw the model with the current transform
		m_model->Draw(renderer, transform);
	}

}


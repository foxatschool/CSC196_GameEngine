#include "Actor.h"
#include "../Renderer/Model.h"

namespace shovel {
	void Actor::Update(float dt) 
	{
		transform.position += velocity * dt;
		velocity *= (1.0f / (1.0f + (damping * dt))); // Dampen velocity
	}

	void Actor::Draw(Renderer& renderer) {
		m_model->Draw(renderer, transform);
	}

}


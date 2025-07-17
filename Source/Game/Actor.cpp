#include "Actor.h"

namespace shovel
{
	void Actor::Update(float dt)
	{

	}

	void Actor::Draw(class Renderer& renderer)
	{
		m_model->Draw(renderer, m_transform);
	}
}

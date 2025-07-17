#pragma once
#include "../Engine/Math/Transform.h"
#include "../Engine/Renderer/Model.h"

namespace shovel
{
	class Actor
	{
	public:
		Actor() = default;
		Actor(Transform transform, Model* model) :
			m_transform{ transform },
			m_model{model}
		{}

		virtual void Update(float dt);
		virtual void Draw(class Renderer& renderer);

		Transform& GetTransform() { return m_transform; }

	protected:
		Transform m_transform;
		Model* m_model;
	};
}
#pragma once
#include "../Engine/Math/Transform.h"
#include "../Engine/Renderer/Model.h"
#include <memory>

namespace shovel
{
	class Actor
	{
	public:
		Actor() = default;
		Actor(Transform transform, std::shared_ptr<class Model> model) :
			m_transform{ transform },
			m_model{model}
		{}

		virtual void Update(float dt);
		virtual void Draw(class Renderer& renderer);

		Transform& GetTransform() { return m_transform; }

	protected:
		Transform m_transform;
		std::shared_ptr<Model> m_model;
	};
}
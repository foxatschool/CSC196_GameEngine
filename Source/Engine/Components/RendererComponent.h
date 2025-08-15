#pragma once
#include "Framework/Component.h"

namespace shovel
{
	class RendererComponent : public Component
	{
	public:
		RendererComponent() = default;

		virtual void Update(float dt);
		virtual void Draw(class Renderer& renderer) = 0;
	};
}
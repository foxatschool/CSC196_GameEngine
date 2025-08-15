#pragma once
#include "RendererComponent.h"

namespace shovel
{
	class SpriteRenderer : public RendererComponent
	{
	public:
		std::string textureName;
	public:
		void Update(float dt);
		// Inherited via RendererComponent
		void Draw(Renderer& renderer);
		

	};
}

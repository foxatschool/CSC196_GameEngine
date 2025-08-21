#pragma once
#include "RendererComponent.h"

namespace shovel
{
	class SpriteRenderer : public RendererComponent
	{
	public:
		std::string textureName;
	public:
		CLASS_PROTOTYPE(SpriteRenderer)
		void Update(float dt);
		// Inherited via RendererComponent
		void Draw(Renderer& renderer);

		void Read(const json::value_t& value) override;

	};
}

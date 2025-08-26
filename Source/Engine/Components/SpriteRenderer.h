#pragma once
#include "RendererComponent.h"

namespace shovel
{
	class SpriteRenderer : public RendererComponent
	{
	public:
		std::string textureName;
		res_t<Texture> texture;
	public:
		CLASS_PROTOTYPE(SpriteRenderer)

		void Start() override;

		void Update(float dt);
		// Inherited via RendererComponent
		void Draw(Renderer& renderer);

		void Read(const json::value_t& value) override;

	};
}

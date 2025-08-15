#include "SpriteRenderer.h"
#include "Renderer/Renderer.h"

namespace shovel
{


	void SpriteRenderer::Update(float dt)
	{
		//
	}

	void SpriteRenderer::Draw(Renderer& renderer)
	{
		auto texture = Recources().Get<Texture>(textureName, renderer).get();

		if (texture)
		{
			renderer.DrawTexture(*texture,
				owner->transform.position.x, owner->transform.position.y,
				owner->transform.rotation,
				owner->transform.scale);
		}
	}
}

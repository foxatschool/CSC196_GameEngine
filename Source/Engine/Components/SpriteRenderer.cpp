#include "SpriteRenderer.h"
#include "Renderer/Renderer.h"
#include "Core/Json.h"

namespace shovel
{
	FACTORY_REGISTER(SpriteRenderer)


	void SpriteRenderer::Update(float dt)
	{
		//
	}

	void SpriteRenderer::Draw(Renderer& renderer)
	{
		auto texture = Resources().Get<Texture>(textureName, renderer).get();

		if (texture)
		{
			renderer.DrawTexture(*texture,
				owner->transform.position.x, owner->transform.position.y,
				owner->transform.rotation,
				owner->transform.scale);
		}
	}
	void SpriteRenderer::Read(const json::value_t& value)
	{
		Object::Read(value);

		JSON_READ(value, textureName);
	}
}

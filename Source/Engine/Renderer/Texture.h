#pragma once
#include <string>
#include "Math/Vector2.h"
#include "Resources/Resource.h"

struct SDL_Texture;

namespace shovel
{
	class Texture : public Resource
	{
	public:
		Texture() = default;
		~Texture();

		bool Load(const std::string& filename, class Renderer& renderer);

		vec2 GetSize();

		friend class Renderer;

	private:
		SDL_Texture* m_texture{ nullptr };
	};
}
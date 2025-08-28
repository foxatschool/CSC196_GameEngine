#include "Texture.h"
#include "Renderer.h"
#include <SDL3/SDL.h> 
#include "../EngineMinimal.h"

namespace shovel
{
	Texture::~Texture()
	{
		if (m_texture)
		{
			SDL_DestroyTexture(m_texture);
		}
	}

	bool Texture::Load(const std::string& filename, Renderer& renderer)
	{
		SDL_Surface* surface = IMG_Load(filename.c_str());
		if (!surface)
		{
			Logger::Error("Failed to load texture: {}", filename);
			return false;
		}

		// create texture from surface, texture is a friend class of renderer
		m_texture = SDL_CreateTextureFromSurface(renderer.m_renderer, surface);
		// once texture is created, surface can be freed up
		SDL_DestroySurface(surface);


		if (!m_texture)
		{
			Logger::Error("Could not create texture: {}", filename);
			return false;
		}
		else
		{
			return true;
		}
	}

	vec2 Texture::GetSize()
	{
		float w, h;
		SDL_GetTextureSize(m_texture, &w, &h);

		return vec2{ w, h };
	}
}
#pragma once
#include <SDL3/SDL.h>
#include "SDL3_ttf/SDL_ttf.h"
#include <iostream>
#include <SDL3_image/SDL_image.h>
#include "Texture.h"

namespace shovel
{
	class Renderer
	{
	public:
		Renderer() = default;

		bool Init();
		void ShutDown();

		bool CreateWindow(const std::string& name, int width, int height, bool fullscreen = false);

		void SetColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);
		void SetColor(float r, float g, float b, float a = 1.0f);
		void Clear();
		void Present();
		void DrawLine(float x1, float y1, float x2, float y2);
		void DrawPoint(float x, float y);

		int GetWidth() const { return m_width; }
		int GetHeight() const { return m_height; }

		void DrawTexture(Texture& texture, float x, float y);
		void DrawTexture(Texture& texture, float x, float y, float angle, float scale, bool flipH = false);
		void DrawTexture(class Texture& texture, const rect& sourceRect, float x, float y, float angle, float scale = 1, bool flipH = false);

	private:

		int m_width {0};
		int m_height {0};
		
		SDL_Window* m_window = nullptr;
		SDL_Renderer* m_renderer = nullptr;

		friend class Text;
		friend class Texture;
	};
}
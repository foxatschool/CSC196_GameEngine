#pragma once
#include <SDL3/SDL.h>
#include <iostream>

namespace shovel
{
	class Renderer
	{
	public:
		Renderer() = default;

		bool init();
		void shutDown();

		bool CreateWindow(const std::string& name, int width, int height);

		void setColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);
		void Clear();
		void present();
		void drawLine(float x1, float y1, float x2, float y2);
		void drawPoint(float x, float y);

	private:
		SDL_Window* m_window = nullptr;
		SDL_Renderer* m_renderer = nullptr;
	};
}
#include "Renderer.h"
#include <iostream>


namespace shovel
{
    bool Renderer::Init()
    {
		// Initialize SDL and TTF
        if (!SDL_Init(SDL_INIT_VIDEO))
        {
            std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
            return false;
        }

        if (!TTF_Init()) {
            std::cerr << "TTF_Init Error: " << SDL_GetError() << std::endl;
            return false;
        }

        return true;
    }

    void Renderer::ShutDown()
    {
        TTF_Quit();
        SDL_DestroyRenderer(m_renderer);
        SDL_DestroyWindow(m_window);
        SDL_Quit();
    }

    bool Renderer::CreateWindow(const std::string& name, int width, int height)
    {
		m_width = width;
		m_height = height;

		// Create the SDL window
        m_window = SDL_CreateWindow(name.c_str(), width, height, 0);
		// Check if the window was created successfully
        if (m_window == nullptr)
        {
            std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
            SDL_Quit();
            return false;
        }
		// Create the SDL renderer
        m_renderer = SDL_CreateRenderer(m_window, NULL);
		// Check if the renderer was created successfully
        if (m_renderer == nullptr)
        {
            std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
            SDL_DestroyWindow(m_window);
            SDL_Quit();
            return false;
        }
        return true;
    }

    void Renderer::SetColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
    {
		// Set the draw color for the renderer
        SDL_SetRenderDrawColor(m_renderer, r, g, b, a);
    }

    void Renderer::SetColor(float r, float g, float b, float a)
    {
		// Set the draw color for the renderer using float values
        SDL_SetRenderDrawColorFloat(m_renderer, r, g, b, a);
    }

    void Renderer::Clear()
    {
        SDL_RenderClear(m_renderer);
    }

    void Renderer::Present()
    {
        SDL_RenderPresent(m_renderer);
    }

    void Renderer::DrawLine(float x1, float y1, float x2, float y2)
    {
        SDL_RenderLine(m_renderer, x1, y1, x2, y2);
    }
    void Renderer::DrawPoint(float x, float y)
    {
		SDL_RenderPoint(m_renderer, x, y);
    }
}

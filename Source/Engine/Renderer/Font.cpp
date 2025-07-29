#include "Font.h"
#include <iostream>
#include <SDL3_ttf/SDL_ttf.h>

shovel::Font::~Font() 
{
	if (m_ttfFont != nullptr) 
	{
		TTF_CloseFont(m_ttfFont);
	}
}

bool shovel::Font::Load(const std::string& name, float fontSize) 
{
	// Initialize the TTF library if it hasn't been done yet
	m_ttfFont = TTF_OpenFont(name.c_str(), fontSize);
	// Check if the font was loaded successfully
	if (m_ttfFont == nullptr) 
	{
		std::cerr << "Could not load font: " << name << std::endl;
		return false;
	}

	return true;
}

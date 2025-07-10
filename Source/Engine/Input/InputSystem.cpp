#include "InputSystem.h"
#include <SDL3/SDL.h>


bool shovel::InputSystem::Initialize()
{
    int numKeys;

    const bool* keyboardState = SDL_GetKeyboardState(&numKeys);

	m_keyboardState.resize(numKeys);
    std::copy(keyboardState, keyboardState + numKeys, m_keyboardState.begin());
	m_prevkeyboardState = m_keyboardState;

	SDL_GetMouseState(&m_mousePosition.x, &m_mousePosition.y);
	m_prevMousePosition = m_mousePosition;

    return true;
}

void shovel::InputSystem::Shutdown()
{
    //
}

void shovel::InputSystem::Update()
{
	//Keyboard Input
	m_prevkeyboardState = m_keyboardState;
    const bool* keyboardState = SDL_GetKeyboardState(nullptr);
    std::copy(keyboardState, keyboardState + m_keyboardState.size(), m_keyboardState.begin());

	// Mouse Input
	m_prevMousePosition = m_mousePosition;

	m_prevMouseButtonState = m_mouseButtonState;
	uint32_t mouseButtonState = SDL_GetMouseState(&m_mousePosition.x, &m_mousePosition.y);

	m_mouseButtonState[(uint8_t)MouseButton::LEFT] = mouseButtonState & SDL_BUTTON_LMASK;
	m_mouseButtonState[(uint8_t)MouseButton::MIDDLE] = mouseButtonState & SDL_BUTTON_MMASK;
	m_mouseButtonState[(uint8_t)MouseButton::RIGHT] = mouseButtonState & SDL_BUTTON_RMASK;
}
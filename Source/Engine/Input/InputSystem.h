#pragma once
#include "../Math/Vector2.h"
#include <vector>
#include <array>

namespace shovel {
    class InputSystem {
    public:
        enum class MouseButton : uint8_t
        {
            LEFT,
            MIDDLE,
            RIGHT
        };

    public:
        InputSystem() = default;

        bool Initialize();

        void Shutdown();

        void Update();

        // Keyboard Input
        bool GetKeyDown(uint8_t key) const { return m_keyboardState[key]; }
        bool GetPreviousKeyDown(uint8_t key) const { return m_prevkeyboardState[key]; }
        bool GetKeyPressed(uint8_t key) const { return !m_prevkeyboardState[key] && m_keyboardState[key]; }
        bool GetKeyReleased(uint8_t key) const { return m_prevkeyboardState[key] && !m_keyboardState[key]; }
        bool GetKeyHeld(uint8_t key) const { return m_prevkeyboardState[key] && m_keyboardState[key]; }

		const vec2& GetMousePosition() const { return m_mousePosition; }
		const vec2& GetPrevMousePosition() const { return m_prevMousePosition; }

		//Mouse Input
        bool GetMouseButtonDown(MouseButton button) const { return m_mouseButtonState[(uint8_t)button]; }
        bool GetPreviousMouseButtonDown(MouseButton button) const { return m_prevMouseButtonState[(uint8_t)button]; }
        bool GetMouseButtonPresed(MouseButton button) const { return !m_prevMouseButtonState[(uint8_t)button] && m_mouseButtonState[(uint8_t)button]; }
        bool GetMouseButtonRealeased(MouseButton button) const { return m_prevMouseButtonState[(uint8_t)button] && !m_mouseButtonState[(uint8_t)button]; }

	private:
        std::vector<bool> m_keyboardState;
        std::vector<bool> m_prevkeyboardState;

        vec2 m_mousePosition{0,0};
        vec2 m_prevMousePosition{0,0};

		std::array<bool, 3> m_mouseButtonState = { false, false, false };
        std::array<bool, 3> m_prevMouseButtonState = { false, false, false };
    };
}
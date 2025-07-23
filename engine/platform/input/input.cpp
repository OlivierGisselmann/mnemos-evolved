#include <input.hpp>

namespace mnm::input
{
    // INTERNAL
    static bool currentKeys[(int)Key::Count] = {};
    static bool previousKeys[(int)Key::Count] = {};

    static i32 mouseX = 0, mouseY = 0;

    void UpdateInputState()
    {
        for(int i = 0; i < static_cast<int>(Key::Count); ++i)
        {
            previousKeys[i] = currentKeys[i];
        }
    }

    void SetKeyState(Key key, bool state)
    {
        currentKeys[(int)key] = state;
    }

    void SetMousePosition(i32 x,i32 y)
    {
        mouseX = x;
        mouseY = y;
    }

    // PUBLIC API
    bool IsKeyDown(Key key) noexcept
    {
        return currentKeys[(int)key];
    }

    bool IsKeyPressed(Key key) noexcept
    {
        return !previousKeys[(int)key] && currentKeys[(int)key];
    }

    bool IsKeyReleased(Key key) noexcept
    {
        return previousKeys[(int)key] && !currentKeys[(int)key];
    }

    i32 GetMouseX() noexcept
    {
        return mouseX;
    }

    i32 GetMouseY() noexcept
    {
        return mouseY;
    }
}

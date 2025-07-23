#ifndef INPUT_SYSTEM_HPP
#define INPUT_SYSTEM_HPP

#include <input.hpp>

namespace mnm::input
{
    void UpdateInputState();

    void SetKeyState(Key key, bool state);
    void SetMousePosition(i32 x, i32 y);
}

#endif

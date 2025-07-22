#ifndef INPUT_HPP
#define INPUT_HPP

#include <defines.hpp>
#include <types.hpp>

namespace mnm::input
{
    enum class Key
    {
        A,
        B,
        C,
        D,
        E,
        F,
        G,
        H,
        I,
        J,
        K,
        L,
        M,
        N,
        O,
        P,
        Q,
        R,
        S,
        T,
        U,
        V,
        W,
        X,
        Y,
        Z,

        Numpad0,
        Numpad1,
        Numpad2,
        Numpad3,
        Numpad4,
        Numpad5,
        Numpad6,
        Numpad7,
        Numpad8,
        Numpad9,

        Alpha0,
        Alpha1,
        Alpha2,
        Alpha3,
        Alpha4,
        Alpha5,
        Alpha6,
        Alpha7,
        Alpha8,
        Alpha9,

        Backspace,
        Return,
        Space,
        Escape,

        F1,
        F2,
        F3,
        F4,
        F5,
        F6,
        F7,
        F8,
        F9,
        F10,
        F11,
        F12,

        Count
    };

    MAPI bool IsKeyDown(Key key) noexcept;
    MAPI bool IsKeyPressed(Key key) noexcept;
    MAPI bool IsKeyReleased(Key key) noexcept;

    MAPI i32 GetMouseX() noexcept;
    MAPI i32 GetMouseY() noexcept;
}

#endif

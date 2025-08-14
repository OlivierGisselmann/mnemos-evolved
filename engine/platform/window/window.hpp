#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <core/logging/log.hpp>
#include <math/vector.hpp>
#include <platform/input/input_system.hpp>

#include <input.hpp>
#include <types.hpp>

#include <iostream>
#include <memory>
#include <string>

namespace mnm::window
{
    // Forward declaration - implementation defined
    struct MWindowContext;

    class MWindow
    {
    public:
        MWindow();
        MWindow(const MWindow&) = delete;
        MWindow& operator=(const MWindow&) = delete;
        ~MWindow();

        bool Initialize(math::Vec2u size, const std::string& title);

        void PollEvents();
        void SwapBuffers();
        bool CloseRequested() const;
        
        math::Vec2u GetSize() const;

        void Shutdown();

    private:
        std::unique_ptr<MWindowContext> mContext;
        math::Vec2u mSize{};
        std::string mTitle = {};
        bool mCloseRequested = false;
    };
}

#endif

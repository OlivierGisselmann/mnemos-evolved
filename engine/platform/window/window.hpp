#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <core/logging/log.hpp>
#include <platform/types.hpp>

#include <iostream>
#include <memory>
#include <string>

namespace mnm::window
{
    struct MWindowContext;

    class MWindow
    {
    public:
        MWindow();
        MWindow(const MWindow&) = delete;
        MWindow& operator=(const MWindow&) = delete;
        ~MWindow();

        bool Initialize(u16 width, u16 height, const std::string& title);

        void PollEvents();
        void SwapBuffers();
        bool CloseRequested() const;

        void Shutdown();

    private:
        std::unique_ptr<MWindowContext> mContext;
        u16 mWidth = 0, mHeight = 0;
        std::string mTitle = {};
        bool mCloseRequested = false;
    };
}

#endif

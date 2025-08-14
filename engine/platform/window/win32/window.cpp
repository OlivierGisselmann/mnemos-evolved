#include <platform/window/window.hpp>

#include <Windows.h>

namespace mnm::window
{
     // Platform specific internal state
    struct MWindowContext
    {
        HINSTANCE hInstance;
        WNDCLASSA wndClass;
        HWND window;
        HDC hdc;
        MSG msg;
    };

    MWindow::MWindow()
    {
        mContext = std::make_unique<MWindowContext>();
    }

    MWindow::~MWindow() {}

    bool MWindow::Initialize(math::Vec2u size, const std::string& title)
    {
        mSize = size;
        mTitle = title;

        mContext->hInstance = GetModuleHandle(0);

        const char* className = "MnemosMainClass";

        // Default initialize window class
        mContext->wndClass = {};

        // Specify window class settings
        mContext->wndClass.hInstance = mContext->hInstance;
        mContext->wndClass.lpszClassName = className;
        mContext->wndClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
        mContext->wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);

        if(!RegisterClassA(&mContext->wndClass))
        {
            log::Log(log::Level::FATAL, log::Channel::WINDOW, "Failed to register WIN32 Window class");
            return false;
        }

        // Create window then check result
        mContext->window = CreateWindowExA(
            0, mContext->wndClass.lpszClassName, mTitle.c_str(), WS_OVERLAPPEDWINDOW | WS_VISIBLE,
            CW_USEDEFAULT, CW_USEDEFAULT, mSize.x, mSize.y, nullptr, nullptr,
            mContext->hInstance, this
        );

        if(!mContext->window)
        {
            log::Log(log::Level::FATAL, log::Channel::WINDOW, "Failed to create WIN32 Window");
            return false;
        }

        mContext->hdc = GetDC(mContext->window);

        ShowWindow(mContext->window, SW_SHOWDEFAULT);
        UpdateWindow(mContext->window);

        log::Log(log::Level::INFO, log::Channel::WINDOW, "WIN32 Window initialized");

        return true;
    }

    void MWindow::Shutdown()
    {
        ReleaseDC(mContext->window, mContext->hdc);
        DestroyWindow(mContext->window);
        UnregisterClassA(mContext->wndClass.lpszMenuName, mContext->hInstance);

        mContext->window = nullptr;

        log::Log(log::Level::INFO, log::Channel::WINDOW, "WIN32 Window shutdown");
    }

    bool MWindow::CloseRequested() const
    {
        return mCloseRequested;
    }

    void MWindow::PollEvents()
    {
        
    }

    void MWindow::SwapBuffers()
    {

    }
}

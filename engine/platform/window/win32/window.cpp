#include <platform/window/window.hpp>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <windowsx.h>

#include <glad/glad.h>
#include <wgl/wglext.h>

#include <gl/GL.h>

PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB = nullptr;
PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = nullptr;
PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT = nullptr;

namespace mnm::window
{
    // TODO: Refactor this -- ugly
    static MWindow* windowPtr{ nullptr };

    static input::Key TranslateWin32Key(WPARAM wParam)
    {
        switch (wParam)
        {
        case 'A': return input::Key::A;
        case 'B': return input::Key::B;
        case 'C': return input::Key::C;
        case 'D': return input::Key::D;
        case 'E': return input::Key::E;
        case 'F': return input::Key::F;
        case 'G': return input::Key::G;
        case 'H': return input::Key::H;
        case 'I': return input::Key::I;
        case 'J': return input::Key::J;
        case 'K': return input::Key::K;
        case 'L': return input::Key::L;
        case 'M': return input::Key::M;
        case 'N': return input::Key::N;
        case 'O': return input::Key::O;
        case 'P': return input::Key::P;
        case 'Q': return input::Key::Q;
        case 'R': return input::Key::R;
        case 'S': return input::Key::S;
        case 'T': return input::Key::T;
        case 'U': return input::Key::U;
        case 'V': return input::Key::V;
        case 'W': return input::Key::W;
        case 'X': return input::Key::X;
        case 'Y': return input::Key::Y;
        case 'Z': return input::Key::Z;

        case VK_F1: return input::Key::F1;
        case VK_F2: return input::Key::F2;
        case VK_F3: return input::Key::F3;
        case VK_F4: return input::Key::F4;
        case VK_F5: return input::Key::F5;
        case VK_F6: return input::Key::F6;
        case VK_F7: return input::Key::F7;
        case VK_F8: return input::Key::F8;
        case VK_F9: return input::Key::F9;
        case VK_F10: return input::Key::F10;
        case VK_F11: return input::Key::F11;
        case VK_F12: return input::Key::F12;

        case '0': return input::Key::Alpha0;
        case '1': return input::Key::Alpha1;
        case '2': return input::Key::Alpha2;
        case '3': return input::Key::Alpha3;
        case '4': return input::Key::Alpha4;
        case '5': return input::Key::Alpha5;
        case '6': return input::Key::Alpha6;
        case '7': return input::Key::Alpha7;
        case '8': return input::Key::Alpha8;
        case '9': return input::Key::Alpha9;

        case VK_NUMPAD0: return input::Key::Numpad0;
        case VK_NUMPAD1: return input::Key::Numpad1;
        case VK_NUMPAD2: return input::Key::Numpad2;
        case VK_NUMPAD3: return input::Key::Numpad3;
        case VK_NUMPAD4: return input::Key::Numpad4;
        case VK_NUMPAD5: return input::Key::Numpad5;
        case VK_NUMPAD6: return input::Key::Numpad6;
        case VK_NUMPAD7: return input::Key::Numpad7;
        case VK_NUMPAD8: return input::Key::Numpad8;
        case VK_NUMPAD9: return input::Key::Numpad9;

        case VK_SPACE: return input::Key::Space;
        case VK_ESCAPE: return input::Key::Escape;
        case VK_BACK: return input::Key::Backspace;
        case VK_RETURN: return input::Key::Return;

        default: return input::Key::Count;
        }
    }

    LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        switch (uMsg)
        {
        case WM_CLOSE:
            DestroyWindow(hwnd);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            if(windowPtr) windowPtr->SetCloseRequested(true);
            return 0;
        case WM_SIZE:
        {
            u32 width = LOWORD(lParam);
            u32 height = HIWORD(lParam);
            if(windowPtr) windowPtr->SetSize({ width, height });
            break;
        }
        case WM_KEYDOWN:
            input::SetKeyState(TranslateWin32Key(wParam), true);
            break;
        case WM_KEYUP:
            input::SetKeyState(TranslateWin32Key(wParam), false);
            break;
        case WM_MOUSEMOVE:
            input::SetMousePosition(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
            break;
        case WM_LBUTTONDOWN:
            break;
        case WM_LBUTTONUP:
            break;
        case WM_RBUTTONDOWN:
            break;
        case WM_RBUTTONUP:
            break;
        }

        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

     // Platform specific internal state
    struct MWindowContext
    {
        // WIN32 Window
        HINSTANCE hInstance;
        WNDCLASSA wndClass;
        HWND window;
        HDC hdc;
        MSG msg;

        // GL Context
        HGLRC mGLContext;
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

        mContext->hInstance = GetModuleHandle(NULL);

        const char* className = "MnemosMainClass";

        // Default initialize window class
        mContext->wndClass = {};

        // Specify window class settings
        mContext->wndClass.hInstance = mContext->hInstance;
        mContext->wndClass.lpszClassName = className;
        mContext->wndClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
        mContext->wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
        mContext->wndClass.lpfnWndProc = WindowProc;

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

        // Set dummy pixel format
        PIXELFORMATDESCRIPTOR pixelFormatDescriptor =
        {
            sizeof(PIXELFORMATDESCRIPTOR),
            1,
            PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
            PFD_TYPE_RGBA,
            32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            24, 8, 0, PFD_MAIN_PLANE, 0, 0, 0, 0
        };

        int pf = ChoosePixelFormat(mContext->hdc, &pixelFormatDescriptor);
        SetPixelFormat(mContext->hdc, pf, &pixelFormatDescriptor);

        // Create dummy GL context
        HGLRC tempContext = wglCreateContext(mContext->hdc);
        wglMakeCurrent(mContext->hdc, tempContext);

        // Load WGL extensions
        wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)
            wglGetProcAddress("wglCreateContextAttribsARB");

        wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC)
            wglGetProcAddress("wglChoosePixelFormatARB");

        wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)
            wglGetProcAddress("wglSwapIntervalEXT");

        if (!wglCreateContextAttribsARB)
            return false;

        // Set real pixel format
        int pixelAttribs[] =
        {
            WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
            WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
            WGL_DOUBLE_BUFFER_ARB,  GL_TRUE,
            WGL_PIXEL_TYPE_ARB,     WGL_TYPE_RGBA_ARB,
            WGL_COLOR_BITS_ARB,     32,
            WGL_DEPTH_BITS_ARB,     24,
            WGL_STENCIL_BITS_ARB,   8,
            0
        };

        int pixelFormat;
        UINT numFormats;
        wglChoosePixelFormatARB(mContext->hdc, pixelAttribs, nullptr, 1, &pixelFormat, &numFormats);

        DescribePixelFormat(mContext->hdc, pixelFormat, sizeof(pixelFormatDescriptor), &pixelFormatDescriptor);
        SetPixelFormat(mContext->hdc, pixelFormat, &pixelFormatDescriptor);

        // Create real GL context
        int contextAttribs[] =
        {
            WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
            WGL_CONTEXT_MINOR_VERSION_ARB, 5,
            WGL_CONTEXT_FLAGS_ARB, 0,
            WGL_CONTEXT_PROFILE_MASK_ARB,
            WGL_CONTEXT_CORE_PROFILE_BIT_ARB, 0
        };

        mContext->mGLContext = wglCreateContextAttribsARB(mContext->hdc, nullptr, contextAttribs);

        // Cleanup dummy context
        wglMakeCurrent(nullptr, nullptr);
        wglDeleteContext(tempContext);

        // Make real context current
        wglMakeCurrent(mContext->hdc, mContext->mGLContext);

        // Load GL functions with GLAD
        if (!gladLoadGL())
        {
            log::Log(log::Level::FATAL, log::Channel::WINDOW, "Failed to load OpenGL functions");
            return false;
        }

        ShowWindow(mContext->window, SW_SHOWDEFAULT);
        UpdateWindow(mContext->window);

        // Disable V-Sync
        wglSwapIntervalEXT(0);
        
        windowPtr = this;

        log::Log(log::Level::INFO, log::Channel::WINDOW, "WIN32 Window initialized");

        std::string renderer = (const char*)glGetString(GL_RENDERER);
        std::string version = (const char*)glGetString(GL_VERSION);

        log::Log(log::Level::INFO, log::Channel::WINDOW, "Selected GPU: " + renderer);
        log::Log(log::Level::INFO, log::Channel::WINDOW, "GL Version: " + version);

        return true;
    }

    void MWindow::Shutdown()
    {
        wglMakeCurrent(mContext->hdc, nullptr);
        wglDeleteContext(mContext->mGLContext);
        ReleaseDC(mContext->window, mContext->hdc);
        DestroyWindow(mContext->window);
        UnregisterClassA(mContext->wndClass.lpszMenuName, mContext->hInstance);

        mContext->window = nullptr;

        log::Log(log::Level::INFO, log::Channel::WINDOW, "WIN32 Window shutdown");
    }

    math::Vec2u MWindow::GetSize() const
    {
        return mSize;
    }

    void MWindow::SetSize(const math::Vec2u& size)
    {
        mSize = size;
    }

    bool MWindow::CloseRequested() const
    {
        return mCloseRequested;
    }

    void MWindow::SetCloseRequested(bool state)
    {
        mCloseRequested = state;
    }

    void MWindow::PollEvents()
    {
        // Loop through all events
        while (PeekMessage(&mContext->msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&mContext->msg);
            DispatchMessage(&mContext->msg);
        }
    }

    void MWindow::SwapWindowBuffers()
    {
        SwapBuffers(mContext->hdc);
    }
}

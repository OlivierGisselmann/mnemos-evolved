#include <platform/window/window.hpp>

#include <X11/Xlib.h>
#include <X11/extensions/Xrender.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>
#include <glad/glad.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glxext.h>

typedef GLXContext (*glXCreateContextAttribsARBProc)(Display*, GLXFBConfig, GLXContext, Bool, const int*);

namespace mnm::window
{
    static input::Key TranslateX11Key(KeySym sym)
    {
        switch (sym)
        {
            case XK_a: return input::Key::A;
            case XK_b: return input::Key::B;
            case XK_c: return input::Key::C;
            case XK_d: return input::Key::D;
            case XK_e: return input::Key::E;
            case XK_f: return input::Key::F;
            case XK_g: return input::Key::G;
            case XK_h: return input::Key::H;
            case XK_i: return input::Key::I;
            case XK_j: return input::Key::J;
            case XK_k: return input::Key::K;
            case XK_l: return input::Key::L;
            case XK_m: return input::Key::M;
            case XK_n: return input::Key::N;
            case XK_o: return input::Key::O;
            case XK_p: return input::Key::P;
            case XK_q: return input::Key::Q;
            case XK_r: return input::Key::R;
            case XK_s: return input::Key::S;
            case XK_t: return input::Key::T;
            case XK_u: return input::Key::U;
            case XK_v: return input::Key::V;
            case XK_w: return input::Key::W;
            case XK_x: return input::Key::X;
            case XK_y: return input::Key::Y;
            case XK_z: return input::Key::Z;

            case XK_F1: return input::Key::F1;
            case XK_F2: return input::Key::F2;
            case XK_F3: return input::Key::F3;
            case XK_F4: return input::Key::F4;
            case XK_F5: return input::Key::F5;
            case XK_F6: return input::Key::F6;
            case XK_F7: return input::Key::F7;
            case XK_F8: return input::Key::F8;
            case XK_F9: return input::Key::F9;
            case XK_F10: return input::Key::F10;
            case XK_F11: return input::Key::F11;
            case XK_F12: return input::Key::F12;

            case XK_0: return input::Key::Alpha0;
            case XK_1: return input::Key::Alpha1;
            case XK_2: return input::Key::Alpha2;
            case XK_3: return input::Key::Alpha3;
            case XK_4: return input::Key::Alpha4;
            case XK_5: return input::Key::Alpha5;
            case XK_6: return input::Key::Alpha6;
            case XK_7: return input::Key::Alpha7;
            case XK_8: return input::Key::Alpha8;
            case XK_9: return input::Key::Alpha9;

            case XK_KP_0: return input::Key::Numpad0;
            case XK_KP_1: return input::Key::Numpad1;
            case XK_KP_2: return input::Key::Numpad2;
            case XK_KP_3: return input::Key::Numpad3;
            case XK_KP_4: return input::Key::Numpad4;
            case XK_KP_5: return input::Key::Numpad5;
            case XK_KP_6: return input::Key::Numpad6;
            case XK_KP_7: return input::Key::Numpad7;
            case XK_KP_8: return input::Key::Numpad8;
            case XK_KP_9: return input::Key::Numpad9;

            case XK_space: return input::Key::Space;
            case XK_Escape: return input::Key::Escape;
            case XK_BackSpace: return input::Key::Backspace;
            case XK_Return: return input::Key::Return;
            
            default: return input::Key::Count;
        }
    }

    // Platform specific internal state
    struct MWindowContext
    {
        // X11 Window
        Display* display = {};
        Window window = {};
        int screen = {};
        Colormap colormap = {};
        XVisualInfo* visualInfo = {};
        XSetWindowAttributes attributes = {};
        XEvent event = {};
        Atom deleteWindowAtom = {};

        // GL Context
        GLXContext context = {};
        GLXFBConfig* fbConfig;
        i32 versionMajor = 4, versionMinor = 5;
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

        // Connect to X11's server
        mContext->display = XOpenDisplay(NULL);
        if(nullptr == mContext->display)
        {
            log::Log(log::Level::FATAL, log::Channel::WINDOW, "Failed to open X11 server connection");
            return false;
        }

        // Setup window default values
        mContext->screen = DefaultScreen(mContext->display);

        // Setting up default framebuffer values
        const int fbAttribs[] = {
            GLX_X_RENDERABLE    , True,
            GLX_DRAWABLE_TYPE   , GLX_WINDOW_BIT,
            GLX_RENDER_TYPE     , GLX_RGBA_BIT,
            GLX_X_VISUAL_TYPE   , GLX_TRUE_COLOR,
            GLX_RED_SIZE        , 8,
            GLX_GREEN_SIZE      , 8,
            GLX_BLUE_SIZE       , 8,
            GLX_ALPHA_SIZE      , 8,
            GLX_DEPTH_SIZE      , 24,
            GLX_STENCIL_SIZE    , 8,
            GLX_DOUBLEBUFFER    , True,
            None
        };

        // Fetch framebuffer configs
        i32 fbCount = 0;
        mContext->fbConfig = glXChooseFBConfig(mContext->display, mContext->screen, fbAttribs, &fbCount);
        if(!mContext->fbConfig)
        {
            log::Log(log::Level::FATAL, log::Channel::WINDOW, "Failed to get a framebuffer config for GL Context");
            return false;
        }

        // Pick first compatible config
        mContext->visualInfo = glXGetVisualFromFBConfig(mContext->display, mContext->fbConfig[0]);

        // Create Colormap
        mContext->colormap = XCreateColormap(mContext->display, RootWindow(mContext->display, mContext->visualInfo->screen), mContext->visualInfo->visual, AllocNone);

        // Setup window attributes
        mContext->attributes.colormap = mContext->colormap;
        mContext->attributes.background_pixel = 0xFFFFFFFF;
        mContext->attributes.border_pixel = 0;
        mContext->attributes.override_redirect = True;
        mContext->attributes.event_mask = KeyPressMask | KeyReleaseMask | StructureNotifyMask | ExposureMask | PointerMotionMask;

        // Create X11 window
        mContext->window = XCreateWindow(
            mContext->display, RootWindow(mContext->display, mContext->screen), 0, 0,
            mSize.x, mSize.y, 0, mContext->visualInfo->depth, InputOutput, mContext->visualInfo->visual,
            CWBackPixel | CWBorderPixel | CWEventMask | CWColormap, &mContext->attributes
        );

        if(BadAlloc == mContext->window)
        {
            log::Log(log::Level::FATAL, log::Channel::WINDOW, "Failed to create X11 Window");
            return false;
        }

        // Catch close event
        mContext->deleteWindowAtom = XInternAtom(mContext->display, "WM_DELETE_WINDOW", False);
        XSetWMProtocols(mContext->display, mContext->window, &mContext->deleteWindowAtom, 1);

        // Disable input key repeat and set window title
        XAutoRepeatOff(mContext->display);
        XStoreName(mContext->display, mContext->window, mTitle.c_str());

        // Show the window
        XClearWindow(mContext->display, mContext->window);
        XMapRaised(mContext->display, mContext->window);
        XFlush(mContext->display);

        // Load extension function for context creation
        glXCreateContextAttribsARBProc glXCreateContextAttribsARB = (glXCreateContextAttribsARBProc)glXGetProcAddressARB((const GLubyte*)"glXCreateContextAttribsARB");
        if(!glXCreateContextAttribsARB)
        {
            log::Log(log::Level::FATAL, log::Channel::WINDOW, "glXCreateContextAttribsARB not supported");
            return false;
        }

        const i32 contextAttribs[] = {
            GLX_CONTEXT_MAJOR_VERSION_ARB, mContext->versionMajor,
            GLX_CONTEXT_MINOR_VERSION_ARB, mContext->versionMinor,
            GLX_CONTEXT_PROFILE_MASK_ARB , GLX_CONTEXT_CORE_PROFILE_BIT_ARB,
            None
        };

        // Get a pointer on glXSwapIntervalEXT function
        PFNGLXSWAPINTERVALEXTPROC glXSwapIntervalEXT = 
        (PFNGLXSWAPINTERVALEXTPROC)glXGetProcAddressARB(
            (const GLubyte*)"glXSwapIntervalEXT");
            if (!glXSwapIntervalEXT)
        {
            log::Log(log::Level::FATAL, log::Channel::WINDOW, "glXSwapIntervalEXT not supported");
            return false;
        }

        // Create GL Context
        mContext->context = glXCreateContextAttribsARB(mContext->display, mContext->fbConfig[0], 0, True, contextAttribs);
        if(!mContext->context)
        {
            log::Log(log::Level::FATAL, log::Channel::WINDOW, "Failed to create GL Context");
            return false;
        }

        glXMakeCurrent(mContext->display, mContext->window, mContext->context);

        // Load GL Functions with GLAD
        if (!gladLoadGLLoader((GLADloadproc)glXGetProcAddress))
        {
            log::Log(log::Level::FATAL, log::Channel::WINDOW, "Failed to load GL functions");
            return false;
        }

        // Disable VSync
        glXSwapIntervalEXT(mContext->display, mContext->window, 0);

        std::string renderer = (const char*)glGetString(GL_RENDERER);
        std::string version = (const char*)glGetString(GL_VERSION);

        log::Log(log::Level::INFO, log::Channel::WINDOW, "X11 Window initialized");
        log::Log(log::Level::INFO, log::Channel::WINDOW, "Selected GPU: " + renderer);
        log::Log(log::Level::INFO, log::Channel::WINDOW, "GL Version: " + version);

        return true;
    }

    math::Vec2u MWindow::GetSize() const
    {
        return mSize;
    }

    void MWindow::Shutdown()
    {
        glXDestroyContext(mContext->display, mContext->context);
        XDestroyWindow(mContext->display, mContext->window);
        XCloseDisplay(mContext->display);
        XFree(mContext->visualInfo);
        XFree(mContext->fbConfig);
        
        log::Log(log::Level::INFO, log::Channel::WINDOW, "X11 Window shutdown");
    }

    bool MWindow::CloseRequested() const
    {
        return mCloseRequested;
    }

    void MWindow::PollEvents()
    {
        if(XPending(mContext->display) > 0)
        {
            XNextEvent(mContext->display, &mContext->event);

            // Close request event
            if(mContext->event.xclient.data.l[0] == mContext->deleteWindowAtom)
                mCloseRequested = true;

                switch (mContext->event.type)
                {
                case DestroyNotify:
                {
                    mCloseRequested = true;
                    break;
                }
                case ConfigureNotify:
                {
                    XConfigureEvent xce = mContext->event.xconfigure;
                    if(xce.width != mSize.x || xce.height != mSize.y)
                    {
                        mSize.x = xce.width;
                        mSize.y = xce.height;
                    }
                    break;
                }
                case KeyPress:
                {
                    KeySym sym = XLookupKeysym(&mContext->event.xkey, 0);
                    input::SetKeyState(TranslateX11Key(sym), true);
                    break;
                }
                case KeyRelease:
                {
                    KeySym sym = XLookupKeysym(&mContext->event.xkey, 0);
                    input::SetKeyState(TranslateX11Key(sym), false);
                    break;
                }
                case MotionNotify:
                {
                    const auto mousePosX = mContext->event.xmotion.x;
                    const auto mousePosY = mContext->event.xmotion.y;
                    input::SetMousePosition(mousePosX, mousePosY);
                    break;
                }
                default:
                    break;
                }
        }
    }

    void MWindow::SwapBuffers()
    {
        glXSwapBuffers(mContext->display, mContext->window);
    }
}

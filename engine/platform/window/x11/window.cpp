#include <platform/window/window.hpp>

#include <X11/Xlib.h>
#include <X11/extensions/Xrender.h>
#include <X11/Xutil.h>
#include <glad/glad.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glxext.h>

typedef GLXContext (*glXCreateContextAttribsARBProc)(Display*, GLXFBConfig, GLXContext, Bool, const int*);

namespace mnm::window
{
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

    bool MWindow::Initialize(u16 width, u16 height, const std::string& title)
    {
        mWidth = width;
        mHeight = height;
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
        mContext->attributes.event_mask = KeyPressMask | KeyReleaseMask | StructureNotifyMask | ExposureMask;

        // Create X11 window
        mContext->window = XCreateWindow(
            mContext->display, RootWindow(mContext->display, mContext->screen), 0, 0,
            mWidth, mHeight, 0, mContext->visualInfo->depth, InputOutput, mContext->visualInfo->visual,
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

        // Set input masks and window title
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

        std::string renderer = (const char*)glGetString(GL_RENDERER);
        std::string version = (const char*)glGetString(GL_VERSION);

        log::Log(log::Level::INFO, log::Channel::WINDOW, "X11 Window initialized");
        log::Log(log::Level::INFO, log::Channel::WINDOW, "Selected GPU: " + renderer);
        log::Log(log::Level::INFO, log::Channel::WINDOW, "GL Version: " + version);

        return true;
    }

    void MWindow::Shutdown()
    {
        glXMakeCurrent(mContext->display, None, nullptr);
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
                    if(xce.width != mWidth || xce.height != mHeight)
                    {
                        mWidth = xce.width;
                        mHeight = xce.height;
                    }
                    break;
                }
                default:
                    XFlush(mContext->display);
                    break;
                }
        }
    }

    void MWindow::SwapBuffers()
    {
        glXSwapBuffers(mContext->display, mContext->window);
    }
}

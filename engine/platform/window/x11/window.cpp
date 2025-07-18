#include <platform/window/window.hpp>

#include <X11/Xlib.h>

namespace mnm::window
{
    // Platform specific internal state
    struct MWindowContext
    {
        Display* display = {};
        Window window = {};
        int screen = {};
        int depth = {};
        Visual* visual = {};
        Colormap colormap = {};
        XSetWindowAttributes attributes = {};
        XEvent event = {};
        Atom deleteWindowAtom = {};
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
        mContext->visual = DefaultVisual(mContext->display, mContext->screen);
        mContext->depth = DefaultDepth(mContext->display, mContext->screen);

        // Create Colormap
        mContext->colormap = XCreateColormap(mContext->display, RootWindow(mContext->display, mContext->screen), mContext->visual, AllocNone);

        // Setup window attributes
        mContext->attributes.colormap = mContext->colormap;
        mContext->attributes.background_pixel = 0xFFFFFFFF;
        mContext->attributes.border_pixel = 0;
        mContext->attributes.override_redirect = True;
        mContext->attributes.event_mask = KeyPressMask | KeyReleaseMask | StructureNotifyMask | ExposureMask;

        // Create X11 window
        mContext->window = XCreateWindow(
            mContext->display, RootWindow(mContext->display, mContext->screen), 0, 0,
            mWidth, mHeight, 0, mContext->depth, InputOutput, mContext->visual,
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
        XSelectInput(mContext->display, mContext->window, ExposureMask | KeyPressMask);
        XStoreName(mContext->display, mContext->window, mTitle.c_str());

        // Show the window
        XClearWindow(mContext->display, mContext->window);
        XMapRaised(mContext->display, mContext->window);
        XFlush(mContext->display);

        log::Log(log::Level::INFO, log::Channel::WINDOW, "X11 Window initialized");

        return true;
    }

    void MWindow::Shutdown()
    {
        XDestroyWindow(mContext->display, mContext->window);
        XCloseDisplay(mContext->display);
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
                    mCloseRequested = true;
                    break;
                default:
                    XFlush(mContext->display);
                    break;
                }
        }
    }

    void MWindow::SwapBuffers()
    {

    }
}

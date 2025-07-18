#include <platform/window/window.hpp>

namespace mnm::window
{
    // Platform specific internal state
    struct MWindowContext
    {
        int x;
    };

    MWindow::MWindow()
    {
        //mContext = std::make_unique<MWindowContext>();
    }

    bool MWindow::Initialize()
    {
        std::cout << "Init Win32 Window\n";

        return true;
    }
}

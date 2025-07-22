#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <defines.hpp>

namespace mnm
{
    class MAPI MnemosApplication
    {
    public:
        virtual void OnInit() = 0;
        virtual void OnUpdate() = 0;
        virtual void OnFixedUpdate() = 0;
        virtual void OnShutdown() = 0;
    };
}

#endif

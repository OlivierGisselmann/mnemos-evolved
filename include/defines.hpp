#ifndef DEFINES_HPP
#define DEFINES_HPP

#ifdef MEXPORT
    #ifdef _MSC_VER
        #define MAPI __declspec(dllexport)
    #else
        #define MAPI __attribute__((visibility("default")))
    #endif
#else
    #ifdef _MSC_VER
        #define MAPI __declspec(dllimport)
    #else
        #define MAPI
    #endif
#endif

#endif

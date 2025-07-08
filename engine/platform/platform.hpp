#ifndef PLATFORM_HPP
#define PLATFORM_HPP

#if defined(WIN32) || defined(_WIN32) || defined(_WIN32_) || defined(__NT__)
    #define MNM_PLATFORM_WIN32
#elif defined(__linux__) || defined(__linux) || defined(_linux_)
    #define MNM_PLATFORM_LINUX
#endif

#endif

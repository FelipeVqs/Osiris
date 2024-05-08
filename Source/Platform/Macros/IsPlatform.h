#pragma once

#if defined(_WIN64)
    #define IS_WIN64() true
    #define IS_LINUX() false
#elif defined(__linux__) && defined(__x86_64__)
    #define IS_WIN64() false
    #define IS_LINUX() true
#else
    #define IS_WIN64() false
    #define IS_LINUX() false
#endif

#if IS_WIN64()
    #define HAVE_WIN64 1
#elif IS_LINUX()
    #define HAVE_LINUX 1
#endif

#if HAVE_WIN64
    // Windows-specific code here
#elif HAVE_LINUX
    // Linux-specific code here
#endif

#pragma once

// Define a macro for each supported compiler
#if defined(__clang__)
    #define HAS_CLANG 1
#elif defined(__GNUC__)
    #define HAS_GCC 1
#elif defined(_MSC_VER)
    #define HAS_MSVC 1
#else
    #error "Unsupported compiler"
#endif

// Use the macros in the code
#if HAS_CLANG
    // Code specific to Clang
#elif HAS_GCC
    // Code specific to GCC
#elif HAS_MSVC
    // Code specific to MSVC
#endif


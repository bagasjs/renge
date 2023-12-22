#ifndef RENGE_BASE_H_
#define RENGE_BASE_H_

#if defined(_WIN32) || defined(__WIN32__)
    #define RN_PLATFORM_WINDOWS
#elif defined(__ANDROID__)
    #error "Android platform for Renge Engine is planned but not implemented yet"
    #define RN_PLATFORM_ANDROID
#elif defined(__linux__) || defined(__gnu_linux__)
    #define RN_PLATFORM_LINUX
#else
    #error "This platform is not supported for Renge Engine, Sorry"
#endif

#ifdef RN_BUILD_DLL
    #ifdef _MSC_VER
        #define RN_API __declspec(dllexport)
    #else
        #define RN_API __attribute__((visibility("default")))
    #endif
#else
    #ifdef _MSC_VER
        #define RN_API __declspec(dllimport)
    #else
        #define RN_API
    #endif
#endif

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#define RN_BIT(pos)   (1 << (pos))
#define RN_SIGN(T, a) (((T)(a) > 0) - ((T)(a) < 0))
#define RN_ABS(T, a)  (RN_SIGN(T, a) * a)
#define RN_MIN(a, b)  ((a) < (b) ? (a) : (b))
#define RN_MAX(a, b)  ((a) > (b) ? (a) : (b))

#endif // RENGE_BASE_H_

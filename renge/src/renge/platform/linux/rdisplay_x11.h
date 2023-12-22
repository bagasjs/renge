#ifndef RENGE_DISPLAY_X11_H_
#define RENGE_DISPLAY_X11_H_

#include "renge/platform/rwindow.h"

#include <X11/Xlib.h>

struct rn_window {
    Window handle;
};

typedef struct rn_display_device {
    Display *display;
    Atom wm_delete_window;

    struct  {
        size_t count;
        rn_window items[RN_MAXIMUM_WINDOWS];
    } windows;

    bool initialized;
} rn_display_device;

struct rn_graphic_context {
    struct {
    } egl;
    struct {
    } opengl;
    struct {
        int test;
    } vulkan;
};


#endif // RENGE_DISPLAY_X11_H_

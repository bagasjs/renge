#include "renge/core/rlog.h"
#include "renge/core/rwindow.h"

#include <X11/Xlib.h>

struct rn_window {
    Window handle;
};

typedef struct rn_display_device {
    Display *display;
    Atom wm_delete_window;
} rn_display_device;

static rn_display_device device = {0};

bool rn_display_device_init(void)
{
    Display *dpy = XOpenDisplay(NULL);
    if(!dpy) {
        RN_CORE_FATAL("Failed to open X11 Display");
        return false;
    }

    device.display = dpy;
    device.wm_delete_window = XInternAtom(device.display, "WM_DELETE_WINDOW", False);

    return true;
}

void rn_display_device_deinit(void)
{
    XCloseDisplay(device.display);
}

rn_window *rn_create_window(const char *title, int x, int y, uint32_t w, uint32_t h, uint8_t flags)
{
}

void rn_destroy_window(rn_window *window);



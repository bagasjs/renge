#include "renge/core/revent.h"
#include "renge/core/rlog.h"
#include "renge/platform/rwindow.h"

#include <X11/Xlib.h>
#include "rdisplay_x11.h"

static rn_display_device device = {0};

bool rn_display_device_init(void)
{
    if(device.initialized) return false;
    device.initialized = true;

    Display *dpy = XOpenDisplay(NULL);
    if(!dpy) {
        RN_CORE_FATAL("Failed to open X11 Display");
        return false;
    }

    device.display = dpy;
    device.wm_delete_window = XInternAtom(device.display, "WM_DELETE_WINDOW", False);
    device.windows.count = 0;

    return true;
}

void rn_display_device_deinit(void)
{
    XCloseDisplay(device.display);
}

rn_window *rn_create_window(const char *title, int x, int y, uint32_t w, uint32_t h, uint8_t flags)
{
    Window root;
    Window handle;

    root = XRootWindow(device.display, DefaultScreen(device.display));

    XSetWindowAttributes swa;
    swa.override_redirect = False;
    swa.event_mask = ExposureMask | ButtonPressMask | KeyPressMask;

    handle = XCreateWindow(device.display, root,
            x, y, w, h, 0,
            CopyFromParent, InputOutput,
            CopyFromParent, CWEventMask,
            &swa);

    XSetWMProtocols(device.display, handle, &device.wm_delete_window, 1);
    XStoreName(device.display, handle, title);
    XMapWindow(device.display, handle);

    if(device.windows.count >= 8) {
        RN_CORE_ERROR("Failed to create a new window, you already have 8 Window");
        return NULL;
    }

    rn_window *result = &device.windows.items[device.windows.count];
    result->handle = handle;
    return result;
}

void rn_destroy_window(rn_window *window)
{
    if(device.windows.count > 0) {
        device.windows.count -= 1;
        XDestroyWindow(device.display, window->handle);
    }
}

void rn_collect_window_events(void)
{
    XEvent event = {0};
    rn_event result;
    while(XPending(device.display) > 0) {
        XNextEvent(device.display, &event);
        switch(event.type) {
            case ClientMessage:
                {
                    if((Atom)event.xclient.data.l[0] == device.wm_delete_window) {
                        result.type = RN_EVENT_WINDOW_CLOSE;
                        rn_event_fire(RN_EVENT_CATEGORY_APPLICATION, &result);
                    }
                } break;
            default:
                {
                } break;
        }
    }
}

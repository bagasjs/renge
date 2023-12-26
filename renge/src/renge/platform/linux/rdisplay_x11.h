#ifndef RENGE_DISPLAY_X11_H_
#define RENGE_DISPLAY_X11_H_

#include "renge/platform/rwindow.h"

#include <X11/X.h>
#include <X11/Xlib.h>
#include <GL/glx.h>
#include <X11/Xutil.h>

struct rn_window {
    Display *display;
    Window handle;
    Colormap colormap;
};

typedef struct rn_display_device {
    Display *display;
    Atom wm_delete_window;

    struct  {
        size_t count;
        rn_window items[RN_MAXIMUM_WINDOWS];
    } windows;

    Screen *default_screen;
    int default_screen_id;
    Window default_root_window;
    unsigned long black_pixel;
    unsigned long white_pixel;

    struct {
        int event_base, error_base;
        int major, minor;
        struct {
            bool EXT_swap_control;
            bool SGI_swap_control;
            bool MESA_swap_control;

            bool ARB_multisample;
            bool ARB_framebuffer_sRGB;
            bool EXT_framebuffer_sRGB;
            bool ARB_create_context;

            bool ARB_create_context_robustness;
            bool ARB_create_context_profile;
            bool EXT_create_context_es2_profile;
            bool ARB_create_context_no_error;
            bool ARB_context_flush_control;

        } extensions;
        struct {
            PFNGLXSWAPINTERVALEXTPROC SwapIntervalEXT;
            PFNGLXSWAPINTERVALSGIPROC SwapIntervalSGI;
            PFNGLXSWAPINTERVALMESAPROC SwapIntervalMESA;
            PFNGLXCREATECONTEXTATTRIBSARBPROC CreateContextAttribsARB;
        } api;
        GLXFBConfig fbconfig;
        XVisualInfo *visual_info;
    } glx;
    struct {
    } egl;

    // GLXFBConfig best_fbc;
    // XVisualInfo *visual_info;

    bool initialized;
} rn_display_device;

rn_display_device *rn__get_display_device(void);

#endif // RENGE_DISPLAY_X11_H_

#include "renge/core/revent.h"
#include "renge/core/rlog.h"
#include "renge/platform/rwindow.h"
#include "renge/core/rstring.h"

#include <GL/glx.h>
#include <X11/X.h>
#include <X11/Xlib.h>
#include "rdisplay_x11.h"

static rn_display_device device = {0};

rn_display_device *rn__get_display_device(void)
{
    return &device;
}

bool rn__string_in_extension_string(const char* string, const char* extensions)
{
    const char* start = extensions;

    for (;;)
    {
        const char* where;
        const char* terminator;

        where = rn_strstr(start, string);
        if (!where)
            return false;

        terminator = where + rn_strlen(string);
        if (where == start || *(where - 1) == ' ')
        {
            if (*terminator == ' ' || *terminator == '\0')
                break;
        }

        start = terminator;
    }

    return true;
}

static int rn__is_glx_extension_supported(const char* extension)
{
    const char* extensions = glXQueryExtensionsString(device.display, device.default_screen_id);
    if (extensions)
    {
        if (rn__string_in_extension_string(extension, extensions))
            return true;
    }

    return false;
}

static bool rn__choose_glx_fb_config(void)
{
	GLint glx_attribs[] = {
		GLX_X_RENDERABLE    , True,
		GLX_DRAWABLE_TYPE   , GLX_WINDOW_BIT,
		GLX_RENDER_TYPE     , GLX_RGBA_BIT,
		GLX_X_VISUAL_TYPE   , GLX_TRUE_COLOR,
		GLX_RED_SIZE        , 8,
		GLX_GREEN_SIZE      , 8,
		GLX_BLUE_SIZE       , 8,
		GLX_ALPHA_SIZE      , 8,
		GLX_DEPTH_SIZE      , 24,
		GLX_STENCIL_SIZE    , 8,
		GLX_DOUBLEBUFFER    , True,
		None
	};

	int fb_count;
    GLXFBConfig* fbc = glXChooseFBConfig(device.display, device.default_screen_id, glx_attribs, &fb_count);
    if (fbc == 0) {
        RN_CORE_ERROR("Failed to retrive GLX Framebuffer");
        return false;
    }

	// Pick the FB config/visual with the most samples per pixel
	int best_fbc = -1, worst_fbc = -1, best_num_samp = -1, worst_num_samp = 999;
	for (int i = 0; i < fb_count; ++i) {
		XVisualInfo *vi = glXGetVisualFromFBConfig(device.display, fbc[i]);
		if (vi != 0) {
			int samp_buf, samples;
			glXGetFBConfigAttrib(device.display, fbc[i], GLX_SAMPLE_BUFFERS, &samp_buf);
			glXGetFBConfigAttrib(device.display, fbc[i], GLX_SAMPLES       , &samples);

			if(best_fbc < 0 || (samp_buf && samples > best_num_samp)) {
				best_fbc = i;
				best_num_samp = samples;
			}
			if(worst_fbc < 0 || !samp_buf || samples < worst_num_samp) {
				worst_fbc = i;
            }
			worst_num_samp = samples;
		}
		XFree(vi);
	}

    device.glx.fbconfig = fbc[best_fbc];
	XFree(fbc);
    return true;
}

bool rn_init_glx(void)
{
    if (!glXQueryExtension(device.display, &device.glx.error_base, &device.glx.event_base)) {
        RN_CORE_ERROR("GLX: GLX extension not found");
        return false;
    }

    if (!glXQueryVersion(device.display, &device.glx.major, &device.glx.minor)) {
        RN_CORE_ERROR("GLX: Failed to query GLX version");
        return false;
    }

    if (device.glx.major == 1 && device.glx.minor < 3) {
        RN_CORE_ERROR("GLX: GLX version 1.3 is required");
        return false;
    }

    if (rn__is_glx_extension_supported("GLX_EXT_swap_control")) {
        device.glx.api.SwapIntervalEXT = (PFNGLXSWAPINTERVALEXTPROC)
            glXGetProcAddressARB((const GLubyte *)"glXSwapIntervalEXT");

        if (device.glx.api.SwapIntervalEXT)
            device.glx.extensions.EXT_swap_control = true;
    }

    if (rn__is_glx_extension_supported("GLX_SGI_swap_control")) {
        device.glx.api.SwapIntervalSGI = (PFNGLXSWAPINTERVALSGIPROC)
            glXGetProcAddressARB((const GLubyte *)"glXSwapIntervalSGI");

        if (device.glx.api.SwapIntervalSGI)
            device.glx.extensions.SGI_swap_control = true;
    }

    if (rn__is_glx_extension_supported("GLX_MESA_swap_control")) {
        device.glx.api.SwapIntervalMESA = (PFNGLXSWAPINTERVALMESAPROC)
            glXGetProcAddressARB((const GLubyte *)"glXSwapIntervalMESA");

        if (device.glx.api.SwapIntervalMESA)
            device.glx.extensions.MESA_swap_control = true;
    }

    if (rn__is_glx_extension_supported("GLX_ARB_create_context"))
    {
        device.glx.api.CreateContextAttribsARB = (PFNGLXCREATECONTEXTATTRIBSARBPROC)
            glXGetProcAddressARB((const GLubyte *)"glXCreateContextAttribsARB");

        if (device.glx.api.CreateContextAttribsARB)
            device.glx.extensions.ARB_create_context = true;
    }

    if (rn__is_glx_extension_supported("GLX_ARB_multisample"))
        device.glx.extensions.ARB_multisample = true;
    if (rn__is_glx_extension_supported("GLX_ARB_framebuffer_sRGB"))
        device.glx.extensions.ARB_framebuffer_sRGB = true;
    if (rn__is_glx_extension_supported("GLX_EXT_framebuffer_sRGB"))
        device.glx.extensions.EXT_framebuffer_sRGB = true;
    if (rn__is_glx_extension_supported("GLX_ARB_create_context_robustness"))
        device.glx.extensions.ARB_create_context_robustness = true;
    if (rn__is_glx_extension_supported("GLX_ARB_create_context_profile"))
        device.glx.extensions.ARB_create_context_profile = true;
    if (rn__is_glx_extension_supported("GLX_EXT_create_context_es2_profile"))
        device.glx.extensions.EXT_create_context_es2_profile = true;
    if (rn__is_glx_extension_supported("GLX_ARB_create_context_no_error"))
        device.glx.extensions.ARB_create_context_no_error = true;
    if (rn__is_glx_extension_supported("GLX_ARB_context_flush_control"))
        device.glx.extensions.ARB_context_flush_control = true;

    if(!rn__choose_glx_fb_config()) {
        return false;
    }

	device.glx.visual_info = glXGetVisualFromFBConfig(device.display, device.glx.fbconfig);
	if (device.glx.visual_info == 0) {
        RN_CORE_ERROR("Could not create correct visual info");
		return false;
	}

	if (device.default_screen_id != device.glx.visual_info->screen) {
        RN_CORE_ERROR("Screen ID doesnt match visual screen ID");
		return false;
	}

    return true;
}

bool rn_init_egl(void)
{
    return true;
}

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

    device.default_screen = XDefaultScreenOfDisplay(device.display);
    device.default_screen_id = XDefaultScreen(device.display);
    device.default_root_window = XRootWindow(device.display, device.default_screen_id);
    device.black_pixel = XBlackPixel(device.display, device.default_screen_id);
    device.white_pixel = XWhitePixel(device.display, device.default_screen_id);
    device.windows.count = 0;

    if(!rn_init_glx()) {
        XCloseDisplay(device.display);
        return false;
    }

    if(!rn_init_egl()) {
        XCloseDisplay(device.display);
        return false;
    }

    return true;
}

void rn_display_device_deinit(void)
{
    XCloseDisplay(device.display);
}

rn_window *rn_create_window(const char *title, int x, int y, uint32_t w, uint32_t h, uint8_t flags)
{
    Window handle;

    XSetWindowAttributes swa;
    swa.override_redirect = True;
    swa.border_pixel = None;
    swa.background_pixel = XBlackPixel(device.display, device.default_screen_id);
    swa.colormap = XCreateColormap(device.display, device.default_root_window, 
            XDefaultVisualOfScreen(device.default_screen), AllocNone);
    swa.event_mask = StructureNotifyMask | KeyPressMask | KeyReleaseMask |
                    PointerMotionMask | ButtonPressMask | ButtonReleaseMask |
                    ExposureMask | FocusChangeMask | VisibilityChangeMask |
                    EnterWindowMask | LeaveWindowMask | PropertyChangeMask;

    handle = XCreateWindow(device.display, device.default_root_window,
            x, y, w, h, 0,
            CopyFromParent, InputOutput,
            CopyFromParent, 
            CWBackPixel | CWColormap | CWBorderPixel | CWEventMask,
            &swa);

    if(!handle) {
        return NULL;
    }

    XSetWMProtocols(device.display, handle, &device.wm_delete_window, 1);
    XStoreName(device.display, handle, title);
    XMapWindow(device.display, handle);

    if(device.windows.count >= 8) {
        RN_CORE_ERROR("Failed to create a new window, you already have 8 Window");
        return NULL;
    }

    rn_window *result = &device.windows.items[device.windows.count];
    result->handle = handle;
    result->colormap = swa.colormap;
    result->display = device.display;
    return result;
}

void rn_destroy_window(rn_window *window)
{
    if(device.windows.count > 0) {
        XFreeColormap(device.display, window->colormap);
        XDestroyWindow(device.display, window->handle);
        device.windows.count -= 1;
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

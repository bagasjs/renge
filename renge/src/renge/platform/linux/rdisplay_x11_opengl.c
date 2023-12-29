#include "renge/core/rlog.h"
#include "renge/core/rmemory.h"
#include "renge/platform/rwindow.h"
#include "renge/platform/rgc.h"

#include "rdisplay_x11.h"

#include <GL/glxext.h>
#include <X11/Xlib.h>
#include <GL/glx.h>

typedef struct rn_opengl_context {
    int source;
    struct {
        GLXContext handle;
        GLXWindow window;
    } glx;
} rn_opengl_context;

rn_opengl_context *rn_create_opengl_context(rn_window *window, const rn_opengl_context_config *config)
{
    rn_display_device *device = rn__get_display_device();

    int attribs[40];
    GLXContext share = NULL;
    GLXContext result_context = NULL;

    if(config->api == RN_OPENGL_CONTEXT_API_OPENGLES) {
        if (!device->glx.extensions.ARB_create_context ||
                !device->glx.extensions.ARB_create_context_profile ||
                !device->glx.extensions.EXT_create_context_es2_profile) {
            RN_CORE_ERROR("GLX: OpenGL ES requested but GLX_EXT_create_context_es2_profile is unavailable");
            return false;
        }
    }

    if (config->forward)
    {
        if (!device->glx.extensions.ARB_create_context)
        {
            RN_CORE_ERROR("GLX: Forward compatibility requested but GLX_ARB_create_context_profile is unavailable");
            return false;
        }
    }

    if(device->glx.extensions.ARB_create_context) {
        int attribs[40];
#define SET_ATTRIB(a, v) \
        { \
            RN_CORE_ASSERT(((size_t) index + 1) < sizeof(attribs) / sizeof(attribs[0])); \
            attribs[index++] = a; \
            attribs[index++] = v; \
        }

        int index = 0, mask = 0, flags = 0;
        if(config->api == RN_OPENGL_CONTEXT_API_OPENGLES) {
            mask |= GLX_CONTEXT_ES2_PROFILE_BIT_EXT;
        } else {
            if (config->profile == RN_OPENGL_CONTEXT_CORE_PROFILE) mask |= GLX_CONTEXT_CORE_PROFILE_BIT_ARB;
            else mask |= GLX_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB;
        }

        if (config->debug) flags |= GLX_CONTEXT_DEBUG_BIT_ARB;
        if (config->version.major != 1 || config->version.minor != 0)
        {
            SET_ATTRIB(GLX_CONTEXT_MAJOR_VERSION_ARB, config->version.major);
            SET_ATTRIB(GLX_CONTEXT_MINOR_VERSION_ARB, config->version.minor);
        }

        if (mask)
            SET_ATTRIB(GLX_CONTEXT_PROFILE_MASK_ARB, mask);

        if (flags)
            SET_ATTRIB(GLX_CONTEXT_FLAGS_ARB, flags);

        SET_ATTRIB(None, None);
        result_context = device->glx.api.CreateContextAttribsARB(device->display,
                device->glx.fbconfig,
                share,
                True,
                attribs);

        if (!result_context) {
            RN_CORE_ERROR("Failed to create GLX context with ARB");
        }
    } else {
        result_context = glXCreateNewContext(device->display, device->glx.fbconfig, GLX_RGBA_TYPE, share, True);
    }

    rn_opengl_context *result = rn_malloc(sizeof(rn_opengl_context));
    if(!result) {
        glXDestroyContext(device->display, result_context);
        return NULL;
    }
    result->glx.handle = result_context;

    result->glx.window = glXCreateWindow(device->display, device->glx.fbconfig, window->handle, NULL);
    if (!result->glx.window)
    {
        RN_CORE_ERROR("Failed to create GLX window");
        return NULL;
    } 

    return result;
}

void rn_destroy_opengl_context(rn_opengl_context *context)
{
    rn_display_device *device = rn__get_display_device();
    glXDestroyWindow(device->display, context->glx.window);
    glXDestroyContext(device->display, context->glx.handle);
}

void rn_make_opengl_context_current(rn_window *window, rn_opengl_context *context)
{
    rn_display_device *device = rn__get_display_device();
    if (window) {
        if (!glXMakeCurrent(device->display, context->glx.window, context->glx.handle)) {
            RN_CORE_ERROR("GLX: Failed to make context current");
            return;
        }
    } else {
        if (!glXMakeCurrent(device->display, None, NULL)) {
            RN_CORE_ERROR("GLX: Failed to clear current context");
            return;
        }
    }

}

void rn_swap_opengl_buffer(rn_window *window, rn_opengl_context *context)
{
    glXSwapBuffers(window->display, context->glx.window);
}


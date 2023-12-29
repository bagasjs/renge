#ifndef RENGE_GRAPHIC_CONTEXT_H_
#define RENGE_GRAPHIC_CONTEXT_H_

#include "renge/platform/rwindow.h"

typedef struct rn_opengl_context rn_opengl_context;

typedef enum rn_opengl_context_config_enums {
    RN_OPENGL_CONTEXT_CONFIG_NONE = 0,

    RN_OPENGL_CONTEXT_FROM_GLX,
    RN_OPENGL_CONTEXT_FROM_EGL,
    RN_OPENGL_CONTEXT_FROM_MESA,

    RN_OPENGL_CONTEXT_ANY_PROFILE,
    RN_OPENGL_CONTEXT_COMPATIBILITY_PROFILE,
    RN_OPENGL_CONTEXT_CORE_PROFILE,

    RN_OPENGL_CONTEXT_API_OPENGL,
    RN_OPENGL_CONTEXT_API_OPENGLES,
} rn_opengl_context_config_enums;

typedef struct rn_opengl_context_config {
    int profile;
    int source;
    int api;
    bool forward;
    bool debug;
    struct { int major, minor; } version;
} rn_opengl_context_config;

rn_opengl_context *rn_create_opengl_context(rn_window *window, const rn_opengl_context_config *config);
void rn_destroy_opengl_context(rn_opengl_context *context);
void rn_make_opengl_context_current(rn_window *window, rn_opengl_context *context);
void rn_swap_opengl_buffer(rn_window *window, rn_opengl_context *context);

#endif // RENGE_GRAPHIC_CONTEXT_H_

#ifndef RENGE_GRAPHIC_CONTEXT_H_
#define RENGE_GRAPHIC_CONTEXT_H_

#include "renge/platform/rwindow.h"

typedef struct rn_opengl_context rn_opengl_context;

typedef struct rn_opengl_context_config {
    bool core_profile;
    bool opengles;
    bool forward;
    bool debug;
    struct { int major, minor; } version;
} rn_opengl_context_config;

rn_opengl_context *rn_create_opengl_context(rn_window *window, const rn_opengl_context_config *config);
void rn_destroy_opengl_context(rn_opengl_context *context);
void rn_make_opengl_context_current(rn_window *window, rn_opengl_context *context);
void rn_swap_opengl_buffer(rn_window *window, rn_opengl_context *context);

#endif // RENGE_GRAPHIC_CONTEXT_H_

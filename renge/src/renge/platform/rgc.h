#ifndef RENGE_GRAPHIC_CONTEXT_H_
#define RENGE_GRAPHIC_CONTEXT_H_

#include "renge/platform/rwindow.h"

typedef struct rn_graphic_context rn_graphic_context;

rn_graphic_context *rn_create_gc(rn_window *window);
void rn_destroy_gc(rn_graphic_context *context);
void rn_swap_buffer(rn_graphic_context *context);

#endif // RENGE_GRAPHIC_CONTEXT_H_

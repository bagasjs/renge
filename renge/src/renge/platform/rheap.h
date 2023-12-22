#ifndef RENGE_HEAP_H_
#define RENGE_HEAP_H_

#include "renge/core/rbase.h"

typedef struct rn_heap_buffer {
    void *data;
    size_t size;
} rn_heap_buffer;

bool rn_heap_buffer_init(rn_heap_buffer *buffer);
void rn_heap_buffer_deinit(rn_heap_buffer buffer);

#endif

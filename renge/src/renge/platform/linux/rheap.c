#include "renge/platform/rheap.h"
#include <sys/mman.h>

bool rn_heap_buffer_init(rn_heap_buffer *buffer)
{
    buffer->data = mmap(NULL,
            buffer->size, 
            PROT_READ | PROT_WRITE,
            MAP_ANONYMOUS | MAP_PRIVATE,
            -1, 0);
    if(!buffer->data) return false;
    return true;
}

void rn_heap_buffer_deinit(rn_heap_buffer buffer)
{
    munmap(buffer.data, buffer.size);
}

#include "rmemory.h"
#include <stdlib.h>

typedef struct rn_memory_manager {
    bool initialized;
} rn_memory_manager;

static rn_memory_manager memory;

bool rn_memory_init(void)
{
    if(memory.initialized) return false;
    memory.initialized = true;
    return true;
}

void rn_memory_deinit(void)
{
    memory.initialized = false;
}

void *rn_malloc(size_t n_bytes)
{
    void *result = malloc(n_bytes);
    if(!result) return NULL;
    return result;
}

void rn_free(void *ptr)
{
    if(!ptr) return;
    free(ptr);
}


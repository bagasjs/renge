#ifndef RENGE_MEMORY_H_
#define RENGE_MEMORY_H_

#include "renge/core/rbase.h"

bool rn_memory_init(void);
void rn_memory_deinit(void);

RN_API void *rn_malloc(size_t n_bytes);
RN_API void rn_free(void *ptr);


#endif // RENGE_MEMORY_H_

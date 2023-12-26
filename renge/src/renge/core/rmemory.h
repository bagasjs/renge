#ifndef RENGE_MEMORY_H_
#define RENGE_MEMORY_H_

#include "renge/core/rbase.h"

RN_API bool rn_memory_init(void);
RN_API void rn_memory_deinit(void);

RN_API void *rn_malloc(size_t n_bytes);
RN_API void rn_free(void *ptr);


#endif // RENGE_MEMORY_H_

#ifndef RENGE_MUTEX_H_
#define RENGE_MUTEX_H_

#include "renge/core/rbase.h"

typedef struct rn_mutex rn_mutex;

rn_mutex *rn_create_mutex(void);
void rn_destroy_mutex(rn_mutex *mutex);
void rn_lock_mutex(rn_mutex *mutex);
void rn_unlock_mutex(rn_mutex *mutex);

#endif // RENGE_MUTEX_H_

#ifndef RENGE_LOG_H_
#define RENGE_LOG_H_

#include "rbase.h"

typedef enum rn_log_level_t {
    RN_LOG_LEVEL_FATAL = 0,
    RN_LOG_LEVEL_ERROR = 1,
    RN_LOG_LEVEL_WARN  = 2,
    RN_LOG_LEVEL_INFO  = 3,
    RN_LOG_LEVEL_TRACE = 4,
} rn_log_level_t;

RN_API bool rn_logger_init(void);
RN_API void rn_logger_deinit(void);
RN_API void rn_logger_print(rn_log_level_t level, const char *fmt, ...);

#endif // RENGE_LOG_H_

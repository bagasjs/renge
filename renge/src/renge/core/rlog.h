#ifndef RENGE_LOG_H_
#define RENGE_LOG_H_

#include "renge/core/rbase.h"

typedef enum rn_log_level {
    RN_LOG_LEVEL_FATAL = 0,
    RN_LOG_LEVEL_ERROR = 1,
    RN_LOG_LEVEL_WARN  = 2,
    RN_LOG_LEVEL_INFO  = 3,
    RN_LOG_LEVEL_TRACE = 4,
} rn_log_level;

RN_API bool rn_logger_init(void);
RN_API void rn_logger_deinit(void);

RN_API void rn_logger_print(rn_log_level level, const char *fmt, ...);
RN_API void rn_core_logger_print(rn_log_level level, const char *fmt, ...);

#define RN_FATAL(...) rn_logger_print(RN_LOG_LEVEL_FATAL, __VA_ARGS__)
#define RN_ERROR(...) rn_logger_print(RN_LOG_LEVEL_ERROR, __VA_ARGS__)
#define RN_WARN(...)  rn_logger_print(RN_LOG_LEVEL_WARN,  __VA_ARGS__)
#define RN_INFO(...)  rn_logger_print(RN_LOG_LEVEL_INFO,  __VA_ARGS__)
#define RN_TRACE(...) rn_logger_print(RN_LOG_LEVEL_TRACE, __VA_ARGS__)


#define RN_CORE_FATAL(...) rn_core_logger_print(RN_LOG_LEVEL_FATAL, __VA_ARGS__)
#define RN_CORE_ERROR(...) rn_core_logger_print(RN_LOG_LEVEL_ERROR, __VA_ARGS__)
#define RN_CORE_WARN(...)  rn_core_logger_print(RN_LOG_LEVEL_WARN,  __VA_ARGS__)
#define RN_CORE_INFO(...)  rn_core_logger_print(RN_LOG_LEVEL_INFO,  __VA_ARGS__)
#define RN_CORE_TRACE(...) rn_core_logger_print(RN_LOG_LEVEL_TRACE, __VA_ARGS__)

#endif // RENGE_LOG_H_

#include "rlog.h"
#include <stdio.h>
#include <stdarg.h>

bool rn_logger_init(void)
{
    return true;
}

void rn_logger_deinit(void)
{
}

void rn_logger_print(rn_log_level level, const char *fmt, ...)
{
    static const char *level_string[] = { "FATAL", "ERROR", "WARN", "INFO", "TRACE", };
    FILE *f = stdout;
    switch(level) {
        case RN_LOG_LEVEL_FATAL:
            {
                f = stderr;
            } break;
        case RN_LOG_LEVEL_ERROR:
            {
                f = stderr;
            } break;
        case RN_LOG_LEVEL_WARN :
            {
                f = stderr;
            } break;
        default:
            break;
    }
    fprintf(f, "[%s] APP: ", level_string[level]);
    va_list ap;
    va_start(ap, fmt);
    vfprintf(f, fmt, ap);
    va_end(ap);
    fputc('\n', f);
}

void rn_core_logger_print(rn_log_level level, const char *fmt, ...)
{
    static const char *level_string[] = { "FATAL", "ERROR", "WARN", "INFO", "TRACE", };
    FILE *f = stdout;
    switch(level) {
        case RN_LOG_LEVEL_FATAL:
            {
                f = stderr;
            } break;
        case RN_LOG_LEVEL_ERROR:
            {
                f = stderr;
            } break;
        case RN_LOG_LEVEL_WARN :
            {
                f = stderr;
            } break;
        default:
            break;
    }
    fprintf(f, "[%s] RENGE: ", level_string[level]);
    va_list ap;
    va_start(ap, fmt);
    vfprintf(f, fmt, ap);
    va_end(ap);
    fputc('\n', f);
}














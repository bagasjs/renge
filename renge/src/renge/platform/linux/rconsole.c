#include "renge/platform/rconsole.h"

#include <unistd.h>

void rn_console_write(const char *message, size_t len)
{
    write(STDOUT_FILENO, (const void*)message, len);
}

void rn_console_error(const char *message, size_t len)
{
    write(STDERR_FILENO, (const void*)message, len);
}

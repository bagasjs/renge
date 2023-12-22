#ifndef RENGE_CONSOLE_H_
#define RENGE_CONSOLE_H_

#include "renge/core/rbase.h"

void rn_console_write(const char *message, size_t len);
void rn_console_error(const char *message, size_t len);

#endif // RENGE_CONSOLE_H_

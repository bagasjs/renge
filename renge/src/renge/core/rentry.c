#include "rentry.h"
#include "rlog.h"

int renge_main(int argc, char **argv)
{
    rn_logger_init();
    rn_logger_print(RN_LOG_LEVEL_INFO, "Engine is initialized successfully");
    return 0;
}

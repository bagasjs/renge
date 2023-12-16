#ifndef RENGE_ENTRPOINT_H_
#define RENGE_ENTRPOINT_H_

#include "renge/core/rapplication.h"

extern void rn_setup_application(rn_application_config *config);
int renge_main(int argc, char **argv);

int main(int argc, char **argv)
{
    return renge_main(argc, argv);
}

#endif // RENGE_ENTRPOINT_H_

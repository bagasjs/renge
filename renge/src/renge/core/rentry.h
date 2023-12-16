#ifndef RENGE_ENTRPOINT_H_
#define RENGE_ENTRPOINT_H_

#include "renge/core/rapplication.h"

extern rn_application *rn_get_application(void);
int renge_main(int argc, char **argv);

int main(int argc, char **argv)
{
    return renge_main(argc, argv);
}

#endif // RENGE_ENTRPOINT_H_

#include "rapplication.h"
#include "rentry.h"
#include "rlog.h"
#include "revent.h"

#define RN_APPLICATION_MAXIMUM_LAYERS 32

struct rn_application {
    bool initialized;
    bool should_close;
    const char *name;
    RN_PFN_on_application_init on_init;
    RN_PFN_on_application_process on_process;
    RN_PFN_on_application_shutdown on_shutdown;
};

static rn_application application = {0};

rn_application *rn_create_application(const rn_application_config *config)
{
    if(application.initialized) {
        return NULL;
    }

    application.initialized = true;
    application.name = config->name;
    application.on_init = config->on_init;
    application.on_process = config->on_process;
    application.on_shutdown = config->on_shutdown;

    return &application;
}

void rn_destroy_application(rn_application *application)
{
    application->initialized = false;
}

void rn_set_application_should_close(rn_application *application, bool should_close)
{
    application->should_close = true;
}

int renge_main(int argc, char **argv)
{
    rn_application *application = rn_get_application();

    application->on_init(application);
    application->should_close = false;

    while(!application->should_close) {
        application->on_process(application);
    }

    application->on_shutdown(application);
    rn_destroy_application(application);
    return 0;
}

#include "rapplication.h"
#include "rentry.h"

#include "rlog.h"
#include "revent.h"
#include "renge/platform/rwindow.h"

#define RN_APPLICATION_MAXIMUM_LAYERS 32

struct rn_application {
    bool initialized;
    bool should_close;
    const char *name;
    RN_PFN_on_application_init on_init;
    RN_PFN_on_application_process on_process;
    RN_PFN_on_application_shutdown on_shutdown;
    void *user_data;
};

static rn_application application = {0};

RN_API rn_application *rn_get_current_application(void)
{
    return &application;
}

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
    application.user_data = config->user_data;

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

void *rn_get_application_user_data(rn_application *application)
{
    return application->user_data;
}

void rn_set_application_user_data(rn_application *application, void *user_data)
{
    application->user_data = user_data;
}

bool rn_init_engine(void)
{
    bool init_success = true;
    init_success = init_success && rn_logger_init();
    init_success = init_success && rn_event_manager_init();
    init_success = init_success && rn_display_device_init();
    return init_success;
}

void rn_deinit_engine(void)
{
    rn_display_device_deinit();
    rn_event_manager_deinit();
    rn_logger_deinit();

}

int renge_main(int argc, char **argv)
{
    if(!rn_init_engine()) {
        return -1;
    }

    RN_CORE_INFO("Engine initialization successfully");

    rn_application *application = rn_get_application();

    application->on_init(application);
    application->should_close = false;

    while(!application->should_close) {
        rn_collect_window_events();
        application->on_process(application);
    }

    application->on_shutdown(application);
    rn_destroy_application(application);

    RN_CORE_INFO("Engine deinitiaization successfully");

    rn_deinit_engine();

    return 0;
}

#include "renge.h"
#include "renge/core/rapplication.h"
#include "renge/core/rentry.h"
#include "renge/core/rlog.h"

void sandbox_init(rn_application *application) {
    RN_INFO("Initializing Sandbox");
}

void sandbox_process(rn_application *application) {
    RN_INFO("Sandbox process");
    rn_set_application_should_close(application, true);
}

void sandbox_shutdown(rn_application *application) {
    RN_INFO("Deinitializing sandbox");
}

rn_application *rn_get_application() {
    rn_application_config config;
    config.name = "Sandbox";
    config.on_init = sandbox_init;
    config.on_process = sandbox_process;
    config.on_shutdown = sandbox_shutdown;
    RN_INFO("Creating client application");
    return rn_create_application(&config);
}

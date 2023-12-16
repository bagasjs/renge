#include "rapplication.h"
#include "rentry.h"
#include "rlog.h"
#include "revent.h"

typedef struct rn_application {
    rn_application_config config;
} rn_application;

static rn_application application = {0};

bool rn_push_application_layer(rn_application_layer_list *list, const rn_application_layer *layer)
{
    if(list->count + 1 > list->capacity) {
        return false;
    }
    list->items[list->count].name = layer->name;
    list->items[list->count].callbacks = layer->callbacks;
    list->count += 1;
    return true;
}

bool rn_init(const rn_application_config *config)
{
    bool result = false;
    result = rn_logger_init() && result;
    result = rn_event_manager_init() && result;
    return result;
}

void rn_deinit(void)
{
    rn_event_manager_init();
    rn_logger_deinit();
}

int renge_main(int argc, char **argv)
{
    rn_setup_application(&application.config);
    if(rn_init(&application.config)) {
        return -2;
    }

    rn_logger_print(RN_LOG_LEVEL_INFO, "Engine is initialized successfully");
    rn_logger_print(RN_LOG_LEVEL_INFO, "Application Name: %s", application.config.name);

    rn_deinit();
    return 0;
}

#include "renge.h"

typedef struct sandbox_state {
    rn_window *window;
    rn_application *application;
} sandbox_state;

void sandbox_handle_event(const rn_event *event, void *user_data)
{
    sandbox_state *state = (sandbox_state *)user_data;
    switch(event->type) {
        case RN_EVENT_WINDOW_CLOSE:
            {
                rn_set_application_should_close(state->application, true);
            } break;
        default:
            break;
    }
}

void sandbox_init(rn_application *application) 
{
    RN_INFO("Initializing Sandbox");
    sandbox_state *state = rn_get_application_user_data(application);
    state->window = rn_create_window("My Window", 0, 0, 800, 600, 0);
    state->application = application;
    rn_event_handler handler;
    handler.on_event = sandbox_handle_event;
    handler.user_data = (void *)state;
    handler.handled_categories = RN_EVENT_CATEGORY_APPLICATION;
    rn_register_event_handler(&handler);
}

void sandbox_process(rn_application *application) 
{
    RN_INFO("Sandbox process");
}

void sandbox_shutdown(rn_application *application) 
{
    sandbox_state *state = rn_get_application_user_data(application);
    rn_destroy_window(state->window);
    RN_INFO("Deinitializing sandbox");
}

static sandbox_state state = {0};

rn_application *rn_get_application() 
{
    rn_application_config config;
    config.name = "Sandbox";
    config.on_init = sandbox_init;
    config.on_process = sandbox_process;
    config.on_shutdown = sandbox_shutdown;
    config.user_data = (void *)&state;
    RN_INFO("Creating client application");
    return rn_create_application(&config);
}

#include "revent.h"
#include "renge/core/rlog.h"

#define RN_MAXIMUM_REGISTERED_EVENT_HANDLERS 256
#define RN_MAXIMUM_EVENTS_IN_EVENT_QUEUE 256

typedef struct rn_event_manager {
    struct {
        rn_event_handler items[RN_MAXIMUM_REGISTERED_EVENT_HANDLERS];
        uint32_t count, capacity;
    } handlers;
    struct {
        rn_event events[RN_MAXIMUM_EVENTS_IN_EVENT_QUEUE];
        uint32_t head, tail;
        bool carry;
    } event_queue;
} rn_event_manager;

static rn_event_manager event_manager = {0};

bool rn_event_manager_init(void)
{
    event_manager.handlers.capacity = RN_MAXIMUM_REGISTERED_EVENT_HANDLERS;
    event_manager.handlers.count = 0;
    return true;
}

void rn_event_manager_deinit(void)
{
    event_manager.handlers.count = 0;
    event_manager.handlers.capacity = RN_MAXIMUM_REGISTERED_EVENT_HANDLERS;
    event_manager.handlers.count = 0;
}

bool rn_register_event_handler(const rn_event_handler *handler)
{
    if(event_manager.handlers.count + 1 > event_manager.handlers.capacity) {
        return false;
    }
    event_manager.handlers.items[event_manager.handlers.count].on_event = handler->on_event;
    event_manager.handlers.items[event_manager.handlers.count].handled_categories = handler->handled_categories;
    event_manager.handlers.items[event_manager.handlers.count].handled_categories = handler->handled_categories;
    event_manager.handlers.count += 1;
    return true;
}

void rn_event_fire(rn_event_category category, const rn_event *event)
{
    for(uint32_t i = 0; i < event_manager.handlers.count; ++i) {
        rn_event_handler handler = event_manager.handlers.items[i];
        if(category & handler.handled_categories) {
            handler.on_event(event);
        }
    }
}

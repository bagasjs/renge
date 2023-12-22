#ifndef RENGE_EVENT_H_
#define RENGE_EVENT_H_

#include "renge/core/rbase.h"

typedef enum rn_event_type {
    RN_EVENT_NONE = 0,
    RN_EVENT_WINDOW_CLOSE, RN_EVENT_WINDOW_RESIZE, RN_EVENT_WINDOW_FOCUS,
    RN_EVENT_WINDOW_LOST_FOCUS, RN_EVENT_WINDOW_MOVED,

    RN_EVENT_KEY_PRESSED, RN_EVENT_KEY_RELEASED,
    RN_EVENT_MOUSE_BUTTON_PRESSED, RN_EVENT_MOUSE_BUTTON_RELEASED,
    RN_EVENT_MOUSE_MOVED, RN_EVENT_MOUSE_SCROLLED,
} rn_event_type;

typedef enum rn_event_category {
    RN_EVENT_CATEGORY_NONE = 0,
    RN_EVENT_CATEGORY_APPLICATION  = RN_BIT(0),
    RN_EVENT_CATEGORY_INPUT        = RN_BIT(1),
    RN_EVENT_CATEGORY_KEYBOARD     = RN_BIT(2),
    RN_EVENT_CATEGORY_MOUSE        = RN_BIT(3),
    RN_EVENT_CATEGORY_MOUSE_BUTTON = RN_BIT(4),
} rn_event_category;

typedef struct rn_event {
    rn_event_type type;
} rn_event;

typedef void (*RN_PFN_on_event)(const rn_event *event, void *user_data);

typedef struct rn_event_handler {
    rn_event_category handled_categories;
    RN_PFN_on_event on_event;
    void *user_data;
} rn_event_handler;

bool rn_event_manager_init(void);
void rn_event_manager_deinit(void);

// TODO: add a way to unregister the event
RN_API bool rn_register_event_handler(const rn_event_handler *handler);
RN_API void rn_event_fire(rn_event_category category, const rn_event *event);

#endif // RENGE_EVENT_H_

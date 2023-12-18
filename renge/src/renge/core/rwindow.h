#ifndef RENGE_WINDOW_H_
#define RENGE_WINDOW_H_

#include "renge/core/rbase.h"

typedef struct rn_monitor_info {
    uint32_t ID;
    uint32_t width, height;
} rn_monitor_info;

typedef struct rn_window rn_window;

bool rn_display_device_init(void);
void rn_display_device_deinit(void);
bool rn_enumerate_monitors_info(rn_monitor_info *monitors, uint32_t *amount);

rn_window *rn_create_window(const char *title, int x, int y, uint32_t w, uint32_t h, uint8_t flags);
void rn_destroy_window(rn_window *window);

#endif // RENGE_WINDOW_H_

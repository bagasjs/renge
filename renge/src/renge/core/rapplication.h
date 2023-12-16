#ifndef RENGE_APPLICATION_H_
#define RENGE_APPLICATION_H_

#include <renge/core/rbase.h>

#define RN_MAXIMUM_APPLICATION_LAYERS 32

typedef void(*RN_PFN_on_app_layer_init)();
typedef void(*RN_PFN_on_app_layer_process)();
typedef void(*RN_PFN_on_app_layer_deinit)();

typedef struct rn_application_layer {
    const char *name;
    struct {
        RN_PFN_on_app_layer_process on_process;
        RN_PFN_on_app_layer_init on_init;
        RN_PFN_on_app_layer_deinit on_deinit;
    } callbacks;
} rn_application_layer;

typedef struct rn_application_layer_list {
    rn_application_layer items[RN_MAXIMUM_APPLICATION_LAYERS];
    size_t count, capacity;
} rn_application_layer_list;

typedef struct rn_application_config {
    const char *name;
    rn_application_layer_list layers;
} rn_application_config;

bool rn_push_application_layer(rn_application_layer_list *list, const rn_application_layer *layer);

bool rn_init(const rn_application_config *config);
void rn_deinit(void);

#endif // RENGE_APPLICATION_H_

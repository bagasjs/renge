#ifndef RENGE_APPLICATION_H_
#define RENGE_APPLICATION_H_

#include <renge/core/rbase.h>

#define RN_MAXIMUM_APPLICATION_LAYERS 32

typedef struct rn_application rn_application;
typedef void(*RN_PFN_on_application_init)(rn_application* app);
typedef void(*RN_PFN_on_application_process)(rn_application* app);
typedef void(*RN_PFN_on_application_shutdown)(rn_application *app);

typedef struct rn_application_config {
    const char *name;
    RN_PFN_on_application_init on_init;
    RN_PFN_on_application_process on_process;
    RN_PFN_on_application_shutdown on_shutdown;
} rn_application_config;

rn_application *rn_create_application(const rn_application_config *config);
void rn_destroy_application(rn_application *application);
void rn_set_application_should_close(rn_application *application, bool should_close);

#endif // RENGE_APPLICATION_H_

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
    void *user_data;
} rn_application_config;

RN_API bool rn_init_engine(void);
RN_API void rn_deinit_engine(void);

RN_API rn_application *rn_create_application(const rn_application_config *config);
RN_API void rn_destroy_application(rn_application *application);
RN_API void rn_set_application_should_close(rn_application *application, bool should_close);
RN_API void rn_set_application_user_data(rn_application *application, void *user_data);
RN_API void *rn_get_application_user_data(rn_application *application);

#endif // RENGE_APPLICATION_H_

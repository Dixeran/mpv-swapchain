#ifndef MPV_CLIENT_API_RENDER_SWAPCHAIN_H_
#define MPV_CLIENT_API_RENDER_SWAPCHAIN_H_

#include "render.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct render_swapchain_init_params {
    void* swapchain_out;
} render_swapchain_init_params;

typedef struct render_swapchain_update_params {
    int h;
    int w;
} render_swapchain_update_params;

#ifdef __cplusplus
}
#endif
#endif // MPV_CLIENT_API_RENDER_SWAPCHAIN_H_

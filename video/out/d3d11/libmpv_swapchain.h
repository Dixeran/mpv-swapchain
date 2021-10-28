#ifndef MPV_LIBMPV_SWAPCHAIN_H_
#define MPV_LIBMPV_SWAPCHAIN_H_

#include "video/out/gpu/context.h"
#include <dxgi.h>

bool is_render_headless(struct ra_ctx *ctx);
bool resize_update(struct ra_ctx *ctx, int *w_new, int *h_new);
void expose_swapchain(struct ra_ctx *ctx, IDXGISwapChain *swapchain);

#endif

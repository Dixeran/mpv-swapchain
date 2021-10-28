#ifndef MPV_LIBMPV_HELPER_H_
#define MPV_LIBMPV_HELPER_H_

#include "video/out/libmpv.h"
#include "video/out/gpu/context.h"

/*
 * Useful helpers for bridging between vo and libmpv backend
 * since we don't have access to those internal structs.
 */

struct mp_client_api;
struct mpv_render_context;

struct render_backend *get_libmpv_renderer_from_client(struct mp_client_api *mp_client);
struct render_backend *get_libmpv_renderer_from_ctx(struct mpv_render_context *ctx);
struct render_backend *get_libmpv_renderer(struct ra_ctx *ctx);

#endif

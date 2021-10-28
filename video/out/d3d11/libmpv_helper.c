#include "libmpv_helper.h"
#include "common/global.h"

struct render_backend *get_libmpv_renderer(struct ra_ctx *ctx)
{
    return get_libmpv_renderer_from_client(ctx->global->client_api);
}

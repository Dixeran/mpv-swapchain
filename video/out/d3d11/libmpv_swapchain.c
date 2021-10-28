#include "config.h"
#include "libmpv/render_swapchain.h"
#include "video/out/libmpv.h"
#include "libmpv_swapchain.h"
#include "libmpv_helper.h"

struct priv
{
    int w;
    int h;
    // user's swapchain pointer
    void *swapchain_out;
};

static int init(struct render_backend *ctx, mpv_render_param *params)
{
    ctx->priv = talloc_zero(NULL, struct priv);
    struct priv *p = ctx->priv;
    p->w = 320;
    p->h = 240;
    p->swapchain_out = NULL;

    char *api = get_mpv_render_param(params, MPV_RENDER_PARAM_API_TYPE, NULL);
    if (!api)
        return MPV_ERROR_INVALID_PARAMETER;

    if (strcmp(api, MPV_RENDER_API_TYPE_SWAPCHAIN) != 0)
        return MPV_ERROR_NOT_IMPLEMENTED;

    render_swapchain_init_params *init_params =
        get_mpv_render_param(params, MPV_RENDER_PARAM_SWAPCHAIN_INIT_PARAMS, NULL);
    if (!init_params)
    {
        return MPV_ERROR_INVALID_PARAMETER;
    }
    if (!init_params->swapchain_out)
    {
        return MPV_ERROR_INVALID_PARAMETER;
    }
    p->swapchain_out = init_params->swapchain_out;
    return 0;
}

static bool check_format(struct render_backend *ctx, int imgfmt)
{
    return true;
}

static int set_parameter(struct render_backend *ctx, mpv_render_param param)
{
    struct priv *p = ctx->priv;
    assert(p != NULL);

    if (param.type != MPV_RENDER_PARAM_SWAPCHAIN_UPDATE_PARAMS)
    {
        return MPV_ERROR_INVALID_PARAMETER;
    }

    render_swapchain_update_params *update_params = param.data;
    if (!update_params)
    {
        return MPV_ERROR_INVALID_PARAMETER;
    }

    p->w = update_params->w;
    p->h = update_params->h;

    return 0;
}

static void reconfig(struct render_backend *ctx, struct mp_image_params *params)
{
}

static void reset(struct render_backend *ctx)
{
}

static void update_external(struct render_backend *ctx, struct vo *vo)
{
}

static void resize(struct render_backend *ctx, struct mp_rect *src, struct mp_rect *dst, struct mp_osd_res *osd)
{
}

static int get_target_size(struct render_backend *ctx, mpv_render_param *params, int *out_w, int *out_h)
{
    return 0;
}

static int render(struct render_backend *ctx, mpv_render_param *params, struct vo_frame *frame)
{
    return 0;
}

static void destroy(struct render_backend *ctx)
{
}

const struct render_backend_fns render_backend_swapchain = {
    .init = init,
    .check_format = check_format,
    .set_parameter = set_parameter,
    .reconfig = reconfig,
    .reset = reset,
    .update_external = update_external,
    .resize = resize,
    .get_target_size = get_target_size,
    .render = render,
    .destroy = destroy,
};

bool is_render_headless(struct ra_ctx *ctx)
{
    struct render_backend *render_ctx = get_libmpv_renderer(ctx);
    if (!render_ctx)
        return false;

    struct priv *p = render_ctx->priv;
    if (!p)
        return false;

    if (p->swapchain_out)
        return true;

    return false;
}

bool resize_update(struct ra_ctx *ctx, int *w_new, int *h_new)
{
    assert(w_new != NULL);
    assert(h_new != NULL);
    struct render_backend *render_ctx = get_libmpv_renderer(ctx);
    struct priv *p = render_ctx->priv;
    if (p && (*w_new != p->w || *h_new != p->h))
    {
        *w_new = p->w;
        *h_new = p->h;
        return true;
    }
    return false;
}

void expose_swapchain(struct ra_ctx *ctx, IDXGISwapChain *swapchain)
{
    struct render_backend *render_ctx = get_libmpv_renderer(ctx);
    struct priv *p = render_ctx->priv;
    if (!p)
        return;

    IDXGISwapChain **p_swapchain = p->swapchain_out;
    *p_swapchain = swapchain;
}

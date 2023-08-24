// SPDX-License-Identifier: GPL-2.0-only
// Copyright (c) 2023 FIXME
// Generated with linux-mdss-dsi-panel-driver-generator from vendor device tree:
//   Copyright (c) 2013, The Linux Foundation. All rights reserved. (FIXME)

#include <linux/delay.h>
#include <linux/gpio/consumer.h>
#include <linux/module.h>
#include <linux/of.h>

#include <drm/drm_mipi_dsi.h>
#include <drm/drm_modes.h>
#include <drm/drm_panel.h>

struct hx83102 {
	struct drm_panel panel;
	struct mipi_dsi_device *dsi;
	struct gpio_desc *reset_gpio;
	bool prepared;
};

static inline struct hx83102 *to_hx83102(struct drm_panel *panel)
{
	return container_of(panel, struct hx83102, panel);
}

static void hx83102_reset(struct hx83102 *ctx)
{
	dev_err(&ctx->dsi->dev, "display reset!!!\n");
	gpiod_set_value_cansleep(ctx->reset_gpio, 0);
	msleep(20);
	gpiod_set_value_cansleep(ctx->reset_gpio, 1);
	msleep(20);
	gpiod_set_value_cansleep(ctx->reset_gpio, 0);
	msleep(50);
}

static int hx83102_on(struct hx83102 *ctx)
{
	struct mipi_dsi_device *dsi = ctx->dsi;
	struct device *dev = &dsi->dev;
	int ret;

	dev_err(dev, "display on!!!\n");

	mipi_dsi_dcs_write_seq(dsi, 0xb9, 0x83, 0x10, 0x2d);
	mipi_dsi_dcs_write_seq(dsi, 0xb1,
			       0x20, 0x11, 0x21, 0x21, 0x22, 0x77, 0x2f, 0x43,
			       0x18, 0x18, 0x18);
	mipi_dsi_dcs_write_seq(dsi, 0xb2,
			       0x00, 0x00, 0x05, 0x00, 0x00, 0x0e, 0x92, 0x4d,
			       0x00, 0x00, 0x00, 0x00, 0x14, 0x20);
	mipi_dsi_dcs_write_seq(dsi, 0xb4,
			       0x14, 0x60, 0x14, 0x60, 0x14, 0x60, 0x14, 0x60,
			       0x03, 0xff, 0x01, 0x20, 0x00, 0xff);
	mipi_dsi_dcs_write_seq(dsi, 0xcc, 0x02);
	mipi_dsi_dcs_write_seq(dsi, 0xd3,
			       0x33, 0x00, 0x3c, 0x03, 0x00, 0x08, 0x00, 0x37,
			       0x00, 0x33, 0x3b, 0x0a, 0x0a, 0x00, 0x00, 0x32,
			       0x10, 0x06, 0x00, 0x06, 0x00, 0x00, 0x02, 0x00,
			       0x02, 0x00, 0x05, 0x15, 0x05, 0x15, 0x00, 0x00,
			       0x00, 0x1a, 0x00, 0x00, 0x00, 0x1a, 0x00, 0x00);
	mipi_dsi_dcs_write_seq(dsi, 0xd5,
			       0x18, 0x18, 0x18, 0x18, 0x19, 0x19, 0x39, 0x39,
			       0x24, 0x24, 0x04, 0x05, 0x06, 0x07, 0x00, 0x01,
			       0x02, 0x03, 0x18, 0x18, 0x38, 0x38, 0x20, 0x21,
			       0x22, 0x23, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
			       0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
			       0x18, 0x18, 0x18, 0x18);
	mipi_dsi_dcs_write_seq(dsi, 0xd6,
			       0x18, 0x18, 0x19, 0x19, 0x18, 0x18, 0x39, 0x39,
			       0x24, 0x24, 0x03, 0x02, 0x01, 0x00, 0x07, 0x06,
			       0x05, 0x04, 0x18, 0x18, 0x38, 0x38, 0x23, 0x22,
			       0x21, 0x20, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
			       0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
			       0x18, 0x18, 0x18, 0x18);
	mipi_dsi_dcs_write_seq(dsi, 0xe7, 0xff, 0x0f, 0x00, 0x00);
	mipi_dsi_dcs_write_seq(dsi, 0xbd, 0x01);
	mipi_dsi_dcs_write_seq(dsi, 0xe7, 0x01);
	mipi_dsi_dcs_write_seq(dsi, 0xbd, 0x00);
	mipi_dsi_dcs_write_seq(dsi, 0xe0,
			       0x00, 0x05, 0x0b, 0x0f, 0x10, 0x3c, 0x3a, 0x3e,
			       0x53, 0x49, 0x63, 0x6d, 0x73, 0x88, 0x84, 0x98,
			       0x9e, 0xbc, 0xb8, 0x5b, 0x63, 0x6e, 0x7f, 0x00,
			       0x05, 0x0b, 0x0f, 0x10, 0x3c, 0x3a, 0x3e, 0x53,
			       0x49, 0x63, 0x6d, 0x73, 0x88, 0x87, 0x98, 0x9e,
			       0xbc, 0xb8, 0x5b, 0x63, 0x6e, 0x7f);
	mipi_dsi_dcs_write_seq(dsi, 0xb0, 0x00, 0x20);
	mipi_dsi_dcs_write_seq(dsi, 0xba,
			       0x70, 0x23, 0xa8, 0x9b, 0xb2, 0x80, 0x80, 0x01,
			       0x10, 0x00, 0x00, 0x00, 0x08, 0x3d, 0x82, 0x77,
			       0x04, 0x01, 0x04);
	mipi_dsi_dcs_write_seq(dsi, 0xbd, 0x01);
	mipi_dsi_dcs_write_seq(dsi, 0xcb, 0x01);
	mipi_dsi_dcs_write_seq(dsi, 0xbd, 0x00);
	mipi_dsi_dcs_write_seq(dsi, 0xbf,
			       0xfc, 0x00, 0x25, 0x9e, 0xf6, 0x00, 0x45);
	mipi_dsi_dcs_write_seq(dsi, 0xbd, 0x02);
	mipi_dsi_dcs_write_seq(dsi, 0xb4,
			       0xc2, 0x00, 0x33, 0x00, 0x33, 0x88, 0xb3, 0x00);
	mipi_dsi_dcs_write_seq(dsi, 0xbd, 0x00);
	mipi_dsi_dcs_write_seq(dsi, 0xbd, 0x01);
	mipi_dsi_dcs_write_seq(dsi, 0xd3, 0x09, 0x00, 0x78);
	mipi_dsi_dcs_write_seq(dsi, 0xbd, 0x00);
	mipi_dsi_dcs_write_seq(dsi, 0xbd, 0x02);
	mipi_dsi_dcs_write_seq(dsi, 0xb1, 0x7f, 0x07, 0xff);
	mipi_dsi_dcs_write_seq(dsi, 0xbd, 0x00);
	mipi_dsi_dcs_write_seq(dsi, 0xbe, 0x01, 0x96);
	mipi_dsi_dcs_write_seq(dsi, 0xd9, 0x00, 0x3f, 0x3f);

	ret = mipi_dsi_dcs_set_tear_on(dsi, MIPI_DSI_DCS_TEAR_MODE_VBLANK);
	if (ret < 0) {
		dev_err(dev, "Failed to set tear on: %d\n", ret);
		return ret;
	}

	ret = mipi_dsi_dcs_exit_sleep_mode(dsi);
	if (ret < 0) {
		dev_err(dev, "Failed to exit sleep mode: %d\n", ret);
		return ret;
	}
	msleep(150);

	ret = mipi_dsi_dcs_set_display_on(dsi);
	if (ret < 0) {
		dev_err(dev, "Failed to set display on: %d\n", ret);
		return ret;
	}
	msleep(20);

	return 0;
}

static int hx83102_off(struct hx83102 *ctx)
{
	struct mipi_dsi_device *dsi = ctx->dsi;
	struct device *dev = &dsi->dev;
	int ret;

	ret = mipi_dsi_dcs_set_display_off(dsi);
	if (ret < 0) {
		dev_err(dev, "Failed to set display off: %d\n", ret);
		return ret;
	}
	msleep(50);

	ret = mipi_dsi_dcs_enter_sleep_mode(dsi);
	if (ret < 0) {
		dev_err(dev, "Failed to enter sleep mode: %d\n", ret);
		return ret;
	}
	msleep(150);

	return 0;
}

static int hx83102_prepare(struct drm_panel *panel)
{
	struct hx83102 *ctx = to_hx83102(panel);
	struct device *dev = &ctx->dsi->dev;
	int ret;

	dev_err(dev, "preparing!!!\n");

	if (ctx->prepared)
		return 0;

	hx83102_reset(ctx);

	ret = hx83102_on(ctx);
	if (ret < 0) {
		dev_err(dev, "Failed to initialize panel: %d\n", ret);
		gpiod_set_value_cansleep(ctx->reset_gpio, 1);
		return ret;
	}

	ctx->prepared = true;
	return 0;
}

static int hx83102_unprepare(struct drm_panel *panel)
{
	struct hx83102 *ctx = to_hx83102(panel);
	struct device *dev = &ctx->dsi->dev;
	int ret;

	if (!ctx->prepared)
		return 0;

	ret = hx83102_off(ctx);
	if (ret < 0)
		dev_err(dev, "Failed to un-initialize panel: %d\n", ret);

	gpiod_set_value_cansleep(ctx->reset_gpio, 1);

	ctx->prepared = false;
	return 0;
}

static const struct drm_display_mode hx83102_mode = {
	.clock = (720 + 55 + 12 + 32) * (1440 + 146 + 2 + 14) * 60 / 1000,
	.hdisplay = 720,
	.hsync_start = 720 + 55,
	.hsync_end = 720 + 55 + 12,
	.htotal = 720 + 55 + 12 + 32,
	.vdisplay = 1440,
	.vsync_start = 1440 + 146,
	.vsync_end = 1440 + 146 + 2,
	.vtotal = 1440 + 146 + 2 + 14,
	.width_mm = 68,
	.height_mm = 136,
};

static int hx83102_get_modes(struct drm_panel *panel,
			     struct drm_connector *connector)
{
	struct drm_display_mode *mode;

	mode = drm_mode_duplicate(connector->dev, &hx83102_mode);
	if (!mode)
		return -ENOMEM;

	drm_mode_set_name(mode);

	mode->type = DRM_MODE_TYPE_DRIVER | DRM_MODE_TYPE_PREFERRED;
	connector->display_info.width_mm = mode->width_mm;
	connector->display_info.height_mm = mode->height_mm;
	drm_mode_probed_add(connector, mode);

	return 1;
}

static const struct drm_panel_funcs hx83102_panel_funcs = {
	.prepare = hx83102_prepare,
	.unprepare = hx83102_unprepare,
	.get_modes = hx83102_get_modes,
};

static int hx83102_probe(struct mipi_dsi_device *dsi)
{
	struct device *dev = &dsi->dev;
	struct hx83102 *ctx;
	int ret;

	dev_err(dev, "probing!!!\n");
	
	ctx = devm_kzalloc(dev, sizeof(*ctx), GFP_KERNEL);
	if (!ctx)
		return -ENOMEM;

	dev_err(dev, "reset-gpio\n");
	ctx->reset_gpio = devm_gpiod_get(dev, "reset", GPIOD_OUT_HIGH);
	if (IS_ERR(ctx->reset_gpio))
		return dev_err_probe(dev, PTR_ERR(ctx->reset_gpio),
				     "Failed to get reset-gpios\n");

	ctx->dsi = dsi;
	mipi_dsi_set_drvdata(dsi, ctx);

	dsi->lanes = 4;
	dsi->format = MIPI_DSI_FMT_RGB888;
	dsi->mode_flags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_CLOCK_NON_CONTINUOUS |
			  MIPI_DSI_MODE_LPM;

	dev_err(dev, "drm panel init\n");
	drm_panel_init(&ctx->panel, dev, &hx83102_panel_funcs,
		       DRM_MODE_CONNECTOR_DSI);
	ctx->panel.prepare_prev_first = true;

	dev_err(dev, "drm panel add\n");
	drm_panel_add(&ctx->panel);

	dev_err(dev, "drm dsi attach\n");
	ret = mipi_dsi_attach(dsi);
	if (ret < 0) {
		dev_err(dev, "Failed to attach to DSI host: %d\n", ret);
		drm_panel_remove(&ctx->panel);
		return ret;
	}

	return 0;
}

static void hx83102_remove(struct mipi_dsi_device *dsi)
{
	struct hx83102 *ctx = mipi_dsi_get_drvdata(dsi);
	int ret;

	ret = mipi_dsi_detach(dsi);
	if (ret < 0)
		dev_err(&dsi->dev, "Failed to detach from DSI host: %d\n", ret);

	drm_panel_remove(&ctx->panel);
}

static const struct of_device_id hx83102_of_match[] = {
	{ .compatible = "himax,hx83102" },
	{ /* sentinel */ }
};
MODULE_DEVICE_TABLE(of, hx83102_of_match);

static struct mipi_dsi_driver hx83102_driver = {
	.probe = hx83102_probe,
	.remove = hx83102_remove,
	.driver = {
		.name = "panel-hx83102",
		.of_match_table = hx83102_of_match,
	},
};
module_mipi_dsi_driver(hx83102_driver);

MODULE_AUTHOR("linux-mdss-dsi-panel-driver-generator <fix@me>"); // FIXME
MODULE_DESCRIPTION("DRM driver for mdss dsi hx83102 720p video");
MODULE_LICENSE("GPL");

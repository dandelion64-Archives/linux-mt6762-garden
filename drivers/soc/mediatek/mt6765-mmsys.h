/* SPDX-License-Identifier: GPL-2.0-only */

#ifndef __SOC_MEDIATEK_MT6765_MMSYS_H
#define __SOC_MEDIATEK_MT6765_MMSYS_H

#define MT6765_DISP_MASK                    GENMASK(2, 2)

#define MT6765_DISP_OVL0_MOUT_EN            0xf3c
#define MT6765_DISP_OVL0_MOUT_RDMA0         BIT(0)
#define MT6765_DISP_OVL0_MOUT_OVL0_2L       BIT(1)
#define MT6765_DISP_OVL0_MOUT_WDMA0         BIT(2)
#define MT6765_DISP_OVL0_MOUT_RSZ0          BIT(3)

#define MT6765_DISP_PATH0_SEL_IN            0xf54
#define MT6765_DISP_PATH0_SEL_IN_OVL0       0
#define MT6765_DISP_PATH0_SEL_IN_OVL0_2L    1
#define MT6765_DISP_PATH0_SEL_IN_RSZ0       2

#define MT6765_DISP_RDMA0_RSZ0_IN_SOUT_SEL              0xf48
#define MT6765_DISP_RDMA0_RSZ0_IN_SOUT_SEL_RDMA_SOUT    0
#define MT6765_DISP_RDMA0_RSZ0_IN_SOUT_SEL_RSZ0         1

#define MT6765_DISP_RDMA0_SOUT_SEL          0xf4c
#define MT6765_DISP_RDMA0_SOUT_SEL_DSI      0
#define MT6765_DISP_RDMA0_SOUT_SEL_COLOR0   1
#define MT6765_DISP_RDMA0_SOUT_SEL_CCORR0   2

#define MT6765_DISP_DSI0_SEL_IN             0xf68
#define MT6765_DISP_DSI0_SEL_IN_RDMA0       0
#define MT6765_DISP_DSI0_SEL_IN_DITHER0     1

#define MT6765_MMSYS_SW0_RST_B              0x140
#define MT6765_MMSYS_LCM_RST_B              0x150

/*
 * Minimal routing table for MT6765:
 * OVL0 -> RDMA0 -> DSI0
 */
static const struct mtk_mmsys_routes mt6765_mmsys_routing_table[] = {
    /* OVL0 -> RDMA0 (through PATH0) */
    {
        .from_comp = DDP_COMPONENT_OVL0,
        .to_comp = DDP_COMPONENT_RDMA0,
        .addr = MT6765_DISP_OVL0_MOUT_EN,
        .mask = MT6765_DISP_MASK,
        .val = MT6765_DISP_OVL0_MOUT_RDMA0,
    }, {
        .from_comp = DDP_COMPONENT_OVL0,
        .to_comp = DDP_COMPONENT_RDMA0,
        .addr = MT6765_DISP_PATH0_SEL_IN,
        .mask = MT6765_DISP_MASK,
        .val = MT6765_DISP_PATH0_SEL_IN_OVL0,
    },
    /* RDMA0 -> DSI0 */
    {
        .from_comp = DDP_COMPONENT_RDMA0,
        .to_comp = DDP_COMPONENT_DSI0,
        .addr = MT6765_DISP_RDMA0_RSZ0_IN_SOUT_SEL,
        .mask = MT6765_DISP_MASK,
        .val = MT6765_DISP_RDMA0_RSZ0_IN_SOUT_SEL_RDMA_SOUT,
    }, {
        .from_comp = DDP_COMPONENT_RDMA0,
        .to_comp = DDP_COMPONENT_DSI0,
        .addr = MT6765_DISP_RDMA0_SOUT_SEL,
        .mask = MT6765_DISP_MASK,
        .val = MT6765_DISP_RDMA0_SOUT_SEL_DSI,
    }, {
        .from_comp = DDP_COMPONENT_RDMA0,
        .to_comp = DDP_COMPONENT_DSI0,
        .addr = MT6765_DISP_DSI0_SEL_IN,
        .mask = MT6765_DISP_MASK,
        .val = MT6765_DISP_DSI0_SEL_IN_RDMA0,
    },
};

#endif /* __SOC_MEDIATEK_MT6765_MMSYS_H */

/*
 * Copyright (c) 2015-2019, Renesas Electronics Corporation
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdint.h>		/* for uint32_t */
#include <lib/mmio.h>
#include "pfc_init_v3m.h"
#include "include/rcar_def.h"
#include "rcar_private.h"
#include "../pfc_regs.h"

/* Pin function bit */
#define GPSR0_DU_EXODDF_DU_ODDF_DISP_CDE	BIT(21)
#define GPSR0_DU_EXVSYNC_DU_VSYNC		BIT(20)
#define GPSR0_DU_EXHSYNC_DU_HSYNC		BIT(19)
#define GPSR0_DU_DOTCLKOUT			BIT(18)
#define GPSR0_DU_DB7				BIT(17)
#define GPSR0_DU_DB6				BIT(16)
#define GPSR0_DU_DB5				BIT(15)
#define GPSR0_DU_DB4				BIT(14)
#define GPSR0_DU_DB3				BIT(13)
#define GPSR0_DU_DB2				BIT(12)
#define GPSR0_DU_DG7				BIT(11)
#define GPSR0_DU_DG6				BIT(10)
#define GPSR0_DU_DG5				BIT(9)
#define GPSR0_DU_DG4				BIT(8)
#define GPSR0_DU_DG3				BIT(7)
#define GPSR0_DU_DG2				BIT(6)
#define GPSR0_DU_DR7				BIT(5)
#define GPSR0_DU_DR6				BIT(4)
#define GPSR0_DU_DR5				BIT(3)
#define GPSR0_DU_DR4				BIT(2)
#define GPSR0_DU_DR3				BIT(1)
#define GPSR0_DU_DR2				BIT(0)

#define GPSR1_DIGRF_CLKOUT			BIT(27)
#define GPSR1_DIGRF_CLKIN			BIT(26)
#define GPSR1_CANFD_CLK				BIT(25)
#define GPSR1_CANFD1_RX				BIT(24)
#define GPSR1_CANFD1_TX				BIT(23)
#define GPSR1_CANFD0_RX				BIT(22)
#define GPSR1_CANFD0_TX				BIT(21)
#define GPSR1_AVB0_AVTP_CAPTURE			BIT(20)
#define GPSR1_AVB0_AVTP_MATCH			BIT(19)
#define GPSR1_AVB0_LINK				BIT(18)
#define GPSR1_AVB0_PHY_INT			BIT(17)
#define GPSR1_AVB0_MAGIC			BIT(16)
#define GPSR1_AVB0_MDC				BIT(15)
#define GPSR1_AVB0_MDIO				BIT(14)
#define GPSR1_AVB0_TXCREFCLK			BIT(13)
#define GPSR1_AVB0_TD3				BIT(12)
#define GPSR1_AVB0_TD2				BIT(11)
#define GPSR1_AVB0_TD1				BIT(10)
#define GPSR1_AVB0_TD0				BIT(9)
#define GPSR1_AVB0_TXC				BIT(8)
#define GPSR1_AVB0_TX_CTL			BIT(7)
#define GPSR1_AVB0_RD3				BIT(6)
#define GPSR1_AVB0_RD2				BIT(5)
#define GPSR1_AVB0_RD1				BIT(4)
#define GPSR1_AVB0_RD0				BIT(3)
#define GPSR1_AVB0_RXC				BIT(2)
#define GPSR1_AVB0_RX_CTL			BIT(1)
#define GPSR1_IRQ0				BIT(0)

#define GPSR2_VI0_FIELD				BIT(16)
#define GPSR2_VI0_DATA11			BIT(15)
#define GPSR2_VI0_DATA10			BIT(14)
#define GPSR2_VI0_DATA9				BIT(13)
#define GPSR2_VI0_DATA8				BIT(12)
#define GPSR2_VI0_DATA7				BIT(11)
#define GPSR2_VI0_DATA6				BIT(10)
#define GPSR2_VI0_DATA5				BIT(9)
#define GPSR2_VI0_DATA4				BIT(8)
#define GPSR2_VI0_DATA3				BIT(7)
#define GPSR2_VI0_DATA2				BIT(6)
#define GPSR2_VI0_DATA1				BIT(5)
#define GPSR2_VI0_DATA0				BIT(4)
#define GPSR2_VI0_VSYNC_N			BIT(3)
#define GPSR2_VI0_HSYNC_N			BIT(2)
#define GPSR2_VI0_CLKENB			BIT(1)
#define GPSR2_VI0_CLK				BIT(0)

#define GPSR3_VI1_FIELD				BIT(16)
#define GPSR3_VI1_DATA11			BIT(15)
#define GPSR3_VI1_DATA10			BIT(14)
#define GPSR3_VI1_DATA9				BIT(13)
#define GPSR3_VI1_DATA8				BIT(12)
#define GPSR3_VI1_DATA7				BIT(11)
#define GPSR3_VI1_DATA6				BIT(10)
#define GPSR3_VI1_DATA5				BIT(9)
#define GPSR3_VI1_DATA4				BIT(8)
#define GPSR3_VI1_DATA3				BIT(7)
#define GPSR3_VI1_DATA2				BIT(6)
#define GPSR3_VI1_DATA1				BIT(5)
#define GPSR3_VI1_DATA0				BIT(4)
#define GPSR3_VI1_VSYNC_N			BIT(3)
#define GPSR3_VI1_HSYNC_N			BIT(2)
#define GPSR3_VI1_CLKENB			BIT(1)
#define GPSR3_VI1_CLK				BIT(0)

#define GPSR4_SDA2				BIT(5)
#define GPSR4_SCL2				BIT(4)
#define GPSR4_SDA1				BIT(3)
#define GPSR4_SCL1				BIT(2)
#define GPSR4_SDA0				BIT(1)
#define GPSR4_SCL0				BIT(0)

#define GPSR5_RPC_INT_N				BIT(14)
#define GPSR5_RPC_WP_N				BIT(13)
#define GPSR5_RPC_RESET_N			BIT(12)
#define GPSR5_QSPI1_SSL				BIT(11)
#define GPSR5_QSPI1_IO3				BIT(10)
#define GPSR5_QSPI1_IO2				BIT(9)
#define GPSR5_QSPI1_MISO_IO1			BIT(8)
#define GPSR5_QSPI1_MOSI_IO0			BIT(7)
#define GPSR5_QSPI1_SPCLK			BIT(6)
#define GPSR5_QSPI0_SSL				BIT(5)
#define GPSR5_QSPI0_IO3				BIT(4)
#define GPSR5_QSPI0_IO2				BIT(3)
#define GPSR5_QSPI0_MISO_IO1			BIT(2)
#define GPSR5_QSPI0_MOSI_IO0			BIT(1)
#define GPSR5_QSPI0_SPCLK			BIT(0)

#define IPSR_28_FUNC(x)				((uint32_t)(x) << 28U)
#define IPSR_24_FUNC(x)				((uint32_t)(x) << 24U)
#define IPSR_20_FUNC(x)				((uint32_t)(x) << 20U)
#define IPSR_16_FUNC(x)				((uint32_t)(x) << 16U)
#define IPSR_12_FUNC(x)				((uint32_t)(x) << 12U)
#define IPSR_8_FUNC(x)				((uint32_t)(x) << 8U)
#define IPSR_4_FUNC(x)				((uint32_t)(x) << 4U)
#define IPSR_0_FUNC(x)				((uint32_t)(x) << 0U)

#define IOCTRL30_POC_VI0_DATA5			BIT(31)
#define IOCTRL30_POC_VI0_DATA4			BIT(30)
#define IOCTRL30_POC_VI0_DATA3			BIT(29)
#define IOCTRL30_POC_VI0_DATA2			BIT(28)
#define IOCTRL30_POC_VI0_DATA1			BIT(27)
#define IOCTRL30_POC_VI0_DATA0			BIT(26)
#define IOCTRL30_POC_VI0_VSYNC_N		BIT(25)
#define IOCTRL30_POC_VI0_HSYNC_N		BIT(24)
#define IOCTRL30_POC_VI0_CLKENB			BIT(23)
#define IOCTRL30_POC_VI0_CLK			BIT(22)
#define IOCTRL30_POC_DU_EXODDF_DU_ODDF_DISP_CDE	BIT(21)
#define IOCTRL30_POC_DU_EXVSYNC_DU_VSYNC	BIT(20)
#define IOCTRL30_POC_DU_EXHSYNC_DU_HSYNC	BIT(19)
#define IOCTRL30_POC_DU_DOTCLKOUT		BIT(18)
#define IOCTRL30_POC_DU_DB7			BIT(17)
#define IOCTRL30_POC_DU_DB6			BIT(16)
#define IOCTRL30_POC_DU_DB5			BIT(15)
#define IOCTRL30_POC_DU_DB4			BIT(14)
#define IOCTRL30_POC_DU_DB3			BIT(13)
#define IOCTRL30_POC_DU_DB2			BIT(12)
#define IOCTRL30_POC_DU_DG7			BIT(11)
#define IOCTRL30_POC_DU_DG6			BIT(10)
#define IOCTRL30_POC_DU_DG5			BIT(9)
#define IOCTRL30_POC_DU_DG4			BIT(8)
#define IOCTRL30_POC_DU_DG3			BIT(7)
#define IOCTRL30_POC_DU_DG2			BIT(6)
#define IOCTRL30_POC_DU_DR7			BIT(5)
#define IOCTRL30_POC_DU_DR6			BIT(4)
#define IOCTRL30_POC_DU_DR5			BIT(3)
#define IOCTRL30_POC_DU_DR4			BIT(2)
#define IOCTRL30_POC_DU_DR3			BIT(1)
#define IOCTRL30_POC_DU_DR2			BIT(0)

#define IOCTRL31_POC_DUMMY_31			BIT(31)
#define IOCTRL31_POC_DUMMY_30			BIT(30)
#define IOCTRL31_POC_DUMMY_29			BIT(29)
#define IOCTRL31_POC_DUMMY_28			BIT(28)
#define IOCTRL31_POC_DUMMY_27			BIT(27)
#define IOCTRL31_POC_DUMMY_26			BIT(26)
#define IOCTRL31_POC_DUMMY_25			BIT(25)
#define IOCTRL31_POC_DUMMY_24			BIT(24)
#define IOCTRL31_POC_VI1_FIELD			BIT(23)
#define IOCTRL31_POC_VI1_DATA11			BIT(22)
#define IOCTRL31_POC_VI1_DATA10			BIT(21)
#define IOCTRL31_POC_VI1_DATA9			BIT(20)
#define IOCTRL31_POC_VI1_DATA8			BIT(19)
#define IOCTRL31_POC_VI1_DATA7			BIT(18)
#define IOCTRL31_POC_VI1_DATA6			BIT(17)
#define IOCTRL31_POC_VI1_DATA5			BIT(16)
#define IOCTRL31_POC_VI1_DATA4			BIT(15)
#define IOCTRL31_POC_VI1_DATA3			BIT(14)
#define IOCTRL31_POC_VI1_DATA2			BIT(13)
#define IOCTRL31_POC_VI1_DATA1			BIT(12)
#define IOCTRL31_POC_VI1_DATA0			BIT(11)
#define IOCTRL31_POC_VI1_VSYNC_N		BIT(10)
#define IOCTRL31_POC_VI1_HSYNC_N		BIT(9)
#define IOCTRL31_POC_VI1_CLKENB			BIT(8)
#define IOCTRL31_POC_VI1_CLK			BIT(7)
#define IOCTRL31_POC_VI0_FIELD			BIT(6)
#define IOCTRL31_POC_VI0_DATA11			BIT(5)
#define IOCTRL31_POC_VI0_DATA10			BIT(4)
#define IOCTRL31_POC_VI0_DATA9			BIT(3)
#define IOCTRL31_POC_VI0_DATA8			BIT(2)
#define IOCTRL31_POC_VI0_DATA7			BIT(1)
#define IOCTRL31_POC_VI0_DATA6			BIT(0)
#define IOCTRL32_POC2_VREF			BIT(0)
#define IOCTRL40_SD0TDSEL1			BIT(1)
#define IOCTRL40_SD0TDSEL0			BIT(0)

#define PUEN0_PUEN_VI0_CLK			BIT(31)
#define PUEN0_PUEN_TDI				BIT(30)
#define PUEN0_PUEN_TMS				BIT(29)
#define PUEN0_PUEN_TCK				BIT(28)
#define PUEN0_PUEN_TRST_N			BIT(27)
#define PUEN0_PUEN_IRQ0				BIT(26)
#define PUEN0_PUEN_FSCLKST_N			BIT(25)
#define PUEN0_PUEN_EXTALR			BIT(24)
#define PUEN0_PUEN_PRESETOUT_N			BIT(23)
#define PUEN0_PUEN_DU_DOTCLKIN			BIT(22)
#define PUEN0_PUEN_DU_EXODDF_DU_ODDF_DISP_CDE	BIT(21)
#define PUEN0_PUEN_DU_EXVSYNC_DU_VSYNC		BIT(20)
#define PUEN0_PUEN_DU_EXHSYNC_DU_HSYNC		BIT(19)
#define PUEN0_PUEN_DU_DOTCLKOUT			BIT(18)
#define PUEN0_PUEN_DU_DB7			BIT(17)
#define PUEN0_PUEN_DU_DB6			BIT(16)
#define PUEN0_PUEN_DU_DB5			BIT(15)
#define PUEN0_PUEN_DU_DB4			BIT(14)
#define PUEN0_PUEN_DU_DB3			BIT(13)
#define PUEN0_PUEN_DU_DB2			BIT(12)
#define PUEN0_PUEN_DU_DG7			BIT(11)
#define PUEN0_PUEN_DU_DG6			BIT(10)
#define PUEN0_PUEN_DU_DG5			BIT(9)
#define PUEN0_PUEN_DU_DG4			BIT(8)
#define PUEN0_PUEN_DU_DG3			BIT(7)
#define PUEN0_PUEN_DU_DG2			BIT(6)
#define PUEN0_PUEN_DU_DR7			BIT(5)
#define PUEN0_PUEN_DU_DR6			BIT(4)
#define PUEN0_PUEN_DU_DR5			BIT(3)
#define PUEN0_PUEN_DU_DR4			BIT(2)
#define PUEN0_PUEN_DU_DR3			BIT(1)
#define PUEN0_PUEN_DU_DR2			BIT(0)

#define PUEN1_PUEN_VI1_DATA11			BIT(31)
#define PUEN1_PUEN_VI1_DATA10			BIT(30)
#define PUEN1_PUEN_VI1_DATA9			BIT(29)
#define PUEN1_PUEN_VI1_DATA8			BIT(28)
#define PUEN1_PUEN_VI1_DATA7			BIT(27)
#define PUEN1_PUEN_VI1_DATA6			BIT(26)
#define PUEN1_PUEN_VI1_DATA5			BIT(25)
#define PUEN1_PUEN_VI1_DATA4			BIT(24)
#define PUEN1_PUEN_VI1_DATA3			BIT(23)
#define PUEN1_PUEN_VI1_DATA2			BIT(22)
#define PUEN1_PUEN_VI1_DATA1			BIT(21)
#define PUEN1_PUEN_VI1_DATA0			BIT(20)
#define PUEN1_PUEN_VI1_VSYNC_N			BIT(19)
#define PUEN1_PUEN_VI1_HSYNC_N			BIT(18)
#define PUEN1_PUEN_VI1_CLKENB			BIT(17)
#define PUEN1_PUEN_VI1_CLK			BIT(16)
#define PUEN1_PUEN_VI0_FIELD			BIT(15)
#define PUEN1_PUEN_VI0_DATA11			BIT(14)
#define PUEN1_PUEN_VI0_DATA10			BIT(13)
#define PUEN1_PUEN_VI0_DATA9			BIT(12)
#define PUEN1_PUEN_VI0_DATA8			BIT(11)
#define PUEN1_PUEN_VI0_DATA7			BIT(10)
#define PUEN1_PUEN_VI0_DATA6			BIT(9)
#define PUEN1_PUEN_VI0_DATA5			BIT(8)
#define PUEN1_PUEN_VI0_DATA4			BIT(7)
#define PUEN1_PUEN_VI0_DATA3			BIT(6)
#define PUEN1_PUEN_VI0_DATA2			BIT(5)
#define PUEN1_PUEN_VI0_DATA1			BIT(4)
#define PUEN1_PUEN_VI0_DATA0			BIT(3)
#define PUEN1_PUEN_VI0_VSYNC_N			BIT(2)
#define PUEN1_PUEN_VI0_HSYNC_N			BIT(1)
#define PUEN1_PUEN_VI0_CLKENB			BIT(0)

#define PUEN2_PUEN_CANFD_CLK			BIT(31)
#define PUEN2_PUEN_CANFD1_RX			BIT(30)
#define PUEN2_PUEN_CANFD1_TX			BIT(29)
#define PUEN2_PUEN_CANFD0_RX			BIT(28)
#define PUEN2_PUEN_CANFD0_TX			BIT(27)
#define PUEN2_PUEN_AVB0_AVTP_CAPTURE		BIT(26)
#define PUEN2_PUEN_AVB0_AVTP_MATCH		BIT(25)
#define PUEN2_PUEN_AVB0_LINK			BIT(24)
#define PUEN2_PUEN_AVB0_PHY_INT			BIT(23)
#define PUEN2_PUEN_AVB0_MAGIC			BIT(22)
#define PUEN2_PUEN_AVB0_MDC			BIT(21)
#define PUEN2_PUEN_AVB0_MDIO			BIT(20)
#define PUEN2_PUEN_AVB0_TXCREFCLK		BIT(19)
#define PUEN2_PUEN_AVB0_TD3			BIT(18)
#define PUEN2_PUEN_AVB0_TD2			BIT(17)
#define PUEN2_PUEN_AVB0_TD1			BIT(16)
#define PUEN2_PUEN_AVB0_TD0			BIT(15)
#define PUEN2_PUEN_AVB0_TXC			BIT(14)
#define PUEN2_PUEN_AVB0_TX_CTL			BIT(13)
#define PUEN2_PUEN_AVB0_RD3			BIT(12)
#define PUEN2_PUEN_AVB0_RD2			BIT(11)
#define PUEN2_PUEN_AVB0_RD1			BIT(10)
#define PUEN2_PUEN_AVB0_RD0			BIT(9)
#define PUEN2_PUEN_AVB0_RXC			BIT(8)
#define PUEN2_PUEN_AVB0_RX_CTL			BIT(7)
#define PUEN2_PUEN_SDA2				BIT(6)
#define PUEN2_PUEN_SCL2				BIT(5)
#define PUEN2_PUEN_SDA1				BIT(4)
#define PUEN2_PUEN_SCL1				BIT(3)
#define PUEN2_PUEN_SDA0				BIT(2)
#define PUEN2_PUEN_SCL0				BIT(1)
#define PUEN2_PUEN_VI1_FIELD			BIT(0)

#define PUEN3_PUEN_DIGRF_CLKOUT			BIT(16)
#define PUEN3_PUEN_DIGRF_CLKIN			BIT(15)
#define PUEN3_PUEN_RPC_INT_N			BIT(14)
#define PUEN3_PUEN_RPC_WP_N			BIT(13)
#define PUEN3_PUEN_RPC_RESET_N			BIT(12)
#define PUEN3_PUEN_QSPI1_SSL			BIT(11)
#define PUEN3_PUEN_QSPI1_IO3			BIT(10)
#define PUEN3_PUEN_QSPI1_IO2			BIT(9)
#define PUEN3_PUEN_QSPI1_MISO_IO1		BIT(8)
#define PUEN3_PUEN_QSPI1_MOSI_IO0		BIT(7)
#define PUEN3_PUEN_QSPI1_SPCLK			BIT(6)
#define PUEN3_PUEN_QSPI0_SSL			BIT(5)
#define PUEN3_PUEN_QSPI0_IO3			BIT(4)
#define PUEN3_PUEN_QSPI0_IO2			BIT(3)
#define PUEN3_PUEN_QSPI0_MISO_IO1		BIT(2)
#define PUEN3_PUEN_QSPI0_MOSI_IO0		BIT(1)
#define PUEN3_PUEN_QSPI0_SPCLK			BIT(0)

#define PUD0_PUD_VI0_CLK			BIT(31)
#define PUD0_PUD_IRQ0				BIT(26)
#define PUD0_PUD_FSCLKST_N			BIT(25)
#define PUD0_PUD_PRESETOUT_N			BIT(23)
#define PUD0_PUD_DU_EXODDF_DU_ODDF_DISP_CDE	BIT(21)
#define PUD0_PUD_DU_EXVSYNC_DU_VSYNC		BIT(20)
#define PUD0_PUD_DU_EXHSYNC_DU_HSYNC		BIT(19)
#define PUD0_PUD_DU_DOTCLKOUT			BIT(18)
#define PUD0_PUD_DU_DB7				BIT(17)
#define PUD0_PUD_DU_DB6				BIT(16)
#define PUD0_PUD_DU_DB5				BIT(15)
#define PUD0_PUD_DU_DB4				BIT(14)
#define PUD0_PUD_DU_DB3				BIT(13)
#define PUD0_PUD_DU_DB2				BIT(12)
#define PUD0_PUD_DU_DG7				BIT(11)
#define PUD0_PUD_DU_DG6				BIT(10)
#define PUD0_PUD_DU_DG5				BIT(9)
#define PUD0_PUD_DU_DG4				BIT(8)
#define PUD0_PUD_DU_DG3				BIT(7)
#define PUD0_PUD_DU_DG2				BIT(6)
#define PUD0_PUD_DU_DR7				BIT(5)
#define PUD0_PUD_DU_DR6				BIT(4)
#define PUD0_PUD_DU_DR5				BIT(3)
#define PUD0_PUD_DU_DR4				BIT(2)
#define PUD0_PUD_DU_DR3				BIT(1)
#define PUD0_PUD_DU_DR2				BIT(0)

#define PUD1_PUD_VI1_DATA11			BIT(31)
#define PUD1_PUD_VI1_DATA10			BIT(30)
#define PUD1_PUD_VI1_DATA9			BIT(29)
#define PUD1_PUD_VI1_DATA8			BIT(28)
#define PUD1_PUD_VI1_DATA7			BIT(27)
#define PUD1_PUD_VI1_DATA6			BIT(26)
#define PUD1_PUD_VI1_DATA5			BIT(25)
#define PUD1_PUD_VI1_DATA4			BIT(24)
#define PUD1_PUD_VI1_DATA3			BIT(23)
#define PUD1_PUD_VI1_DATA2			BIT(22)
#define PUD1_PUD_VI1_DATA1			BIT(21)
#define PUD1_PUD_VI1_DATA0			BIT(20)
#define PUD1_PUD_VI1_VSYNC_N			BIT(19)
#define PUD1_PUD_VI1_HSYNC_N			BIT(18)
#define PUD1_PUD_VI1_CLKENB			BIT(17)
#define PUD1_PUD_VI1_CLK			BIT(16)
#define PUD1_PUD_VI0_FIELD			BIT(15)
#define PUD1_PUD_VI0_DATA11			BIT(14)
#define PUD1_PUD_VI0_DATA10			BIT(13)
#define PUD1_PUD_VI0_DATA9			BIT(12)
#define PUD1_PUD_VI0_DATA8			BIT(11)
#define PUD1_PUD_VI0_DATA7			BIT(10)
#define PUD1_PUD_VI0_DATA6			BIT(9)
#define PUD1_PUD_VI0_DATA5			BIT(8)
#define PUD1_PUD_VI0_DATA4			BIT(7)
#define PUD1_PUD_VI0_DATA3			BIT(6)
#define PUD1_PUD_VI0_DATA2			BIT(5)
#define PUD1_PUD_VI0_DATA1			BIT(4)
#define PUD1_PUD_VI0_DATA0			BIT(3)
#define PUD1_PUD_VI0_VSYNC_N			BIT(2)
#define PUD1_PUD_VI0_HSYNC_N			BIT(1)
#define PUD1_PUD_VI0_CLKENB			BIT(0)

#define PUD2_PUD_CANFD_CLK			BIT(31)
#define PUD2_PUD_CANFD1_RX			BIT(30)
#define PUD2_PUD_CANFD1_TX			BIT(29)
#define PUD2_PUD_CANFD0_RX			BIT(28)
#define PUD2_PUD_CANFD0_TX			BIT(27)
#define PUD2_PUD_AVB0_AVTP_CAPTURE		BIT(26)
#define PUD2_PUD_AVB0_AVTP_MATCH		BIT(25)
#define PUD2_PUD_AVB0_LINK			BIT(24)
#define PUD2_PUD_AVB0_PHY_INT			BIT(23)
#define PUD2_PUD_AVB0_MAGIC			BIT(22)
#define PUD2_PUD_AVB0_MDC			BIT(21)
#define PUD2_PUD_AVB0_MDIO			BIT(20)
#define PUD2_PUD_AVB0_TXCREFCLK			BIT(19)
#define PUD2_PUD_AVB0_TD3			BIT(18)
#define PUD2_PUD_AVB0_TD2			BIT(17)
#define PUD2_PUD_AVB0_TD1			BIT(16)
#define PUD2_PUD_AVB0_TD0			BIT(15)
#define PUD2_PUD_AVB0_TXC			BIT(14)
#define PUD2_PUD_AVB0_TX_CTL			BIT(13)
#define PUD2_PUD_AVB0_RD3			BIT(12)
#define PUD2_PUD_AVB0_RD2			BIT(11)
#define PUD2_PUD_AVB0_RD1			BIT(10)
#define PUD2_PUD_AVB0_RD0			BIT(9)
#define PUD2_PUD_AVB0_RXC			BIT(8)
#define PUD2_PUD_AVB0_RX_CTL			BIT(7)
#define PUD2_PUD_SDA2				BIT(6)
#define PUD2_PUD_SCL2				BIT(5)
#define PUD2_PUD_SDA1				BIT(4)
#define PUD2_PUD_SCL1				BIT(3)
#define PUD2_PUD_SDA0				BIT(2)
#define PUD2_PUD_SCL0				BIT(1)
#define PUD2_PUD_VI1_FIELD			BIT(0)

#define PUD3_PUD_DIGRF_CLKOUT			BIT(16)
#define PUD3_PUD_DIGRF_CLKIN			BIT(15)
#define PUD3_PUD_RPC_INT_N			BIT(14)
#define PUD3_PUD_RPC_WP_N			BIT(13)
#define PUD3_PUD_RPC_RESET_N			BIT(12)
#define PUD3_PUD_QSPI1_SSL			BIT(11)
#define PUD3_PUD_QSPI1_IO3			BIT(10)
#define PUD3_PUD_QSPI1_IO2			BIT(9)
#define PUD3_PUD_QSPI1_MISO_IO1			BIT(8)
#define PUD3_PUD_QSPI1_MOSI_IO0			BIT(7)
#define PUD3_PUD_QSPI1_SPCLK			BIT(6)
#define PUD3_PUD_QSPI0_SSL			BIT(5)
#define PUD3_PUD_QSPI0_IO3			BIT(4)
#define PUD3_PUD_QSPI0_IO2			BIT(3)
#define PUD3_PUD_QSPI0_MISO_IO1			BIT(2)
#define PUD3_PUD_QSPI0_MOSI_IO0			BIT(1)
#define PUD3_PUD_QSPI0_SPCLK			BIT(0)

#define MOD_SEL0_sel_hscif0			BIT(10)
#define MOD_SEL0_sel_scif1			BIT(9)
#define MOD_SEL0_sel_canfd0			BIT(8)
#define MOD_SEL0_sel_pwm4			BIT(7)
#define MOD_SEL0_sel_pwm3			BIT(6)
#define MOD_SEL0_sel_pwm2			BIT(5)
#define MOD_SEL0_sel_pwm1			BIT(4)
#define MOD_SEL0_sel_pwm0			BIT(3)
#define MOD_SEL0_sel_rfso			BIT(2)
#define MOD_SEL0_sel_rsp			BIT(1)
#define MOD_SEL0_sel_tmu			BIT(0)

/* SCIF3 Registers for Dummy write */
#define SCIF3_BASE		(0xE6C50000U)
#define SCIF3_SCFCR		(SCIF3_BASE + 0x0018U)
#define SCIF3_SCFDR		(SCIF3_BASE + 0x001CU)
#define SCFCR_DATA		(0x0000U)

/* Realtime module stop control */
#define CPG_BASE		(0xE6150000U)
#define CPG_MSTPSR0		(CPG_BASE + 0x0030U)
#define CPG_RMSTPCR0		(CPG_BASE + 0x0110U)
#define RMSTPCR0_RTDMAC		(0x00200000U)

/* RT-DMAC Registers */
#define RTDMAC_CH		(0U)		/* choose 0 to 15 */

#define RTDMAC_BASE		(0xFFC10000U)
#define RTDMAC_RDMOR		(RTDMAC_BASE + 0x0060U)
#define RTDMAC_RDMCHCLR		(RTDMAC_BASE + 0x0080U)
#define RTDMAC_RDMSAR(x)	(RTDMAC_BASE + 0x8000U + (0x80U * (x)))
#define RTDMAC_RDMDAR(x)	(RTDMAC_BASE + 0x8004U + (0x80U * (x)))
#define RTDMAC_RDMTCR(x)	(RTDMAC_BASE + 0x8008U + (0x80U * (x)))
#define RTDMAC_RDMCHCR(x)	(RTDMAC_BASE + 0x800CU + (0x80U * (x)))
#define RTDMAC_RDMCHCRB(x)	(RTDMAC_BASE + 0x801CU + (0x80U * (x)))
#define RTDMAC_RDMDPBASE(x)	(RTDMAC_BASE + 0x8050U + (0x80U * (x)))
#define RTDMAC_DESC_BASE	(RTDMAC_BASE + 0xA000U)
#define RTDMAC_DESC_RDMSAR	(RTDMAC_DESC_BASE + 0x0000U)
#define RTDMAC_DESC_RDMDAR	(RTDMAC_DESC_BASE + 0x0004U)
#define RTDMAC_DESC_RDMTCR	(RTDMAC_DESC_BASE + 0x0008U)

#define RDMOR_DME		(0x0001U)	/* DMA Master Enable */
#define RDMCHCR_DPM_INFINITE	(0x30000000U)	/* Infinite repeat mode */
#define RDMCHCR_RPT_TCR		(0x02000000U)	/* enable to update TCR */
#define RDMCHCR_TS_2		(0x00000008U)	/* Word(2byte) units transfer */
#define RDMCHCR_RS_AUTO		(0x00000400U)	/* Auto request */
#define RDMCHCR_DE		(0x00000001U)	/* DMA Enable */
#define RDMCHCRB_DRST		(0x00008000U)	/* Descriptor reset */
#define RDMCHCRB_SLM_256	(0x00000080U)	/* once in 256 clock cycle */
#define RDMDPBASE_SEL_EXT	(0x00000001U)	/* External memory use */

static void pfc_reg_write(uint32_t addr, uint32_t data)
{
	mmio_write_32(PFC_PMMR, ~data);
	mmio_write_32((uintptr_t)addr, data);
}

static void start_rtdma0_descriptor(void)
{
	uint32_t reg;

	/* Module stop clear */
	while ((mmio_read_32(CPG_MSTPSR0) & RMSTPCR0_RTDMAC) != 0U) {
		reg = mmio_read_32(CPG_RMSTPCR0);
		reg &= ~RMSTPCR0_RTDMAC;
		cpg_write(CPG_RMSTPCR0, reg);
	}

	/* Initialize ch0, Reset Descriptor */
	mmio_write_32(RTDMAC_RDMCHCLR, BIT(RTDMAC_CH));
	mmio_write_32(RTDMAC_RDMCHCRB(RTDMAC_CH), RDMCHCRB_DRST);

	/* Enable DMA */
	mmio_write_16(RTDMAC_RDMOR, RDMOR_DME);

	/* Set first transfer */
	mmio_write_32(RTDMAC_RDMSAR(RTDMAC_CH), RCAR_PRR);
	mmio_write_32(RTDMAC_RDMDAR(RTDMAC_CH), SCIF3_SCFDR);
	mmio_write_32(RTDMAC_RDMTCR(RTDMAC_CH), 0x00000001U);

	/* Set descriptor */
	mmio_write_32(RTDMAC_DESC_RDMSAR, 0x00000000U);
	mmio_write_32(RTDMAC_DESC_RDMDAR, 0x00000000U);
	mmio_write_32(RTDMAC_DESC_RDMTCR, 0x00200000U);
	mmio_write_32(RTDMAC_RDMCHCRB(RTDMAC_CH), RDMCHCRB_SLM_256);
	mmio_write_32(RTDMAC_RDMDPBASE(RTDMAC_CH), RTDMAC_DESC_BASE
						 | RDMDPBASE_SEL_EXT);

	/* Set transfer parameter, Start transfer */
	mmio_write_32(RTDMAC_RDMCHCR(RTDMAC_CH), RDMCHCR_DPM_INFINITE
					       | RDMCHCR_RPT_TCR
					       | RDMCHCR_TS_2
					       | RDMCHCR_RS_AUTO
					       | RDMCHCR_DE);
}

void pfc_init_v3m(void)
{
	/* Work around for PFC eratta */
	start_rtdma0_descriptor();

	// pin function
	// md[4:1]!=0000
	/* initialize GPIO/perihperal function select */

	pfc_reg_write(PFC_GPSR0, 0x00000000);

	pfc_reg_write(PFC_GPSR1, GPSR1_CANFD_CLK);

	pfc_reg_write(PFC_GPSR2, 0x00000000);

	pfc_reg_write(PFC_GPSR3, 0x00000000);

	pfc_reg_write(PFC_GPSR4, GPSR4_SDA2
				   | GPSR4_SCL2);

	pfc_reg_write(PFC_GPSR5, GPSR5_QSPI1_SSL
				   | GPSR5_QSPI1_IO3
				   | GPSR5_QSPI1_IO2
				   | GPSR5_QSPI1_MISO_IO1
				   | GPSR5_QSPI1_MOSI_IO0
				   | GPSR5_QSPI1_SPCLK
				   | GPSR5_QSPI0_SSL
				   | GPSR5_QSPI0_IO3
				   | GPSR5_QSPI0_IO2
				   | GPSR5_QSPI0_MISO_IO1
				   | GPSR5_QSPI0_MOSI_IO0
				   | GPSR5_QSPI0_SPCLK);

	/* initialize peripheral function select */
	pfc_reg_write(PFC_IPSR0, IPSR_28_FUNC(0)
				   | IPSR_24_FUNC(0)
				   | IPSR_20_FUNC(0)
				   | IPSR_16_FUNC(0)
				   | IPSR_12_FUNC(0)
				   | IPSR_8_FUNC(0)
				   | IPSR_4_FUNC(0)
				   | IPSR_0_FUNC(0));

	pfc_reg_write(PFC_IPSR1, IPSR_28_FUNC(0)
				   | IPSR_24_FUNC(0)
				   | IPSR_20_FUNC(0)
				   | IPSR_16_FUNC(0)
				   | IPSR_12_FUNC(0)
				   | IPSR_8_FUNC(0)
				   | IPSR_4_FUNC(0)
				   | IPSR_0_FUNC(0));

	pfc_reg_write(PFC_IPSR2, IPSR_28_FUNC(0)
				   | IPSR_24_FUNC(0)
				   | IPSR_20_FUNC(0)
				   | IPSR_16_FUNC(0)
				   | IPSR_12_FUNC(0)
				   | IPSR_8_FUNC(0)
				   | IPSR_4_FUNC(0)
				   | IPSR_0_FUNC(0));

	pfc_reg_write(PFC_IPSR3, IPSR_28_FUNC(0)
				   | IPSR_24_FUNC(0)
				   | IPSR_20_FUNC(0)
				   | IPSR_16_FUNC(0)
				   | IPSR_12_FUNC(0)
				   | IPSR_8_FUNC(0)
				   | IPSR_4_FUNC(0)
				   | IPSR_0_FUNC(0));

	pfc_reg_write(PFC_IPSR4, IPSR_28_FUNC(0)
				   | IPSR_24_FUNC(0)
				   | IPSR_20_FUNC(0)
				   | IPSR_16_FUNC(0)
				   | IPSR_12_FUNC(0)
				   | IPSR_8_FUNC(0)
				   | IPSR_4_FUNC(0)
				   | IPSR_0_FUNC(0));

	pfc_reg_write(PFC_IPSR5, IPSR_28_FUNC(0)
				   | IPSR_24_FUNC(0)
				   | IPSR_20_FUNC(0)
				   | IPSR_16_FUNC(0)
				   | IPSR_12_FUNC(0)
				   | IPSR_8_FUNC(0)
				   | IPSR_4_FUNC(0)
				   | IPSR_0_FUNC(0));

	pfc_reg_write(PFC_IPSR6, IPSR_28_FUNC(0)
				   | IPSR_24_FUNC(0)
				   | IPSR_20_FUNC(0)
				   | IPSR_16_FUNC(0)
				   | IPSR_12_FUNC(0)
				   | IPSR_8_FUNC(0)
				   | IPSR_4_FUNC(0)
				   | IPSR_0_FUNC(0));

	pfc_reg_write(PFC_IPSR7, IPSR_28_FUNC(0)
				   | IPSR_24_FUNC(4)
				   | IPSR_20_FUNC(4)
				   | IPSR_16_FUNC(4)
				   | IPSR_12_FUNC(4)
				   | IPSR_8_FUNC(0)
				   | IPSR_4_FUNC(0)
				   | IPSR_0_FUNC(0));

	pfc_reg_write(PFC_IPSR8, IPSR_28_FUNC(0)
				   | IPSR_24_FUNC(0)
				   | IPSR_20_FUNC(0)
				   | IPSR_16_FUNC(4)
				   | IPSR_12_FUNC(0)
				   | IPSR_8_FUNC(0)
				   | IPSR_4_FUNC(0)
				   | IPSR_0_FUNC(0));

	/* initialize POC Control */

	pfc_reg_write(PFC_POCCTRL0, IOCTRL30_POC_VI0_DATA5
				   | IOCTRL30_POC_VI0_DATA4
				   | IOCTRL30_POC_VI0_DATA3
				   | IOCTRL30_POC_VI0_DATA2
				   | IOCTRL30_POC_VI0_DATA1
				   | IOCTRL30_POC_VI0_DATA0
				   | IOCTRL30_POC_VI0_VSYNC_N
				   | IOCTRL30_POC_VI0_HSYNC_N
				   | IOCTRL30_POC_VI0_CLKENB
				   | IOCTRL30_POC_VI0_CLK
				   | IOCTRL30_POC_DU_EXODDF_DU_ODDF_DISP_CDE
				   | IOCTRL30_POC_DU_EXVSYNC_DU_VSYNC
				   | IOCTRL30_POC_DU_EXHSYNC_DU_HSYNC
				   | IOCTRL30_POC_DU_DOTCLKOUT
				   | IOCTRL30_POC_DU_DB7
				   | IOCTRL30_POC_DU_DB6
				   | IOCTRL30_POC_DU_DB5
				   | IOCTRL30_POC_DU_DB4
				   | IOCTRL30_POC_DU_DB3
				   | IOCTRL30_POC_DU_DB2
				   | IOCTRL30_POC_DU_DG7
				   | IOCTRL30_POC_DU_DG6
				   | IOCTRL30_POC_DU_DG5
				   | IOCTRL30_POC_DU_DG4
				   | IOCTRL30_POC_DU_DG3
				   | IOCTRL30_POC_DU_DG2
				   | IOCTRL30_POC_DU_DR7
				   | IOCTRL30_POC_DU_DR6
				   | IOCTRL30_POC_DU_DR5
				   | IOCTRL30_POC_DU_DR4
				   | IOCTRL30_POC_DU_DR3
				   | IOCTRL30_POC_DU_DR2);

	pfc_reg_write(PFC_IOCTRL31, IOCTRL31_POC_DUMMY_31
				   | IOCTRL31_POC_DUMMY_30
				   | IOCTRL31_POC_DUMMY_29
				   | IOCTRL31_POC_DUMMY_28
				   | IOCTRL31_POC_DUMMY_27
				   | IOCTRL31_POC_DUMMY_26
				   | IOCTRL31_POC_DUMMY_25
				   | IOCTRL31_POC_DUMMY_24
				   | IOCTRL31_POC_VI1_FIELD
				   | IOCTRL31_POC_VI1_DATA11
				   | IOCTRL31_POC_VI1_DATA10
				   | IOCTRL31_POC_VI1_DATA9
				   | IOCTRL31_POC_VI1_DATA8
				   | IOCTRL31_POC_VI1_DATA7
				   | IOCTRL31_POC_VI1_DATA6
				   | IOCTRL31_POC_VI1_DATA5
				   | IOCTRL31_POC_VI1_DATA4
				   | IOCTRL31_POC_VI1_DATA3
				   | IOCTRL31_POC_VI1_DATA2
				   | IOCTRL31_POC_VI1_DATA1
				   | IOCTRL31_POC_VI1_DATA0
				   | IOCTRL31_POC_VI1_VSYNC_N
				   | IOCTRL31_POC_VI1_HSYNC_N
				   | IOCTRL31_POC_VI1_CLKENB
				   | IOCTRL31_POC_VI1_CLK
				   | IOCTRL31_POC_VI0_FIELD
				   | IOCTRL31_POC_VI0_DATA11
				   | IOCTRL31_POC_VI0_DATA10
				   | IOCTRL31_POC_VI0_DATA9
				   | IOCTRL31_POC_VI0_DATA8
				   | IOCTRL31_POC_VI0_DATA7
				   | IOCTRL31_POC_VI0_DATA6);

	pfc_reg_write(PFC_POCCTRL2, 0x00000000);

	pfc_reg_write(PFC_TDSELCTRL0, 0x00000000);

	/* initialize Pull enable */
	pfc_reg_write(PFC_PUEN0, PUEN0_PUEN_VI0_CLK
				   | PUEN0_PUEN_TDI
				   | PUEN0_PUEN_TMS
				   | PUEN0_PUEN_TCK
				   | PUEN0_PUEN_TRST_N
				   | PUEN0_PUEN_IRQ0
				   | PUEN0_PUEN_FSCLKST_N
				   | PUEN0_PUEN_DU_EXHSYNC_DU_HSYNC
				   | PUEN0_PUEN_DU_DOTCLKOUT
				   | PUEN0_PUEN_DU_DB7
				   | PUEN0_PUEN_DU_DB6
				   | PUEN0_PUEN_DU_DB5
				   | PUEN0_PUEN_DU_DB4
				   | PUEN0_PUEN_DU_DB3
				   | PUEN0_PUEN_DU_DB2
				   | PUEN0_PUEN_DU_DG7
				   | PUEN0_PUEN_DU_DG6
				   | PUEN0_PUEN_DU_DG5
				   | PUEN0_PUEN_DU_DG4
				   | PUEN0_PUEN_DU_DG3
				   | PUEN0_PUEN_DU_DG2
				   | PUEN0_PUEN_DU_DR7
				   | PUEN0_PUEN_DU_DR6
				   | PUEN0_PUEN_DU_DR5
				   | PUEN0_PUEN_DU_DR4
				   | PUEN0_PUEN_DU_DR3
				   | PUEN0_PUEN_DU_DR2);

	pfc_reg_write(PFC_PUEN1, PUEN1_PUEN_VI1_DATA11
				   | PUEN1_PUEN_VI1_DATA10
				   | PUEN1_PUEN_VI1_DATA9
				   | PUEN1_PUEN_VI1_DATA8
				   | PUEN1_PUEN_VI1_DATA7
				   | PUEN1_PUEN_VI1_DATA6
				   | PUEN1_PUEN_VI1_DATA5
				   | PUEN1_PUEN_VI1_DATA4
				   | PUEN1_PUEN_VI1_DATA3
				   | PUEN1_PUEN_VI1_DATA2
				   | PUEN1_PUEN_VI1_DATA1
				   | PUEN1_PUEN_VI1_DATA0
				   | PUEN1_PUEN_VI1_VSYNC_N
				   | PUEN1_PUEN_VI1_HSYNC_N
				   | PUEN1_PUEN_VI1_CLKENB
				   | PUEN1_PUEN_VI1_CLK
				   | PUEN1_PUEN_VI0_DATA11
				   | PUEN1_PUEN_VI0_DATA10
				   | PUEN1_PUEN_VI0_DATA9
				   | PUEN1_PUEN_VI0_DATA8
				   | PUEN1_PUEN_VI0_DATA7
				   | PUEN1_PUEN_VI0_DATA6
				   | PUEN1_PUEN_VI0_DATA5
				   | PUEN1_PUEN_VI0_DATA4
				   | PUEN1_PUEN_VI0_DATA3
				   | PUEN1_PUEN_VI0_DATA2
				   | PUEN1_PUEN_VI0_DATA1);

	pfc_reg_write(PFC_PUEN2, PUEN2_PUEN_CANFD_CLK
				   | PUEN2_PUEN_CANFD1_RX
				   | PUEN2_PUEN_CANFD1_TX
				   | PUEN2_PUEN_CANFD0_RX
				   | PUEN2_PUEN_CANFD0_TX
				   | PUEN2_PUEN_AVB0_AVTP_CAPTURE
				   | PUEN2_PUEN_AVB0_AVTP_MATCH
				   | PUEN2_PUEN_AVB0_LINK
				   | PUEN2_PUEN_AVB0_PHY_INT
				   | PUEN2_PUEN_AVB0_MAGIC
				   | PUEN2_PUEN_AVB0_TXCREFCLK
				   | PUEN2_PUEN_AVB0_TD3
				   | PUEN2_PUEN_AVB0_TD2
				   | PUEN2_PUEN_AVB0_TD1
				   | PUEN2_PUEN_AVB0_TD0
				   | PUEN2_PUEN_AVB0_TXC
				   | PUEN2_PUEN_AVB0_TX_CTL
				   | PUEN2_PUEN_AVB0_RD3
				   | PUEN2_PUEN_AVB0_RD2
				   | PUEN2_PUEN_AVB0_RD1
				   | PUEN2_PUEN_AVB0_RD0
				   | PUEN2_PUEN_AVB0_RXC
				   | PUEN2_PUEN_AVB0_RX_CTL
				   | PUEN2_PUEN_VI1_FIELD);

	pfc_reg_write(PFC_PUEN3, PUEN3_PUEN_DIGRF_CLKOUT
				   | PUEN3_PUEN_DIGRF_CLKIN);

	/* initialize PUD Control */
	pfc_reg_write(PFC_PUD0, PUD0_PUD_VI0_CLK
				   | PUD0_PUD_IRQ0
				   | PUD0_PUD_FSCLKST_N
				   | PUD0_PUD_DU_EXODDF_DU_ODDF_DISP_CDE
				   | PUD0_PUD_DU_EXVSYNC_DU_VSYNC
				   | PUD0_PUD_DU_EXHSYNC_DU_HSYNC
				   | PUD0_PUD_DU_DOTCLKOUT
				   | PUD0_PUD_DU_DB7
				   | PUD0_PUD_DU_DB6
				   | PUD0_PUD_DU_DB5
				   | PUD0_PUD_DU_DB4
				   | PUD0_PUD_DU_DB3
				   | PUD0_PUD_DU_DB2
				   | PUD0_PUD_DU_DG7
				   | PUD0_PUD_DU_DG6
				   | PUD0_PUD_DU_DG5
				   | PUD0_PUD_DU_DG4
				   | PUD0_PUD_DU_DG3
				   | PUD0_PUD_DU_DG2
				   | PUD0_PUD_DU_DR7
				   | PUD0_PUD_DU_DR6
				   | PUD0_PUD_DU_DR5
				   | PUD0_PUD_DU_DR4
				   | PUD0_PUD_DU_DR3
				   | PUD0_PUD_DU_DR2);

	pfc_reg_write(PFC_PUD1, PUD1_PUD_VI1_DATA11
				   | PUD1_PUD_VI1_DATA10
				   | PUD1_PUD_VI1_DATA9
				   | PUD1_PUD_VI1_DATA8
				   | PUD1_PUD_VI1_DATA7
				   | PUD1_PUD_VI1_DATA6
				   | PUD1_PUD_VI1_DATA5
				   | PUD1_PUD_VI1_DATA4
				   | PUD1_PUD_VI1_DATA3
				   | PUD1_PUD_VI1_DATA2
				   | PUD1_PUD_VI1_DATA1
				   | PUD1_PUD_VI1_DATA0
				   | PUD1_PUD_VI1_VSYNC_N
				   | PUD1_PUD_VI1_HSYNC_N
				   | PUD1_PUD_VI1_CLKENB
				   | PUD1_PUD_VI1_CLK
				   | PUD1_PUD_VI0_DATA11
				   | PUD1_PUD_VI0_DATA10
				   | PUD1_PUD_VI0_DATA9
				   | PUD1_PUD_VI0_DATA8
				   | PUD1_PUD_VI0_DATA7
				   | PUD1_PUD_VI0_DATA6
				   | PUD1_PUD_VI0_DATA5
				   | PUD1_PUD_VI0_DATA4
				   | PUD1_PUD_VI0_DATA3
				   | PUD1_PUD_VI0_DATA2
				   | PUD1_PUD_VI0_DATA1
				   | PUD1_PUD_VI0_DATA0
				   | PUD1_PUD_VI0_VSYNC_N
				   | PUD1_PUD_VI0_HSYNC_N
				   | PUD1_PUD_VI0_CLKENB);

	pfc_reg_write(PFC_PUD2, PUD2_PUD_CANFD_CLK
				   | PUD2_PUD_CANFD1_RX
				   | PUD2_PUD_CANFD1_TX
				   | PUD2_PUD_CANFD0_RX
				   | PUD2_PUD_CANFD0_TX
				   | PUD2_PUD_AVB0_AVTP_CAPTURE
				   | PUD2_PUD_VI1_FIELD);

	pfc_reg_write(PFC_PUD3, PUD3_PUD_DIGRF_CLKOUT
				   | PUD3_PUD_DIGRF_CLKIN);

	/* initialize Module Select */
	pfc_reg_write(PFC_MOD_SEL0, 0x00000000);

	// gpio
	/* initialize positive/negative logic select */
	mmio_write_32(GPIO_POSNEG0, 0x00000000U);
	mmio_write_32(GPIO_POSNEG1, 0x00000000U);
	mmio_write_32(GPIO_POSNEG2, 0x00000000U);
	mmio_write_32(GPIO_POSNEG3, 0x00000000U);
	mmio_write_32(GPIO_POSNEG4, 0x00000000U);
	mmio_write_32(GPIO_POSNEG5, 0x00000000U);

	/* initialize general IO/interrupt switching */
	mmio_write_32(GPIO_IOINTSEL0, 0x00000000U);
	mmio_write_32(GPIO_IOINTSEL1, 0x00000000U);
	mmio_write_32(GPIO_IOINTSEL2, 0x00000000U);
	mmio_write_32(GPIO_IOINTSEL3, 0x00000000U);
	mmio_write_32(GPIO_IOINTSEL4, 0x00000000U);
	mmio_write_32(GPIO_IOINTSEL5, 0x00000000U);

	/* initialize general output register */
	mmio_write_32(GPIO_OUTDT0, 0x00000000U);
	mmio_write_32(GPIO_OUTDT1, 0x00000000U);
	mmio_write_32(GPIO_OUTDT2, 0x00000000U);
	mmio_write_32(GPIO_OUTDT3, 0x00000000U);
	mmio_write_32(GPIO_OUTDT4, 0x00000000U);
	mmio_write_32(GPIO_OUTDT5, 0x00000000U);

	/* initialize general input/output switching */
	mmio_write_32(GPIO_INOUTSEL0, 0x00000000U);
	mmio_write_32(GPIO_INOUTSEL1, 0x00000000U);
	mmio_write_32(GPIO_INOUTSEL2, 0x00000000U);
	mmio_write_32(GPIO_INOUTSEL3, 0x00000000U);
	mmio_write_32(GPIO_INOUTSEL4, 0x00000000U);
	mmio_write_32(GPIO_INOUTSEL5, 0x00000000U);
}

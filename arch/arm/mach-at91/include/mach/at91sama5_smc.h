/*
 * [origin: Linux kernel include/asm-arm/arch-at91/at91sam9_smc.h]
 *
 * Copyright (C) 2007 Andrew Victor
 * Copyright (C) 2007 Atmel Corporation.
 *
 * Static Memory Controllers (SMC) - System peripherals registers.
 * Based on AT91SAM9261 datasheet revision D.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#ifndef AT91SAMA5_SMC_H
#define AT91SAMA5_SMC_H

#define at91_smc_read(id, field) \
	__raw_readl(AT91_BASE_SMC + ((id) * 0x14) + field)

#define at91_smc_write(id, field, value) \
	__raw_writel(value, AT91_BASE_SMC + ((id) * 0x14) + field)

#ifndef __ASSEMBLY__
struct sama5_smc_config {
	/* Setup register */
	u8 ncs_read_setup;
	u8 nrd_setup;
	u8 ncs_write_setup;
	u8 nwe_setup;

	/* Pulse register */
	u8 ncs_read_pulse;
	u8 nrd_pulse;
	u8 ncs_write_pulse;
	u8 nwe_pulse;

	/* Cycle register */
	u16 read_cycle;
	u16 write_cycle;

	/* Timings register */
	u8 tclr_timings;
	u8 tadl_timings;
	u8 tar_timings;
	u8 ocms_timings:1;
	u8 trr_timings;
	u8 twb_timings;
	u8 rbnsel_timings;
	u8 nfsel_timings:1;

	/* Mode register */
	u32 mode;
	u8 tdf_cycles:4;
};

extern void sama5_smc_configure(int id, int cs,
				struct sama5_smc_config *config);
extern void sama5_smc_read(int id, int cs,
			   struct sama5_smc_config *config);
extern void sama5_smc_read_mode(int id, int cs,
				struct sama5_smc_config *config);
extern void sama5_smc_write_mode(int id, int cs,
				 struct sama5_smc_config *config);
#endif

/* Setup Register for CS n */
#define AT91_SMC_SETUP		0x00
		/* NWE Setup Length */
#define		AT91_SMC_NWESETUP       (0x3f <<  0)
#define			AT91_SMC_NWESETUP_(x)       ((x) << 0)
		/* NCS Setup Length in Write Access */
#define		AT91_SMC_NCS_WRSETUP	(0x3f <<  8)
#define			AT91_SMC_NCS_WRSETUP_(x)	((x) << 8)
		/* NRD Setup Length */
#define		AT91_SMC_NRDSETUP       (0x3f << 16)
#define			AT91_SMC_NRDSETUP_(x)       ((x) << 16)
		/* NCS Setup Length in Read Access */
#define		AT91_SMC_NCS_RDSETUP	(0x3f << 24)
#define			AT91_SMC_NCS_RDSETUP_(x)	((x) << 24)

/* Pulse Register for CS n */
#define AT91_SMC_PULSE		0x04
		/* NWE Pulse Length */
#define		AT91_SMC_NWEPULSE       (0x3f <<  0)
#define			AT91_SMC_NWEPULSE_(x)       ((x) << 0)
		/* NCS Pulse Length in Write Access */
#define		AT91_SMC_NCS_WRPULSE	(0x3f <<  8)
#define			AT91_SMC_NCS_WRPULSE_(x)    ((x) << 8)
		/* NRD Pulse Length */
#define		AT91_SMC_NRDPULSE       (0x3f << 16)
#define			AT91_SMC_NRDPULSE_(x)       ((x) << 16)
		/* NCS Pulse Length in Read Access */
#define		AT91_SMC_NCS_RDPULSE	(0x3f << 24)
#define			AT91_SMC_NCS_RDPULSE_(x)    ((x) << 24)

/* Cycle Register for CS n */
#define AT91_SMC_CYCLE		0x08
		/* Total Write Cycle Length */
#define		AT91_SMC_NWECYCLE       (0x1ff <<  0)
#define			AT91_SMC_NWECYCLE_(x)       ((x) << 0)
		/* Total Read Cycle Length */
#define		AT91_SMC_NRDCYCLE       (0x1ff << 16)
#define			AT91_SMC_NRDCYCLE_(x)       ((x) << 16)

/* Timings Register for CS n */
#define AT91_SMC_TIMINGS	0x0c
		/* CLE to REN Low Delay */
#define		AT91_SMC_TCLR       (0xf <<  0)
#define			AT91_SMC_TCLR_(x)           ((x) << 0)
		/* ALE to Data Start */
#define		AT91_SMC_TADL       (0xf <<  4)
#define			AT91_SMC_TADL_(x)           ((x) << 4)
		/* ALE to REN Low Delay */
#define		AT91_SMC_TAR        (0xf <<  8)
#define			AT91_SMC_TAR_(x)            ((x) << 8)
		/* Off Chip Memory Scrambling - Enabled */
#define		AT91_SMC_OCMS       (0x1 << 12)
#define			AT91_SMC_OCMS_(x)           ((x) << 12)
		/* Ready to REN Low Delay */
#define		AT91_SMC_TRR        (0xf << 16)
#define			AT91_SMC_TRR_(x)            ((x) << 16)
		/* WEN Hign to REN to Busy */
#define		AT91_SMC_TWB        (0xf << 24)
#define			AT91_SMC_TWB_(x)            ((x) << 24)
		/* Ready/Busy Line Selection */
#define		AT91_SMC_RBNSEL     (0x7 << 28)
#define			AT91_SMC_RBNSEL_(x)         ((x) << 28)
		/* NAND Flash Selection */
#define		AT91_SMC_NFSEL      (0x1 << 31)
#define			AT91_SMC_NFSEL_(x)          ((x) << 31)

/* Mode Register for CS n */
#define AT91_SMC_MODE		0x10
		/* Read Mode */
#define		AT91_SMC_READMODE	(0x1 <<  0)
		/* Write Mode */
#define		AT91_SMC_WRITEMODE	(0x1 <<  1)
		/* NWAIT Mode */
#define		AT91_SMC_EXNWMODE	(0x3 <<  4)
#define			AT91_SMC_EXNWMODE_DISABLE	(0 << 4)
#define			AT91_SMC_EXNWMODE_FROZEN	(2 << 4)
#define			AT91_SMC_EXNWMODE_READY		(3 << 4)
		/* Byte Access Type */
#define		AT91_SMC_BAT		(0x1 <<  8)
#define			AT91_SMC_BAT_SELECT         (0 << 8)
#define			AT91_SMC_BAT_WRITE          (1 << 8)
		/* Data Bus Width */
#define		AT91_SMC_DBW		(0x1 << 12)
#define			AT91_SMC_DBW_8              (0 << 12)
#define			AT91_SMC_DBW_16             (1 << 12)
		/* Data Float Time. */
#define		AT91_SMC_TDF		(0xf << 16)
#define			AT91_SMC_TDF_(x)            ((x) << 16)
		/* TDF Optimization - Enabled */
#define		AT91_SMC_TDFMODE	(0x1 << 20)

#endif

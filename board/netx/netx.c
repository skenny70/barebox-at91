/*
 * Copyright (C) 2004 Sascha Hauer, Synertronixx GmbH
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 *
 */

#include <common.h>
#include <net.h>
#include <cfi_flash.h>
#include <init.h>
#include <environment.h>
#include <asm/arch/netx-regs.h>
#include <partition.h>
#include <fs.h>
#include <fcntl.h>
#include <asm/arch/netx-eth.h>

static struct device_d cfi_dev = {
	.name     = "cfi_flash",
	.id       = "nor0",

	.map_base = 0xC0000000,
	.size     = 32 * 1024 * 1024,
};

static struct device_d sdram_dev = {
	.name     = "ram",
	.id       = "ram0",

	.map_base = 0x80000000,
	.size     = 64 * 1024 * 1024,

	.type     = DEVICE_TYPE_DRAM,
};

struct netx_eth_platform_data eth0_data = {
	.xcno = 0,
};

static struct device_d netx_eth_dev0 = {
	.name		= "netx-eth",
	.id		= "eth0",
	.platform_data	= &eth0_data,
	.type		= DEVICE_TYPE_ETHER,
};

struct netx_eth_platform_data eth1_data = {
	.xcno = 1,
};

static struct device_d netx_eth_dev1 = {
	.name		= "netx-eth",
	.id		= "eth1",
	.platform_data	= &eth1_data,
	.type		= DEVICE_TYPE_ETHER,
};

static int netx_devices_init(void) {
	register_device(&cfi_dev);
	register_device(&sdram_dev);
	register_device(&netx_eth_dev0);
//	register_device(&netx_eth_dev1);

	dev_add_partition(&cfi_dev, 0x00000, 0x40000, "self");
	dev_protect(&cfi_dev, 0x40000, 0, 1);

	/* Do not overwrite primary env for now */
	dev_add_partition(&cfi_dev, 0xc0000, 0x80000, "env"); 

	return 0;
}

device_initcall(netx_devices_init);

static struct device_d netx_serial_device = {
        .name     = "netx_serial",
        .id       = "cs0",
	.map_base = NETX_PA_UART0,
	.size     = 0x40,
        .type     = DEVICE_TYPE_CONSOLE,
};

static int netx_console_init(void)
{
	/* configure gpio for serial */
	*(volatile unsigned long *)(0x00100800) = 2;
	*(volatile unsigned long *)(0x00100804) = 2;
	*(volatile unsigned long *)(0x00100808) = 2;
	*(volatile unsigned long *)(0x0010080c) = 2;

	register_device(&netx_serial_device);
	return 0;
}

console_initcall(netx_console_init);

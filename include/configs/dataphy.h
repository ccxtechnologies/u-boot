/*
 * Copyright (C) 2016-2018 Digi International, Inc.
 * Copyright (C) 2015 Freescale Semiconductor, Inc.
 *
 * Configuration settings for the Digi ConnecCore 6UL SBC board.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */
#ifndef CCIMX6ULSBC_CONFIG_H
#define CCIMX6ULSBC_CONFIG_H

#include "ccimx6ul_common.h"

#define CONFIG_BOARD_DESCRIPTION	"CCX Technologies DataPHY"

/* uncomment for SECURE mode support */
/* #define CONFIG_SECURE_BOOT */

/* FLASH and environment organization */
#define CONFIG_SYS_BOOT_NAND

#define CONFIG_SYS_USE_NAND
#define CONFIG_ENV_IS_IN_NAND
#define CONFIG_CMD_MTDPARTS
#define CONFIG_MTD_DEVICE
#define CONFIG_MTD_PARTITIONS
#define CONFIG_CMD_UPDATE_NAND
#define CONFIG_SYS_STORAGE_MEDIA	"nand"
#define CONFIG_CMD_BOOTSTREAM

#define CONFIG_CMD_NAND
#define CONFIG_CMD_NAND_TRIMFFS

/* NAND stuff */
#define CONFIG_NAND_MXS
#define CONFIG_SYS_MAX_NAND_DEVICE	1
#define CONFIG_SYS_NAND_BASE		0x40000000
#define CONFIG_SYS_NAND_5_ADDR_CYCLE
#define CONFIG_SYS_NAND_ONFI_DETECTION

/* DMA stuff, needed for GPMI/MXS NAND support */
#define CONFIG_APBH_DMA
#define CONFIG_APBH_DMA_BURST
#define CONFIG_APBH_DMA_BURST8

#define CONFIG_SYS_FSL_USDHC_NUM	1

/* U-Boot Environment */
#undef CONFIG_ENV_SIZE
#define CONFIG_ENV_OFFSET		(3 * SZ_1M)
#define CONFIG_ENV_SIZE			SZ_128K
#define CONFIG_SYS_REDUNDANT_ENVIRONMENT
#define CONFIG_DYNAMIC_ENV_LOCATION
#if (CONFIG_DDR_MB == 1024)
# define CONFIG_ENV_PARTITION_SIZE	(3 * SZ_1M)
#else
# define CONFIG_ENV_PARTITION_SIZE	(1 * SZ_1M)
#endif /* (CONFIG_DDR_MB == 1024) */
/* The environment may use any good blocks within the "environment" partition */
#define CONFIG_ENV_RANGE		CONFIG_ENV_PARTITION_SIZE

#define CONFIG_CMD_EXPORTENV
#define CONFIG_CMD_IMPORTENV

/* Serial port */
#define CONFIG_MXC_UART
#define CONFIG_MXC_UART_BASE		UART5_BASE
#undef CONFIG_CONS_INDEX
#define CONFIG_CONS_INDEX		5
#define CONSOLE_DEV			"ttymxc4"
#define CONFIG_BAUDRATE			115200

#define CONFIG_NETCONSOLE 1

#define IMX_FEC_BASE		ENET_BASE_ADDR
#define CONFIG_FEC_MXC_PHYADDR  0x1
#define CONFIG_ETHPRIME         "FEC0"
#define CONFIG_FEC_XCV_TYPE     RMII
#define CONFIG_PREBOOT		"echo;echo --- CCX Technologies DataPHY ---;echo"
#define CONFIG_IPADDR		192.168.43.9
#define CONFIG_SERVERIP		192.168.43.1
#define CONFIG_GATEWAYIP	192.168.43.1
#define CONFIG_NETMASK		255.255.255.0

/* I2C */
#define CONFIG_SYS_I2C_MXC_I2C1
#define CONFIG_SYS_I2C_MXC_I2C2

#define CONFIG_EXTRA_ENV_SETTINGS \
		"ethaddr=ce:ce:ce:ce:ce:01\0" \
		"eth1addr=ce:ce:ce:ce:ce:02\0" \
		"wlanaddr=ce:ce:ce:ce:ce:03\0" \
		"btaddr=ce:ce:ce:ce:ce:04\0" \
		"fdtaddr=0x83000000\0" \
		"fdtfile=/boot/linux.dtb\0" \
		"kernelfile=/boot/zImage\0" \
		"console=" CONSOLE_DEV "\0" \
		"mmcdev=0\0" \
		"mmcrootpart=2\0" \
		"loadfdt=ext4load mmc ${mmcdev}:${mmcrootpart} ${fdtaddr} ${fdtfile}\0" \
		"loadkernel=ext4load mmc ${mmcdev}:${mmcrootpart} ${loadaddr} ${kernelfile}\0" \
		"loadall=mmc dev ${mmcdev} && mmc rescan && run loadkernel && run loadfdt\0" \
		"bootargs=rootwait\0" \
		"setconsoleargs=setenv bootargs ${bootargs} console=${console},${baudrate}\0" \
		"setfsargs=setenv bootargs ${bootargs} root=/dev/mmcblk${mmcdev}p${mmcrootpart} rootfstype=ext4 rw\0" \
		"setbootargs=run setconsoleargs && run setfsargs && echo Set bootargs to ${bootargs}...\0" \
		"bootkernel=bootz ${loadaddr} - ${fdtaddr}\0" \
		"netconsole=setenv ncip $serverip; setenv stdin nc; setenv stdout nc; setenv stderr nc;\0" \
		"mtdparts=mtdparts=gpmi-nand:3m(bootloader),1m(environment),1m(safe),12m(linux),14m(recovery),122m(rootfs),-(update)\0" \
		"bootcmd_mfg=echo Manufacturing Mode == BURNING FUSES FOR NAND BOOT ==; "\
		"fuse prog -y 0 5 0x00002000; "\
		"fuse prog -y 0 5 0x00000800; "\
		"fuse prog -y 0 5 0x00000080; "\
		"fuse prog -y 0 5 0x00000010; "\
		"fuse prog -y 0 6 0x00000010;\0" \

#define CONFIG_BOOTCOMMAND \
		"echo !! DEFAULT BOOT !!" \
		" && run loadall"\
		" && run setbootargs"\
		" && run bootkernel" \

#define CONFIG_SYS_MMC_ENV_DEV	0
#define CONFIG_FEC_ENET_DEV	0

/* UBI and UBIFS support */
#define CONFIG_RBTREE
#define CONFIG_CMD_UBIFS
#define CONFIG_LZO
#define CONFIG_DIGI_UBI

#endif /* CCIMX6ULSBC_CONFIG_H */

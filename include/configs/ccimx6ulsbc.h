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

/* uncomment for PLUGIN mode support */
/* #define CONFIG_USE_PLUGIN */

/* uncomment for SECURE mode support */
/* #define CONFIG_SECURE_BOOT */

/* uncomment for BEE support, needs to enable CONFIG_CMD_FUSE */
/* #define CONFIG_CMD_BEE */

/* FLASH and environment organization */
#define CONFIG_SYS_BOOT_NAND

#if defined(CONFIG_SYS_BOOT_NAND)
#define CONFIG_SYS_USE_NAND
#define CONFIG_ENV_IS_IN_NAND
#define CONFIG_CMD_MTDPARTS
#define CONFIG_MTD_DEVICE
#define CONFIG_MTD_PARTITIONS
#define CONFIG_CMD_UPDATE_NAND
#define CONFIG_SYS_STORAGE_MEDIA	"nand"
#define CONFIG_CMD_BOOTSTREAM
#else
#define CONFIG_ENV_IS_IN_MMC
#define CONFIG_CMD_UPDATE_MMC
#define CONFIG_SYS_STORAGE_MEDIA	"mmc"
#endif

#ifdef CONFIG_SYS_USE_NAND
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
#endif

#define CONFIG_SYS_FSL_USDHC_NUM	1

/* U-Boot Environment */
#if defined(CONFIG_ENV_IS_IN_MMC)
#define CONFIG_ENV_OFFSET		(8 * SZ_64K)
#elif defined(CONFIG_ENV_IS_IN_SPI_FLASH)
#define CONFIG_ENV_OFFSET		(768 * 1024)
#define CONFIG_ENV_SPI_BUS		CONFIG_SF_DEFAULT_BUS
#define CONFIG_ENV_SPI_CS		CONFIG_SF_DEFAULT_CS
#define CONFIG_ENV_SPI_MODE		CONFIG_SF_DEFAULT_MODE
#define CONFIG_ENV_SPI_MAX_HZ		CONFIG_SF_DEFAULT_SPEED
#elif defined(CONFIG_ENV_IS_IN_NAND)
#undef CONFIG_ENV_SIZE
#define CONFIG_ENV_OFFSET		(3 * SZ_1M)
#define CONFIG_ENV_SIZE			SZ_128K
#endif
#define CONFIG_SYS_REDUNDANT_ENVIRONMENT
#define CONFIG_DYNAMIC_ENV_LOCATION
#if (CONFIG_DDR_MB == 1024)
# define CONFIG_ENV_PARTITION_SIZE	(3 * SZ_1M)
#else
# define CONFIG_ENV_PARTITION_SIZE	(1 * SZ_1M)
#endif /* (CONFIG_DDR_MB == 1024) */
/* The environment may use any good blocks within the "environment" partition */
#define CONFIG_ENV_RANGE		CONFIG_ENV_PARTITION_SIZE

/* Serial port */
#define CONFIG_MXC_UART
#define CONFIG_MXC_UART_BASE		UART5_BASE
#undef CONFIG_CONS_INDEX
#define CONFIG_CONS_INDEX		5
#define CONSOLE_DEV			"ttymxc4"
#define CONFIG_BAUDRATE			115200

/* Ethernet */
#define CONFIG_FEC_ENET_DEV		0
#if (CONFIG_FEC_ENET_DEV == 0)
#define IMX_FEC_BASE			ENET_BASE_ADDR
#define CONFIG_FEC_MXC_PHYADDR          0x0
#define CONFIG_ETHPRIME                 "FEC0"
#define CONFIG_FEC_XCV_TYPE             RMII
#elif (CONFIG_FEC_ENET_DEV == 1)
#define IMX_FEC_BASE			ENET2_BASE_ADDR
#define CONFIG_FEC_MXC_PHYADDR          0x1
#define CONFIG_ETHPRIME                 "FEC1"
#define CONFIG_FEC_XCV_TYPE             RMII
#endif

#define CONFIG_NETCONSOLE 1

#define IMX_FEC_BASE			ENET_BASE_ADDR
#define CONFIG_FEC_MXC_PHYADDR          0x0
#define CONFIG_FEC_XCV_TYPE             RMII
#define CONFIG_PREBOOT		"echo;echo --- CCX Technologies DataPHY ---;echo"
#define CONFIG_IPADDR		192.168.43.9
#define CONFIG_SERVERIP		192.168.43.1
#define CONFIG_GATEWAYIP	192.168.43.1
#define CONFIG_NETMASK		255.255.255.0
#define CONFIG_ETHADDR	ce:ce:ce:ce:ce:ce

/* I2C */
#define CONFIG_SYS_I2C_MXC_I2C1
#define CONFIG_SYS_I2C_MXC_I2C2

#define CONFIG_EXTRA_ENV_SETTINGS \
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

#define CONFIG_BOOTCOMMAND \
		"echo !! DEFAULT BOOT !!" \
		" && run loadall"\
		" && run setbootargs"\
		" && run bootkernel" \

#define CONFIG_SYS_MMC_ENV_DEV	0
#define CONFIG_FEC_ENET_DEV	0

/* Carrier board version and ID commands */
#define CONFIG_CMD_BOARD_VERSION
#define CONFIG_CMD_BOARD_ID

/* Carrier board version in OTP bits */
#define CONFIG_HAS_CARRIERBOARD_VERSION
#ifdef CONFIG_HAS_CARRIERBOARD_VERSION
/* The carrier board version is stored in Bank 4 Word 6 (GP1)
 * in bits 3..0 */
#define CONFIG_CARRIERBOARD_VERSION_BANK	4
#define CONFIG_CARRIERBOARD_VERSION_WORD	6
#define CONFIG_CARRIERBOARD_VERSION_MASK	0xf
#define CONFIG_CARRIERBOARD_VERSION_OFFSET	0
#endif /* CONFIG_HAS_CARRIERBOARD_VERSION */

/* Carrier board ID in OTP bits */
#define CONFIG_HAS_CARRIERBOARD_ID
#ifdef CONFIG_HAS_CARRIERBOARD_ID
/* The carrier board ID is stored in Bank 4 Word 6 (GP1)
 * in bits 11..4 */
#define CONFIG_CARRIERBOARD_ID_BANK	4
#define CONFIG_CARRIERBOARD_ID_WORD	6
#define CONFIG_CARRIERBOARD_ID_MASK	0xff
#define CONFIG_CARRIERBOARD_ID_OFFSET	4
#endif /* CONFIG_HAS_CARRIERBOARD_ID */

/* UBI and UBIFS support */
#define CONFIG_RBTREE
#define CONFIG_CMD_UBIFS
#define CONFIG_LZO
#define CONFIG_DIGI_UBI

#endif /* CCIMX6ULSBC_CONFIG_H */

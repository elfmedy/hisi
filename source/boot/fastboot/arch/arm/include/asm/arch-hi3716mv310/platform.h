/* Hi3716x */
#ifndef __HI_CHIP_REGS_H__
#define __HI_CHIP_REGS_H__

#define REG_BASE_SCTL                 0x101E0000
#define REG_BASE_TIMER01              0x101E2000
#define REG_BASE_GPIO5                0x101E4000
#define REG_BASE_TIMER67              0x10206000
#define REG_BASE_GPIO0                0x101E6000
#define REG_BASE_GPIO1                0x101E7000
#define REG_BASE_GPIO2                0x101E8000
#define REG_BASE_GPIO3                0x101E9000
#define REG_BASE_GPIO4                0x101EA000
#define REG_BASE_TIMER45              0x101EB000
#define REG_BASE_GPIO6                0x101EC000
#define REG_BASE_GPIO7                0x101ED000
#define REG_BASE_GPIO8                0x101EE000
#define REG_BASE_GPIO9                0x101EF000
#define REG_BASE_GPIO10               0x101F0000
#define REG_BASE_GPIO11               0x101F1000
#define REG_BASE_GPIO12               0x101F2000
#define GPIO_SIZE                     0x1000
#define MAX_GPIO_NUMS                 (6)

#define REG_BASE_CRG                  0x101F5000
/* CA clock and reset register */
#define HI3716MV300_REG_PERI_CRG29    0x00B4

#define REG_BASE_UART0                0x101E5000
#define REG_BASE_UART1                0x101FC000
#define REG_BASE_UART3                0x101FE000
#define REG_BASE_PERI_CTRL            0x10200000
#define REMAP_CTRL_ADDR               0x04
#define REG_BASE_WDG                  0x10201000
#define REG_BASE_TIMER23              0x10202000
#define REG_BASE_IO_CONFIG            0x10203000
#define REG_BASE_A9_PERI              0x10220000
#define REG_BASE_CSSYS                0x10330000
#define REG_BASE_DNR                  0x10450000
#define MEM_BASE_NAND                 0x24000000
#define MEM_BASE_SPI                  0x26000000
#define MEM_BASE_SPI_NAND             0x2A000000
#if (CONFIG_CHIP_TYPE == hi3716mv330)
#  define MEM_BASE_FMC                  0x60200000
#endif
#define REG_BASE_NANDC                0x60010000
#define REG_BASE_SFC                  0x60020000
#define REG_BASE_DMAC                 0x60030000
#define REG_BASE_SPI_NAND             0x60040000
#define REG_BASE_FMC                  0x60050000

#define REG_BASE_OHCI                 0X60070000
#define REG_BASE_EHCI                 0X60080000
#define REG_BASE_USB2_DEVICE          0X60180000
#define REG_BASE_SF                   0X600D0000
#define REG_BASE_GMAC                 0x60140000
#define REG_BASE_MCI                  0x601C0000
#define REG_BASE_LANSWITCH            0X63000000

/* DDRC PHY register */
#define REG_BASE_PHY                  0x10100000
#define DDRC_PHY_REG4B                0x083C
#define DDRC_PHY_REG8                 0x08E0
#define DDRC_PHY_REG11                0x0920
#define DDRC_PHY_REG29                0x09C0
#define DDRC_PHY_REG2                 0x0808
#define DDRC_PHY_REG80                0x0A00
#define DDRC_PHY_REG81                0x0A04

#define REG_SC_CTRL                   0x0000
#define REG_SC_SYSRES                 0x0004
#define REG_SC_APLLFREQCTRL0          0x0018
#define REG_SC_APLLFREQCTRL1          0x001C
#define REG_SC_LOW_POWER_CTRL         0x0040
#define REG_SC_IO_REUSE_SEL           0x0044
#define REG_SC_SRST_REQ_CTRL          0x0048
#define REG_SC_CA_RST_CTRL            0x004C
#define REG_SC_WDG_RST_CTRL           0x0050
#define REG_SC_DDRC_DFI_RST_CTRL      0x0054
#define REG_SC_PLLLOCK_STAT           0x0070
#define REG_SC_GEN0                   0x0080
#define REG_SC_GEN1                   0x0084
#define REG_SC_GEN2                   0x0088
#define REG_SC_GEN3                   0x008C
#define REG_SC_GEN4                   0x0090
#define REG_SC_GEN5                   0x0094
#define REG_SC_GEN6                   0x0098
#define REG_SC_GEN7                   0x009C
#define REG_SC_GEN8                   0x00A0
#define REG_SC_GEN9                   0x00A4
#define REG_SC_GEN10                  0x00A8
#define REG_SC_GEN11                  0x00AC
#define REG_SC_GEN12                  0x00B0
#define REG_SC_GEN13                  0x00B4
#define REG_SC_GEN14                  0x00B8
#define REG_SC_GEN15                  0x00BC
#define REG_SC_LOCKEN                 0x020C
#define REG_SC_GEN16                  0x00C0
#define REG_SC_GEN17                  0x00C4
#define REG_SC_GEN18                  0x00C8
#define REG_SC_GEN19                  0x00CC
#define REG_SC_GEN20                  0x00D0
#define REG_SC_GEN21                  0x00D4
#define REG_SC_GEN22                  0x00D8
#define REG_SC_GEN23                  0x00DC
#define REG_SC_GEN24                  0x00E0
#define REG_SC_GEN25                  0x00e4
#define REG_SC_GEN26                  0x00e8
#define REG_SC_GEN27                  0x00ec
#define REG_SC_GEN28                  0x00F0
#define REG_SC_GEN29                  0x00F4
#define REG_SC_GEN30                  0x00F8
#define REG_SC_GEN31                  0x00FC

#define REG_KLD_BASE                  (0x10000000)
#define REG_KLD_DDRSCRAMBLE_EN        (REG_KLD_BASE + 0x178)

#define REG_DDRC_BASE                 (0x10100000)
#define REG_DDR_DMC0_LPCTRL           (REG_DDRC_BASE + 0x1028)

#define HI3716MV310_PERI_CRG26        (REG_BASE_CRG + 0x68)

#define HI3716MV310_PERI_CRG51        (REG_BASE_CRG + 0xcc)
#define HI3716MV310_PERI_CRG73        (REG_BASE_CRG + 0x120)
#define HI3716MV310_PERI_CRG90        (REG_BASE_CRG + 0x168)

#define HI3716MV310_PERI_FEPHY        (REG_BASE_PERI_CTRL + 0x118)
#define HI3716MV310_PERI_LDO_CTRL     (REG_BASE_PERI_CTRL + 0x11c)

#define HI3716MV310_PERI_SOC_FUSE_0    (0x840)
#define HI3716MV310_PERI_SOC_FUSE_MASK (0x1f << 16)

#define HISFV300_MAC0_PORTSEL         0x0200
#define REG_START_MODE                0x0000
#define REG_PERI_STAT                 0x0004
#define REG_PERI_CTRL                 0x0008
#define HI3716MV300_REG_PERI_CRG26    0x00A8
#define SCTL_REMAP_STAT               (1<<9)
#define NF_BOOTBW_MASK                (1<<12)

#define REG_TIMER_RELOAD              0x000
#define REG_TIMER_VALUE               0x004
#define REG_TIMER_CONTROL             0x008

#define MEM_BASE_BOOTRAM              0x00000000
#define MEM_SIZE_BOOTRAM              0x00001000

#define MEM_CONF_ITCM_SIZE            3
#define MEM_BASE_DDR                  0x80000000

#define DEFAULT_UART_CLK              54000000

#define BOOT_FROM_NANDR               0x8
#define BOOT_FROM_DDR                 0x4
#define BOOT_FROM_EMMC                0x3
#define BOOT_FROM_SPI_NAND            0x2
#define BOOT_FROM_NAND                0x1
#define BOOT_FROM_SPI                 0x0

#define REG_START_FLAG                (REG_BASE_SCTL + REG_SC_GEN12)
#define REG_USB_UART_FLAG             (REG_BASE_SCTL + REG_SC_GEN2)
#define CONFIG_START_MAGIC            (0x444f574e)
#define RAM_START_ADRS                0x10c00

#define HINFC504_BOOT_CFG             0xC4

#define REG_SC_SYSID0                 0x0EE0
#define REG_SC_SYSID1                 0x0EE4
#define REG_SC_SYSID2                 0x0EE8
#define REG_SC_SYSID3                 0x0EEC

#define REG_BASE_CA                    0x10000000

#define CA_CTRL_PROC                   0x78
#define CA_VENDOR_OFFSET               28
#define CA_VENDOR_MASK                 0x0f
#define CA_TYPE_NO_CA                  0
#define CA_TYPE_NAGRA                  1

#define HI3716MV300_CA_BASE                       0x10180000
#define HI3716MV300_CA_BASE_MAILBOX               0x84
#define HI3716MV300_CA_BASE_MAILBOX_ENABLE        1
#define HI3716MV300_CA_BASE_BOOT_SEL_CTRL         0x40000

#define HI3716MV300_BOOT_MODE_SEL                 0x80
#define HI3716MV300_BOOT_MODE_SEL_MASK            0x03

#define HI3716MV300_ECO_VERSION                   0x600c0a08
#define HI3716MV300_ECO_VERSION_OFFSET 24
#define HI3716MV300_ECO_VERSION_MASK   1
#define HI3716MV300_DDRPHY_REG81_REG              0x10100A04
#define HI3716MV300_DDRPHY_REG81_VAL   0x1e
#define HI3716MV300_DDRPHY_REGCA_REG              0x10100b28
#define HI3716MV300_DDRPHY_REGCA_VAL   0x0

#define HI3716MV310_CA_BASE                       0x10180000
#define HI3716MV310_BOOT_MODE_SEL                 0x80
#define HI3716MV310_BOOT_MODE_SEL_MASK            0x03

#define HI3716MV310_CA_BOOTSEL_CTRL               0x84
#define HI3716MV310_CA_BOOTSEL_CTRL_MASK          0x04

#define HI3716MV310_REG_OTP_ID_WORD               (HI3716MV300_CA_BASE + 0x128)
#define HI3716MV310_OTP_ID_WORD_VALUE_NORMAL      0x2A13C812
#define HI3716MV310_OTP_ID_WORD_VALUE_SECURE      0x6EDBE953

#define CA_BOOTMODE_OFFSET             2
#define CA_BOOTMODE_MASK               3
#define NORMAL_BOOTMODE_OFFSET         9
#define NORMAL_BOOTMODE_MASK           3
#define OTP_BOOTMODE_OFFSET            2
#define OTP_BOOTMODE_MASK              1
#define PIN_BOOTMODE_OFFSET            11
#define PIN_BOOTMODE_MASK              1
#define CA_SCS_MASK                    2

#define HI3712_BOOTMODE_OFFSET         10
#define HI3712_BOOTMODE_MASK           1
#define HI3712_OSC_FREQ                24000000

/*********************************************************************/
/*
 * 0x1-> init item1
 * 0x2-> init item2
 * 0x3->init item1 & item2
 */
#define INIT_REG_ITEM1               1
#define INIT_REG_ITEM2               2
#define INIT_REG_ITEM1_ITEM2         (INIT_REG_ITEM1 | INIT_REG_ITEM2)

/******************************************************************************/
#define WDG_LOAD                      (REG_BASE_WDG + 0x0000)
#define WDG_VALUE                     (REG_BASE_WDG + 0x0004)
#define WDG_CONTROL                   (REG_BASE_WDG + 0x0008)
#define WDG_LOCK                      (REG_BASE_WDG + 0x0c00)

#define WDG_ENABLE(_nn) do { \
	(*(volatile unsigned int *)(WDG_LOCK)    = (0x1ACCE551)); \
	(*(volatile unsigned int *)(WDG_LOAD)    = (_nn)); \
	(*(volatile unsigned int *)(WDG_CONTROL) = (0x3)); \
	(*(volatile unsigned int *)(WDG_LOCK)    = (0)); \
} while (0)

#define WDG_DISABLE() do { \
	(*(volatile unsigned int *)(WDG_LOCK)    = (0x1ACCE551)); \
	(*(volatile unsigned int *)(WDG_CONTROL) = (0)); \
	(*(volatile unsigned int *)(WDG_LOCK)    = (0)); \
} while (0)

#include <asm/platform_common.h>

#endif /*End of __HI_BOARD_H__ */


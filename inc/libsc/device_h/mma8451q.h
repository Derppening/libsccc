/*
 * mma8451q.h
 *
 *  Created on: Jan 16, 2015
 *      Author: Peter
 */

#pragma once

#define MMA8451Q_DEFAULT_ADDRESS        0x1C

// Registers
#define MMA8451Q_RA_REG_OUT_ALL            MMA8451Q_RA_REG_OUT_X_MSB
#define MMA8451Q_RA_REG_STATUS            0x00
#define MMA8451Q_RA_REG_OUT_X_MSB        0x01
#define MMA8451Q_RA_REG_OUT_X_LSB        0x02
#define MMA8451Q_RA_REG_OUT_Y_MSB        0x03
#define MMA8451Q_RA_REG_OUT_Y_LSB        0x04
#define MMA8451Q_RA_REG_OUT_Z_MSB        0x05
#define MMA8451Q_RA_REG_OUT_Z_LSB        0x06
#define MMA8451Q_RA_REG_SYSMOD         0x0B
#define MMA8451Q_RA_INT_SOURCE        0x0C
#define MMA8451Q_RA_REG_WHO_AM_I        0x0D
#define MMA8451Q_RA_XYZ_DATA_CFG        0x0E
#define MMA8451Q_RA_HP_FILTER_CUTOFF    0x0F
#define MMA8451Q_RA_FF_MT_CFG            0x15
#define MMA8451Q_RA_FF_MT_SRC            0x16
#define MMA8451Q_RA_FF_MT_THS            0x17
#define MMA8451Q_RA_FF_MT_COUNT            0x18
#define MMA8451Q_RA_PULSE_CFG            0x21
#define MMA8451Q_RA_PULSE_SRC            0x22
#define MMA8451Q_RA_PULSE_THSX        0x23
#define MMA8451Q_RA_PULSE_THSY        0x24
#define MMA8451Q_RA_PULSE_THSZ        0x25
#define MMA8451Q_RA_PULSE_TMLT        0x26
#define MMA8451Q_RA_PULSE_LTCY            0x27
#define MMA8451Q_RA_PULSE_WIND        0x28
#define MMA8451Q_RA_CTRL_REG1            0x2A
#define MMA8451Q_RA_CTRL_REG2            0x2B
#define MMA8451Q_RA_CTRL_REG4            0x2D
#define MMA8451Q_RA_CTRL_REG5            0x2E

//STATUS
#define MMA8451Q_S_ZYXOW                1<<7
#define MMA8451Q_S_ZOW                    1<<6
#define MMA8451Q_S_YOW                    1<<5
#define MMA8451Q_S_XOW                    1<<4
#define MMA8451Q_S_ZYXDR                1<<3
#define MMA8451Q_S_ZDR                    1<<2
#define MMA8451Q_S_YDR                    1<<1
#define MMA8451Q_S_XDR                    1<<0

// CTRL_REG_1
#define MMA8451Q_CR1_ASLP_RATE1            1<<7
#define MMA8451Q_CR1_ASLP_RATE2            1<<6
#define MMA8451Q_CR1_LNOISE                1<<2
#define MMA8451Q_CR1_F_READ                1<<1
#define MMA8451Q_CR1_F_ACTIVE            MMA8451Q_CR1_F_ACTIVE_MASK
#define MMA8451Q_CR1_F_ACTIVE_SHIFT        0
#define MMA8451Q_CR1_F_ACTIVE_MASK        0x1

// CTRL_REG_2
#define MMA8451Q_CR2_RST                1<<6
#define MMA8451Q_CR2_MODS1                1<<1
#define MMA8451Q_CR2_MODS0                1<<0

// CTRL_REG_4
#define MMA8451Q_CR4_INT_EN_ASLP        1<<7
#define MMA8451Q_CR4_INT_EN_FIFO        1<<6
#define MMA8451Q_CR4_INT_EN_TRANS        1<<5
#define MMA8451Q_CR4_INT_EN_LNDPRT        1<<4
#define MMA8451Q_CR4_INT_EN_PULSE        1<<3
#define MMA8451Q_CR4_INT_EN_FF_MT        1<<2
#define MMA8451Q_CR4_INT_EN_DRDY        1<<0

// CTRL_REG_5
#define MMA8451Q_CR5_INT_CFG_ASLP        1<<7
#define MMA8451Q_CR5_INT_CFG_FIFO        1<<6
#define MMA8451Q_CR5_INT_CFG_TRANS        1<<5
#define MMA8451Q_CR5_INT_CFG_LNDPRT        1<<4
#define MMA8451Q_CR5_INT_CFG_PULSE        1<<3
#define MMA8451Q_CR5_INT_CFG_FF_MT        1<<2
#define MMA8451Q_CR5_INT_CFG_DRDY        1<<0

// HP_FILTER_CUTOFF
#define MMA8451Q_HFC_PULSE_HPF_BYP        1<<5
#define MMA8451Q_HFC_PULSE_LPF_EN        1<<4
#define MMA8451Q_HFC_SEL1                1<<1
#define MMA8451Q_HFC_SEL0                1<<0

// XYZ_DATA_CFG
#define MMA8451Q_XDC_HPF_OUT            1<<4

// FF_MT_CFG
#define MMA8451Q_FMC_ELE                1<<7
#define MMA8451Q_FMC_OAE                1<<6
#define MMA8451Q_FMC_ZEFE                1<<5
#define MMA8451Q_FMC_YEFE                1<<4
#define MMA8451Q_FMC_XEFE                1<<3

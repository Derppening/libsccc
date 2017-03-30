/*
 * mma8451q.cpp
 *
 * Author: Petel__
 * Copyright (c) 2014-2016 HKUST SmartCar Team
 * Refer to LICENSE for details
 */

#include <cassert>
#include <cmath>
#include <cstdint>

#include <array>
#include <vector>

#include "libbase/log.h"
#include "libbase/helper.h"
#include LIBBASE_H(i2c_master)
#include LIBBASE_H(soft_i2c_master)

#include "libsc/config.h"
#include "libsc/device_h/mma8451q.h"
#include "libsc/mma8451q.h"
#include "libsc/system.h"
#include "libutil/math.h"
#include "libutil/misc.h"

using namespace LIBBASE_NS;
using namespace libutil;
using namespace std;

#define HALF_PI 1.57079633f

namespace libsc {

#ifdef LIBSC_USE_MMA8451Q

namespace
{

#if LIBSC_USE_MMA8451Q == 1
inline Pin::Name GetSclPin(const uint8_t id)
{
    if (id != 0)
    {
        assert(false);
    }
    return LIBSC_MMA8451Q0_SCL;
}

inline Pin::Name GetSdaPin(const uint8_t id)
{
    if (id != 0)
    {
        assert(false);
    }
    return LIBSC_MMA8451Q0_SDA;
}

#endif

Mma8451q::I2cMaster::Config GetI2cMasterConfig(const Mma8451q::Config &config)
{
    Mma8451q::I2cMaster::Config product;
    product.scl_pin = GetSclPin(config.id);
    product.sda_pin = GetSdaPin(config.id);
    product.baud_rate_khz = 400;
    product.scl_low_timeout = 1000;
#if !LIBSC_USE_SOFT_MMA8451Q
    product.min_scl_start_hold_time_ns = 600;
    product.min_scl_stop_hold_time_ns = 600;
#endif
    return product;
}

}

Mma8451q::Mma8451q(const Config &config)
        :
          m_sensitivity(config.sensitivity),
          m_scale_factor(1 << ((Byte)m_sensitivity + 0x0C)),
          m_last_accel{},
          m_last_angle{},
          m_last_accel_f{},
          m_last_angle_f{}
{

    if(!config.i2c_master_ptr){
        m_i2c_master = new I2cMaster(GetI2cMasterConfig(config));
    }else{
        m_i2c_master = config.i2c_master_ptr;
    }
    assert(Verify());
    System::DelayUs(1);

    SetActive(false);
    System::DelayUs(1);

    WriteRegByte(MMA8451Q_RA_REG_SYSMOD, 0x0);
    System::DelayUs(1);

    WriteRegByte(MMA8451Q_RA_XYZ_DATA_CFG, 2 - (Byte)config.sensitivity);
    System::DelayUs(1);

    WriteRegByte(MMA8451Q_RA_CTRL_REG2, (Byte)config.power_mode);
    System::DelayUs(1);
//
//	WriteRegByte(MMA8451Q_RA_CTRL_REG1, (Byte)config.output_data_rate << 3 | MMA8451Q_CR1_LNOISE);
    WriteRegByte(MMA8451Q_RA_CTRL_REG1, (Byte)config.output_data_rate << 3);
    System::DelayUs(1);

    SetActive(true);
    System::DelayUs(1);
}

bool Mma8451q::Verify()
{
    Byte who_am_i;
    if (!m_i2c_master->GetByte(MMA8451Q_DEFAULT_ADDRESS, MMA8451Q_RA_REG_WHO_AM_I,
            &who_am_i))
    {
        return false;
    }
    else
    {
        return (who_am_i == 0x1A);
    }
}

bool Mma8451q::Update()
{
    if (ReadRegByte(MMA8451Q_RA_REG_STATUS) & MMA8451Q_S_ZYXDR)
    {
        GetAllAccel();
//		GetAllAngle();
        return true;
    }
    return false;
}

bool Mma8451q::UpdateF()
{
    if (ReadRegByte(MMA8451Q_RA_REG_STATUS) & MMA8451Q_S_ZYXDR)
    {
        GetAllAccelF();
//		GetAllAngle();
        return true;
    }
    return false;
}

void Mma8451q::GetAllAccel()
{
    const vector<Byte> &data = m_i2c_master->GetBytes(MMA8451Q_DEFAULT_ADDRESS,
            MMA8451Q_RA_REG_OUT_ALL, 0x06);
    if (data.empty())
    {
        LOG_W("MMA8451Q Failed reading 0x%X", MMA8451Q_RA_REG_OUT_ALL);
        return;
    }

    for (int i = 0, j = 0; i < 3; i++, j += 2)
        m_last_accel[i] = (int16_t)(data[j] << 8 | data[j + 1]);

//	const vector<Byte> &data = m_i2c_master->GetBytes(MMA8451Q_DEFAULT_ADDRESS,
//			MMA8451Q_RA_REG_OUT_Y_MSB, 2);
//	if (data.empty())
//	{
//		LOG_W("MMA8451Q Failed reading 0x%X", MMA8451Q_RA_REG_OUT_ALL);
//		return;
//	}
//
////	for (int i = 0, j = 0; i < 3; i++, j += 2)
////	{
//		m_last_accel_f[1] = (int16_t)(data[0] << 8 | data[1]) / m_scale_factor;
////	}
}

void Mma8451q::GetAllAccelF()
{
    const vector<Byte> &data = m_i2c_master->GetBytes(MMA8451Q_DEFAULT_ADDRESS,
            MMA8451Q_RA_REG_OUT_ALL, 0x06);
    if (data.empty())
    {
        LOG_W("MMA8451Q Failed reading 0x%X", MMA8451Q_RA_REG_OUT_ALL);
        return;
    }

    for (int i = 0, j = 0; i < 3; i++, j += 2)
        m_last_accel_f[i] = (int16_t)(data[j] << 8 | data[j + 1]) / (float)m_scale_factor;
}

void Mma8451q::GetAllAngle()
{
    for (int j = 0; j < 3; j++)
    {
        const float factor = m_last_accel_f[(j + 1) % 3] * m_last_accel_f[(j + 1) % 3]
                + m_last_accel_f[(j + 2) % 3] * m_last_accel_f[(j + 2) % 3];
        m_last_angle_f[j] = Math::ArcTan(m_last_accel_f[j] / Math::Sqrt2(factor));
        if (!isfinite(m_last_angle_f[j]))
            m_last_angle_f[j] = HALF_PI;
    }
    m_last_angle_f[2] -= HALF_PI * ((m_last_accel_f[2] < 0)? -1 : 1);
}

void Mma8451q::SetActive(const bool flag)
{
    uint8_t reg = ReadRegByte(MMA8451Q_RA_CTRL_REG1);
    if (flag)
    {
        SET_BIT(reg, MMA8451Q_CR1_F_ACTIVE_SHIFT);
    }
    else
    {
        CLEAR_BIT(reg, MMA8451Q_CR1_F_ACTIVE_SHIFT);
    }

    WriteRegByte(MMA8451Q_RA_CTRL_REG1, reg);
}

Byte Mma8451q::ReadRegByte(const Byte reg)
{
    Byte data = 0;
    if (!m_i2c_master->GetByte(MMA8451Q_DEFAULT_ADDRESS, reg, &data))
    {
        printf("MMA8451Q Failed reading 0x%X", reg);
    }
    return data;
}

void Mma8451q::WriteRegByte(const Byte reg, const Byte data)
{
    if (!m_i2c_master->SendByte(MMA8451Q_DEFAULT_ADDRESS, reg, data))
    {
        printf("MMA8451Q Failed sending 0x%X", reg);
    }
}

#else
Mma8451q::Mma8451q(const Config&)
    : m_i2c_master(nullptr), m_sensitivity(Config::Sensitivity::kHigh),
      m_scale_factor(0.0f) {
  LOG_DL("Configured not to use Mma8451q");
}
bool Mma8451q::Update() { return false; }

#endif

}

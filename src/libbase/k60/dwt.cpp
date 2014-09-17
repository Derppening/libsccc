/*
 * dwt.cpp
 *
 * Author: Ming Tsang
 * Copyright (c) 2014 HKUST SmartCar Team
 */

#include "libbase/k60/hardware.h"

#include <cassert>
#include <cstdint>

#include "libbase/k60/clock_utils.h"
#include "libbase/k60/dwt.h"
#include "libbase/k60/misc_utils.h"

namespace libbase
{
namespace k60
{

void Dwt::DelayUs(const uint16_t us)
{
	if (GET_BIT(DWT->CTRL, DWT_CTRL_NOCYCCNT_Pos))
	{
		// CYCCNT not implemented
		assert(false);
		return;
	}

	SET_BIT(DWT->CTRL, DWT_CTRL_CYCCNTENA_Pos);
	const uint32_t count = ClockUtils::GetCoreTickPerUs(us);
	DWT->CYCCNT = 0;
	while (DWT->CYCCNT < count)
	{}
}

}
}

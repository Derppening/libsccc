/*
 * simple_buzzer.h
 * Simple Buzzer
 *
 * Author: Ming Tsang
 * Copyright (c) 2014 HKUST SmartCar Team
 */

#pragma once

#include <cstdint>

#include "libbase/k60/gpio.h"

namespace libsc
{
namespace k60
{

class SimpleBuzzer
{
public:
	struct Config
	{
		uint8_t id;
		bool is_active_high;
	};

	explicit SimpleBuzzer(const Config &config);

	void SetBeep(const bool is_beep);
	bool GetBeep() const;

private:
	libbase::k60::Gpo m_pin;
	bool m_is_active_high;
};

}
}

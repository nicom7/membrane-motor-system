#pragma once

#include <Arduino.h>

struct DigitalEventData
{
	static constexpr int SIZE = 2;

	byte code = 0;
	bool value = false;
};

struct AnalogEventData
{
	static constexpr int SIZE = 5;

	int32_t value = 0;
	byte code = 0;
};

typedef AnalogEventData EventData;

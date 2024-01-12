#pragma once

#include "utils/event_data.h"

struct SerialPacket
{
	static constexpr int SIZE = AnalogEventData::SIZE + 1;

	AnalogEventData eventData;
	char channel = 0;
};

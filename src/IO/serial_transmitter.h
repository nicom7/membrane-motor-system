#pragma once

#include "serial_packet.h"
#include "utils/updatable.h"
#include "utils/led.h"
#include <Arduino.h>

class SerialTransmitter : public IUpdatable
{
public:
	SerialTransmitter(arduino::HardwareSerial& serialInterface);
	virtual ~SerialTransmitter();

	void writeSerial(const SerialPacket& packet);

	void setup(unsigned long baudRate);
	void update(int deltaTime) override;

private:
	arduino::HardwareSerial* m_serialInterface = nullptr;

	// Activity LED blinking period in ms
	static constexpr unsigned int ACTIVITY_LED_BLINK_PERIOD = 100;
	// Activity LED blinking duration in ms
	static constexpr unsigned int ACTIVITY_LED_BLINK_DURATION = 1000;

	// Activity LED: Will blink when receiving data for this channel
	LED m_activityLED;
};

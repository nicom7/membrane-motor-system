#include "serial_transmitter.h"

#include <Arduino.h>

SerialTransmitter::SerialTransmitter(arduino::HardwareSerial& serialInterface)
	: m_serialInterface(&serialInterface)
{
}

SerialTransmitter::~SerialTransmitter()
{
}

void SerialTransmitter::writeSerial(const SerialPacket& packet)
{
	if (m_serialInterface)
	{
		m_activityLED.blink(ACTIVITY_LED_BLINK_PERIOD, ACTIVITY_LED_BLINK_DURATION);

		m_serialInterface->write(packet.channel);
		m_serialInterface->write(packet.eventData.code);
		m_serialInterface->write((const char*)&packet.eventData.value, sizeof(packet.eventData.value));
	}
}

void SerialTransmitter::setup(unsigned long baudRate)
{
	m_serialInterface->begin(baudRate);
	m_activityLED.setup();

}

void SerialTransmitter::update(int deltaTime)
{
	m_activityLED.update(deltaTime);
}

#include "serial_receiver.h"

#include "serial_packet.h"
#include <Arduino.h>

SerialReceiver::SerialReceiver(arduino::HardwareSerial& serialInterface, byte channel)
	: m_serialInterface(&serialInterface)
	, m_channel(channel)
{
	for (byte i = 0; i < MAX_OBSERVERS; i++)
	{
		m_analogObservers[i] = nullptr;
	}
}

SerialReceiver::SerialReceiver(const SerialReceiver& other)
	: m_serialInterface(other.m_serialInterface)
	, m_channel(other.m_channel)
	, m_numAnalogObservers(other.m_numAnalogObservers)
{
	for (byte i = 0; i < MAX_OBSERVERS; i++)
	{
		m_analogObservers[i] = other.m_analogObservers[i];
	}
}

bool SerialReceiver::readSerial(SerialPacket& packet)
{
	if (m_serialInterface && m_serialInterface->available() >= packet.SIZE)
	{

		packet.channel = m_serialInterface->read();
		packet.eventData.code = m_serialInterface->read();
		m_serialInterface->readBytes((char*)&packet.eventData.value, sizeof(packet.eventData.value));

		return true;
	}

	return false;
}

void SerialReceiver::add(IObserver<AnalogEventData>& observer)
{
	m_analogObservers[m_numAnalogObservers] = &observer;
	m_numAnalogObservers = (m_numAnalogObservers + 1) % MAX_OBSERVERS;
}

void SerialReceiver::update(int deltaTime)
{
	SerialPacket packet;
	while (readSerial(packet))
	{
		if (packet.channel == m_channel)
		{
			m_activityLED.blink(ACTIVITY_LED_BLINK_PERIOD, ACTIVITY_LED_BLINK_DURATION);

		#if MMS_DEBUG_SERIAL
			Serial.print("received event: ");
			Serial.print(packet.eventData.code);
			Serial.print(" ");
			Serial.println(packet.eventData.value);
		#endif
			notify(packet.eventData);
		}
	}

	m_activityLED.update(deltaTime);
}

void SerialReceiver::setup(unsigned long baudRate)
{
	m_serialInterface->begin(baudRate);
	m_activityLED.setup();
}

void SerialReceiver::notify(const AnalogEventData& data)
{
	for (byte i = 0; i < m_numAnalogObservers; i++)
	{
		m_analogObservers[i]->update(data);
	}
}

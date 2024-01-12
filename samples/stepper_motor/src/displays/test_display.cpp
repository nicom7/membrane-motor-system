#include "test_display.h"

TestDisplay::TestDisplay(const byte analogOutputPins[], byte numAnalogOutputs, const byte digitalOutputPins[], byte numDigitalOutputs)
	: m_analogOutputPins(analogOutputPins)
	, m_numAnalogOutputs(numAnalogOutputs)
	, m_digitalOutputPins(digitalOutputPins)
	, m_numDigitalOutputs(numDigitalOutputs)
{
}

TestDisplay::~TestDisplay()
{
}

void TestDisplay::setup()
{
	for (byte i = 0; i < m_numAnalogOutputs; i++)
	{
		pinMode(m_analogOutputPins[i], OUTPUT);
	}

	for (byte i = 0; i < m_numDigitalOutputs; i++)
	{
		pinMode(m_digitalOutputPins[i], OUTPUT);
	}
}

void TestDisplay::update(const AnalogEventData& data)
{
	if (data.code < m_numAnalogOutputs)
	{
		analogWrite(m_analogOutputPins[data.code], map(data.value, 0, 1023, 0, 255));
	}
}

void TestDisplay::update(const DigitalEventData& data)
{
	if (data.code < m_numDigitalOutputs)
	{
		digitalWrite(m_digitalOutputPins[data.code], data.value);
	}
}

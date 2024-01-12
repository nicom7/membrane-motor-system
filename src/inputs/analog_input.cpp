#include "analog_input.h"

#include <Arduino.h>

AnalogInput::AnalogInput(const byte inputPin, const byte inputCode)
	: Input(inputPin, inputCode)
{
}

AnalogInput::AnalogInput(const AnalogInput& other)
	: Input(other)
{
}

AnalogInput::~AnalogInput()
{
}

void AnalogInput::setup()
{
	setupInput();
}

void AnalogInput::setupInput()
{
	pinMode(m_inputPin, INPUT);
}

void AnalogInput::update(int /*deltaTime*/)
{
	updateInput();
}

unsigned int AnalogInput::getCurrentValue() const
{
	return m_curInputValue;
}

void AnalogInput::updateInput()
{
	m_curInputValue = analogRead(m_inputPin);

	if (m_prevInputValue != m_curInputValue)
	{
		// Input value has changed
		handleInput();

		m_prevInputValue = m_curInputValue;
	}
}

void AnalogInput::handleInput()
{
	AnalogEventData data;
	data.code = m_inputCode;
	data.value = (int32_t)m_curInputValue;

#if MMS_DEBUG_INPUTS
	Serial.print("input ");
	Serial.print(data.code);
	Serial.print(" ");
	Serial.println(data.value);
#endif

	notify(data);
}

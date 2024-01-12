#include "digital_input.h"

#include <Arduino.h>

DigitalInput::DigitalInput(const byte inputPin, const byte inputCode, int holdTime, bool pullUp)
	: Input(inputPin, inputCode)
	, m_holdTime(holdTime)
	, m_pullUp(pullUp)
{
}

DigitalInput::DigitalInput(const DigitalInput& other)
	: Input(other)
	, m_holdTime(other.m_holdTime)
	, m_pullUp(other.m_pullUp)
{
}

DigitalInput::~DigitalInput()
{
}

void DigitalInput::setup()
{
	setupInput(m_pullUp);
}

void DigitalInput::setupInput(bool pullUp)
{
	pinMode(m_inputPin, pullUp ? INPUT_PULLUP : INPUT);

#if MMS_DEBUG_INPUTS
	Serial.print("setup input ");
	Serial.println(m_inputCode);
#endif
}

void DigitalInput::update(int deltaTime)
{
	updateInput(deltaTime);
}

unsigned int DigitalInput::getCurrentValue() const
{
	return (m_curInputValue == LOW ? 1 : 0);
}

DigitalInput::DigitalInputState DigitalInput::getCurrentState() const
{
	return m_curState;
}

void DigitalInput::updateInput(int deltaTime)
{
	updateDebounce(deltaTime);

	bool pressed = getCurrentValue();
	bool held = pressed && m_holdTime >= 0 && m_holdTimer > m_holdTime;

	if (m_prevInputValue != m_curInputValue || held)
	{
		DigitalInputState prevState = m_curState;
		m_curState = held ? DS_HELD : (pressed ? DS_PRESSED : DS_RELEASED);

		if (m_curState != prevState)
		{
			// Button has been pressed/held (LOW) or released (HIGH)
			handleInput(m_curState);

			m_prevInputValue = m_curInputValue;
		}
	}

	if (pressed)
	{
		// Increase hold timer
		m_holdTimer += deltaTime;
	}
	else
	{
		// Reset hold timer
		m_holdTimer = 0;
	}
}

void DigitalInput::updateDebounce(int deltaTime)
{
	PinStatus pinStatus = digitalRead(m_inputPin);

	if (m_debounceTimer >= 0 && m_debounceTimer < DEBOUNCE_TIME)
	{
		m_debounceTimer += deltaTime;
	}

	if (pinStatus != m_prevInputValue)
	{
		if (m_debounceTimer < 0)
		{
			m_debounceTimer = 0;
		}
	}
	else
	{
		m_debounceTimer = -1;
	}

	if (m_debounceTimer >= DEBOUNCE_TIME)
	{
		m_curInputValue = pinStatus;
	}
}

void DigitalInput::handleInput(DigitalInputState state)
{
	EventData data;
	data.code = m_inputCode;
	data.value = state;

#if MMS_DEBUG_INPUTS
	Serial.print("input ");
	Serial.print(data.code);
	Serial.print(" ");
	Serial.println(state == DS_HELD ? "held" : (state == DS_PRESSED ? "pressed" : "released"));
#endif

	notify(data);
}

#include "input_manager.h"

#include "digital_input.h"
#include "analog_input.h"

#include <Arduino.h>

InputManager::InputManager(const byte maxInputs)
	: m_maxInputs(maxInputs)
{
	if (m_maxInputs > 0)
	{
		m_inputs = new Input * [m_maxInputs];

		for (int i = 0; i < m_maxInputs; i++)
		{
			m_inputs[i] = nullptr;
		}
	}
}

InputManager::~InputManager()
{
	if (m_inputs)
	{
		for (int i = 0; i < m_maxInputs; i++)
		{
			if (m_inputs[i])
			{
				delete m_inputs[i];
			}
		}
		delete[] m_inputs;
	}
}

void InputManager::setup(IObserver<EventData>& observer)
{
	m_observer = &observer;
}

void InputManager::update(int deltaTime)
{
	for (int i = 0; i < m_maxInputs; i++)
	{
		if (m_inputs[i])
		{
			m_inputs[i]->update(deltaTime);
		}
	}
}

void InputManager::addDigitalInput(byte inputPin, byte inputCode, int holdTime, bool pullUp)
{
	if (inputCode < m_maxInputs)
	{
		if (m_inputs[inputCode])
		{
			delete m_inputs[inputCode];
		}

		m_inputs[inputCode] = new DigitalInput(inputPin, inputCode, holdTime, pullUp);
		setupInput(inputCode);
	}
}

void InputManager::addAnalogInput(byte inputPin, byte inputCode)
{
	if (inputCode < m_maxInputs)
	{
		if (m_inputs[inputCode])
		{
			delete m_inputs[inputCode];
		}

		m_inputs[inputCode] = new AnalogInput(inputPin, inputCode);
		setupInput(inputCode);
	}
}

void InputManager::setupInput(byte inputCode)
{
	m_inputs[inputCode]->setup();
	if (m_observer)
	{
		m_inputs[inputCode]->add(*m_observer);
	}
}

unsigned int InputManager::getCurrentValue(byte inputCode) const
{
	return (inputCode < m_maxInputs && m_inputs[inputCode]) ?
		m_inputs[inputCode]->getCurrentValue() : DigitalInput::DS_RELEASED;
}

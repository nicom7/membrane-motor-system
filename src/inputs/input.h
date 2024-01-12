#pragma once

#include "utils/abstract_observable.h"
#include "utils/updatable.h"

class Input : public AbstractObservable<EventData>, public IUpdatable
{
public:
	Input(byte inputPin, byte inputCode)
		: AbstractObservable<EventData>(), m_inputPin(inputPin), m_inputCode(inputCode) {}
	Input(const Input& other)
		: AbstractObservable<EventData>(other), m_inputPin(other.m_inputPin), m_inputCode(other.m_inputCode) {}
	virtual ~Input() {}

	virtual void setup() = 0;
	virtual unsigned int getCurrentValue() const = 0;

protected:
	const byte m_inputPin = 0;
	const byte m_inputCode = 0;
};

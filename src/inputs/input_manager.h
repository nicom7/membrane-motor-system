#pragma once

#include "input.h"
#include "digital_input.h"
#include "utils/updatable.h"
#include "utils/observer.h"
#include "utils/utils.h"

class InputManager : public IUpdatable
{
public:
	InputManager(const byte maxInputs = DEFAULT_MAX_INPUTS);
	virtual ~InputManager();

	void setup(IObserver<EventData>& observer);
	void update(int deltaTime) override;

	void addDigitalInput(byte inputPin, byte inputCode, int holdTime = -1, bool pullUp = true);
	void addAnalogInput(byte inputPin, byte inputCode);

	unsigned int getCurrentValue(byte inputCode) const;

private:
	void setupInput(byte inputCode);

	static constexpr byte DEFAULT_MAX_INPUTS = 32;

	const byte m_maxInputs = 0;
	byte m_numInputs = 0;
	Input** m_inputs = nullptr;

	IObserver<EventData>* m_observer = nullptr;
};

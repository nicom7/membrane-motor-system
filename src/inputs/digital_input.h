#pragma once

#include "input.h"
#include "utils/utils.h"

class DigitalInput : public Input
{
public:
	enum DigitalInputState
	{
		DS_RELEASED = 0,
		DS_PRESSED,
		DS_HELD,

		DS_COUNT
	};

	DigitalInput(const byte inputPin, const byte inputCode, int holdTime = -1, bool pullUp = true);
	DigitalInput(const DigitalInput& other);
	virtual ~DigitalInput();

	void setup() override;
	void update(int deltaTime) override;

	unsigned int getCurrentValue() const override;
	DigitalInputState getCurrentState() const;

	static constexpr int DEFAULT_HOLD_TIME = 1 * MSEC_PER_SEC;	// Consider input hold after more than 1 second (set to -1 to disable hold repeat)

private:
	void setupInput(bool pullup);
	void updateInput(int deltaTime);
	void updateDebounce(int deltaTime);
	void handleInput(DigitalInputState state);

	PinStatus m_prevInputValue = HIGH;
	PinStatus m_curInputValue = HIGH;
	DigitalInputState m_curState = DS_RELEASED;

	const int m_holdTime = DEFAULT_HOLD_TIME;
	int m_holdTimer = 0;

	static constexpr int DEBOUNCE_TIME = 5;
	int m_debounceTimer = -1;

	bool m_pullUp = true;
};

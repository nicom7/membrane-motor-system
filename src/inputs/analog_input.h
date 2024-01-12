#pragma once

#include "input.h"

class AnalogInput : public Input
{
public:
	AnalogInput(const byte inputPin, const byte inputCode);
	AnalogInput(const AnalogInput& other);
	virtual ~AnalogInput();

	void setup() override;
	void update(int deltaTime) override;

	unsigned int getCurrentValue() const override;

private:
	void setupInput();
	void updateInput();
	void handleInput();

	unsigned int m_prevInputValue = 0;
	unsigned int m_curInputValue = 0;
};

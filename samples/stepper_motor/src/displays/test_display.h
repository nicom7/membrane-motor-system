#pragma once

#include "utils/observer.h"

class TestDisplay : public IObserver<AnalogEventData>, public IObserver<DigitalEventData>
{
public:
	TestDisplay(const byte analogOutputPins[] = nullptr, byte numAnalogOutputs = 0, const byte digitalOutputPins[] = nullptr, byte numDigitalOutputs = 0);
	virtual ~TestDisplay();

	void setup();
	void update(const AnalogEventData& data) override;
	void update(const DigitalEventData& data) override;

private:
	const byte* m_analogOutputPins = nullptr;
	byte m_numAnalogOutputs = 0;

	const byte* m_digitalOutputPins = nullptr;
	byte m_numDigitalOutputs = 0;
};

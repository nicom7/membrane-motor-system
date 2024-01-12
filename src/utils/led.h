#pragma once

#include <Arduino.h>
#include "utils/updatable.h"

class LED : public IUpdatable
{
public:
	LED();
	~LED();

	void setup();
	void update(int deltaTime) override;

	void blink(unsigned int period = DEFAULT_PERIOD, unsigned int duration = DEFAULT_DURATION);

private:
	void toggle();
	void setState(bool on);

	static constexpr unsigned int DEFAULT_PERIOD = 1000; // Blinking period in ms. Set to 0 for always on.
	static constexpr unsigned int DEFAULT_DURATION = 0;	 // Blink duration in ms. Set to 0 for infinite blinking.
	static constexpr pin_size_t DEFAULT_PIN = LED_BUILTIN;

	unsigned int m_period = DEFAULT_PERIOD;
	unsigned int m_duration = 1;

	unsigned int m_timer = 0;
	unsigned int m_durationTimer = 1;
	bool m_state = false;
};

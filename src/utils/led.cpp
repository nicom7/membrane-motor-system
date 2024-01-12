#include "led.h"

LED::LED()
{
}

LED::~LED()
{
}

void LED::setup()
{
	static bool setupDone = false;
	if (!setupDone)
	{
		pinMode(DEFAULT_PIN, OUTPUT);
		setupDone = true;
	}
}

void LED::update(int deltaTime)
{
	if (m_duration == 0 || m_durationTimer < m_duration)
	{
		if (m_period != 0)
		{
			m_timer += deltaTime;
			if (m_timer >= m_period)
			{
				toggle();
				m_timer -= m_period;
			}
		}
		m_durationTimer += deltaTime;
	}
	else
	{
		setState(false);
	}
}

void LED::blink(unsigned int period, unsigned int duration)
{
	m_period = period;
	m_duration = duration;
	m_durationTimer = 0;
	m_timer = 0;
	setState(true);
}

void LED::toggle()
{
	setState(!m_state);
}

void LED::setState(bool on)
{
	if (on != m_state)
	{
		m_state = on;
		digitalWrite(DEFAULT_PIN, m_state ? HIGH : LOW);
	}
}

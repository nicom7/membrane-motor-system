#include "abstract_board_controller.h"

void AbstractBoardController::setup()
{
	m_prevUpdateTime = millis();
	m_heartbeatLED.setup();
	m_heartbeatLED.blink();
}

void AbstractBoardController::loop()
{
	unsigned long curTime = millis();
	int deltaTime = 0;

	// Prevent negative dt
	if (m_prevUpdateTime <= curTime)
	{
		deltaTime = curTime - m_prevUpdateTime;
	}
	m_prevUpdateTime = curTime;

	update(deltaTime);
	m_heartbeatLED.update(deltaTime);
}

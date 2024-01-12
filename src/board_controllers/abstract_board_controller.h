#pragma once

#include <Arduino.h>
#include "board_controllers/board_controller.h"
#include "utils/updatable.h"
#include "utils/led.h"

class AbstractBoardController : public IBoardController, public IUpdatable
{
public:
	// Inherited via IBoardController
	void setup() override;
	void loop() override final;

	virtual void setup1() {};
	virtual void loop1() {};

private:
	LED m_heartbeatLED;

	unsigned long m_prevUpdateTime = 0;
};

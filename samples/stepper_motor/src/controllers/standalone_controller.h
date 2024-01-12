#pragma once

#include <Arduino.h>
#include "board_controllers/abstract_board_controller.h"
#include "inputs/input_manager.h"
#include "utils/observer.h"
#include "stepper_motor_controller.h"
#include "displays/motor_state_display.h"
#include "events/input.h"

class StandaloneController : public AbstractBoardController, public IObserver<EventData>
{
public:
	StandaloneController(byte motorEnablePin, const byte motorInputPins[4]);
	virtual ~StandaloneController();

	// Inherited via IBoardController
	void setup() override;

protected:
	void update(const EventData& data) override;
	void update(int deltaTime) override;

private:
	static constexpr int INPUT_STEPS = 10;	// Number of steps per button press

	InputManager m_inputManager;
	StepperMotorController m_motorController;
	MotorStateDisplay m_display;

	static constexpr unsigned int UPDATE_PERIOD = DEFAULT_UPDATE_PERIOD;	// Update period in ms

	unsigned int m_updateTimer = 0;
};

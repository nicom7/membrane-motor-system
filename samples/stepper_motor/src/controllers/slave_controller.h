#pragma once

#include <Arduino.h>
#include "board_controllers/abstract_board_controller.h"
#include "utils/observer.h"
#include "inputs/input_manager.h"
#include "stepper_motor_controller.h"
#include "displays/motor_state_display.h"
#include "IO/serial_receiver.h"
#include "events/input.h"

class SlaveController : public AbstractBoardController, public IObserver<EventData>
{
public:
	SlaveController(byte motorEnablePin, const byte motorInputPins[4], arduino::HardwareSerial& serialInterface, TwoWire& displayInterface = Wire);
	virtual ~SlaveController();

	void addDigitalInput(byte inputPin, byte inputCode, int holdTime = -1, bool pullUp = true);
	void addAnalogInput(byte inputPin, byte inputCode);

	// Inherited via IBoardController
	void setup() override;
	void setup1() override;
	void loop1() override final;

protected:
	void update(const EventData& data) override;
	void update(int deltaTime) override;

private:
	TwoWire& m_displayInterface;
	StepperMotorController m_motorController;
	MotorStateDisplay m_display;
	SerialReceiver m_serialReceiver;
	InputManager m_inputManager;

	static constexpr unsigned long BAUD_RATE = DEFAULT_BAUD_RATE;
	static constexpr unsigned int UPDATE_PERIOD = DEFAULT_UPDATE_PERIOD;	// Update period in ms

	unsigned int m_updateTimer = 0;
};

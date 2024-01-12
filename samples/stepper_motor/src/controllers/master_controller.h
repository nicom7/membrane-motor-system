#pragma once

#include <Arduino.h>
#include "board_controllers/abstract_board_controller.h"
#include "utils/observer.h"
#include "inputs/input_manager.h"
#include "IO/serial_transmitter.h"
#include "events/input.h"

class MasterController : public AbstractBoardController, public IObserver<EventData>
{
public:
	MasterController(arduino::HardwareSerial& serialInterface);
	virtual ~MasterController();

	void addDigitalInput(byte inputPin, byte inputCode, int holdTime = -1, bool pullUp = true);
	void addAnalogInput(byte inputPin, byte inputCode);

	// Inherited via IBoardController
	void setup() override;

protected:
	void update(const EventData& data) override;
	void update(int deltaTime) override;

	void sendData(byte code, int32_t value = 0);

private:
	static constexpr int INPUT_STEPS = 10;	// Number of steps per button press

	InputManager m_inputManager;
	SerialTransmitter m_serialTransmitter;

	static constexpr unsigned long BAUD_RATE = DEFAULT_BAUD_RATE;
	static constexpr unsigned int UPDATE_PERIOD = DEFAULT_UPDATE_PERIOD;	// Update period in ms
	
	static constexpr unsigned int MOTOR_ROTATION_SPEED = FULL_ROTATION * 0.02;	// 4 rotations per second

	unsigned int m_updateTimer = 0;
};

#include "slave_controller.h"

#include "utils/utils.h"
#include "events/serial_code.h"
#include "IO/serial_packet.h"

SlaveController::SlaveController(byte motorEnablePin, const byte motorInputPins[4], arduino::HardwareSerial& serialInterface, TwoWire& displayInterface)
	: AbstractBoardController()
	, m_displayInterface(displayInterface)
	, m_motorController(motorEnablePin, motorInputPins)
	, m_display(m_motorController.getTotalSteps())
	, m_serialReceiver(serialInterface)
{
}

SlaveController::~SlaveController()
{
}

void SlaveController::addDigitalInput(byte inputPin, byte inputCode, int holdTime, bool pullUp)
{
	m_inputManager.addDigitalInput(inputPin, inputCode, holdTime, pullUp);
}

void SlaveController::addAnalogInput(byte inputPin, byte inputCode)
{
	m_inputManager.addAnalogInput(inputPin, inputCode);
}

void SlaveController::setup()
{
	AbstractBoardController::setup();

	Serial.begin(BAUD_RATE);

	m_motorController.setup();

	m_serialReceiver.setup(BAUD_RATE);
	m_serialReceiver.add(*this);

	m_inputManager.setup(*this);
}

void SlaveController::setup1()
{
	m_display.setup(m_displayInterface);
}

void SlaveController::update(const EventData& data)
{
	switch (data.code)
	{
	case SC_MOVE:
	{
		// Prevent setting a target position beyond origin position
		long newPosition = m_motorController.getTargetPosition() + data.value;
		if (!m_inputManager.getCurrentValue(IN_SENSOR_DETECTED) || newPosition >= 0)
		{
			m_motorController.setTargetPosition(newPosition);
		}
		break;
	}
	case IN_TOGGLE_MOTOR:
	case SC_SET_ENABLED:
	{
		m_motorController.setMotorEnabled(data.value != 0);
		break;
	}
	case SC_RESET:
	{
		m_motorController.reset();
		break;
	}
	case SC_SET_POSITION:
	{
		m_motorController.setTargetPosition(data.value);
		break;
	}
	case SC_SET_ANGLE:
	{
		m_motorController.setTargetAngle(data.value);
		break;
	}
	case SC_SET_SPEED:
	{
		m_motorController.setMaxSpeed(data.value);
		break;
	}
	case SC_SET_ANGULAR_SPEED:
	{
		m_motorController.setMaxAngularSpeed(data.value);
		break;
	}
	case SC_SET_DIRECTION:
	{
		m_motorController.setDirection((Direction)data.value);
		break;
	}
	case SC_START:
	{
		m_motorController.start();
		break;
	}
	case SC_STOP:
	{
		m_motorController.stop();
		break;
	}
	case SC_SET_ORIGIN:
	{
		m_motorController.setOrigin();
		break;
	}
	case IN_SENSOR_DETECTED:
	{
		if (data.value == DigitalInput::DS_PRESSED)
		{
			m_motorController.setOrigin();
		}
		break;
	}
	default:
		break;
	}
}

void SlaveController::update(int deltaTime)
{
	m_updateTimer += deltaTime;

	if (m_updateTimer >= UPDATE_PERIOD)
	{
		m_inputManager.update(m_updateTimer);
		m_motorController.update();

		m_updateTimer = 0;
	}

	m_serialReceiver.update(deltaTime);

	m_motorController.run();
}

void SlaveController::loop1()
{
	m_display.setTargetPosition(m_motorController.getTargetPosition());
	m_display.setCurrentPosition(m_motorController.getCurrentPosition());
	m_display.setEnabled(m_motorController.isMotorEnabled());
	m_display.update(0);
}

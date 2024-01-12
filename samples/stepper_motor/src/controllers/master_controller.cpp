#include "master_controller.h"

#include "utils/utils.h"
#include "events/serial_code.h"

MasterController::MasterController(arduino::HardwareSerial& serialInterface)
	: AbstractBoardController()
	, m_serialTransmitter(serialInterface)
{
}

MasterController::~MasterController()
{
}

void MasterController::addDigitalInput(byte inputPin, byte inputCode, int holdTime, bool pullUp)
{
	m_inputManager.addDigitalInput(inputPin, inputCode, holdTime, pullUp);
}

void MasterController::addAnalogInput(byte inputPin, byte inputCode)
{
	m_inputManager.addAnalogInput(inputPin, inputCode);
}

void MasterController::setup()
{
	AbstractBoardController::setup();

	Serial.begin(BAUD_RATE);

	m_inputManager.setup(*this);

	m_serialTransmitter.setup(BAUD_RATE);
}

void MasterController::update(const EventData& data)
{
	const int speed = MOTOR_ROTATION_SPEED;
	const Direction dir = DI_SHORTEST_PATH;
	const int moveSteps = 1;
	bool pressed = data.value == DigitalInput::DS_PRESSED;
	bool held = data.value == DigitalInput::DS_HELD;

	switch (data.code)
	{
	case IN_MOVE_COUNTER_CLOCKWISE:
	{
		if (pressed)
		{
			sendData(SC_SET_ANGULAR_SPEED, speed);
			sendData(SC_MOVE, -moveSteps);
		}
		else if (held)
		{
			sendData(SC_SET_ANGULAR_SPEED, speed);
			sendData(SC_SET_DIRECTION, DI_COUNTER_CLOCKWISE);
			sendData(SC_START);
		}
		else
		{
			sendData(SC_STOP);
		}
		break;
	}
	case IN_MOVE_CLOCKWISE:
	{
		if (pressed)
		{
			sendData(SC_SET_ANGULAR_SPEED, speed);
			sendData(SC_MOVE, moveSteps);
		}
		else if (held)
		{
			sendData(SC_SET_ANGULAR_SPEED, speed);
			sendData(SC_SET_DIRECTION, DI_CLOCKWISE);
			sendData(SC_START);
		}
		else
		{
			sendData(SC_STOP);
		}
		break;
	}
	case IN_SET_POSITION_0:
	{
		if (pressed)
		{
			sendData(SC_SET_ANGULAR_SPEED, speed);
			sendData(SC_SET_DIRECTION, dir);
			sendData(SC_SET_ANGLE, 0);
		}
		break;
	}
	case IN_SET_POSITION_90:
	{
		if (pressed)
		{
			sendData(SC_SET_ANGULAR_SPEED, speed);
			sendData(SC_SET_DIRECTION, dir);
			sendData(SC_SET_ANGLE, 90);
		}
		break;
	}
	case IN_SET_POSITION_180:
	{
		if (pressed)
		{
			sendData(SC_SET_ANGULAR_SPEED, speed);
			sendData(SC_SET_DIRECTION, dir);
			sendData(SC_SET_ANGLE, 180);
		}
		break;
	}
	case IN_SET_POSITION_270:
	{
		if (pressed)
		{
			sendData(SC_SET_ANGULAR_SPEED, speed);
			sendData(SC_SET_DIRECTION, dir);
			sendData(SC_SET_ANGLE, 270);
		}
		break;
	}
	case IN_TOGGLE_MOTOR:
	{
		sendData(SC_SET_ENABLED, pressed);
		break;
	}
	case IN_START_COUNTER_CLOCKWISE_VIT_LOW:
	{
		if (pressed)
		{
			sendData(SC_SET_ANGULAR_SPEED, 2880);
			sendData(SC_SET_DIRECTION, DI_COUNTER_CLOCKWISE);
			sendData(SC_START);
		}
		break;
	}
	case IN_START_COUNTER_CLOCKWISE_VIT_MED:
	{
		if (pressed)
		{
			sendData(SC_SET_ANGULAR_SPEED, 6080);
			sendData(SC_SET_DIRECTION, DI_COUNTER_CLOCKWISE);
			sendData(SC_START);
		}
		break;
	}
	case IN_START_COUNTER_CLOCKWISE_VIT_HI:
	{
		if (pressed)
		{
			sendData(SC_SET_ANGULAR_SPEED, 8640);
			sendData(SC_SET_DIRECTION, DI_COUNTER_CLOCKWISE);
			sendData(SC_START);
		}
		break;
	}
	case IN_START_COUNTER_CLOCKWISE_VIT_VHI:
	{
		if (pressed)
		{
			sendData(SC_SET_ANGULAR_SPEED, 11000);
			sendData(SC_SET_DIRECTION, DI_COUNTER_CLOCKWISE);
			sendData(SC_START);
		}
		break;
	}
	case IN_START_CLOCKWISE_VIT_VLOW:
	{
		if (pressed)
		{
			sendData(SC_SET_ANGULAR_SPEED, 480);
			sendData(SC_SET_DIRECTION, DI_CLOCKWISE);
			sendData(SC_START);
		}
		break;
	}
	case IN_START_CLOCKWISE_VIT_LOW:
	{
		if (pressed)
		{
			sendData(SC_SET_ANGULAR_SPEED, 2880);
			sendData(SC_SET_DIRECTION, DI_CLOCKWISE);
			sendData(SC_START);
		}
		break;
	}
	case IN_START_CLOCKWISE_VIT_MED:
	{
		if (pressed)
		{
			sendData(SC_SET_ANGULAR_SPEED, 6080);
			sendData(SC_SET_DIRECTION, DI_CLOCKWISE);
			sendData(SC_START);
		}
		break;
	}
	case IN_START_CLOCKWISE_VIT_HI:
	{
		if (pressed)
		{
			sendData(SC_SET_ANGULAR_SPEED, 8640);
			sendData(SC_SET_DIRECTION, DI_CLOCKWISE);
			sendData(SC_START);
		}
		break;
	}
		case IN_START_CLOCKWISE_VIT_VHI:
	{
		if (pressed)
		{
			sendData(SC_SET_ANGULAR_SPEED, 10000);
			sendData(SC_SET_DIRECTION, DI_CLOCKWISE);
			sendData(SC_START);
		}
		break;
	}
	case IN_STOP:
	{
		if (pressed)
		{
			sendData(SC_STOP);
		}
		break;
	}
	case IN_SET_POSITION_ANALOG:
	{
		sendData(SC_SET_POSITION, data.value);
		break;
	}
	case IN_SET_ORIGIN:
	{
		if (pressed)
		{
			sendData(SC_SET_ORIGIN);
		}
	}
	default:
		break;
	}
}

void MasterController::update(int deltaTime)
{
	m_updateTimer += deltaTime;

	if (m_updateTimer >= UPDATE_PERIOD)
	{
		m_inputManager.update(m_updateTimer);

		m_updateTimer = 0;
	}

	m_serialTransmitter.update(deltaTime);
}

void MasterController::sendData(byte code, int32_t value)
{
	SerialPacket packet;
	packet.channel = 0;
	packet.eventData.code = code;
	packet.eventData.value = value;
	m_serialTransmitter.writeSerial(packet);
}

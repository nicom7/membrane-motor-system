#include "stepper_motor_controller.h"

#include "utils/utils.h"

StepperMotorController::StepperMotorController(byte enablePin, const byte inputPins[4])
	: m_stepper(AccelStepper::DRIVER, inputPins[0], inputPins[1], inputPins[2], inputPins[3])
	, m_enablePin(enablePin)
{
}

StepperMotorController::~StepperMotorController()
{
}

void StepperMotorController::setup()
{
	m_stepper.setMaxSpeed(DEFAULT_MAX_SPEED);
	m_stepper.setAcceleration(ACCELERATION);
	setMotorEnabled(true);
}

void StepperMotorController::update()
{
	if (m_motorEnabled)
	{
		m_stepper.moveTo(m_targetPosition);
	}
	else
	{
		stop();
	}
}

void StepperMotorController::run()
{
	m_stepper.run();
}

int StepperMotorController::getTotalSteps() const
{
	return TOTAL_STEPS;
}

long StepperMotorController::getTargetPosition() const
{
	return m_targetPosition;
}

long StepperMotorController::angleFromPosition(long position, bool clamped)
{
	long angle = -angleFromSteps(position);
	return clamped ? clampedAngle(angle) : angle;
}

long StepperMotorController::positionFromAngle(long angle)
{
	return -stepsFromAngle(angle);
}

long StepperMotorController::angleFromSteps(long steps)
{
	return roundf(steps / (float)TOTAL_STEPS * FULL_ROTATION);
}

long StepperMotorController::stepsFromAngle(long angle)
{
	return roundf(angle / (float)FULL_ROTATION * TOTAL_STEPS);
}

long StepperMotorController::clampedAngle(long angle)
{
	angle = angle % FULL_ROTATION;
	angle += (angle < 0) ? FULL_ROTATION : 0;

	return angle;
}

void StepperMotorController::setTargetPosition(long targetPos)
{
	m_targetPosition = targetPos;
}

void StepperMotorController::setTargetAngle(long targetAngle)
{
	long currentPosition = getCurrentPosition();
	long currentAngle = angleFromPosition(currentPosition);

	long deltaAngle = clampedAngle(targetAngle - currentAngle);

	switch (m_direction)
	{
	case DI_SHORTEST_PATH:
	{
		if (deltaAngle > HALF_ROTATION)
		{
			deltaAngle -= FULL_ROTATION;
		}
	}
	break;
	case DI_LONGEST_PATH:
	{
		if (deltaAngle < HALF_ROTATION)
		{
			deltaAngle -= FULL_ROTATION;
		}
	}
	break;
	case DI_COUNTER_CLOCKWISE:
	{
		if (deltaAngle > 0)
		{
			deltaAngle -= FULL_ROTATION;
		}
	}
	break;
	case DI_CLOCKWISE:
	default:
	{
		if (deltaAngle < 0)
		{
			deltaAngle += FULL_ROTATION;
		}
	}
	break;
	}

	setTargetPosition(positionFromAngle(deltaAngle) + currentPosition);
}

long StepperMotorController::getCurrentPosition()
{
	return m_stepper.currentPosition();
}

void StepperMotorController::setMotorEnabled(bool enabled)
{
	m_motorEnabled = enabled;
}

bool StepperMotorController::isMotorEnabled() const
{
	return m_motorEnabled;
}

int StepperMotorController::getMaxSpeed()
{
	return m_stepper.maxSpeed();
}

void StepperMotorController::setMaxSpeed(int maxSpeed)
{
	m_stepper.setMaxSpeed(maxSpeed);
}

void StepperMotorController::setMaxAngularSpeed(int maxAngularSpeed)
{
	m_stepper.setMaxSpeed(stepsFromAngle(maxAngularSpeed));
}

Direction StepperMotorController::getDirection() const
{
	return m_direction;
}

void StepperMotorController::setDirection(Direction direction)
{
	m_direction = direction;
}

void StepperMotorController::start()
{
	setTargetPosition(m_direction == DI_CLOCKWISE ? MIN_POSITION : MAX_POSITION);
}

void StepperMotorController::stop()
{
	m_stepper.stop();
	setTargetPosition(m_stepper.targetPosition());
}

void StepperMotorController::reset()
{
	setDirection(DI_CLOCKWISE);
	start();
}

void StepperMotorController::setOrigin()
{
	m_stepper.setCurrentPosition(0);
	setTargetPosition(0);
}

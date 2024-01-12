#pragma once

#include <Arduino.h>
#include <AccelStepper.h>
#include "utils/observer.h"
#include "utils/utils.h"

class StepperMotorController
{
public:
	StepperMotorController(byte enablePin, const byte inputPins[4]);
	virtual ~StepperMotorController();

	void setup();
	void update();

	void run();

	int getTotalSteps() const;

	long getTargetPosition() const;
	void setTargetPosition(long targetPos);

	long getTargetAngle() const;
	void setTargetAngle(long targetAnglePos);

	long getCurrentPosition();

	void setMotorEnabled(bool enabled);
	bool isMotorEnabled() const;

	int getMaxSpeed();
	void setMaxSpeed(int maxSpeed);
	void setMaxAngularSpeed(int maxAngularSpeed);

	Direction getDirection() const;
	void setDirection(Direction direction);

	void start();
	void stop();

	void reset();
	void setOrigin();

private:
	static long angleFromPosition(long position, bool clamped = true);
	static long positionFromAngle(long angle);
	static long angleFromSteps(long steps);
	static long stepsFromAngle(long angle);
	static long clampedAngle(long angle);

	static constexpr int TOTAL_STEPS = 1036; // number of steps per revolution
	static constexpr int DEFAULT_MAX_SPEED = 1000;
	static constexpr int ACCELERATION = 4000;

	// Use half range to make sure MAX_POSITION - MIN_POSITION is less than LONG_MAX
	static constexpr long MIN_POSITION = LONG_MIN / 2;
	static constexpr long MAX_POSITION = LONG_MAX / 2;

	// define stepper motor with step mode and inputs
	AccelStepper m_stepper;

	byte m_enablePin = 0;

	bool m_motorEnabled = false;
	long m_targetPosition = 0L;

	Direction m_direction = DI_CLOCKWISE;
};

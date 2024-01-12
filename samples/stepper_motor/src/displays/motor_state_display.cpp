#include "motor_state_display.h"

#include "utils/utils.h"

MotorStateDisplay::MotorStateDisplay(int totalSteps)
	: m_totalSteps(totalSteps)
{
}

MotorStateDisplay::~MotorStateDisplay()
{
}

void MotorStateDisplay::setup(TwoWire& interface)
{
	m_matrix.begin(IS3741_ADDR_DEFAULT, &interface);
	m_matrix.setRotation(3);

	// By default the LED controller communicates over I2C at 400 KHz.
	// Arduino Uno can usually do 800 KHz, and 32-bit microcontrollers 1 MHz.
	interface.setClock(4000000);

	// Set brightness to max and bring controller out of shutdown state
	m_matrix.setLEDscaling(0xFF);
	m_matrix.setGlobalCurrent(0x02);

	m_matrix.fill(0);
	m_matrix.enable(true); // bring out of shutdown
	m_matrix.setRotation(0);
	m_matrix.setTextWrap(false);

	m_circleColor = m_matrix.color565(m_matrix.ColorHSV(0x4000));
	m_targetColor = m_matrix.color565(m_matrix.ColorHSV(0x8000));
	m_centerX = m_matrix.width() / 2;
	m_centerY = m_matrix.height() / 2;
	m_radius = min(m_centerX, m_centerY) + 1;

	m_matrix.drawCircle(m_centerX, m_centerY, m_radius, m_circleColor);

	m_redraw = true;
}

void MotorStateDisplay::update(int deltaTime)
{
	if (m_redraw)
	{
		updateDisplayTargetPosition();
		updateDisplayMotorPosition();

		// Clear previous lines
		// start = micros();
		m_matrix.drawLine(m_centerX, m_centerY, m_centerX + m_prevMotorDx, m_centerY + m_prevMotorDy, 0);
		m_matrix.drawLine(m_centerX, m_centerY, m_centerX + m_prevTargetDx, m_centerY + m_prevTargetDy, 0);

		m_matrix.drawLine(m_centerX, m_centerY, m_centerX + m_motorDx, m_centerY + m_motorDy, m_circleColor);
		m_matrix.drawLine(m_centerX, m_centerY, m_centerX + m_targetDx, m_centerY + m_targetDy, m_targetColor);
		// Serial.println(micros() - start);

		m_matrix.drawPixel(0, 0, m_enabled ? m_colorEnabled : m_colorDisabled);

		m_prevMotorDx = m_motorDx;
		m_prevMotorDy = m_motorDy;

		m_prevTargetDx = m_targetDx;
		m_prevTargetDy = m_targetDy;

		m_redraw = false;
	}
}

float MotorStateDisplay::getRelativePosition(long absolutePosition)
{
	int wrappedPos = absolutePosition % m_totalSteps;
	if (wrappedPos < 0)
	{
		wrappedPos += m_totalSteps;
	}

	return (float)wrappedPos / m_totalSteps;
}

void MotorStateDisplay::updateDisplayTargetPosition()
{
	float relativeTargetPosition = getRelativePosition(m_targetPosition);

	float targetAngle = relativeTargetPosition * TWO_PI;

	m_targetDx = (m_radius - 1) * cos(targetAngle);
	m_targetDy = (m_radius - 1) * sin(targetAngle);
}

void MotorStateDisplay::updateDisplayMotorPosition()
{
	float relativeMotorPosition = getRelativePosition(m_currentPosition);

	float motorAngle = relativeMotorPosition * TWO_PI;

	m_motorDx = (m_radius - 1) * cos(motorAngle);
	m_motorDy = (m_radius - 1) * sin(motorAngle);
}

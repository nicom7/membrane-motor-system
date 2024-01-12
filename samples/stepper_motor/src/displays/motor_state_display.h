#pragma once

#include "utils/updatable.h"

#include <Adafruit_IS31FL3741.h>
#include <math.h>

class MotorStateDisplay : public IUpdatable
{
public:
	MotorStateDisplay(int totalSteps);
	virtual ~MotorStateDisplay();

	void setup(TwoWire& interface = Wire);
	void update(int deltaTime) override;

	void setTargetPosition(long position)
	{
		if (m_targetPosition != position)
		{
			m_targetPosition = position;
			m_redraw = true;
		}
	}

	void setCurrentPosition(long position)
	{
		if (m_currentPosition != position)
		{
			m_currentPosition = position;
			m_redraw = true;
		}
	}

	void setEnabled(bool enabled)
	{
		if (m_enabled != enabled)
		{
			m_enabled = enabled;
			m_redraw = true;
		}
	}

private:
	void getAbsoluteCoordinates(float relative, int& x0, int& x1);
	float getRelativePosition(long absolutePosition);
	void updateDisplayTargetPosition();
	void updateDisplayMotorPosition();

	long m_targetPosition = 0;
	long m_currentPosition = 0;
	int m_totalSteps = 1;

	Adafruit_IS31FL3741_QT m_matrix;

	uint16_t m_circleColor = 0;
	uint16_t m_targetColor = 0;
	int m_centerX = 0;
	int m_centerY = 0;
	int m_radius = 0;

	int m_motorDx = 0;
	int m_motorDy = 0;
	int m_targetDx = 0;
	int m_targetDy = 0;

	int m_prevMotorDx = 0;
	int m_prevMotorDy = 0;
	int m_prevTargetDx = 0;
	int m_prevTargetDy = 0;

	const uint16_t m_colorEnabled = m_matrix.color565(m_matrix.ColorHSV(0x4000));
	const uint16_t m_colorDisabled = m_matrix.color565(m_matrix.ColorHSV(0x0100));
	bool m_enabled = false;

	bool m_redraw = false;
};

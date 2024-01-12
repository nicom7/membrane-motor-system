#include "standalone_controller.h"

#include "utils/utils.h"

StandaloneController::StandaloneController(byte motorEnablePin, const byte motorInputPins[4])
	: AbstractBoardController()
	, m_inputManager()
	, m_motorController(motorEnablePin, motorInputPins)
	, m_display(m_motorController.getTotalSteps())
{
}

StandaloneController::~StandaloneController()
{
}

void StandaloneController::setup()
{
	AbstractBoardController::setup();

	m_inputManager.setup(*this);

	m_motorController.setup();
	m_display.setup();
}

void StandaloneController::update(const EventData& data)
{
	switch (data.code)
	{
	default:
		break;
	}
}

void StandaloneController::update(int deltaTime)
{
	m_updateTimer += deltaTime;

	if (m_updateTimer >= UPDATE_PERIOD)
	{
		m_inputManager.update(m_updateTimer);
		m_motorController.update();

		m_display.setTargetPosition(m_motorController.getTargetPosition());
		m_display.setCurrentPosition(m_motorController.getCurrentPosition());
		m_display.update(m_updateTimer);

		m_updateTimer = 0;
	}

	m_motorController.run();
}

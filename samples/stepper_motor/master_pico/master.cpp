// Master code (Raspberry Pi Pico)

#include "controllers/master_controller.h"

MasterController boardController(Serial1);

void setup()
{
	boardController.setup();

	boardController.addDigitalInput(22, IN_SET_ORIGIN);
	boardController.addDigitalInput(17, IN_MOVE_CLOCKWISE, 1000);
	boardController.addDigitalInput(16, IN_MOVE_COUNTER_CLOCKWISE, 1000);
	boardController.addDigitalInput(1, IN_SET_POSITION_0);
	boardController.addDigitalInput(2, IN_SET_POSITION_90);
	boardController.addDigitalInput(3, IN_SET_POSITION_180);
	boardController.addDigitalInput(4, IN_SET_POSITION_270);
	boardController.addDigitalInput(5, IN_START_COUNTER_CLOCKWISE_VIT_LOW);
	boardController.addDigitalInput(6, IN_START_COUNTER_CLOCKWISE_VIT_MED);
	boardController.addDigitalInput(7, IN_START_COUNTER_CLOCKWISE_VIT_HI);
	boardController.addDigitalInput(8, IN_START_COUNTER_CLOCKWISE_VIT_VHI);
	boardController.addDigitalInput(9, IN_START_CLOCKWISE_VIT_LOW);
	boardController.addDigitalInput(10, IN_START_CLOCKWISE_VIT_MED);
	boardController.addDigitalInput(11, IN_START_CLOCKWISE_VIT_HI);
	boardController.addDigitalInput(12, IN_START_CLOCKWISE_VIT_VHI);
	boardController.addDigitalInput(13, IN_START_CLOCKWISE_VIT_VLOW);
	boardController.addDigitalInput(14, IN_STOP);
	boardController.addDigitalInput(20, IN_TOGGLE_MOTOR);
	// boardController.addAnalogInput(26, IN_SET_POSITION_ANALOG);
	// boardController.addDigitalInput(code, pin);
	// ...
}

void loop()
{
	boardController.loop();
}

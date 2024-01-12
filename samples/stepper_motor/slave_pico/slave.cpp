// Slave code (Raspberry Pi Pico)

#include "controllers/slave_controller.h"

const byte motorPins[] = { 14, 15, 8, 9 };
const byte motorEnablePin = 8;

SlaveController boardController(motorEnablePin, motorPins, Serial1, Wire1);

void setup()
{
	Wire1.setSDA(18u);
	Wire1.setSCL(19u);
	Wire1.begin();

	boardController.setup();

	// boardController.addDigitalInput(17, IN_TOGGLE_MOTOR);
	// boardController.addDigitalInput(22, SI_DETECTED, -1, false); 	// No repeat and no pullup resistor for IR sensor input
	// boardController.addDigitalInput(code, pin);
	// ...
}

void loop()
{
	boardController.loop();
}

void setup1()
{
	boardController.setup1();
}

void loop1()
{
	boardController.loop1();
}

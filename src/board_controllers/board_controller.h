#pragma once

class IBoardController
{
public:
	virtual ~IBoardController() {}

	virtual void setup() = 0;
	virtual void loop() = 0;
};

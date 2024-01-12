#pragma once

enum SerialCode
{
	SC_MOVE = 0x80,		// Begin at 0x80 to avoid ambiguity with InputCode enum values

	SC_SET_ENABLED,
	SC_RESET,

	SC_SET_POSITION,
	SC_SET_ANGLE,
	SC_SET_SPEED,
	SC_SET_ANGULAR_SPEED,
	SC_SET_DIRECTION,

	SC_START,
	SC_STOP,

	SC_SET_ORIGIN
};

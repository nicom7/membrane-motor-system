#pragma once

enum InputCode
{
	IN_SET_POSITION_0 = 0x0,
	IN_SET_POSITION_90,
	IN_SET_POSITION_180,
	IN_SET_POSITION_270,
	IN_SET_POSITION_90_VIT_0_07,
	IN_SET_POSITION_FUT1,
	IN_SET_POSITION_FUT2,
	IN_SET_POSITION_FUT3,
	IN_SET_POSITION_FUT4,
	IN_SET_POSITION_FUT5,
	IN_SET_POSITION_FUT6,


	IN_MOVE_COUNTER_CLOCKWISE,
	IN_MOVE_CLOCKWISE,

	IN_TOGGLE_MOTOR,	// Input low to enable, high or pullup to disable

	IN_START_CLOCKWISE_VIT_VLOW,
	IN_START_CLOCKWISE_VIT_LOW,
	IN_START_CLOCKWISE_VIT_MED,
	IN_START_CLOCKWISE_VIT_HI,
	IN_START_CLOCKWISE_VIT_VHI,
	IN_START_COUNTER_CLOCKWISE_VIT_LOW,
	IN_START_COUNTER_CLOCKWISE_VIT_MED,
	IN_START_COUNTER_CLOCKWISE_VIT_HI,
	IN_START_COUNTER_CLOCKWISE_VIT_VHI,
	IN_STOP,

	IN_SET_POSITION_ANALOG,
	IN_SET_ORIGIN,

	IN_SENSOR_DETECTED
};

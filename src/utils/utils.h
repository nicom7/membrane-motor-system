#pragma once

#define MSEC_PER_SEC 1000UL
#define USEC_PER_MSEC 1000UL
#define USEC_PER_SEC (USEC_PER_MSEC * MSEC_PER_SEC)
#define FULL_ROTATION 360
#define HALF_ROTATION (FULL_ROTATION >> 1)
#define QUARTER_ROTATION (FULL_ROTATION >> 2)
#define DEFAULT_BAUD_RATE 9600
#define DEFAULT_UPDATE_PERIOD 8	// Update period in ms

#define UNUSED(expr) (void)(expr)

template<class T>
void Swap(T& x, T& y)
{
	T temp;
	temp = x;
	x = y;
	y = temp;
}

enum Direction
{
	DI_CLOCKWISE = 0,
	DI_COUNTER_CLOCKWISE,
	DI_SHORTEST_PATH,
	DI_LONGEST_PATH,

	DI_COUNT
};

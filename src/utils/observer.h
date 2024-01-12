#pragma once

#include "event_data.h"

template<class T>
class IObserver
{
public:
	virtual ~IObserver() {}

	virtual void update(const T& data) = 0;
};

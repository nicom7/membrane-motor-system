#pragma once

#include "observer.h"

template<class T>
class IObservable
{
public:
	virtual ~IObservable() {}

	virtual void add(IObserver<T>& observer) = 0;
	virtual void notify(const T& data) = 0;
};

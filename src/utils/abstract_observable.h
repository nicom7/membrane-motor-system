#pragma once

#include "observable.h"

template<class T>
class AbstractObservable : public IObservable<T>
{
public:
	AbstractObservable();
	AbstractObservable(const AbstractObservable& other);
	virtual ~AbstractObservable() = 0;

	void add(IObserver<T>& observer) override;

protected:
	void notify(const T& data) override;

private:
	static constexpr byte MAX_OBSERVERS = 8;
	IObserver<T>* m_observers[MAX_OBSERVERS];
	byte m_numObservers = 0;
};

template<class T>
AbstractObservable<T>::AbstractObservable()
{
	for (byte i = 0; i < MAX_OBSERVERS; i++)
	{
		m_observers[i] = nullptr;
	}
}

template<class T>
AbstractObservable<T>::AbstractObservable(const AbstractObservable& other)
{
	for (byte i = 0; i < MAX_OBSERVERS; i++)
	{
		m_observers[i] = other.m_observers[i];
	}
}

template<class T>
AbstractObservable<T>::~AbstractObservable()
{
}

template<class T>
void AbstractObservable<T>::add(IObserver<T>& observer)
{
	m_observers[m_numObservers] = &observer;
	m_numObservers = (m_numObservers + 1) % MAX_OBSERVERS;
}

template<class T>
void AbstractObservable<T>::notify(const T& data)
{
	for (byte i = 0; i < m_numObservers; i++)
	{
		m_observers[i]->update(data);
	}
}

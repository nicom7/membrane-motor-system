#pragma once

#include "utils/event_data.h"
#include "utils/observable.h"
#include "utils/updatable.h"
#include "utils/led.h"
#include <Arduino.h>

class SerialPacket;

class SerialReceiver : public IObservable<AnalogEventData>, public IUpdatable
{
public:
	SerialReceiver(arduino::HardwareSerial& serialInterface, byte channel = 0);
	SerialReceiver(const SerialReceiver& other);
	bool readSerial(SerialPacket& packet);

	void add(IObserver<AnalogEventData>& observer) override;
	void update(int deltaTime) override;
	void setup(unsigned long baudRate);

protected:
	void notify(const AnalogEventData& data) override;

private:
	arduino::HardwareSerial* m_serialInterface = nullptr;
	byte m_channel = 0;

	static constexpr byte MAX_OBSERVERS = 8;
	IObserver<AnalogEventData>* m_analogObservers[MAX_OBSERVERS];
	byte m_numAnalogObservers = 0;

	// Activity LED blinking period in ms
	static constexpr unsigned int ACTIVITY_LED_BLINK_PERIOD = 100;
	// Activity LED blinking duration in ms
	static constexpr unsigned int ACTIVITY_LED_BLINK_DURATION = 1000;

	// Activity LED: Will blink when receiving data for this channel
	LED m_activityLED;
};

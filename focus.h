#ifndef _FOCUS_H
#define _FOCUS_H

#include "statemachine.h"

class LightSwitch;
class Thermometer;
class LightSensor;

class Focus : public BelState {
public:
	void init(LightSwitch *lightSwitch, Thermometer *thermometer, LightSensor *lightSensor);

	void onButtonClicked(const BelButton &button);
	void onEnter();
	void onExit();
	void setFocus(bool doFocus);
	void printTitle();
	void printSensorValues();
	void printMenu();
	void onTimerUpdate(const unsigned long remainingMs);


private:
	LightSwitch *m_lightSwitch;
	Thermometer *m_thermometer;
	LightSensor *m_lightSensor;
	bool m_doFocus = false;
};

#endif // _FOCUS_H


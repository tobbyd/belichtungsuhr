#ifndef _FOCUS_H
#define _FOCUS_H

#include "statemachine.h"

class LightSwitch;
class Thermometer;
class LightSensor;

class Focus : public BelState {
public:
	void init(LightSwitch *lightSwitch);

	void onButtonClicked(const BelButton &button);
	void onEnter();
	void onExit();
	void setFocus(bool doFocus);
	void printTitle();
	void printMenu();


private:
	LightSwitch *m_lightSwitch;
	bool m_doFocus = false;
};

#endif // _FOCUS_H

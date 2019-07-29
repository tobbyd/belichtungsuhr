#ifndef _CHEMIE_CLOCK_H
#define _CHEMIE_CLOCK_H

#include "statemachine.h"

class ChemieClock : public BelState {
public:
	ChemieClock(const char *title);
	ChemieClock(const __FlashStringHelper* title) ;

	void init(LightSwitch *lightSwitch, int startSeconds, bool turnOnLight);

	virtual void onButtonClicked(const BelButton &button);
	virtual void onEnter();
	virtual void printMenu();
	virtual void printTime();
	virtual void onTimerUp();
	virtual void onTimerUpdate(const unsigned long remainingMs);

private:
	const char *m_ctitle;
	const __FlashStringHelper *m_ftitle;
	unsigned int m_currentSeconds;
	bool m_turnOnLight;
	LightSwitch *m_lightSwitch;
	TimerRunningState m_state = TimerRunningState::STOPPED;
};


#endif // _CHEMIE_CLOCK_H

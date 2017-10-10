#ifndef _CHEMIE_CLOCK_H
#define _CHEMIE_CLOCK_H

#include "statemachine.h"

class ChemieClock : public BelState {
public:
	ChemieClock(const char *title, int startSeconds);
	ChemieClock(const __FlashStringHelper* title, int startSeconds);

	virtual void onButtonClicked(const BelButton &button);
	virtual void onEnter();
	virtual void printMenu();
	virtual void printTime();
	virtual void onTimerUp();
	virtual void onTimerUpdate(const unsigned long remainingMs);

private:
	char *m_ctitle;
	__FlashStringHelper *m_ftitle;
	unsigned int m_currentSeconds;
	TimerRunningState m_state = TimerRunningState::STOPPED;
};


#endif // _CHEMIE_CLOCK_H


#ifndef _ENLARGER_H
#define _ENLARGER_H

#include "timer.h"

class LightSwitch;

class Enlarger : public BelState {
public:
	Enlarger() { }
	void init(LightSwitch *lightSwitch);

	void onEnter();
	void onButtonClicked(const BelButton &button);
	virtual void onTimerUp();
	virtual void onTimerUpdate(const unsigned long remainingMs);

private:
	void changeBase();
	void printMenu();
	void printTime();
	void printBase();

	void calcValues();
	void writeTime(char *buffer, int size, int pot);
	unsigned long getMs(int pot);

	int m_currentPot = 10;
	int m_base = 3;

	float m_posMs[31];
	float m_negMs[11];

	LightSwitch *m_lightSwitch = nullptr;
	TimerRunningState m_state = TimerRunningState::STOPPED;

};

#endif //_ENLARGER_H


#ifndef _ENLARGER_H
#define _ENLARGER_H

class Enlarger : public BelState {
public:
	Enlarger() { }
	void init(RCSwitch *sender);

	void onEnter();
	void onButtonClicked(const BelButton &button);
	virtual void onTimerUp();
	virtual void onTimerUpdate(const unsigned long remainingMs);

	void enlargerOn();
	void enlargerOff();
	void changeBase();

private:
	void printMenu();
	void printTime();
	void printBase() {

	void calcValues();
	void writeTime(char *buffer, int size, int pot);
	unsigned long getMs(int pot);

	int m_currentPot = 10;
	int m_base = 3;

	float m_posMs[31];
	float m_negMs[11];

	RCSwitch *m_sender;
	TimerRunningState m_state = TimerRunningState::STOPPED;

};

#endif //_ENLARGER_H


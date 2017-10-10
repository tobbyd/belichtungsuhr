#ifndef _TIMER_H
#define _TIMER_H

class BelState;

enum class TimerRunningState {
	RUNNING,
	STOPPED,
	PAUSED,
};

class Timer {
public:
	Timer(BelState *states[]);
	void startTimer(int STATENUM, unsigned long millisToDo);
	unsigned long pauseTimer();
	void continueTimer();
	void check();


private:
	unsigned long m_timeOutMillis;
	unsigned long m_millisToDo;
	unsigned long m_nextUpdateMillis;
	int m_callerState;
	bool m_isRunning;
	BelState **m_states;
};



#endif // _TIMER_H


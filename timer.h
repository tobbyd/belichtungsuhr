#ifndef _TIMER_H
#define _TIMER_H

class BelState;

enum class TimerRunningState : uint8_t {
	PRERUNNING,
	RUNNING,
	STOPPED,
	PAUSED,
};

class Timer {
public:
	Timer();
	void startTimer(BelState *state, unsigned long millisToDo);
	// run until paused or reset
	void startTimer(BelState *state);
	unsigned long pauseTimer();
	void continueTimer();
	void check();


private:
	unsigned long m_timeOutMillis;
	unsigned long m_millisToDo;
	unsigned long m_nextUpdateMillis;
	BelState *m_callerState;
	bool m_isRunning;
};



#endif // _TIMER_H



#include "timer.h"
#include "statemachine.h"

Timer::Timer(BelState *states[]):
	m_timeOutMillis(static_cast<unsigned long>(-1)),
	m_millisToDo(static_cast<unsigned long>(-1)),
	m_nextUpdateMillis(static_cast<unsigned long>(-1)),
	m_callerState(-1),
	m_isRunning(false),
	m_states(states)
{

}


void Timer::startTimer(int STATENUM, unsigned long millisToDo) {
	unsigned long refTime = millis();
	m_timeOutMillis = refTime + millisToDo;
	m_millisToDo = millisToDo;

	// start backwards in 1000ms steps from timeoutMillis to now.
	// for -5600ms overall, first tick is at -5000
	m_nextUpdateMillis = m_timeOutMillis - 1000*((m_timeOutMillis-refTime)/1000);
	m_callerState = STATENUM;
	m_isRunning = true;
}

unsigned long Timer::pauseTimer() { 
	unsigned long refTime = millis();
	m_isRunning = false;
	m_millisToDo = m_timeOutMillis - refTime;
	return m_millisToDo;
}

void Timer::continueTimer() { 
	startTimer(m_callerState, m_millisToDo);
}

void Timer::check() { 
	if(m_isRunning) {
		unsigned long refTime = millis();
		if(refTime >= m_timeOutMillis) {
			m_isRunning = false;
			StateMachine::instance().setToState(m_callerState);
			StateMachine::instance().execState();
			m_states[m_callerState]->onTimerUp();
		} else if (refTime >= m_nextUpdateMillis) {
			m_nextUpdateMillis += 1000; // should not be modified after onTimerUpdate, because onTimerUpdate may set a new timer
			m_states[m_callerState]->onTimerUpdate(m_timeOutMillis - m_nextUpdateMillis + 1000);
		}
	}
}


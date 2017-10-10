
#include "chemieClock.h"

ChemieClock::ChemieClock(const char *title, int currentSeconds): 
	m_ctitle(title),
	m_ftitle(nullptr),
	m_currentSeconds(currentSeconds) {
}

ChemieClock::ChemieClock(const __FlashStringHelper* title, int currentSeconds):
	m_ctitle(nullptr),
	m_ftitle(title),
	m_currentSeconds(currentSeconds) {
}

void ChemieClock::onButtonClicked(const BelButton &button) {
	switch(button) {
	case BelButton::BUTTON_INC:
		if(m_state == TimerRunningState::STOPPED) {
			m_currentSeconds += 30;
			printTime();
		}
		break;
	case BelButton::BUTTON_DEC:
		if(m_state == TimerRunningState::STOPPED) {
			if(m_currentSeconds > 30) {
				m_currentSeconds -= 30;
				printTime();
			} else {
				beeper.buzz();
			}
		}
		break;
	case BelButton::BUTTON_ENTER:
		if(m_state == TimerRunningState::RUNNING) {
			timer.pauseTimer();
			MyLCD::instance().play();
			m_state = TimerRunningState::PAUSED;
		} else if(m_state == TimerRunningState::STOPPED) {
			const unsigned long lsec = m_currentSeconds;
			timer.startTimer(STATE_DEV, lsec*1000);
			MyLCD::instance().pause();
			m_state = TimerRunningState::RUNNING;
		} else { // paused
			timer.continueTimer();
			MyLCD::instance().play();
			m_state = TimerRunningState::RUNNING;
		}
		break;
	case BelButton::BUTTON_RESET:
		m_state = TimerRunningState::STOPPED;
		break;
	}
}

void ChemieClock::printMenu() {
	if(m_ctitle != nullptr) {
		MyLCD::instance().printTitle(m_ctitle);
	} else {
		MyLCD::instance().printTitle(m_ftitle);
	}

	if(m_state == TimerRunningState::RUNNING) {
		MyLCD::instance().pause();
	} else {
		MyLCD::instance().play();
	}
	printTime();
}

void ChemieClock::printTime() {
	const char timeBuffer[11];
	snprintf(timeBuffer, 11, "    %3d:%02d", (m_currentSeconds/60), (m_currentSeconds % 60));
	MyLCD::instance().printValue(timeBuffer);
}

void ChemieClock::onEnter() {
	printMenu();
}

void ChemieClock::onTimerUp() {
	beeper.timerUp();
	StateMachine::instance().setToState((StateMachine::instance().getCurrentStateNum() + 1) % NUMSTATES);
	printTime();
	MyLCD::instance().play();
	m_state = TimerRunningState::STOPPED;
}

void ChemieClock::onTimerUpdate(const unsigned long remainingMs) {	
	int sec = remainingMs / 1000;
	if(sec > 3)
		beeper.tock();
	else
		beeper.tick();
	const char timeBuffer[11];
	snprintf(timeBuffer, 11, "       %3d", sec);
	MyLCD::instance().printValue(timeBuffer);
}


#include "enlarger.h"
#include <stdio.h>
#undef round
#undef pow
#include <math.h>
#include <RCSwitch.h>



void Enlarger::init(LightSwitch *lightSwitch) {
	m_lightSwitch = lightSwitch;
	calcValues();
}

void Enlarger::printMenu() {
	MyLCD::instance().printTitle(F("Belichtung"));
}

void Enlarger::onButtonClicked(const BelButton &button) {
	switch(button) {
	case BelButton::BUTTON_INC:
		if(m_state == TimerRunningState::STOPPED) {
			if(m_currentPot < 30) {
				m_currentPot++;
				printTime();
			} else {
				beeper.buzz();
			}
		}
		break;
	case BelButton::BUTTON_DEC:
		if(m_state == TimerRunningState::STOPPED) {
			if(m_currentPot > -10 ) {
				m_currentPot--;
				printTime();
			} else {
				beeper.buzz();
			}
		}
		break;
	case BelButton::BUTTON_ENTER:
		if(m_state == TimerRunningState::RUNNING) {
			timer.pauseTimer();
			m_lightSwitch->enlargerOn(false);
			MyLCD::instance().play();
			m_state = TimerRunningState::PAUSED;
		} else if(m_state == TimerRunningState::STOPPED) {
			m_countDown = 4;
			timer.startTimer(this, (m_countDown)*1000); // last update is not sent
			MyLCD::instance().pause();
			m_state = TimerRunningState::RUNNING;
		} else { // paused
			timer.continueTimer();
			m_lightSwitch->enlargerOn(true);
			MyLCD::instance().pause();
			m_state = TimerRunningState::RUNNING;
		}
		break;
	case BelButton::BUTTON_RESET:
		if(m_state == TimerRunningState::RUNNING || m_state == TimerRunningState::PAUSED) {
			timer.pauseTimer();
			m_lightSwitch->enlargerOn(false);
			m_state = TimerRunningState::STOPPED;
		} else {
			changeBase();
		}
		break;
	}
}

void Enlarger::changeBase() {
	switch(m_base) {
	case(2):
	case(3):
	case(4):
	case(5): m_base++; break;
	default: m_base = 2; break;
	}
	calcValues();
	printBase();
	printTime();
}

void Enlarger::printBase() {
	char buf[4];
	snprintf(buf,4,"1/%1d", m_base);
	MyLCD::instance().printHints(buf);
}

void Enlarger::printTime() {
	char buf[13];
	writeTime(buf, 13, m_currentPot);
	MyLCD::instance().printValue(buf);
}

void Enlarger::calcValues() {
	const float frac = pow(2,float(1)/m_base);
	m_posMs[0] = 1000;
	m_negMs[0] = 1000;
	const float sqrOne = m_negMs[0]*m_negMs[0];
	for(int i=1; i<31; i++) {
		m_posMs[i] = m_posMs[i-1]*frac;
	}
	for(int i=1; i<11; i++) {
		m_negMs[i] = sqrOne/m_posMs[i];
	}
}


void Enlarger::writeTime(char *buffer, int size, int pot) {
	if(pot >= 0) {
		const int roundValue = (int)round(m_posMs[pot]/1000);
		if(roundValue >= 10) {
			snprintf(buffer, size, "  %5d s ", roundValue);
		} else {
			const int is = round(m_posMs[pot]/100);
			const int precomma = is/10;
			const int postcomma = is % 10;
			
			snprintf(buffer, size, "    %1d,%1d s ", precomma, postcomma);
		}
	} else {
		uint32_t ms = m_negMs[-pot];
		snprintf(buffer, size, "    %3dms", ms);
	}
}

unsigned long Enlarger::getMs(int pot) {
	long res;
	if(pot >= 0) {
		res = round(m_posMs[pot]);
	} else {
		res = round(m_negMs[pot]);
	}
	return res;
}


void Enlarger::onEnter() {
	printMenu();
	printTime();
	printBase();
}

void Enlarger::onTimerUp() {
	if(m_countDown == 1) { // stops at 1, because 0 is here
		m_countDown = 0;
		timer.startTimer(this, getMs(m_currentPot)); // start actual timer after countdown
		m_lightSwitch->enlargerOn(true);
	} else {
		m_lightSwitch->enlargerOn(false);
		StateMachine::instance().nextState();
		// necessary? We switch to next state anyway...
		printTime();
		printBase();
		m_state = TimerRunningState::STOPPED;
	}
}

void Enlarger::onTimerUpdate(const unsigned long remainingMs) {
	if(m_countDown > 1) {
		m_countDown--;
		beeper.tick();
		const char timeBuffer[13];
		snprintf(timeBuffer, 13, "       %3d", m_countDown);
		MyLCD::instance().printValue(timeBuffer);
	} else {
		int sec = remainingMs / 1000;
		if(sec > 3)
			beeper.tock();
		else
			beeper.tick();
		const char timeBuffer[13];
		snprintf(timeBuffer, 13, "       %3d", sec);
		MyLCD::instance().printValue(timeBuffer);
	}
}


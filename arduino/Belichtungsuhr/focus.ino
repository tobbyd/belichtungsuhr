#include "focus.h"
#include "limits.h"


void Focus::init(LightSwitch *lightSwitch) {
	m_lightSwitch = lightSwitch;
}

void Focus::onButtonClicked(const BelButton &button) {
	switch(button) {
	case BelButton::BUTTON_ENTER:
		m_doFocus = !m_doFocus;
		setFocus(m_doFocus);
		printTitle();
		break;
	case BelButton::BUTTON_RESET:
		m_lightSwitch->workingLightOn(false);
		m_lightSwitch->darkRoomLightOn(false);
		m_lightSwitch->enlargerOn(false);
		break;
	}
}

void Focus::setFocus(bool doFocus) {
	m_lightSwitch->workingLightOn(!doFocus);
	m_lightSwitch->darkRoomLightOn(true); // always on, just turn off on "reset"
	m_lightSwitch->enlargerOn(doFocus);
}

void Focus::printTitle() {
	if(m_doFocus) {
		MyLCD::instance().printTitle(F("Focus on"));
	} else {
		MyLCD::instance().printTitle(F("Focus off"));
	}
}


void Focus::onEnter() {
// do not change workingLight. This is done either at focus on/off, or by chemieclock (working light on, when finished)
//	m_lightSwitch->workingLightOn(false);
	m_lightSwitch->darkRoomLightOn(true);
	m_lightSwitch->enlargerOn(false);
	printMenu();
}

void Focus::printMenu() {
	printTitle();
  MyLCD::instance().clearValue();
  MyLCD::instance().clearHints();
}


void Focus::onExit() 
{
	if(m_doFocus) {
		m_doFocus = false;
	}
	m_lightSwitch->workingLightOn(false);
	m_lightSwitch->darkRoomLightOn(true);
	m_lightSwitch->enlargerOn(false);
}

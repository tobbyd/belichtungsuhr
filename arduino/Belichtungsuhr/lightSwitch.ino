#include "lightSwitch.h"
#include "myLCD.h"
#include <RCSwitch.h>

void LightSwitch::init(RCSwitch *sender) 
{
	m_sender = sender;
	workingLightOn(false);
	enlargerOn(false);
	darkRoomLightOn(true);
}

void LightSwitch::workingLightOn(const bool on) const {
	if(on) {
		m_sender->sendTriState(workingLight_On);
		MyLCD::instance().darkMode(false);
	} else {
		MyLCD::instance().darkMode(true);
		m_sender->sendTriState(workingLight_Off);
	}
}


void LightSwitch::darkRoomLightOn(const bool on) const {
	if(on) {
		m_sender->sendTriState(darkRoomLight_On);
	} else {
		m_sender->sendTriState(darkRoomLight_Off);
	}
}

void LightSwitch::enlargerOn(const bool on) const {
	if(on) {
		m_sender->sendTriState(enlarger_On);
	} else {
		m_sender->sendTriState(enlarger_Off);
	}
}

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

void LightSwitch::workingLightOn(bool on) {
	if(on) {
		m_sender->sendTriState(workingLight_On);
	} else {
		m_sender->sendTriState(workingLight_Off);
	}
}


void LightSwitch::darkRoomLightOn(bool on) {
	if(on) {
		m_sender->sendTriState(darkRoomLight_On);
	} else {
		m_sender->sendTriState(darkRoomLight_Off);
	}
}

void LightSwitch::enlargerOn(bool on) {
	if(on) {
		m_sender->sendTriState(enlarger_On);
	} else {
		m_sender->sendTriState(enlarger_Off);
	}
}






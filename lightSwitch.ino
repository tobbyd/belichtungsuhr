#include "lightSwitch.h"
#include "myLCD.h"
#include <RCSwitch.h>

void LightSwitch::init(RCSwitch *sender) 
{
	m_lightOn[static_cast<int>(LightType::WorkingLight)] = false;
	m_lightOn[static_cast<int>(LightType::DarkRoomLight)] = true;

	m_sender = sender;

	lightOff(LightType::WorkingLight);
	lightOn(LightType::DarkRoomLight);

}

void LightSwitch::onButtonClicked(const BelButton &button) {
	switch(button) {
	case BelButton::BUTTON_INC:
		m_currentMenuEntry = (m_currentMenuEntry + 1) % LIGHTCOUNT;
		break;
	case BelButton::BUTTON_DEC:
		m_currentMenuEntry = (m_currentMenuEntry + 1) % LIGHTCOUNT;
		break;
	case BelButton::BUTTON_ENTER:
		if(m_lightOn[m_currentMenuEntry]) {
			lightOff(m_currentMenuEntry); 
		} else {
			lightOn(m_currentMenuEntry);
		}
		break;
	}
	printMenu();
}

void LightSwitch::onEnter() {
	m_currentMenuEntry = LightType::WorkingLight;
	printMenu();
}

void LightSwitch::printMenu() {
	MyLCD::instance().printTitle(F("Lichtschalter"));
	switch(m_currentMenuEntry) {
	case LightType::WorkingLight: 
		MyLCD::instance().printValue("Arbeitsl.");
		break;
	case LightType::DarkRoomLight: 
		MyLCD::instance().printValue("Rotlicht");
		break;
	}
	if(m_lightOn[m_currentMenuEntry])
		MyLCD::instance().printHints("an");
	else
		MyLCD::instance().printHints("aus");
	
}

void LightSwitch::lightOn(const LightType &lightType) {
	if(lightType < LIGHTCOUNT) {
		m_lightOn[lightType] = true;
		Serial.println(LIGHTONCONST[lightType]);
		m_sender->sendTriState(LIGHTONCONST[lightType]);
	}
}

void LightSwitch::lightOff(const LightType &lightType) {
	if(lightType < LIGHTCOUNT) {
		m_lightOn[lightType] = false;
		Serial.println(LIGHTOFFCONST[lightType]);
		m_sender->sendTriState(LIGHTOFFCONST[lightType]);
	}
}





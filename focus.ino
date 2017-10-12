#include "focus.h"


void Focus::init(LightSwitch *lightSwitch, Thermometer *thermometer, LightSensor *lightSensor) {
	m_lightSwitch = lightSwitch;
	m_thermometer = thermometer;
	m_lightSensor = lightSensor;
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

	if(doFocus) {
		// to infinity!
		timer.startTimer(this, -1);
	} else {
		timer.pauseTimer();
	}
}

void Focus::printTitle() {
	if(m_doFocus) {
		MyLCD::instance().printTitle(F("Focus on"));
	} else {
		MyLCD::instance().printTitle(F("Focus off"));
	}
}

void Focus::printSensorValues() {
	float temperature = m_thermometer->getTemperature();
	int lightValue = m_lightSensor->getLight();

	char buffer[13];
	snprintf(buffer,13, "%2.1f°C L%4d", temperature, lightValue);
}

void Focus::onEnter() {
	m_lightSwitch->workingLightOn(false);
	m_lightSwitch->darkRoomLightOn(true);
	m_lightSwitch->enlargerOn(false);
	printMenu();
}

void Focus::printMenu() {
	printTitle();
	printSensorValues();
}


void Focus::onExit() 
{
	if(m_doFocus) {
		timer.pauseTimer();
		m_doFocus = false;
	}
	m_lightSwitch->workingLightOn(false);
	m_lightSwitch->darkRoomLightOn(true);
	m_lightSwitch->enlargerOn(false);
}


void Focus::onTimerUpdate(const unsigned long remainingMs) {
	printSensorValues();
}


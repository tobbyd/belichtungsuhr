#include "focus.h"
#include "limits.h"


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
		timer.startTimer(this);
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

	const int is = round(temperature*10);
	const int precomma = is / 10;
	const int postcomma = is % 10;
	
	snprintf(buffer, 13, "%2d,%1d C %4dL", precomma, postcomma, lightValue);


	MyLCD::instance().printValue(buffer);
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
	MyLCD::instance().printHints("");
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


#include "belbutton.h"

void ButtonHandler::init(const int PIN_Joystick_X, const int PIN_Joystick_Y, const int PIN_Joystick_Enter, const int PIN_Reset)
{
	m_PIN_Joystick_X = PIN_Joystick_X; 
	m_PIN_Joystick_Y = PIN_Joystick_Y; 
	m_PIN_Joystick_Enter = PIN_Joystick_Enter; 
	m_PIN_Reset = PIN_Reset;
	m_lastJoystickX = JoyStickState::JOYSTICK_MEDIUM;
	m_lastJoystickY = JoyStickState::JOYSTICK_MEDIUM;
	m_lastJoystickEnter = HIGH; // HIGH means not pressed!
	m_lastReset = HIGH;
	
	pinMode(m_PIN_Joystick_Enter, INPUT_PULLUP);
	pinMode(m_PIN_Reset, INPUT_PULLUP);

}

void ButtonHandler::checkTaster(BelButton &result, const int PIN, int &lastValue, BelButton buttonToSet) {
	int currentButton = digitalRead(PIN);
	if(currentButton == LOW) {
		if(lastValue != LOW) {
			result = buttonToSet;
			delay(30); // prell button
		}
	}
	lastValue = currentButton;
}

void ButtonHandler::checkJoystick(BelButton &result, const int PIN, JoyStickState &lastValue, BelButton buttonToSetLow, BelButton buttonToSetHigh) {
	int joystickValue = analogRead(PIN);
	if(joystickValue < JOYSTICK_THRESHOLD) { // 0..32
		if(lastValue != JoyStickState::JOYSTICK_LOW) {
			result = buttonToSetLow;
			delay(30); 
		}
		lastValue = JoyStickState::JOYSTICK_LOW;
	} else if (joystickValue > 1024 - JOYSTICK_THRESHOLD) { // 992..1024
		if(lastValue != JoyStickState::JOYSTICK_HIGH) {
			result = buttonToSetHigh;
			delay(30);
		}
		lastValue = JoyStickState::JOYSTICK_HIGH;
	} else {
		lastValue = JoyStickState::JOYSTICK_MEDIUM;
	}
}

BelButton ButtonHandler::readButton() {
	BelButton result = BelButton::BUTTON_NONE;

	checkTaster(result, m_PIN_Joystick_Enter, m_lastJoystickEnter, BelButton::BUTTON_ENTER); 
	checkTaster(result, m_PIN_Reset, m_lastReset, BelButton::BUTTON_RESET); 
	checkJoystick(result, m_PIN_Joystick_X, m_lastJoystickX, BelButton::BUTTON_UP, BelButton::BUTTON_DOWN);
	checkJoystick(result, m_PIN_Joystick_Y, m_lastJoystickY, BelButton::BUTTON_INC, BelButton::BUTTON_DEC);


	

	return result;
}

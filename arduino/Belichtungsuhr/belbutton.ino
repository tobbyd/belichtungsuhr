#include "belbutton.h"
#include "beeper.h"



void ButtonHandler::init(const int PIN_Joystick_X, const int PIN_Joystick_Y, const int PIN_Joystick_Enter, const int PIN_Reset, const int PIN_IR)
{
	m_PIN_Joystick_X = PIN_Joystick_X; 
	m_PIN_Joystick_Y = PIN_Joystick_Y; 
	m_PIN_Joystick_Enter = PIN_Joystick_Enter; 
	m_PIN_Reset = PIN_Reset;
  m_PIN_IR = PIN_IR;
	m_lastJoystickX = JoyStickState::JOYSTICK_MEDIUM;
	m_lastJoystickY = JoyStickState::JOYSTICK_MEDIUM;
	m_lastJoystickEnter = HIGH; // HIGH means not pressed!
	m_lastReset = HIGH;
	
	pinMode(m_PIN_Joystick_Enter, INPUT_PULLUP);
	pinMode(m_PIN_Reset, INPUT_PULLUP);
  //pinMode(m_PIN_IR, INPUT_PULLUP);
  //attachInterrupt(digitalPinToInterrupt(m_PIN_IR), checkIR, CHANGE);
  irrecv.enableIRIn();

}

bool ButtonHandler::checkIR(BelButton &res) {
  while (irrecv.decode(&m_irresults)) {
    switch(m_irresults.value)
    {

    // Elegoo
    case 0xFF629D: // VOL+ 
    case 0xFF906F: // UP
    // Samsung Blueray
    case 0xD04CFC60: // UP
    res = BelButton::BUTTON_UP;
    break;

    // Elegoo
    case 0xFFA857: // VOL-
    case 0xFFE01F: // DOWN
    // Samsung Blueray
    case 0x61DB14E2: // Down
    res = BelButton::BUTTON_DOWN;
    break;

    // Elegoo
    case 0xFFC23D: // Fast Forward
    // Samsung Blueray
    case 0x6F89644: // Right
    res = BelButton::BUTTON_INC;
    break;

    // Elegoo
    case 0xFF22DD: // Fast Back
    // Samsung Blueray
    case 0x72726A46: // Left
    res = BelButton::BUTTON_DEC;
    break;

    // Elegoo
    case 0xFF02FD: // Play Pause
    // Samsung Blueray
    case 0x20464B24: // Enter
    res = BelButton::BUTTON_ENTER;
    break;

    // Elegoo 
    case 0xFFA25D: // Power
    // Samsung Blueray
    case 0xE4CD1208: // Power
    case 0xF4BA2988: // Source Power
    //res = BelButton::BUTTON_POWER; // not implemented yet
    break;


    // Elegoo
    case 0xFFE21D: // Func/Stop
    // Samsung Blueray
    case 0xCA8FB328: // Tools
    case 0x66387AC0: // Info
    case 0x9D3BF25E: // Return
    case 0x3C50321E: // Exit
    res = BelButton::BUTTON_RESET;
    break;

    default:
    res = BelButton::BUTTON_NONE;
    }
    delay(250);
    irrecv.resume();
  }
  return res != BelButton::BUTTON_NONE;
}



bool ButtonHandler::checkJoystick(BelButton &result, const int PIN, JoyStickState &lastValue, BelButton buttonToSetLow, BelButton buttonToSetHigh) {
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
  return result != BelButton::BUTTON_NONE;
}

bool ButtonHandler::checkTaster(BelButton &result, const int PIN, int &lastValue, BelButton buttonToSet) {
  int currentButton = digitalRead(PIN);
  if(currentButton == LOW) {
    if(lastValue != LOW) {
      result = buttonToSet;
      delay(30); // prell button
    }
  }
  lastValue = currentButton;
  return result != BelButton::BUTTON_NONE;
}

BelButton ButtonHandler::readButton() {
	BelButton result = BelButton::BUTTON_NONE;

  // lazy eval
  (checkIR(result) || 
      checkTaster(result, m_PIN_Joystick_Enter, m_lastJoystickEnter, BelButton::BUTTON_ENTER) || 
      checkTaster(result, m_PIN_Reset, m_lastReset, BelButton::BUTTON_RESET) ||
      checkJoystick(result, m_PIN_Joystick_X, m_lastJoystickX, BelButton::BUTTON_UP, BelButton::BUTTON_DOWN) ||
      checkJoystick(result, m_PIN_Joystick_Y, m_lastJoystickY, BelButton::BUTTON_INC, BelButton::BUTTON_DEC));
      
	return result;
}

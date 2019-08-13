#ifndef _BELBUTTON_H
#define _BELBUTTON_H


#define JOYSTICK_THRESHOLD 32

#include <IRremote.h>


enum class BelButton {
	BUTTON_INC,
	BUTTON_DEC,
	BUTTON_UP,
	BUTTON_DOWN,
	BUTTON_ENTER,
	BUTTON_RESET,	

	BUTTON_NONE,
};

enum class JoyStickState {
	JOYSTICK_LOW,
	JOYSTICK_MEDIUM,
	JOYSTICK_HIGH,
};


class ButtonHandler {
public:
	ButtonHandler() { }
	void init(int PIN_Joystick_X, int PIN_Joystick_y, int PIN_Joystick_Enter, int PIN_Reset, const int PIN_IR);
	BelButton readButton();

  BelButton IR_BelButton;

private:
  bool checkIR(BelButton &result);
	bool checkJoystick(BelButton &result, const int PIN, JoyStickState &lastValue, BelButton buttonToSetLow, BelButton buttonToSetHigh);
  bool checkTaster(BelButton &result, const int PIN, int &lastValue, BelButton buttonToSet);

	int m_PIN_Joystick_X; 
	int m_PIN_Joystick_Y; 
	int m_PIN_Joystick_Enter; 
	int m_PIN_Reset;
  int m_PIN_IR;

	JoyStickState m_lastJoystickX;
	JoyStickState m_lastJoystickY;
	int m_lastJoystickEnter;
	int m_lastReset;
  
  decode_results m_irresults; 
};


#endif // _BELBUTTON_H

#ifndef _BELBUTTON_H
#define _BELBUTTON_H


#define JOYSTICK_THRESHOLD 32

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
	void init(int PIN_Joystick_X, int PIN_Joystick_y, int PIN_Joystick_Enter, int PIN_Reset);
	BelButton readButton();

private:
	void checkTaster(BelButton &result, const int PIN, int &lastValue, BelButton buttonToSet);
	void checkJoystick(BelButton &result, const int PIN, JoyStickState &lastValue, BelButton buttonToSetLow, BelButton buttonToSetHigh);

	int m_PIN_Joystick_X; 
	int m_PIN_Joystick_Y; 
	int m_PIN_Joystick_Enter; 
	int m_PIN_Reset;

	JoyStickState m_lastJoystickX;
	JoyStickState m_lastJoystickY;
//	uint8_t m_lastJoystickEnter;
	int m_lastJoystickEnter;
//	uint8_t m_lastReset;
	int m_lastReset;
};


#endif // _BELBUTTON_H

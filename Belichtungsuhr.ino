
#include "statemachine.h"
#include "belbutton.h"
#include "lightSwitch.h"
#include "myLCD.h"
#include "timer.h"
#include "beeper.h"

#include <LiquidCrystal.h>

#define PIN_JOYSTICK_X 		A1
#define PIN_JOYSTICK_Y 		A2
#define PIN_JOYSTICK_ENTER 	2
#define PIN_RESET 		4

#define PIN_BUZZER 5
ButtonHandler buttonHandler;

//                BS  E  D4 D5  D6 D7
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
// PWM background dim
#define PINBACKLIGHT 6

LightSwitch lightSwitch;

#define STATE_LIGHTSWITCH 0
#define NUMSTATES 1

BelState *states[NUMSTATES];
Timer timer(states);
Beeper beeper(PIN_BUZZER);


void setup() {
	buttonHandler.init(PIN_JOYSTICK_X, PIN_JOYSTICK_Y, PIN_JOYSTICK_ENTER, PIN_RESET);
	Serial.begin(9600);
  lightSwitch.init(3);
  MyLCD::instance().init(&lcd, PINBACKLIGHT);

  states[STATE_LIGHTSWITCH] = &lightSwitch;

  StateMachine::instance().setStates(states);
  StateMachine::instance().setToState(STATE_LIGHTSWITCH);

  StateMachine::instance().execState();
}

void loop() { 
	BelButton currentButton = buttonHandler.readButton();

  if(currentButton == BelButton::BUTTON_UP) {
    Serial.println("Up");
  } else if(currentButton == BelButton::BUTTON_DOWN) {
    Serial.println("Down");
  } else if(currentButton != BelButton::BUTTON_NONE) {
    StateMachine::instance().getCurrentState()->onButtonClicked(currentButton);
    
  }
  
}


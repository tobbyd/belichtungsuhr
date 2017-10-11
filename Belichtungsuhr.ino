
#include "statemachine.h"
#include "belbutton.h"
#include "lightSwitch.h"
#include "myLCD.h"
#include "timer.h"
#include "beeper.h"
#include "chemieClock.h"

#include <LiquidCrystal.h>
#include <RCSwitch.h>

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
ChemieClock devClock("Dev", 60);
ChemieClock fixClock("Fix", 90);


#define STATE_LIGHTSWITCH 0
#define STATE_DEV 1
#define STATE_FIX 2
#define NUMSTATES 3

BelState *states[NUMSTATES];

Timer timer(states);
Beeper beeper(PIN_BUZZER);
RCSwitch sender;


void setup() {
  MyLCD::instance().init(&lcd, PINBACKLIGHT);
  MyLCD::instance().printTitle(F("start Clock..."));

  buttonHandler.init(PIN_JOYSTICK_X, PIN_JOYSTICK_Y, PIN_JOYSTICK_ENTER, PIN_RESET);
  Serial.begin(9600);

  sender.enableTransmit(3);  // An Pin 3
  sender.setProtocol(1);
  sender.setPulseLength(302);
  lightSwitch.init(&sender);
  
  states[STATE_LIGHTSWITCH] = &lightSwitch;
  states[STATE_DEV] = &devClock;
  states[STATE_FIX] = &fixClock;

  StateMachine::instance().setStates(states);
  StateMachine::instance().setToState(STATE_DEV);

  StateMachine::instance().execState();
  beeper.beepbeep();
}

void loop() { 
	BelButton currentButton = buttonHandler.readButton();

  if(currentButton == BelButton::BUTTON_UP) {
    StateMachine::instance().setToState((StateMachine::instance().getCurrentStateNum() + NUMSTATES - 1) % NUMSTATES);
  } else if(currentButton == BelButton::BUTTON_DOWN) {
    StateMachine::instance().setToState((StateMachine::instance().getCurrentStateNum() + 1) % NUMSTATES);
  } else if(currentButton != BelButton::BUTTON_NONE) {
    StateMachine::instance().getCurrentState()->onButtonClicked(currentButton); 
  }
  StateMachine::instance().execState();
  timer.check();
  
}


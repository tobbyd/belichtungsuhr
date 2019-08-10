
#include "statemachine.h"
#include "belbutton.h"
#include "lightSwitch.h"
#include "myLCD.h"
#include "timer.h"
#include "beeper.h"
#include "chemieClock.h"
#include "enlarger.h"
#include "focus.h"

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

Focus focus;
Enlarger enlarger;
// title, default time, turn light on when finished
ChemieClock devClock("Dev");
ChemieClock fixClock("Fix");


#define STATE_FOCUS 0
#define STATE_ENLARGER 1
#define STATE_DEV 2
#define STATE_FIX 3
#define NUMSTATES 4

BelState *states[NUMSTATES];

Timer timer;
Beeper beeper(PIN_BUZZER);
RCSwitch sender;


void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  MyLCD::instance().init(&lcd, PINBACKLIGHT);
  MyLCD::instance().printTitle(F("start Clock..."));

  buttonHandler.init(PIN_JOYSTICK_X, PIN_JOYSTICK_Y, PIN_JOYSTICK_ENTER, PIN_RESET);
  //Serial.begin(9600);

  sender.enableTransmit(3);  // An Pin 3
  sender.setProtocol(1);
  sender.setPulseLength(302);
  
  lightSwitch.init(&sender);
  enlarger.init(&lightSwitch);
  focus.init(&lightSwitch);
  devClock.init(&lightSwitch, 90, false);
  fixClock.init(&lightSwitch, 60, true);
  
  states[STATE_FOCUS] = &focus;
  states[STATE_ENLARGER] = &enlarger;
  states[STATE_DEV] = &devClock;
  states[STATE_FIX] = &fixClock;

  StateMachine::instance().setStates(states, NUMSTATES);
  StateMachine::instance().setToState(STATE_FOCUS);

  StateMachine::instance().execState();
  beeper.beepbeep();
}

void loop() { 
	BelButton currentButton = buttonHandler.readButton();

  if(currentButton == BelButton::BUTTON_UP) {
    StateMachine::instance().prevState();
  } else if(currentButton == BelButton::BUTTON_DOWN) {
    StateMachine::instance().nextState();
  } else if(currentButton != BelButton::BUTTON_NONE) {
    StateMachine::instance().getCurrentState()->onButtonClicked(currentButton); 
  }
  StateMachine::instance().execState();
  timer.check();
  
}


#include "beeper.h"
#include "pitches.h"

// Buzzer just has to be connected to Ground 
// and to the specified PIN to the Buzzer "+" marking


Beeper::Beeper(const int PIN): m_PIN(PIN) {
	pinMode(m_PIN, OUTPUT);
}


void Beeper::beep() const {
  tone(m_PIN, NOTE_A6, 50);
}

void Beeper::beepbeep() const {
  beep();
  delay(100);
  beep();
}

void Beeper::buzz() const {
	tone(m_PIN, NOTE_A4, 100);
}

void Beeper::dec() const {
  tone(m_PIN, NOTE_A6, 50);
  delay(75); // different as up by purpose: down sounds shorter.
  tone(m_PIN, NOTE_A5, 50);
}

void Beeper::next() const {
  tone(m_PIN, NOTE_A4, 50);
  delay(60); 
  tone(m_PIN, NOTE_A5, 50);
  delay(60); 
  tone(m_PIN, NOTE_A6, 50);
}

void Beeper::inc() const {
  tone(m_PIN, NOTE_A5, 50);
  delay(60); 
  tone(m_PIN, NOTE_A6, 50);
}

void Beeper::prev() const {
  tone(m_PIN, NOTE_A6, 50);
  delay(60); 
  tone(m_PIN, NOTE_A5, 50);
  delay(60); 
  tone(m_PIN, NOTE_A4, 50);
}

void Beeper::state(int i) const {
  while(i >= 0) {
    tone(m_PIN, NOTE_E5, 100);
    delay(200);
    i--;
  }
}

void Beeper::tick() const {
	tone(m_PIN, NOTE_A6, 50);
}

void Beeper::timerUp() const {
  tone(m_PIN, NOTE_A6, 50);
  delay(100);
  tone(m_PIN, NOTE_A6, 50);
  delay(100);
  tone(m_PIN, NOTE_A6, 50);
  delay(100);
  tone(m_PIN, NOTE_A6, 50);
}

void Beeper::tock() const {
	tone(m_PIN, NOTE_A2, 5);
}

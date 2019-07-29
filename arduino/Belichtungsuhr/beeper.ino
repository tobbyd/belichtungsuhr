
#include "beeper.h"
#include "pitches.h"


Beeper::Beeper(const int PIN): m_PIN(PIN) {
	pinMode(m_PIN, OUTPUT);
}

void Beeper::buzz() const {
	tone(m_PIN, NOTE_A4, 100);
}

void Beeper::plus() const {
	tone(m_PIN, NOTE_A5, 50);
	delay(60); 
	tone(m_PIN, NOTE_A6, 50);
}

void Beeper::minus() const {
	tone(m_PIN, NOTE_A6, 50);
	delay(75); // different as up by purpose: down sounds shorter.
	tone(m_PIN, NOTE_A5, 50);
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

void Beeper::tick() const {
	tone(m_PIN, NOTE_A6, 50);
}

void Beeper::tock() const {
	tone(m_PIN, NOTE_A2, 5);
}

void Beeper::beep() const {
	tone(m_PIN, NOTE_A6, 50);
}

void Beeper::beepbeep() const {
	beep();
	delay(100);
	beep();
}



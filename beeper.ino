
#include "beeper.h"
#include "frequencies.h"


Beeper::Beeper(const int PIN): m_PIN(PIN) {
	pinMode(m_PIN, output);
}

void Beeper::plus() const {
	tone(buzzer_pin, NOTE_A5, 50);
	delay(60); 
	tone(buzzer_pin, NOTE_A6, 50);
}

void Beeper::minus() const {
	tone(buzzer_pin, NOTE_A6, 50);
	delay(75); // different as up by purpose: down sounds shorter.
	tone(buzzer_pin, NOTE_A5, 50);
}

void Beeper::timerUp() const {
	tone(buzzer_pin, NOTE_A5, 50);
	delay(100);
	tone(buzzer_pin, NOTE_A5, 50);
	delay(100);
	tone(buzzer_pin, NOTE_A5, 50);
	delay(100);
	tone(buzzer_pin, NOTE_A5, 50);
}

void Beeper::tick() const {
	tone(buzzer_pin, NOTE_A5, 50);
}

void Beeper::tock() const {
	tone(buzzer_pin, NOTE_A3, 25);

}


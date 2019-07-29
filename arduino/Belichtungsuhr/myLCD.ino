
#include <LiquidCrystal.h>
#include "myLCD.h"


void MyLCD::init(LiquidCrystal *lcd, const int backlightPIN) {
	m_lcd = lcd;
	m_backlightPIN = backlightPIN;
	byte play[8] = {
		B10000, 
		B11000, 
		B11100, 
		B11110,
		B11100,
		B11000,
		B10000,
		B00000,};
	byte pause[8] = {
		B00000,
		B11011,
		B11011,
		B11011,
		B11011,
		B11011,
		B11011,
		B00000,};
	m_lcd->createChar(0, play);
	m_lcd->createChar(1, pause);

	m_lcd->begin(16, 2);
	darkMode(true);
}

void MyLCD::clearTitle() const {
	m_lcd->setCursor(0, 0);
	m_lcd->print(F("                "));
	m_lcd->setCursor(0, 0);
}

void MyLCD::printTitle(const char *title) const {
	clearTitle();
	m_lcd->print(title);
}
void MyLCD::printTitle(const __FlashStringHelper* title) const {
	clearTitle();
	m_lcd->print(title);
}

void MyLCD::clearHints() const {
	m_lcd->setCursor(0, 1);
	m_lcd->print(F("   "));
	m_lcd->setCursor(0, 1);
}

void MyLCD::play() const {
	clearHints();
	m_lcd->setCursor(0, 1);
	m_lcd->write(byte(0));
}

void MyLCD::pause() const {
	clearHints();
	m_lcd->setCursor(0, 1);
	m_lcd->write(byte(1));
}

void MyLCD::printHints(const char *hints) const {
	clearHints();
	m_lcd->print(hints);
}
void MyLCD::printHints(const __FlashStringHelper *hints) const {
	clearHints();
	m_lcd->print(hints);
}

void MyLCD::clearValue() const {
	m_lcd->setCursor(4, 1);
	m_lcd->print(F("            "));
	m_lcd->setCursor(4, 1);
}

void MyLCD::printValue(const char *values) const {
	clearValue();
	m_lcd->print(values);

}
void MyLCD::printValue(const __FlashStringHelper *values) const {
	clearValue();
	m_lcd->print(values);
}

void MyLCD::darkMode(const bool on) const {
	if(on) {
		analogWrite(m_backlightPIN, DARKMODE_ON_VALUE);
	} else {
		analogWrite(m_backlightPIN, DARKMODE_OFF_VALUE);
	}
}

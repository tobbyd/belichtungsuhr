
#include <LiquidCrystal.h>
#include "myLCD.h"


void MyLCD::init(const LiquidCrystal *lcd, const int backlightPIN) {
	m_lcd = lcd;
	m_backlightPIN = backlightPIN;
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
	m_lcd->print(F("    "));
	m_lcd->setCursor(0, 1);
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
	m_lcd->setCursor(5, 1);
	m_lcd->print(F("          "));
	m_lcd->setCursor(5, 1);
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


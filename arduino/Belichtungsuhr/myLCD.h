#ifndef __MY_LCD_H
#define __MY_LCD_H

#include <LiquidCrystal.h>

#define DARKMODE_OFF_VALUE 31 // 0 <= x < 256
#define DARKMODE_ON_VALUE 1 // 0 <= x < 256

class MyLCD {
public:
	static MyLCD & instance() {
		static MyLCD m_instance;
		return m_instance;
	}

	void init(LiquidCrystal *lcd, const int backlightPIN);
	void pause() const;
	void play() const;
	void printTitle(const char *title) const; // first row, max 16 chars
	void printTitle(const __FlashStringHelper* title) const;
	void printHints(const char *hints) const; // second row left, max 4 chars
	void printHints(const __FlashStringHelper* hints) const; // second row left, max 4 chars
	void printValue(const char *values) const; // second row right, max 12 chars
	void printValue(const __FlashStringHelper* values) const; // second row right, max 12 chars
	void darkMode(const bool on) const;
 
  void clearTitle()const;
  void clearHints()const;
  void clearValue()const;
private:


	MyLCD () { }

	LiquidCrystal *m_lcd;
	int m_backlightPIN;
};


#endif // __MY_LCD_H

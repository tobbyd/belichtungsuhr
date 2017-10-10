#ifndef _BEEPER_H
#define _BEEPER_H

class Beeper {
public:
	Beeper(const int PIN);

	void timerUp() const ;
	void tick() const ;
	void tock() const ;
	void plus() const ;
	void minus() const ;

private:
	m_PIN;
}

#endif // _BEEPER_H


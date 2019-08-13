#ifndef _BEEPER_H
#define _BEEPER_H

class Beeper {
public:
	Beeper(const int PIN);

  void beep() const ;
  void beepbeep() const ;
  void buzz() const ;
  void dec() const ;
  void next() const;
  void inc() const ;
  void prev() const;
  void state(int i) const;
  void tick() const ;
	void timerUp() const ;
	void tock() const ;

private:
	int m_PIN;
};

#endif // _BEEPER_H

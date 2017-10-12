#ifndef _THERMOMETER_H
#define _THERMOMETER_H

// Nenntemperaturwert für den Thermistor
#define THERMISTORNOMINAL 10000
// Nenntemperatur auf dem Datenblatt
#define TEMPERATURENOMINAL 25
// Anzahl der Proben
#define THERMO_NUMSAMPLES 5
// Beta-Wert für unseren Thermistor
#define BCOEFFICIENT 3977
// Wert des Serienwiderstandes
#define THERMO_SERIESRESISTOR 10000

class Thermometer {
public:
	void init(int PIN)  { m_PIN = PIN;}
	float getTemperature();

private:
	int m_PIN;

};

#endif // _THERMOMETER_H


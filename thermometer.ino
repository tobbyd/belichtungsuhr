#include "thermometer.h"

float Thermometer::getTemperature() {
	// TODO: do real calculation
	return 26.42;


	float average;
	float samples[THERMO_NUMSAMPLES];
	int i;

	for (i = 0; i < THERMO_NUMSAMPLES; i++) {
		samples[i] = analogRead(m_PIN);
		delay(10);
	}

	average = 0;
	for (i = 0; i < THERMO_NUMSAMPLES; i++) {
		average += samples[i];
	}
	
	average /= THERMO_NUMSAMPLES;
	
	// Umwandlung des thermischen Spannungswertes in Widerstand
	average = 1023 / average - 1;
	average = THERMO_SERIESRESISTOR / average;

	//Berechnen Sie die Temperatur mit der Beta-Faktor-Gleichung weiteres zur Gleichung bei google
	float steinhart;
	steinhart = average / THERMISTORNOMINAL;     // (R/Ro)
	steinhart = log(steinhart); // ln(R/Ro)
	steinhart /= BCOEFFICIENT;                   // 1/B * ln(R/Ro)
	steinhart += 1.0 / (TEMPERATURENOMINAL + 273.15); // + (1/To)
	steinhart = 1.0 / steinhart;                 // Invertiert den Wert
	steinhart -= 273.15;                         // Umwandeln in Celsius

	return steinhart;
}


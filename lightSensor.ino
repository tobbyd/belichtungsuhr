#include "lightSensor.h"

int LightSensor::getLight() {
	// TODO: fancy calculations?
	return analogRead(m_PIN);
}


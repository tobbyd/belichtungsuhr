#include "lightSensor.h"

int LightSensor::getLight() {
	// TODO: revert dummy value
	return 42;
	// TODO: fancy calculations?
	return analogRead(m_PIN);
}


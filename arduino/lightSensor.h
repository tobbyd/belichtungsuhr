#ifndef _LIGHT_SENSOR_H
#define _LIGHT_SENSOR_H

class LightSensor {
public:
	void init(int PIN) { m_PIN=PIN; }
	int getLight();
private:
	int m_PIN;
};

#endif // _LIGHT_SENSOR_H


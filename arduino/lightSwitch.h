#ifndef _LIGHTSWITCH_H
#define _LIGHTSWITCH_H

#include "statemachine.h"
#include <RCSwitch.h>
	
const char workingLight_On[] = "0FF0FF0FFF0F"; // Working Light / "B"
const char darkRoomLight_On[] = "0FF0FFF0FF0F"; // Darkroom Light / "C"
const char workingLight_Off[] = "0FF0FF0FFFF0";
const char darkRoomLight_Off[] = "0FF0FFF0FFF0";
const char enlarger_On[] = "0FF0F0FFFF0F";
const char enlarger_Off[] = "0FF0F0FFFFF0";

class LightSwitch {
public:
	LightSwitch() { }
	void init(RCSwitch *sender);
	~LightSwitch() { }


	void workingLightOn(bool on);
	void darkRoomLightOn(bool on);
	void enlargerOn(bool on);

private:
	RCSwitch *m_sender;
};

#endif // _LIGHTSWITCH_H

#ifndef _LIGHTSWITCH_H
#define _LIGHTSWITCH_H

#include "statemachine.h"
#include <RCSwitch.h>


enum LightType {
	WorkingLight,
	DarkRoomLight,
	None,
};

#define LIGHTCOUNT 2


const char s1[] = "0FF0FF0FFF0F"; // Working Light / "B"
const char s2[] = "0FF0FFF0FF0F"; // Darkroom Light / "C"
const char s3[] = "0FF0FF0FFFF0";
const char s4[] = "0FF0FFF0FFF0";

const char * const LIGHTONCONST[] = {s1, s2};
const char * const LIGHTOFFCONST[] = {s3, s4 };


class LightSwitch : public BelState {
public:
	LightSwitch() { }
	void init(RCSwitch *sender);
	~LightSwitch() { }

	void onEnter();
	void onButtonClicked(const BelButton &button);

	void lightOn(const LightType &menuEntry);
	void lightOff(const LightType &menuEntry);

private:
	void printMenu();

	LightType m_currentMenuEntry;

	RCSwitch *m_sender;
	bool m_lightOn[LIGHTCOUNT];

};

#endif // _LIGHTSWITCH_H

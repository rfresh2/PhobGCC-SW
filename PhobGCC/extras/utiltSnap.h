#include <cmath>

#ifndef EXTRAS_UTILT_H
#define EXTRAS_UTILT_H


namespace utiltsnap {

	ExtrasSlot extrasUtiltConfigSlot = EXTRAS_UNSET;

	enum UtiltSettings{ // this is limited to 4 setting slots (including toggle)
		UTILT_SETTING_ENABLE,
		UTILT_SETTING_UNSET1, // todo: have settings able to be configured
		UTILT_SETTING_UNSET2,
		UTILT_SETTING_UNSET3
	};

	enum UtiltSettingEnable{
		UTILT_ENABLED,
		UTILT_DISABLED
	};


	void remap(float* Ax, float* Ay, const IntOrFloat config[]){
		if (config[UTILT_SETTING_ENABLE].intValue != UTILT_ENABLED) {
			return;
		}

		// We're trying to hit the green color on https://i.imgur.com/s1owyUY.png
		if (abs(*Ax) <= 30 && *Ay >= 13 && *Ay <= 52) {
			*Ay = max(*Ay, 28);
			// snap x for turnaround tilts
			// we want to hit the green triangles on the side from above image
			if (*Ax >= 13) { // expands out to x = 30
				*Ax = 23;
			}
			if (*Ax <= -13) { // expands out to x = -30
				*Ax = -23;
			}
		}

		return;
	}

	bool toggle(IntOrFloat config[]) {
		int& enabled = config[UTILT_SETTING_ENABLE].intValue;
		if (enabled != UTILT_DISABLED){
			enabled = UTILT_DISABLED;
		} else {
			enabled = UTILT_ENABLED;
		}
		setExtrasSettingInt(extrasUtiltConfigSlot, UTILT_SETTING_ENABLE, enabled);
		return (enabled == UTILT_ENABLED);
	}
}

#endif // EXTRA_UTILT_H
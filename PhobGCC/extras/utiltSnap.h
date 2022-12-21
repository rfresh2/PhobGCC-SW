#include <cmath>

#ifndef EXTRAS_UTILT_H
#define EXTRAS_UTILT_H


namespace utiltsnap {

	ExtrasSlot extrasUtiltConfigSlot = EXTRAS_UNSET;

	enum UtiltSettings{
		UTILT_SETTING_ENABLE,
		UTILT_SETTING_MIN_AY, // todo: have settings able to be configured
		UTILT_SETTING_MAX_AY,
		UTILT_SETTING_AX_RANGE,
        UTILT_SETTING_SNAP_AY
	};

	enum UtiltSettingEnable{
        UTILT_ENABLED,
		UTILT_DISABLED
	};


	void remap(float* Ax, float* Ay, const IntOrFloat config[]){
		if (config[UTILT_SETTING_ENABLE].intValue != UTILT_ENABLED) {
			return;
		}

		if (abs(*Ax) <= 28 && *Ay >= 13 && *Ay <= 52) {
			*Ay = max(*Ay, 28);
			if (*Ax >= 15) {
				*Ax = max(*Ax, 23);
			}
			if (*Ax <= -15) {
				*Ax = min(*Ax, -23);
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
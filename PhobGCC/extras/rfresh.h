#include <cmath>

#ifndef EXTRAS_RFRESH_H
#define EXTRAS_RFRESH_H


namespace rfresh {

	ExtrasSlot extrasRfreshConfigSlot = EXTRAS_UNSET;

	enum RfreshSettings{ // this is limited to 4 setting slots (including toggle)
		RFRESH_SETTING_ENABLE,
		RFRESH_SETTING_UNSET1, // todo: have settings able to be configured
		RFRESH_SETTING_UNSET2,
		RFRESH_SETTING_UNSET3
	};

	enum RfreshSettingEnable{
		RFRESH_ENABLED,
		RFRESH_DISABLED
	};

    void shieldDrop(float* Ax, float* Ay, const IntOrFloat config[]){
        if (abs(*Ax) <= 22 && *Ay <= -23 && *Ay >= -54) {
            *Ay = -54;
        }
        return;
    }

    void perfectAngles(float* Ax, float* Ay, const IntOrFloat config[]){
        int sAngle = 8;
        int dAngle = 30;
        int cardinalAngle = 70;
        // X axis
        if (*Ay >= sAngle && *Ay <= dAngle && *Ax >= cardinalAngle) {
            *Ax = 75;
            *Ay = 23;
        }
        if (*Ay <= -sAngle && *Ay >= -dAngle && *Ax >= cardinalAngle) {
            *Ax = 75;
            *Ay = -23;
        }
        if (*Ay >= sAngle && *Ay <= dAngle && *Ax <= -cardinalAngle) {
            *Ax = -75;
            *Ay = 23;
        }
        if (*Ay <= -sAngle && *Ay >= -dAngle && *Ax <= -cardinalAngle) {
            *Ax = -75;
            *Ay = -23;
        }

        // Y axis
        if (*Ax >= sAngle && *Ax <= dAngle && *Ay >= cardinalAngle) {
            *Ax = 23;
            *Ay = 75;
        }
        if (*Ax <= -sAngle && *Ax >= -dAngle && *Ay >= cardinalAngle) {
            *Ax = -23;
            *Ay = 75;
        }
        if (*Ax >= sAngle && *Ax <= dAngle && *Ay <= -cardinalAngle) {
            *Ax = 23;
            *Ay = -75;
        }
        if (*Ax <= -sAngle && *Ax >= -dAngle && *Ay <= -cardinalAngle) {
            *Ax = -23;
            *Ay = -75;
        }
        return;
    }

    void cardinals(float* Ax, float* Ay, const IntOrFloat config[]){
        if((abs(*Ax) <= 7) && (abs(*Ay) >= 75)){
			*Ax = 0;
            if (*Ay >= 75) {
                *Ay = 80;
            } else {
                *Ay = -80;
            }
		}
		if((abs(*Ay) <= 7) && (abs(*Ax) >= 75)){
			*Ay = 0;
            if (*Ax >= 75) {
                *Ax = 80;
            } else {
                *Ax = -80;
            }
		}
        return;
    }

    void uptiltSnap(float* Ax, float* Ay, const IntOrFloat config[]){
        // We're trying to hit the green color on https://i.imgur.com/s1owyUY.png
		if (abs(*Ax) <= 30 && *Ay >= 13 && *Ay <= 52) {
			*Ay = max(*Ay, 28.0f);
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

    void remap(float* Ax, float* Ay, const IntOrFloat config[]){
		// if (config[RFRESH_SETTING_ENABLE].intValue != RFRESH_ENABLED) {
		// 	return;
		// }
        // rfresh::cardinals(Ax, Ay, config);
        // rfresh::perfectAngles(Ax, Ay, config);
        rfresh::uptiltSnap(Ax, Ay, config);
        rfresh::shieldDrop(Ax, Ay, config);

		return;
	}

	bool toggle(IntOrFloat config[]) {
		int& enabled = config[RFRESH_SETTING_ENABLE].intValue;
		if (enabled != RFRESH_DISABLED){
			enabled = RFRESH_DISABLED;
		} else {
			enabled = RFRESH_ENABLED;
		}
		setExtrasSettingInt(extrasRfreshConfigSlot, RFRESH_SETTING_ENABLE, enabled);
		return (enabled == RFRESH_ENABLED);
	}
}

#endif // EXTRA_RFRESH_H
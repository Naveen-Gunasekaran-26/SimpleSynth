#ifndef _CUSTOM_CLASS_
#define _CUSTOM_CLASS_
#include <SDL.h>


class ParameterSmoother {

public:

	ParameterSmoother(float smoothingTime, int sampleRate) {

		a = exp((-2 * M_PI) / smoothingTime * 0.001 * sampleRate);
		b = 1.0 - a;
		z = 0.0;
	}

	inline double process(float input) {
		z = (input * b) + (z * a);
		return z;
	}

private:

	double a, b, z;

};





#endif
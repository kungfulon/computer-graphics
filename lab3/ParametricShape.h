#pragma once

#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define SAMPLES 2000

class ParametricShape
{
public:
	virtual void draw();

protected:
	virtual double fX(double z) = 0;
	virtual double fY(double z) = 0;
	
	virtual double step() {
		return 2 * M_PI / samples();
	}
	
	virtual int samples() {
		return SAMPLES;
	}
};

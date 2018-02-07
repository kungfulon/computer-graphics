#pragma once

#include "ParametricShape.h"

class Rose : public ParametricShape
{
public:
	Rose(int k, double amplitude) : k(k), amplitude(amplitude) {

	}

protected:
	double fX(double z) {
		return amplitude * cos(k * z) * cos(z);
	}

	double fY(double z) {
		return amplitude * cos(k * z) * sin(z);
	}

private:
	int k;
	double amplitude;
};
#pragma once

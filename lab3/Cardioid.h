#pragma once

#include "ParametricShape.h"

class Cardioid : public ParametricShape
{
public:
	Cardioid(double radius) : radius(radius) {

	}

protected:
	double fX(double z) {
		return 2 * radius * (1 - cos(z)) * cos(z);
	}

	double fY(double z) {
		return 2 * radius * (1 - cos(z)) * sin(z);
	}

private:
	double radius;
};

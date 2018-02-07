#pragma once

#include "ParametricShape.h"

class ArchimedeanSpiral : public ParametricShape
{
public:
	ArchimedeanSpiral(double turn, double tightness) : turn(turn), tightness(tightness) {

	}

protected:
	double fX(double z) {
		return tightness * z * cos(z + turn);
	}

	double fY(double z) {
		return tightness * z * sin(z + turn);
	}

	int samples() {
		return tightness * __super::samples() * 7;
	}

private:
	double turn;
	double tightness;
};

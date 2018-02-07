#include <windows.h>
#include <gl/GL.h>
#include "ParametricShape.h"

void ParametricShape::draw() {
	glBegin(GL_LINE_STRIP);
	double z = 0.0;

	for (int i = 0; i < SAMPLES; ++i, z += step()) {
		glVertex2d(fX(z), fY(z));
	}

	glEnd();
}

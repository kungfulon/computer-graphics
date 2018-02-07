#include <windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <gl/glut.h>
#include <cstdio>
#include "Cardioid.h"
#include "Rose.h"
#include "ArchimedeanSpiral.h"

const double ANGLES_MODIFIER[4] = { 0.0, -60.0, 120.0, -60.0 };

inline double degreesToRadians(double deg) {
	return deg * M_PI / 180.0;
}

void myInit(void) {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	glPointSize(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

void koch_recur(int level, double prev_x, double prev_y, double x, double y, double line_len, double angles, bool flip) {
	if (level == 0) {		
		glVertex2d(prev_x, prev_y);
		glVertex2d(x, y);
	} else {
		--level;
		line_len /= 3.0;

		for (int i = 0; i < 4; ++i) {
			double anglesModifier = degreesToRadians(ANGLES_MODIFIER[i]);
			angles += (!flip) ? anglesModifier : -anglesModifier;
			x = prev_x + cos(angles) * line_len, y = prev_y + sin(angles) * line_len;
			koch_recur(level, prev_x, prev_y, x, y, line_len, angles, flip);
			prev_x = x, prev_y = y;
		}
	}
}

void koch_line(int level, double prev_x, double prev_y, double x, double y, double line_len, double angles, bool flip) {
	glBegin(GL_LINE_STRIP);
	koch_recur(level, prev_x, prev_y, x, y, line_len, angles, flip);
	glEnd();
}

void drawKochSnowflake(int generation) {
	koch_line(generation, -0.5, -0.25, -0.5, -0.25, 1.0, 0.0, false);
	koch_line(generation, -0.5, -0.25, -0.5, -0.25, 1.0, degreesToRadians(60.0), true);
	koch_line(generation, 0.5, -0.25, 0.5, -0.25, 1.0, degreesToRadians(120.0), false);
}

void myDisplay(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	
	glViewport(0, 250, 250, 250);
	drawKochSnowflake(5);

	glViewport(300, 250, 250, 250);
	Cardioid c(0.25);
	c.draw();

	glViewport(0, 0, 250, 250);
	Rose r(6, 0.75);
	r.draw();

	glViewport(250, 0, 250, 250);
	ArchimedeanSpiral a(0.0, 0.02);
	a.draw();
	

	glFlush();
}

int main(int argc, char *argv[]) {
	// Initialize GLUT.
	glutInit(&argc, argv);
	// Set the mode to draw in.
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	// Set the window size in screen pixels.
	glutInitWindowSize(500, 500);
	// Set the window position in screen pixels.
	glutInitWindowPosition(0, 0);
	// Create the window.
	glutCreateWindow("Lab");
	// Set the callback funcion to call when we need to draw something.
	glutDisplayFunc(myDisplay);
	// Initialize some things.
	myInit();
	// Now that we have set everything up, loop responding to events.
	glutMainLoop();
}

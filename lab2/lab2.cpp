/* Module      : MainFile.cpp
* Author      :
* Email       :
* Course      : Computer Graphics
*
* Description :
*
*
* Date        :
*
* History:
* Revision      Date          Changed By
* --------      ----------    ----------
* 01.00         ?????          ???
* First release.
*
*/

/* -- INCLUDE FILES ------------------------------------------------------ */
#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>

#include <iostream>
#include <fstream>
#include <vector>

/* -- DATA STRUCTURES ---------------------------------------------------- */
// Our point class.
class GLfloatPoint {
private:
	GLfloat x, y;

public:
	GLfloatPoint() : x(0), y(0) { }
	GLfloatPoint(GLfloat x, GLfloat y) : x(x), y(y) { }
	void glVertex() {
		glVertex2f(x, y);
	}
};

/* -- GLOBAL VARIABLES --------------------------------------------------- */
int g_iMode = 3;

/* -- LOCAL VARIABLES ---------------------------------------------------- */


/* ----------------------------------------------------------------------- */
/* Function    : void drawDot( GLint x, GLint y )
*
* Description : Draw a point at location (x, y) in the window.
*
* Parameters  : GLint x : X coordinate of point to draw.
*               GLint y : X coordinate of point to draw.
*
* Returns     : void
*/

void drawDot(GLfloat x, GLfloat y) {
	glBegin(GL_POINTS);
	glVertex2f(x, y);
	glEnd();
}

void drawPolygon(GLfloat n, ...) {
	va_list vl;
	va_start(vl, n);

	glBegin(GL_POLYGON);

	for (int i = 0; i < n; ++i) {
		GLfloatPoint point = va_arg(vl, GLfloatPoint);
		point.glVertex();
	}

	glEnd();
}

void drawPolyline(std::vector<GLfloatPoint> pts) {
	glBegin(GL_LINE_STRIP);

	for (size_t i = 0; i < pts.size(); ++i) {
		pts[i].glVertex();
	}

	glEnd();
}

void drawPolylineFile(const char *file) {
	std::ifstream fData(file);

	if (!fData.bad()) {
		int cnt;
		fData >> cnt;

		while (cnt--) {
			int n;
			fData >> n;
			std::vector<GLfloatPoint> pts(n);
			GLfloat x, y;

			for (int i = 0; i < n; ++i) {
				fData >> x >> y;
				pts[i] = GLfloatPoint(x, y);
			}

			drawPolyline(pts);
		}
	}
}

/* ----------------------------------------------------------------------- */
/* Function    : void myInit( void )
*
* Description : Initialize OpenGL and the window where things will be
*               drawn.
*
* Parameters  : void
*
* Returns     : void
*/

void myInit(void) {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	glPointSize(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 800.0, 0.0, 600.0);
}


/* ----------------------------------------------------------------------- */
/* Function    : void myDisplay( void )
*
* Description : This function gets called everytime the window needs to
*               be redrawn.
*
* Parameters  : void
*
* Returns     : void
*/

void myDisplay(void) {
	glClear(GL_COLOR_BUFFER_BIT);

	switch (g_iMode) {
	case 1:
		drawPolylineFile("dinosaur.dat");
		break;
	case 2:
		for (int i = 0; i < 5; ++i) {
			for (int j = 0; j < 5; ++j) {
				glViewport(160 * i, 120 * j, 160, 120);
				drawPolylineFile("dinosaur.dat");
			}
		}
		break;
	case 3:
		for (int i = 0; i < 5; ++i) {
			for (int j = 0; j < 5; ++j) {
				glMatrixMode(GL_PROJECTION);
				glLoadIdentity();

				if ((i + j) % 2) {
					gluOrtho2D(0.0, 800.0, 0.0, 600.0);
				} else {
					gluOrtho2D(0.0, 800.0, 600.0, 0.0);
				}

				glViewport(160 * i, 120 * j, 160, 120);
				drawPolylineFile("dinosaur.dat");
			}
		}
		break;
	}

	glFlush();
}


/* ----------------------------------------------------------------------- */
/* Function    : int main( int argc, char** argv )
*
* Description : This is the main function. It sets up the rendering
*               context, and then reacts to user events.
*
* Parameters  : int argc     : Number of command-line arguments.
*               char *argv[] : Array of command-line arguments.
*
* Returns     : int : Return code to pass to the shell.
*/

int main(int argc, char *argv[]) {
	// Initialize GLUT.
	glutInit(&argc, argv);
	// Set the mode to draw in.
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	// Set the window size in screen pixels.
	glutInitWindowSize(800, 600);
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

/* ----------------------------------------------------------------------- */


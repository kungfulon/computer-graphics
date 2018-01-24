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

/* -- DATA STRUCTURES ---------------------------------------------------- */
// Our point class.
class GLintPoint {
private:
	GLint x, y;

public:
	GLintPoint() : x(0), y(0) { }
	GLintPoint(int x, int y) : x(x), y(y) { }
	void glVertex() {
		glVertex2i(x, y);
	}
};

/* -- GLOBAL VARIABLES --------------------------------------------------- */

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

void drawDot(GLint x, GLint y) {
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

void drawPolygon(GLint n, ...) {
	va_list vl;
	va_start(vl, n);

	glBegin(GL_POLYGON);

	for (int i = 0; i < n; ++i) {
		GLintPoint point = va_arg(vl, GLintPoint);
		point.glVertex();
	}

	glEnd();
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
	glPointSize(5.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 640.0, 480.0, 0.0);
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
	drawDot(10, 10);
	drawDot(20, 30);
	drawDot(30, 50);
	glColor3f(1.0, 0.0, 0.0);
	drawPolygon(3, GLintPoint(100, 100), GLintPoint(300, 100), GLintPoint(200, 50));
	glColor3f(0.0, 0.0, 1.0);
	drawPolygon(4, GLintPoint(125, 100), GLintPoint(275, 100), GLintPoint(275, 200), GLintPoint(125, 200));
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
	glutInitWindowSize(640, 480);
	// Set the window position in screen pixels.
	glutInitWindowPosition(100, 150);
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


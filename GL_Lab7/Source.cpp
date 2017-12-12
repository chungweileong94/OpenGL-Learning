#include <windows.h>
#include <math.h>
#include <GL\glut.h>
#include <string>

#define PI 3.14159265

using namespace std;

void drawPoint(GLint x, GLint y, GLfloat size) {
	glPointSize(size);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

void drawRegularPolygon(GLint x, GLint y,
	GLint radius, GLint side,
	GLfloat orientation) {
	GLint xp, yp;
	glBegin(GL_POLYGON);
	for (int i = 0; i < side; i++) {
		xp = (int)(x + radius * cos(orientation + 2 * PI / side*i));
		yp = (int)(y + radius * sin(orientation + 2 * PI / side*i));
		glVertex2i(xp, yp);
	}
	glEnd();
}

void drawTriangle(GLint x1, GLint y1,
	GLint x2, GLint y2,
	GLint x3, GLint y3) {
	glBegin(GL_TRIANGLES);
	glVertex2i(x1, y1);
	glVertex2i(x2, y2);
	glVertex2i(x3, y3);
	glEnd();
}

void drawText(const char* text, GLint length, GLint x, GLint y) {
	glMatrixMode(GL_PROJECTION);
	double* matrix = new double[16];
	glGetDoublev(GL_PROJECTION_MATRIX, matrix);
	glLoadIdentity();
	glOrtho(0, 800, 0, 600, -5, 5);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();
	glLoadIdentity();
	glRasterPos2i(x, y);
	for (int i = 0; i < length; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int)text[i]);
	}
	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(matrix);
	glMatrixMode(GL_MODELVIEW);
}

void renderScene() {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Background color

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 800, 0, 600);

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 0.0f, 0.0f); // Set brush color to red
	drawPoint(400, 300, 5.0);

	glColor3f(0.0f, 1.0f, 0.0f); // Set brush color to green
	drawTriangle(0, 0, 0, 100, 100, 100);

	glColor3f(0.0f, 0.0f, 1.0f); // Set brush color to blue
	drawRegularPolygon(400, 300, 100, 500, 0);

	string text = "Hello, World";
	drawText(text.data(), text.size(), 0, 400);

	glFlush();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Hello OpenGL!");
	glutDisplayFunc(renderScene);
	glutMainLoop();


	system("PAUSE");
	return 0;
}
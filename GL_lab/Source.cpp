//#include <Windows.h>
#include <GL\glut.h>

using namespace std;

void drawPoint(GLint x, GLint y, GLfloat size);
void drawTriangle(GLint x1, GLint y1, GLint x2, GLint y2, GLint x3, GLint y3);
int main(int argc, char ** argv);
void render();

void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(640, 480);
	glutCreateWindow("OpenGL");
	glutDisplayFunc(render);

	glutMainLoop();
}

void drawPoint(GLint x, GLint y, GLfloat size) {
	glPointSize(size);
	glBegin(GL_POINTS);

	glVertex2i(x, y);

	glEnd();
}

void drawTriangle(GLint x1, GLint y1, GLint x2, GLint y2, GLint x3, GLint y3) {
	glBegin(GL_TRIANGLES);

	glVertex2i(x1, y1);
	glVertex2i(x2, y2);
	glVertex2i(x3, y3);

	glEnd();
}

void render() {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 800, 0, 600);

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 0, 0);
	drawPoint(400, 300, 4);

	glColor3f(0, 1.0f, 0);
	drawTriangle(0, 0, 0, 100, 100, 100);
	glFlush();
}
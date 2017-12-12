#include <GL/glut.h>
#include "Object.h"

int width = 800, height = 600;
Object sprite01 = Object(width / 2, height / 2, .1, .1, 0, 20);
Object sprite02 = Object(width / 2, height / 2 - 100, .1, .1, 0, 20);
Object sprite03 = Object(width / 2, height / 2 + 200, .1, .1, 0, 1);

void draw();

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Animation");

	glutDisplayFunc(draw);

	glutMainLoop();

	system("PAUSE");
	return 0;
}

void draw()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, width, 0, height);

	glClear(GL_COLOR_BUFFER_BIT);

	glColor3i(0, 0, 0);
	sprite01.drawPoint();
	if (sprite01.x >= width)
	{
		sprite01.xVel = -sprite01.xVel;
	}
	else if (sprite01.x <= 0) {
		sprite01.xVel = -sprite01.xVel;
	}
	sprite01.translate(sprite01.xVel, 0);

	sprite02.drawPoint();
	sprite02.rotate(width / 2, height / 2, 100);

	glColor3i(1, 0, 0);
	sprite03.drawPoint();
	sprite03.scale(1.001);

	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();
}


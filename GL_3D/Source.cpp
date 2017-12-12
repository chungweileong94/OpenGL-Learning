//#include <windows.h>
#include <GL/glut.h>
#include "space.h"
#include "model.h"

using namespace std;
using model::World;

World world;

ViewFrustum viewer;
Window window;
WorldTransform worldTransform;
Transform transform;

void windowSettings() {
	window.title = "3d space";
	window.offsetX = 50;
	window.offsetY = 50;
	window.width = 800;
	window.height = 600;
}

void spaceSettings() {
	viewer.eyeX = 0.0;
	viewer.eyeY = 0.0;
	viewer.eyeZ = 40.0;
	viewer.refX = 0.0;
	viewer.refY = 0.0;
	viewer.refZ = 0.0;
	viewer.nearZ = 0.1;
	viewer.farZ = 500.0;
	viewer.upX = 0.0;
	viewer.upY = 1.0;
	viewer.upZ = 0.0;
	viewer.fieldOfView = 60.0;
	viewer.aspectRatio = static_cast<GLdouble> (window.width / window.height);
}

void init() {
	windowSettings();
	spaceSettings();
	worldTransform.tX = 0.0;
	worldTransform.tY = 0.0;
	worldTransform.tZ = 0.0;
	worldTransform.rotateX = 0.0;
	worldTransform.rotateY = 0.0;
	worldTransform.rotateZ = 0.0;
	worldTransform.sX = 1.0;
	worldTransform.sY = 1.0;
	worldTransform.sZ = 1.0;
	transform.displayAmt = 1.0;
	transform.rotateAmt = 2.0;
}

void perspectiveView() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(viewer.fieldOfView, viewer.aspectRatio, viewer.nearZ, viewer.farZ);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(viewer.eyeX, viewer.eyeY, viewer.eyeZ, viewer.refX, viewer.refY, viewer.refZ, viewer.upX, viewer.upY, viewer.upZ);
}

void renderer(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();

	glTranslatef(worldTransform.tX, worldTransform.tY, worldTransform.tZ);
	glRotatef(worldTransform.rotateX, 1.0f, 0.0f, 0.0f);
	glRotatef(worldTransform.rotateY, 0.0f, 1.0f, 0.0f);
	glRotatef(worldTransform.rotateZ, 0.0f, 0.0f, 1.0f);

	world.draw();
	glPopMatrix();
	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();
}

void reshapeVIew(GLint width, GLint height) {
	window.width = width;
	window.height = height;
	glViewport(0, 0, width, height);
}

void lighting() {
	static GLfloat diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	static GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	static GLfloat ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	static GLfloat specref[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	static GLfloat position[] = { 10.0f, 10.0f, 10.0f, 1.0f };
	short shininess = 255;

	glDisable(GL_LIGHTING);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glEnable(GL_LIGHT0);

	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
	glMateriali(GL_FRONT, GL_SHININESS, shininess);

	glEnable(GL_NORMALIZE);

	glEnable(GL_LIGHTING);
}

void keyboardControl1(unsigned char key, GLint x, GLint y) {
	GLfloat displayX, displayY, displayZ;
	displayX = displayY = displayZ = 0.0;
	switch (key) {
	case 'a': case 'A': displayX = -transform.displayAmt;	break;
	case 'd': case 'D': displayX = transform.displayAmt;	break;
	case 'q': case 'Q': displayY = -transform.displayAmt;	break;
	case 'e': case 'E': displayY = transform.displayAmt;	break;
	case 'w': case 'W': displayZ = -transform.displayAmt;	break;
	case 's': case 'S': displayZ = transform.displayAmt;	break;

	}
	worldTransform.translate(displayX, displayY, displayZ);
	glutPostRedisplay();
}

void keyboardControl2(GLint key, GLint x, GLint y) {
	switch (key) {
	case GLUT_KEY_DOWN: break;
	case GLUT_KEY_UP: break;
	case GLUT_KEY_LEFT: break;
	case GLUT_KEY_RIGHT: break;
	case GLUT_KEY_HOME:
		init();
	}
	glutPostRedisplay();
}

void mouseControl(GLint button, GLint state, int x, int y) {
	y = window.height - y;

	switch (button)
	{
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN && !transform.leftMouseIsPressed)
		{
			transform.mouseX = x;
			transform.mouseY = y;
			transform.leftMouseIsPressed = true;
		}

		if (state == GLUT_UP&&transform.leftMouseIsPressed)
		{
			transform.leftMouseIsPressed = false;
		}
		break;
	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN && !transform.rightMouseIsPressed)
		{
			transform.mouseX = x;
			transform.mouseY = y;
			transform.rightMouseIsPressed = true;
		}

		if (state == GLUT_UP && transform.rightMouseIsPressed)
		{
			transform.rightMouseIsPressed = false;
		}
		break;
	}
}

void mouseMoveControl(int x, int y) {
	y = window.height - y;
	GLint dx = x - transform.mouseX;
	GLint dy = y - transform.mouseY;

	if (transform.leftMouseIsPressed)
	{
		worldTransform.rotate(-dy*0.2f, 0, 0);
		worldTransform.rotate(0, dx*0.2f, 0.0f);
	}

	/*if (transform.rightMouseIsPressed)
	{
		worldTransform.rotate(0, dx*0.2f, 0.0f);
	}*/

	transform.mouseX = x;
	transform.mouseY = y;
	glutPostRedisplay();
}

void main(int argc, char** argv) {
	init();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);
	glutInitWindowPosition(window.offsetX, window.offsetY);
	glutInitWindowSize(window.width, window.height);
	glutCreateWindow(window.title.c_str());
	glutDisplayFunc(renderer);
	glutReshapeFunc(reshapeVIew);
	glutKeyboardFunc(keyboardControl1);
	glutSpecialFunc(keyboardControl2);

	glutMouseFunc(mouseControl);
	glutMotionFunc(mouseMoveControl);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CCW);
	glClearColor(0, 0, 0, 0);
	glEnable(GL_CULL_FACE);

	perspectiveView();

	lighting();

	glutMainLoop();
}
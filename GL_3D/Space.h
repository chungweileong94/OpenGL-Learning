#ifndef SPACCE_H
#define SPACE_H
#include <string>
#include <GL\glut.h>

using namespace std;

struct Window {
	string title;
	GLint offsetX;
	GLint offsetY;
	GLint width;
	GLint height;
};


struct ViewFrustum {
	GLdouble eyeX, eyeY, eyeZ;
	GLdouble refX, refY, refZ;
	GLdouble upX, upY, upZ;
	GLdouble nearZ, farZ;
	GLdouble fieldOfView; //Angle in Y direction
	GLdouble aspectRatio;
};

struct WorldTransform
{
	GLdouble rotateX, rotateY, rotateZ;
	GLdouble tX, tY, tZ;
	GLdouble sX, sY, sZ;

	void translate(GLfloat dX, GLfloat dY, GLfloat dZ) {
		tX += dX;
		tY += dY;
		tZ += dZ;
	}

	void rotate(GLfloat dX, GLfloat dY, GLfloat dZ) {
		rotateX += dX;
		rotateY += dY;
		rotateZ += dZ;
	}
};

struct Transform
{
	GLdouble displayAmt;
	GLdouble rotateAmt;

	GLint mouseX, mouseY;
	bool leftMouseIsPressed, rightMouseIsPressed;
};

#endif // !SPACCE_H

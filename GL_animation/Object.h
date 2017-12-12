#ifndef OBJECT_H
#define OBJECT_H
#include <GL/glut.h>

#define PI 3.14159265

class Object
{
public:
	Object();
	Object(GLfloat x, GLfloat y, GLfloat xVel, GLfloat yVel, GLfloat angle, GLfloat size);
	void drawPoint();
	void translate(GLfloat tx, GLfloat ty);
	void rotate(GLfloat centerX, GLfloat centerY, GLfloat radius);
	void scale(GLfloat factor);

	GLfloat x, y, xVel, yVel, angle, size;
};

#endif // !OBJECT_H

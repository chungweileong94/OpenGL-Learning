#include "Object.h"
#include <math.h>

Object::Object() {}

Object::Object(GLfloat x, GLfloat y, GLfloat xVel, GLfloat yVel, GLfloat angle, GLfloat size)
{
	this->x = x;
	this->y = y;
	this->xVel = xVel;
	this->yVel = yVel;
	this->angle = angle;
	this->size = size;
}


void Object::drawPoint()
{
	glPointSize(size);
	glBegin(GL_POINTS);
	glVertex2i(this->x, this->y);
	glEnd();
}

void Object::translate(GLfloat tx, GLfloat ty)
{
	this->x += tx;
	this->y += ty;
}

void Object::rotate(GLfloat centerX, GLfloat centerY, GLfloat radius)
{
	this->x = centerX + radius*cos(angle*PI / 180);
	this->y = centerY + radius*sin(angle*PI / 180);

	if (angle < 360)
	{
		angle++;
	}
	else {
		angle = 0;
	}
}

void Object::scale(GLfloat factor)
{
	size = size * factor;
}

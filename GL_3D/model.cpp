#include "model.h"
#include "GL\glut.h"

void model::Teapot::draw()
{
	glColor3f(1.0f, 1.0f, 0.0f);
	glFrontFace(GL_CW);
	glutSolidTeapot(5);
	glFrontFace(GL_CCW);
}

void model::Box::draw()
{
	static GLfloat vertices[8][3] = {
		{ -5.0f, -5.0f, 5.0f },
		{ 5.0f, -5.0f, 5.0f },
		{ 5.0f, -5.0f, -5.0f },
		{ -5.0f, -5.0f, -5.0f },
		{ -5.0f, 5.0f, 5.0f },
		{ 5.0f, 5.0f, 5.0f },
		{ 5.0f, 5.0f, -5.0f },
		{ -5.0f, 5.0f, -5.0f }
	};

	static int faces[6 * 4] = {
		3, 0, 4, 7,
		3, 2, 1, 0,
		2, 3, 7, 6,
		1, 2, 6, 5,
		4, 5, 6, 7,
		0, 1, 5, 4
	};

	static GLfloat normals[6][3] = {
		{ -1.0f, 0.0f, 0.0f },
		{ 0.0f, -1.0f, 0.0f },
		{ 0.0f, 0.0f, -1.0f },
		{ 1.0f, 0.0f, 0.0f },
		{ 0.0f, 1.0f, 0.0f },
		{ 0.0f, 0.0f, 1.0f }
	};

	static GLfloat colors[6][3] = {
		{ 1.0f, 0.0f, 0.0f },
		{ 0.0f, 1.0f, 0.0f },
		{ 0.0f, 0.0f, 1.0f },
		{ 1.0f, 1.0f, 0.0f },
		{ 0.0f, 1.0f, 1.0f },
		{ 1.0f, 0.0f, 1.0f }
	};

	int numberOfFace = 6;
	int verticesPerFace = 4;

	int n = 0;
	glColor3f(1.0f, 0.0f, 1.0f);
	for (int i = 0; i < numberOfFace; i++)
	{
		glColor3fv(colors[i]);
		glBegin(GL_POLYGON);
		glNormal3fv(normals[i]);
		for (int j = 0; j < verticesPerFace; j++)
		{
			glVertex3fv(vertices[faces[n++]]);
		}
		glEnd();
	}
}

void model::World::draw()
{
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 10.0f);
	teapot.draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, -3.0f, 0.0f);
	glScalef(1.0f, 1.0f, 1.0f);
	box.draw();
	glPopMatrix();
}

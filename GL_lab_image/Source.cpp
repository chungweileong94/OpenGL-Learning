#include <iostream>
#include <windows.h>
#include <math.h>
#include <gl/glut.h>
#include <string>
#include "image.h"
#include "texture.h"

#define PI 3.14159265

using namespace std;

GLuint textureMap[2]; // Number of maps to load
Map checkerMap = Map(64, 64, 3);
GLuint bmpTexture = 0;

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

void drawText(const char *text, GLint length,
	GLint x, GLint y) {
	glMatrixMode(GL_PROJECTION);
	double *matrix = new double[16];
	glGetDoublev(GL_PROJECTION_MATRIX, matrix);
	glLoadIdentity();
	glOrtho(0, 800, 0, 600, -5, 5);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();
	glLoadIdentity();
	glRasterPos2i(x, y);
	for (int i = 0; i < length; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,
			(int)text[i]);
	}
	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(matrix);
	glMatrixMode(GL_MODELVIEW);
}

int ImageLoad(char *filename, Image *image) {
	FILE *file;
	unsigned long size;
	unsigned long i;
	unsigned short int planes;
	unsigned short int bpp; // bit per pixel
	char temp;

	// Exceptions handlers
	if ((file = fopen(filename, "rb")) == NULL) { // fopen from stdio
		cerr << "File not found: " << filename << "\n";
		return 0;
	}
	fseek(file, 18, SEEK_CUR); // fseek from stdio
	if (i = fread(&image->sizeX, 4, 1, file) != 1) {
		cerr << "Read width error: " << filename << "\n";
		return 0;
	}
	if (i = fread(&image->sizeY, 4, 1, file) != 1) {
		cerr << "Read height error: " << filename << "\n";
		return 0;
	}
	size = image->sizeX * image->sizeY * 3;
	if (i = fread(&planes, 2, 1, file) != 1) {
		cerr << "Read planes error: " << filename << "\n";
		return 0;
	}
	if (planes != 1) {
		cerr << "Plane not one error: " << filename << "\n";
		return 0;
	}
	if (i = fread(&bpp, 2, 1, file) != 1) {
		cerr << "Read bpp error: " << filename << "\n";
		return 0;
	}
	if (bpp != 24) {
		cerr << "bpp not 24 bits: " << filename << "\n";
		return 0;
	}
	fseek(file, 24, SEEK_CUR);
	image->data = new char[size];
	if (image->data == NULL) {
		cerr << "No memory error: " << filename << "\n";
		return 0;
	}
	if ((i = fread(image->data, size, 1, file)) != 1) {
		cerr << "Read imageg data error: " << filename << "\n";
		return 0;
	}

	for (i = 0; i < size; i += 3) { // reverse BGR to RGB
		temp = image->data[i];
		image->data[i] = image->data[i + 2];
		image->data[i + 2] = temp;
	}
	return 1;
}

Image *loadTexture(char* filename) {
	Image *img;
	img = new Image[sizeof(Image)];
	if (img == NULL) {
		cerr << "No memory error." << endl;
	}
	if (!ImageLoad(filename, img)) {
		exit(1);
	}
	return img;
}

void renderScene() {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Background color

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 800, 0, 600);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0f, 0.0f, 0.0f); // Set brush color to red
	drawPoint(400, 300, 5.0);

	glColor3f(0.0f, 1.0f, 0.0f); // Set brush color to green
	drawTriangle(0, 0, 0, 100, 100, 100);

	glColor3f(0.0f, 0.0f, 1.0f); // Set brush color to blue
	drawRegularPolygon(400, 300, 100, 500, 0);

	glColor3f(1.0f, 0.5f, 0.0f); // Set brush color to orange
	string text;
	text = "First text rendering.";
	drawText(text.data(), text.size(), 0, 550);

	glBindTexture(GL_TEXTURE_2D, textureMap[0]);
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);	glVertex2f(550, 50);
	glTexCoord2f(1, 0);	glVertex2f(350, 50);
	glTexCoord2f(1, 1);	glVertex2f(350, 250);
	glTexCoord2f(0, 1);	glVertex2f(550, 250);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, bmpTexture);

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);	glVertex2f(50, 50);
	glTexCoord2f(1, 0);	glVertex2f(150, 50);
	glTexCoord2f(1, 1);	glVertex2f(150, 150);
	glTexCoord2f(0, 1);	glVertex2f(50, 150);
	glEnd();

	glFlush();
	glutSwapBuffers();
}

void processImage() {
	//Enable texture
	glEnable(GL_DEPTH_TEST);

	// Load checker map
	checkerMap.generateCheckerImage();
	glGenTextures(2, textureMap);

	//Version 1
	// Setup image data into texture
	glBindTexture(GL_TEXTURE_2D, textureMap[0]);
	glTexImage2D(GL_TEXTURE_2D, 0, checkerMap.bitDepth,
		checkerMap.width, checkerMap.height, 0,
		GL_RGB, GL_UNSIGNED_BYTE,
		&checkerMap.checkerImage);
	//Texture parameters
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	//VERSION 2
	// Setup image data into texture
	char filename[] = "image/minion.bmp";
	Image *minionBMP = loadTexture(filename);
	if (minionBMP == NULL) {
		printf("Image was not return from loadTexture function.");
		exit(0);
	}

	glBindTexture(GL_TEXTURE_2D, bmpTexture);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, minionBMP->sizeX, minionBMP->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, minionBMP->data);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	glEnable(GL_TEXTURE_2D);
}

int main(int argc, char** argv) {

	glutInit(&argc, argv);
	void drawPoint(GLint x, GLint y, GLfloat size);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Hello OpenGL!");

	processImage();

	glutDisplayFunc(renderScene);

	glutMainLoop();

	system("PAUSE");
	return 0;
}
#ifndef IMAGE_H
#define IMAGE_H
#include <gl/glut.h>

class Map
{
public:
	int width, height;
	int bitDepth;
	GLubyte checkerImage[64][64][3];

	Map();
	Map(GLint width, GLint height, GLint bitDepth);
	void generateCheckerImage();
};

Map::Map()
{
}

Map::Map(GLint width, GLint height, GLint bitDepth)
{
	this->width = width;
	this->height = height;
	this->bitDepth = bitDepth;
}

void Map::generateCheckerImage()
{
	int c;

	for (int i = 0; i < 64; i++)
	{
		for (int j = 0; j < 64; j++)
		{
			c = (((i & 0x8) == 0) ^ ((j & 0x8) == 0)) * 255; //checker logic
			checkerImage[i][j][0] = c;
			checkerImage[i][j][1] = c;
			checkerImage[i][j][2] = c;
		}
	}
}

class Image
{
public:
	unsigned long sizeX;
	unsigned long sizeY;
	char *data;
	Image();
};

Image::Image()
{

}

#endif // !IMAGE_H

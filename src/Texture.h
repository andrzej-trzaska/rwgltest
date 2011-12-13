#pragma once
#include <string>
#include <gl/glut.h>
#include <SOIL.h>

using namespace std;

class Texture
{
public:
	Texture(void);
	~Texture(void);
	void Draw(void);

private:
	string name;
	GLuint *data;
};


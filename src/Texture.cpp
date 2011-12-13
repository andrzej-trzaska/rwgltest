#include "Texture.h"


Texture::Texture(void)
{
}


Texture::~Texture(void)
{
	delete data;
}

void Texture::Draw(void)
{
	//glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,Ka->getArrayRGBA());
	//glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,Kd->getArrayRGBA());
	//glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,Ks->getArrayRGBA());
	//glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, Ns);
}

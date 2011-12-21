/* Copyright (C) 2011 Andrzej Trzaska
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is furnished to do
 * so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "Light.h"

Light::Light(int light_num) {
	if (light_num < 0 || light_num > 7) {
		return;
	}

	switch (light_num) {
	case 0:
		this->LightNo = GL_LIGHT0;
		break;
	case 1:
		this->LightNo = GL_LIGHT1;
		break;
	case 2:
		this->LightNo = GL_LIGHT2;
		break;
	case 3:
		this->LightNo = GL_LIGHT3;
		break;
	case 4:
		this->LightNo = GL_LIGHT4;
		break;
	case 5:
		this->LightNo = GL_LIGHT5;
		break;
	case 6:
		this->LightNo = GL_LIGHT6;
		break;
	case 7:
		this->LightNo = GL_LIGHT7;
		break;
	}

	//reset values
	for(GLbyte i = 0; i < 4; i++) {
		Ambient[i] = 0;
		Diffuse[i] = 0;
		Specular[i] = 0;
		pos[i] = 0;
	}
	glEnable(LightNo);
}

void Light::DrawMe(void) {
	glLightfv(LightNo, GL_POSITION, pos);
}

void Light::Init(void) {
	glEnable(GL_LIGHTING);
	GLfloat Ambient[] = { 0.4f, 0.4f, 0.4f, 0.0f };
	GLfloat DiffuseM[] = { 0.75f, 0.75f, 0.75f, 0.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, Ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, DiffuseM);
}

void Light::Enable(void) {
	glEnable(LightNo);
}

void Light::Disable(void) {
	glDisable(LightNo);
}

void Light::setPos(GLfloat pos[4]) {
	this->pos[0] = pos[0];
	this->pos[1] = pos[1];
	this->pos[2] = pos[2];
	this->pos[3] = pos[3];
}

void Light::setAmbient(GLfloat amb[4]) {
	this->Ambient[0] = amb[0];
	this->Ambient[1] = amb[1];
	this->Ambient[2] = amb[2];
	this->Ambient[3] = amb[3];
	glLightfv(LightNo, GL_AMBIENT, Ambient);
}

void Light::setDiffuse(GLfloat dif[4]) {
	this->Diffuse[0] = dif[0];
	this->Diffuse[1] = dif[1];
	this->Diffuse[2] = dif[2];
	this->Diffuse[3] = dif[3];
	glLightfv(LightNo, GL_DIFFUSE, Diffuse);
}

void Light::setSpecular(GLfloat spec[4]) {
	this->Specular[0] = spec[0];
	this->Specular[1] = spec[1];
	this->Specular[2] = spec[2];
	this->Specular[3] = spec[3];
	glLightfv(LightNo, GL_SPECULAR, Specular);
}

Light::~Light(void) {

}


//Light *l;
//void init_Light() {
//    Light::Init();
//    l = new Light(0);
//    l->Enable();
//    GLfloat Position[] = {1.0f, 1.0f, 1.0f, 1.0};
//    GLfloat Ambient[] = {0.4f, 0.0f, 0.0f, 0.0f};
//    GLfloat Diffuse[] = {0.75f, 0.0f, 0.0f, 0.0f};
//    l->setPos(Position);
//    l->setAmbient(Ambient);
//    l->setDiffuse(Diffuse);
//    l->setSpecular(Ambient);
//}

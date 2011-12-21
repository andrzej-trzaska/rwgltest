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

#pragma warning (disable : 4996)
#include "Scene.h"
#include "ObjMesh.h"
#include "Light.h"
#include "Sound.h"

Scene::Scene(string filename) {
    init_Glut();
	load(filename);
    playAllSounds();
}

void Scene::load(string filename) {
	string line;
	GLbyte lightNum = 0;

	ifstrm.open(filename);
	if(!ifstrm.is_open()) {
		return;
	}

	while(getline(ifstrm, line)) {
		if(line.empty()) {
		} else if(!line.find("# ")) {
		} else if(!line.find(("sound "))) {
			char fn[20];
			GLfloat pos[3];
			sscanf(line.c_str(), "sound %s %f %f %f", fn, &pos[0], &pos[1], &pos[2]);
			string fname = "./Data/";
			fname += fn;
			Sound *s = new Sound(fname.c_str());
			s->setPosition(pos);
			Sounds.push_back(s);
		} else if(!line.find("light ")) {
			Light::Init();
			Light *l = new Light(lightNum);
			GLfloat pos[4] = { 0 };
			GLfloat amb[4] = { 0 };
			GLfloat dif[4] = { 0 };
			GLfloat spec[4] = { 0 };

			sscanf(line.c_str(), "light %f %f %f %f %f %f %f %f %f %f %f %f",
					&pos[0], &pos[1], &pos[2], &amb[0], &amb[1], &amb[2],
					&dif[0], &dif[1], &dif[2], &spec[0], &spec[1], &spec[2]);

			pos[3] = 1.0f;
			l->setPos(pos);
			l->setAmbient(amb);
			l->setDiffuse(dif);
			l->setSpecular(spec);

			Lights.push_back(l);
			lightNum++;
		} else if(!line.find("model ")) {
			Mesh_Struct o;
			char fn[20];
			sscanf(line.c_str(), "model %s %f %f %f %f %f %f %f %f %f", fn, &o.pos[0], &o.pos[1], &o.pos[2],
				&o.scale[0], &o.scale[1], &o.scale[2], &o.rot[0], &o.rot[1], &o.rot[2]);
			o.Name = fn;
			o.mesh = new ObjMesh("./Data/" + o.Name);
			Meshes.push_back(o);
		}
	}
}

void Scene::playAllSounds(void) {
    for(GLuint i = 0;i < Sounds.size();i++){
        Sounds[i]->loop();
    }
}

void Scene::draw(void) {
	glPushMatrix();

	for(GLuint i=0; i < Lights.size(); i++) {
		Lights[i]->DrawMe();
	}

	for(GLuint i = 0; i < Meshes.size(); i++) {
		glPushMatrix();
		glTranslatef(Meshes[i].pos[0], Meshes[i].pos[1], Meshes[i].pos[2]);
		glRotatef(Meshes[i].rot[0], 1.0f, 0.0f, 0.0f);
		glRotatef(Meshes[i].rot[1], 0.0f, 1.0f, 0.0f);
		glRotatef(Meshes[i].rot[2], 0.0f, 0.0f, 1.0f);
		glScalef(Meshes[i].scale[0], Meshes[i].scale[1], Meshes[i].scale[2]);
		Meshes[i].mesh->DrawMe();
		glPopMatrix();
	}

	glPopMatrix();
}

void Scene::init_Glut(void) {
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("A basic OpenGL Window");
    glutSetCursor(GLUT_CURSOR_NONE);
    glClearColor(0.5f, 0.5f, 0.5f, 0.0f);
    glShadeModel(GL_SMOOTH);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glutFullScreen();
}

Scene::~Scene(void) {
	delete this;
}

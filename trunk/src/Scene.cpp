/* Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above notice and this permission notice shall be included in all copies
 * or substantial portions of the Software.
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

Scene::Scene(string filename) {
	load(filename);
}

void Scene::load(string filename) {
	string line;

	ifstrm.open(filename);
	if(!ifstrm.is_open()) {
		return;
	}

	while(getline(ifstrm, line)) {
		if(!line.find("# ")) {
		} else if (line.empty()) {
		} else {
			Mesh_Struct o;
			char fn[20];
			sscanf(line.c_str(), "%s %f %f %f %f %f %f %f %f %f", fn, &o.pos[0], &o.pos[1], &o.pos[2], 
				&o.scale[0], &o.scale[1], &o.scale[2], &o.rot[0], &o.rot[1], &o.rot[2]);
			o.filename = fn;
			o.mesh = new ObjMesh("./Data/" + o.filename);
			Meshes.push_back(o);
		}
	}
}

void Scene::draw(void) {
	glPushMatrix();

	for(uint i = 0; i < Meshes.size(); i++) {
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

Scene::~Scene(void) {
	delete this;
}

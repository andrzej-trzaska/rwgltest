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

#include "ObjMesh.h"
#include <SOIL.h>

ObjMesh::ObjMesh(string filename) {
	parse_mtl(filename);
	parse_obj(filename);
}

void ObjMesh::parse_obj(string filename) {
	string line;
	GLuint materialid = 1;

	ifstrm.open(filename);
	if(!ifstrm.is_open()) {
		return;
	}

	while(getline(ifstrm, line)) {
		if(!line.find("# ")) {
		} else if (line.empty()) {
		} else if(!line.find("usemtl ")) {
			line.replace(0, 7, "");
			for(GLuint i = 0; i < Materials.size(); i++) {
				if(Materials[i].name == line) {
					materialid = Materials[i].matId;
					break;
				}
			}
		} else if(!line.find("v ")) {
			Vertex o;// = {0, 0 ,0};
			sscanf_s(line.c_str(), "v %f %f %f", &o.x, &o.y, &o.z);
			VertexArray.push_back(o);
		} else if(!line.find("vn ")) {
			Normal o = {0, 0 ,0};
			sscanf_s(line.c_str(), "vn %f %f %f", &o.x, &o.y, &o.z);
			NormalArray.push_back(o);
		} else if(!line.find("vt ")) {
			TexCoord o = {0, 0};
			sscanf_s(line.c_str(), "vt %f %f", &o.u, &o.v);
			TexCoordArray.push_back(o);
		} else if(!line.find("f ")) {
			Face o;
			sscanf_s(line.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d",
				&o.Vertex[0], &o.TexCoord[0], &o.Normal[0],
				&o.Vertex[1], &o.TexCoord[1], &o.Normal[1],
				&o.Vertex[2], &o.TexCoord[2], &o.Normal[2]);
			o.TextureNo = materialid;
			FaceArray.push_back(o);
		}
	}
	ifstrm.close();
}

void ObjMesh::parse_mtl(string filename) {
	string fname = filename;
	GLuint fn = fname.find(".obj");
	fname.replace(fn, 4, ".mtl");
	
	ifstrm.open(fname);
	if(!ifstrm.is_open()) {
		return;
	}

	string line;
	while(getline(ifstrm, line)) {
		if(!line.find("# ")) {
		} else if(line.empty()) {
		} else if(!line.find("newmtl ")) {
			Material o;
			line.replace(0, 7, "");
			o.name = line;

			getline(ifstrm, line);
			sscanf_s(line.c_str(), "Ka %f %f %f", &o.ambient[0], &o.ambient[1], &o.ambient[2]);

			getline(ifstrm, line);
			sscanf_s(line.c_str(), "Kd %f %f %f", &o.diffuse[0], &o.diffuse[1], &o.diffuse[2]);

			getline(ifstrm, line);
			sscanf_s(line.c_str(), "Ks %f %f %f", &o.specular[0], &o.specular[1], &o.specular[2]);

			getline(ifstrm, line);
			sscanf_s(line.c_str(), "illum %d", &o.illum);

			getline(ifstrm, line);
			line.replace(0, 7, "");
			string mtlfile = "./Data/";
			mtlfile += line;
			o.matId = SOIL_load_OGL_texture(mtlfile.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
			Materials.push_back(o);
		}
	}
	ifstrm.close();
}

void ObjMesh::DrawMe(void) {
	GLuint currtexture = 0;

	glPushMatrix();
	glEnable(GL_TEXTURE_2D);

	for(GLuint i = 0; i < FaceArray.size(); i++) {
		if(currtexture != FaceArray[i].TextureNo) {
			glEnd();
			currtexture = FaceArray[i].TextureNo;
			glBindTexture(GL_TEXTURE_2D, currtexture);
			glBegin(GL_TRIANGLES);
		}

		for(int j = 0; j < 3; j++) {
			glTexCoord2f(TexCoordArray[FaceArray[i].TexCoord[j] - 1].u, 
				         TexCoordArray[FaceArray[i].TexCoord[j] - 1].v);
			glNormal3f(NormalArray[FaceArray[i].Normal[j] - 1].x, 
				       NormalArray[FaceArray[i].Normal[j] - 1].y, 
				       NormalArray[FaceArray[i].Normal[j] - 1].z);
			glVertex3f(VertexArray[FaceArray[i].Vertex[j] - 1].x, 
					   VertexArray[FaceArray[i].Vertex[j] - 1].y, 
				       VertexArray[FaceArray[i].Vertex[j] - 1].z);
		}
	}
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

ObjMesh::~ObjMesh(void) {
	delete this;
}

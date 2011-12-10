#include "ObjMesh.h"

ObjMesh::ObjMesh(string filename) {
	parse_obj(filename);
	parse_mtl(filename);
}

void ObjMesh::parse_obj(string filename) {
	string line;

	ifstrm.open(filename);
	if(!ifstrm.is_open()) {
		return;
	}

	while(getline(ifstrm, line)) {
		if(!line.find("# ")) {
		} else if (line.empty()) {
		} else if(!line.find("v ")) {
			ObjVertex o = {0, 0 ,0};
			sscanf_s(line.c_str(), "v %f %f %f", &o.x, &o.y, &o.z);
			VertexArray.push_back(o);
		} else if(!line.find("vn ")) {
			ObjNormal o = {0, 0 ,0};
			sscanf_s(line.c_str(), "vn %f %f %f", &o.x, &o.y, &o.z);
			NormalArray.push_back(o);
		} else if(!line.find("vt ")) {
			ObjTexCoord o = {0, 0};
			sscanf_s(line.c_str(), "vt %f %f", &o.u, &o.v);
			TexCoordArray.push_back(o);
		} else if(!line.find("f ")) {
			ObjFace o;
			sscanf_s(line.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d",
				&o.Vertex[0], &o.TexCoord[0], &o.Normal[0],
				&o.Vertex[1], &o.TexCoord[1], &o.Normal[1],
				&o.Vertex[2], &o.TexCoord[2], &o.Normal[2]);
			FaceArray.push_back(o);
		}
	}
	ifstrm.close();
}

void ObjMesh::parse_mtl(string filename) {
	string fname = filename;
	uint fn = fname.find(".obj");
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
			ObjMaterial o = {0};
			//char* name = "";
			sscanf_s(line.c_str(), "newmtl %s", o.name);	// tu sie wysypuje
			getline(ifstrm, line);
			sscanf_s(line.c_str(), "Ka %f %f %f", o.ambient[0], o.ambient[1], o.ambient[2]);
			getline(ifstrm, line);
			sscanf_s(line.c_str(), "Kd %f %f %f", o.diffuse[0], o.diffuse[1], o.diffuse[2]);
			getline(ifstrm, line);
			sscanf_s(line.c_str(), "Kd %f %f %f", o.specular[0], o.specular[1], o.specular[2]);
			getline(ifstrm, line);
			sscanf_s(line.c_str(), "illum %d", o.illum);
			Materials.push_back(o);
		}
	}
}

void ObjMesh::DrawMe(void) {
	glPushMatrix();
	glRotatef(180, 0.0f, 1.0f, 0.0f); // reverse on y

	//glEnable(GL_TEXTURE_2D);
	glBegin(GL_TRIANGLES);


	for(uint i = 0; i < FaceArray.size(); i++) {
		for(int j = 0; j < 3; j++) {
			glTexCoord2f(
				TexCoordArray[FaceArray[i].TexCoord[j] - 1].u, 
				TexCoordArray[FaceArray[i].TexCoord[j] - 1].v);
			glNormal3f(
				NormalArray[FaceArray[i].Normal[j] - 1].x, 
				NormalArray[FaceArray[i].Normal[j] - 1].y, 
				NormalArray[FaceArray[i].Normal[j] - 1].z);
			glVertex3f(
				VertexArray[FaceArray[i].Vertex[j] - 1].x, 
				VertexArray[FaceArray[i].Vertex[j] - 1].y, 
				VertexArray[FaceArray[i].Vertex[j] - 1].z);
		}
	}
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void ObjMesh::SaveAs(string filename) {
	ofstream of(filename);

	if(!of.is_open()) return;

	of << "# Vertices" << endl << endl;

	for(uint i = 0; i < VertexArray.size(); i++) {
		of << "v " << VertexArray[i].x << " "
			       << VertexArray[i].y << " "
				   << VertexArray[i].z << endl;
	}
	of << endl << "# Normals" << endl << endl;

	for(uint i = 0; i < NormalArray.size(); i++) {
		of << "vn " << NormalArray[i].x << " "
			        << NormalArray[i].y << " "
					<< NormalArray[i].z << endl;
	}

	of << endl << "# Texture Coords" << endl << endl;

	for(uint i = 0; i < TexCoordArray.size(); i++) {
		of << "vt " << TexCoordArray[i].u << " "
			        << TexCoordArray[i].v << endl;
	}

	of << endl << "# Faces" << endl << endl;

	for(uint i = 0; i < FaceArray.size(); i++) {
		of << "f ";
		for(int j = 0; j < 3; j++) {
			of << FaceArray[i].Vertex[j] << "/"
			   << FaceArray[i].TexCoord[j] << "/"
			   << FaceArray[i].Normal[j];
			if(j < 2) {
				of << " ";
			}
		}
		of << endl;
	}

	of << endl << "# End";
}


ObjMesh::~ObjMesh(void) {
	delete this;
}

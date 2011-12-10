#pragma once

#include <string>
#include <fstream>
#include <vector>
#include <stdio.h>

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

using namespace std;

typedef unsigned int uint;
typedef unsigned short ushort;
typedef unsigned char Byte;

struct ObjVertex {
    float x, y, z;
};

struct ObjNormal {
	float x, y, z;
};

struct ObjTexCoord {
    float u, v;
};

struct ObjFace {
    int Vertex[3];
    int Normal[3];
    int TexCoord[3];
};

struct ObjMaterial {
	char* name;
	float ambient[4];
	float diffuse[4];
	float specular[4];
	Byte illum;
};

class ObjMesh {
public:
    ObjMesh(string filename);


	void DrawMe(void);
	void SaveAs(string filename);
    ~ObjMesh(void);

private:
	void parse_obj(string filename);
	void parse_mtl(string filename);

	ifstream ifstrm;
	vector<ObjVertex> VertexArray;
	vector<ObjNormal> NormalArray;
	vector<ObjTexCoord> TexCoordArray;
	vector<ObjFace> FaceArray;
	vector<ObjMaterial> Materials;
};
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
#include <SOIL.h>

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
    uint Vertex[3];
    uint Normal[3];
    uint TexCoord[3];
	uint TextureNo;
};

struct ObjMaterial {
	//char* name;
	string name;
	float ambient[3];
	float diffuse[3];
	float specular[3];
	Byte illum;
};
struct Texture2 {
	string name;
	GLuint data;
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
	vector<Texture2> textures;
};
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

#ifndef OBJMESH_H
#define OBJMESH_H

#include <string>
#include <fstream>
#include <vector>

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
    uint Vertex[3];
    uint Normal[3];
    uint TexCoord[3];
	GLuint TextureNo;
};

struct ObjMaterial {
	string name;
	float ambient[3];
	float diffuse[3];
	float specular[3];
	Byte illum;
	GLuint matId;
};

class ObjMesh {
public:
    ObjMesh(string filename);
	void DrawMe(void);
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

#endif

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

#ifndef LIGHT_H_
#define LIGHT_H_

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

class Light {
public:
	Light(int light_num);
	static void Init(void);
	void DrawMe(void);
	void Enable(void);
	void Disable(void);
    void setPos(GLfloat pos[4]);
    void setAmbient(GLfloat amb[4]);
    void setDiffuse(GLfloat dif[4]);
    void setSpecular(GLfloat spec[4]);
	virtual ~Light(void);
private:
    GLenum LightNo;
	GLfloat pos[4];
	GLfloat Ambient[4];
	GLfloat Diffuse[4];
	GLfloat Specular[4];
};

#endif /* LIGHT_H_ */

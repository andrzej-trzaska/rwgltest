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

#include <stdlib.h>			// exit()
#include <math.h>			// sin() cos()

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <al.h>
#include <AL/alut.h>

#include "Scene.h"
#include "Listener.h"

//angle of rotation
float xpos = 0, ypos = 0, zpos = 0, xrot = 0, yrot = 0, angle = 0.0;
float cRadius = 10.0f; //our radius distance from our character
int lastx, lasty;

Scene *scene;
Listener *listener;

void callback_draw(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glTranslatef(0.0f, 0.0f, -cRadius);
	glRotatef(xrot, 1.0, 0.0, 0.0);
	glRotatef(yrot, 0.0, 1.0, 0.0); //rotate our camera on the y-axis (up and down)
	glTranslated(-xpos, 0.0f, -zpos); //translate the screen to the position of our camera

	scene->draw();
	glutSwapBuffers(); //swap the buffers
}

void callback_reshape(int w, int h) {
	if (y == 0 || x == 0) return;  //Nothing is visible then, so return
	glViewport(0, 0, w, h); //set the viewport to the current window specifications
	glMatrixMode(GL_PROJECTION); //set the matrix to projection
	glLoadIdentity();
	gluPerspective(60, (GLfloat) w / (GLfloat) h, 0.1, 100.0); //set the perspective (angle of sight, width, height, depth)
	glMatrixMode(GL_MODELVIEW); //set the matrix back to model
}

void callback_motion(int x, int y) {
	int diffx = x - lastx; //check the difference between the current x and the last x position
	int diffy = y - lasty; //check the difference between the current y and the last y position

	lastx = x; //set lastx to the current x position
	lasty = y; //set lasty to the current y position
	xrot += diffy; //set the xrot to xrot with the addition of the difference in the y position
	yrot += diffx; //set the xrot to yrot with the addition of the difference in the x position
}

void callback_keyboard(unsigned char key, int x, int y) {
	if (key == 'q') {
		xrot += 1;
		if (xrot > 360)
			xrot -= 360;
	}

	if (key == 'z') {
		xrot -= 1;
		if (xrot < -360)
			xrot += 360;
	}

	if (key == 'w') {
		float xrotrad, yrotrad;

		yrotrad = (yrot / 180 * 3.141592654f);
		xrotrad = (xrot / 180 * 3.141592654f);
		xpos += sin(yrotrad);
		zpos -= cos(yrotrad);
		ypos -= sin(xrotrad);

		listener->setPos(xpos, ypos, zpos);
	}

	if (key == 's') {
		float xrotrad, yrotrad;

		yrotrad = (yrot / 180 * 3.141592654f);
		xrotrad = (xrot / 180 * 3.141592654f);
		xpos -= sin(yrotrad);
		zpos += cos(yrotrad);
		ypos += sin(xrotrad);

		listener->setPos(xpos, ypos, zpos);
	}

	if (key == 'a') {
		float yrotrad;

		yrotrad = (yrot / 180 * 3.141592654f);
		xpos -= cos(yrotrad) * 0.2f;
		zpos -= sin(yrotrad) * 0.2f;

		listener->setPos(xpos, ypos, zpos);
	}

	if (key == 'd') {
		float yrotrad;

		yrotrad = (yrot / 180 * 3.141592654f);
		xpos += cos(yrotrad) * 0.2f;
		zpos += sin(yrotrad) * 0.2f;

		listener->setPos(xpos, ypos, zpos);
	}

	if (key == 27) {
		exit(0);
	}
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
    alutInit(&argc, argv);

	scene = new Scene("./data/Scene.Scene");
	listener = new Listener();
	listener->setPos(xpos, ypos, zpos);

	glutIdleFunc(callback_draw);
	glutDisplayFunc(callback_draw);
	glutReshapeFunc(callback_reshape);
	glutPassiveMotionFunc(callback_motion);
	glutKeyboardFunc(callback_keyboard);

	glutMainLoop();
	return 0;
}

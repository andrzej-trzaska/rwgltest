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
#include <SOIL.h>

#include "Scene.h"

#define NUM_BUFFERS         10
#define NUM_SOURCES         10
#define NUM_ENVIRONMENTS    1

//angle of rotation
float   xpos = 0, ypos = 0, zpos = 0, xrot = 0, yrot = 0, angle = 0.0;
float   cRadius = 10.0f;    //our radius distance from our character
int     lastx, lasty;
//sounds
ALfloat listenerPos[] = { 0.0, 0.0, 4.0 };

Scene *scene;

//=======================================================================================================================
//   init OpenAL
//=======================================================================================================================
//
void init_Audio(void) {
	char    al_bool;
	ALfloat listenerVel[] = { 0.0, 0.0, 0.0 };
	ALfloat listenerOri[] = { 0.0, 0.0, 1.0, 0.0, 1.0, 0.0 };
	ALfloat source0Pos[] = { 0.0, 0.0, 0.0 };
	ALfloat source0Vel[] = { 0.0, 0.0, 0.0 };
	ALuint  buffer[NUM_BUFFERS];
	ALuint  source[NUM_SOURCES];
	ALsizei size, freq;
	ALenum  format;
	ALvoid  *data;

    glClearColor(0.0, 0.0, 0.0, 1.0);

    //alutInit(0, NULL);
    alListenerfv(AL_POSITION, listenerPos);
    alListenerfv(AL_VELOCITY, listenerVel);
    alListenerfv(AL_ORIENTATION, listenerOri);

    alGetError();   //clear error

    //Generate buffers, or no sound will be produced
    alGenBuffers(NUM_BUFFERS, buffer);

    if (alGetError() != AL_NO_ERROR) exit(1);

    alutLoadWAVFile("data/a.wav", &format, &data, &size, &freq, &al_bool);
    alBufferData(buffer[0], format, data, size, freq);
    alutUnloadWAV(format, data, size, freq);

    alGetError();   //clear error
    alGenSources(NUM_SOURCES, source);

    if (alGetError() != AL_NO_ERROR) exit(2);

    alSourcef(source[0], AL_PITCH, 1.0f);
    alSourcef(source[0], AL_GAIN, 1.0f);
    alSourcefv(source[0], AL_POSITION, source0Pos);
    alSourcefv(source[0], AL_VELOCITY, source0Vel);
    alSourcei(source[0], AL_BUFFER, buffer[0]);
    alSourcei(source[0], AL_LOOPING, AL_TRUE);

	//start playing the musics!
	alSourcePlay(source[0]);
}

//=======================================================================================================================
//   init OpenGL
//=======================================================================================================================
//
void init_Rendering(void) {
	glClearColor(0.5f,0.5f,0.5f,0.0f);
	glShadeModel(GL_SMOOTH);    //set the shader to smooth shader
	glEnable(GL_LIGHTING);      //enable the lighting
	glEnable(GL_LIGHT0);        //enable LIGHT0, our Diffuse Light
	glEnable(GL_DEPTH_TEST);    //Enables Depth Testing
	glEnable(GL_TEXTURE_2D);    //Enable Texture Mapping ( NEW )

	glDepthFunc(GL_LEQUAL);     //The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  //Really Nice Perspective Calculations

	glutFullScreen();

	//light position
	GLfloat lightPos0[] = { 4.0f, 5.0f, 8.0f, 1.0f };       //Positioned at (4, 5, 8)
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);

	//Setup Material Porperties & colours for the light
	{
		float Ambient[] = {0.4f,0.4f,0.4f,0.0f};
		float Diffuse[] = {0.75f,0.75f,0.75f,0.0f};
		glMaterialfv(GL_FRONT,GL_AMBIENT,Ambient);
		glMaterialfv(GL_FRONT,GL_DIFFUSE,Diffuse);
	}
	{
		float Ambient[] = {0.4f,0.4f,0.4f,0.0f};
		float Diffuse[] = {0.95f,0.95f,0.95f,0.0f};
		glLightfv(GL_LIGHT0,GL_AMBIENT,Ambient);
		glLightfv(GL_LIGHT0,GL_DIFFUSE,Diffuse);
	}
}


//=======================================================================================================================
//   Load Scene
//=======================================================================================================================
//
void init_Scene(void) {
	scene = new Scene("./data/Scene.Scene");
}

//=======================================================================================================================
//   initialization
//=======================================================================================================================
//
void init_All(void) {
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("A basic OpenGL Window");
	glutSetCursor(GLUT_CURSOR_NONE);

	init_Rendering();
	init_Scene();
	init_Audio();
}

//=======================================================================================================================
//   display func
//=======================================================================================================================
//
void callback_draw(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

    glTranslatef(0.0f, 0.0f, -cRadius);
    glRotatef(xrot, 1.0, 0.0, 0.0);
    glRotatef(yrot, 0.0, 1.0, 0.0);     //rotate our camera on the y-axis (up and down)
	glTranslated(-xpos, 0.0f, -zpos);   //translate the screen to the position of our camera


	scene->draw();
    glutSwapBuffers();  //swap the buffers
}

//=======================================================================================================================
//   reshape func
//=======================================================================================================================
//
void callback_reshape(int w, int h) {
    glViewport(0, 0, (GLsizei) w, (GLsizei) h); //set the viewport to the current window specifications
    glMatrixMode(GL_PROJECTION);    //set the matrix to projection
    glLoadIdentity();
    gluPerspective(60, (GLfloat) w / (GLfloat) h, 0.1, 100.0);  //set the perspective (angle of sight, width, height, depth)
    glMatrixMode(GL_MODELVIEW); //set the matrix back to model
}

//=======================================================================================================================
//   mouse func
//=======================================================================================================================
//
void callback_motion(int x, int y) {
    int diffx = x - lastx;  //check the difference between the current x and the last x position
    int diffy = y - lasty;  //check the difference between the current y and the last y position

    lastx = x;  //set lastx to the current x position
    lasty = y;  //set lasty to the current y position
    xrot += diffy;  //set the xrot to xrot with the addition of the difference in the y position
    yrot += diffx;  //set the xrot to yrot with the addition of the difference in the x position
}

//=======================================================================================================================
//   keyboard func
//=======================================================================================================================
//
void callback_keyboard(unsigned char key, int x, int y) {
    if (key == 'q') {
        xrot += 1;
        if (xrot > 360) xrot -= 360;
    }

    if (key == 'z') {
        xrot -= 1;
        if (xrot < -360) xrot += 360;
    }

    if (key == 'w') {
        float   xrotrad, yrotrad;

        yrotrad = (yrot / 180 * 3.141592654f);
        xrotrad = (xrot / 180 * 3.141592654f);
        xpos += sin(yrotrad);
        zpos -= cos(yrotrad);
        ypos -= sin(xrotrad);

        listenerPos[0] = xpos;
        listenerPos[2] = zpos;
        alListenerfv(AL_POSITION, listenerPos);
    }

    if (key == 's') {
        float   xrotrad, yrotrad;

        yrotrad = (yrot / 180 * 3.141592654f);
        xrotrad = (xrot / 180 * 3.141592654f);
        xpos -= sin(yrotrad);
        zpos += cos(yrotrad);
        ypos += sin(xrotrad);

        listenerPos[0] = xpos;
        listenerPos[2] = zpos;
        alListenerfv(AL_POSITION, listenerPos);
    }

    if (key == 'a') {
        float   yrotrad;

        yrotrad = (yrot / 180 * 3.141592654f);
        xpos -= cos(yrotrad) * 0.2f;
        zpos -= sin(yrotrad) * 0.2f;

        listenerPos[0] = xpos;
        listenerPos[2] = zpos;
        alListenerfv(AL_POSITION, listenerPos);
    }

    if (key == 'd') {
        float   yrotrad;

        yrotrad = (yrot / 180 * 3.141592654f);
        xpos += cos(yrotrad) * 0.2f;
        zpos += sin(yrotrad) * 0.2f;

        listenerPos[0] = xpos;
        listenerPos[2] = zpos;
        alListenerfv(AL_POSITION, listenerPos);
    }

    if (key == 27) {
        exit(0);
    }
}

//=======================================================================================================================
//   entry point
//=======================================================================================================================
//
int main(int argc, char **argv) {
	glutInit(&argc, argv);
    alutInit(&argc, argv);
	init_All();

    glutIdleFunc(callback_draw);
    glutDisplayFunc(callback_draw);
    glutReshapeFunc(callback_reshape);
    glutPassiveMotionFunc(callback_motion);
	glutKeyboardFunc(callback_keyboard);

    glutMainLoop();
    return 0;
}

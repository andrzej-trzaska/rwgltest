#pragma region includes
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

#include "ObjMesh.h"
#include "Camera.h"
#include "Listener.h"
#pragma endregion

#pragma region pragma comments
#pragma comment(lib, "alut.lib")
#pragma comment(lib, "OpenAL32.lib")
#pragma comment(lib, "SOIL.lib")
#pragma endregion

#pragma region defines
#define NUM_BUFFERS         10
#define NUM_SOURCES         10
#define NUM_ENVIRONMENTS    1

#define FALSE               0
#define TRUE                1
#pragma endregion

#pragma region variables
//angle of rotation
float   xpos = 0, ypos = 0, zpos = 0, xrot = 0, yrot = 0, angle = 0.0;
float   cRadius = 10.0f;    //our radius distance from our character
int     lastx, lasty;

//positions of the cubes
float   position[10][3];

//light position
GLfloat lightPos0[] = { 4.0f, 5.0f, 8.0f, 1.0f };       //Positioned at (4, 5, 8)

//textures
GLuint  texture[3];         //Storage For One Texture ( NEW )

//sounds
ALfloat listenerPos[] = { 0.0, 0.0, 4.0 };
ALfloat listenerVel[] = { 0.0, 0.0, 0.0 };
ALfloat listenerOri[] = { 0.0, 0.0, 1.0, 0.0, 1.0, 0.0 };
ALfloat source0Pos[] = { 0.0, 0.0, 0.0 };
ALfloat source0Vel[] = { 0.0, 0.0, 0.0 };
ALuint  buffer[NUM_BUFFERS];
ALuint  source[NUM_SOURCES];
ALuint  environment[NUM_ENVIRONMENTS];
ALsizei size, freq;
ALenum  format;
ALvoid  *data;

//meshes
ObjMesh *mesh;
#pragma endregion

//=======================================================================================================================
//   set the positions of the cubes
//=======================================================================================================================
//
void pick_CubePositions(void) {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 3; j++) {
            position[i][j] = (float)(rand() % 10 + 1);
        }
    }

    source0Pos[0] = position[0][0];
    source0Pos[1] = position[0][1];
    source0Pos[2] = position[0][2];
}

//=======================================================================================================================
//   draws plane
//=======================================================================================================================
//
void draw_Ground(void) {
	glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[2]);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-100.0f, -1.0f, -100.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(100.0f, -1.0f, -100.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(100.0f, -1.0f, 100.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-100.0f, -1.0f, 100.0f);
    glEnd();
	glDisable(GL_TEXTURE_2D);
}

//=======================================================================================================================
//   draws cube
//=======================================================================================================================
//
void drawTexturedCube(void) {
	glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glBegin(GL_QUADS);
    glRotatef(45.0f, 1.0, 1.0, 1.0);

    //Front Face
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);

    //Back Face
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);

    //Top Face
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);

    //Bottom Face
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);

    //Right face
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);

    //Left Face
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);

    glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

//=======================================================================================================================
//   draw the cubes
//=======================================================================================================================
//
void draw_Cubes(void) {
    for (int i = 0; i < 10 - 1; i++) {
        glPushMatrix();
        glTranslated(-position[i + 1][0] * 10, 0, -position[i + 1][2] * 10);    //translate the cube

        drawTexturedCube();

        glPopMatrix();
    }
}

//=======================================================================================================================
//   init OpenAL
//=======================================================================================================================
//
void init_Audio(void) {
    char    al_bool;

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
	//glEnable(GL_CULL_FACE);

	glDepthFunc(GL_LEQUAL);     //The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  //Really Nice Perspective Calculations
	//glEnable(GL_COLOR_MATERIAL);
	//glColor4f(1.0f, 1.0f, 1.0f, 0.5);   //Full Brightness. 50% Alpha
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE);  //Set The Blending Function For Translucency


	//lights
	GLfloat redDiffuseMaterial[] = { 1.0, 0.0, 0.0 };       //set the material to red
	GLfloat whiteSpecularMaterial[] = { 1.0, 1.0, 1.0 };    //set the material to white
	GLfloat greenEmissiveMaterial[] = { 0.0, 1.0, 0.0 };    //set the material to green
	GLfloat whiteSpecularLight[] = { 1.0, 1.0, 1.0 };       //set the light specular to white
	GLfloat blackAmbientLight[] = { 0.0, 0.0, 0.0 };        //set the light ambient to black
	GLfloat whiteDiffuseLight[] = { 1.0, 1.0, 1.0 };        //set the diffuse light to white
	GLfloat blankMaterial[] = { 0.0, 0.0, 0.0 };            //set the diffuse light to white

	//glLightfv(GL_LIGHT0, GL_SPECULAR, whiteSpecularLight);
	//glLightfv(GL_LIGHT0, GL_AMBIENT, blackAmbientLight);
	//glLightfv(GL_LIGHT0, GL_DIFFUSE, whiteDiffuseLight);
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

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
//   Initialize Models
//=======================================================================================================================
//
void init_Models(void)
{

	//mesh = new ObjMesh("./Data/girl.obj");
	//mesh = new ObjMesh("./Data/torus.obj");
	mesh = new ObjMesh("./Data/rapide/rapide.obj");
	//ObjMesh mesh("./Data/rapide/rapide.obj");
	//ObjMesh *mesh = new ObjMesh("./Data/rapide/rapide.obj");
	//meshes.push_back(mesh);
	//mesh->DrawMe();
	//mesh->SaveAs("mesh.obj");
}

//=======================================================================================================================
//   Load Bitmaps And Convert To Textures
//=======================================================================================================================
//
bool init_Textures(void) {
	//load an image file directly as a new OpenGL texture
	texture[0] = SOIL_load_OGL_texture("./Data/NeHe.bmp", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	if (texture[0] == 0) return false;

	texture[1] = SOIL_load_OGL_texture("./Data/Glass.bmp", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	if (texture[1] == 0) return false;

	texture[2] = SOIL_load_OGL_texture("./Data/grass.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	if (texture[2] == 0) return false;

	//Typical Texture Generation Using Data From The Bitmap
	//glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	return true;    //Return Success
}

//=======================================================================================================================
//   initialization
//=======================================================================================================================
//
void init_All(void) {
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("A basic OpenGL Window");
	glutFullScreen();
	glutSetCursor(GLUT_CURSOR_NONE);

	pick_CubePositions();
	init_Rendering();
	//init_Textures();
	init_Models();
	init_Audio();
}

//=======================================================================================================================
//   display func
//=======================================================================================================================
//
void callback_draw(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);

    glTranslatef(0.0f, 0.0f, -cRadius);
    glRotatef(xrot, 1.0, 0.0, 0.0);
	//glColor3f(0.0f, 0.5f, 0.0f);

	glPushMatrix();
	mesh->DrawMe();
	glPopMatrix();
	//glRotatef(-180, 0.0f, 1.0f, 0.0f); // reverse back

    //drawTexturedCube();
    glRotatef(yrot, 0.0, 1.0, 0.0);     //rotate our camera on the y-axis (up and down)
	glTranslated(-xpos, 0.0f, -zpos);   //translate the screen to the position of our camera


	draw_Ground();
	draw_Cubes();        //call the cube drawing function
    glutSwapBuffers();  //swap the buffers
    //angle++;            //increase the angle
}

//=======================================================================================================================
//   reshape func
//=======================================================================================================================
//
void callback_reshape(int w, int h) {
    glViewport(0, 0, (GLsizei) w, (GLsizei) h); //set the viewport to the current window specifications
    glMatrixMode(GL_PROJECTION);    //set the matrix to projection
    glLoadIdentity();
    gluPerspective(60, (GLfloat) w / (GLfloat) h, 0.1, 100.0);  //set the perspective (angle of sight, width, height,
    ///, depth)
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
    alutInit(&argc, argv);
	glutInit(&argc, argv);
	init_All();

    glutIdleFunc(callback_draw);
    glutDisplayFunc(callback_draw);
    glutReshapeFunc(callback_reshape);
    glutPassiveMotionFunc(callback_motion);
	glutKeyboardFunc(callback_keyboard);

    glutMainLoop();
    return 0;
}

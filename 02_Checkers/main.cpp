#define GLUT_DISABLE_ATEXIT_HACK	
#include <windows.h>
#include <iostream>

#include <GL\glut.h>
#include "Tree.h"

#define RED 0
#define GREEN 0
#define BLUE 0
#define ALPHA 1

#define ECHAP 27

using namespace std;

int WIDTH = 800, HEIGHT = 600;
Tree arbolito(5);
bool play = true;

void init_scene();
GLvoid initGL();
GLvoid window_display();
GLvoid window_reshape(GLsizei width, GLsizei height);
GLvoid window_key(unsigned char key, int x, int y);
GLvoid callback_mouse(int button, int state, int x, int y);
GLvoid window_idle();

int main(int argc, char **argv) 
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition(10, 10);
	glutCreateWindow("Checkers");

	initGL();
	init_scene();
	glutDisplayFunc(&window_display);
	glutReshapeFunc(&window_reshape);
	glutMouseFunc(&callback_mouse);
	glutKeyboardFunc(&window_key);	
	glutIdleFunc(&window_idle);

	glutMainLoop();
	return 1;
}

GLvoid initGL()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(RED, GREEN, BLUE, ALPHA);
}

GLvoid window_idle()
{
	if (!arbolito.player && play)
		play = arbolito.choosePlay();
	glutPostRedisplay();
}

GLvoid window_key(unsigned char key, int x, int y)
{
	switch (key) {
	case ECHAP:
		exit(1);
		break;	
	default:
		printf("La touche %d non active.\n", key);
		break;
	}
}

void init_scene()
{
}

GLvoid window_reshape(GLsizei width, GLsizei height)
{
	glViewport(0, 0, width, height);
	WIDTH = width;
	HEIGHT = height;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
}

GLvoid window_display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(-25, 25, -25, 25, 20, 40);
	glTranslatef(0, 0, -30);
	arbolito.draw();
	glutSwapBuffers();
	glFlush();
}
\
GLvoid callback_mouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON && arbolito.player && play)
	{
		float coordX = (x / (float)WIDTH)*10.0;
		float coordY = ((HEIGHT - y) / (float)HEIGHT)*10.0;
		arbolito.selectSpace(coordX, coordY);
	}
}
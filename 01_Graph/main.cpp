#include "Graph.h"
#include <glm\glm.hpp>

using namespace std;

#include <windows.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>


#include <GL\glew.h>
#include <GL\freeglut.h>
#include <GL\glut.h>
#include <random>
#include <vector>

#define RED 0
#define GREEN 0
#define BLUE 0
#define ALPHA 1

#define ECHAP 27

std::default_random_engine random_engine;

void init_scene();
GLvoid initGL();
GLvoid window_display();
GLvoid window_reshape(GLsizei width, GLsizei height);
GLvoid window_key(unsigned char key, int x, int y);
GLvoid callback_mouse(int button, int state, int x, int y);
GLvoid window_idle();

int main(int argc, char **argv)
{
	std::mt19937 mt(random_engine());
	Graph a;
	vector<glm::vec2> points;
	for (int i = 0; i < 6; ++i) {
		int num = std::uniform_int_distribution<int>(2, 5)(random_engine);
		int x = -25 + (i * 10);
		for (int j = 0; j < num; ++j) {			
			int y = std::uniform_int_distribution<int>(-25, 25)(random_engine);
			points.push_back (glm::vec2(x, y));
		}		
	}
	for (int i = 0; i < points.size() - 3; ++i) {
		float w = std::uniform_real_distribution<float>(1, 10)(random_engine);
		a.insert(points[i], points[i + 1], w);
		a.insert(points[i], points[i + 2], w);
		a.insert(points[i], points[i + 3], w);
	}
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("grafo");
	
	initGL();
	init_scene();
	
	glutDisplayFunc(&window_display);
	glutReshapeFunc(&window_reshape);	
	glutMouseFunc(&callback_mouse);

	glutKeyboardFunc(&window_key);
	
	//function called on each frame
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

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
}

GLvoid window_display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	glOrtho(-30, 30, -30, 30, 1, 100);

	glTranslatef(0,0,-30);

	glutSwapBuffers();

	glFlush();
}
\
GLvoid callback_mouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
	{
		
	}
}
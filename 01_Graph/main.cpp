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

Graph a;


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
	
	
	//1
	a.insert(glm::vec2(-15, 15), glm::vec2( -15, -15), 20);
	a.insert(glm::vec2(-15, 15), glm::vec2(-8,-2 ), 12);
	a.insert(glm::vec2(-15, 15), glm::vec2(-5,10 ), 9);

	//2
	a.insert(glm::vec2(-15, -15), glm::vec2(-8,-2 ), 11);
	a.insert(glm::vec2(-15, -15), glm::vec2(-2,-12 ), 13);

	//3
	a.insert(glm::vec2(-8, -2), glm::vec2(-5,10 ), 3);
	a.insert(glm::vec2(-8, -2), glm::vec2(8,5 ), 17);
	a.insert(glm::vec2(-8, -2), glm::vec2(-2,-12 ), 4);

	//4
	a.insert(glm::vec2(-5,10 ), glm::vec2(5, 18), 10);

	//5
	a.insert(glm::vec2(-2,-12), glm::vec2(8, -17), 6);

	//6
	a.insert(glm::vec2(5,18 ), glm::vec2(14,15 ), 8);
	a.insert(glm::vec2(5, 18), glm::vec2(8,5 ), 7);

	//7
	a.insert(glm::vec2(8,5), glm::vec2(14,15 ), 5);
	a.insert(glm::vec2(8, 5), glm::vec2(8,-17 ), 16);
	a.insert(glm::vec2(8, 5), glm::vec2(16,-17 ),18 );

	//8
	a.insert(glm::vec2(8,-17), glm::vec2(16, -17), 2);

	//9
	a.insert(glm::vec2(14,15 ), glm::vec2(16,-17 ), 21);
	
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
	
	glOrtho(-30, 30, -30, 30, 20, 40);

	glTranslatef(0,0,-30);

	a.draw();

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


/*for (int i = 0; i < 6; ++i) {
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
*/
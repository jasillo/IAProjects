#pragma once
#define GLUT_DISABLE_ATEXIT_HACK	
#include <windows.h>
#include <GL\glut.h>
#include "Node.h"
#include <iostream>

class Tree
{
private:
	Node *root;
	unsigned short level;
	void generateNewLevel(Node *n, unsigned short lv);
	void generateLevels(Node *n, unsigned short lv);
	void destroy(Node *n);
	short selectedX, selectedY;
	
public:
	Tree(unsigned short lv);
	~Tree();

	bool player;
	bool movePiece( short c1,  short r1,  short c2,  short r2);
	void draw();
	void selectSpace(float x, float y);
	bool choosePlay();
};


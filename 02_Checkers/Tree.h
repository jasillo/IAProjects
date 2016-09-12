#pragma once

#include "Node.h"
#include <iostream>

class Tree
{
private:
	Node *root;
	unsigned short level;
	void generateNewLevel(Node *n, unsigned short lv);
	void generateLevels(Node *n, unsigned short lv);
public:
	Tree(unsigned short lv);
	~Tree();

	bool movePiece( short c1,  short r1,  short c2,  short r2);
};


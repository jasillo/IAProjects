#pragma once
#include "Node.h"
#include "Edge.h"
#include <vector>
#include <glm\glm.hpp>

#include <GL\glew.h>
#include <GL\freeglut.h>
#include <GL\glut.h>

#include <sstream>
#include <iomanip>

#include <iostream>
#include <queue>
#include <tuple>

using namespace std;

class Graph
{
public:
	Graph(){}
	~Graph();	
	bool insert(glm::vec2 a, glm::vec2 b, float w);	
	void draw();
	void setPoint(float x, float y);
	void deepSearch();
	void aStarSearch();
	void glString(const std::string str, void* );

private:
	vector<Edge *> myEdges;
	vector<Node *> myNodes;
	Node * startNode;
	Node * endNode;

	Node* findNode(glm::vec2 a);	
	void updateVector(vector<Node*> * v);
};


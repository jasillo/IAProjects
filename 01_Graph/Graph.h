#pragma once
#include "Node.h"
#include "Edge.h"
#include <vector>
#include <glm\glm.hpp>

using namespace std;

class Graph
{
public:
	Graph(){}
	~Graph();	
	bool insert(glm::vec2 a, glm::vec2 b, float w);	

private:
	vector<Edge *> myEdges;
	vector<Node *> myNodes;

	Node* findNode(glm::vec2 a);

};


#pragma once

#include <glm/glm.hpp>
#include <vector>
#include "Edge.h"

using namespace std;

class Edge;

class Node
{
public:
	Node(glm::vec2 d);
	~Node();
	Edge* findEdge(Node* a);
	void clear();
	glm::vec2 getData();

private:
	glm::vec2 data;
	vector<Edge *> myEdges;
};


#pragma once

#include <glm/glm.hpp>
#include <vector>
#include "Edge.h"

using namespace std;

class Edge;

class Node
{
public:
	Node(glm::vec2 data);
	~Node();
	glm::vec2 point;
	vector<Edge *> myEdges;

};


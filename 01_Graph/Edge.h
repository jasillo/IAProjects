#pragma once
#include "Node.h"

class Node;

using namespace std;

class Edge
{
public:
	Edge(float d);
	~Edge();
	vector<Node *> myNodes;
	int distance;
};


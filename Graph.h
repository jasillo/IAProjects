#pragma once
#include "Node.h"
#include "Edge.h"
#include <vector>

using namespace std;


class Graph
{
public:
	Graph(){}
	~Graph();
	vector<Edge *> myEdge;
	vector<Node *> myNode;	
};


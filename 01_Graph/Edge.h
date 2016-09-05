#pragma once
#include "Node.h"

class Node;

using namespace std;

class Edge
{
public:
	Edge(float d, Node *a, Node *b);
	~Edge();
	void clear();
	void setDistance(float w);
	bool isMyNode(Node *a);
	glm::vec2 getNode(int i);
	bool selected;
	Node* getNodeDiferent(Node* n);
	int getDistance();
	
private:
	vector<Node *> myNodes;
	int distance;
};


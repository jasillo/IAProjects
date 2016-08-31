#include "Edge.h"


Edge::Edge(float d, Node *a, Node *b): distance(d){
	myNodes.push_back(a);
	myNodes.push_back(a);
}

Edge::~Edge() {
	myNodes.clear();
}

void Edge::clear()
{
	myNodes.clear();
}

void Edge::setDistance(float w)
{
	distance = w;
}

bool Edge::isMyNode(Node * a)
{
	return (a == myNodes[0] || a == myNodes[1]);
}



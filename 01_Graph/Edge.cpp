#include "Edge.h"


Edge::Edge(float d, Node *a, Node *b): distance(d){
	myNodes.push_back(a);
	myNodes.push_back(b);
	selected = false;
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

glm::vec2 Edge::getNode(int i)
{
	return myNodes[i]->getData();
}

Node * Edge::getNodeDiferent(Node * n)
{
	if (n != myNodes[0])
		return myNodes[0];
	else
		return myNodes[1];
}

int Edge::getDistance()
{
	return distance;
}



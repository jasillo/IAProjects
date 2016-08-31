#include "Node.h"


Node::Node(glm::vec2 d): data(d) {
	
}
Node::~Node() {
	myEdges.clear();
 }

Edge * Node::findEdge(Node * a)
{
	for (Edge* e : myEdges) {
		if (e->isMyNode(a))
			return e;
	}
	return nullptr;
}

void Node::clear()
{
	myEdges.clear();
}

glm::vec2 Node::getData()
{
	return data;
}

void Node::addEdge(Edge * e)
{
	myEdges.push_back(e);
}


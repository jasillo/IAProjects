#include "Graph.h"


Graph::~Graph() {
	for (Edge* e : myEdges)
		e->clear();
	for (Node* n : myNodes)
		n->clear();

	for (Edge* e : myEdges)
		delete e;	
	for (Node* n : myNodes)
		delete n;
}

//se inserta 2 puntos, si existen, se sobre escribe la arista
bool Graph::insert(glm::vec2 a, glm::vec2 b, float w)
{
	Node *n1 = findNode(a);
	Node *n2 = findNode(b);
	
	// si alguno no existe -> se crea el respectivo nodo
	if (!n1)
		myNodes.push_back(new Node(a));
	if (!n2)
		myNodes.push_back(new Node(b));
	
	//se busca la arista, si existe se sobreescribe el peso
	Edge* e = n1->findEdge(n2);
	if (e)
		e->setDistance(w);
	else
		myEdges.push_back(new Edge(w, n1, n2));
	return true;
}

Node * Graph::findNode(glm::vec2 a)
{
	for (Node* n : myNodes) {
		if (n->getData() == a)
			return n;
	}
	return nullptr;
}



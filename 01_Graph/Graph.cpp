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
	if (!n1) {
		n1 = new Node(a);
		myNodes.push_back(n1);
	}		
	if (!n2) {
		n2 = new Node(b);
		myNodes.push_back(n2);
	}
			
	//se busca la arista, si existe se sobreescribe el peso
	Edge* e = n1->findEdge(n2);
	if (e)
		e->setDistance(w);
	else{

		e = new Edge(w, n1, n2);
		myEdges.push_back(e);
		n1->addEdge(e);
		n2->addEdge(e);
	}
		
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



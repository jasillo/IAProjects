#include "Graph.h"



Graph::~Graph() {
	starNode = nullptr;
	endNode = nullptr;

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

void Graph::draw()
{
	//glutSolidSphere(1, 10, 10);
	for (Node* n : myNodes)
	{
		if (n->selected)
			glColor3f(1, 0, 0);
		else
			glColor3f(1, 1, 1);
		glm::vec2 p = n->getData();
		glPushMatrix();
		glTranslatef(p.x,p.y,0);
		glutSolidSphere(2, 15, 15);
		glPopMatrix();
	}
	
	
	glBegin(GL_LINES);
	for (Edge* e : myEdges) {
		if (e->selected)
			glColor3f(1, 0, 0);
		else
			glColor3f(1, 1, 1);
		glm::vec2 p1 = e->getNode(0);
		glm::vec2 p2 = e->getNode(1);
		
		glVertex3f(p1.x, p1.y, 0);
		glVertex3f(p2.x, p2.y, 0);
		
	}
	glEnd();

}

void Graph::deepSearch()
{
	if (!starNode || !endNode)
		return;
}

void Graph::aStarSearch()
{
	if (!starNode || !endNode)
		return;
	Node* n1 = starNode;
	
}

Node * Graph::findNode(glm::vec2 a)
{
	for (Node* n : myNodes) {
		if (n->getData() == a)
			return n;
	}
	return nullptr;
}



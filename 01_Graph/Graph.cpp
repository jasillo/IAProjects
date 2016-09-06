#include "Graph.h"



Graph::~Graph() {
	startNode = nullptr;
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

		
		//glRasterPos2f(10,1);
		//gluPerspective(10, 10, 10, 10);
		glColor3f(0,1,0);
		glRasterPos2f(0,2);
		//glTranslatef(p.x, p.y+2, 0);
		//glColor3f(0,50,0);
		
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15,(int) 256);
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15,(int) 30);
		glPopMatrix();
	}

	glLineWidth(2);
		
	glBegin(GL_LINES);
	for (Edge* e : myEdges) {
		if (e->selected)
			glColor3f(1, 0, 0);
		else
			glColor3f(1, 1, 1);
		glm::vec2 p1 = e->getNode(0);
		glm::vec2 p2 = e->getNode(1);

		
	   	glm::vec2 r = p1+p2;
		r.x = r.x / 2;
		r.y = r.y / 2;
		/*glPushMatrix();		
		glRasterPos2f(20,r.y+2);
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15,55);
		// glTranslatef(r.x,r.y+2,0);
		//
		glPopMatrix();*/

		glVertex3f(p1.x, p1.y, 0);
		glVertex3f(p2.x, p2.y, 0);
		
	}
	glEnd();

}

void Graph::setPoint(float x, float y)
{
	for (Node* n : myNodes) {
		glm::vec2 p = n->getData();
		if (glm::length(glm::distance(p, glm::vec2(x, y))) < 2) {
			if (endNode)
				endNode->selected = false;
			endNode = startNode;
			startNode = n;
			startNode->selected = true;
			if (endNode)
				endNode->selected = true;
			return;
		}			
	}		
}

void Graph::deepSearch()
{
	if (!startNode || !endNode)
		return;
	for (Edge *e : myEdges)
		e->selected = false;
	for (Node *n : myNodes)
		n->visited = false;

	vector<Node*> route;
	route.push_back(startNode);
	startNode->visited = true;

	while (!route.empty() && route.back() != endNode) {
		Node *n = route.back()->getNodeNotSelected();		
		if (n) {
			route.push_back(n);
			n->visited = true;
		}			
		else 
			route.pop_back();
	}
	float cost = 0;
	if (!route.empty()) {
		for (int i = 0; i < route.size() - 1; ++i) {
			Edge *e = route[i]->findEdge(route[i + 1]);
			e->selected = true;
			cost += e->getDistance();
		}
	}
	cout << "costo = " << cost << endl;
}

void Graph::aStarSearch()
{
	if (!startNode || !endNode)
		return;
	Node* n1 = startNode;
	
}

Node * Graph::findNode(glm::vec2 a)
{
	for (Node* n : myNodes) {
		if (n->getData() == a)
			return n;
	}
	return nullptr;
}



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

void Graph::glString(const std::string str, void* font = GLUT_BITMAP_8_BY_13)
{
	for (size_t i = 0; i < str.size(); ++i)
	{
		glutBitmapCharacter(font, str[i]);
	}
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

		glColor3f(0,1,0);
		glRasterPos2i(0, 2);
		double val_x = p.x;
		double val_y = p.y;
		std::ostringstream oss;
		oss << std::setprecision(17) << val_x << ","<<val_y;
		//oss << std::setprecision(17) << val_y;
		glString(oss.str());

		glPopMatrix();
	}

	/*
	glm::vec2 r;
	r.x = (p1.x + p2.x) / 2;
	r.y = (p1.y + p2.y) / 2;
	//glPushMatrix();
	double val_xx = r.x;
	double val_yy = r.y;
	glTranslatef(val_xx, val_yy, 0);
	glColor3f(0, 1, 0);
	glRasterPos2i(0, 2);

	std::ostringstream oss;
	oss << std::setprecision(17) << val_xx << "," << val_yy;
	//oss << std::setprecision(17) << val_y;
	glString(oss.str());
	//glPopMatrix();
	*/
	

	

	glLineWidth(2);		
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

	for (Edge* ee : myEdges) {
		glm::vec2 p11 = ee->getNode(0);
		glm::vec2 p22 = ee->getNode(1);


		glPushMatrix();
		double val_xx = (p11.x + p22.x)/2.0;
		double val_yy = (p11.y + p22.y)/2.0;
		glTranslatef(val_xx, val_yy, 0);
		glColor3f(0, 1, 0);
		glRasterPos2i(0, 2);

		std::ostringstream oss;
		oss << std::setprecision(17) << ee->getDistance();
		//oss << std::setprecision(17) << val_y;
		glString(oss.str());
		glPopMatrix();
	}

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
		cout << "costo = " << cost << endl;
	}
	
}

void Graph::aStarSearch()
{
	if (!startNode || !endNode)
		return;
	for (Edge *e : myEdges)
		e->selected = false;
	for (Node *n : myNodes)
		n->visited = false;

	vector<Node*> opened;
	for (int i = 0; i < myNodes.size(); ++i) {
		myNodes[i]->ancestor = nullptr;
		myNodes[i]->weight = 1000000;
		myNodes[i]->distanceToFinal = glm::length(glm::distance(endNode->getData(), myNodes[i]->getData()));
	}
	startNode->weight = 0;
	opened.push_back(startNode);

	while (!opened.empty() && opened[0] != endNode) {
		Node * father = opened[0];
		opened.erase(opened.begin());
		vector<Edge*> ve = father->getEdges();		
		father->visited = true;
		
		for (Edge *e : ve) {
			Node *n = e->getNodeDiferent(father);
			if (!n->visited) {
				opened.push_back(n);
				float w = father->weight + e->getDistance();
				if (w < n->weight) {
					n->weight = w;
					n->ancestor = father;
				}
				updateVector(&opened);
			}			
		}			
	}

	//existe solucion
	if (opened[0] == endNode) {
		Node *n1 = endNode;
		while (n1->ancestor) {
			Node *n2 = n1->ancestor;
			Edge* e = n2->findEdge(n1);
			e->selected = true;
			n1 = n2;
		}
		cout << "costo = " << opened[0]->weight << endl;
	}
}

Node * Graph::findNode(glm::vec2 a)
{
	for (Node* n : myNodes) {
		if (n->getData() == a)
			return n;
	}
	return nullptr;
}

/* se actualiza el valor de pesos con respecto al nodo 'id'
que tiene un menor peso + la distancia al nodo final*/
void Graph::updateVector(vector<Node*>* v){		
	for (int i = v->size()-1 ; i > 0; --i) {		
		if (v->at(i)->weight + v->at(i)->distanceToFinal < v->at(i - 1)->weight + v->at(i - 1)->distanceToFinal)
			swap(v->at(i), v->at(i - 1));
		else
			return;
	}
}



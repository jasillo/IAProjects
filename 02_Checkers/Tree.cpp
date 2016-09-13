#include "Tree.h"


Tree::Tree(unsigned short lv) : level(lv)
{
	root = new Node;
	generateLevels(root, level);
	selectedX = 20;
	selectedY = 20;
	player = false;
}


Tree::~Tree()
{
	destroy(root);
}

bool Tree::movePiece(short c1,  short r1,  short c2,  short r2){
	if (root->validate(c2,r2) == -1)
		return false;	
	Node *n = root->findChild(c1,r1,c2,r2);
	if (!n)
		return false; // no existe esta jugada	
	root->removeChild(n);
	std::swap(root, n);
	destroy(n);
	generateNewLevel(root,level);
	return true;
}

void Tree::draw()
{
	bool t = false;
	glBegin(GL_QUADS);
	for (int r = 0; r < 8; ++r) {
		t = !t;
		for (int c = 0; c < 8; ++c) {
			if (t)
				glColor3f(0.2, 0.2, 0.2);
			else
				glColor3f(1, 1, 0.7);
			if (c == selectedX && r == selectedY)
				glColor3f(0.3, 1, 0.3);

			glVertex2f(c*5.0-20, r*5.0-20);
			glVertex2f((c + 1)*5.0-20, r*5.0-20);
			glVertex2f((c + 1)*5.0-20, (r + 1)*5.0-20);
			glVertex2f(c*5.0-20, (r + 1)*5.0-20);
			t = !t;
		}
	}
	glEnd();

	glTranslatef(0,0,3);
	for (int row = 0; row < 8; ++row)
		for (int col = 0; col < 8; ++col) {
			if (root->board[col][row] == 1)
				glColor3f(1,1,1);
			else if (root->board[col][row] == 3)
				glColor3f(1,0,0);
			if (root->board[col][row] >0) {
				glPushMatrix();
				glTranslatef(col*5.0-17.5,row*5.0-17.5,0);
				glutSolidSphere(2, 15, 10);
				glPopMatrix();
			}
		}
}

void Tree::selectSpace(float x, float y)
{
	short posX = x;
	short posY = y;
	--posX;
	--posY;	
	
	int test = root->validate(posX, posY);
	if (test == 0 && selectedX < 8) {
		if (movePiece(selectedX, selectedY, posX, posY)) {
			selectedX = 20;
			selectedY = 20;
			player = false;
		}
	}
	else if (test == 1) {
		if (selectedX == posX && selectedY == posY) {
			selectedX = 20;
			selectedY = 20;
		}
		else {
			selectedX = posX;
			selectedY = posY;
		}		
	}	
}

bool Tree::choosePlay()
{
	int i =-1; 
	root->minmax(-100, 100, &i);
	std::cout << i << std::endl;

	if (i == -1){
		std::cout << "fin";
		return false;
	}
	Node *n = root->children[i];
	root->removeChild(n);
	std::swap(root, n);
	destroy(n);
	generateNewLevel(root, level);
	player = true;
	return true;
}


void Tree::generateNewLevel(Node *n, unsigned short lv)
{
	--lv;
	if (lv == 1)
		n->generateChildren();
	else
		for (Node *child : n->children)
			generateLevels(child,lv);
}

void Tree::generateLevels(Node * n, unsigned short lv)
{
	if (lv > 1) {
		n->generateChildren();
		--lv;
		for (Node *child : n->children)
			generateLevels(child, lv);
	}
}

void Tree::destroy(Node * n)
{
	for (int i = 0; i < n->children.size(); ++i)
		destroy(n->children[i]);
	delete n;
}

#include "Tree.h"


Tree::Tree(unsigned short lv) : level(lv)
{
	root = new Node;
	generateLevels(root, level);
}


Tree::~Tree()
{
	delete root;
}

bool Tree::movePiece(short c1,  short r1,  short c2,  short r2){
	if (root->validate(c2,r2) == -1)
		return false;
	
	Node *n = root->findChild(c1,r1,r2,c2);
	if (!n)
		return false; // no existe esta jugada
	root->removeChild(n);
	std::swap(root, n);
	delete n;
	generateNewLevel(root,level);
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
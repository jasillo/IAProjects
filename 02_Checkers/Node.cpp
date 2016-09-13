#include "Node.h"

const int Node::dc[] = { -1, 1, -1, 1 };
const int Node::dr[] = { 1, 1, -1, -1 };


int Node::validate(short c, short r)
{
	if (0 <= c &&  c < 8 && 0 <= r && r < 8) 
		return board[c][r];		
	return -1;
}

int Node::minmax(short alpha, short betha, int *p)
{
	if (children.empty()) {
		return countPieces();		
	}
	int temp;
	
	for (int i = 0; i < children.size(); ++i) {
		short value = children[i]->minmax(alpha, betha, &temp);
		//std::cout << value<<std::endl;
		if (value < alpha || value > betha)
			i=children.size();
		else {
			if (player)//minimizar
			{
				if (betha > value) {
					betha = value;
					*p = i;
				}
			}				
			else //maximizar
			{
				if (alpha < value) {
					alpha = value;
					*p = i;
				}
			}				
		}		
	}
	
	if (player)
		return betha;
	else
		return alpha;
}


Node::Node()
{	
	for (unsigned int row = 0; row < 8; ++row)	
		for (unsigned int col = 0; col < 8; ++col)
			board[col][row] = 0;	

	unsigned int x;
	// mis fichas
	for (unsigned int row = 0; row < 3; ++row) {
		x = row % 2;
		for (unsigned int col = 0; col < 8; col += 2) 
			board[col + x][row] = 1;		
	}
		
	// fichas del openente
	for (unsigned int row = 5; row < 8; ++row) {
		x = row % 2;
		for (unsigned int col = 0; col < 8; col += 2)
			board[col + x][row] = 3;		
	}
	player = false;
}

Node::Node(unsigned short b[8][8])
{
	for (int row = 0; row < 8; ++row)
		for (int col = 0; col < 8; ++col)
			board[col][row] = b[col][row];	
	player = false;
}


Node::~Node()
{	
}

unsigned int Node::countPieces()
{
	int c = 0;
	for (int row = 0; row < 8; ++row)
		for (int col = 0; col < 8; ++col)
			if (board[col][row] > 0)
				++c;
	return c;
}



void Node::removeChild(Node * n)
{
	for (unsigned int i = 0; i < children.size(); ++i)
		if (children.at(i) == n) {
			children.erase(children.begin()+i);
			return;
		}
}

Node * Node::findChild(unsigned short c1, unsigned short r1, unsigned short c2, unsigned short r2)
{
	for (Node* n : children)
		if (!n->board[c1][r1] && n->board[c2][r2])
			return n;
	return nullptr;
}

void Node::generateChildren()
{
	if (player) 
		for (unsigned int row = 0; row < 8; ++row)
			for (unsigned int col = 0; col < 8; ++col) {
				if (board[col][row] == 1) {
					pieceMove(col, row, 0);
					pieceMove(col, row, 1);
				}
			}
	else
		for (unsigned int row = 0; row < 8; ++row)
			for (unsigned int col = 0; col < 8; ++col) {
				if (board[col][row] == 3) {
					pieceMove(col, row, 2);
					pieceMove(col, row, 3);
				}
			}	
}


void Node::pieceMove(unsigned short c, unsigned short r, unsigned short type)
{
	int t = validate(c + dc[type], r + dr[type]);
	if (t == 0) {
		Node *n = new Node(board);
		children.push_back(n);
		n->board[c + dc[type]][r + dr[type]] = n->board[c][r];
		n->board[c][r] = 0;
		n->player = !player;
	}
	else if ((player && t == 3) || (!player && t == 1))
	{
		if (validate(c + 2 * dc[type], r + 2 * dr[type]) == 0) {
			Node *n = new Node(board);
			children.push_back(n);
			n->board[c + 2*dc[type]][r + 2*dr[type]] = n->board[c][r];
			n->board[c][r] = 0;
			n->board[c + dc[type]][r + dr[type]] = 0;
			n->player = !player;
		}
	}	
}


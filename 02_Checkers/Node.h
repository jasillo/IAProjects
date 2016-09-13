#pragma once

#include <vector>
#include <iostream>

class Node
{
private:		
	static const int dr[], dc[];
	void pieceMove(unsigned short c, unsigned short r, unsigned short type);
	bool player;	

public:
	Node();
	~Node();
	Node(unsigned short b[8][8]);
	std::vector<Node*> children;
	
	unsigned short board[8][8];
	unsigned int countPieces();	
	void removeChild(Node* n);
	Node* findChild(unsigned short c1, unsigned short r1, unsigned short c2, unsigned short r2);
	void generateChildren();
	int validate(short c, short r);
	int minmax(short alpha, short betha, int *p);
	
};

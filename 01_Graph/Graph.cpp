#include "Graph.h"


Graph::~Graph() {
	for (Edge* e : myEdge) {
		delete e;
	}
	for (Node* e : myNode) {
		delete e;
	}
}



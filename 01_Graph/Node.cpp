#include "Node.h"


Node::Node(glm::vec2 data): point(data) {
	
}
Node::~Node() {
	myEdges.clear();
 }


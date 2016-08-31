#include "Graph.h"
#include <glm\glm.hpp>

using namespace std;
int main()
{
	Graph a;
	a.insert(glm::vec2(4, 2), glm::vec2(2, 2),10);
	return 1;
}
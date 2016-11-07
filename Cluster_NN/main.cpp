#include "NN_cluster.h"
#include <glm\glm.hpp>
#include <vector>


int main() 
{
	std::vector<glm::vec2> lista;
	lista.push_back(glm::vec2(1, 1));
	lista.push_back(glm::vec2(2, 2));
	lista.push_back(glm::vec2(3, 3));
	lista.push_back(glm::vec2(1, 3));
	lista.push_back(glm::vec2(1, 4));
	lista.push_back(glm::vec2(1, 2));
	lista.push_back(glm::vec2(3, 1));

	CNN_cluster my_clasificator;
	my_clasificator.cluster(&lista,3.0);
	return 0;
}
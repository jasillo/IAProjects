#include "NN_cluster.h"
#include <glm\glm.hpp>
#include <vector>
#include <cmath>
#include <random>
#include <vector>
#include <glm/vec2.hpp>
#include <glm/gtc/random.hpp>
#include <fstream>
#include "Plotter.h"

void llenar_int_vec(std::vector<glm::vec2> &v,int n_centros,int min,int max)
{
	int x,y,r;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(min, max);
	for (int i = 0; i < n_centros; ++i)
	{
		x = dis(gen);
		y = dis(gen);
		r = dis(gen)%50;		
		//std::cout <<r <<" "<< x << " "<<y;
		if (x + r > max)//{ x = x - ((x + r) - (max));}
			x = x - (r -(max-x));
		if (x - r < min)
		{
			x = x + (r - (x - min));
		}
		if (y + r > max)//{ x = x - ((x + r) - (max));}
			y = y - (r - (max - y));
		if (y - r < min)
		{
			y = y + (r - (y - min));
		}
		
		v.push_back(glm::vec2(x, y));
		for (int j = 0; j < 10; ++j)
		{
			std::uniform_int_distribution<> dis(x-r, x+r);
			int xx = dis(gen);
			if(j<10)
			{
				std::uniform_int_distribution<> dis(y-r, y+r);
				int yy = dis(gen);
				v.push_back(glm::vec2(xx, yy));				
			}
		}
		//v.push_back(glm::vec2(dis(gen), dis(gen)));
	}
	//std::cout << std::endl;
}
void imprime_int_vec(std::vector<glm::vec2> &v)
{
	std::ofstream w("puntos.txt");
	if (w.is_open()){
		for (auto i : v){w<< i.x << " " << i.y <<"\n";}
		w.close();
	}
}

int main() 
{
	std::vector<glm::vec2> lista;
	
	llenar_int_vec(lista, 10, 1, 99);
	//imprime_int_vec(lista);
	/*lista.push_back(glm::vec2(1, 1));
	lista.push_back(glm::vec2(6, 2));
	lista.push_back(glm::vec2(3, 3));
	lista.push_back(glm::vec2(1, 3));
	lista.push_back(glm::vec2(2, 4));
	lista.push_back(glm::vec2(1, 2));
	lista.push_back(glm::vec2(2, 1));*/

	CNN_cluster my_clasificator;
	std::vector<int> index = my_clasificator.cluster(&lista,10.0);
	Plotter pl(400,400);
	pl.plot(&lista);
	for (int i = 0; i < index.size(); ++i) {
		pl.Circumference(lista.at(index[i]),10.0);
	}
	pl.savePng("puntos.png");
	return 0;
}

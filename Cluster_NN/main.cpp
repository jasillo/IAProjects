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

void llenar_int_vec(vector<glm::vec2> &v, int n_centros,int densidad, int min, int max)
{
	float x, y, r;
	std::random_device rd;
	std::mt19937 gen(rd());
	//std::uniform_real_distribution<> dis(10.0, 90.0);
	std::uniform_real_distribution<> dis(min, max);
	for (int i = 0; i < n_centros; ++i)
	{
		x = (float)dis(gen);
		y = (float)dis(gen);
		//radio randomico 
		//r = (int)dis(gen) % 50;
		//radio estatico
		r = 10.0;
		//cout << r << " " << x << " " << y;
		//creo el centro y corrigo si es que usara un radio que sobre pase el limite haciendolo encajar 
		if (x + r > max)//{ x = x - ((x + r) - (max));}
			x = x - (r - (max - x));
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
		
		//por cada centro 
		//for (int t = 0; t < 10; ++t)
		for (int t = 0; t < densidad; ++t)
		{
			//genero angulo aleatorio entre 0 y 359
			std::uniform_real_distribution<> dis2(0, 359);
			float angle = (float)dis2(gen);
			
			//genero un radio temporal y  menor al radio con el que se trabaje para que este contenido dentro del circulo
			std::uniform_real_distribution<> dis3(0, r);
			float rt = (float)dis3(gen);

			//genero un punto dentro del circulo añadiendo el centro con el que se esta trabajando 
			float xx = x + rt*cos(angle);
			float yy = y + rt*sin(angle);
			v.push_back(glm::vec2(xx, yy));

			//cout << angle <<" "<<rt<<" "<<xx<<" "<<yy<<endl;
		}
		//cout << endl;
		
	}
	//cout << endl;
	
}
void imprime_vec(vector<glm::vec2> &v)
{	
	for (auto i : v) {  cout << i.x << " " << i.y << "\n"; }
	/*ofstream w("puntos.txt");
	if (w.is_open()){
		for (auto i : v){w<< i.x << " " << i.y <<"\n";}
		w.close();
	}*/	
}
void lee_vec(vector<glm::vec2> &v)
{
	std::string linea;
	std::string::size_type sz;
	ifstream r("puntos.txt");
	int i = 0;
	if (r.is_open())
	{
		while (getline(r, linea)) {
			v[i].x = std::stof(linea,&sz);
			v[i].y = std::stof(linea.substr(sz));
			i++;
		}
		r.close();
	}
	else cout << "fallo a leer";

}


int main() 
{
	std::vector<glm::vec2> lista;
	
	llenar_int_vec(lista, 10, 50,1, 99);
	lee_vec(lista);
	imprime_vec(lista);
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

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <random>

#define CROSSOVER_RATE	0.75
#define MUTATION_RATE	0.05
#define INFINITE	1000

using namespace std;
int citiesSize = 0;
int *cities;
std::default_random_engine random_engine;
vector<int> chromosomeBase, optimalRoute;

bool readFile(string name) {
	ifstream file(name);
	if (file.bad()) {
		return false;
	}
	file >> citiesSize;
	cities = new int [citiesSize * citiesSize];	
	int total = citiesSize * citiesSize;
	for (int i = 0; i < total; ++i)
		file >> cities[i];
}

int calculateCost(vector<int> *route) {
	int cost = 0;
	//cost from the initial city to the firt of the route
	cost += cities[route->at(0)];
	//cost betwen cities
	for (int i = 0; i < citiesSize - 2; ++i)
		cost += cities[citiesSize*route->at(i) + route->at(i + 1)];
	//cost from the last city to the initial city
	cost += cities[route->at(citiesSize - 2)];
	return cost;
}

vector<int> createChromosome() {	
	vector<int> temp = chromosomeBase;
	vector<int> result;
	
	while (!temp.empty()) {
		int rd = uniform_int_distribution<int>(0, temp.size()-1)(random_engine);
		result.push_back(temp.at(rd));
		temp.erase(temp.begin() + rd);
	}
	return result;
}

void passChromosome(vector<vector<int>> *src, vector<vector<int>> *des) {
	if (src->empty())
		return;
	int rd = uniform_int_distribution<int>(0, src->size() - 1)(random_engine);
	des->push_back(src->at(rd));
	src->erase(src->begin() + rd);
}

void mutate(vector<int> * chromosome) {
	int rd1 = uniform_int_distribution<int>(0, chromosome->size() - 1)(random_engine);
	int rd2 = uniform_int_distribution<int>(0, chromosome->size() - 1)(random_engine);
	while (rd1 == rd2)
		rd2 = uniform_int_distribution<int>(0, chromosome->size() - 1)(random_engine);
	swap(chromosome->at(rd1), chromosome->at(rd2));
}

void crossover(vector<int> * chromosome1, vector<int> * chromosome2) {
	vector<int> temp1 = *chromosome1;
	vector<int> temp2 = *chromosome2;
	
	int rd = uniform_int_distribution<int>(1, chromosome1->size() - 1)(random_engine);
	for (int i = 0; i < rd; ++i)
		swap(chromosome1->at(i), chromosome2->at(i));
		
	for (int i = 0; i < rd; ++i) {
		for (int j = rd; j < chromosome1->size(); ++j) {
			if (chromosome1->at(i) == chromosome1->at(j)) {
				for (int l = 0; l < rd; ++l) {
					bool found = true;
					for (int k = 0; k < rd; ++k)
						found = found && chromosome1->at(k) != temp1.at(l);

					if (found)
						swap(chromosome1->at(i), temp1.at(l));
				}
			}
			if (chromosome2->at(i) == chromosome2->at(j)) {
				for (int l = 0; l < rd; ++l) {
					bool found = true;
					for (int k = 0; k < rd; ++k)
						found = found && chromosome2->at(k) != temp2.at(l);

					if (found)
						swap(chromosome2->at(i), temp2.at(l));
				}
			}
		}
	}
}

int main() {
	if (readFile("cities.txt"))
		cout <<"numero de ciudades : " << citiesSize << endl;
	else{
		cout << "file no found" << endl;
		return 0;
	}
	
	std::mt19937 mt(random_engine());
	int populationSize, generations;
	vector<vector<int>> population;

	for (int i = 1; i < citiesSize; ++i)
		chromosomeBase.push_back(i);


	while (1) {
		cout << "cantidad de poblacion : ";
		cin >> populationSize;
		cout << "numero de generaciones : ";
		cin >> generations;
		cout << endl;

		//generate started population
		vector<int> optimalRoute;
		int optimalWeight = INFINITE;
		population.clear();
		for (int i = 0; i < populationSize; ++i) {
			population.push_back(createChromosome());
			int x = calculateCost(&population.back());
			if (x < optimalWeight) {
				optimalWeight = x;
				optimalRoute = population.back();
			}
		}
		
		// Generate new generations
		while (generations--) {
			vector<vector<int>> temp;
			temp.clear();
			while (!population.empty()) {
				passChromosome(&population, &temp);
				passChromosome(&population, &temp);
				int s = temp.size();
				
				if (uniform_real_distribution<float>(0, 1)(random_engine) < CROSSOVER_RATE)
					crossover(&temp.at(s - 2), &temp.at(s - 1));
											
				if (uniform_real_distribution<float>(0, 1)(random_engine) < MUTATION_RATE)
					mutate(&temp.at(s - 2));
				if (uniform_real_distribution<float>(0, 1)(random_engine) < MUTATION_RATE)
					mutate(&temp.at(s - 1));			
			}

			population = temp;
			for (int i = 0; i < population.size(); ++i) {
				int x = calculateCost(&population.back());
				if (x < optimalWeight) {
					optimalWeight = x;
					optimalRoute = population.back();
				}
			}
		}

		cout << "costo minimo : " << optimalWeight << endl;
		cout << "ruta optima : ";
		for (int i : optimalRoute)
			cout << i << " ";
		cout << endl << endl;
	}
	return 1;
}
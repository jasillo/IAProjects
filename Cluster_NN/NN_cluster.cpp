#include "NN_cluster.h"


void CNN_cluster::calculate_initialActivitie(std::vector<Tpoint>* points, float radius)
{
	tam = points->size();
	matrixConections = new float[tam * tam];
	neuronsActivities = new float[tam];
	newActivities = new float[tam];
	float squaredRadius = radius * radius;

	for (int i = 0; i < tam*tam; ++i)
		matrixConections[i] = 0;

	for (int i = 0; i < tam; ++i) {
		neuronsActivities[i] = 0;
		newActivities[i] = 0;
	}		

	for (int i = 0; i < tam; ++i) {
		for (int j = i + 1; j < tam; ++j) {
			float distance = glm::length(glm::distance(points->at(i), points->at(j)));
			if (distance <= radius) {
				float weight = squaredRadius / (distance*distance + squaredRadius);
				matrixConections[i * tam + j] = weight;
				matrixConections[j * tam + i] = weight;				
				neuronsActivities[i] += weight;
				neuronsActivities[j] += weight;
			}
		}
	}
}


bool CNN_cluster::calculate_newActivities()
{	
	for (int i = 0; i < tam; ++i) {		
		if (neuronsActivities[i] > 0) {
			float sum = 0;
			for (int j = 0; j < tam; ++j) {			
				if (matrixConections[i * tam + j] > 0 && neuronsActivities[j] > 0) {
					sum += matrixConections[i * tam + j] * (neuronsActivities[i] - neuronsActivities[j]);
				}				
			}
			newActivities[i] = neuronsActivities[i] + alpha * sum;
		}		
		
	}
	bool active = false;
	for (int i = 0; i < tam; ++i) {		
		if (newActivities[i] <= 0) {
			neuronsActivities[i] = 0;
		}
		else if (neuronsActivities[i] != newActivities[i]) {
			neuronsActivities[i] = newActivities[i];
			active = true;
		}
	}
	return active;
}


std::vector<int> CNN_cluster::cluster(std::vector<Tpoint>* points, float radius)
{
	std::vector<int> indices;
	int count = 0;
	int k = 0;
	calculate_initialActivitie(points, radius);

	while (calculate_newActivities())
		++count;
	std::cout << "proceso de tramsmicion termino en " << count << " pasos." << std::endl;

	for (int i = 0; i < tam; ++i) {
		if (neuronsActivities[i]) {
			++k;
			indices.push_back(i);
		}
	}			
	std::cout << "generando " << k << " clusters" << std::endl;
	
	delete[] matrixConections;
	delete[] neuronsActivities;
	delete[] newActivities;
	return indices;
}


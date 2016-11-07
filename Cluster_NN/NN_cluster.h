#pragma once
#include <vector>
#include <glm\glm.hpp>
#include <iostream>

typedef typename glm::vec2 Tpoint;

class CNN_cluster
{	
private:
	int tam;
	float alpha;
	float *matrixConections;
	float *neuronsActivities;
	float *newActivities;
	void calculate_initialActivitie(std::vector<Tpoint> *points, float radius);
	bool calculate_newActivities();

public:
	CNN_cluster() {
		alpha = 0.8f;
	};
	~CNN_cluster() {};

	std::vector<int> cluster(std::vector<Tpoint> *points, float radius);
};


#pragma once
#include <stdint.h>
#include <vector>
#include <png.h>
#include <glm\glm.hpp>
#include <math.h>
#include <iostream>

typedef typename glm::vec2 point_t;

typedef struct {
	uint8_t red;
	uint8_t green;
	uint8_t blue;
	uint8_t alpha;
} pixel_t;

class Plotter
{
private:
	pixel_t *bitmap;
	size_t width, height;
	size_t margin;
	float factor;
	size_t limit_x, limit_y;
public:	
	Plotter(size_t w, size_t h);
	~Plotter();

	bool savePng(char* name);
	void plot(std::vector<point_t> *v);
	void Circumference(point_t p, float radius);
	void clean();
	void setLimits(size_t x);
};


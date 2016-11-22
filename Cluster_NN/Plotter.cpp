#include "Plotter.h"



Plotter::Plotter(size_t w, size_t h):width(w),height(h)
{
	size_t size = width * height;
	bitmap = new pixel_t[size];
	for (int i = 0; i < size; ++i) {
		bitmap[i].red = 255;
		bitmap[i].green = 255;
		bitmap[i].blue = 255;
		bitmap[i].alpha = 255;
	}
	margin = 15;
	factor = (width - 2 * margin) / 100.0;
	limit_x = factor * 100 + margin;
	limit_y = 100 * (height / width) * factor + margin;
	std::cout << limit_x << " " << limit_y << std::endl;
}


Plotter::~Plotter()
{
	delete[] bitmap;
}

bool Plotter::savePng(char* name)
{
	FILE * fp;
	png_structp png_ptr = NULL;
	png_infop info_ptr = NULL;
	png_byte ** row_pointers = NULL;
	
	int pixel_size = 4;
	int depth = 8;

	fp = fopen(name, "wb");
	if (!fp) {
		return false;
	}

	png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (png_ptr == NULL) {
		fclose(fp);
		return false;
	}

	info_ptr = png_create_info_struct(png_ptr);
	if (info_ptr == NULL) {
		png_destroy_write_struct(&png_ptr, &info_ptr);
		fclose(fp);
		return false;
	}

	/* Set up error handling. */
	if (setjmp(png_jmpbuf(png_ptr))) {
		png_destroy_write_struct(&png_ptr, &info_ptr);
		fclose(fp);
		return false;
	}

	/* Set image attributes. */
	png_set_IHDR(png_ptr,
		info_ptr,
		width,
		height,
		depth,
		PNG_COLOR_TYPE_RGBA,
		PNG_INTERLACE_NONE,
		PNG_COMPRESSION_TYPE_DEFAULT,
		PNG_FILTER_TYPE_DEFAULT);

	/* Initialize rows of PNG. */
	row_pointers = (png_bytep*)png_malloc(png_ptr, height * sizeof(png_byte *));
		for (size_t y = 0; y < height; ++y) {
		png_byte *row = (png_bytep)png_malloc(png_ptr, sizeof(uint8_t) * width * pixel_size);
		row_pointers[y] = row;
		for (size_t x = 0; x < width; ++x) {
			size_t index = y * width + x;
			*row++ = bitmap[index].red;
			*row++ = bitmap[index].green;
			*row++ = bitmap[index].blue;
			*row++ = bitmap[index].alpha;
		}
	}


	/* Write the image data to "fp". */
	png_init_io(png_ptr, fp);
	png_set_rows(png_ptr, info_ptr, row_pointers);
	png_write_png(png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, NULL);

	for (size_t y = 0; y < height; y++) {
		png_free(png_ptr, row_pointers[y]);
	}
	png_free(png_ptr, row_pointers);

	return true;
}

void Plotter::plot(std::vector<point_t>* v)
{
	clean();	
	for (int i = 0; i < v->size(); ++i)	{
		int x = v->at(i).x * factor + margin;
		int y = height - (v->at(i).y * factor + margin);
		std::cout << x << " " << y << std::endl;
		if (x < limit_x && y < limit_y && x > margin && y > margin) {
			size_t index = y*width +x;
			bitmap[index].red = 0;
			bitmap[index].green = 0; 
			bitmap[index + 1].red = 0;
			bitmap[index + 1].green = 0;
			bitmap[index - width].red = 0;
			bitmap[index - width].green = 0;
			bitmap[index - width + 1].red = 0;
			bitmap[index - width + 1].green = 0;
		}		
	}
}

void Plotter::Circumference(point_t p, float radius)
{
	size_t center_x = p.x * factor + margin;
	size_t center_y = p.y * factor + margin;
	float r = radius * factor;
	
	for (int i = center_y - r; i <= center_y + r; ++i) {
		if (i < limit_y && i > margin) {
			int r_tmp = i - center_y;
			int tmp = sqrt(pow(r, 2) - pow(abs(r_tmp), 2));
			int x1 = center_x - tmp;
			int x2 = center_x + tmp;
			if (x1 <limit_x && x1>margin) {
				size_t index = (height - i) * width + x1;
				bitmap[index].blue = 0;
				bitmap[index].green = 0;
				bitmap[index].red = 255;
			}
			if (x2 <limit_x && x2>margin) {
				size_t index = (height - i) * width + x2;
				bitmap[index].blue = 0;
				bitmap[index].green = 0;
				bitmap[index].red = 255;
			}
		}
	}
	for (int i = center_x - r; i <= center_x + r; ++i) {
		if (i < limit_x && i > margin) {
			int r_tmp = i - center_x;
			int tmp = sqrt(pow(r, 2) - pow(abs(r_tmp), 2));
			int y1 = center_y - tmp;
			int y2 = center_y + tmp;
			if (y1 <limit_y && y1>margin) {
				size_t index = (height - y1) * width + i;
				bitmap[index].blue = 0;
				bitmap[index].green = 0;
				bitmap[index].red = 255;
			}
			if (y2 <limit_x && y2>margin) {
				size_t index = (height - y2) * width +  i;
				bitmap[index].blue = 0;
				bitmap[index].green = 0;
				bitmap[index].red = 255;
			}
		}
	}
}

void Plotter::clean()
{
	size_t size = width * height;
	for (int i = 0; i < size; ++i) {
		bitmap[i].red = 255;
		bitmap[i].green = 255;
		bitmap[i].blue = 255;
		bitmap[i].alpha = 255;
	}

	//drawing axes
	size_t tmp = (height - margin) * width;
	for (int i = margin; i < width - margin; ++i) {
		bitmap[tmp + i].red = 0;
		bitmap[tmp + i].green = 0;
		bitmap[tmp + i].blue = 0;
	}
	tmp = width * height - width * margin;
	for (int i = margin + width * margin; i < tmp; i += width) {
		bitmap[i].red = 0;
		bitmap[i].green = 0;
		bitmap[i].blue = 0;
	}
}

//seteamos en base al tamaño del eje x
void Plotter::setLimits(size_t x)
{	
	factor = (width - 2 * margin) / (float)x;
	limit_x = factor * x + margin;
	limit_y = x * (height / width) * factor + margin;
}

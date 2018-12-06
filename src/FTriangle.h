#pragma once

#include "Figure.h"
#include <algorithm>

class FTriangle : public CFigure
{
public:
	FTriangle();
	~FTriangle();
	void draw_triangle(int, int, int, int, int, int);
	void draw_pixel(int, int);
	void draw_fpixel(int, int);
	void draw_line(int, int, int, int);
	void draw_fline(int, int, int, int);
	void draw_ftriangle();
	void display();
};
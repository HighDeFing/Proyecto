#pragma once

#include "Figure.h"
#include <cmath>

class FCircle : public CFigure
{
public:

	FCircle();
	~FCircle();
	void draw_fpixel(int, int);
	void draw_circle(int, int, int, int);
	void fill_circle(int, int);
	void draw_pixel(int, int);
	void FCircle::draw_line(int, int, int, int);
	void Horizline(int, int, int);
	void display();
};
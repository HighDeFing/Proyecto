#pragma once

#include "Figure.h"

class FElipse : public CFigure
{
public:
	FElipse();
	~FElipse();
	void draw_elipse(int, int, int, int);
	void draw_pixel(int, int);
	void draw_fpixel(int, int);
	void Horizline(int, int, int);
	void display();
};
#pragma once

#include "Figure.h"

class FRectangle : public CFigure
{
public:
	FRectangle();
	~FRectangle();
	void draw_rectangle(int, int, int, int);
	void draw_pixel(int, int);
	void draw_fpixel(int, int);
	void Horizline(int, int, int);
	void display();
};
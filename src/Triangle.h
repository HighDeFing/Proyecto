#pragma once

#include "Figure.h"


class CTriangle : public CFigure
{
public:
	CTriangle();
	~CTriangle();
	void draw_triangle(int, int, int, int, int, int);
	void draw_pixel(int, int);
	void draw_line(int, int, int, int);
	void display();
};
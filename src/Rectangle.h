#pragma once

#include "Figure.h"

class CRectangle : public CFigure
{
public:
	CRectangle();
	~CRectangle();
	void draw_rectangle(int, int, int, int);
	void draw_pixel(int, int);
	void display();
};
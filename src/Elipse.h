#pragma once

#include "Figure.h"

class CElipse : public CFigure
{
public:
	CElipse();
	~CElipse();
	void draw_elipse(int, int, int, int);
	void draw_pixel(int, int);
	void display();
};

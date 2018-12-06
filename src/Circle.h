#pragma once

#include "Figure.h"
#include <cmath>

class CCircle : public CFigure
{
	public:
		CCircle();
		~CCircle();
		void draw_circle(int, int, int, int);
		void draw_pixel(int, int);
		void display();
};
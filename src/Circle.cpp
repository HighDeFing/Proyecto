#include "Circle.h"
#include <cmath>

CCircle::CCircle()
{

	mVertices = new float*[2];
	for (int i = 0; i < 2; ++i)
		mVertices[i] = new float[2];

	mType = CIRCLE;
}

CCircle::~CCircle()
{
	for (int i = 0; i < 2; ++i)
		delete[] mVertices[i];
}

void CCircle::display()
{
	int x1, x2, y1, y2;
	glColor3fv(mColor);
	x1 = int(mVertices[0][0]); x2 = int(mVertices[1][0]); y1 = int(mVertices[0][1]); y2 = int(mVertices[1][1]);
	draw_circle(x1, x2, y1, y2);
}

void CCircle::draw_pixel(int x, int y) {
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}


void CCircle::draw_circle(int x1, int x2, int y1, int y2) {

		int midx, midy, x, y, radius, dp;
		radius = abs(y1-y2);
		/* mid position of x-axis */
		midx = x1;
		/* mid position of y-axis */
		midy = y1;
		dp = 1 - radius;
		x = 0, y = radius;

		/* draws a circle */
		do {
			/*
			 * plot points on all eight octants -
			 * circle centered at (midx, midy)
			 */
			draw_pixel(midx + x, midy + y);
			draw_pixel(midx - x, midy + y);
			draw_pixel(midx + x, midy - y);
			draw_pixel(midx - x, midy - y);
			draw_pixel(midx + y, midy + x);
			draw_pixel(midx - y, midy + x);
			draw_pixel(midx + y, midy - x);
			draw_pixel(midx - y, midy - x);
			/*
			 * calculate next points(x, y) - considering
			 * the circle centered on (0, 0).
			 */
			x = x + 1;
			if (dp < 0) {
				dp = dp + 2 * x + 1;
			}
			else {
				y = y - 1;
				dp = dp + 2 * (x - y) + 1;
			}

		} while (x < y);


}

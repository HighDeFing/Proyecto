#include "FCircle.h"
#include <cmath>

FCircle::FCircle()
{

	mVertices = new float*[2];
	for (int i = 0; i < 2; ++i)
		mVertices[i] = new float[2];

	mType = FCIRCLE;
}

FCircle::~FCircle()
{
	for (int i = 0; i < 2; ++i)
		delete[] mVertices[i];
}

void FCircle::display()
{
	int x1, x2, y1, y2;
	
	
	x1 = int(mVertices[0][0]); x2 = int(mVertices[1][0]); y1 = int(mVertices[0][1]); y2 = int(mVertices[1][1]);
	draw_circle(x1, x2, y1, y2);
}

void FCircle::draw_pixel(int x, int y) {
	glColor3fv(mColor);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

void FCircle::draw_fpixel(int x, int y) {
	glColor3fv(fColor);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

void FCircle::draw_line(int x1, int x2, int y1, int y2) {
	int dx, dy, i, e;
	int incx, incy, inc1, inc2;
	int x, y;

	dx = x2 - x1;
	dy = y2 - y1;

	if (dx < 0) dx = -dx;
	if (dy < 0) dy = -dy;
	incx = 1;
	if (x2 < x1) incx = -1;
	incy = 1;
	if (y2 < y1) incy = -1;
	x = x1; y = y1;
	if (dx > dy) {
		draw_pixel(x, y);
		e = (dy << 1) - dx;
		inc1 = (dy - dx) << 1;
		inc2 = dy << 1;
		for (i = 0; i < dx; i++) {
			if (e >= 0) {
				y += incy;
				e += inc1;
			}
			else
				e += inc2;
			x += incx;
			draw_pixel(x, y);
		}

	}
	else {
		draw_pixel(x, y);
		e = (dx << 1) - dy;
		inc1 = (dx - dy) << 1;
		inc2 = dx << 1;
		for (i = 0; i < dy; i++) {
			if (e >= 0) {
				x += incx;
				e += inc1;
			}
			else
				e += inc2;
			y += incy;
			draw_pixel(x, y);
		}
	}
}
void FCircle::Horizline(int xMin, int yMin, int  xMax) {

	for (int i = xMin; i <= xMax; i++)
		draw_fpixel(i, yMin);
}

void  FCircle::fill_circle(int x, int y) {
	
}

void  FCircle::draw_circle(int x1, int x2, int y1, int y2) {
	/* Assumes center of circle is at origin. Integer arithmetic only */
	int midx, midy, x, y, radius, dp;
	radius = abs(y1 - y2);
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
		Horizline(midx -x + 1, midy + y, midx + x - 1);
		Horizline(midx -y + 1, midy + x, midx +  y - 1);
		Horizline(midx -y + 1, midy -x, midx + y - 1);
		Horizline(midx -x + 1, midy -y, midx + x - 1);
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

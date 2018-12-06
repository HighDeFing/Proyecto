#include "FElipse.h"
#include <stdlib.h>
#

FElipse::FElipse()
{

	mVertices = new float*[2];
	for (int i = 0; i < 2; ++i)
		mVertices[i] = new float[2];

	mType = LINE;
}

FElipse::~FElipse()
{
	for (int i = 0; i < 2; ++i)
		delete[] mVertices[i];
}

void FElipse::display()
{
	int x1, x2, y1, y2;
	
	x1 = int(mVertices[0][0]); x2 = int(mVertices[1][0]); y1 = int(mVertices[0][1]); y2 = int(mVertices[1][1]);
	draw_elipse(x1, x2, y1, y2);
}

void FElipse::draw_pixel(int x, int y) {
	glColor3fv(mColor);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

void FElipse::draw_fpixel(int x, int y) {
	glColor3fv(fColor);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}


void FElipse::Horizline(int xMin, int yMin, int  xMax) {

	for (int i = xMin; i <= xMax; i++)
		draw_fpixel(i, yMin);
}

void FElipse::draw_elipse(int x1, int x2, int y1, int y2) {
	long midx, midy, xradius, yradius;
	long xrad2, yrad2, twoxrad2, twoyrad2;
	long x, y, dp, dpx, dpy;

	/* x axis radius and y axis radius of ellipse */
	xradius = abs(x2 - x1); yradius = abs(y1 - y2);

	/* finding the center postion to draw ellipse */
	midx = x1;
	midy = y1;

	xrad2 = xradius * xradius;
	yrad2 = yradius * yradius;

	twoxrad2 = 2 * xrad2;
	twoyrad2 = 2 * yrad2;
	x = dpx = 0;
	y = yradius;
	dpy = twoxrad2 * y;

	draw_pixel(midx + x, midy + y);
	draw_pixel(midx - x, midy + y);
	draw_pixel(midx + x, midy - y);
	draw_pixel(midx - x, midy - y);
	Horizline(midx -x + 1, midy + y, midx + x - 1);
	Horizline(midx -x + 1, midy -y, midx + x - 1);

	dp = (long)(0.5 + yrad2 - (xrad2 * yradius) + (0.25 * xrad2));

	while (dpx < dpy) {
		x = x + 1;
		dpx = dpx + twoyrad2;
		if (dp < 0) {
			dp = dp + yrad2 + dpx;
		}
		else {
			y = y - 1;
			dpy = dpy - twoxrad2;
			dp = dp + yrad2 + dpx - dpy;
		}

		/* plotting points in y-axis(top/bottom) */
		draw_pixel(midx + x, midy + y);
		draw_pixel(midx - x, midy + y);
		draw_pixel(midx + x, midy - y);
		draw_pixel(midx - x, midy - y);
		Horizline(midx - x + 1, midy + y, midx + x - 1);
		Horizline(midx - x + 1, midy - y, midx + x - 1);
		//sleep(100);
	}

	//delay(500);

	dp = (long)(0.5 + yrad2 * (x + 0.5) * (x + 0.5) +
		xrad2 * (y - 1) * (y - 1) - xrad2 * yrad2);

	while (y > 0) {
		y = y - 1;
		dpy = dpy - twoxrad2;

		if (dp > 0) {
			dp = dp + xrad2 - dpy;
		}
		else {
			x = x + 1;
			dpx = dpx + twoyrad2;
			dp = dp + xrad2 - dpy + dpx;
		}

		/* plotting points at x-axis(left/right) */
		draw_pixel(midx + x, midy + y);
		draw_pixel(midx - x, midy + y);
		draw_pixel(midx + x, midy - y);
		draw_pixel(midx - x, midy - y);
		Horizline(midx - x + 1, midy + y, midx + x - 1);
		Horizline(midx - x + 1, midy - y, midx + x - 1);
		//delay(100);
	}
}
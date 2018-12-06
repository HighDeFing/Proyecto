#pragma once

#include "../headers/glfw3.h"

enum FigureType
{
	NONE,
	LINE,
	QUAD,
	CIRCLE,
	RECTANGLE,
	ELIPSE,
	TRIANGLE,
	FCIRCLE,
	FELIPSE,
	FRECTANGLE,
	FTRIANGLE,
};

class CFigure
{
protected:
	float **mVertices, mColor[3], fColor[3];
	int mType;

public:
	CFigure();
	virtual ~CFigure();
	void setVertex(int id, float x, float y);
	void setColor(float r, float g, float b);
	void setFColor(float r, float g, float b);
	virtual void display() = 0;
	int getType();
	float* getVertex(int id);
	float* getColor();
};
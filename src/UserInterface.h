#pragma once

#include "../headers/AntTweakBar.h"
#include <iostream>
#include <string>
#include "Figure.h"

using std::string;

//Singleton user interface class

class CUserInterface
{
private:
	static CUserInterface * mInterface; //Holds the instance of the class
	TwBar *mUserInterface;
	float mFigureColor[3], fFigureColor[3];
	string mFigureType;

public:
	///Method to obtain the only instance of the calls
	static CUserInterface * Instance();
	~CUserInterface();
	void reshape();
	void show();
	void hide();
	void setFigureColor(float *color);
	void setFigureType(string type);
	float* getFigureColor();
	FigureType getFigureType();
	float* getFigureFColor();
	void setFigureFColor(float *color);

private:
	///Private constructor
	CUserInterface(); 
};
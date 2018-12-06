#include "Main.h"
#include "Line.h"
#include "Quad.h"
#include "Circle.h"
#include "UserInterface.h"
#include "Rectangle.h"
#include "Elipse.h"
#include "Triangle.h"
#include "FCircle.h"
#include "FElipse.h"
#include "FRectangle.h"
#include "FTriangle.h"



using std::vector;

GLFWwindow *gWindow;
int gWidth, gHeight;
bool gPress, trian=false;
CUserInterface * userInterface;
vector <CFigure *> figures;
FigureType figureSelected;
int picked;
int triang=0;


void pick(int x, int y)
{
	float* Color;
	picked = -1;
	//userInterface->hide();

	for (unsigned int i = 0; i < figures.size(); i++)
	{
		float *b1, *b2;
		float *v1 = figures[i]->getVertex(0);
		float *v2 = figures[i]->getVertex(1);
		float max[2];
		float min[2];
		// This should be precalculated

		max[0] = MAX(v1[0], v2[0]);
		max[1] = MAX(v1[1], v2[1]);

		min[0] = MIN(v1[0], v2[0]);
		min[1] = MIN(v1[1], v2[1]);
		if (x >= min[0] && x <= max[0] && y >= min[1] && y <= max[1]) {
			picked = i;
			userInterface->setFigureColor(figures[picked]->getColor());
			userInterface->show();
			int type = figures[picked]->getType();
					if (figures[i]->getType() == TRIANGLE) {
						userInterface->setFigureType("Triangle");
					}else if (type == LINE) {
						max[0] = MAX(v1[0], v2[0]);
						max[1] = MAX(v1[1], v2[1]);
						min[0] = MIN(v1[0], v2[0]);
						min[1] = MIN(v1[1], v2[1]);
						userInterface->setFigureType("Line");
						CRectangle *rectangle = new CRectangle();
						rectangle->setVertex(0, max[0], max[1]);
						rectangle->setVertex(1, min[0], min[1]);
						Color = userInterface->getFigureColor();
						rectangle->setColor(255,0,0);
						figures.push_back(rectangle);
						//gPress = true;
					}
					else if (type == CIRCLE || type== FRECTANGLE) {
						userInterface->setFigureType("Cricle");
						//gPress = true;
					}
					else if (type == RECTANGLE || type == FRECTANGLE) {

						userInterface->setFigureType("Rectangle");
					}
					else if (type == ELIPSE || type == FELIPSE) {
						userInterface->setFigureType("Elipse");
					}
					else if (type == TRIANGLE || type == FTRIANGLE) {
						userInterface->setFigureType("Triangle");
					}
				}
	}

}

void updateUserInterface()
{
	if (picked > -1)
	{
		float * color = userInterface->getFigureColor();
		figures[picked]->setColor(color[0], color[1], color[2]);
	}
}

void display()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	for (unsigned int i = 0; i < figures.size(); i++)
		figures[i]->display();
}

void reshape(GLFWwindow *window, int width, int height)
{
	gWidth = width;
	gHeight = height;

	glViewport(0, 0, gWidth, gHeight);

	userInterface->reshape();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0, gWidth, 0, gHeight, -1.0f, 1.0f);
}

void keyInput(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if (TwEventKeyGLFW(key, action))
		//figureSelected = userInterface->getFigureType();
		return;

	if (action == GLFW_PRESS)
	{
		switch (key)
		{
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(window, GL_TRUE);
			break;

		case GLFW_KEY_P:
			figureSelected = NONE;
			//userInterface->hide();
			break;

		case GLFW_KEY_L:
			figureSelected = LINE;
			//userInterface->hide();
			break;

		case GLFW_KEY_Q:
			figureSelected = QUAD;
			//userInterface->hide();
			break;
		}
	}
}

void mouseButton(GLFWwindow* window, int button, int action, int mods)
{
	float * Color,*FColor;
	if (TwEventMouseButtonGLFW(button, action))
		return;

	double x, y;
	glfwGetCursorPos(gWindow, &x, &y);

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && !gPress)
	{
		float ax = float(x);
		float ay = gHeight - float(y);
		if (trian) {
			figures.back()->setVertex(1, ax, ay);
			trian = false;
		}else if (figureSelected == NONE) {
			pick(int(ax), int(ay));
		}
		else if (figureSelected == FTRIANGLE) {
			FTriangle *ftriangle = new FTriangle();
			ftriangle->setVertex(0, ax, ay);
			ftriangle->setVertex(1, ax, ay);
			ftriangle->setVertex(2, ax, ay);
			Color = userInterface->getFigureColor();
			ftriangle->setColor(Color[0], Color[1], Color[2]);
			FColor = userInterface->getFigureFColor();
			ftriangle->setFColor(FColor[0], FColor[1], FColor[2]);
			figures.push_back(ftriangle);
			gPress = true;
			trian = true;
		}else if (figureSelected == TRIANGLE) {
			CTriangle *triangle = new CTriangle();
			triangle->setVertex(0, ax, ay);
			triangle->setVertex(1, ax, ay);
			triangle->setVertex(2, ax, ay);
			Color = userInterface->getFigureColor();
			triangle->setColor(Color[0], Color[1], Color[2]);
			figures.push_back(triangle);
			gPress = true;
			trian = true;
		}
		else if (figureSelected == LINE)
		{
			CLine *line = new CLine();
			line->setVertex(0, ax, ay);
			line->setVertex(1, ax, ay);
			Color=userInterface->getFigureColor();
			line->setColor(Color[0], Color[1], Color[2]);
			figures.push_back(line);
			gPress = true;
		}
		else if (figureSelected == CIRCLE) {
			CCircle *circle = new CCircle();
			circle->setVertex(0, ax, ay);
			circle->setVertex(1, ax, ay);
			Color = userInterface->getFigureColor();
			circle->setColor(Color[0], Color[1], Color[2]);
			figures.push_back(circle);
			gPress = true;
		}
		else if (figureSelected == ELIPSE) {
			CElipse *elipse = new CElipse();
			elipse->setVertex(0, ax, ay);
			elipse->setVertex(1, ax, ay);
			Color = userInterface->getFigureColor();
			elipse->setColor(Color[0], Color[1], Color[2]);
			figures.push_back(elipse);
			gPress = true;
		}
		else if (figureSelected == RECTANGLE){
			CRectangle *rectangle = new CRectangle();
			rectangle->setVertex(0, ax, ay);
			rectangle->setVertex(1, ax, ay);
			Color = userInterface->getFigureColor();
			rectangle->setColor(Color[0], Color[1], Color[2]);
			figures.push_back(rectangle);
			gPress = true;
		}else if (figureSelected == FCIRCLE) {
			FCircle *fcircle = new FCircle();
			fcircle->setVertex(0, ax, ay);
			fcircle->setVertex(1, ax, ay);
			Color = userInterface->getFigureColor();
			fcircle->setColor(Color[0], Color[1], Color[2]);
			FColor = userInterface->getFigureFColor();
			fcircle->setFColor(FColor[0], FColor[1], FColor[2]);
			figures.push_back(fcircle);
			gPress = true;
		}
		else if (figureSelected == FELIPSE) {
			FElipse *felipse = new FElipse();
			felipse->setVertex(0, ax, ay);
			felipse->setVertex(1, ax, ay);
			Color = userInterface->getFigureColor();
			felipse->setColor(Color[0], Color[1], Color[2]);
			FColor = userInterface->getFigureFColor();
			felipse->setFColor(FColor[0], FColor[1], FColor[2]);
			figures.push_back(felipse);
			gPress = true;
		}
		else if (figureSelected == FRECTANGLE) {
			FRectangle *frectangle = new FRectangle();
			frectangle->setVertex(0, ax, ay);
			frectangle->setVertex(1, ax, ay);
			Color = userInterface->getFigureColor();
			frectangle->setColor(Color[0], Color[1], Color[2]);
			FColor = userInterface->getFigureFColor();
			frectangle->setFColor(FColor[0], FColor[1], FColor[2]);
			figures.push_back(frectangle);
			gPress = true;
		}/*else
		
			CQuad *quad = new CQuad();
			quad->setVertex(0, ax, ay);
			quad->setVertex(1, ax, ay);
			figures.push_back(quad);

			gPress = true;
		}*/
	}
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
		gPress = false;

}

void cursorPos(GLFWwindow* window, double x, double y)
{
	if (TwEventMousePosGLFW(int(x), int(y)))
		return;
	CFigure *aux=figures.back();
	if (gPress) {
		float ax = float(x);
		float ay = gHeight - float(y);
		figures.back()->setVertex(1, ax, ay);
		if (trian) {
			figures.back()->setVertex(2, ax, ay);
		}
	}


}

void charInput(GLFWwindow* window, unsigned int scanChar)
{
	if (TwEventCharGLFW(scanChar, GLFW_PRESS))
		return;
}

void destroy()
{
	for (unsigned int i = 0; i < figures.size(); i++)
		delete figures[i];

	delete userInterface;

	TwTerminate();
	glfwDestroyWindow(gWindow);
	glfwTerminate();
}

bool initGlfw()
{
	if (!glfwInit())
		return false;

	gWindow = glfwCreateWindow(gWidth, gHeight, "ICG - Plantilla", NULL, NULL);

	if (!gWindow)
	{
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(gWindow);

	const GLFWvidmode * vidMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	glfwSetWindowPos(gWindow, (vidMode->width - gWidth) >> 1, (vidMode->height - gHeight) >> 1);

	glfwSetWindowSizeCallback(gWindow, reshape);
	glfwSetKeyCallback(gWindow, keyInput);
	glfwSetMouseButtonCallback(gWindow, mouseButton);
	glfwSetCursorPosCallback(gWindow, cursorPos);
	glfwSetCharCallback(gWindow, charInput);

	return true;
}

bool initUserInterface()
{
	if (!TwInit(TW_OPENGL, NULL))
		return false;

	userInterface = CUserInterface::Instance();

	return true;
}

int main(void)
{
	gWidth = 1200;
	gHeight = 680;
	gPress = false;
	//figureSelected = LINE;
	picked = -1;

	if (!initGlfw() || !initUserInterface())
		return EXIT_FAILURE;

	reshape(gWindow, gWidth, gHeight);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	while (!glfwWindowShouldClose(gWindow))
	{
		
		display();
		TwDraw();
		figureSelected = userInterface->getFigureType();
		updateUserInterface();
		glfwSwapBuffers(gWindow);
		glfwPollEvents();
		
	}

	destroy();

	return EXIT_SUCCESS;
}
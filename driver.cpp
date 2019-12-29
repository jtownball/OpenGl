
#include <Windows.h>
#include <math.h>
#include <GL/GL.h>
#include <GL/glut.h>
#include <random>

const double PI = 3.14159265;
const int screenWidth = 1000;
const int screenHeight = 1000;

void display() 
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);

	glBegin(GL_POINTS);
	glVertex2f(10.0, 10.0);
	glVertex2f(150.0, 80.0);
	glVertex2f(100.0, 20.0);
	glVertex2f(200.0, 100.0);
	glEnd();
	glFlush();
}

class GLintPoint
{
public:
	GLint x, y;
};

// return a random integer
// between the values of 0
// and m - 1
int random(int m)
{
	return std::rand() % m;
}

// draws a dot at position (x,y)
void drawDot(GLint x, GLint y)
{
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

void Sierpinski(void)
{
	GLintPoint T[3] = {
					   {screenWidth / 4,screenHeight / 4},
					   {screenWidth / 2,screenHeight * 3/4},
					   {screenWidth * 3/4, screenHeight / 4}
					  };

	int index = random(3);
	GLintPoint point = T[index];
	drawDot(point.x, point.y);
	for (int i = 0; i < 10000; ++i)
	{
		index = random(3);
		point.x = (point.x + T[index].x) / 2; 
		point.y = (point.y + T[index].y) / 2; 
		drawDot(point.x, point.y);
	}
	glFlush();
}

double myFunction(GLdouble x)
{
	double val = static_cast<double>(x);
	// put any mathematical function here
	//double retVal = exp(-x) * cos(2 * PI * x);

	// normal distribution
	double sigma = 1;
	double mu = 3;
	double retVal = exp(-0.5 * pow((x - mu), 2) / sigma) / (sigma * sqrt(2 * PI));
	return (GLdouble)retVal;
}

void drawFunction(void)
{
	GLdouble A, B, C, D;
	A = screenWidth / 15;
	B = 7.5;
	C = screenHeight / 2.0;
	D = C;

	glBegin(GL_POINTS);
	for (GLdouble x = -5; x < 10; x += 0.005)
	{
		glVertex2d(A*x + B, C*myFunction(x) + D);
	}
	glEnd();
	glFlush();
}

void myinit() 
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, screenWidth, 0.0, screenHeight);
}

void main(int argc, char** argv) 
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(screenWidth, screenHeight);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Points");
	// Sierpinski
	//glutDisplayFunc(Sierpinski);

	//drawFunction
	glutDisplayFunc(drawFunction);

	//glutDisplayFunc(display);

	myinit();
	glutMainLoop();
}

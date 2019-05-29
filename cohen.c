#define GLUT_DISABLE_ATEXIT_HACK
#include<stdio.h>
#include<GL/gl.h>
#include<GL/glut.h>
#include<stdlib.h>
#include<math.h>
#define bottom 1
#define left 2
#define top 4
#define right 8
int xmin=50, xmax=100, ymin=50, ymax=100;
int compute(int x, int y)
{
	int code = 0;
	if(x < xmin)
		code |= left;
	if(x > xmax)
		code |= right;
	if(y < ymin)
		code |= bottom;
	if(y > ymax)
		code |= top;
	return code;
}
void init()
{
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, 500, 0, 500);
	glMatrixMode(GL_MODELVIEW);
}
void cohen(int x0, int y0, int x1, int y1)
{
	bool done = false, accept = false;
	int x, y;
	float m = (y1-y0)/(float)(x1-x0);
	while(!done)
	{
		int code0 = compute(x0, y0);
		int code1 = compute(x1, y1);
		if(code0 & code1)
			done = true;
		else if(!(code0 | code1))
			done = accept = true;
		else
		{
			int out = code0?code0:code1;
			if(out & bottom)
			{
				y = ymin;
				x = x0 + (ymin - x0)*(1.0/m);
			}
			if(out & left)
			{
				x = xmin;
				y = y0 + (xmin - x0)*m;
			}
			if(out & top)
			{
				y = ymax;
				x = x0 + (ymax - y0)*(1.0/m);
			}
			if(out & right)
			{
				x = xmax;
				y = y0 + (xmax - x0)*m;
			}

			if(out == code0)
			{
				x0 = x;
				y0 = y;
				code0 = compute(x0, y0);
			}
			if(out == code1)
			{
				x1 = x;
				y1 = y;
				code1 = compute(x1, y1);
			}
		}
	}
	glTranslatef(100, 100, 0);
	glColor3f(1, 0, 0);
	glBegin(GL_LINE_LOOP);
		glVertex2f(xmin, ymin);
		glVertex2f(xmin, ymax);
		glVertex2f(xmax, ymax);
		glVertex2f(xmax, ymin);
	glEnd();
	if(accept)
	{
		glColor3f(0, 1, 0);
		glBegin(GL_LINES);
			glVertex2f(x0, y0);
			glVertex2f(x1, y1);
		glEnd();
	}
}
void display()
{
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1, 0, 0);
	glBegin(GL_LINE_LOOP);
		glVertex2f(xmin, ymin);
		glVertex2f(xmin, ymax);
		glVertex2f(xmax, ymax);
		glVertex2f(xmax, ymin);
	glEnd();
	glColor3f(0, 1, 0);
	glBegin(GL_LINES);
		glVertex2f(70, 20);
		glVertex2f(90, 120);
	glEnd();
	cohen(70, 20, 90, 120);
	glFlush();
}
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutCreateWindow("Cohen Sutherland");
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	init();
	glutDisplayFunc(display);
	glutMainLoop();
}
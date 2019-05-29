#define GLUT_DISABLE_ATEXIT_HACK
#include<stdio.h>
#include<GL/gl.h>
#include<GL/glut.h>
#include<stdlib.h>
#include<math.h>
int xcor1, xcor0, ycor1, ycor0;
float m;
void init()
{
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, 500, 0, 500);
	glMatrixMode(GL_MODELVIEW);
}
void draw_pixel(int x, int y)
{
	glColor3f(1, 0, 0);
	glBegin(GL_POINTS);
		glVertex2f(x, y);
	glEnd();
}
void linedrawing()
{
	if(xcor0 > xcor1)
	{
		xcor0 ^= xcor1 ^= xcor0 ^= xcor1;
		ycor0 ^= ycor1 ^= ycor0 ^= ycor1;
	}
	int dy, dx, p, ppos, pneg, x=xcor0, y=ycor0;
	dy = ycor1 - ycor0;
	dx = xcor1 - xcor0;
	m = dy/(float)dx;
	dy = abs(dy);
	dx = abs(dx);
	p = 2*dy-dx;
	ppos = 2*dy;
	pneg = 2*dy-2*dx;
	while(x < xcor1)
	{
		x++;
		if(p < 0)
			p += pneg;
		else
		{
			if(m < 0)
				y--;
			else
				y++;
            p += ppos;
		}
		draw_pixel(x, y);
	}
}
void linedrawing1()
{
	if(ycor0 > ycor1)
	{
		xcor0 ^= xcor1 ^= xcor0 ^= xcor1;
		ycor0 ^= ycor1 ^= ycor0 ^= ycor1;
	}
	float dy, dx, m, p, ppos, pneg, x=xcor0, y=ycor0;
	dy = ycor1 - ycor0;
	dx = xcor1 - xcor0;
	m = dx/(float)dy;
	dy = abs(dy);
	dx = abs(dx);
	p = 2*dx-dy;
	ppos = 2*dx;
	pneg = 2*dx-2*dy;
	while(y < ycor1)
	{
		y++;
		if(p < 0)
			p += pneg;
		else
		{
			if(m < 0)
				x--;
			else
				x++;
            p += ppos;
		}
		draw_pixel(x, y);
	}
}
void display()
{
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	m = (ycor1 - ycor0) / (float) (xcor1 - xcor0);
	if(m < 1)
		linedrawing();
	else
		linedrawing1();
	glFlush();
}
int main(int argc, char **argv)
{
    scanf("%d%d%d%d", &xcor0, &ycor0, &xcor1, &ycor1);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutCreateWindow("Bresenham Line Drawing");
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	init();
	glutDisplayFunc(display);
	glutMainLoop();
}
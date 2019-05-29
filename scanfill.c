#define GLUT_DISABLE_ATEXIT_HACK
#include<stdio.h>
#include<GL/gl.h>
#include<GL/glut.h>
#include<stdlib.h>
#include<math.h>
int flag=0;
void init()
{
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, 500, 0, 500);
	glMatrixMode(GL_MODELVIEW);
}
void edgedetect(int x0, int y0, int x1, int y1, int *le, int *re)
{
	if(y0 > y1)
	{
		x0 ^= x1 ^= x0 ^= x1;
		y0 ^= y1 ^= y0 ^= y1;
	}
	float m = (x1 - x0)/(float)(y1-y0), x=x0;
	for(int i=y0; i<=y1; i++)
	{
		x += m;
		if(x < le[i])
			le[i] = x;
		if(x > re[i])
			re[i] = x;
	}
}
void scanfill(int x0, int y0, int x1, int y1, int x2, int y2, int x3, int y3)
{
	int le[500], re[500]={0};
	for(int i=0; i<500; i++)
		le[i] = 500;
	edgedetect(x0, y0, x1, y1, le, re);
	edgedetect(x1, y1, x2, y2, le, re);
	edgedetect(x2, y2, x3, y3, le, re);
	edgedetect(x3, y3, x0, y0, le, re);
	for(int i=0; i<500; i++)
	{
		for(int j=le[i]; j<=re[i]; j++)
		{
			glColor3f(0, 1, 0);
			glBegin(GL_POINTS);
				glVertex2f(j, i);
			glEnd();
		}
	}
}
void display()
{
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1, 0, 0);
	glBegin(GL_LINE_LOOP);
		glVertex2f(200, 100);
		glVertex2f(100, 200);
		glVertex2f(200, 400);
		glVertex2f(400, 200);
	glEnd();
	if(flag == 1)
		scanfill(200, 100, 100, 200, 200, 400, 400, 200);
	glFlush();
}
void menu(int id)
{
	switch(id)
	{
		case 1: flag = 1; break;
		case 2: flag = 0; break;
		case 3: exit(0);
	}
	glutPostRedisplay();
}
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutCreateWindow("Scanfill");
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	init();

	glutCreateMenu(menu);
	glutAddMenuEntry("Fill Color", 1);
	glutAddMenuEntry("Clear Color", 2);
	glutAddMenuEntry("Quit", 3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);


	glutDisplayFunc(display);
	glutMainLoop();
}
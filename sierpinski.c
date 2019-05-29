#define GLUT_DISABLE_ATEXIT_HACK
#include<stdio.h>
#include<GL/gl.h>
#include<GL/glut.h>
#include<stdlib.h>
#include<math.h>
float v[4][3] = {
	{0, 0, 1}, {0, 1, -1}, {-1, -1, -1}, {1, -1, -1}
};
void init()
{
	glMatrixMode(GL_PROJECTION);
	glOrtho(-2, 2, -2, 2, -2, 2);
	glMatrixMode(GL_MODELVIEW);
}
void draw_triangle(float *a, float *b, float *c)
{
	glBegin(GL_TRIANGLES);
		glVertex3fv(a);
		glVertex3fv(b);
		glVertex3fv(c);
	glEnd();
}
void divide(float *a, float *b, float *c, int m)
{
	if(m > 0)
	{
		float v1[3], v2[3], v3[3];
		for(int i=0; i<3; i++)
		{
			v1[i] = (a[i]+c[i])/2.0;
			v2[i] = (a[i]+b[i])/2.0;
			v3[i] = (b[i]+c[i])/2.0;
		}
		divide(a, v1, v2, m-1);
		divide(b, v2, v3, m-1);
		divide(c, v1, v3, m-1);
	}
	else
		draw_triangle(a, b, c);
}
void display()
{
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColor3f(1, 0, 0);
	divide(v[1], v[2], v[3], 1);
	glColor3f(0, 1, 0);
	divide(v[0], v[1], v[2], 1);
	glColor3f(0, 0, 1);
	divide(v[0], v[1], v[3], 1);
	glColor3f(1, 1, 0);
	divide(v[0], v[2], v[3], 1);

	glFlush();
}
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("Gasket");
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	init();
	glEnable(GL_DEPTH_TEST);
	glutDisplayFunc(display);
	glutMainLoop();
}
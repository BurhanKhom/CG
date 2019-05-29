#define GLUT_DISABLE_ATEXIT_HACK
#include<stdio.h>
#include<GL/gl.h>
#include<GL/glut.h>
#include<stdlib.h>
#include<math.h>
float theta[] = {0, 0, 0};
int axis=0;
float v[8][3] = {
	{-1, -1, 1},
	{-1, 1, 1},
	{1, 1, 1},
	{1, -1, 1},
	{-1, -1, -1},
	{-1, 1, -1},
	{1, 1, -1},
	{1, -1, -1},
};
void init()
{
	glMatrixMode(GL_PROJECTION);
	glOrtho(-2, 2, -2, 2, -2, 2);
	glMatrixMode(GL_MODELVIEW);
}
void polygon(float *a, float *b, float *c, float *d)
{
	glBegin(GL_POLYGON);
		glVertex3fv(a);
		glVertex3fv(b);
		glVertex3fv(c);
		glVertex3fv(d);
	glEnd();
}
void cube()
{
	glColor3f(1, 0, 0);
	polygon(v[0], v[1], v[2], v[3]);

	glColor3f(0, 1, 0);
	polygon(v[0], v[1], v[5], v[4]);

	glColor3f(0, 0, 1);
	polygon(v[4], v[5], v[6], v[7]);

	glColor3f(1, 0, 1);
	polygon(v[6], v[7], v[3], v[2]);

	glColor3f(1, 1, 0);
	polygon(v[1], v[2], v[6], v[5]);

	glColor3f(0, 1, 1);
	polygon(v[0], v[3], v[7], v[4]);
}
void spin()
{
	theta[axis] += 0.1;
	if(theta[axis] > 360)
		theta[axis] = 0;
	glutPostRedisplay();
}
void display()
{
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glRotatef(theta[0], 1, 0, 0);
	glRotatef(theta[1], 0, 1, 0);
	glRotatef(theta[2], 0, 0, 1);
	cube();
	glFlush();
	glutSwapBuffers();
}
void mouseHandler(int btn, int state, int x, int y)
{
	if(btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		axis = 1;
	if(btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
		axis = 2;
}
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("Color Cube");
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	init();
	glutIdleFunc(spin);
	glutMouseFunc(mouseHandler);
	glEnable(GL_DEPTH_TEST);
	glutDisplayFunc(display);
	glutMainLoop();
}
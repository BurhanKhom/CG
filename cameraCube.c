#define GLUT_DISABLE_ATEXIT_HACK
#include<stdio.h>
#include<GL/gl.h>
#include<GL/glut.h>
#include<stdlib.h>
#include<math.h>
float view[] = {0, 0, 4};
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
	glFrustum(-2, 2, -2, 2, 2, 20);
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
void display()
{
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(view[0], view[1], view[2], 0, 0, 0, 0, 1, 0);
	cube();
	glFlush();
	glutSwapBuffers();
}
void keyboardHandler(unsigned char key, int x, int y)
{
    glLoadIdentity();
	switch(key)
	{
		case 'a': view[0] -= 1; break;
		case 'd': view[0] += 1; break;
		case 'w': view[1] += 1; break;
		case 's': view[1] -= 1; break;
		case 'm': view[2] -= 1; break;
		case 'k': view[2] += 1; break;
	}
	glutPostRedisplay();
}
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("Color Cube");
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	init();
	glutKeyboardFunc(keyboardHandler);
	glEnable(GL_DEPTH_TEST);
	glutDisplayFunc(display);
	glutMainLoop();
}
#define GLUT_DISABLE_ATEXIT_HACK
#include<stdio.h>
#include<GL/gl.h>
#include<GL/glut.h>
#include<stdlib.h>
#include<math.h>
float triangle[3][3] = {
	{0, 300, 150},
	{0, 0, 200},
	{1, 1, 1}
};
float rot_mat[3][3] = {{0}, {0}, {0}};
float result[3][3] = {{0}, {0}, {0}};
float h, k, m, n, theta=0;
void init()
{
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-500, 500, -500, 500);
	glMatrixMode(GL_MODELVIEW);
}
void draw_triangle(float a[3][3])
{
	glBegin(GL_TRIANGLES);
		glVertex2f(a[0][0], a[1][0]);
		glVertex2f(a[0][1], a[1][1]);
		glVertex2f(a[0][2], a[1][2]);
	glEnd();
}
void multiply()
{
	for(int i=0; i<3; i++)
		for(int j=0; j<3; j++)
			for(int k=0; k<3; k++)
				result[i][j] += rot_mat[i][k] * triangle[k][j];
}
void rotateTriangle(int m, int n)
{
	rot_mat[0][0] = cos(theta);
	rot_mat[0][1] = -sin(theta);
	rot_mat[0][2] = m;

	rot_mat[1][0] = sin(theta);
	rot_mat[1][1] = cos(theta);
	rot_mat[1][2] = n;

	rot_mat[2][0] = 0;
	rot_mat[2][1] = 0;
	rot_mat[2][2] = 1;

	multiply();
}
void display()
{
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m = -h*(cos(theta)-1) + k*sin(theta);
	n = k*(cos(theta)-1) - h*sin(theta);

	glColor3f(1, 0, 0);
	draw_triangle(triangle);

	rotateTriangle(0, 0);
	glColor3f(0, 1, 0);
	draw_triangle(result);

	for(int i=0; i<3; i++)
		for(int j=0; j<3; j++)
			result[i][j] = 0;
	rotateTriangle(m, n);
	glColor3f(1, 1, 0);
	draw_triangle(result);
	glFlush();
}
int main(int argc, char **argv)
{
	printf("Enter angle: ");
	scanf("%f", &theta);
	theta = (theta * 3.14)/180.0;
	printf("Enter fixed point: ");
	scanf("%f%f", &h, &k);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutCreateWindow("Rotate Triangle");
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	init();
	glutDisplayFunc(display);
	glutMainLoop();
}
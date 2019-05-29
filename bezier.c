#define GLUT_DISABLE_ATEXIT_HACK
#include<stdio.h>
#include<GL/gl.h>
#include<GL/glut.h>
#include<stdlib.h>
#include<math.h>
#define PI 3.1416
int flag=0;
GLsizei winWidth=600,winHeight=600;
float xwcMin=0.0, xwcMax=130.0;
float ywcMin=0.0,ywcMax=130.0;
struct wcPt3D
{
	float x,y,z;
};
void bino(int n,int *C)
{
	int k,j;
	for(k=0;k<=n;k++)
	{
		C[k]=1;
		for(j=n;j>=k+1;j--)
			C[k] *= j;
		for(j=n-k;j>=2;j--)
			C[k] /= j;
	}
}
void computeBezPt(float u,wcPt3D *bezPt,int nCtrlPts,wcPt3D *ctrlPts,int *C)
{
	int k,n=nCtrlPts-1;
	float bezBlendFcn;
	bezPt -> x=bezPt -> y=bezPt -> z=0.0;
	for(k=0;k<nCtrlPts;k++)
	{
		bezBlendFcn = C[k]*pow(u,k)*pow(1-u,n-k);
		bezPt ->x += ctrlPts[k].x*bezBlendFcn;
		bezPt ->y += ctrlPts[k].y*bezBlendFcn;
		bezPt ->z += ctrlPts[k].z*bezBlendFcn;
	}
}
void bezier(wcPt3D *ctrlPts,int nCtrlPts,int nBezCurvePts)
{
	wcPt3D bezCurvePt;
	float u;
	int *C,k;
	C=new int[nCtrlPts];
	bino(nCtrlPts-1,C);
	glBegin(GL_LINE_STRIP);
	for(k=0;k<=nBezCurvePts;k++)
	{
		u=float(k)/float(nBezCurvePts);
		computeBezPt(u,&bezCurvePt,nCtrlPts,ctrlPts,C);
		glVertex2f(bezCurvePt.x,bezCurvePt.y);
	}
	glEnd();
	delete[]C;
}
void displayFcn()
{
	int nCtrlPts=4,nBezCurvePts=20;
	static float theta=0;
	wcPt3D ctrlPts[4]={
	{20,100,0},
	{30,110,0},
	{50,90,0},
	{60,100,0}};
	if(flag==1)
	{
	
		ctrlPts[1].x +=10*sin(theta*PI/180.0);
		ctrlPts[1].y +=5*sin(theta*PI/180.0);
		ctrlPts[2].x -=10*sin((theta+30)*PI/180.0);
		ctrlPts[2].y -=10*sin((theta+30)*PI/180.0);
		ctrlPts[3].x -=4*sin((theta)*PI/180.0);
		ctrlPts[3].y +=sin((theta-30)*PI/180.0);
	}
	theta +=2.0;
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,1.0,1.0);
	glPointSize(5);
	glPushMatrix();
	glLineWidth(5);
	glColor3f(255/255,153/255.0,51/255.0);
	for(int i=0;i<8;i++)
	{
		glTranslatef(0,-0.8,0);
		bezier(ctrlPts,nCtrlPts,nBezCurvePts);
	}
	glColor3f(1,1,1);
	for(int i=0;i<8;i++)
	{
		glTranslatef(0,-0.8,0);
		bezier(ctrlPts,nCtrlPts,nBezCurvePts);
	}
	glColor3f(19/255.0,136/255.0,8/255.0);
	for(int i=0;i<8;i++)
	{
		glTranslatef(0,-0.8,0);
		bezier(ctrlPts,nCtrlPts,nBezCurvePts);
	}
	glPopMatrix();
	glColor3f(0.7,0.5,0.3);
	glLineWidth(5);
	glBegin(GL_LINES);	
	glVertex2f(20,100);
	glVertex2f(20,40);
	glEnd();
	glFlush();
	glutPostRedisplay();
	glutSwapBuffers();
}
void winReshapeFun(int newWidth,int newHeight)
{
	glViewport(0,0,newWidth,newHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(xwcMin,xwcMax,ywcMin,ywcMax);
	glClear(GL_COLOR_BUFFER_BIT);
}
void menu(int id)
{
	if(id==1)
	{
		flag=1;
	}
	else if(id==2)
	{
		flag=0;
	}
	glutPostRedisplay();
}
int main(int argc,char **argu)
{
	glutInit(&argc,argu);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
	glutInitWindowPosition(50,50);
	glutInitWindowSize(winWidth,winHeight);
	glutCreateWindow("Bezier Curve");
	glutCreateMenu(menu);
	glutAddMenuEntry("Start Animation",1);
	glutAddMenuEntry("Stop Animation",2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutDisplayFunc(displayFcn);
	glutReshapeFunc(winReshapeFun);
	glutMainLoop();
}
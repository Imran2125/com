#include<stdio.h>
#include<stdlib.h>
#include<GL/glut.h>
float x1=200.0, y1=200.0, x2=100, y2=300.0, x3=200, y3=400.0, x4=300.0, y4=300, le[500], re[500];
int fillflag = 0;
void init()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluOrtho2D(0.0, 500.0, 0.0, 500.0);
}
void edgedetect(float x1, float y1, float x2, float y2)
{
	float temp, x, m;
	if ((y2 - y1) < 0)
	{
		temp = y1;
		y1 = y2;
		y2 = temp;
		temp = x1;
		x1 = x2;
		x2 = temp;
	}
	if ((y2 - y1) != 0)
		m = (x2 - x1) / (y2 - y1);
	else
		m = x2 - x1;
	x = x1;
	for (int i = y1; i <= y2; i++)
	{
		if (x < le[i])
			le[i] = x;
		if (x > re[i])
			re[i] = x;
		x += m;
	}
}
void draw_pixel(int x, int y)
{
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}
void scanfill()
{
	int i, y;
	for (i = 0; i < 500; i++)
	{
		le[i] = 500;
		re[i] = 0;
	}
	edgedetect(x1, y1, x2, y2);
	edgedetect(x2, y2, x3, y3);
	edgedetect(x3, y3, x4, y4);
	edgedetect(x4, y4, x1, y1);
	for (y =0 ; y < 500; y++)
	{
		if (le[y] <= re[y])
		{
			for (i = le[y]; i < re[y]; i++)
				draw_pixel(i, y);
		}
	}
}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0,0.0,0.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glVertex2f(x3, y3);
	glVertex2f(x4, y4);
	glEnd();
	if (fillflag == 1)
		scanfill();
	glFlush();
}
void fillmenu(int option)
{
	if (option == 1)
		fillflag = 1;
	if (option == 2)
		fillflag = 2;
	display();
}
void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE| GLUT_RGB);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(500,500);
	glutCreateWindow("Scan Line fill");
	init();
	glutDisplayFunc(display);
	glutCreateMenu(fillmenu);
	glutAddMenuEntry("Fill polygon", 1);
	glutAddMenuEntry("Empty polygon", 2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();
}

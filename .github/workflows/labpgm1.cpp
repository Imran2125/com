#include<stdio.h>
#include<GL/glut.h>
int x1, y1, x2, y2;
void myInit()
{
	glClearColor(0.0,0.0,0.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	gluOrtho2D(0,500,0,500);
}
void draw_pixel(int x, int y)
{
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}
void draw_line(int x1, int x2, int y1, int y2)
{
	int dx, dy, i, pk;
	int incx, incy, inc1, inc2;
	int x, y;
	dx = x2 - x1;
	dy = y2 - y1;
	if (dx < 0)
		dx = -dx;
	if (dy < 0)
		dy = -dy;
	incx = 1;
	if (x2 < x1)
		incx = -1;
	incy = 1;
	if (y2 < y1)
		incy = -1;
	x = x1, y = y1;
	if (dx > dy)
	{
		draw_pixel(x, y);
		pk = 2 * dy - dx;
		inc1 = 2 * (dy - dx);
		inc2 = 2 * dy;
		for (i = 0; i < dx; i++)
		{
			if (pk >= 0)
			{
				y += incy;
				pk += inc1;
			}
			else
			{
				pk += inc2;
				x += incx;
			}
			draw_pixel(x,y);
		}
	}
	else
	{
		draw_pixel(x, y);
		pk = 2 * dx - dy;
		inc1 = 2 * (dx-dy);
		inc2 = 2 * dx;
		for (i = 0; i < dy; i++)
		{
			if (pk >= 0)
			{
				x+= incx;
				pk+= inc1;
			}
			else
			{
				pk += inc2;
				y += incy;
			}
			draw_pixel(x, y);
		}

	}
}
void display()
{
	draw_line(x1, x2, y1, y2);
	glFlush();
}
void main(int argc,char **argv)
{
	printf("Enter the start point of the line (x1,y1)\n");
	scanf_s("%d %d", &x1, &y1);
	printf("Enter the end points of the line (x2,y2)\n");
	scanf_s("%d %d", &x2, &y2);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Bresenham's Line drawing algorithm");
	myInit();
	glutDisplayFunc(display);
	glutMainLoop();
}
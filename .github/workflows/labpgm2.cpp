#include<stdio.h>
#include<GL/glut.h>
int x, y;
int where_to_rotate = 0;
float rotate_angle = 0.0;
float translate_x = 0.0, translate_y = 0.0;
void draw_pixel(float x1, float y1)
{
	glPointSize(10.0);
	glBegin(GL_POINTS);
	glVertex2f(x1, y1);
	glEnd();
}
void triangle(int x, int y)
{
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_TRIANGLES);
	glVertex2f(x, y);
	glVertex2f(x + 400, y + 300);
	glVertex2f(x + 300, y + 10);
	glEnd();
}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glColor3f(0, 0, 0);
	draw_pixel(0, 0);
	if (where_to_rotate == 1)
	{
		translate_x = 0.0;
		translate_y = 0.0;
		rotate_angle += .1;
	}
	if (where_to_rotate == 2)
	{
		translate_x = x;
		translate_y = y;
		rotate_angle += .3;
		glColor3f(1.0, 0.0, 0.0);
		draw_pixel(x, y);
	}
	glTranslatef(translate_x, translate_y, 0.0);
	glRotatef(rotate_angle, 0.0, 0.0, 1.0);
	glTranslatef(-translate_x, -translate_y, 0.0);
	triangle(translate_x, translate_y);
	glutPostRedisplay();
	glutSwapBuffers();
}

void myInit()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-800.0, 800.0, -800.0, 800.0);
	glMatrixMode(GL_MODELVIEW);
}
void rotate_menu(int option)
{
	if (option == 1)
		where_to_rotate = 1;
	if (option == 2)
		where_to_rotate = 2;
	if (option == 3)
		where_to_rotate = 3;
}
void main(int argc, char** argv)
{
	printf("Enter the fixed point for rotation\n");
	scanf_s("%d %d", &x, &y);
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Rotate a triangle");
	myInit();
	glutDisplayFunc(display);
	glutCreateMenu(rotate_menu);
	glutAddMenuEntry("1.Rotate about origin", 1);
	glutAddMenuEntry("2.Rotate about fixed point", 2);
	glutAddMenuEntry("3.Stop Rotation",3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();
}

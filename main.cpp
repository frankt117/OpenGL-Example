//-------------------------------------------------------------------------------
//      File Base: Program #3
//       File ext: cpp
//         Author: Frank Torres
//        Created: 2/16/11
//    Description: Using OpenGL to rotate a Pendulum
//-------------------------------------------------------------------------------

#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <iostream>

using namespace std;

//Global vars of prevaious point positions
static GLfloat spin = -101.0;

enum
{
	POS = 1,
	NEG,
	NUL
};

static void reshape(int w, int h)
{
   if (w <= h) 
   {
      glViewport(0, (GLint) (h-w)/2, (GLsizei) w, (GLsizei) w);
   } 
   else 
   {
      glViewport((GLint) (w-h)/2, 0, (GLsizei) h, (GLsizei) h);
   }

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();

   gluOrtho2D(0.0,1.0,0.0,1.0);
  

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

   return;
}


void display(void)
{
	/* clear all pixels  */
	glClear (GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	glTranslatef(0.5f, 0.5f, 0.0f);
	glRotatef(spin, 0.0, 0.0, 1.0);

	glBegin(GL_POINTS);
		glColor3f (0.0f, 1.0f, 0.0f);
		glVertex3f(0.5f, 0.5f, 0.0f);
	glEnd( );

	glBegin(GL_LINES);
		glColor3f (1.0f, 1.0f, 1.0f);
		glVertex3f(2.5f, 0.5f, 0.0f); // origin of the line
		glVertex3f(0.0f, 0.0f, 0.0f); // ending point of the line
	glEnd( );

	glTranslatef(0.5f, 0.1f, 0.0f);
	GLUquadric* disk = gluNewQuadric ( );
	gluQuadricDrawStyle	(disk, GLU_FILL);
	gluDisk	(disk, 0, 0.1f, 20.0f, 1.0f);


	/* don't wait!  
	* start processing buffered OpenGL routines 
	*/
	glFlush ();
	glPopMatrix();
	glutSwapBuffers();
}

void init (void) 
{
/* select clearing color 	*/
   glClearColor (0.0, 0.0, 0.0, 0.0);

/* initialize viewing values  */
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}

void movePendulumPos(void)
{
	spin = spin + 1;
	glutPostRedisplay();
}


void movePendulumNeg(void)
{
	spin = spin - 1;
	glutPostRedisplay();
}


void processKeys(unsigned char key, int x, int y) {

	if (key == 27) 
		exit(0);
	if (key == 43)
		glutIdleFunc(movePendulumPos);
	if (key == 45)
		glutIdleFunc(movePendulumNeg);
}

void processMenuEvents(int option) {

	switch (option) {
		case POS : 
			glutIdleFunc(movePendulumNeg);
			break;
		case NEG : 
			glutIdleFunc(movePendulumPos);
			break;
		case NUL : 
			glutIdleFunc(NULL);
			break;
	}
}


void createMenu() {

	int menu;
	menu = glutCreateMenu(processMenuEvents);
	glutAddMenuEntry("Clockwise",POS);
	glutAddMenuEntry("Counterclockwise",NEG);
	glutAddMenuEntry("Stop",NUL);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize (250, 250); 
	glutInitWindowPosition (200, 200);
	glutCreateWindow ("Program #3");
	init ();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(processKeys);
	createMenu();
	glutMainLoop();
	return 0;   /* ANSI C requires main to return int. */
}


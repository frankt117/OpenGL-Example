//-------------------------------------------------------------------------------
//      File Base: Program #4
//       File ext: cpp
//         Author: Frank Torres
//        Created: 2/16/11
//    Description: Using OpenGL to make a robot arm
//-------------------------------------------------------------------------------

#include <GL/glut.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

static int shoulder = 0, elbow = 0, wrist = 0;
bool wireORsolid = false;
bool viewType = false;
int currentSizeW = 350;
int currentSizeH = 350;
static int xRot = 0, yRot = 0;

void init(void) 
{
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_FLAT);
}

void display(void)
{
   //cout << wireORsolid << endl;
   if(wireORsolid == false)
   {
		glClear (GL_COLOR_BUFFER_BIT);
   }
   else
   {
		glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   }
	
   glPushMatrix();
   glTranslatef (2.0, 0.0, 0.0);

   glPushMatrix();
   glTranslatef (-2.0, 0.0, 0.0);
   glRotatef ((GLfloat) shoulder, 0.0, 0.0, 1.0);
   glTranslatef (2.0, 0.0, 0.0);
   glPushMatrix();
   glScalef (5.0, 1.0, 1.0);

   if(wireORsolid == false)
   {
		glutWireCube (1.0);
   }
   else
   {
	   glColor3d(1.0,0.0,0.0);
	   glutSolidCube (1.0);
   }

   glPopMatrix();

 
   glTranslatef (2.2, 0.0, 0.0);
   glRotatef ((GLfloat) elbow, 0.0, 0.0, 1.0);
   glTranslatef (2.2, 0.0, 0.0);
   glPushMatrix();
   glScalef (4.0, 1.0, 1.0);
   if(wireORsolid == false)
   {
		glutWireCube (1.0);
   }
   else
   {
	   glColor3d(0.0,1.0,0.0);
	   glutSolidCube (1.0);
   }
   glPopMatrix();
  

   glTranslatef (1.8, 0.0, 0.0);
   glRotatef ((GLfloat) wrist, 0.0, 0.0, 1.0);
   glTranslatef (1.8, 0.0, 0.0);
   glPushMatrix();
   glScalef (3.0, 1.0, 1.0);
   if(wireORsolid == false)
   {
		glutWireCube (1.0);
   }
   else
   {
	   glColor3d(0.0,0.0,1.0);
	   glutSolidCube (1.0);
   }
   glPopMatrix();

   glPopMatrix();
   glPopMatrix();
   glutSwapBuffers();


   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef (0.0, 0.0, -15.0);
   glRotatef ((GLfloat) xRot,1.0, 0.0, 0.0);
   glRotatef ((GLfloat) yRot,0.0, 1.0, 0.0);
}

void reshape (int w, int h)
{
	currentSizeW = w;
	currentSizeH = h;
	glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   if(viewType == false)
   {
		gluPerspective(65.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
   }
   else
   {
		glOrtho(-500.0, (GLfloat) currentSizeW, -500.0,(GLfloat) currentSizeH, 6.0, 20.0);
   }
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef (0.0, 0.0, -15.0);
   glRotatef ((GLfloat) xRot,1.0, 0.0, 0.0);
   glRotatef ((GLfloat) yRot,0.0, 1.0, 0.0);
}

void keyboard (unsigned char key, int x, int y)
{
   switch (key) {
      case 's':
         shoulder = (shoulder + 5) % 360;
         glutPostRedisplay();
         break;
      case 'S':
         shoulder = (shoulder - 5) % 360;
         glutPostRedisplay();
         break;
      case 'e':
         elbow = (elbow + 5) % 360;
         glutPostRedisplay();
         break;
      case 'E':
         elbow = (elbow - 5) % 360;
         glutPostRedisplay();
         break;
	  case 'w':
         wrist = (wrist + 5) % 360;
         glutPostRedisplay();
         break;
      case 'W':
         wrist = (wrist - 5) % 360;
         glutPostRedisplay();
         break;
	case 'x':
         xRot = (xRot + 1) % 360;
         glutPostRedisplay();
         break;
      case 'X':
         xRot = (xRot - 1) % 360;
         glutPostRedisplay();
         break;
	case 'y':
         yRot = (yRot + 1) % 360;
         glutPostRedisplay();
         break;
    case 'Y':
         yRot = (yRot - 1) % 360;
         glutPostRedisplay();
         break;
	  case 'h':
      if(wireORsolid == false)
      {
         glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
         wireORsolid = true;
      }
      else
      {
         glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
         wireORsolid = false;
      }
		
		glutPostRedisplay();
		break;
	  case 'p':
		   glMatrixMode (GL_PROJECTION);
         glLoadIdentity ();
        if(viewType == false)
		   {
			   glOrtho(-500.0, (GLfloat) currentSizeW, -500.0, currentSizeH, 5.0, 200.0);
            viewType = true;
		   }
		   else
		   {
            gluPerspective(65.0, (GLfloat) currentSizeW/(GLfloat) currentSizeH, 1.0, 20.0);
			   viewType = false;
		   }
		   
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslatef (0.0, 0.0, -15.0);
        glRotatef ((GLfloat) xRot,1.0, 0.0, 0.0);
        glRotatef ((GLfloat) yRot,0.0, 1.0, 0.0);
         glutPostRedisplay();
		   break;
      case 27:
         exit(0);
         break;
      default:
         break;
   }
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize (500, 500); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow (argv[0]);
   init ();
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0;
}


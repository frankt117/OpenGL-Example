#include <GL/glut.h>
#include <math.h>


using namespace std;

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

   float x,y,h;
   int i, j, k, m, indt, I1, I2, I3;
   k = 3;
   //verts
	float v[16][3];
   //triangles
	int ltri[18][3];
   //vertex normals
	float vn[16][3];
   //triangle normals
	float tn[3];
	

	//Store Vertices
	h = 1.0f/(float)k;
	m = 0;

	for (j = 0; j <= k; j++)
	{
		y = (float)j*h;
      //cout << y << endl;

		for(i = 0; i <= k; i++)
		{
			
			x = (float)i*h;
         //int M = (int)m;
			v[m][0] = x;
			v[m][1] = y;
			v[m][2] = 0.5f * exp(-0.04f * sqrt(pow((80.0f * x) - 40.0f,2.0f) + pow((90.0f * y) - 45.0f, 2.0f))) * 
			cos(0.15f * sqrt(pow((80.0f * x) - 40.0f, 2.0f) + pow((90.0f * y) - 45.0f, 2.0f)));
			 m++;
		}
	}	


	//Store Triangle
	indt = 0;

	for (j = 1; j <= k; j++)
	{
		y = (float)j*h;
      //indt = 0;
		for(i = 1; i <= k; i++) 
		{

         m = j*(k+1) + i; 
         ltri[indt][0] = m-k-2;
			ltri[indt][1] = m-k-1;
			ltri[indt][2] = m;
			ltri[indt+1][0] = m-k-2;
			ltri[indt+1][1] = m;
			ltri[indt+1][2] = m-1;

         

			indt = indt + 2;
		}
	}

   

	//Initialize normals
	for (m = 0; m <= (((k+1)*(k+1))-1); m++) 
	{
		//int M = (int)m;
		vn[m][0] = 0;
		vn[m][1] = 0;
		vn[m][2] = 0;
	}


	//Add triangle normals to vertex normals
	for (indt = 0; indt <= (2*(k*k))-1; indt++)
	{ 
      I1 = ltri[indt][0];
		I2 = ltri[indt][1];
		I3 = ltri[indt][2];


		tn[0] = (v[I1][1]-v[I1][1])*(v[I3][2]-v[I1][2])-
			(v[I2][2]-v[I1][2])*(v[I3][1]-v[I1][1]);
		tn[1] = (v[I2][2]-v[I1][2])*(v[I3][0]-v[I1][0])-
			(v[I2][0]-v[I1][0])*(v[I3][2]-v[I1][2]);
		tn[2] = (v[I2][0]-v[I1][0])*(v[I3][1]-v[I1][1])-
			(v[I2][1]-v[I1][1])*(v[I3][0]-v[I1][0]);
		
      //Normalize
      float norm = sqrt((tn[0] * tn[0]) + (tn[1] * tn[1]) + (tn[2] * tn[2]));
      tn[0] /= norm;
      tn[1] /= norm;
      tn[2] /= norm;

		vn[I1][0] += tn[0], vn[I1][1] += tn[1], vn[I1][2] += tn[2];
		vn[I2][0] += tn[0], vn[I2][1] += tn[1], vn[I2][2] += tn[2];
		vn[I3][0] += tn[0], vn[I3][1] += tn[1], vn[I3][2] += tn[2];

      //cout << vn[(int)i3][0] << endl;
	}

	//Normalize vertex normals
	for (m = 0; m <= (((k+1)*(k+1))-1); m++)	
	{
		//int M = (int)m;
      float norm = sqrt((vn[m][0] * vn[m][0]) + (vn[m][1] * vn[m][1]) + (vn[m][2] * vn[m][2]));
      vn[m][0] /= norm;
      //cout << "VN: " << vn[m][0] << endl;
      vn[m][1] /= norm;
      //cout << "VN: " << vn[m][1] << endl;
      vn[m][2] /= norm;
      //cout << "VN: " << vn[m][2] << endl;
	}
	
	for (indt = 0; indt <= (2*(k*k))-1; indt++)
	{ 
      I1 = ltri[indt][0];
		I2 = ltri[indt][1];
		I3 = ltri[indt][2];

      //Draw Triangles
      glColor3f(0.0f,0.0f,1.0f);
      glBegin(GL_TRIANGLE_STRIP);
      glVertex3f(v[I1][0],v[I1][1],v[I1][2]);
      glVertex3f(v[I2][0],v[I2][1],v[I2][2]);
      glVertex3f(v[I3][0],v[I3][1],v[I3][2]);
      glEnd();
   }

   glFlush ();
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


int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize (250, 250); 
   glutInitWindowPosition (200, 200);
   glutCreateWindow ("hello");
   init ();
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutMainLoop();
   return 0;   /* ANSI C requires main to return int. */
}

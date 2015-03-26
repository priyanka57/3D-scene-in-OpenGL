#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

int axes=0;       
int th=0;         
int ph=0;         
int fov=55;       
double asp=1;     
double dim=5.0;   
double zh=0; 

#define Cos(x) (cos((x)*3.1415927/180))
#define Sin(x) (sin((x)*3.1415927/180))


void initGL() {
glClearColor(0.0f, 1.0f, 1.0f,1.0f);
glClearDepth(1.0f);
}

#define LEN 8192  
void Print(const char* format , ...)
{
   char    buf[LEN];
   char*   ch=buf;
   va_list args;
   va_start(args,format);
   vsnprintf(buf,LEN,format,args);
   va_end(args);
   while (*ch)
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,*ch++);
}

static void Project()
{
   //  Tell OpenGL we want to manipulate the projection matrix
   glMatrixMode(GL_PROJECTION);
   //  Undo previous transformations
   glLoadIdentity();
   //  Perspective transformation
      gluPerspective(fov,asp,dim/4,4*dim);
   glMatrixMode(GL_MODELVIEW);
   //  Undo previous transformations
   glLoadIdentity();
}

static void pyramid(double x,double y,double z,
                 double dx,double dy,double dz)
{
glLoadIdentity();
	glPushMatrix();
	glTranslated(x,y,z);
	glRotated(th,0,1,0);
	glRotatef(ph,1,0,0);
	glScaled(dx,dy,dz);
   	glBegin(GL_TRIANGLES);
	//front
	glColor3f(0.5f, 0.35f, 0.05f);	
	glVertex3f(0.0f, 1.0f, 0.0f);
  	glColor3f(0.0f, 0.35f, 0.0f);	
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glColor3f(0.5f, 0.35f, 0.05f);	
	glVertex3f(1.0f, -1.0f, 1.0f);
	//Right
	glColor3f(0.5f, 0.35f, 0.05f);	
	glVertex3f(0.0f, 1.0f, 0.0f);
  	glColor3f(0.0f, 0.35f, 0.0f);	
	glVertex3f(1.0f, -1.0f, 1.0f);
	glColor3f(0.5f, 0.35f, 0.05f);	
	glVertex3f(1.0f, -1.0f, -1.0f);
	//Back
	glColor3f(0.5f, 0.35f, 0.05f);	
	glVertex3f(0.0f, 1.0f, 0.0f);
  	glColor3f(0.0f, 0.35f, 0.0f);	
	glVertex3f(1.0f, -1.0f, -1.0f);
	glColor3f(0.5f, 0.35f, 0.05f);	
	glVertex3f(-1.0f, -1.0f, -1.0f);
	//Left
	glColor3f(0.5f, 0.35f, 0.05f);	
	glVertex3f(0.0f, 1.0f, 0.0f);
  	glColor3f(0.0f, 0.35f, 0.0f);	
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glColor3f(0.5f, 0.35f, 0.05f);	
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glEnd();	
	glPopMatrix();	
	
}




 static void PolyPlane(int type, double x,double y,double z)
{
	
	glLoadIdentity();
   //  Save transformation
   glPushMatrix();
	glTranslated(x,y,z);
	glTranslatef(2.0f, 3.0f,-10.0f);
	glRotatef(th,0,1,0);
	glRotatef(ph,1,0,0);
	glScalef(1,1,1);
   	
   //  Fuselage and wings
   glColor3f(0,0,1); 
   glBegin(type);
   glVertex2f( 1.0, 0.0);
   glVertex2f( 0.8, 0.1);
   glVertex2f( 0.0, 0.1);
   glVertex2f(-1.0, 0.5);
   glVertex2f(-1.0,-0.5);
   glVertex2f( 0.0,-0.1);
   glVertex2f( 0.8,-0.1);
   glEnd();
   //  Vertical tail
   glColor3f(1,0,0);
   glBegin(type);
   glVertex3f(-1.0, 0.0,0.0);
   glVertex3f(-1.0, 0.0,0.5);
   glVertex3f(-0.5, 0.0,0.0);
   glEnd();
   //  Undo transformations
   glPopMatrix();
}


static void FlatPlane(double x,double y,double z)
{
glLoadIdentity();
	glPushMatrix();
	glTranslatef(-4.0f, -2.35f,-10.0f);
	glRotatef(th,0,1,0);
	glRotatef(ph,1,0,0);
	glScalef(1,1,1);
   glTranslated(x,y,z);
	
    glColor3f(0,0,0);
   glBegin(GL_POLYGON);
   glVertex3f( 10.0, 0.3, 0);
   glVertex3f( 10.0, 0.3, 0);
   glVertex3f(-10.0, 0.3, 0);
   glVertex3f(-10.0,-0.3, 0);
   glVertex3f( 10,-0.3,0);
   glEnd();
glPopMatrix();	
}


void display()
{  
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);	
	glLoadIdentity();

	glRotatef(th,0,1,0);
	glRotatef(ph,1,0,0);

	pyramid(-3.0, -1.0,-10.0 , 0.9,0.9,0.9);
         pyramid(-2.9, -1.5, -13.0 , 0.8,0.8,0.8);
         pyramid(-2.8, -2.0,-16.0, 0.7, 0.7, 0.7);
	PolyPlane(GL_POLYGON , 0,0,0);
	FlatPlane( 0.0, 0.0, 0.0);
         
	glWindowPos2i(5,5);
   Print("Angle=%d,%d  Dim=%.1f FOV=%d ",th,ph,dim,fov);

	double Ex = -2*dim*Sin(th)*Cos(ph);
      double Ey = +2*dim        *Sin(ph);
      double Ez = +2*dim*Cos(th)*Cos(ph);
      gluLookAt(Ex,Ey,Ez , 0,0,0 , 0,Cos(ph),0);
	glFlush();
	glutSwapBuffers();	//swap front and back buffers
}



void special(int key,int x,int y)
{
   //  Right arrow key - increase angle by 5 degrees
   if (key == GLUT_KEY_RIGHT)
      th += 5;
   //  Left arrow key - decrease angle by 5 degrees
   else if (key == GLUT_KEY_LEFT)
      th -= 5;
   //  Up arrow key - increase elevation by 5 degrees
   else if (key == GLUT_KEY_UP)
      ph += 5;
   //  Down arrow key - decrease elevation by 5 degrees
   else if (key == GLUT_KEY_DOWN)
      ph -= 5;
   //  PageUp key - increase dim
   else if (key == GLUT_KEY_PAGE_UP)
      dim += 0.1;
   //  PageDown key - decrease dim
   else if (key == GLUT_KEY_PAGE_DOWN && dim>1)
      dim -= 0.1;
   //  Keep angles to +/-360 degrees
   th %= 360;
   ph %= 360;
   //  Update projection
   Project();
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

void key(unsigned char ch,int x,int y)
{
   //  Exit on ESC
   if (ch == 27)
      exit(0);
   //  Reset view angle
   else if (ch == '0')
      th = ph = 0;
         //  Change field of view angle
   else if (ch == '-' && ch>1)
      fov--;
   else if (ch == '+' && ch<179)
      fov++;
   //  Reproject
   Project();
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

void reshape(int width,int height)
{
   //  Ratio of the width to the height of the window
   asp = (height>0) ? (double)width/height : 1;
   //  Set the viewport to the entire window
   glViewport(0,0, width,height);
   //  Set projection
   Project();
}


int main(int argc,char* argv[])
{
   //  Initialize GLUT and process user parameters
   glutInit(&argc,argv);
	
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
   glutInitWindowSize(600,600);
	glutInitWindowPosition(50, 50);
      //  Create the window
   glutCreateWindow("3D scene");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutSpecialFunc(special);
   	glutKeyboardFunc(key);
	initGL();
      glutMainLoop();
   return 0;
}

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <windows.h>
#include <wingdi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define PI_ 3.14159265358979323846
double central[2] = {1.9,0};
double theta = PI_/2;
double wheel_theta = 0;
double direction[2] = {0.05*cos(theta),0.05*sin(theta)};
double wheel_direction[2] = {0.05*cos(theta+wheel_theta),0.05*sin(theta+wheel_theta)};
int speed = 100;
#define r (0.1)
GLuint LoadTexture( const char * filename )
{

  GLuint texture;

  int width, height;

  unsigned char * data;

  FILE * file;

  file = fopen( filename, "rb" );

  if ( file == NULL ) return 0;
  width = 1024;
  height = 512;
  data = (unsigned char *)malloc( width * height * 3 );
  //int size = fseek(file,);
  fread( data, width * height * 3, 1, file );
  fclose( file );

 for(int i = 0; i < width * height ; ++i)
{
   int index = i*3;
   unsigned char B,R;
   B = data[index];
   R = data[index+2];

   data[index] = R;
   data[index+2] = B;

}


glGenTextures( 1, &texture );
glBindTexture( GL_TEXTURE_2D, texture );
glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_MODULATE );
glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST );


glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR );
glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_REPEAT );
glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_REPEAT );
gluBuild2DMipmaps( GL_TEXTURE_2D, 3, width, height,GL_RGB, GL_UNSIGNED_BYTE, data );
free( data );

return texture;
}
void Keyboard(unsigned char key, int x, int y)
{
    switch (key)
   {
   case 'w':
      {
          speed = speed - 3;
      }
      break;
   case 'd':
      {
          wheel_theta += 0.05;
      }
      break;
   case 'a':
      {
          wheel_theta -= 0.05;
      }
      break;
   case 's':
     {
          speed = speed + 3;
     }
      break;
   }

    glutPostRedisplay();
}
void mydisplay(){
    Sleep(speed);
    central[0] += 0.1*direction[0];
    central[1] += 0.1*direction[1];
    theta += 0.05*wheel_theta;
    direction[0] = 0.05*cos(theta);
    direction[1] = 0.05*sin(theta);
    wheel_direction[0] = 0.05*cos(theta+wheel_theta);
    wheel_direction[1] = 0.05*sin(theta+wheel_theta);
     glClear(GL_COLOR_BUFFER_BIT);
	double u,v;
	double x1 = direction[0];
	double y1 = direction[1];
	double x2 = -direction[1];
	double y2 = direction[0];
	glBegin(GL_QUAD_STRIP);
	glColor3f(1.0, 1.0, 1.0);
	for(u=-PI_/2;u<PI_/2+0.05;u=u+0.1)
	{
		for(v=0.8;v>=0.6;v=v-0.2)
		{
			glVertex3f(1.2+v*cos(u),v*sin(u),0);
		}
		for(v=0.8;v>=0.6;v=v-0.2)
		{
			glVertex3f(1.2+v*cos(u+0.05),v*sin(u+0.05),0);
		}
	}
	for(u=PI_/2+0.05;u<3*PI_/2+0.05;u=u+0.1)
	{
		for(v=0.8;v>=0.6;v=v-0.2)
		{
			glVertex3f(-1.2+v*cos(u),v*sin(u),0);
		}
		for(v=0.8;v>=0.6;v=v-0.2)
		{
			glVertex3f(-1.2+v*cos(u+0.05),v*sin(u+0.05),0);
		}
	}
	glEnd();
    glBegin(GL_QUADS);
    glVertex3f(1.2,0.8,0);
    glVertex3f(1.2,0.6,0);
    glVertex3f(-1.2,0.6,0);
    glVertex3f(-1.2,0.8,0);
    glVertex3f(1.2,-0.8,0);
    glVertex3f(1.2,-0.6,0);
    glVertex3f(-1.2,-0.6,0);
    glVertex3f(-1.2,-0.8,0);
    glColor3f(0.0, 1.0, 1.0);
    glVertex3f(central[0]-x1-x2,central[1]-y1-y2,0.15);
    glVertex3f(central[0]-x1+x2,central[1]-y1+y2,0.15);
    glVertex3f(central[0]+x1+x2,central[1]+y1+y2,0.15);
    glVertex3f(central[0]+x1-x2,central[1]+y1-y2,0.15);
    glVertex3f(central[0]-x1-x2,central[1]-y1-y2,0.05);
    glVertex3f(central[0]-x1+x2,central[1]-y1+y2,0.05);
    glVertex3f(central[0]+x1+x2,central[1]+y1+y2,0.05);
    glVertex3f(central[0]+x1-x2,central[1]+y1-y2,0.05);
    glVertex3f(central[0]+x1+x2,central[1]+y1+y2,0.05);
    glVertex3f(central[0]+x1-x2,central[1]+y1-y2,0.05);
    glVertex3f(central[0]+x1-x2,central[1]+y1-y2,0.15);
    glVertex3f(central[0]+x1+x2,central[1]+y1+y2,0.15);
    glVertex3f(central[0]+x1-x2,central[1]+y1-y2,0.05);
    glVertex3f(central[0]-x1-x2,central[1]-y1-y2,0.05);
    glVertex3f(central[0]-x1-x2,central[1]-y1-y2,0.15);
    glVertex3f(central[0]+x1-x2,central[1]+y1-y2,0.15);
    glVertex3f(central[0]+x1+x2,central[1]+y1+y2,0.05);
    glVertex3f(central[0]-x1+x2,central[1]-y1+y2,0.05);
    glVertex3f(central[0]-x1+x2,central[1]-y1+y2,0.15);
    glVertex3f(central[0]+x1+x2,central[1]+y1+y2,0.15);
    glVertex3f(central[0]-x1-x2,central[1]-y1-y2,0.05);
    glVertex3f(central[0]-x1+x2,central[1]-y1+y2,0.05);
    glVertex3f(central[0]-x1+x2,central[1]-y1+y2,0.15);
    glVertex3f(central[0]-x1-x2,central[1]-y1-y2,0.15);
	glEnd();
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(central[0]+x1+x2,central[1]+y1+y2,0.05);
	for(u=0;u<2*PI_+0.1;u=u+0.1)
	{
        glVertex3f(central[0]+x1+x2+cos(u)*wheel_direction[0],central[1]+y1+y2+cos(u)*wheel_direction[1],0.05+0.05*sin(u));
	}
	glEnd();
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(central[0]+x1+1.3*x2,central[1]+y1+1.3*y2,0.05);
	for(u=0;u<2*PI_+0.1;u=u+0.1)
	{
        glVertex3f(central[0]+x1+1.3*x2+cos(u)*wheel_direction[0],central[1]+y1+1.3*y2+cos(u)*wheel_direction[1],0.05+0.05*sin(u));
	}
	glEnd();
	glBegin(GL_QUAD_STRIP);
	for(u=0;u<2*PI_+0.1;u=u+0.1)
	{
	    glVertex3f(central[0]+x1+x2+cos(u)*wheel_direction[0],central[1]+y1+y2+cos(u)*wheel_direction[1],0.05+0.05*sin(u));
        glVertex3f(central[0]+x1+1.3*x2+cos(u)*wheel_direction[0],central[1]+y1+1.3*y2+cos(u)*wheel_direction[1],0.05+0.05*sin(u));
	}
	glEnd();
    glBegin(GL_TRIANGLE_FAN);
	glVertex3f(central[0]+x1-x2,central[1]+y1-y2,0.05);
	for(u=0;u<2*PI_+0.1;u=u+0.1)
	{
        glVertex3f(central[0]+x1-x2+cos(u)*wheel_direction[0],central[1]+y1-y2+cos(u)*wheel_direction[1],0.05+0.05*sin(u));
	}
	glEnd();
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(central[0]+x1-1.1*x2,central[1]+y1-1.1*y2,0.05);
	for(u=0;u<2*PI_+0.1;u=u+0.1)
	{
        glVertex3f(central[0]+x1-1.3*x2+cos(u)*wheel_direction[0],central[1]+y1-1.3*y2+cos(u)*wheel_direction[1],0.05+0.05*sin(u));
	}
	glEnd();
	glBegin(GL_QUAD_STRIP);
	for(u=0;u<2*PI_+0.1;u=u+0.1)
	{
	    glVertex3f(central[0]+x1-x2+cos(u)*wheel_direction[0],central[1]+y1-y2+cos(u)*wheel_direction[1],0.05+0.05*sin(u));
        glVertex3f(central[0]+x1-1.3*x2+cos(u)*wheel_direction[0],central[1]+y1-1.3*y2+cos(u)*wheel_direction[1],0.05+0.05*sin(u));
	}
	glEnd();
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(central[0]-x1+x2,central[1]-y1+y2,0.05);
	for(u=0;u<2*PI_+0.1;u=u+0.1)
	{
        glVertex3f(central[0]-x1+x2+cos(u)*direction[0],central[1]-y1+y2+cos(u)*direction[1],0.05+0.05*sin(u));
	}
	glEnd();
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(central[0]-x1+1.3*x2,central[1]-y1+1.3*y2,0.05);
	for(u=0;u<2*PI_+0.1;u=u+0.1)
	{
        glVertex3f(central[0]-x1+1.3*x2+cos(u)*direction[0],central[1]-y1+1.3*y2+cos(u)*direction[1],0.05+0.05*sin(u));
	}
	glEnd();
	glBegin(GL_QUAD_STRIP);
	for(u=0;u<2*PI_+0.1;u=u+0.1)
	{
	    glVertex3f(central[0]-x1+x2+cos(u)*direction[0],central[1]-y1+y2+cos(u)*direction[1],0.05+0.05*sin(u));
        glVertex3f(central[0]-x1+1.3*x2+cos(u)*direction[0],central[1]-y1+1.3*y2+cos(u)*direction[1],0.05+0.05*sin(u));
	}
	glEnd();
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(central[0]-x1-x2,central[1]-y1-y2,0.05);
	for(u=0;u<2*PI_+0.1;u=u+0.1)
	{
        glVertex3f(central[0]-x1-x2+cos(u)*direction[0],central[1]-y1-y2+cos(u)*direction[1],0.05+0.05*sin(u));
	}
	glEnd();
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(central[0]-x1-1.3*x2,central[1]-y1-1.3*y2,0.05);
	for(u=0;u<2*PI_+0.1;u=u+0.1)
	{
        glVertex3f(central[0]-x1-1.3*x2+cos(u)*direction[0],central[1]-y1-1.3*y2+cos(u)*direction[1],0.05+0.05*sin(u));
	}
	glEnd();
	glBegin(GL_QUAD_STRIP);
	for(u=0;u<2*PI_+0.1;u=u+0.1)
	{
	    glVertex3f(central[0]-x1-x2+cos(u)*direction[0],central[1]-y1-y2+cos(u)*direction[1],0.05+0.05*sin(u));
        glVertex3f(central[0]-x1-1.3*x2+cos(u)*direction[0],central[1]-y1-1.3*y2+cos(u)*direction[1],0.05+0.05*sin(u));
	}
	glEnd();
	glutSwapBuffers();
	glFlush();
}
void init()
{
	glClearColor (0.0, 0.0, 0.0, 1.0);

	glColor3f(0.0, 1.0, 1.0);

	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluLookAt(0, 0, 0, 0, 1, 1, 0, 1, -1);
	glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);
}
int main(int argc, char** argv){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(800,800);
	glutInitWindowPosition(0,0);
	glutCreateWindow("race");
    GLuint texture;
    texture= LoadTexture( "road.bmp" );
    glBindTexture (GL_TEXTURE_2D, texture);
	glutKeyboardFunc(Keyboard);
	glutDisplayFunc(mydisplay);
	glutIdleFunc(mydisplay);
	init();

	glutMainLoop();
}

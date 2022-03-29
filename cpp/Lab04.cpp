/***C/C++  http://bbs.csdn.net/topics/100091584***/
#include <stdio.h> 
#include <stdlib.h>
#include <math.h>
#include <iostream>
/***freeglut***/
#include ".\GL\freeglut.h"
#define PI 3.1415926
#define YSpace 400
 
void ChangeSize(int , int );					 
void RenderScene(void);		
void SetupRC();
void myKeyboard(unsigned char, int, int);
void mymouse(GLint, GLint, GLint, GLint);
void RotateMatrix(float, GLfloat, GLfloat, GLfloat);
int px = 1, py = 1;
float tx = 0, ty = 0, tz = 0 ;
float theta = 0;
int thetaX = 0, thetaY = 0, thetaZ = 0;
float big = 1.0 , small = 1.0;

GLfloat multiMatrix[] = { 1.0,0.0,0.0,0.0,
						0.0,1.0,0.0,0.0,
						0.0,0.0,1.0,0.0,
						0.0,0.0,0.0,1.0 };

int main(int argc, char** argv) 
{ 
   glutInit(&argc, argv); 
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  
   glutInitWindowSize(400,400);				 
   glutInitWindowPosition(600,80);            
   glutCreateWindow("Moving Cube"); 
   SetupRC();    
     
   glutMouseFunc(mymouse);
   glutReshapeFunc(ChangeSize); 
   glutDisplayFunc(RenderScene); 
   glutKeyboardFunc(myKeyboard);  
   glutMainLoop();	
   return 0; 
} 

void SetupRC(){
	GLfloat whiteLight[] = { 0.45f,0.45f,0.45f,1.0f };
	GLfloat sourceLight[] = { 0.25f,0.25f,0.25f,1.0f };
	GLfloat lightPos[] = { 0.f,25.0f,20.0f,0.0f };

	//Enable lighting
	glEnable(GL_LIGHTING);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,whiteLight);
	glLightfv(GL_LIGHT0,GL_AMBIENT,sourceLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, sourceLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glEnable(GL_LIGHT0);

	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_DEPTH_TEST);
}

void menuSelect(int option)
{
	switch(option)
	{
	case 0:
		glShadeModel(GL_FLAT);
		glutPostRedisplay();
		break;
	case 1:
		glShadeModel(GL_SMOOTH);
		glutPostRedisplay();
		break;
	default:
		break;
	}
}

void buildPopupMenu()
{
	int menu_id;
	menu_id = glutCreateMenu(menuSelect);
    glutAddMenuEntry("Flat",0);
    glutAddMenuEntry("Smooth",1);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

}

void ChangeSize(int w, int h) 
{ 	
   glViewport(0, 0, w, h);             
   glMatrixMode(GL_PROJECTION); 
   glLoadIdentity(); 
   glOrtho(-10,10,-10,10,-10,20);       
   glMatrixMode(GL_MODELVIEW); 
   glLoadIdentity(); 
} 
void RenderScene(void) 
{ 
   glClearColor(1.0, 1.0, 1.0, 1.0);  
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
   glMatrixMode(GL_MODELVIEW); 
   glLoadIdentity(); 
   gluLookAt(0.0f,0.0f,10.0f,0,0,0,0,1,0);
   
   //draw X-axis, Y-axis , Z-axis
   glColor3f(1.0f, 0.0f, 0.0f);
   glBegin(GL_LINES);
   glVertex3f(-100, 0, 0);
   glVertex3f(100, 0, 0);
   glVertex3f(0, -100, 0);
   glVertex3f(0, 100, 0);
   glVertex3f(0, 0, -100);
   glVertex3f(0, 0, 100);
   glVertex3f(px , py ,0);
   glVertex3f(0, 0, 0);
   glEnd();

   glColor3f(1.0f, 0.0f, 0.0f);
   glPointSize(6);
   glBegin(GL_POINTS);
   glVertex3f(px, py, 0);
   glEnd();  
   
   RotateMatrix(theta, px, py, 0); 

   glColor3f(1, 1, 0);
   glutSolidCube(6);
   glutSwapBuffers(); 
}

void myKeyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'r':
		theta = 0;		
		break;
    // e:繞軸旋轉
	case 'e':
		theta += 3;		
		std::cout << "旋轉角度: " << theta << "\n";
		break;
	case 'q':
		theta -= 3;
		std::cout << "旋轉角度: " << theta << "\n";
		break;
	}
	glutPostRedisplay();
}


void mymouse(GLint button, GLint state, GLint x, GLint y) {

	switch (button)
	{
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_UP) {
			std::cout << "x座標: " << x << "\n";
			std::cout << "y座標: " << YSpace - y << "\n";		
			px = (x-200)/20;
			py = (YSpace - y - 200) / 20;
		}
	default:
		break;
	}
	
}

void RotateMatrix(float angle, GLfloat X, GLfloat Y , GLfloat Z) {
	GLfloat Cos = cos(angle * PI / 180);
	GLfloat Sin = sin(angle * PI / 180);

	double magnitude = sqrt(X * X + Y * Y + Z * Z);
	if (magnitude == 0) throw "ERROR";
	X /= magnitude;
	Y /= magnitude;
	Z /= magnitude;

	multiMatrix[0] = Cos + (1 - Cos) * X * X;
	multiMatrix[1] = Sin*Z + (1 - Cos) * Y * X;
	multiMatrix[2] = - Sin * Y + (1 - Cos) * Z * X;
	multiMatrix[4] = -  Sin * Z + (1 - Cos) * X * Y;
	multiMatrix[5] = Cos + (1 - Cos) * Y * Y;
	multiMatrix[6] = Sin * X + (1 - Cos) * Z * Y;
	multiMatrix[8] = Sin * Y + (1 - Cos) * X * Z;
	multiMatrix[9] = - Sin * X + (1 - Cos) * Y * Z;
	multiMatrix[10] = Cos + (1 - Cos) * Z * Z;
	glMultMatrixf(multiMatrix);
}




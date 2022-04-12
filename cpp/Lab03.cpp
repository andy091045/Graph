/***C/C++  http://bbs.csdn.net/topics/100091584***/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/***freeglut***/
#include ".\GL\freeglut.h"
#define PI 3.1415926

//作業三:旋轉位移方塊(不能用glut API)

void ChangeSize(int, int);
void RenderScene(void);
void SetupRC();
void myKeyboard(unsigned char, int, int);
void mySpecialKey(int, int, int);
float tx = 0, ty = 0, tz = 0;
int thetaX = 0, thetaY = 0, thetaZ = 0;
float big = 1.0, small = 1.0;

GLfloat rotMatrixX[] = {1.0, 0.0, 0.0, 0.0,
                        0.0, 1.0, 0.0, 0.0,
                        0.0, 0.0, 1.0, 0.0,
                        0.0, 0.0, 0.0, 1.0};
GLfloat rotMatrixY[] = {1.0, 0.0, 0.0, 0.0,
                        0.0, 1.0, 0.0, 0.0,
                        0.0, 0.0, 1.0, 0.0,
                        0.0, 0.0, 0.0, 1.0};
GLfloat rotMatrixZ[] = {1.0, 0.0, 0.0, 0.0,
                        0.0, 1.0, 0.0, 0.0,
                        0.0, 0.0, 1.0, 0.0,
                        0.0, 0.0, 0.0, 1.0};

GLfloat translateMatrix[] = {1.0, 0.0, 0.0, 0.0,
                             0.0, 1.0, 0.0, 0.0,
                             0.0, 0.0, 1.0, 0.0,
                             0.0, 0.0, 0.0, 1.0};

GLfloat scaleMatrix[] = {1.0, 0.0, 0.0, 0.0,
                         0.0, 1.0, 0.0, 0.0,
                         0.0, 0.0, 1.0, 0.0,
                         0.0, 0.0, 0.0, 1.0};

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(600, 80);
    glutCreateWindow("Moving Cube");
    SetupRC();

    glutReshapeFunc(ChangeSize);
    glutDisplayFunc(RenderScene);
    glutKeyboardFunc(myKeyboard);
    glutSpecialFunc(mySpecialKey);
    glutMainLoop();
    return 0;
}

void SetupRC()
{
    GLfloat whiteLight[] = {0.45f, 0.45f, 0.45f, 1.0f};
    GLfloat sourceLight[] = {0.25f, 0.25f, 0.25f, 1.0f};
    GLfloat lightPos[] = {0.f, 25.0f, 20.0f, 0.0f};

    // Enable lighting
    glEnable(GL_LIGHTING);

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, whiteLight);
    glLightfv(GL_LIGHT0, GL_AMBIENT, sourceLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, sourceLight);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glEnable(GL_LIGHT0);

    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_DEPTH_TEST);
}

void menuSelect(int option)
{
    switch (option)
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
    glutAddMenuEntry("Flat", 0);
    glutAddMenuEntry("Smooth", 1);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void ChangeSize(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10, 10, -10, 10, -10, 20);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
void RenderScene(void)
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(10.0f, 10.0f, 10.0f, 0, 0, 0, 0, 1, 0);

    // draw X-axis, Y-axis , Z-axis
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex3f(-100, 0, 0);
    glVertex3f(100, 0, 0);
    glVertex3f(0, -100, 0);
    glVertex3f(0, 100, 0);
    glVertex3f(0, 0, -100);
    glVertex3f(0, 0, 100);
    glEnd();

    // cube
    // glRotatef(thetaX, 1,0,0);
    // glRotatef(thetaY, 0, 1, 0);
    // glRotatef(thetaZ, 0, 0, 1);
    // glTranslatef(tx, ty, tz);

    rotMatrixX[5] = cos(thetaX * PI / 180);
    rotMatrixX[6] = -sin(thetaX * PI / 180);
    rotMatrixX[9] = sin(thetaX * PI / 180);
    rotMatrixX[10] = cos(thetaX * PI / 180);
    glMultMatrixf(rotMatrixX);

    rotMatrixY[0] = cos(thetaY * PI / 180);
    rotMatrixY[2] = sin(thetaY * PI / 180);
    rotMatrixY[8] = -sin(thetaY * PI / 180);
    rotMatrixY[10] = cos(thetaY * PI / 180);
    glMultMatrixf(rotMatrixY);

    rotMatrixZ[0] = cos(thetaZ * PI / 180);
    rotMatrixZ[1] = -sin(thetaZ * PI / 180);
    rotMatrixZ[4] = sin(thetaZ * PI / 180);
    rotMatrixZ[5] = cos(thetaZ * PI / 180);
    glMultMatrixf(rotMatrixZ);

    translateMatrix[12] = tx;
    translateMatrix[13] = ty;
    glMultMatrixf(translateMatrix);

    glMultMatrixf(scaleMatrix);

    glColor3f(1, 1, 0);
    glutSolidCube(6);
    glutSwapBuffers();
}

void myKeyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'r':
        thetaX = 0;
        thetaY = 0;
        thetaZ = 0;
        tx = 0;
        ty = 0;
        tz = 0;
        big = 1;
        small = 1;
        scaleMatrix[0] = big;
        scaleMatrix[5] = big;
        scaleMatrix[10] = big;
        break;
    case 'a':
        thetaX += 3;
        break;
    case 'd':
        thetaX -= 3;
        break;
    case 'w':
        thetaY += 3;
        break;
    case 's':
        thetaY -= 3;
        break;
    case 'z':
        thetaZ += 3;
        break;
    case 'x':
        thetaZ -= 3;
        break;
    case 'q':
        big += 0.1;
        small = big;
        scaleMatrix[0] = big;
        scaleMatrix[5] = big;
        scaleMatrix[10] = big;
        break;
    case 'e':
        small -= 0.1;
        big = small;
        scaleMatrix[0] = small;
        scaleMatrix[5] = small;
        scaleMatrix[10] = small;
        break;
    }
    glutPostRedisplay();
}

void mySpecialKey(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_LEFT:
        tx -= 0.1;
        break;
    case GLUT_KEY_RIGHT:
        tx += 0.1;
        break;
    case GLUT_KEY_UP:
        ty += 0.1;
        break;
    case GLUT_KEY_DOWN:
        ty -= 0.1;
        break;
    }
    glutPostRedisplay();
}

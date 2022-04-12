/***C/C++  http://bbs.csdn.net/topics/100091584***/
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <Cmath>
#include <math.h>
/***freeglut***/
#include ".\GL\freeglut.h"

//�e�����e
#define canvasX 600
#define canvasY 600

// glOrtho �d��
//-30~30
#define regionX 60
#define regionY 60

//作業五: 點選網格產生方塊並且顯示該方塊座標

bool mouseClick = false;
int colrow = 10;
float px = 0, py = 0;

void ChangeSize(int, int);
void RenderScene(void);
void buildPopupMenu();
void changeGrid(int);
void unit(int, int);
void mymouse(GLint, GLint, GLint, GLint);

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(canvasX, canvasY);
    glutInitWindowPosition(600, 80);
    glutCreateWindow("Simple Rectangle");

    buildPopupMenu();
    glutMouseFunc(mymouse);
    glutReshapeFunc(ChangeSize);
    glutDisplayFunc(RenderScene);
    glutMainLoop();
    return 0;
}

void menuSelect(int option)
{
    switch (option)
    {
    case 0:
        colrow = 10;
        glutPostRedisplay();
        break;
    case 1:
        colrow = 15;
        glutPostRedisplay();
        break;
    case 2:
        colrow = 20;
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
    glutAddMenuEntry("10", 0);
    glutAddMenuEntry("15", 1);
    glutAddMenuEntry("20", 2);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void ChangeSize(int w, int h)
{
    printf("Window Size= %d X %d\n", w, h);
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-(regionX / 2), regionX / 2, -(regionY / 2), regionY / 2, -30, 30);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
void RenderScene(void)
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 1.0f, 0, 0, 0, 0, 1, 0);

    // draw Grid
    changeGrid(colrow);

    // draw Square Unit
    if (mouseClick)
    {
        // if Exceed the range of colrow don't draw the unit
        if (px <= colrow && px >= -colrow)
        {
            if (py <= colrow && py >= -colrow)
            {
                // draw unit
                glBegin(GL_TRIANGLES);
                glColor3f(1, 0, 0);
                glVertex3f(px, py + 1, 0);
                glColor3f(1, 0, 0);
                glVertex3f(px + 1, py, 0);
                glColor3f(1, 0, 0);
                glVertex3f(px + 1, py + 1, 0);

                glColor3f(1, 0, 0);
                glVertex3f(px, py + 1, 0);
                glColor3f(1, 0, 0);
                glVertex3f(px, py, 0);
                glColor3f(1, 0, 0);
                glVertex3f(px + 1, py, 0);

                glEnd();
            }
        }
    }

    glutSwapBuffers();
}

// draw Grid
void changeGrid(int a)
{
    for (int x = -a; x <= a; x++)
    {
        for (int y = -a; y <= a; y++)
        {
            unit(x, y);
        }
    }
}

void unit(int x, int y)
{
    glLineWidth(1.0);
    glColor3f(1.0, 0.0, 0.0);

    glBegin(GL_LINE_LOOP);
    glVertex2f(x, y);
    glVertex2f(x + 1, y);
    glVertex2f(x + 1, y + 1);
    glVertex2f(x, y + 1);
    glEnd();
}

void mymouse(GLint button, GLint state, GLint x, GLint y)
{

    switch (button)
    {
    case GLUT_LEFT_BUTTON:
        if (state == GLUT_UP)
        {
            px = ceil(x / (canvasX / regionX) - 30);
            py = ceil((canvasY - y) / (canvasY / regionY) - 30);
            std::cout << "x�y��: " << px << "\n";
            std::cout << "y�y��: " << py << "\n"
                      << "\n";
            mouseClick = true;
        }
    default:
        break;
    }
}
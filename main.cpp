#include<iostream>
#include "approximator.h"
#include "Vector.h"
#include"object.h"
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <GL/glut.h>
#include<windows.h>
#include <math.h>
#include<vector>
#include<set>
#include<fstream>
#include "Parser.h"
int sz = 420; // количество строк в файле
vector<Object> container; //здесь храним орбиты
void menu(int pos);
void idle();
void display();
int create_window(int argc, char **argv, char *param, int width, int height)
{
    glutInit(&argc, argv);
    int res = 0;
    int nmenu = 0;
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(width, height);
    glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE);
    res = glutCreateWindow(param);
    nmenu = glutCreateMenu(menu);
    glutSetMenu(nmenu);
    glutAddMenuEntry("close window", 1);
    glutAddMenuEntry("update", 2);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    return res;
}
int main(int argc, char *argv[])
{
    create_window(argc, argv, "window1", 600, 300);
    Object obj =Object(1, 1);
    obj.init_from_file("C:\\Users\\frolo\\Documents\\codeblocks\\visual_model\\data.csv", sz);
    container.push_back(obj);
    Vector v = Vector(0, 0, 0);
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}

void menu(int pos)
{
    switch(pos)
    {
    case 1 :
        {
            int buf = glutGetWindow();
            std::cout<<buf;
            glutDestroyWindow(buf);
        }
    case 2 :
        {
            glutSetWindow(1);
            glutPostRedisplay();
        }
    }
}
void display()
{
    (container[0]).render(0.5);
    glutSwapBuffers();
}
void idle()
{

}

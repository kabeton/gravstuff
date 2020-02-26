#include<iostream>
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
#include"renderer.h"
#include "Parser.h"
int sz = 420; // количество строк в файле
deque<Object> container; //здесь храним орбиты
Renderer renderer = Renderer(&container);

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
    glutAddMenuEntry("dynamic", 3);
    glutAddMenuEntry("static", 4);
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
    renderer.set_initial_time(0.2);
    //std::cout<<renderer.get_mode()<<std::endl;
    //renderer.set_mode(true);
    //std::cout<<renderer.get_mode()<<std::endl;
    //int a;
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
            break;
        }
    case 2 :
        {
           // glutSetWindow(1);
           // glutPostRedisplay();
        }
    case 3:
        {
            renderer.set_initial_time(0.2);
            renderer.set_mode(true);
            display();
            break;
        }
    case 4:
        {
            renderer.set_mode(false);
            display();
            break;
        }
    default:
        {
            break;
        }
    }
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    if(renderer.get_mode())
    {
        renderer.dynamic_render(0.00001);
    }
    else
    {
        renderer();
    }
    glutSwapBuffers();

}
void idle()
{
    std::cout<<renderer.get_mode()<<std::endl;
    display();
}

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
#include"grid.h"
//std::vector<Point> Grid::data = std::vector<Point>();
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
void show(std::vector<Point> dt) //костыль для вывода вектора на экран
{
    std::cout<<"The result is: "<<std::endl;
    for(auto it = dt.begin(); it != dt.end(); ++it) std::cout<<"angle = "<<it->angle<<"  velocity = "<<it->initial_velocity<<"  final = "<<it->final_velocity<<std::endl;
}
int main(int argc, char *argv[])
{
    double min_angle = 0;
    double max_angle = 360;
    double angle_range = 360;
    double min_velocity = 0;
    double max_velocity = 1000;
    double velocity_range = 1000;
    double start_angle = angle_range / 2;
    double start_velocity = velocity_range / 2;
    double range[4];
    range[0] = velocity_range / 2.0;
    range[1] = velocity_range / 2.0;
    range[2] = angle_range / 2.0;
    range[3] = angle_range / 2.0;
    double boundary[4];
    std::vector<Point> result;
    for (int h = 1; h < 10; ++h)
    {
        Grid grid = Grid();
        grid.set_angle_range(start_angle - range[2], start_angle + range[3]);
        grid.set_velocity_range(start_velocity - range[0], start_velocity + range[1]);
        grid.set_grid_size(3, 3);
        result = grid.calculate();
        start_angle = result[0].angle;
        start_velocity = result[0].initial_velocity;
        range[0] = range[0] / grid.num_divisions;
        range[1] = range[1] / grid.num_divisions;
        range[2] = range[2] / grid.num_divisions;
        range[3] = range[3] / grid.num_divisions;
        boundary[0] = result[0].initial_velocity - min_velocity;
        boundary[1] = max_velocity - result[0].initial_velocity;
        boundary[2] = result[0].angle - min_angle;
        boundary[3] = max_angle - result[0].angle;
        if (range[0] > boundary[0]) range[0] = boundary[0];
        if (range[1] > boundary[1]) range[1] = boundary[1];
        if (range[2] > boundary[2]) range[2] = boundary[2];
        if (range[3] > boundary[3]) range[3] = boundary[3];
        //show(result);
    }
    std::cout<<"****"<<std::endl;
    show(Grid::data);
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
    display();
}

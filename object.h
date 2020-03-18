#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED
#include<vector>
#include<deque>
#include<map>
#include"Vector.h"
#include<algorithm>
#include<GL/glut.h>
#include"Parser.h"
#include<fstream>
#include<math.h>
using namespace std;
class Compare
{
public:
    double t = 0;
   bool operator()(double* &it1, const double &it2)
    {
        return bool(*it1 < it2);
    }
};
class Object
{
public:
    double angle;
    bool is_initiated = 0;
    double velocity;
    Compare cmp;
    Object(double _angle, double _velocity)
    {
        angle = _angle;
        velocity = _velocity;
        cmp = Compare();
    }
    void set_initial_time(double _time)
    {
        time = _time;
        std::cout<<"**"<<time<<std::endl;
    }
    Vector get_value(double time)
    {
        cmp.t = time;
        auto it = lower_bound(data.begin(), data.end(), time,  cmp);
        if (it == data.end())
        {
            return Vector(0, 0, 0);
        }
        return Vector((*it)[1], (*it)[2], (*it)[3]);
    }

    void render(double step)
    {
        glBegin(GL_POINTS);
        for (double i = step; i > -1; i += step)
        {
            Vector point = get_value(i + 0.1);
            //std::cout<<point<<std::endl;
            if (point == Vector(0, 0, 0))
            {
                i = -2;
                continue;
            }
            glVertex2f(point.x, point.y);
        }
        glEnd();
    }
    void dynamic_render(double dt)
    {
        Vector point = get_value(time);
        if(flag)
        {

        glBegin(GL_POINTS);
       // for (double i = 0; i <= time; i +=step)
        //{
            glVertex2f(point.x, point.y);
        //}
        glEnd();
        }
        else
        {

        //Vector point = get_value(time);
        glClear(GL_COLOR_BUFFER_BIT);
        glBegin(GL_POLYGON);
        for(double i = 0; i < 6.28; i +=0.5)
        {
            glVertex2f(point.x + 0.05*cos(i), point.y + 0.05*sin(i));
        }
        glEnd();
        }
        flag = !flag;
        time += dt;
    }
    void parser_init(char _sep)
    {
        parser.sep = _sep;
    }
    int init_from_file(string path, int numlines)
    {
        std::ifstream f;
        f.open(path);
        if(!f.is_open())
            {
                std::cout<<"error"<<std::endl;
                return 0;
            }
        for (int k = 0; k < numlines; ++k)
        {
            char buf[30] = {0};
            f.getline(buf, 30);
            data.push_back(parser.string_to_doubles(buf));
        }
        is_initiated = 1;
        return 1;
    }


private:
    std::deque<double*> data;
    Parser parser = Parser();
    deque<double*>::iterator position = data.begin();
    double time = 1;
    double n = 1;
    double step = 0.0000001;
    bool flag = true;
};


#endif // OBJECT_H_INCLUDED

#ifndef GRID_H_INCLUDED
#define GRID_H_INCLUDED
#include<string>
#include<algorithm>
#include <unistd.h>
#include <sys/types.h>
#include <iostream>
#include <fstream>
#include <sys/wait.h>
string path = "C:\\Users\\frolo\\Documents\\codeblocks\\visual_model\\data.csv";//��� �������
double get_solution(double angle, double velocity, string *_path)
{
    string ofname;
    ofname = to_string(velocity) + "_" + to_string(angle);
    *_path = "/home/kabe/infa/scimod/gravi/" + ofname;
    pid_t id = fork();
    pid_t pid;
    int status;
    if(id == 0) {
      (void)execl("/home/kabe/infa/scimod/gravi/a.out", "/home/kabe/infa/scimod/gravi/a.out", to_string(velocity).c_str(), to_string(angle).c_str(), (char *)0);
    } 
    pid = waitpid(-1, &status, 0);
    ifstream spd("speed");
    double spd_fin;
    spd >> spd_fin; 
    spd.close();
    return spd_fin;
}
class Point
{
public:
    double initial_velocity;
    double angle;
    double final_velocity;
    string path;
    bool operator<(Point _point)
    {
        return (final_velocity < _point.final_velocity);
    }
};
class Grid
{
public:
    static std::vector<Point> data;
    double min_angle;
    double max_angle;
    double min_velocity;
    double max_velocity;
    int num_divisions = 2;
    int num_brunch = 1;
    int depth = 4;
    int grid_size1 = 10;
    int grid_size2 = 10;
    void set_velocity_range(double v1, double v2)
    {
        min_velocity = v1;
        max_velocity = v2;
    }
    void set_angle_range(double a1, double a2)
    {
        min_angle = a1;
        max_angle = a2;
    }
    void set_param(int divisions, int brunch, int _depth)
    {
        num_divisions = divisions;
        num_brunch = brunch;
        depth = _depth;
    }
    void set_grid_size(int a, int b)
    {
        grid_size1 = a;
        grid_size2 = b;
    }
    std::vector<Point> calculate()
    {
        std::vector<Point> buf;
        double angle_step = (max_angle - min_angle) / grid_size1;
        double velocity_step = (max_velocity - min_velocity) / grid_size2;
        for(double i = min_angle; i <= max_angle; i += angle_step)
        {
            for(double g = min_velocity; g <= max_velocity; g += velocity_step)
            {
                Point point = Point();
                point.angle = i;
                point.initial_velocity = g;
                point.final_velocity = get_solution(i, g, &(point.path));
                data.push_back(point);
                if (buf.size() < num_brunch)
                {
                    buf.push_back(point);
                    std::sort(buf.begin(), buf.end());
                }
                else
                {
                    for(auto it = buf.begin(); it != buf.end(); ++it)
                    {
                        if(point.final_velocity > (*it).final_velocity)
                        {
                            (*it) = point;
                            std::sort(buf.begin(), buf.end());
                        }
                    }
                }
            }
        }
        return buf;
    }

};
std::vector<Point> Grid::data = std::vector<Point>();

#endif // GRID_H_INCLUDED

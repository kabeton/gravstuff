#ifndef RENDERER_H_INCLUDED
#define RENDERER_H_INCLUDED
#include<GL/glut.h>
#include"object.h"
#include<deque>
class Renderer
{
public:

    Renderer(deque<Object> *_container)
    {
        container = _container;
    }
    void render(deque<Object> *_container)
    {
        for(auto it = _container->begin(); it != _container->end(); ++it)
        {
            (*it).render(0.1);
        }
    }
    void dynamic_render(double dt)
    {
        for(auto it = container->begin(); it != container->end(); ++it)
        {
            (*it).dynamic_render(0.1);
        }
    }
    void operator()(void)
    {
        this->render(container);
    }
    void set_initial_time(double _time)
    {
        for(auto it = container->begin(); it != container->end(); ++it) (*it).set_initial_time(_time);
    }
    bool get_mode()
    {
        return mode;
    }
    void set_mode(bool _mode)
    {
        mode = _mode;
    }
private:
    deque<Object> *container = NULL;
    bool mode = true;

};


#endif // RENDERER_H_INCLUDED

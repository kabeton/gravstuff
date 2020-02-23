#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED
#include<iostream>
#include<stdlib.h>
class Vector
{
public:
    friend std::ostream& operator<<(std::ostream &os, Vector *v);
	double x = 0, y = 0, z = 0;
	Vector()
	{

	};
    Vector(double _x, double _y, double _z)
    {
        x = _x;
        y = _y;
        z = _z;
    };
    void show()
    {
        std::cout<<x<<" "<<y<<" "<<z<<std::endl;
    };
	void update(double _x, double _y, double _z)
	{
		x = _x;
		y = _y;
		z = _z;
	};
	double get_x()
	{
	    return x;
	};
	double get_y()
	{
	    return y;
	};
	double get_z()
	{
	    return z;
	};
	bool operator==(Vector v1)
	{
	    return (v1.x==x && v1.y==y && v1.z==z);
	}
	bool operator==(int n)
	{
	    return !(bool(x + y + z));
	}
};
std::ostream& operator<<(std::ostream &os, const Vector &v)
    {
        os<<v.x<<" "<<v.y<<" "<<v.z;
        return os;
    };


#endif // VECTOR_H_INCLUDED

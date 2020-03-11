
#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>

typedef struct planet
{
	double m;
	double x;
	double y;
	double v;
	double vx;
	double vy;
	double r;
	double phi;	
	double omega;
	double per;
}planet;

using namespace std;
int main()
{
	double m0=1.989*pow(10,30);
	vector <planet> p;
	p.resize(8);
	double vx0,vy0;
	
	p[0].m=3.285*pow(10,23); //Меркурий
	p[0].r=57.91*pow(10,9);
	p[0].phi=30*3.14159265/180;
	p[0].per=88*86400;
	p[0].omega=2*3.14159265/p[0].per;
	
	p[1].m=4.86*pow(10,24); //Венера
	p[1].r=108000000000.0;
	p[1].phi=-47*3.14159265/180;
	p[1].per=225*86400;
	p[1].omega=2*3.14159265/p[1].per;
	
	p[2].m=5.97*pow(10,24); //Земля
	p[2].r=149600000000.0;
	p[2].phi=0;
	p[2].per=365*86400;
	p[2].omega=2*3.14159265/p[2].per;
	
	p[3].m=6.39*pow(10,23); //Марс
	p[3].r=228000000000.0;
	p[3].phi=75*3.14159265/180;
	p[3].per=687*86400;
	p[3].omega=2*3.14159265/p[3].per;
	
	p[4].m=1.89*pow(10,27); //Юпитер
	p[4].r=778570000000.0;
	p[4].phi=95*3.14159265/180;
	p[4].per=4332*86400;
	p[4].omega=2*3.14159265/p[4].per;
	
	p[5].m=5.68*pow(10,26); //Сатурн
	p[5].r=1430000000000.0;
	p[5].phi=110*3.14159265/180;
	p[5].per=10759*86400;
	p[5].omega=2*3.14159265/p[5].per;
	
	p[6].m=8.68*pow(10,25); //Уран
	p[6].r=2800000000000.0;
	p[6].phi=-150*3.14159265/180;
	p[6].per=30685*86400;
	p[6].omega=2*3.14159265/p[6].per;
	
	p[7].m=1.02*pow(10,26); //Нептун
	p[7].r=4550000000000.0;
	p[7].phi=165*3.14159265/180;
	p[7].per=60190*86400;
	p[7].omega=2*3.14159265/p[7].per;
	
	for(int i=0;i<8;i++)
	{
		p[i].x=(p[i].r)*cos(p[i].phi);
		p[i].y=(p[i].r)*sin(p[i].phi);
		p[i].v=2*3.14159265*p[i].r/p[i].per;
		p[i].vx=(p[i].v)*sin(p[i].phi);
		p[i].vy=(p[i].v)*cos(p[i].phi);
	}
	
	/*double x1,y1,vx1,vy1;
	x=149600000000.0;
	y=0;
	vx=0;
	vy=sqrt(6.67*pow(10,-11)*2*pow(10,30)/sqrt(x*x+y*y));*/
	double x0,y0,fx,fy;
	ifstream in("input.txt");
	in>>vx0>>vy0;
	fx=0;
	fy=0;
	x0=p[2].x;
	y0=p[2].y;
	vx0+=p[2].vx;
	vy0+=p[2].vy;
	ofstream out("ship.txt");
	ofstream out1("mercury.txt");
	ofstream out2("venus.txt");
	ofstream out3("earth.txt");
	ofstream out4("mars.txt");
	ofstream out5("jup.txt");
	ofstream out6("sat.txt");
	ofstream out7("ur.txt");
	ofstream out8("nept.txt");
	
	for(long long i=0;i<=86400*365*6;i+=3600)
	{
		for(int j=0;j<8;j++)
		{
			p[j].x=(p[j].r)*cos((p[j].omega)*i+p[j].phi);
			p[j].y=(p[j].r)*sin((p[j].omega)*i+p[j].phi);
			p[j].vx=(p[j].v)*sin((p[j].omega)*i+p[j].phi);
			p[j].vy=(p[j].v)*cos((p[j].omega)*i+p[j].phi);
		}
		x0+=vx0*3600;
		y0+=vy0*3600;
		vx0+=(-6.67*pow(10,-11)*m0*pow(x0*x0+y0*y0,-1.5)*x0*3600);
		vy0+=(-6.67*pow(10,-11)*m0*pow(x0*x0+y0*y0,-1.5)*y0*3600);
		for(int j=0;j<8;j++)
		{
			vx0+=(6.67*pow(10,-11)*p[j].m*pow((p[j].x-x0)*(p[j].x-x0)+(p[j].y-y0)*(p[j].y-y0),-1.5)*(p[j].x-x0)*3600);
			vy0+=(6.67*pow(10,-11)*p[j].m*pow((p[j].x-x0)*(p[j].x-x0)+(p[j].y-y0)*(p[j].y-y0),-1.5)*(p[j].y-y0)*3600);
		}
			out<<i<<' '<<x0/1496/pow(10,8)<<' '<<y0/1496/pow(10,8)<<endl;		
			out1<<i<<' '<<p[0].x/1496/pow(10,8)<<' '<<p[0].y/1496/pow(10,8)<<' '<<sqrt(p[0].x*p[0].x+p[0].y*p[0].y)/1496/pow(10,8)<<' '<<endl;
			out2<<i<<' '<<p[1].x/1496/pow(10,8)<<' '<<p[1].y/1496/pow(10,8)<<' '<<sqrt(p[1].x*p[1].x+p[1].y*p[1].y)/1496/pow(10,8)<<' '<<endl;
			out3<<i<<' '<<p[2].x/1496/pow(10,8)<<' '<<p[2].y/1496/pow(10,8)<<' '<<sqrt(p[2].x*p[2].x+p[2].y*p[2].y)/1496/pow(10,8)<<' '<<endl;
			out4<<i<<' '<<p[3].x/1496/pow(10,8)<<' '<<p[3].y/1496/pow(10,8)<<' '<<sqrt(p[3].x*p[3].x+p[3].y*p[3].y)/1496/pow(10,8)<<' '<<endl;
			out5<<i<<' '<<p[4].x/1496/pow(10,8)<<' '<<p[4].y/1496/pow(10,8)<<' '<<sqrt(p[4].x*p[4].x+p[4].y*p[4].y)/1496/pow(10,8)<<' '<<endl;
			out6<<i<<' '<<p[5].x/1496/pow(10,8)<<' '<<p[5].y/1496/pow(10,8)<<' '<<sqrt(p[5].x*p[5].x+p[5].y*p[5].y)/1496/pow(10,8)<<' '<<endl;
			out7<<i<<' '<<p[6].x/1496/pow(10,8)<<' '<<p[6].y/1496/pow(10,8)<<' '<<sqrt(p[6].x*p[6].x+p[6].y*p[6].y)/1496/pow(10,8)<<' '<<endl;
			out8<<i<<' '<<p[7].x/1496/pow(10,8)<<' '<<p[7].y/1496/pow(10,8)<<' '<<sqrt(p[7].x*p[7].x+p[7].y*p[7].y)/1496/pow(10,8)<<' '<<endl;
	}
	in.close();
	out1.close();
	out2.close();
	out3.close();
	out4.close();
	out5.close();
	out6.close();
	out7.close();
	out8.close();
	out.close();
	return 0;
}

#include <boost/numeric/odeint.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <stdio.h>
#include <stdlib.h>

//Отношения масс планет к массе Солнца

#define n1 0.00000016425 //Меркурий
#define n2 0.0000024335 //Венера
#define n3 0.000002986 //Земля
#define n4 0.0000003195 //Марс
#define n5 0.000949 //Юпитер
#define n6 0.00028415 //Сатурн
#define n7 0.000043405 //Уран
#define n8 0.0000512 //Нептун

using namespace boost::numeric::odeint;
using namespace std;

double fx[9]; //горизонтальные компоненты сил тяготения 
double fy[9]; //вертикальные компоненты сил тяготения

double fxt;
double fyt;

double n[8] = {n1, n2, n3, n4, n5, n6, n7, n8}; //отношения масс планет к массе Солнца

/*
 x - вектор исходных координат (x1.x2.x3....xn);
 dxdt - вектор производных (x1'.x2'.x3'....xn');
 t - переменная. по которой интегрируем. т.е. x'=f(t);
 observer - печатает таблицу x(t);
 stepper - алгоритм интегрирования;
 integrate_adaptive(stepper(),rhs,x(0),t0,t(конеч.),dt(шаг),observer);
 x(0) - начальные условия;
 t0 - начальный момент времени;
 
 x[0] -x
 x[1] - y
 x[2] - x'
 x[3] - y' //корабль
 
 x[4]
 x[5]
 x[6]
 x[7] //Меркурий
 
 x[8]
 x[9]
 x[10]
 x[11] //Венера
 
 x[12]
 x[13]
 x[14]
 x[15] //Земля
 
 x[16]
 x[17]
 x[18]
 x[19] //Марс
 
 x[20]
 x[21]
 x[22]
 x[23] //Юпитер
 
 x[24]
 x[25]
 x[26]
 x[27] //Сатурн
 
 x[28]
 x[29]
 x[30]
 x[31] //Уран
 
 x[32]
 x[33]
 x[34]
 x[35] //Нептун
 
 */

void rhs(const vector<double> &x, vector<double> &dxdt, const double t)
{

  fxt=0.0;
  fyt=0.0;
	fxt=-6,67*pow(10,-11)*2*pow(10,30)*pow((x[4]*x[4]+x[1]*x[1]),-1.5)*(x[0]); // Сила на корабль от Солнца
	fyt=-6,67*pow(10,-11)*2*pow(10,30)*pow((x[4]*x[4]+x[1]*x[1]),-1.5)*(x[1]); 
	
	dxdt[0]=x[2]; //переприсваиваем ускорение корабля
	dxdt[1]=x[3];
	dxdt[2]=fxt;
	dxdt[3]=fyt;
}

typedef runge_kutta_dopri5<vector<double>> Stepper;

int main(int argc, char *argv[], char *envp[]) {
  double v0, angle;
  if(argc > 1) {
    v0 = stod(argv[1]);
    angle = stod(argv[2]);
  } else {
    cout << "no parameters provided" << endl;
    exit(0);
  }
  int saveflag = 0;
  if(argc == 4) saveflag++;
  
  vector<double> x;
  x.resize(4);
  vector<double> x0;
  x0.resize(4); //присваиваем начальные условия
  	
  x0[0]=1000; 
  x0[1]=0;
  x0[2]=0;
  x0[3]=(20+(2*3.14159265*1000/60)); //корабль
  //x0[2] = v0 * cos(angle);
  //x0[3] = v0 * sin(angle);
  cout << x0[2] << " " << x0[3] << endl;
  	

  FILE *files[9];
  if(saveflag) {
    files[0] = fopen("ship.csv", "w");
  }

  Stepper stepper;
  double t = 0;
  double dt = 0.1;
  for(int iter = 0; iter < 1200; iter++) {
    t += dt;
    
    stepper.do_step(rhs, x0, t, dt);
    if(saveflag) {
      for(int i = 0; i <= 0; i++) {
        fprintf(files[i], "%g %g %g\n", t, x0[4*i], x0[4*i+1]);
      }
    }
    
    //if(sqrt(x0[0]*x0[0] + x0[1]*x0[1]) > 40000){
      //break;
    //}
  }
  
  double final_speed = sqrt(x0[2]*x0[2] + x0[3]*x0[3]);
  FILE *fd;
  fd = fopen("param_file", "a");
  fprintf(fd, "%g %g\n", angle, final_speed);
  fclose(fd);
  
  if(saveflag) {
    for(int i = 0; i < 1; i++) {
      fclose(files[i]);
    }
  }
  return 0;
}

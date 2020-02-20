#include <boost/numeric/odeint.hpp>
#include <iostream>
#include <vector>

using namespace boost::numeric::odeint;
using namespace std;

/*
 x - вектор исходных координат (x1,x2,x3,...xn);
 dxdt - вектор производных (x1',x2',x3',...xn');
 t - переменная, по которой интегрируем, т.е. x'=f(t);
 observer - печатает таблицу x(t);
 stepper - алгоритм интегрирования;
 integrate_adaptive(stepper(),rhs,x(0),t0,t(конеч.),dt(шаг),observer);
 x(0) - начальные условия;
 t0 - начальный момент времени;
 */

void rhs(const vector<double> &x, vector<double> &dxdt, const double t) {
  dxdt[0] = 2*t;

}

void observer(vector<double> &x, const double t) {
  cout << t << " " << x[0] << endl;
}

typedef runge_kutta_dopri5<vector<double>> stepper;

int main() {
  vector<double> x;
  x.push_back(0);
  integrate_adaptive(stepper(), rhs, x, 0.0, 10.0, 0.1, observer);

  return 0;
}


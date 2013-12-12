// flrw.cpp

// Author: Jonah Miller (jonah.maxwell.miller@gmail.com)
// Time-stamp: <2013-12-11 17:36:48 (jonah)>

// This is the implementation of my program to numerically explore
// Friedmann-Lemaitre-Robertson-Walker metrics.

// For background, see the included pdf or latex file. For usage, see
// the readme or the header file.

// Dependencies
// ----------------------------------------------------------------------
// This program depends on the RKF45 package I wrote, which is an
// implementation of a fourth-order Runge-Kutte Fehlberg integration
// scheme. If you don't have it, you can find it here:
// https://github.com/Yurlungur/runge_kutta
// ----------------------------------------------------------------------


// Include statements
// ----------------------------------------------------------------------
#include "flrw.hpp"
#include <cmath>
#include <cassert>
#include <fstream>
using std::endl;
// ----------------------------------------------------------------------


// Utility functions
// ----------------------------------------------------------------------
double eval_func(double (*func)(double,double), const dVector& y) {
  assert ( y.size() == 2 && "y = [a,b]" );
  double a = y[0];
  double b = y[1];
  return func(a,b);
}
// ----------------------------------------------------------------------


// The iteration function
// ----------------------------------------------------------------------
double get_p(double (*omega)(double), double rho) {
  return omega(rho)*rho;
}
double get_rho(double a, double b) {
  return (3*b + 3*K - LAMBDA*a*a)/(8*M_PI*a*a);
}
double get_rho(const dVector& y) {
  return eval_func(get_rho,y);
}
double get_a_prime(double a, double b) {
  return b;
}
double get_a_prime(const dVector& y) {
  return eval_func(get_a_prime,y);
}
double get_b_prime(double (*omega)(double), double a, double b) {
  double rho = get_rho(a,b);
  double p = get_p(omega,rho);
  return (-1)*(K + b*b + 8*M_PI*p*a*a + LAMBDA*a*a)/(2*a);
}
double get_b_prime(double (*omega)(double), const dVector& y) {
  assert ( y.size() == 2 && "y = [a,b]" );
  double a = y[0];
  double b = y[1];
  return get_b_prime(omega,a,b);
}
dVector get_y_prime(double (*omega)(double), const dVector& y) {
  dVector output;
  output.push_back(get_a_prime(y));
  output.push_back(get_b_prime(omega,y));
  return output;
}
// ----------------------------------------------------------------------


// Output
// ----------------------------------------------------------------------
std::ostream& operator <<(std::ostream& out, const dVector& in) {
  out << "[";
  for (unsigned int i = 0; i < in.size()-1; i++) {
    out << in[i] << ", ";
  }
  out << in[in.size()-1] << "]";
  return out;
}

void print_simulation(const RKF45& simulation, std::ostream& out,
		      double (*omega)(double)) {
  // Some convenience variables
  dVector y;
  double t,a,b,rho,p;

  // Print a header line
  out << "# t\ta\ta'\trho\tp" << endl;

  // Prints the rest
  for (int n = 0; n < simulation.steps(); n++) {
    // Assign variables
    t = simulation.get_t(n);
    y = simulation.get_y(n);
    a = y[0];
    b = y[1];
    rho = get_rho(y);
    p = get_p(omega,rho);
    // Output
    out << t << " "
	<< a << " " << b << " "
	<< rho << " " << p
	<< endl;
  }
}
void print_simulation(const RKF45& simulation, const char* filename,
		      double (*omega)(double)) {
  std::ofstream file;
  file.open(filename);
  print_simulation(simulation,file,omega);
  file.close();
}
// ----------------------------------------------------------------------

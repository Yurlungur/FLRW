// flrw.cpp

// Author: Jonah Miller (jonah.maxwell.miller@gmail.com)
// Time-stamp: <2013-12-12 17:22:40 (jonah)>

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
  double rho = y[1];
  return func(a,rho);
}
// ----------------------------------------------------------------------


// The iteration function
// ----------------------------------------------------------------------
double get_p(double (*omega)(double), double rho) {
  return omega(rho)*rho;
}

double get_a_prime(double a, double rho) {
  //  std::cout << "\tb = " << b << std::endl;
  return sqrt((a*a*8.0*M_PI*rho-LAMBDA)/3.0);
}

double get_a_prime(const dVector& y) {
  return eval_func(get_a_prime,y);
}

double get_rho_prime(double (*omega)(double), double a, double rho) {
  return -3*(get_a_prime(a,rho)/a)*(rho + get_p(omega,rho));
}

dVector get_y_prime(double (*omega)(double), const dVector& y) {
  dVector output;
  double a = y[0];
  double rho = y[1];
  double a_prime = get_a_prime(a,rho);
  double rho_prime = get_rho_prime(omega,a,rho);
  output.push_back(a_prime);
  output.push_back(rho_prime);
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
  double t,a,rho,p;

  // Print a header line
  out << "# t\ta\trho\tp" << endl;

  // Prints the rest
  for (int n = 0; n < simulation.steps(); n++) {
    // Assign variables
    t = simulation.get_t(n);
    y = simulation.get_y(n);
    a = y[0];
    rho = y[1];
    p = get_p(omega,rho);
    // Output
    out << t << " "
	<< a << " "
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

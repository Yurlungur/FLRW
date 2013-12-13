// matter_dominated_universe.cpp
// Author: Jonah Miller (jonah.maxwell.miller@gmail.com)
// Time-stamp: <2013-12-13 17:42:26 (jonah)>

// This is the main loop to generate a radiation dominated universe to
// simulate.

// Includes
#include "flrw.hpp"
#include <iostream>
#include <string>
#include <cmath>
using std::cout;
using std::endl;
using std::string;


// Global constants
// ----------------------------------------------------------------------
const int NUM_STARTING_CONDITIONS = 4;
const string DATA_FILE_START = "radiation_dominated_universe_rho0";
const string DATA_FILE_END = ".dat";
const double RHO_START [] = {32,64,128,256};
const string RHO_START_STRINGS [] = {"32","64","128","256"};
const double A_0 = 0.01;
const double T_0 = pow(A_0,2);
const double MAX_T = 100;
const double MAX_DT = 0.01*MAX_T;
const double RELATIVE_ERROR_FACTOR = 1E-5;
// ----------------------------------------------------------------------


// The radiation dominated universe has an equation of state variable
// of w=1/3, so we use this and implement a method.
// ----------------------------------------------------------------------
double omega(double rho) {
  return 1.0/3.0;
}
dVector f(double t, const dVector& y) {
  return get_y_prime(omega,y);
}
// ----------------------------------------------------------------------


// And the main function
// ----------------------------------------------------------------------
int main () {
  // Some variables we'll use
  dVector y0;
  string outfile_name;
  RKF45 integrator;

  // Some settings
  y0.push_back(A_0);
  y0.push_back(RHO_START[0]);
  integrator.set_f(f);
  integrator.set_max_dt(MAX_DT);
  integrator.set_relative_error_factor(RELATIVE_ERROR_FACTOR);
  integrator.set_t0(T_0);

  cout << "Let's simulate a radiation dominated universe!\n"
       << "We assume that:\n"
       << "\tt_0 = " << T_0 << "\n"
       << "\ta(t_0) = " << A_0 << "."
       << endl;

  for (int i = 0; i < NUM_STARTING_CONDITIONS; i++) {
    cout << "-------------------------------------------------------\n"
	 << "We now simulate with rho = " << RHO_START_STRINGS[i] << "."
	 << endl;
    y0[1] = RHO_START[i];
    integrator.set_y0(y0);
    integrator.reset();
    outfile_name = DATA_FILE_START + RHO_START_STRINGS[i] + DATA_FILE_END;
    cout << "Working..." << endl;
    integrator.integrate(MAX_T);
    cout << "Finished! Saving to file " << outfile_name << "." << endl;
    print_simulation(integrator,&outfile_name[0],omega);
    cout << "-------------------------------------------------------\n"
	 << endl;
  }

  cout << "And we're all done!\n"
       << "Have a nice day!"
       << endl;

  return 0;
}
// ----------------------------------------------------------------------

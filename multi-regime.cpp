// dark_energy_dominated_universe.cpp
// Author: Jonah Miller (jonah.maxwell.miller@gmail.com)
// Time-stamp: <2013-12-14 16:36:12 (jonah)>

// This is the main loop to generate a univers that changes regime.

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
const string DATA_FILE_START = "multi-regime_universe_";
const string DATA_FILE_END = ".dat";
const double RHO_START = 200;
const string NAME_STRINGS [] = {"abrupt_transition",
				"moderate_transition",
				"mild_transition",
				"no_transition"};
const double A_0 = 0.01;
const double T_0 = 0;
const double MAX_T = 0.1;
const double MAX_DT = 0.01*MAX_T;
const double RELATIVE_ERROR_FACTOR = 1E-5;
// ----------------------------------------------------------------------


// Omega Constants
// ----------------------------------------------------------------------
const double RHO_MIN = 0;// Minimum rho
const double OMEGA_MIN = -1; // The omega we want when rho is small
const double ERF_MIN = -1; // erf ranges from -1 to 1
const double RHO_DARK_ENERGY [] = {10,20,25,37}; // When we transition
						 // from a matter to
						 // dark energy
						 // dominated universe
const double RHO_MATTER [] = {20,40,80,92}; // When we transition from
					    // a radiation dominated
					    // to a matter dominated
					    // universe.
const double RHO_RADIATION = RHO_START; // Initial rho value.
// Transition between dark energy and matter dominated regimes
const double TRANSITION_WIDTH_DE [] = {1.0,5.0,12.0,20.0}; 
// Transition between matter and radiation dominated regimes.
const double TRANSITION_WIDTH_MR [] = {1.0,5.0,12.0,20.0}; 
const double DE_AMPLITUDE = 1.0/2.0; // (1/2) Size of change in rho
				     // between dark energy and
				     // radation regimes.
const double MATTER_AMPLITUDE = (1.0/2.0)*(1.0/3.0); // (1/2) size of
						     // change in rho
						     // between
						     // radiation and
						     // matter
						     // regimes.
// ----------------------------------------------------------------------


// We're testing a number of omegas here. So we define a new omega for each.
// ----------------------------------------------------------------------
double omega0(double rho) {
  return OMEGA_MIN
    + DE_AMPLITUDE + MATTER_AMPLITUDE
    + DE_AMPLITUDE * erf((rho-RHO_DARK_ENERGY[0])/TRANSITION_WIDTH_DE[0])
    + MATTER_AMPLITUDE * erf((rho-RHO_MATTER[0])/TRANSITION_WIDTH_MR[0]);
}
double omega1(double rho) {
  return OMEGA_MIN
    + DE_AMPLITUDE + MATTER_AMPLITUDE
    + DE_AMPLITUDE * erf((rho-RHO_DARK_ENERGY[1])/TRANSITION_WIDTH_DE[1])
    + MATTER_AMPLITUDE * erf((rho-RHO_MATTER[1])/TRANSITION_WIDTH_MR[1]);
}
double omega2(double rho) {
  return OMEGA_MIN
    + DE_AMPLITUDE + MATTER_AMPLITUDE
    + DE_AMPLITUDE * erf((rho-RHO_DARK_ENERGY[2])/TRANSITION_WIDTH_DE[2])
    + MATTER_AMPLITUDE * erf((rho-RHO_MATTER[2])/TRANSITION_WIDTH_MR[2]);
}
double omega3(double rho) {
  return OMEGA_MIN
    + DE_AMPLITUDE + MATTER_AMPLITUDE
    + DE_AMPLITUDE * erf((rho-RHO_DARK_ENERGY[3])/TRANSITION_WIDTH_DE[3])
    + MATTER_AMPLITUDE * erf((rho-RHO_MATTER[3])/TRANSITION_WIDTH_MR[3]);
}
// And an f for each.
dVector f0(double t, const dVector& y) {
  return get_y_prime(omega0,y);
}
dVector f1(double t, const dVector& y) {
  return get_y_prime(omega1,y);
}
dVector f2(double t, const dVector& y) {
  return get_y_prime(omega2,y);
}
dVector f3(double t, const dVector& y) {
  return get_y_prime(omega3,y);
}
// ----------------------------------------------------------------------


// And a vector of these functions
dVector (*f [4])(double,const dVector&);
double (*omega [4])(double);

// And the main function
// ----------------------------------------------------------------------
int main () {
  // Set the array
  f[0] = f0;
  f[1] = f1;
  f[2] = f2;
  f[3] = f3;
  omega[0] = omega0;
  omega[1] = omega1;
  omega[2] = omega2;
  omega[3] = omega3;

  // Some variables we'll use
  dVector y0;
  string outfile_name;
  RKF45 integrator;

  // Some settings
  y0.push_back(A_0);
  y0.push_back(RHO_START);
  integrator.set_f(f[0]);
  integrator.set_max_dt(MAX_DT);
  integrator.set_relative_error_factor(RELATIVE_ERROR_FACTOR);
  integrator.set_t0(T_0);

  cout << "Let's simulate a multi-regime universe!\n"
       << "We assume that:\n"
       << "\tt_0 = " << T_0 << "\n"
       << "\ta(t_0) = " << A_0 << "\n"
       << "\trho(t_0) = " << RHO_START << "."
       << endl;

  for (int i = 0; i < NUM_STARTING_CONDITIONS; i++) {
    cout << "-------------------------------------------------------\n"
	 << "We now simulate " << NAME_STRINGS[i] << "."
	 << endl;
    integrator.set_f(f[i]);
    integrator.set_y0(y0);
    integrator.reset();
    outfile_name = DATA_FILE_START + NAME_STRINGS[i] + DATA_FILE_END;
    cout << "Working..." << endl;
    integrator.integrate(MAX_T);
    cout << "Finished! Saving to file " << outfile_name << "." << endl;
    print_simulation(integrator,&outfile_name[0],omega[i]);
    cout << "-------------------------------------------------------\n"
	 << endl;
  }

  cout << "And we're all done!\n"
       << "Have a nice day!"
       << endl;

  return 0;
}
// ----------------------------------------------------------------------

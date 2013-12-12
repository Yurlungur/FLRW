// flrw_test_driver.cpp

// Author: Jonah Miller (jonah.maxwell.miller@gmail.com)
// Time-stamp: <2013-12-12 17:21:27 (jonah)>

// This is the unit test driver for the FLRW library.


// Includes
#include "flrw.hpp"
#include <iostream>
#include <cmath>
using namespace std;


// ----------------------------------------------------------------------
double omega_1(double rho) {
  return 1.0;
}
// ----------------------------------------------------------------------


// ----------------------------------------------------------------------
int main() {
  cout << "-------------------------------------------------------\n"
       << "This is the unit test driver for the FLRW library.\n"
       << "Note that we have set:\n"
       << "\tK = " << K << "\n"
       << "\tLAMBDA = " << LAMBDA << ".\n"
       << "Beginning test.\n"
       << "-------------------------------------------------------"
       << endl;

  cout << "\n"
       << "-------------------------------------------------------\n"
       << "Making test dVector. It will contain a and b."
       << endl;
  dVector y;
  y.push_back(0.1);
  y.push_back(0.1);
  cout << "Vector is: " << y << "." << endl;
  cout << "-------------------------------------------------------"
       << endl;

  cout << "\n"
       << "-------------------------------------------------------\n"
       << "Testing the eval_func method by applying the pow\n"
       << "function to the vector.\n"
       << "We expect the result to be: 1.\n"
       << "The result is: " << eval_func(pow,y) << ".\n"
       << "-------------------------------------------------------"
       << endl;

  cout << "\n"
       << "-------------------------------------------------------\n"
       << "Testing the get_prime methods. Still assuming omega = 1."
       << endl;
  double a_prime = get_a_prime(y);
  double rho_prime = get_rho_prime(omega_1,y[0],y[1]);
  dVector y_prime = get_y_prime(omega_1,y);
  cout << "\ta_prime = " << a_prime << "\n"
       << "\trho_prime = " << rho_prime << "\n"
       << "\ty_prime = " << y_prime << ".\n"
       << "-------------------------------------------------------"
       << endl;

  cout << "\n"
       << "-------------------------------------------------------\n"
       << "This concludes the test. Thanks for reading.\n"
       << "-------------------------------------------------------"
       << endl;

  return 0;
}
// ----------------------------------------------------------------------

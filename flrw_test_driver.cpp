// flrw_test_driver.cpp

// Author: Jonah Miller (jonah.maxwell.miller@gmail.com)
// Time-stamp: <2013-12-11 17:49:52 (jonah)>

// This is the unit test driver for the FLRW library.


// Includes
#include "flrw.hpp"
#include <iostream>
#include <cmath>
using namespace std;


// ----------------------------------------------------------------------
double omega_1(double rho) {
  return 1;
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
  y.push_back(1);
  y.push_back(2);
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
       << "Testing the get p and rho methods. Assuming omega = 1."
       << endl;
  double rho = get_rho(y);
  cout << "\trho = " << rho << "\n"
       << "\tp = " << get_p(omega_1,rho) << ".\n"
       << "-------------------------------------------------------"
       << endl;

  cout << "\n"
       << "-------------------------------------------------------\n"
       << "Testing the get_prime methods. Still assuming omega = 1."
       << endl;
  double a_prime = get_a_prime(y);
  double b_prime = get_b_prime(omega_1,y);
  dVector y_prime = get_y_prime(omega_1,y);
  cout << "\ta_prime = " << a_prime << "\n"
       << "\tb_prime = " << b_prime << "\n"
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

// flrw.hpp

// Author: Jonah Miller (jonah.maxwell.miller@gmail.com)
// Time-stamp: <2013-12-14 00:24:48 (jonah)>

// This is the prototype and header file for the program that uses
// Runge-Kutta methods to numerically explore
// Friedmann-Lemaitre-Robertson-Walker metrics.

// Background
// ----------------------------------------------------------------------
// See the included pdf or latex file.
// ----------------------------------------------------------------------


// Dependencies
// ----------------------------------------------------------------------
// This program depends on the RKF45 package I wrote, which is an
// implementation of a fourth-order Runge-Kutte Fehlberg integration
// scheme. If you don't have it, you can find it here:
// https://github.com/Yurlungur/runge_kutta
// ----------------------------------------------------------------------


// Usage
// ----------------------------------------------------------------------
// STUB
// ----------------------------------------------------------------------


// Include guard
#pragma once
// Includes
#include "rkf45.hpp"
#include <iostream>


// Global constants
// ----------------------------------------------------------------------
const int K = 0; // The normalized curvature. We include it for
		 // completeness.
const double LAMBDA = 0; // The cosmological constant if we choose to
			 // add it.
// ----------------------------------------------------------------------


// Utility Functions
// ----------------------------------------------------------------------
// Evaluates a function func that takes in two doubles on the state
// vector y. y = [a,b], where a is the scale factor and b is the
// derivative of the scale factor.
double eval_func(double (*func)(double,double), const dVector& y);
// ----------------------------------------------------------------------


// The iteration function
// ----------------------------------------------------------------------
// Gets the pressure as a function of energy density and equation of
// state variable omega. The equation of state variable is assumed to
// be some function of rho.
double get_p(double (*omega)(double), double rho);

// Gets the derivative of the scale factor. Takes scale factor and
// derivative. Mostly for clarity... since the answer is obvious.
double get_a_prime(double a, double rho);
// Finds a' given the state vector y = [a,rho]
double get_a_prime(const dVector& y);

// Gets the derivative of rho
double get_rho_prime(double (*omega)(double),double a, double rho);

// The function for iterating through time steps. y' = f(y). We call
// this method get_y_prime to indicate that it also takes the equation
// of state function omega. The user must specify omega and define a
// new function to feed into the runge-kutta integrator. However, this
// method should help.
dVector get_y_prime(double (*omega)(double), const dVector& y);

// ----------------------------------------------------------------------


// Output
// ----------------------------------------------------------------------
// Overload the stream input operator to print an input dVector. If
// you print the fields on a grid, this will look pretty bad.
std::ostream& operator<< (std::ostream& out, const dVector& in);

// Prints a nicely formatted data set for the simulation to the output
// stream out. Takes the equation of state function to plot that too.
void print_simulation(const RKF45& simulation, std::ostream& out,
		      double (*omega)(double));
// Takes a filename instead of a string.
void print_simulation(const RKF45& simulation, const char* filename,
		      double (*omega)(double));
// ----------------------------------------------------------------------

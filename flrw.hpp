// flrw.hpp

// Author: Jonah Miller (jonah.maxwell.miller@gmail.com)\
// Time-stamp: <2013-12-11 03:02:28 (jonah)>

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

// Gets the energy density rho as a function of the scale factor a
// and its derivative b.
double get_rho(double a, double b);
// Finds rho given the state vector y = [a,b]
double get_rho(const dVector& y);

// Gets the derivative of the scale factor. Takes scale factor and
// derivative. Mostly for clarity... since the answer is obvious.
double get_a_prime(double a, double b);
// Finds a' given the state vector y = [a,b]
double get_a_prime(const dVector& y);

// Gets the value of the second derivative of the scale factor, a'' =
// b'. Technically a function of a and b, but the equation of state
// function must be defined too.
double get_b_prime(double (*omega)(double), double a, double b);
// Finds b' given the state vector y = [a,b]
double get_b_prime(double (*omega)(double), const dVector& y);

// ----------------------------------------------------------------------

#!/usr/bin/env python2

# Author: Jonah Miller (jonah.maxwell.miller@gmail.com)
# Time-stamp: <2013-12-12 17:28:32 (jonah)>

# This is a companion program to my FLRW simulator. It takes a data
# file and generates a plot of the scale factor, its derivative, the
# density, and the pressure of the matter.
# Call the program  with
# python2 plot_all_variables.py filename.dat

# Imports
# ----------------------------------------------------------------------
import numpy as np
import scipy as sp
import matplotlib as mpl
import matplotlib.pyplot as plt
import sys, os
# ----------------------------------------------------------------------


# Parameters for plots
# ----------------------------------------------------------------------
xlabel = "Cosmological time. (geometrized units)"
my_linewidth = 5
fontsize = 20
# ----------------------------------------------------------------------


def load_data(filename):
    """
    Takes a file name as a string and extracts the simulation data
    from it. Returns a tuple of arrays:
    (times,a_values,b_values,rho_values,p_values)
    """
    with open(filename,'r') as f:
        data = np.loadtxt(filename).transpose()
    times = data[0]
    a_values = data[1]
    rho_values = data[2]
    p_values = data[3]
    return times,a_values,rho_values,p_values

def plot_data(times,a_values,rho_values,p_values):
    """
    Takes the times,a_values,b_values,rho_values, and p_values
    and makes a nice plot out of them. Takes labels, etc. into account.
    """
    mpl.rcParams.update({'font.size': fontsize})
    lines = [plt.plot(times,y_set,linewidth=my_linewidth)
             for y_set in [a_values,rho_values,p_values]]
    plt.legend(["a",r'$\rho$',"p"])
    plt.xlabel(xlabel)
    plt.show()
    return

def plot_file(filename):
    "Plots the data in a file."
    times,a_values,rho_values,p_values = load_data(filename)
    plot_data(times,a_values,rho_values,p_values)
    return

if __name__ == "__main__":
    for filename in sys.argv[1:]:
        plot_file(filename)

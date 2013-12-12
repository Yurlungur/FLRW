#!/usr/bin/env python2

# Author: Jonah Miller (jonah.maxwell.miller@gmail.com)
# Time-stamp: <2013-12-12 17:39:42 (jonah)>

# This is a companion program to my FLRW simulator. It takes any
# number of data files and generates a plot of all the scale factors
# and their derivatives.
# Call the program with
# python2 plot_scale_factor.py datafile1.dat datafile2.dat datafile3.dat

# Imports
# ----------------------------------------------------------------------
import numpy as np
import scipy as sp
import matplotlib as mpl
import matplotlib.pyplot as plt
import plot_all_variables as pav
import sys,os
# ----------------------------------------------------------------------


def plot_scale_factors(time_list,scale_factor_list,initial_rho_list):
    """
    Takes two lists. One a list of arrays of times. Another a list of
    arrays scale factors Plots scale factors as a function of
    time. All on the same plot.

    Assumes that time_list and scale_factor_list are same length.

    initial_b_list is for the plot legend.
    """
    mpl.rcParams.update({'font.size': pav.fontsize})
    lines = [plt.plot(time_list[i],scale_factor_list[i],
                      linewidth=pav.my_linewidth)
             for i in range(len(time_list))]
    plt.legend([str(rho) for rho in initial_rho_list])
    plt.xlabel(pav.xlabel)
    plt.show()
    return

def sort_lists(time_list,scale_factor_list,initial_rho_list):
    """
    Takes the lists and sorts them based on the initial_b_list.
    """
    RHO_MAP = {initial_rho_list[i] : (time_list[i],scale_factor_list[i])
             for i in range(len(initial_rho_list))}
    initial_rho_list.sort()
    time_list = [RHO_MAP[rho][0] for rho in initial_rho_list]
    scale_factor_list = [RHO_MAP[rho][1] for rho in initial_rho_list]
    return time_list,scale_factor_list,initial_rho_list

if __name__ == "__main__":
    time_list = []
    scale_factor_list = []
    initial_rho_list = []
    for filename in sys.argv[1:]:
        times,a_values,rho_values,p_values = pav.load_data(filename)
        time_list.append(times)
        scale_factor_list.append(a_values)
        initial_rho_list.append(rho_values[0])
    time_list,scale_factor_list,initial_rho_list = sort_lists(time_list,
                                                            scale_factor_list,
                                                            initial_rho_list)
    plot_scale_factors(time_list,scale_factor_list,initial_rho_list)
    

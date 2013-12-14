#!/usr/bin/env python2
# multi-regime.py

# Author: Jonah Miller (jonah.maxwell.miller@gmail.com)
# Time-stamp: <2013-12-14 16:06:28 (jonah)>

# This is a library to plot and fit for omega(rho) variable. We choose
# omega so that we get the three distinct regimes for which we know
# the analytic solution with continuous transition regions.

# Imports
# ----------------------------------------------------------------------
import numpy as np
import matplotlib as mpl
import matplotlib.pyplot as plt
import plot_all_variables as pav
from scipy.special import erf
# ----------------------------------------------------------------------

# Constants
# ----------------------------------------------------------------------
RHO_MIN=0
OMEGA_MIN = -1
ERF_MIN = -1
RHO_DARK_ENERGY = [10,20,25,37]
RHO_MATTER = [20,40,80,92]
RHO_RADIATION = 200
TRANSITION_WIDTH_DE=[1,5,12,20]
TRANSITION_WIDTH_MR=[1,5,12,20]
NUM_ERFS = 2
DE_AMPLITUDE = 1.0/2.0
MATTER_AMPLITUDE = (1.0/3.0)* DE_AMPLITUDE
XLABEL=r'$\rho$'
YLABEL=r'$\omega$'
# ----------------------------------------------------------------------

def omega(rho,
          rho_dark_energy,transition_width_de,
          rho_matter,transition_width_mr):
    return OMEGA_MIN \
        + DE_AMPLITUDE + MATTER_AMPLITUDE\
        + DE_AMPLITUDE*erf((rho - rho_dark_energy)/transition_width_de)\
        + MATTER_AMPLITUDE*erf((rho - rho_matter)/transition_width_mr)

def plot_rho():
    mpl.rcParams.update({'font.size': pav.fontsize})
    x = np.linspace(0,RHO_RADIATION,100)
    ys = [omega(x,RHO_DARK_ENERGY[i],TRANSITION_WIDTH_DE[i],
                RHO_MATTER[i],TRANSITION_WIDTH_MR[i]) for i in range(len(RHO_DARK_ENERGY))]
    lines = [plt.plot(x,y,linewidth=pav.my_linewidth) for y in ys]
    plt.axis([RHO_MIN,RHO_RADIATION,
              1.1*OMEGA_MIN,
              1.1*(OMEGA_MIN + 2*(DE_AMPLITUDE + MATTER_AMPLITUDE))])
    plt.xlabel(XLABEL)
    plt.ylabel(YLABEL)
    plt.legend(["Abrupt transition",
                "Moderate transition",
                "Mild transition",
                "No well-defined regimes"],
               loc=4)
    plt.show()
    return

if __name__ == "__main__":
    plot_rho()

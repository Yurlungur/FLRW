# multi-regime.py

# Author: Jonah Miller (jonah.maxwell.miller@gmail.com)
# Time-stamp: <2013-12-14 12:47:37 (jonah)>

# This is a library to plot and fit for omega(rho) variable. We choose
# omega so that we get the three distinct regimes for which we know
# the analytic solution with continuous transition regions.

# Imports
# ----------------------------------------------------------------------
import numpy as np
import plot_all_variables_as_pav
from scipy.special import erf
# ----------------------------------------------------------------------

# Constants
# ----------------------------------------------------------------------
RHO_MIN = 1
ERF_MIN = -1
RHO_DARK_ENERGY = 0.1
RHO_MATTER = 32
RHO_RADIATION = 256
TRANSITION_WIDTH_DE=1
TRANSITION_WIDTH_MR=1
NUM_ERFS = 2
XLABEL=r'$\rho$'
YLABEL=r'$\omega$'
# ----------------------------------------------------------------------

def omega(rho):
    return RHO_MIN \
        - NUM_ERFS * ERF_MIN \
        + erf((x-RHO_DARK_ENERGY)/TRANSITION_WIDTH_DE)\
        + erf((x-RHO_MATTER)/TRANSITION_WIDTH_MR)

def plot_rho():
    mpl.rcParams.update({'font.size': pav.fontsize})
    x = np.linspace(0,RHO_RADIATION,100)
    y = omega(x)
    plt.plot(x,y,linewidth=pav.my_linewidth)
    plt.xlabel(XLABEL)
    plt.ylabel(YLABEL)
    plt.show()
    return

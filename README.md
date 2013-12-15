======================================================================
                               FLRW:
A numerical exploration of Friedmann-Lemaitre-Robertson-Walker Metrics
======================================================================
Author: Jonah Miller (jonah.maxwell.miller@gmail.com)
Time-stamp: <2013-12-14 21:56:46 (jonah)>

                         INTRODUCTION
----------------------------------------------------------------------
This is my program to numerically solve for homogeneous, isotropic
solutions to Einstein's equations. To this end, I assume the
Friedmann-Lemaitre-Robertson-Walker metric and numerically solve the
Friedmann eqautons (see, e.g., Wald, or just look at Wikipedia:
https://en.wikipedia.org/wiki/Friedmann_equations).

For a brief derivation of the equations I solve, see the included pdf
file. I use my implementation for the 4(5) Runge-Kutta-Fehlberg method
with adaptive step sizes. The required libraries should be included in
the github repository. However, if you want to play with my RKF
integrator all by itself, you can find it here:
https://github.com/Yurlungur/runge_kutta
----------------------------------------------------------------------

                    INSTALLATION and USE
----------------------------------------------------------------------
This program uses the linux make utility for installation and
configuration. It is not configured for Windows, allthough it could
probably be easily modified ot run in that environment.

There are a number of small, pre-configured programs
that use the main libraries that you can build to run a
simulation. Here are the commands:

make test --- This makes a unit test driver for the libraries
              in question.
make radiation_dominated_universe --- Simulate a universe filled
                                      mostly with photons. This
				      matches the state of the
				      universe right after reheating
				      (or the big bang).
make matter_dominated_universe --- Simulate a universe filled with
     			       	   non-interacting dust, much like the
				   stars and galaxies that fill the
				   universe today.
make dark_energy_dominated_universe --- Simulate the universe as it
     				    	would be if only dark energy
					filled the universe. It is
					likely the universe will look
					like this in the far future.
make multi-regime --- Simulate the universe as it transitions from
     		      radiation-dominated to matter-dominated to
		      dark energy-dominated. We examine four possible
		      ways the universe could transition by selecting
		      an equation of state relating density and pressure
		      of matter in the universe.
make our_future_universe --- Recent experiments show
     			     (http://www.scientificamerican.com/article.cfm?id=dark-energy-cosmological-constant&page=2)
     			     that the universe may have an equation
			     of state variable omega(rho) equal to -1.2.
			     The type of matter required to create this is
			     strange indeed. It doesn't dilute. Rather
			     energy density increases as the scale
			     factor increases. This simulation explores
			     that possibility.
make all --- Generates all of the above simulations
make clean --- Cleans the directory, removing all binary files.

Once you've run make, you should have a *.bin file in your
directiory. execute it with
chmod a+x *.bin
./<file name>.bin

The program will then run a number of simulations and output a number
of data files ending in *.dat. Each file has three columns, each line
is one time step. They show the following quantities:
time a(t) rho(t) p(t)

You can plot these quantities with four convenient python programs
included, which require python 2.7, numpy, scipy, and matplotlib. Call
them with
python2 program.py filename1.dat filename2.dat
they can take an arbitrary number of files.

The python programs:
plot_scale_factor.py --- plots the scale factor as a function of
		     	 time for each included *.dat file
plot_all_variables.py --- plots a(t),rho(t), and p(t) on the same
		      	  plot.
plot_all_variables_big_a.py --- The same as plot_all_variables.py
                                but a(t) has been rescaled for easier
				viewing.
MultiRegime.py --- Plots omega(rho) for every equation of state used
	       	   in the multi-regime simulation. Takes no input
		   data.
----------------------------------------------------------------------

                     PHYSICS DETAILS
----------------------------------------------------------------------
We use geometrized units, which means that c=G=hbar=1.
The scale factor is not normalized. It has no absolute meaning.

Although the cosmological constant LAMBDA can be set to a non-zero
value, this is not recomended. The preferred way to include a
cosmological constant is manipulate the equation of state function
omega(rho). A constant value of -1.0 corresponds to a positive
cosmological constant.

A nonzero curvature can be included by setting K=-1 or K=+1. This sets
the normalized curvature to a negative or positive value
respectively. However, this feature is untested. Treat it with
caution.
----------------------------------------------------------------------

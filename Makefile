# Makefile for the FLRW package
# Author: Jonah Miller (jonah.maxwell.miller@gmail.com)
# Time-stamp: <2013-12-14 14:21:02 (jonah)>

# The default compiler is g++
CXX = g++

# Flags for the compiler. Ask for warnings. Enable the debugger.
CXXFLAGS = -Wall -g

default: multi-regime
all: test radiation_dominated_universe matter_dominated_universe dark_energy_dominated_universe our_future_universe multi-regime

multi-regime: multi-regime.bin
multi-regime.bin: multi-regime.o flrw.o rkf45.o
	$(CXX) $(CXXFLAGS) -o $@ $^
multi-regime.o: rkf45.hpp flrw.hpp

our_future_universe: our_future_universe.bin
our_future_universe.bin: our_future_universe.o flrw.o rkf45.o
	$(CXX) $(CXXFLAGS) -o $@ $^
our_future_universe.o: rkf45.hpp flrw.hpp

dark_energy_dominated_universe: dark_energy_dominated_universe.bin
dark_energy_dominated_universe.bin: dark_energy_dominated_universe.o flrw.o rkf45.o
	$(CXX) $(CXXFLAGS) -o $@ $^
dark_energy_dominated_universe.o: rkf45.hpp flrw.hpp

matter_dominated_universe: matter_dominated_universe.bin
matter_dominated_universe.bin: matter_dominated_universe.o flrw.o rkf45.o
	$(CXX) $(CXXFLAGS) -o $@ $^
matter_dominated_universe.o: rkf45.hpp flrw.hpp

radiation_dominated_universe: radiation_dominated_universe.bin
radiation_dominated_universe.bin: radiation_dominated_universe.o flrw.o rkf45.o
	$(CXX) $(CXXFLAGS) -o $@ $^
radiation_dominated_universe.o: rkf45.hpp flrw.hpp

test: flrw_test_driver
flrw_test_driver: flrw_test_driver.bin
flrw_test_driver.bin: flrw.o flrw_test_driver.o rkf45.o
	$(CXX) $(CXXFLAGS) -o $@ $^
flrw_test_driver.o: flrw.hpp rkf45.hpp

flrw.o: flrw.hpp rkf45.hpp
rkf45.o: rkf45.hpp

.PHONY: default all test flrw_test_driver radiation_dominated_universe matter_dominated_universe dark_energy_dominated_universe our_future_universe multi-regime	

clean:
	$(RM) rkf45.o flrw.o flrw_test_driver.bin flrw_test_driver.o radiation_dominated_universe.bin radiation_dominated_universe.o matter_dominated_universe.bin matter_dominated_universe.o dark_energy_dominated_universe.o dark_energy_dominated_universe.bin our_future_universe.o our_future_universe.bin multi-regime.bin multi-regime.o multi-regime.bin
# Makefile for the FLRW package
# Author: Jonah Miller (jonah.maxwell.miller@gmail.com)
# Time-stamp: <2013-12-11 20:09:54 (jonah)>

# The default compiler is g++
CXX = g++

# Flags for the compiler. Ask for warnings. Enable the debugger.
CXXFLAGS = -Wall -g

default: radiation_dominated_universe
all: test radiation_dominated_universe

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

.PHONY: default all test flrw_test_driver radiation_dominated_universe

clean:
	$(RM) rkf45.o flrw.o flrw_test_driver.bin flrw_test_driver.o radiation_dominated_universe.bin radiation_dominated_universe.o
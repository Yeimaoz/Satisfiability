# A template C++ Makefile for your SAT solver.
MAKE = make

# Using c++ compiler
CXX = g++

# Debugging flags
#FLAGS=-Wall -Wold-style-cast -Wformat=2 -ansi -pedantic -ggdb3 \
-DDEBUG
# Optimizing flags
CXXFLAGS = -Wall -Wold-style-cast -Wformat=2 -ansi -pedantic -O3

# Source files destination
SRC ?= src

# Object files destination
BUILDDIR ?= build

# List all the .o files you need to build here
OBJS = parser.o sat.o

# This is the name of the executable file that gets built.  Please
# don't change it.
EXENAME=solver


all: $(BUILDDIR) $(BUILDDIR)/$(EXENAME)

# Compile %.cpp file to %.o
$(BUILDDIR)/%.o: $(SRC)/%.cpp
	$(CXX) $< -c -o $@

# Compile the execution file with all objs
build/$(EXENAME): $(foreach objs, $(OBJS), $(BUILDDIR)/$(objs))
	$(CXX) $(CXXFLAGS) $^ -o $@

# New a build directory
$(BUILDDIR): 
	mkdir -p $@

# The "phony" `clean' compilation target.  Type `make clean' to remove
# your object files and your executable.
.PHONY: clean
clean:
	rm -rf $(BUILDDIR) $(EXENAME)

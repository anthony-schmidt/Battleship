# This is the Makefile for our final project

# Software Engineers:
# Daniel Schermerhorn - dscherme@nd.edu
# Landon Bachman - lbachma2@nd.edu 
# David Chirumbole - dchirumb@nd.edu
# Anthony Schmidt - aschmi25@nd.edu

# Project Manager:
# Kaiwen Dong - kdong2@nd.edu

# Project Director
# Matthew Morrison, Assistant Teaching Professor, University of Notre Dame, matt.morrrison@nd.edu

# G++ is for the GCC compiler for C++
PP := g++

# CFLAGS
FLAGS := -O2 -g -Wall -Wextra -Wconversion -Wshadow -pedantic -Werror -lm
CXXFLAGS := -m64 -std=c++11 -Weffc++ $(FLAGS)

# Folder Variables
INC := inc
SRC := src
OBJ := obj
EXE := exe


$(OBJ)/battleship.o: $(SRC)/battleship.cpp
	$(PP) $(CXXFLAGS) -c $(SRC)/battleship.cpp -o $@

$(OBJ)/battlefunc.o: $(SRC)/battlefunc.cpp
	$(PP) $(CXXFLAGS) -c $(SRC)/battlefunc.cpp -o $@

$(OBJ)/algorithm.o: $(SRC)/algorithm.cpp
	$(PP) $(CXXFLAGS) -c $(SRC)/algorithm.cpp -o $@

battleship: $(OBJ)/battleship.o $(OBJ)/battlefunc.o $(OBJ)/algorithm.o
	$(PP) $(CXXFLAGS) $(OBJ)/battleship.o $(OBJ)/battlefunc.o $(OBJ)/algorithm.o -o $(EXE)/battleship 

#battleship: $(OBJ)/battleship.o $(OBJ)/battlefunc.o
#	$(PP) $(CXXFLAGS) $(OBJ)/battleship.o $(OBJ)/battlefunc.o -o $(EXE)/battleship 

all: battleship


# Make initialize
initialize:
	rm -rf $(OBJ) $(EXE)
	mkdir $(OBJ) $(EXE)

# clean
clean :
	rm -rf $(OBJ)/* $(EXE)/* *.o

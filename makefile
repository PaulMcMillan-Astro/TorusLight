################################################################################
#
# Makefile for the torus project
#
# written by Walter Dehnen at Oxford University, 1995-97
#            Paul McMillan thereafter
# address: Theoretical Physics, 1 Keble Road, Oxford OX1 3NP, UK
# e-mail:  w.dehnen1.physics.oxford.ac.uk
#
################################################################################

all: mains


#
# MACRO DEFINITIONS that depend on the archetcture
#
# directories
INC		= src/
SRC		= src/
SRCPOT		= src/pot/
SRCUTILS	= src/utils/
EXE		= ${SRC}mains/
OBJ		= obj/
BIN		= bin/
INCL		= src/utils/
LIB		= obj/


# Compiler
CPP	= g++

# flags for compiler for optimized & debug code
CFLAGS 	= -c -o $@ -O3 -ffast-math -I$(INC) -I$(SRCPOT) -I$(SRCUTILS)
CFLAGS_WD = -c -o $@ -O3 -ffast-math -I$(SRCUTILS)
MFLAGS	= -O3 -ffast-math -I$(INC) -I$(SRCPOT) -I$(INCL)

# flags for linker for optimized & debug code
LDFLAGS     =  -o $(BIN)$@ -L$(LIB) -lTorus -lPot -lOther -lWD -lm


# commands to put file into library
AR            = ar r
RL            = ranlib

#
# include the macro definitions, dependencies, and rules that are
# unspecific to the machine used
#

include	make.torus

clean:
	- rm -rf obj/* lib/* bin/* *~ src/*~ src/mains/*~ \
	src/pot/*~ src/utils/*~

halfclean:
	- rm -rf obj/* lib/* bin/* 

################################################################################

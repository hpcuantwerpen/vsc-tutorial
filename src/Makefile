# Makefile for the Tutorial examples.
# The Makefile should be compatible with EasyBuild when compiled without 
# MPI and OpenMP enabled, tough you will need to define OMPFLAG as the option
# that should be passed to the compiler to compile with OpenMP.
#
# IMPORTANT: Run with make -R (or make --no-builtin-variables) if CC etc are 
# not defined in the environment or the make command line as otherwise the 
# built-in values will be used rather than the defaults given below.
#

CC      ?= icc
MPICC   ?= mpiicc
CFLAGS  ?= -O2 -xHost
OMPFLAG ?= -qopenmp

.SUFFIXES:

examples : bindir \
		   ../bin/omp_hello ../bin/mpi_hello ../bin/mpi_omp_hello \
		   ../bin/eat_mem

clean : 
	-/bin/rm ../bin/*
	
bindir :
	-mkdir ../bin

omp_hello : ../bin/omp_hello
../bin/omp_hello : omp_hello.c
	$(CC) $(CFLAGS) $(OMPFLAG) $< -o $@

mpi_hello : ../bin/mpi_hello
../bin/mpi_hello : mpi_hello.c
	$(MPICC) $(CFLAGS) $< -o $@

mpi_omp_hello : ../bin/mpi_omp_hello
../bin/mpi_omp_hello : mpi_omp_hello.c
	$(MPICC) $(CFLAGS) $(OMPFLAG) $< -o $@

eat_mem : ../bin/eat_mem
../bin/eat_mem : eat_mem.c
	$(CC) $(CFLAGS) $< -o $@

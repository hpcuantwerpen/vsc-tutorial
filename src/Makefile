# Makefile for the Tutorial examples.
# The Makefile should be compatible with EasyBuild when compiled without 
# MPI and OpenMP enabled, tough you will need to define OMPFLAG as the option
# that should be passed to the compiler to compile with OpenMP.
#
# IMPORTANT: Run with make -R (or make --no-builtin-variables) if CC etc are 
# not defined in the environment or the make command line as otherwise the 
# built-in values will be used rather than the defaults given below.
#
# Note: Preprocessor macros that can be defined:
#  * DEBUG: Prints some debug information in hybrid_hello.
#  * HAVE_NUMALIB: Define this if the system has libnuma (relevant for
#    hybrid_hello)
#
# Build examples:
# make examples CC=icc MPICC=mpiicc CFLAGS=-O0 OMPFLAG=-qopenmp DEFINES=-DHAVE_NUMALIB LIBS=-lnuma
#

CC      ?= icc
MPICC   ?= mpiicc
CFLAGS  ?= -O2 -xHost
OMPFLAG ?= -qopenmp
DEFINES ?= -DHAVE_NUMALIB
#DEFINES ?= -DHAVE_NUMALIB -DDEBUG
LIBS    ?= -lnuma

.SUFFIXES:

examples : config bindir \
	       ../bin/serial_check ../bin/omp_check ../bin/mpi_check ../bin/mpi_omp_check \
		   ../bin/serial_hello ../bin/omp_hello ../bin/mpi_hello ../bin/mpi_omp_hello \
		   ../bin/eat_mem   ../bin/eat_cpu   ../bin/eat_disk

clean : 
	-/bin/rm ../bin/*
	
bindir :
	-mkdir -p ../bin
	
config :
	@echo -e
	@echo -e "C compiler:               " $(CC)
	@echo -e "MPI C compiler:           " $(MPICC)
	@echo -e "Compiler flags:           " $(CFLAGS)
	@echo -e "OpenMP flag:              " $(OMPFLAG)
	@echo -e "Preprocessor definitions: " $(DEFINES)
	@echo -e "Additional libraries:     " $(LIBS)
	@echo -e

#
# Simple hello world style programs,
# separate source for each for increased readability.
#

serial_hello : ../bin/serial_hello
../bin/serial_hello : serial_hello.c Makefile
	$(CC) $(CFLAGS) $(OMPFLAG) $< -o $@

omp_hello : ../bin/omp_hello
../bin/omp_hello : omp_hello.c Makefile
	$(CC) $(CFLAGS) $(OMPFLAG) $< -o $@

mpi_hello : ../bin/mpi_hello
../bin/mpi_hello : mpi_hello.c Makefile
	$(MPICC) $(CFLAGS) $< -o $@

mpi_omp_hello : ../bin/mpi_omp_hello
../bin/mpi_omp_hello : mpi_omp_hello.c Makefile
	$(MPICC) $(CFLAGS) $(OMPFLAG) $< -o $@

#
# Cray acheck-like programs, common source to not have
# to maintain multiple very similar versions.
#

serial_check : ../bin/serial_check
../bin/serial_check : hybrid_check.c Makefile
	$(CC) $(CFLAGS) $(DEFINES) $(LIBS) $< -o $@

omp_check : ../bin/omp_check
../bin/omp_check : hybrid_check.c Makefile
	$(MPICC) $(CFLAGS) $(OMPFLAG) $(DEFINES) -DWITH_OMP $(LIBS) $< -o $@

mpi_check : ../bin/mpi_check
../bin/mpi_check : hybrid_check.c Makefile
	$(MPICC) $(CFLAGS) $(OMPFLAG) $(DEFINES) -DWITH_MPI $(LIBS) $< -o $@

mpi_omp__check : ../bin/mpi_omp__check
../bin/mpi_omp_check : hybrid_check.c Makefile
	$(MPICC) $(CFLAGS) $(OMPFLAG) $(DEFINES) -DWITH_MPI -DWITH_OMP $(LIBS) $< -o $@

#
# Testing memory, CPU and disk load
#

eat_mem : ../bin/eat_mem
../bin/eat_mem : eat_mem.c Makefile
	$(CC) $(CFLAGS) $< -o $@

eat_cpu : ../bin/eat_cpu
../bin/eat_cpu : eat_cpu.c Makefile
	$(CC) $(CFLAGS) $< -o $@

eat_disk : ../bin/eat_disk
../bin/eat_disk : eat_disk.c Makefile
	$(CC) $(CFLAGS) $< -o $@

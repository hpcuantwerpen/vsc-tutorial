#! /bin/bash
#PBS -L tasks=40:lprocs=1:swap=1gb
#PBS -l walltime=5:00
#PBS -N MPI-hello-test

cd $PBS_O_WORKDIR

module load calcua/supported
module load vsc-tutorial/201810-intel-2018b

mpirun mpi_hello

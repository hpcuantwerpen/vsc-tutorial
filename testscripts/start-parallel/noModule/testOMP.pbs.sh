#! /bin/bash
#PBS -L tasks=1:lprocs=7:swap=4gb
#PBS -l walltime=5:00
#PBS -N omp-hello-test

cd $PBS_O_WORKDIR

module load $VSC_INSTITUTE_CLUSTER/supported
module load intel/2018a
module load torque-tools

export OMP_NUM_THREADS=$(torque-lprocs 0)
../../../bin/omp_hello

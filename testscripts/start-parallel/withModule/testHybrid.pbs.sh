#! /bin/bash
#PBS -L tasks=8:lprocs=7:swap=4gb
#PBS -l walltime=5:00
#PBS -N hybrid-hello-test

cd $PBS_O_WORKDIR

module load $VSC_INSTITUTE_CLUSTER/supported
module load vsc-tutorial/201810-intel-2018b
module load torque-tools

export OMP_NUM_THREADS=$(torque-lprocs 0)
torque-host-per-line >machinefile.$PBS_JOBID
mpirun -machinefile machinefile.$PBS_JOBID mpi_omp_hello
/bin/rm machinefile.$PBS_JOBID

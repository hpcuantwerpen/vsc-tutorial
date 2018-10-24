#!/bin/bash -l
# Example for qsub array jobs
#PBS -L tasks=1:lprocs=1:swap=512mb
#PBS -l walltime=00:15:00

cd $PBS_O_WORKDIR

INPUT_FILE="input_${PBS_ARRAYID}.dat"
OUTPUT_FILE="output_${PBS_ARRAYID}.dat"
./test_set ${PBS_ARRAYID} -input ${INPUT_FILE}  -output ${OUTPUT_FILE}

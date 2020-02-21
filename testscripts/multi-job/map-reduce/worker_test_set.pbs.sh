#!/bin/bash -l
#PBS -L tasks=28:lprocs=1:swap=1gb
#PBS -l walltime=04:00:00

cd $PBS_O_WORKDIR

INPUT_FILE="input_${PBS_ARRAYID}.dat"
OUTPUT_FILE="output_${PBS_ARRAYID}.dat"
./test_set ${PBS_ARRAYID} -input ${INPUT_FILE} -output ${OUTPUT_FILE}

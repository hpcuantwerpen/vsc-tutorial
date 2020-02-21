#!/bin/bash
# Example for sbatch array jobs
#SBATCH --ntasks=1 --cpus-per-task=1 --mem-per-cpu=512m
#SBATCH --time=5:00

INPUT_FILE="input_${SLURM_ARRAY_TASK_ID}.dat"
OUTPUT_FILE="output_${SLURM_ARRAY_TASK_ID}.dat"
./test_set ${SLURM_ARRAY_TASK_ID} -input ${INPUT_FILE}  -output ${OUTPUT_FILE}

#! /bin/bash
#
#SBATCH --ntasks=1 --cpus-per-task=1 --mem=512m
#SBATCH --time=1:00

INPUT_FILE="input_${SLURM_ARRAY_TASK_ID}.dat"
OUTPUT_FILE="output_${SLURM_ARRAY_TASK_ID}.dat"
./test_set ${SLURM_ARRAY_TASK_ID} -input ${INPUT_FILE} -output ${OUTPUT_FILE}
# Sleep can be added to better see what happens in the squeue
# (you'd never do that for a real job of course, this is only for the
# exercises)
sleep $(( 10 + $RANDOM % 5 ))

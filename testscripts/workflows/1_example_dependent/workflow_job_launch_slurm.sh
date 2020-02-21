#!/bin/bash

module purge
module load calcua/supported
module load personal
# We need to lad slurmtools for the jsbatch command which makes life a lot easier
# for this case.
module load slurm-tools

first=$(jsbatch --job-name=job_leader workflow_job_first.slurm.sh)
sbatch --job-name=job_mult_5  --export=ALL,multiplier=5  --dependency=afterok:$first workflow_job_depend.slurm.sh
sbatch --job-name=job_mult_10 --export=ALL,multiplier=10 --dependency=afterok:$first workflow_job_depend.slurm.sh

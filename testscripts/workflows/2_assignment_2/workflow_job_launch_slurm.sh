#!/bin/bash

module purge
module load calcua/supported
module load personal
# We need to lad slurmtools for the jsbatch command which makes life a lot easier
# for this case.
module load slurm-tools

first=$(jsbatch --job-name=job_sim1 workflow_job_first.slurm.sh)
second=$(jsbatch --job-name=job_sim2 --dependency=afterok:$first workflow_job_second.slurm.sh)
sbatch --job-name=job_pert_1 --export=ALL,perturbation=1 --dependency=afterok:$second workflow_job_perturbation.slurm.sh
sbatch --job-name=job_pert_2 --export=ALL,perturbation=2 --dependency=afterok:$second workflow_job_perturbation.slurm.sh

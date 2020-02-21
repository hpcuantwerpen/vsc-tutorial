#! /bin/bash -l

module load calcua/supported
module load personal
module load slurm-tools/develop

preproc=$(jsbatch atools-pre.slurm)
compute=$(jsbatch --array 1-100 --dependency=afterok:$preproc atools-run.slurm)
sbatch --dependency=afterok:$compute atools-reduce.slurm

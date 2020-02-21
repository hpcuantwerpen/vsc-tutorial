#! /bin/bash -l

module load calcua/supported
module load personal
module load slurm-tools/develop

preproc=$(jsbatch array-pre.slurm)
compute=$(jsbatch --array 1-100 --dependency=afterok:$preproc array-run.slurm)
sbatch --dependency=afterok:$compute array-reduce.slurm

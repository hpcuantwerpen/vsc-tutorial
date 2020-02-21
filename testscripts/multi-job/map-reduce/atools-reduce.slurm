#! /bin/bash
#SBATCH --ntasks=1 --cpus-per-task=1 --mem=1g
#SBATCH --time=5:00
#

module load calcua/supported
module load personal
module load atools/slurm

areduce -t $(arange -t 1-100 --log atools-run.slurm.log* --completed) --pattern 'output/output_{t}.dat' \
        --empty empty_body --reduce reduce_body --out all_output.txt

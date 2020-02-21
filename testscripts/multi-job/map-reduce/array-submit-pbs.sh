#! /bin/bash -l

preproc=$(qsub array-pre.pbs)
compute=$(qsub -t 1-100 -W depend=afterok:$preproc array-run.pbs)
qsub -W depend=afterany:$compute array-reduce.pbs

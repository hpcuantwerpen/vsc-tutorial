#!/bin/bash
first=$(qsub -N job_leader workflow_job_first.pbs.sh)
qsub -N job_mult_5  -v multiplier=5  -W depend=afterany:$first workflow_job_depend.pbs.sh
qsub -N job_mult_10 -v multiplier=10 -W depend=afterany:$first workflow_job_depend.pbs.sh

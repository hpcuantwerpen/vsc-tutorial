#!/bin/bash
first=$(qsub -N job_sim1 workflow_job_first.pbs.sh)
second=$(qsub -N job_sim2 -W depend=afterany:$first workflow_job_second.pbs.sh)
qsub -N job_pert_1 -v perturbation=1 -W depend=afterany:$second workflow_job_perturbation.pbs.sh
qsub -N job_pert_2 -v perturbation=2 -W depend=afterany:$second workflow_job_perturbation.pbs.sh

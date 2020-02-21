#! /bin/bash
#SBATCH --ntasks=1 --cpus-per-task=1 --mem=1g
#SBATCH --time=5:00
#

./post.sh
# Sleep can be added to better see what happens in the squeue
# (you'd never do that for a real job of course, this is only for the
# exercises)
sleep 20
        
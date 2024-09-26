#!/bin/bash
#SBATCH --job-name=nSRMT103HZ
#SBATCH --output=res_omp.txt
#SBATCH --error=err_omp.txt
##SBATCH --ntasks=1
#SBATCH --cpus-per-task=28
#SBATCH --time=3-0:5:0 #  2-0 #unlimited
export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK

# BCL (ms) 	
# num_of_beats (#)
# Tub 1: Dense 2: Intermediate 3: Sparse
# 0: nSR; 	1: cAF
# 0: male; 	1: female
time ./pace_2 1000 28 2 0 0
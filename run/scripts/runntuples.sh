#!/bin/bash

cd /disk0/QGjetsPetr/
source setup.sh
source aliases.sh
cd /disk0/QGjetsPetr/run/scripts/
for i in 900 2360 7000 13000; do
for j in 900 2360 7000 13000; do
if [[ j -gt i ]]; then
            #sbatch -n1 -o /disk0/QGjetsPetr/run/logs/job_ntuple_${i}_${j} ./runprod.sh $i $j              
            #sbatch -n1 -o /disk0/QGjetsPetr/run/logs/job_ntuple_noMPI_noISR_${i}_${j} ./runprod_noMPI_noISR.sh $i $j              
            #sbatch -n1 -o /disk0/QGjetsPetr/run/logs/job_ntuple_trim_${i}_${j} ./runprod_trim.sh $i $j              
            #sbatch -n1 -o /disk0/QGjetsPetr/run/logs/job_ntuple_trim_noMPI_noISR_${i}_${j} ./runprod_trim_noMPI_noISR.sh $i $j  
            sbatch -n1 -o /disk0/QGjetsPetr/run/logs/job_ntuple_pythia_${i}_${j} ./runprod_pythia.sh $i $j
            sbatch -n1 -o /disk0/QGjetsPetr/run/logs/job_ntuple_pythia_noMPI_noISR_${i}_${j} ./runprod_noMPI_noISR_pythia.sh $i $j
            sbatch -n1 -o /disk0/QGjetsPetr/run/logs/job_ntuple_trim_pythia_${i}_${j} ./runprod_trim_pythia.sh $i $j
            sbatch -n1 -o /disk0/QGjetsPetr/run/logs/job_ntuple_trim_pythia_noMPI_noISR_${i}_${j} ./runprod_trim_noMPI_noISR_pythia.sh $i $j

fi
done;
done;

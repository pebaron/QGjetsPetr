#!/bin/bash

cd /disk0/QGjetsPetr/
source setup.sh
source aliases.sh
cd /disk0/QGjetsPetr/run/scripts/
for i in 900 2360 7000 13000; do
for j in 900 2360 7000 13000; do
if [[ j -gt i ]]; then
           echo sbatch -n1 -o /disk0/QGjetsPetr/run/logs/job_ang_${i}_${j} ./runprodfinal.sh $i $j              
           echo sbatch -n1 -o /disk0/QGjetsPetr/run/logs/job_ang_NoMPI_NoISR_${i}_${j} ./runprodfinalNoMPINoISR.sh $i $j             
           echo sbatch -n1 -o /disk0/QGjetsPetr/run/logs/job_ang_trim_${i}_${j} ./runprodfinal_trim.sh $i $j              
           echo sbatch -n1 -o /disk0/QGjetsPetr/run/logs/job_ang_trim_NoMPI_NoISR_${i}_${j} ./runprodfinalNoMPINoISR_trim.sh $i $j             
           
           echo sbatch -n1 -o /disk0/QGjetsPetr/run/logs/job_ang_pythia_${i}_${j} ./runprodfinal_pythia.sh $i $j
           echo sbatch -n1 -o /disk0/QGjetsPetr/run/logs/job_ang_pythia_NoMPI_NoISR_${i}_${j} ./runprodfinalNoMPINoISR_pythia.sh $i $j

           echo sbatch -n1 -o /disk0/QGjetsPetr/run/logs/job_ang_trim_pythia_${i}_${j} ./runprodfinal_pythia_trim.sh $i $j
           echo sbatch -n1 -o /disk0/QGjetsPetr/run/logs/job_ang_trim_pythia_NoMPI_NoISR_${i}_${j} ./runprodfinalNoMPINoISR_pythia_trim.sh $i $j
 
fi
done;
done;

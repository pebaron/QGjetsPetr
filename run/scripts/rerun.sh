#!/bin/bash

sbatch -n1 -o /disk0/QGjetsPetr/run/logs/job_ang_900_2360 ./runprodfinal.sh 900 2360
sbatch -n1 -o /disk0/QGjetsPetr/run/logs/job_ang_NoMPI_NoISR_2360_7000 ./runprodfinalNoMPINoISR.sh 2360 7000
sbatch -n1 -o /disk0/QGjetsPetr/run/logs/job_ang_pythia_NoMPI_NoISR_900_2360 ./runprodfinalNoMPINoISR_pythia.sh 900 2360
sbatch -n1 -o /disk0/QGjetsPetr/run/logs/job_ang_trim_NoMPI_NoISR_2360_7000 ./runprodfinalNoMPINoISR_trim.sh 2360 7000
sbatch -n1 -o /disk0/QGjetsPetr/run/logs/job_ang_trim_NoMPI_NoISR_900_2360 ./runprodfinalNoMPINoISR_trim.sh 900 2360
sbatch -n1 -o /disk0/QGjetsPetr/run/logs/job_ang_trim_NoMPI_NoISR_900_7000 ./runprodfinalNoMPINoISR_trim.sh 900 7000


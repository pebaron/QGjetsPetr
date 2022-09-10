#!/bin/bash

for j in {1..10}; do sbatch -n1 ./run_pythia_trim.sh QGjets_900GeV ${j} ; done
for j in {1..10}; do sbatch -n1 ./run_pythia_trim.sh QGjets_2360GeV ${j} ; done
for j in {1..10}; do sbatch -n1 ./run_pythia_trim.sh QGjets_7TeV ${j} ; done
for j in {1..10}; do sbatch -n1 ./run_pythia_trim.sh QGjets_13TeV ${j} ; done

for j in {1..10}; do sbatch -n1 ./run_pythia_trim.sh QGjets_13TeV_noMPI_noISR ${j} ; done
##for j in {1..10}; do sbatch -n1 ./run_pythia_trim.sh QGjets_13TeV_noMPI_withISR ${j} ; done
##for j in {1..10}; do sbatch -n1 ./run_pythia_trim.sh QGjets_13TeV_withMPI_noISR ${j} ; done
for j in {1..10}; do sbatch -n1 ./run_pythia_trim.sh QGjets_2360GeV_noMPI_noISR ${j} ; done
##for j in {1..10}; do sbatch -n1 ./run_pythia_trim.sh QGjets_2360GeV_noMPI_withISR ${j} ; done
##for j in {1..10}; do sbatch -n1 ./run_pythia_trim.sh QGjets_2360GeV_withMPI_noISR ${j} ; done
for j in {1..10}; do sbatch -n1 ./run_pythia_trim.sh QGjets_7TeV_noMPI_noISR ${j} ; done
##for j in {1..10}; do sbatch -n1 ./run_pythia_trim.sh QGjets_7TeV_noMPI_withISR ${j} ; done
##for j in {1..10}; do sbatch -n1 ./run_pythia_trim.sh QGjets_7TeV_withMPI_noISR ${j} ; done
for j in {1..10}; do sbatch -n1 ./run_pythia_trim.sh QGjets_900GeV_noMPI_noISR ${j} ; done
##for j in {1..10}; do sbatch -n1 ./run_pythia_trim.sh QGjets_900GeV_noMPI_withISR ${j} ; done
##for j in {1..10}; do sbatch -n1 ./run_pythia_trim.sh QGjets_900GeV_withMPI_noISR ${j} ; done

#for j in {1..10}; do sbatch -n1 ./run_pythia_trim.sh QGjets_900GeV_nohadr_withMPI_and_part_shower ${j} ; done
#for j in {1..10}; do sbatch -n1 ./run_pythia_trim.sh QGjets_2360GeV_nohadr_withMPI_and_part_shower ${j} ; done
#for j in {1..10}; do sbatch -n1 ./run_pythia_trim.sh QGjets_7TeV_nohadr_withMPI_and_part_shower ${j} ; done
#for j in {1..10}; do sbatch -n1 ./run_pythia_trim.sh QGjets_13TeV_nohadr_withMPI_and_part_shower ${j} ; done

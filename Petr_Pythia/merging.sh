#!/bin/bash

#yodamerge -o Pythia_QGjets_900GeV_merge.yoda QGjets_900GeV_[1-9]*/*.yoda
#yodamerge -o Pythia_QGjets_2360GeV_merge.yoda QGjets_2360GeV_[1-9]*/*.yoda
#yodamerge -o Pythia_QGjets_7TeV_merge.yoda QGjets_7TeV_[1-9]*/*.yoda
#yodamerge -o Pythia_QGjets_13TeV_merge.yoda QGjets_13TeV_[1-9]*/*.yoda

#yodamerge -o Pythia_QGjets_900GeV_noMPI_noISR_merge.yoda QGjets_900GeV_noMPI_noISR_[1-9]*/*.yoda
#yodamerge -o Pythia_QGjets_2360GeV_noMPI_noISR_merge.yoda QGjets_2360GeV_noMPI_noISR_[1-9]*/*.yoda
#yodamerge -o Pythia_QGjets_7TeV_noMPI_noISR_merge.yoda QGjets_7TeV_noMPI_noISR_[1-9]*/*.yoda
#yodamerge -o Pythia_QGjets_13TeV_noMPI_noISR_merge.yoda QGjets_13TeV_noMPI_noISR_[1-9]*/*.yoda

#yodamerge -o Pythia_QGjets_900GeV_withMPI_noISR_merge.yoda QGjets_900GeV_withMPI_noISR_[1-9]*/*.yoda
#yodamerge -o Pythia_QGjets_2360GeV_withMPI_noISR_merge.yoda QGjets_2360GeV_withMPI_noISR_[1-9]*/*.yoda
#yodamerge -o Pythia_QGjets_7TeV_withMPI_noISR_merge.yoda QGjets_7TeV_withMPI_noISR_[1-9]*/*.yoda
#yodamerge -o Pythia_QGjets_13TeV_withMPI_noISR_merge.yoda QGjets_13TeV_withMPI_noISR_[1-9]*/*.yoda

#yodamerge -o Pythia_QGjets_900GeV_noMPI_withISR_merge.yoda QGjets_900GeV_noMPI_withISR_[1-9]*/*.yoda
#yodamerge -o Pythia_QGjets_2360GeV_noMPI_withISR_merge.yoda QGjets_2360GeV_noMPI_withISR_[1-9]*/*.yoda
#yodamerge -o Pythia_QGjets_7TeV_noMPI_withISR_merge.yoda QGjets_7TeV_noMPI_withISR_[1-9]*/*.yoda
#yodamerge -o Pythia_QGjets_13TeV_noMPI_withISR_merge.yoda QGjets_13TeV_noMPI_withISR_[1-9]*/*.yoda

yodamerge -o Pythia_QGjets_900GeV_nohadr_withMPI_and_part_shower_merge.yoda QGjets_900GeV_nohadr_withMPI_and_part_shower_[1-9]*/*.yoda
yodamerge -o Pythia_QGjets_2360GeV_nohadr_withMPI_and_part_shower_merge.yoda QGjets_2360GeV_nohadr_withMPI_and_part_shower_[1-9]*/*.yoda
yodamerge -o Pythia_QGjets_7TeV_nohadr_withMPI_and_part_shower_merge.yoda QGjets_7TeV_nohadr_withMPI_and_part_shower_[1-9]*/*.yoda
yodamerge -o Pythia_QGjets_13TeV_nohadr_withMPI_and_part_shower_merge.yoda QGjets_13TeV_nohadr_withMPI_and_part_shower_[1-9]*/*.yoda

for i in `ls *.yoda`; do yoda2root $i;done

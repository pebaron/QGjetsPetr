#!/bin/bash

#here to continue

hadd 900_hadr_pythia.root   QGjets_900GeV_*/test.root
hadd 2360_hadr_pythia.root  QGjets_2360GeV_*/test.root
hadd 7000_hadr_pythia.root  QGjets_7TeV_*/test.root
hadd 13000_hadr_pythia.root QGjets_13TeV_*/test.root

hadd trim_900_hadr_pythia.root   trim_QGjets_900GeV_*/test.root
hadd trim_2360_hadr_pythia.root  trim_QGjets_2360GeV_*/test.root
hadd trim_7000_hadr_pythia.root  trim_QGjets_7TeV_*/test.root
hadd trim_13000_hadr_pythia.root trim_QGjets_13TeV_*/test.root






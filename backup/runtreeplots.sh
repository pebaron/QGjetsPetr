#!/bin/bash

for i in `less listofvars2.txt`; do
    for j in `less listofvars2.txt`; do
        root -l -b -q "./PlotFromTTree.C(\"analyzed_histos_boosted_Y0.root\",\"TTree_ML_TagHistos\", \"$i\", \"$j\")"
    done;
done;

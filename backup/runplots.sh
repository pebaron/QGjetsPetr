#!/bin/bash
for i in `less variables.txt`;do root -l -b -q "./PlotVariable2.C(\"$i\")";done
for i in `less truth_variables.txt`;do root -l -b -q "./PlotVariable2.C(\"$i\", \"TruthTPReco/Trees/TruthProbes_OC/TPTree_TruthProbes_OC\")";done


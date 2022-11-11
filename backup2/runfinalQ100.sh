#!/bin/bash

##rm -rf angs1D_filter_herwig_average/*.png
##rm -rf angs1D_filter_herwig_average_no_7000_13000/*.pdf 
##
##root -l -b -q PlotAngsFilter1DAverage.C
##root -l -b -q PlotAngsFilter1DAverageMMDT.C
##root -l -b -q PlotAngsFilter1DAverageNo7000_13000.C
##root -l -b -q PlotAngsFilter1DAverageMMDTNo7000_13000.C
##
##root -l -b -q "./PlotAngsFilter1DAverage.C(1)"
##root -l -b -q "./PlotAngsFilter1DAverageMMDT.C(1)"
##root -l -b -q "./PlotAngsFilter1DAverageNo7000_13000.C(1)"
##root -l -b -q "./PlotAngsFilter1DAverageMMDTNo7000_13000.C(1)"

root -l -b -q "./PlotAngsFilter1DAverage.C(0, \"100\")"
root -l -b -q "./PlotAngsFilter1DAverageMMDT.C(0, \"100\")"
root -l -b -q "./PlotAngsFilter1DAverageNo7000_13000.C(0, \"100\")"
root -l -b -q "./PlotAngsFilter1DAverageMMDTNo7000_13000.C(0, \"100\")"

#root -l -b -q "./PlotAngsFilter1DAverage.C(1, \"100\")"
#root -l -b -q "./PlotAngsFilter1DAverageMMDT.C(1, \"100\")"
#root -l -b -q "./PlotAngsFilter1DAverageNo7000_13000.C(1, \"100\")"
#root -l -b -q "./PlotAngsFilter1DAverageMMDTNo7000_13000.C(1, \"100\")"

mkdir -p angs1D_filter_herwig_average/Q100/
mkdir -p angs1D_filter_herwig_average_no_7000_13000/Q100/
cp angs1D_filter_herwig_average/*Lam100* angs1D_filter_herwig_average/Q100/
cp angs1D_filter_herwig_average_no_7000_13000/*Lam100* angs1D_filter_herwig_average_no_7000_13000/Q100/


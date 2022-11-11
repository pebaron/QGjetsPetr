#!/bin/bash

rm -rf angs1D_filter_herwig_average/*.png
rm -rf angs1D_filter_herwig_average_no_7000_13000/*.pdf 

root -l -b -q PlotAngsFilter1DAverage.C
root -l -b -q PlotAngsFilter1DAverageMMDT.C
root -l -b -q PlotAngsFilter1DAverageNo7000_13000.C
root -l -b -q PlotAngsFilter1DAverageMMDTNo7000_13000.C

root -l -b -q "./PlotAngsFilter1DAverage.C(1)"
root -l -b -q "./PlotAngsFilter1DAverageMMDT.C(1)"
root -l -b -q "./PlotAngsFilter1DAverageNo7000_13000.C(1)"
root -l -b -q "./PlotAngsFilter1DAverageMMDTNo7000_13000.C(1)"

#root -l -b -q "./PlotAngsFilter1DAverage.C(0, \"100\"")"
#root -l -b -q "./PlotAngsFilter1DAverageMMDT.C(0, \"100\"")"
#root -l -b -q "./PlotAngsFilter1DAverageNo7000_13000.C(0, \"100\"")"
#root -l -b -q "./PlotAngsFilter1DAverageMMDTNo7000_13000.C(0, \"100\"")"

#root -l -b -q "./PlotAngsFilter1DAverage.C(1, \"100\"")"
#root -l -b -q "./PlotAngsFilter1DAverageMMDT.C(1, \"100\"")"
#root -l -b -q "./PlotAngsFilter1DAverageNo7000_13000.C(1, \"100\"")"
#root -l -b -q "./PlotAngsFilter1DAverageMMDTNo7000_13000.C(1, \"100\"")"


mkdir -p angs1D_filter_herwig_average/Q50/
mkdir -p angs1D_filter_herwig_average_no_7000_13000/Q50/
cp angs1D_filter_herwig_average/*Lam50* angs1D_filter_herwig_average/Q50/
cp angs1D_filter_herwig_average_no_7000_13000/*Lam50* angs1D_filter_herwig_average_no_7000_13000/Q50/

#
cd ~/testarea/new_QG_production/angs1D_filter_herwig_average/Q50
for i in `ls *.pdf | sort --version-sort --field-separator=_ --reverse`; do a=`ls ../../angs1D_filter_herwig_average_no_7000_13000/Q50/*${i:10}`; pdfunite $i $a united_$i;done
for i in `ls united_*.pdf`; do echo $i;cpdf -twoup $i -o two_$i;done
for i in `ls two_united_*.pdf | sort --version-sort --field-separator=_ --reverse`; do pdf270 $i;done

filelist=""
for i in `ls *270.pdf | sort --version-sort --field-separator=_ --reverse`;do filelist+="${i} ";done
#for i in `ls *herwig*.pdf | sort --version-sort --field-separator=_ --reverse`;do a=$(echo \*${i:20} | sed 's\herwig_av\pythia_av\g');filelist+="${i} ";filelist+="${a} ";done
pdfunite ${filelist} all_Q50_right_plots_no7000_13000.pdf
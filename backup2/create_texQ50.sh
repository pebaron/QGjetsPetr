#!/bin/bash

echo "\documentclass{article}" >> angs.tex
echo "\usepackage[utf8]{inputenc} " >> angs.tex
echo "\usepackage{pgfplots}" >> angs.tex
echo "\pgfplotsset{compat=1.9}" >> angs.tex
#echo "\usepackage[T1]{fontenc}    " >> angs.tex
echo "\usepackage{cite}" >> angs.tex
echo "\usepackage{subfig}" >> angs.tex
echo "\usepackage{amsmath}" >> angs.tex
echo "\usepackage{enumitem}" >> angs.tex
#echo "\usepackage[T1]{fontenc}" >> angs.tex
echo "\usepackage{color}" >> angs.tex
echo "\usepackage{graphicx}" >> angs.tex
#echo "\usepackage[utf8]{inputenc}" >> angs.tex
echo "\usepackage{multirow}" >> angs.tex
echo "\usepackage{wrapfig}" >> angs.tex
echo "\usepackage{booktabs}" >> angs.tex
echo "\usepackage[colorlinks = true," >> angs.tex
echo "            linkcolor = blue," >> angs.tex
echo "            urlcolor  = blue," >> angs.tex
echo "            citecolor = blue," >> angs.tex
echo "            anchorcolor = blue]{hyperref}" >> angs.tex
echo "\usepackage{subfig}" >> angs.tex
echo "\usepackage{pdfpages}" >> angs.tex
echo "\usepackage[total={17cm,17cm}, top=1cm, left=1cm, bottom=1cm, right=1cm, includefoot]{geometry}" >> angs.tex
echo "\begin{document}" >> angs.tex
echo "\tableofcontents" >> angs.tex
#for dir in `ls -d */`;do

afilelist=""
ifilelist=""
pafilelist=""
pifilelist=""
afilelist=""
ifilelist=""
pafilelist=""
pifilelist=""
for i in `ls *herwig_av*.pdf | sort --version-sort --field-separator=_ --reverse`; do a=`ls ../../angs1D_filter_herwig_average_no_7000_13000/Q50/*${i:10}`; ls $a;ls $i; pa=$(echo $a | sed 's\herwig_average.pdf\pythia_average.pdf\'); paa=$(ls ../../angs1D_filter_herwig_average_no_7000_13000/Q50/*${pa#*clone});ls $paa;pi=$(echo "${i:10}" | sed 's\herwig_average.pdf\pythia_average.pdf\g');pii=$(ls *$pi);ls $pii;afilelist+="${a} ";ifilelist+="${i} ";pafilelist+="${paa} ";pifilelist+="${pii} ";echo "----------------";done

echo $afilelist &> log_afilelist.txt
echo $ifilelist &> log_ifilelist.txt
echo $pafilelist &> log_pafilelist.txt
echo $pifilelist &> log_pifilelist.txt

#length=${afilelist[@]}
afoo=($afilelist)
ifoo=($ifilelist)
pafoo=($pafilelist)
pifoo=($pifilelist)


for i in ${!afoo[@]}; do 
  #echo ${afoo[$i]}
  #echo ${ifoo[$i]}
  #echo ${pafoo[$i]}
  #echo ${pifoo[$i]}
  #echo "----foooo------"
  var=$(echo ${pafoo[$i]#*no_cut_} | sed 's\__pythia_average.pdf\\g' | sed 's&_& &g')
  score=$(echo ${ifoo[$i]%no_cut*} | sed 's\1D_\\g' | sed 's\_clone_h\\g' | sed 's\_\\g')
  echo "\section{$var \$\Delta_{comb.} = $score\$}" >> angs.tex
  echo "$var \$\Delta_{comb.} = $score\$" >> angs.tex
  echo "\begin{figure}[h!]" >> angs.tex
  echo "\centering" >> angs.tex
  echo "\includegraphics[width=9cm]{$PWD/${afoo[$i]}} " >> angs.tex
  echo "\includegraphics[width=9cm]{$PWD/${ifoo[$i]}} " >> angs.tex
  echo "\caption{ HERWIG without 7000-13000 GeV combination (left), All Energy combinations combinations (right).}" >> angs.tex
  echo "\includegraphics[width=9cm]{$PWD/${pafoo[$i]}} " >> angs.tex
  echo "\includegraphics[width=9cm]{$PWD/${pifoo[$i]}} " >> angs.tex
  echo "\caption{ PYTHIA without 7000-13000 GeV combination (left), All Energy combinations combinations (right).}" >> angs.tex
  echo "\end{figure}" >> angs.tex
  echo "\clearpage" >> angs.tex
done;


echo "\end{document}" >> angs.tex


pdflatex angs.tex
pdflatex angs.tex
#mv angs.tex createpdf.tex
#rm createpdf.pdf 
#rm createpdf.aux 
#rm createpdf.log
#rm createpdf.out 
#rm createpdf.fls 
#rm createpdf.fdb_latexmk 
#
#
#pdflatex createpdf.tex
#mv createpdf.pdf SF_trigger.pdf

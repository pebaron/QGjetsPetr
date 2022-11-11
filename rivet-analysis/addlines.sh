#!/bin/bash

for i in 02 04 05 06 08 10; do 
for j in 50 100 200 400 800; do
#for i in 02; do 
#for j in 50; do
a="_histFastJets${i}PtSubLeading = bookHisto1D(\"FastJets${i}PtSubLeading\", 50, 0, 200);";
b="_histFastJets${i}PtSubLeadingQ${j} = bookHisto1D(\"FastJets${i}PtSubLeadingQ${j}\", 50, 0, 200);";
c="_histFastJets${i}PtLeading = bookHisto1D(\"FastJets${i}PtLeading\", 50, 0, 200);";
d="_histFastJets${i}PtLeadingQ${j} = bookHisto1D(\"FastJets${i}PtLeadingQ${j}\", 50, 0, 200);";
e="_histFastJets${i}PtReclust = bookHisto1D(\"FastJets${i}PtReclust\", 50, 0, 200);";
f="_histFastJets${i}PtReclustQ${j} = bookHisto1D(\"FastJets${i}PtReclustQ${j}\", 50, 0, 200);";
sed -i "/${a}/ i ${b}" MC_DIJET_PB_CH.cc;
sed -i "/${c}/ i ${d}" MC_DIJET_PB_CH.cc;
sed -i "/${e}/ i ${f}" MC_DIJET_PB_CH.cc;
done
done
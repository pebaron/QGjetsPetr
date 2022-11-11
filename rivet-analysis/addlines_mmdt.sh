#!/bin/bash

for i in 02 04 05 06 08 10; do 
for j in 50 100 200 400 800; do
#for i in 02; do 
#for j in 50; do
a="mmdt_histFastJets${i}PtSubLeading = bookHisto1D(\"mmdt_FastJets${i}PtSubLeading\", 50, 0, 200);";
b="mmdt_histFastJets${i}PtSubLeadingQ${j} = bookHisto1D(\"mmdt_FastJets${i}PtSubLeadingQ${j}\", 50, 0, 200);";
c="mmdt_histFastJets${i}PtLeading = bookHisto1D(\"mmdt_FastJets${i}PtLeading\", 50, 0, 200);";
d="mmdt_histFastJets${i}PtLeadingQ${j} = bookHisto1D(\"mmdt_FastJets${i}PtLeadingQ${j}\", 50, 0, 200);";
e="mmdt_histFastJets${i}PtReclust = bookHisto1D(\"mmdt_FastJets${i}PtReclust\", 50, 0, 200);";
f="mmdt_histFastJets${i}PtReclustQ${j} = bookHisto1D(\"mmdt_FastJets${i}PtReclustQ${j}\", 50, 0, 200);";
sed -i "/${a}/ i ${b}" MC_DIJET_PB_CH.cc;
sed -i "/${c}/ i ${d}" MC_DIJET_PB_CH.cc;
sed -i "/${e}/ i ${f}" MC_DIJET_PB_CH.cc;
done
done
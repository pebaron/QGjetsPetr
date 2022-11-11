#!/bin/bash
source /root/.bashrc
source /disk0/QGjetsPetr/setup.sh
#source /disk0/ROOT/root/bin/thisroot.sh
source /disk0/opt/root/bin/thisroot.sh
echo "Arguments are: Energy [900, 2360, 7000, 13000], "
echo "               Events [1-10000000], "
echo "               Seed [61972970 23354883 88615218 70896900 18669684 71917516 25202807 62914023 20426705 23209777],"
echo "               PtWindow [0,25,...,175], PDF - name,"
echo "               Hadronization - [hadr, nohadr]"
Energy=$1
Events=$2
Seed=$3
Window=$4
PDF=$5
Hadronization=$6

FileName="Energy_${Energy}_NEvt_${Events}_Seed_${Seed}_PtWindow_${Window}_PDF_${PDF}_${Hadronization}.in"
FileName2="Energy_${Energy}_NEvt_${Events}_Seed_${Seed}_PtWindow_${Window}_PDF_${PDF}_${Hadronization}"

rm -rf /disk0/QGjetsPetr/run/files_test_noMPI_noISR/${FileName2} 
mkdir /disk0/QGjetsPetr/run/files_test_noMPI_noISR/${FileName2}
cd /disk0/QGjetsPetr/run/files_test_noMPI_noISR/$FileName2

echo "Creating File: ${FileName}"
echo "# -*- ThePEG-repository -*-" > $FileName
echo "" >> $FileName
echo "##################################################" >> $FileName
echo "# Example generator based on LHC parameters" >> $FileName
echo "# usage: Herwig read LHC.in" >> $FileName
echo "##################################################" >> $FileName
echo "" >> $FileName
echo "read snippets/PPCollider.in" >> $FileName
echo "" >> $FileName
echo "##################################################" >> $FileName
echo "# Technical parameters for this run" >> $FileName
echo "##################################################" >> $FileName
echo "cd /Herwig/Generators" >> $FileName
echo "" >> $FileName
echo "##################################################" >> $FileName
echo "# LHC physics parameters (override defaults here) " >> $FileName
echo "##################################################" >> $FileName
echo "" >> $FileName
echo "# Intrinsic pT tune extrapolated to LHC energy" >> $FileName
echo "set /Herwig/Shower/ShowerHandler:IntrinsicPtGaussian 2.2*GeV" >> $FileName
#echo "set /Herwig/Shower/ShowerHandler:SplittingGenerator:ISR NULL" >> $FileName
echo "" >> $FileName
echo "########################" >> $FileName
echo "## sqrt(s) = ${Energy} GeV ##" >> $FileName
echo "########################" >> $FileName
echo "set EventGenerator:EventHandler:LuminosityFunction:Energy ${Energy}.0" >> $FileName


if [ "$Hadronization" = "hadr" ]; then
    echo "Runnig hadronization."
    echo "#set EventGenerator:EventHandler:DecayHandler NULL" >> $FileName
    echo "#set EventGenerator:EventHandler:HadronizationHandler NULL" >> $FileName
    echo "#set EventGenerator:EventHandler:CascadeHandler NULL" >> $FileName
    echo "set EventGenerator:EventHandler:CascadeHandler:DoISR No" >> $FileName
    echo "cd /Herwig/EventHandlers" >> $FileName
    echo "set EventHandler:CascadeHandler:MPIHandler NULL" >> $FileName #PB ADDED RECENTLY 22.9.2021
    #echo "set EventGenerator:EventHandler:CascadeHandler:DoISR No" >> $FileName
    #echo "set /Herwig/Shower/SplittingGenerator:ISR No" >> $FileName
else 
    echo "Runnig no_hadronization."
    echo "set EventGenerator:EventHandler:DecayHandler NULL" >> $FileName
    echo "set EventGenerator:EventHandler:HadronizationHandler NULL" >> $FileName
    echo "set EventGenerator:EventHandler:CascadeHandler NULL" >> $FileName
    echo "set EventGenerator:EventHandler:CascadeHandler:DoISR No" >> $FileName
    echo "cd /Herwig/EventHandlers" >> $FileName
    echo "set EventHandler:CascadeHandler:MPIHandler NULL" >> $FileName #PB ADDED RECENTLY 22.9.2021
    #echo "set EventGenerator:EventHandler:CascadeHandler:DoISR No" >> $FileName
    #echo "set /Herwig/Shower/SplittingGenerator:ISR No" >> $FileName
fi

echo "" >> $FileName
echo "########################" >> $FileName
echo "## Petr Baron - different pdf's , CT14lo, NNPDF31_lo_as_0118, MMHT2014lo68cl - default by Herwig" >> $FileName
echo "########################" >> $FileName
echo "cd /Herwig/Partons" >> $FileName
echo "create ThePEG::LHAPDF PDFSet ThePEGLHAPDF.so" >> $FileName
echo "set PDFSet:PDFName ${PDF}" >> $FileName
echo "set PDFSet:RemnantHandler HadronRemnants" >> $FileName
echo "set /Herwig/Particles/p+:PDF PDFSet" >> $FileName
echo "set /Herwig/Particles/pbar-:PDF PDFSet" >> $FileName
echo "set PPExtractor:FirstPDF PDFSet" >> $FileName
echo "set PPExtractor:SecondPDF PDFSet" >> $FileName
echo "set /Herwig/Shower/ShowerHandler:PDFA PDFSet" >> $FileName
echo "set /Herwig/Shower/ShowerHandler:PDFB PDFSet" >> $FileName
echo "set /Herwig/Partons/MPIExtractor:FirstPDF PDFSet" >> $FileName
echo "set /Herwig/Partons/MPIExtractor:SecondPDF PDFSet" >> $FileName
echo "set /Herwig/Partons/PPExtractor:FirstPDF PDFSet" >> $FileName
echo "set /Herwig/Partons/PPExtractor:SecondPDF PDFSet" >> $FileName
echo "set /Herwig/Shower/ShowerHandler:PDFARemnant" >> $FileName
echo "set /Herwig/Shower/ShowerHandler:PDFBRemnant" >> $FileName
echo "cd /" >> $FileName
echo "" >> $FileName
echo "##################################################" >> $FileName
echo "# Matrix Elements for hadron-hadron collisions " >> $FileName
echo "# (by default only gamma/Z switched on)" >> $FileName
echo "##################################################" >> $FileName
echo "cd /Herwig/MatrixElements/" >> $FileName
echo "" >> $FileName
echo "#" >> $FileName
echo "#  Electroweak boson W/Z processes" >> $FileName
echo "#" >> $FileName
echo "# Drell-Yan Z/gamma" >> $FileName
echo "# insert SubProcess:MatrixElements[0] MEqq2gZ2ff" >> $FileName
echo "# PB exclude Drell-Yan" >> $FileName
echo "# Drell-Yan W" >> $FileName
echo "# insert SubProcess:MatrixElements[0] MEqq2W2ff" >> $FileName
echo "#" >> $FileName
echo "# W+jet" >> $FileName
echo "# insert SubProcess:MatrixElements[0] MEWJet" >> $FileName
echo "#" >> $FileName
echo "# Z+jet" >> $FileName
echo "# insert SubProcess:MatrixElements[0] MEZJet" >> $FileName
echo "#" >> $FileName
echo "# WW/WZ/ZZ" >> $FileName
echo "# insert SubProcess:MatrixElements[0] MEPP2VV" >> $FileName
echo "#" >> $FileName
echo "# Wgamma/Zgamma" >> $FileName
echo "# insert SubProcess:MatrixElements[0] MEPP2VGamma" >> $FileName
echo "#" >> $FileName
echo "# add QED radiation off W/Z decay products using YFS formalism" >> $FileName
echo "# cd /Herwig/EventHandlers" >> $FileName
echo "# insert EventHandler:PostSubProcessHandlers[0] /Herwig/QEDRadiation/QEDRadiationHandler" >> $FileName
echo "" >> $FileName
echo "#" >> $FileName
echo "#  QCD and gamma processes" >> $FileName
echo "#" >> $FileName
echo "# QCD 2-2 scattering" >> $FileName
echo "insert SubProcess:MatrixElements[0] MEQCD2to2" >> $FileName
echo "#" >> $FileName
echo "# gamma+jet" >> $FileName
echo "# insert SubProcess:MatrixElements[0] MEGammaJet" >> $FileName
echo "#" >> $FileName
echo "# gamma-gamma" >> $FileName
echo "# insert SubProcess:MatrixElements[0] MEGammaGamma" >> $FileName
echo "" >> $FileName
echo "#" >> $FileName
echo "#  Heavy quark processes" >> $FileName
echo "#" >> $FileName
echo "#" >> $FileName
echo "# top-antitop production" >> $FileName
echo "# insert SubProcess:MatrixElements[0] MEHeavyQuark" >> $FileName
echo "#" >> $FileName
echo "# single-top" >> $FileName
echo "# t-channel" >> $FileName
echo "# insert SubProcess:MatrixElements[0] MESingleTopTChannel" >> $FileName
echo "# s-channel" >> $FileName
echo "# insert SubProcess:MatrixElements[0] MESingleTopSChannel" >> $FileName
echo "# tW" >> $FileName
echo "# insert SubProcess:MatrixElements[0] MESingleTopTW" >> $FileName
echo "#" >> $FileName
echo "#  Higgs Processes" >> $FileName
echo "#" >> $FileName
echo "#" >> $FileName
echo "# gg/qqbar -> Higgs (recommend including q qbar->Hg as not in ME correction)" >> $FileName
echo "# insert SubProcess:MatrixElements[0] MEHiggs" >> $FileName
echo "# insert SubProcess:MatrixElements[0] MEHiggsJet" >> $FileName
echo "# set MEHiggsJet:Process qqbar" >> $FileName

if [ "$Hadronization" = "hadr" ]; then
    # change for low pt
    echo "Running hadronization, pt cut > 95.0 GeV."
    echo "set /Herwig/Cuts/JetKtCut:MinKT 95.0*GeV" >> $FileName
else 
    given_Pt=(0 25 50 75 100 125 150 175)
    lower_Pt=(0 15 40 65 90 115 140 165)
    upper_Pt=(35 60 85 110 135 160 185 210)
    k=0
    for i in "${given_Pt[@]}"
    do
        if [ $i -eq $Window ]
            then
            echo "Window is: "
            echo $i
            index=$k
            echo "Index is: "
            echo $index
        fi
        let "k++"
    done
    echo "Pt block is ${Window} GeV "
    echo "Running no_hadronization, ${lower_Pt[$index]}.0 < pt cut < ${upper_Pt[$index]}.0  GeV."
    echo "set /Herwig/Cuts/JetKtCut:MinKT ${lower_Pt[$index]}.0*GeV" >> $FileName
    echo "set /Herwig/Cuts/JetKtCut:MaxKT ${upper_Pt[$index]}.0*GeV" >> $FileName
fi

echo "##set /Herwig/Cuts/JetKtCut:MinEta 0" >> $FileName
echo "##set /Herwig/Cuts/JetKtCut:MaxEta 0.5" >> $FileName
echo "#" >> $FileName
echo "# higgs+jet" >> $FileName
echo "# insert SubProcess:MatrixElements[0] MEHiggsJet" >> $FileName
echo "#" >> $FileName
echo "# higgs + W (N.B. if considering all W decay modes useful to set )" >> $FileName
echo "#           (jet pT cut to zero so no cut on W decay products    )" >> $FileName
echo "# insert SubProcess:MatrixElements[0] MEPP2WH" >> $FileName
echo "# set /Herwig/Cuts/JetKtCut:MinKT 0.0*GeV" >> $FileName
echo "#" >> $FileName
echo "# higgs + Z (N.B. if considering all Z decay modes useful to set )" >> $FileName
echo "#           (jet pT cut to zero so no cut on Z decay products    )" >> $FileName
echo "# insert SubProcess:MatrixElements[0] MEPP2ZH" >> $FileName
echo "# set /Herwig/Cuts/JetKtCut:MinKT 0.0*GeV" >> $FileName
echo "#" >> $FileName
echo "# VBF Higgs" >> $FileName
echo "# insert SubProcess:MatrixElements[0] MEPP2HiggsVBF" >> $FileName
echo "#" >> $FileName
echo "# t tbar Higgs" >> $FileName
echo "# insert SubProcess:MatrixElements[0] MEPP2ttbarH" >> $FileName
echo "#" >> $FileName
echo "# b bbar Higgs" >> $FileName
echo "# insert SubProcess:MatrixElements[0] MEPP2bbbarH" >> $FileName
echo "" >> $FileName
echo "cd /Herwig/Generators" >> $FileName
echo "" >> $FileName
echo "##################################################" >> $FileName
echo "#  Useful analysis handlers for hadron-hadron physics" >> $FileName
echo "##################################################" >> $FileName
echo "# analysis of W/Z events" >> $FileName
echo "# insert EventGenerator:AnalysisHandlers 0 /Herwig/Analysis/DrellYan" >> $FileName
echo "# analysis of top-antitop events" >> $FileName
echo "# insert EventGenerator:AnalysisHandlers 0 /Herwig/Analysis/TTbar" >> $FileName
echo "# analysis of gamma+jet events" >> $FileName
echo "# insert EventGenerator:AnalysisHandlers 0 /Herwig/Analysis/GammaJet" >> $FileName
echo "# analysis of gamma-gamma events" >> $FileName
echo "# insert EventGenerator:AnalysisHandlers 0 /Herwig/Analysis/GammaGamma" >> $FileName
echo "# analysis of higgs-jet events" >> $FileName
echo "# insert EventGenerator:AnalysisHandlers 0 /Herwig/Analysis/HiggsJet" >> $FileName
echo "" >> $FileName
echo "##################################################" >> $FileName
echo "## prepare for Rivet analysis or HepMC output" >> $FileName
echo "## when running with parton shower" >> $FileName
echo "##################################################" >> $FileName
echo "read snippets/Rivet.in" >> $FileName
#echo "insert /Herwig/Analysis/Rivet:Analyses 0 MC_LHQG_dijet " >> $FileName
echo "insert /Herwig/Analysis/Rivet:Analyses 0 MC_DIJET_PB_CH" >> $FileName
echo "set /Herwig/Analysis/Basics:CheckQuark No" >> $FileName
echo "#read snippets/HepMC.in" >> $FileName
echo "#set /Herwig/Analysis/HepMC:PrintEvent NNN" >> $FileName
echo "" >> $FileName
echo "##################################################" >> $FileName
echo "## prepare for Rivet analysis or HepMC output" >> $FileName
echo "## when running at fixed order (NO shower)" >> $FileName
echo "##################################################" >> $FileName
echo "#read snippets/RivetFixedOrder.in" >> $FileName
echo "#insert /Herwig/Analysis/RivetFixedOrder:Analyses 0 XXX_2015_ABC123" >> $FileName
echo "#read snippets/HepMCFixedOrder.in" >> $FileName
echo "#set /Herwig/Analysis/HepMCFixedOrder:PrintEvent NNN" >> $FileName
echo "" >> $FileName
echo "##################################################" >> $FileName
echo "# Save run for later usage with 'Herwig run'" >> $FileName
echo "##################################################" >> $FileName
echo "saverun ${FileName2} EventGenerator" >> $FileName

echo "Done Creating File: ${FileName}" 

echo "Lunching: Herwig read ${FileName}" 
Herwig read $FileName

echo "-------------------------------------------------------------"
echo "Lunching: Herwig run ${FileName2}.run -N $Events -s $Seed" 
echo ${FileName2}
Herwig run ${FileName2}.run -N $Events -s $Seed
echo "---------------------DONE------------------------------------"

##for s in 61972970 23354883 88615218 70896900 18669684 71917516 25202807 62914023 20426705 23209777;do
##for j in 0 25 50 75 100 125 150 175;do
##echo "Reading file == Herwig read LHC_pb900_no_hadronization_${j}.in with seed $s.";
##Herwig read LHC_pb900_no_hadronization_${j}.in;
###mkdir ${s}_mass_window_start_${j}_900
##mv LHC900_${j}.run LHC900_${j}_${s}.run;
###mv other_pdgid.txt ${s}_900_other_pdgid.txt
##echo "Running Herwig == Herwig run LHC900_${j}_${s}.run -N ${c} -s ${s}";
##Herwig run LHC900_${j}_${s}.run -N $c -s $s;
##done;
##done;
cd -

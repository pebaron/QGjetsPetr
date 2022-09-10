#!/bin/bash

# set env
source /disk0/Herwig7/bin/activate
export RIVET_ANALYSIS_PATH=/disk0/QGjetsPetr/rivet-analysis/
export LD_LIBRARY_PATH="/disk0/QGjetsPetr/rivet-analysis:$LD_LIBRARY_PATH"
source /disk0/opt/root/bin/thisroot.sh
# run

cd /disk0/QGjetsPetr/Petr_Pythia/

mkdir trim_${1}_${2}
cd trim_${1}_${2}
cp /disk0/Herwig7/src/pythia8240/examples/${1} .
cp /disk0/QGjetsPetr/Andrzej/Runs/Pythia/QGjets.cmnd .
sed -i "s/Random:seed = 0/Random:seed = ${2}/" QGjets.cmnd
mkfifo ${1}.fifo

./${1} &
#rivet -a MC_DIJET_PB_CH ${1}.fifo -o ${1}_${2}.yoda
rivet -a MC_DIJET_PB_CH_TRIM ${1}.fifo 



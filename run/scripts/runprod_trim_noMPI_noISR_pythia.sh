#!/bin/bash

cd /disk0/QGjetsPetr/
source setup.sh
source aliases.sh
cd /disk0/QGjetsPetr/run/scripts/

echo "Now producing ntuples on Pythia NoMPINoISR-----------------------------------"
root -l -b -q "./CreateAngularitiesNoMPINoISRTrim.C(\"$1\", \"$2\", 1)"
#echo "Now producing ntuples on Herwig NoMPINoISR-----------------------------------"
#root -l -b -q "./CreateAngularitiesNoMPINoISR.C(\"$1\", \"$2\")"

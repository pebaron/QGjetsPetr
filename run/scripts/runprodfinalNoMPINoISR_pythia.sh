#!/bin/bash

cd /disk0/QGjetsPetr/
source setup.sh
source aliases.sh
cd /disk0/QGjetsPetr/run/scripts/

echo "Running Pythia NoMPINoISR---------------"
root -l -b -q "./GenerateAngNoMPINoISR.C(\"$1\", \"$2\", 1)"
#echo "Running Herwig NoMPINoISR---------------"
#root -l -b -q "./GenerateAngNoMPINoISR.C(\"$1\", \"$2\")"

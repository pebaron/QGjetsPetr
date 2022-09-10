#!/bin/bash

cd /disk0/QGjetsPetr/
source setup.sh
source aliases.sh
cd /disk0/QGjetsPetr/run/scripts/

#echo "Running Pythia ---------------"
#root -l -b -q "./GenerateAng.C(\"$1\", \"$2\", 1)"
echo "Running Herwig test ---------------"
root -l -b -q ./GenerateAngTest.C

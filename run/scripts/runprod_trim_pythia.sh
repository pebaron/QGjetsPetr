#!/bin/bash

cd /disk0/QGjetsPetr/
source setup.sh
source aliases.sh
cd /disk0/QGjetsPetr/run/scripts/

echo "Now producing ntuples on Pythia -----------------------------------"
root -l -b -q "./CreateAngularitiesTrim.C(\"$1\", \"$2\", 1)"
#echo "Now producing ntuples on Herwig -----------------------------------"
#root -l -b -q "./CreateAngularities.C(\"$1\", \"$2\")"

#!/bin/bash

source /disk0/Herwig7/bin/activate 
export RIVET_ANALYSIS_PATH="/disk0/QGjetsPetr/rivet-analysis/:${RIVET_ANALYSIS_PATH}"
export LD_LIBRARY_PATH="/disk0/QGjetsPetr/rivet-analysis:$LD_LIBRARY_PATH"


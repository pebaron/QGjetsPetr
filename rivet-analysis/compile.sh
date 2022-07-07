#!/bin/bash

#cmd='rivet-buildplugin RivetMC_DIJET_PB_CH.so MC_DIJET_PB_CH.cc -L -I -lfastjetcontribfragile -I/disk0/Herwig7/include -I/disk0/opt/root/include'
cmd='rivet-buildplugin RivetMC_DIJET_PB_CH.so MC_DIJET_PB_CH.cc -L -I -lfastjetcontribfragile -I/disk0/Herwig7/include -I/disk0/opt/root/include -L/disk0/opt/root/lib -lCore -lCint -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lTree -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -pthread -lm -ldl -rdynamic '
echo will do: $cmd
echo "-----------------------------"
$cmd
##just for now rivet-buildplugin RivetMC_MC_LHQG_dijet.so MC_LHQG_dijet.cc -L -I -lfastjetcontribfragile 
#rivet-build RivetMC_DIJET_PB_CH.so MC_DIJET_PB_CH.cc -L -I -lfastjetcontribfragile
#rivet-build RivetMC_MC_LHQG_dijet.so MC_LHQG_dijet.cc -L -I -lfastjetcontribfragile

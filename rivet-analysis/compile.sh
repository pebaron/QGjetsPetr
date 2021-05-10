#!/bin/bash

rivet-buildplugin RivetMC_DIJET_PB_CH.so MC_DIJET_PB_CH.cc -L -I -lfastjetcontribfragile
rivet-buildplugin RivetMC_MC_LHQG_dijet.so MC_LHQG_dijet.cc -L -I -lfastjetcontribfragile
#rivet-build RivetMC_DIJET_PB_CH.so MC_DIJET_PB_CH.cc -L -I -lfastjetcontribfragile
#rivet-build RivetMC_MC_LHQG_dijet.so MC_LHQG_dijet.cc -L -I -lfastjetcontribfragile

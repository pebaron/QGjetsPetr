#!/bin/bash

root -l -b -q ./Compare.C
root -l -b -q "./Compare.C(\"ML/ParticleTopMass\", \"2B0S/ParticleTopMass\")"

#root -l -b -q "./Compare.C(\"ML/DetectorDiTopMass\", \"2B0S/DetectorDiTopMass\")"
#root -l -b -q "./Compare.C(\"ML/ParticleDiTopMass\", \"2B0S/ParticleDiTopMass\")"

root -l -b -q "./Compare.C(\"ML/DetectorTop1Mass\", \"2B0S/DetectorTop1Mass\")"
root -l -b -q "./Compare.C(\"ML/DetectorTop2Mass\", \"2B0S/DetectorTop2Mass\")"

#root -l -b -q "./Compare.C(\"ML/DetectorDiTop1Mass\", \"2B0S/DetectorDiTop1Mass\")"
#root -l -b -q "./Compare.C(\"ML/DetectorDiTop2Mass\", \"2B0S/DetectorDiTop2Mass\")"

root -l -b -q "./Compare.C(\"ML/ParticleTop1Mass\", \"2B0S/ParticleTop1Mass\")"
oot -l -b -q "./Compare.C(\"ML/ParticleTop2Mass\", \"2B0S/ParticleTop2Mass\")"
#root -l -b -q "./Compare.C(\"ML/ParticleTop2Mass\", \"2B0S/ParticleTop2Mass\")"

#root -l -b -q "./Compare.C(\"ML/ParticleDiTop1Mass\", \"2B0S/ParticleDiTop1Mass\")"
#root -l -b -q "./Compare.C(\"ML/ParticleDiTop2Mass\", \"2B0S/ParticleDiTop2Mass\")"
#root -l -b -q "./Compare.C(\"ML/ParticleFourTopMass\", \"4B0S/ParticleFourTopMass\")"
#define Muons_cxx
//#include "Muons.h"
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

struct tc_t {
   std::vector<Double_t> var_HLT_mu15 {100};
   std::vector<Double_t> var_CaloLRLikelihood {100};
   std::vector<Double_t> var_CaloLikelihood {100};
   std::vector<Double_t> var_CaloMuonIDTag {100};
   std::vector<Double_t> var_CaloTag {100};
   std::vector<Double_t> var_CaloTagged {100};
   std::vector<Double_t> var_Combined {100};
   std::vector<Double_t> var_CombinedTrackParticle {100};
   std::vector<Double_t> var_EnergyLoss {100};
   std::vector<Double_t> var_EnergyLossSigma {100};
   std::vector<Double_t> var_ExtrapolateMuonToIP {100};
   std::vector<Double_t> var_FSR_CandidateEnergy {100};
   std::vector<Double_t> var_FSRcandidate {100};
   std::vector<Double_t> var_InnerDetectorTrackParticle {100};
   std::vector<Double_t> var_Loose {100};
   std::vector<Double_t> var_MOP {100};
   std::vector<Double_t> var_MeasEnergyLoss {100};
   std::vector<Double_t> var_MeasEnergyLossSigma {100};
   std::vector<Double_t> var_Medium {100};
   std::vector<Double_t> var_MuGirl {100};
   std::vector<Double_t> var_MuGirlLowBeta {100};
   std::vector<Double_t> var_MuTag {100};
   std::vector<Double_t> var_MuTagIMO {100};
   std::vector<Double_t> var_MuidCo {100};
   std::vector<Double_t> var_MuidSA {100};
   std::vector<Double_t> var_NotIsolated {100};
   std::vector<Double_t> var_NumberOfMuonAuthors {100};
   std::vector<Double_t> var_ParamEnergyLoss {100};
   std::vector<Double_t> var_ParamEnergyLossSigmaMinus {100};
   std::vector<Double_t> var_ParamEnergyLossSigmaPlus {100};
   std::vector<Double_t> var_Parametrized {100};
   std::vector<Double_t> var_Primary {100};
   std::vector<Double_t> var_STACO {100};
   std::vector<Double_t> var_SegmentTagged {100};
   std::vector<Double_t> var_SiliconAssociatedForwardMuon {100};
   std::vector<Double_t> var_Tail {100};
   std::vector<Double_t> var_Tight {100};
   std::vector<Double_t> var_VeryLoose {100};
   std::vector<Double_t> var_allAuthors {100};
   std::vector<Double_t> var_annBarrel {100};
   std::vector<Double_t> var_annEndCap {100};
   std::vector<Double_t> var_author {100};
   std::vector<Double_t> var_beta {100};
   std::vector<Double_t> var_charge {100};
   std::vector<Double_t> var_clearCache {100};
   std::vector<Double_t> var_e {100};
   std::vector<Double_t> var_energyLossType {100};
   std::vector<Double_t> var_eta {100};
   std::vector<Double_t> var_index {100};
   std::vector<Double_t> var_innAngle {100};
   std::vector<Double_t> var_m {100};
   std::vector<Double_t> var_meanDeltaADCCountsMDT {100};
   std::vector<Double_t> var_midAngle {100};
   std::vector<Double_t> var_momentumBalanceSignificance {100};
   std::vector<Double_t> var_msInnerMatchChi2 {100};
   std::vector<Double_t> var_msInnerMatchDOF {100};
   std::vector<Double_t> var_msOuterMatchChi2 {100};
   std::vector<Double_t> var_msOuterMatchDOF {100};
   std::vector<Double_t> var_muonType {100};
   std::vector<Double_t> var_passesHighPtCuts {100};
   std::vector<Double_t> var_passesIDCuts {100};
   std::vector<Double_t> var_phi {100};
   std::vector<Double_t> var_pt {100};
   std::vector<Double_t> var_quality {100};
   std::vector<Double_t> var_rapidity {100};
   std::vector<Double_t> var_scatteringCurvatureSignificance {100};
   std::vector<Double_t> var_scatteringNeighbourSignificance {100};
   std::vector<Double_t> var_segmentChi2OverDoF {100};
   std::vector<Double_t> var_segmentDeltaEta {100};
   std::vector<Double_t> var_segmentDeltaPhi {100};
   std::vector<Double_t> var_spectrometerFieldIntegral {100};
   std::vector<Double_t> var_t0 {100};
   std::vector<Double_t> var_mtype {100};
   std::vector<Double_t> var_unknown {100};
   std::vector<Double_t> var_usingPrivateStore {100};
   std::vector<Double_t> var_usingStandaloneStore {100};
   std::vector<Double_t> var_multi {100};
   std::vector<Double_t> var_mumumll {100};
   std::vector<Double_t> var_mumupt {100};
   std::vector<Double_t> var_mumueta {100};
   std::vector<Double_t> var_mumuphi {100};
   std::vector<Double_t> var_mumue {100};
   void set_HLT_mu15(Double_t* v, size_t len) {var_HLT_mu15.assign(v,v+len);}
   void set_CaloLRLikelihood(Double_t* v, size_t len) {var_CaloLRLikelihood.assign(v,v+len);}
   void set_CaloLikelihood(Double_t* v, size_t len) {var_CaloLikelihood.assign(v,v+len);}
   void set_CaloMuonIDTag(Double_t* v, size_t len) {var_CaloMuonIDTag.assign(v,v+len);}
   void set_CaloTag(Double_t* v, size_t len) {var_CaloTag.assign(v,v+len);}
   void set_CaloTagged(Double_t* v, size_t len) {var_CaloTagged.assign(v,v+len);}
   void set_Combined(Double_t* v, size_t len) {var_Combined.assign(v,v+len);}
   void set_CombinedTrackParticle(Double_t* v, size_t len) {var_CombinedTrackParticle.assign(v,v+len);}
   void set_EnergyLoss(Double_t* v, size_t len) {var_EnergyLoss.assign(v,v+len);}
   void set_EnergyLossSigma(Double_t* v, size_t len) {var_EnergyLossSigma.assign(v,v+len);}
   void set_ExtrapolateMuonToIP(Double_t* v, size_t len) {var_ExtrapolateMuonToIP.assign(v,v+len);}
   void set_FSR_CandidateEnergy(Double_t* v, size_t len) {var_FSR_CandidateEnergy.assign(v,v+len);}
   void set_FSRcandidate(Double_t* v, size_t len) {var_FSRcandidate.assign(v,v+len);}
   void set_InnerDetectorTrackParticle(Double_t* v, size_t len) {var_InnerDetectorTrackParticle.assign(v,v+len);}
   void set_Loose(Double_t* v, size_t len) {var_Loose.assign(v,v+len);}
   void set_MOP(Double_t* v, size_t len) {var_MOP.assign(v,v+len);}
   void set_MeasEnergyLoss(Double_t* v, size_t len) {var_MeasEnergyLoss.assign(v,v+len);}
   void set_MeasEnergyLossSigma(Double_t* v, size_t len) {var_MeasEnergyLossSigma.assign(v,v+len);}
   void set_Medium(Double_t* v, size_t len) {var_Medium.assign(v,v+len);}
   void set_MuGirl(Double_t* v, size_t len) {var_MuGirl.assign(v,v+len);}
   void set_MuGirlLowBeta(Double_t* v, size_t len) {var_MuGirlLowBeta.assign(v,v+len);}
   void set_MuTag(Double_t* v, size_t len) {var_MuTag.assign(v,v+len);}
   void set_MuTagIMO(Double_t* v, size_t len) {var_MuTagIMO.assign(v,v+len);}
   void set_MuidCo(Double_t* v, size_t len) {var_MuidCo.assign(v,v+len);}
   void set_MuidSA(Double_t* v, size_t len) {var_MuidSA.assign(v,v+len);}
   void set_NotIsolated(Double_t* v, size_t len) {var_NotIsolated.assign(v,v+len);}
   void set_NumberOfMuonAuthors(Double_t* v, size_t len) {var_NumberOfMuonAuthors.assign(v,v+len);}
   void set_ParamEnergyLoss(Double_t* v, size_t len) {var_ParamEnergyLoss.assign(v,v+len);}
   void set_ParamEnergyLossSigmaMinus(Double_t* v, size_t len) {var_ParamEnergyLossSigmaMinus.assign(v,v+len);}
   void set_ParamEnergyLossSigmaPlus(Double_t* v, size_t len) {var_ParamEnergyLossSigmaPlus.assign(v,v+len);}
   void set_Parametrized(Double_t* v, size_t len) {var_Parametrized.assign(v,v+len);}
   void set_Primary(Double_t* v, size_t len) {var_Primary.assign(v,v+len);}
   void set_STACO(Double_t* v, size_t len) {var_STACO.assign(v,v+len);}
   void set_SegmentTagged(Double_t* v, size_t len) {var_SegmentTagged.assign(v,v+len);}
   void set_SiliconAssociatedForwardMuon(Double_t* v, size_t len) {var_SiliconAssociatedForwardMuon.assign(v,v+len);}
   void set_Tail(Double_t* v, size_t len) {var_Tail.assign(v,v+len);}
   void set_Tight(Double_t* v, size_t len) {var_Tight.assign(v,v+len);}
   void set_VeryLoose(Double_t* v, size_t len) {var_VeryLoose.assign(v,v+len);}
   void set_allAuthors(Double_t* v, size_t len) {var_allAuthors.assign(v,v+len);}
   void set_annBarrel(Double_t* v, size_t len) {var_annBarrel.assign(v,v+len);}
   void set_annEndCap(Double_t* v, size_t len) {var_annEndCap.assign(v,v+len);}
   void set_author(Double_t* v, size_t len) {var_author.assign(v,v+len);}
   void set_beta(Double_t* v, size_t len) {var_beta.assign(v,v+len);}
   void set_charge(Double_t* v, size_t len) {var_charge.assign(v,v+len);}
   void set_clearCache(Double_t* v, size_t len) {var_clearCache.assign(v,v+len);}
   void set_e(Double_t* v, size_t len) {var_e.assign(v,v+len);}
   void set_energyLossType(Double_t* v, size_t len) {var_energyLossType.assign(v,v+len);}
   void set_eta(Double_t* v, size_t len) {var_eta.assign(v,v+len);}
   void set_index(Double_t* v, size_t len) {var_index.assign(v,v+len);}
   void set_innAngle(Double_t* v, size_t len) {var_innAngle.assign(v,v+len);}
   void set_m(Double_t* v, size_t len) {var_m.assign(v,v+len);}
   void set_meanDeltaADCCountsMDT(Double_t* v, size_t len) {var_meanDeltaADCCountsMDT.assign(v,v+len);}
   void set_midAngle(Double_t* v, size_t len) {var_midAngle.assign(v,v+len);}
   void set_momentumBalanceSignificance(Double_t* v, size_t len) {var_momentumBalanceSignificance.assign(v,v+len);}
   void set_msInnerMatchChi2(Double_t* v, size_t len) {var_msInnerMatchChi2.assign(v,v+len);}
   void set_msInnerMatchDOF(Double_t* v, size_t len) {var_msInnerMatchDOF.assign(v,v+len);}
   void set_msOuterMatchChi2(Double_t* v, size_t len) {var_msOuterMatchChi2.assign(v,v+len);}
   void set_msOuterMatchDOF(Double_t* v, size_t len) {var_msOuterMatchDOF.assign(v,v+len);}
   void set_muonType(Double_t* v, size_t len) {var_muonType.assign(v,v+len);}
   void set_passesHighPtCuts(Double_t* v, size_t len) {var_passesHighPtCuts.assign(v,v+len);}
   void set_passesIDCuts(Double_t* v, size_t len) {var_passesIDCuts.assign(v,v+len);}
   void set_phi(Double_t* v, size_t len) {var_phi.assign(v,v+len);}
   void set_pt(Double_t* v, size_t len) {var_pt.assign(v,v+len);}
   void set_quality(Double_t* v, size_t len) {var_quality.assign(v,v+len);}
   void set_rapidity(Double_t* v, size_t len) {var_rapidity.assign(v,v+len);}
   void set_scatteringCurvatureSignificance(Double_t* v, size_t len) {var_scatteringCurvatureSignificance.assign(v,v+len);}
   void set_scatteringNeighbourSignificance(Double_t* v, size_t len) {var_scatteringNeighbourSignificance.assign(v,v+len);}
   void set_segmentChi2OverDoF(Double_t* v, size_t len) {var_segmentChi2OverDoF.assign(v,v+len);}
   void set_segmentDeltaEta(Double_t* v, size_t len) {var_segmentDeltaEta.assign(v,v+len);}
   void set_segmentDeltaPhi(Double_t* v, size_t len) {var_segmentDeltaPhi.assign(v,v+len);}
   void set_spectrometerFieldIntegral(Double_t* v, size_t len) {var_spectrometerFieldIntegral.assign(v,v+len);}
   void set_t0(Double_t* v, size_t len) {var_t0.assign(v,v+len);}
   void set_mtype(Double_t* v, size_t len) {var_mtype.assign(v,v+len);}
   void set_unknown(Double_t* v, size_t len) {var_unknown.assign(v,v+len);}
   void set_usingPrivateStore(Double_t* v, size_t len) {var_usingPrivateStore.assign(v,v+len);}
   void set_usingStandaloneStore(Double_t* v, size_t len) {var_usingStandaloneStore.assign(v,v+len);}
   void set_multi(Double_t* v, size_t len) {var_multi.assign(v,v+len);}
   void set_mumumll(Double_t* v, size_t len) {var_mumumll.assign(v,v+len);}
   void set_mumupt(Double_t* v, size_t len) {var_mumupt.assign(v,v+len);}
   void set_mumueta(Double_t* v, size_t len) {var_mumueta.assign(v,v+len);}
   void set_mumuphi(Double_t* v, size_t len) {var_mumuphi.assign(v,v+len);}
   void set_mumue(Double_t* v, size_t len) {var_mumue.assign(v,v+len);}
};

class Muons {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
 //tc_t            *muon_branch;
   vector<double>  var_HLT_mu15;
   vector<double>  var_CaloLRLikelihood;
   vector<double>  var_CaloLikelihood;
   vector<double>  var_CaloMuonIDTag;
   vector<double>  var_CaloTag;
   vector<double>  var_CaloTagged;
   vector<double>  var_Combined;
   vector<double>  var_CombinedTrackParticle;
   vector<double>  var_EnergyLoss;
   vector<double>  var_EnergyLossSigma;
   vector<double>  var_ExtrapolateMuonToIP;
   vector<double>  var_FSR_CandidateEnergy;
   vector<double>  var_FSRcandidate;
   vector<double>  var_InnerDetectorTrackParticle;
   vector<double>  var_Loose;
   vector<double>  var_MOP;
   vector<double>  var_MeasEnergyLoss;
   vector<double>  var_MeasEnergyLossSigma;
   vector<double>  var_Medium;
   vector<double>  var_MuGirl;
   vector<double>  var_MuGirlLowBeta;
   vector<double>  var_MuTag;
   vector<double>  var_MuTagIMO;
   vector<double>  var_MuidCo;
   vector<double>  var_MuidSA;
   vector<double>  var_NotIsolated;
   vector<double>  var_NumberOfMuonAuthors;
   vector<double>  var_ParamEnergyLoss;
   vector<double>  var_ParamEnergyLossSigmaMinus;
   vector<double>  var_ParamEnergyLossSigmaPlus;
   vector<double>  var_Parametrized;
   vector<double>  var_Primary;
   vector<double>  var_STACO;
   vector<double>  var_SegmentTagged;
   vector<double>  var_SiliconAssociatedForwardMuon;
   vector<double>  var_Tail;
   vector<double>  var_Tight;
   vector<double>  var_VeryLoose;
   vector<double>  var_allAuthors;
   vector<double>  var_annBarrel;
   vector<double>  var_annEndCap;
   vector<double>  var_author;
   vector<double>  var_beta;
   vector<double>  var_charge;
   vector<double>  var_clearCache;
   vector<double>  var_e;
   vector<double>  var_energyLossType;
   vector<double>  var_eta;
   vector<double>  var_index;
   vector<double>  var_innAngle;
   vector<double>  var_m;
   vector<double>  var_meanDeltaADCCountsMDT;
   vector<double>  var_midAngle;
   vector<double>  var_momentumBalanceSignificance;
   vector<double>  var_msInnerMatchChi2;
   vector<double>  var_msInnerMatchDOF;
   vector<double>  var_msOuterMatchChi2;
   vector<double>  var_msOuterMatchDOF;
   vector<double>  var_muonType;
   vector<double>  var_passesHighPtCuts;
   vector<double>  var_passesIDCuts;
   vector<double>  var_phi;
   vector<double>  var_pt;
   vector<double>  var_quality;
   vector<double>  var_rapidity;
   vector<double>  var_scatteringCurvatureSignificance;
   vector<double>  var_scatteringNeighbourSignificance;
   vector<double>  var_segmentChi2OverDoF;
   vector<double>  var_segmentDeltaEta;
   vector<double>  var_segmentDeltaPhi;
   vector<double>  var_spectrometerFieldIntegral;
   vector<double>  var_t0;
   vector<double>  var_mtype;
   vector<double>  var_unknown;
   vector<double>  var_usingPrivateStore;
   vector<double>  var_usingStandaloneStore;
   vector<double>  var_multi;

   // List of branches
   TBranch        *b_muon_branch_var_HLT_mu15;   //!
   TBranch        *b_muon_branch_var_CaloLRLikelihood;   //!
   TBranch        *b_muon_branch_var_CaloLikelihood;   //!
   TBranch        *b_muon_branch_var_CaloMuonIDTag;   //!
   TBranch        *b_muon_branch_var_CaloTag;   //!
   TBranch        *b_muon_branch_var_CaloTagged;   //!
   TBranch        *b_muon_branch_var_Combined;   //!
   TBranch        *b_muon_branch_var_CombinedTrackParticle;   //!
   TBranch        *b_muon_branch_var_EnergyLoss;   //!
   TBranch        *b_muon_branch_var_EnergyLossSigma;   //!
   TBranch        *b_muon_branch_var_ExtrapolateMuonToIP;   //!
   TBranch        *b_muon_branch_var_FSR_CandidateEnergy;   //!
   TBranch        *b_muon_branch_var_FSRcandidate;   //!
   TBranch        *b_muon_branch_var_InnerDetectorTrackParticle;   //!
   TBranch        *b_muon_branch_var_Loose;   //!
   TBranch        *b_muon_branch_var_MOP;   //!
   TBranch        *b_muon_branch_var_MeasEnergyLoss;   //!
   TBranch        *b_muon_branch_var_MeasEnergyLossSigma;   //!
   TBranch        *b_muon_branch_var_Medium;   //!
   TBranch        *b_muon_branch_var_MuGirl;   //!
   TBranch        *b_muon_branch_var_MuGirlLowBeta;   //!
   TBranch        *b_muon_branch_var_MuTag;   //!
   TBranch        *b_muon_branch_var_MuTagIMO;   //!
   TBranch        *b_muon_branch_var_MuidCo;   //!
   TBranch        *b_muon_branch_var_MuidSA;   //!
   TBranch        *b_muon_branch_var_NotIsolated;   //!
   TBranch        *b_muon_branch_var_NumberOfMuonAuthors;   //!
   TBranch        *b_muon_branch_var_ParamEnergyLoss;   //!
   TBranch        *b_muon_branch_var_ParamEnergyLossSigmaMinus;   //!
   TBranch        *b_muon_branch_var_ParamEnergyLossSigmaPlus;   //!
   TBranch        *b_muon_branch_var_Parametrized;   //!
   TBranch        *b_muon_branch_var_Primary;   //!
   TBranch        *b_muon_branch_var_STACO;   //!
   TBranch        *b_muon_branch_var_SegmentTagged;   //!
   TBranch        *b_muon_branch_var_SiliconAssociatedForwardMuon;   //!
   TBranch        *b_muon_branch_var_Tail;   //!
   TBranch        *b_muon_branch_var_Tight;   //!
   TBranch        *b_muon_branch_var_VeryLoose;   //!
   TBranch        *b_muon_branch_var_allAuthors;   //!
   TBranch        *b_muon_branch_var_annBarrel;   //!
   TBranch        *b_muon_branch_var_annEndCap;   //!
   TBranch        *b_muon_branch_var_author;   //!
   TBranch        *b_muon_branch_var_beta;   //!
   TBranch        *b_muon_branch_var_charge;   //!
   TBranch        *b_muon_branch_var_clearCache;   //!
   TBranch        *b_muon_branch_var_e;   //!
   TBranch        *b_muon_branch_var_energyLossType;   //!
   TBranch        *b_muon_branch_var_eta;   //!
   TBranch        *b_muon_branch_var_index;   //!
   TBranch        *b_muon_branch_var_innAngle;   //!
   TBranch        *b_muon_branch_var_m;   //!
   TBranch        *b_muon_branch_var_meanDeltaADCCountsMDT;   //!
   TBranch        *b_muon_branch_var_midAngle;   //!
   TBranch        *b_muon_branch_var_momentumBalanceSignificance;   //!
   TBranch        *b_muon_branch_var_msInnerMatchChi2;   //!
   TBranch        *b_muon_branch_var_msInnerMatchDOF;   //!
   TBranch        *b_muon_branch_var_msOuterMatchChi2;   //!
   TBranch        *b_muon_branch_var_msOuterMatchDOF;   //!
   TBranch        *b_muon_branch_var_muonType;   //!
   TBranch        *b_muon_branch_var_passesHighPtCuts;   //!
   TBranch        *b_muon_branch_var_passesIDCuts;   //!
   TBranch        *b_muon_branch_var_phi;   //!
   TBranch        *b_muon_branch_var_pt;   //!
   TBranch        *b_muon_branch_var_quality;   //!
   TBranch        *b_muon_branch_var_rapidity;   //!
   TBranch        *b_muon_branch_var_scatteringCurvatureSignificance;   //!
   TBranch        *b_muon_branch_var_scatteringNeighbourSignificance;   //!
   TBranch        *b_muon_branch_var_segmentChi2OverDoF;   //!
   TBranch        *b_muon_branch_var_segmentDeltaEta;   //!
   TBranch        *b_muon_branch_var_segmentDeltaPhi;   //!
   TBranch        *b_muon_branch_var_spectrometerFieldIntegral;   //!
   TBranch        *b_muon_branch_var_t0;   //!
   TBranch        *b_muon_branch_var_mtype;   //!
   TBranch        *b_muon_branch_var_unknown;   //!
   TBranch        *b_muon_branch_var_usingPrivateStore;   //!
   TBranch        *b_muon_branch_var_usingStandaloneStore;   //!
   TBranch        *b_muon_branch_var_multi;   //!

   Muons(TTree *tree=0, TString FileName="data_sel.root");
   virtual ~Muons();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop(TString OutName = "out.root");
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};


Muons::Muons(TTree *tree, TString FileName="data_sel.root") : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(FileName.Data());
      if (!f || !f->IsOpen()) {
         f = new TFile(FileName.Data());
      }
      f->GetObject("Muons",tree);

   }
   Init(tree);
}

Muons::~Muons()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t Muons::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t Muons::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void Muons::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("var_HLT_mu15", &var_HLT_mu15, &b_muon_branch_var_HLT_mu15);
   fChain->SetBranchAddress("var_CaloLRLikelihood", &var_CaloLRLikelihood, &b_muon_branch_var_CaloLRLikelihood);
   fChain->SetBranchAddress("var_CaloLikelihood", &var_CaloLikelihood, &b_muon_branch_var_CaloLikelihood);
   fChain->SetBranchAddress("var_CaloMuonIDTag", &var_CaloMuonIDTag, &b_muon_branch_var_CaloMuonIDTag);
   fChain->SetBranchAddress("var_CaloTag", &var_CaloTag, &b_muon_branch_var_CaloTag);
   fChain->SetBranchAddress("var_CaloTagged", &var_CaloTagged, &b_muon_branch_var_CaloTagged);
   fChain->SetBranchAddress("var_Combined", &var_Combined, &b_muon_branch_var_Combined);
   fChain->SetBranchAddress("var_CombinedTrackParticle", &var_CombinedTrackParticle, &b_muon_branch_var_CombinedTrackParticle);
   fChain->SetBranchAddress("var_EnergyLoss", &var_EnergyLoss, &b_muon_branch_var_EnergyLoss);
   fChain->SetBranchAddress("var_EnergyLossSigma", &var_EnergyLossSigma, &b_muon_branch_var_EnergyLossSigma);
   fChain->SetBranchAddress("var_ExtrapolateMuonToIP", &var_ExtrapolateMuonToIP, &b_muon_branch_var_ExtrapolateMuonToIP);
   fChain->SetBranchAddress("var_FSR_CandidateEnergy", &var_FSR_CandidateEnergy, &b_muon_branch_var_FSR_CandidateEnergy);
   fChain->SetBranchAddress("var_FSRcandidate", &var_FSRcandidate, &b_muon_branch_var_FSRcandidate);
   fChain->SetBranchAddress("var_InnerDetectorTrackParticle", &var_InnerDetectorTrackParticle, &b_muon_branch_var_InnerDetectorTrackParticle);
   fChain->SetBranchAddress("var_Loose", &var_Loose, &b_muon_branch_var_Loose);
   fChain->SetBranchAddress("var_MOP", &var_MOP, &b_muon_branch_var_MOP);
   fChain->SetBranchAddress("var_MeasEnergyLoss", &var_MeasEnergyLoss, &b_muon_branch_var_MeasEnergyLoss);
   fChain->SetBranchAddress("var_MeasEnergyLossSigma", &var_MeasEnergyLossSigma, &b_muon_branch_var_MeasEnergyLossSigma);
   fChain->SetBranchAddress("var_Medium", &var_Medium, &b_muon_branch_var_Medium);
   fChain->SetBranchAddress("var_MuGirl", &var_MuGirl, &b_muon_branch_var_MuGirl);
   fChain->SetBranchAddress("var_MuGirlLowBeta", &var_MuGirlLowBeta, &b_muon_branch_var_MuGirlLowBeta);
   fChain->SetBranchAddress("var_MuTag", &var_MuTag, &b_muon_branch_var_MuTag);
   fChain->SetBranchAddress("var_MuTagIMO", &var_MuTagIMO, &b_muon_branch_var_MuTagIMO);
   fChain->SetBranchAddress("var_MuidCo", &var_MuidCo, &b_muon_branch_var_MuidCo);
   fChain->SetBranchAddress("var_MuidSA", &var_MuidSA, &b_muon_branch_var_MuidSA);
   fChain->SetBranchAddress("var_NotIsolated", &var_NotIsolated, &b_muon_branch_var_NotIsolated);
   fChain->SetBranchAddress("var_NumberOfMuonAuthors", &var_NumberOfMuonAuthors, &b_muon_branch_var_NumberOfMuonAuthors);
   fChain->SetBranchAddress("var_ParamEnergyLoss", &var_ParamEnergyLoss, &b_muon_branch_var_ParamEnergyLoss);
   fChain->SetBranchAddress("var_ParamEnergyLossSigmaMinus", &var_ParamEnergyLossSigmaMinus, &b_muon_branch_var_ParamEnergyLossSigmaMinus);
   fChain->SetBranchAddress("var_ParamEnergyLossSigmaPlus", &var_ParamEnergyLossSigmaPlus, &b_muon_branch_var_ParamEnergyLossSigmaPlus);
   fChain->SetBranchAddress("var_Parametrized", &var_Parametrized, &b_muon_branch_var_Parametrized);
   fChain->SetBranchAddress("var_Primary", &var_Primary, &b_muon_branch_var_Primary);
   fChain->SetBranchAddress("var_STACO", &var_STACO, &b_muon_branch_var_STACO);
   fChain->SetBranchAddress("var_SegmentTagged", &var_SegmentTagged, &b_muon_branch_var_SegmentTagged);
   fChain->SetBranchAddress("var_SiliconAssociatedForwardMuon", &var_SiliconAssociatedForwardMuon, &b_muon_branch_var_SiliconAssociatedForwardMuon);
   fChain->SetBranchAddress("var_Tail", &var_Tail, &b_muon_branch_var_Tail);
   fChain->SetBranchAddress("var_Tight", &var_Tight, &b_muon_branch_var_Tight);
   fChain->SetBranchAddress("var_VeryLoose", &var_VeryLoose, &b_muon_branch_var_VeryLoose);
   fChain->SetBranchAddress("var_allAuthors", &var_allAuthors, &b_muon_branch_var_allAuthors);
   fChain->SetBranchAddress("var_annBarrel", &var_annBarrel, &b_muon_branch_var_annBarrel);
   fChain->SetBranchAddress("var_annEndCap", &var_annEndCap, &b_muon_branch_var_annEndCap);
   fChain->SetBranchAddress("var_author", &var_author, &b_muon_branch_var_author);
   fChain->SetBranchAddress("var_beta", &var_beta, &b_muon_branch_var_beta);
   fChain->SetBranchAddress("var_charge", &var_charge, &b_muon_branch_var_charge);
   fChain->SetBranchAddress("var_clearCache", &var_clearCache, &b_muon_branch_var_clearCache);
   fChain->SetBranchAddress("var_e", &var_e, &b_muon_branch_var_e);
   fChain->SetBranchAddress("var_energyLossType", &var_energyLossType, &b_muon_branch_var_energyLossType);
   fChain->SetBranchAddress("var_eta", &var_eta, &b_muon_branch_var_eta);
   fChain->SetBranchAddress("var_index", &var_index, &b_muon_branch_var_index);
   fChain->SetBranchAddress("var_innAngle", &var_innAngle, &b_muon_branch_var_innAngle);
   fChain->SetBranchAddress("var_m", &var_m, &b_muon_branch_var_m);
   fChain->SetBranchAddress("var_meanDeltaADCCountsMDT", &var_meanDeltaADCCountsMDT, &b_muon_branch_var_meanDeltaADCCountsMDT);
   fChain->SetBranchAddress("var_midAngle", &var_midAngle, &b_muon_branch_var_midAngle);
   fChain->SetBranchAddress("var_momentumBalanceSignificance", &var_momentumBalanceSignificance, &b_muon_branch_var_momentumBalanceSignificance);
   fChain->SetBranchAddress("var_msInnerMatchChi2", &var_msInnerMatchChi2, &b_muon_branch_var_msInnerMatchChi2);
   fChain->SetBranchAddress("var_msInnerMatchDOF", &var_msInnerMatchDOF, &b_muon_branch_var_msInnerMatchDOF);
   fChain->SetBranchAddress("var_msOuterMatchChi2", &var_msOuterMatchChi2, &b_muon_branch_var_msOuterMatchChi2);
   fChain->SetBranchAddress("var_msOuterMatchDOF", &var_msOuterMatchDOF, &b_muon_branch_var_msOuterMatchDOF);
   fChain->SetBranchAddress("var_muonType", &var_muonType, &b_muon_branch_var_muonType);
   fChain->SetBranchAddress("var_passesHighPtCuts", &var_passesHighPtCuts, &b_muon_branch_var_passesHighPtCuts);
   fChain->SetBranchAddress("var_passesIDCuts", &var_passesIDCuts, &b_muon_branch_var_passesIDCuts);
   fChain->SetBranchAddress("var_phi", &var_phi, &b_muon_branch_var_phi);
   fChain->SetBranchAddress("var_pt", &var_pt, &b_muon_branch_var_pt);
   fChain->SetBranchAddress("var_quality", &var_quality, &b_muon_branch_var_quality);
   fChain->SetBranchAddress("var_rapidity", &var_rapidity, &b_muon_branch_var_rapidity);
   fChain->SetBranchAddress("var_scatteringCurvatureSignificance", &var_scatteringCurvatureSignificance, &b_muon_branch_var_scatteringCurvatureSignificance);
   fChain->SetBranchAddress("var_scatteringNeighbourSignificance", &var_scatteringNeighbourSignificance, &b_muon_branch_var_scatteringNeighbourSignificance);
   fChain->SetBranchAddress("var_segmentChi2OverDoF", &var_segmentChi2OverDoF, &b_muon_branch_var_segmentChi2OverDoF);
   fChain->SetBranchAddress("var_segmentDeltaEta", &var_segmentDeltaEta, &b_muon_branch_var_segmentDeltaEta);
   fChain->SetBranchAddress("var_segmentDeltaPhi", &var_segmentDeltaPhi, &b_muon_branch_var_segmentDeltaPhi);
   fChain->SetBranchAddress("var_spectrometerFieldIntegral", &var_spectrometerFieldIntegral, &b_muon_branch_var_spectrometerFieldIntegral);
   fChain->SetBranchAddress("var_t0", &var_t0, &b_muon_branch_var_t0);
   fChain->SetBranchAddress("var_mtype", &var_mtype, &b_muon_branch_var_mtype);
   fChain->SetBranchAddress("var_unknown", &var_unknown, &b_muon_branch_var_unknown);
   fChain->SetBranchAddress("var_usingPrivateStore", &var_usingPrivateStore, &b_muon_branch_var_usingPrivateStore);
   fChain->SetBranchAddress("var_usingStandaloneStore", &var_usingStandaloneStore, &b_muon_branch_var_usingStandaloneStore);
   fChain->SetBranchAddress("var_multi", &var_multi, &b_muon_branch_var_multi);
   Notify();
}

Bool_t Muons::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void Muons::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t Muons::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}


void Muons::Loop(TString OutName = "out.root")
{
tc_t *tc = new tc_t();
//   In a ROOT session, you can do:
//      root> .L Muons.C
//      root> Muons t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch

TFile * out= new TFile(OutName.Data(),"recreate");
TH1D * h_probes = new TH1D("h_probes", "h_probes", 22, -2.5,2.5);
TH1D * h_matches = new TH1D("h_matches", "h_matches", 22, -2.5,2.5);

TH1D * h_deltaR =  new TH1D("h_deltaR", "h_deltaR", 50, 0,10);
double eta1, eta2, phi1, phi2, deltaR;
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      for (int i=0 ; i < var_multi.size();i++){
         if (i==0){
            eta1=var_eta[i];
            phi1=var_phi[i];
         }else{
            eta2=var_eta[i];
            phi2=var_phi[i];
         }
         //if ((var_quality[0] == 3)&&(var_quality[1]==3)){
            h_probes->Fill(var_eta[i]);
            if (var_HLT_mu15[i]>0.0){
               h_matches->Fill(var_eta[i]);
            }
         //}
      }
      deltaR = TMath::Sqrt((eta1-eta2)*(eta1-eta2) + (phi1-phi2)*(phi1-phi2) );
      h_deltaR->Fill(deltaR);
      }
   
   TEfficiency * eff = new TEfficiency ( *h_matches, *h_probes);
   eff->Draw();
   //h_deltaR->Draw();
   eff->SetName("HLT_mu15");
   eff->Write();
   h_deltaR->Write();
   out->Close();
}

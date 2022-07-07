#include "Rivet/Analysis.hh"
#include "Rivet/Projections/FastJets.hh"
#include "Rivet/Projections/FinalState.hh"
#include "Rivet/Projections/IdentifiedFinalState.hh"
#include "Rivet/Projections/VetoedFinalState.hh"

#include "fastjet/JetDefinition.hh"
#include "fastjet/ClusterSequence.hh"
#include "fastjet/tools/Recluster.hh"
#include "fastjet/contrib/ModifiedMassDropTagger.hh"
#include <sstream>
#include <stdio.h> 
#include <math.h>  
#include <iostream>
#include <fstream>
using namespace std;

//#include <fastjet/config.h>
//#if ! (FASTJET_VERSION_NUMBER >= 30100)
//#error "This code requires FastJet >= 3.1.0"
//#endif

using namespace fastjet; 

namespace Rivet {

  using namespace Cuts;

  class MC_DIJET_PB_CH : public Analysis {
  public:

    //DEFAULT_RIVET_ANALYSIS_CTOR(MC_ZINCPB);

    vector<double> JET_AVG_PTMINS;    ///< minimal pt for the avg of the 2 hardest jets pt
    const double JET_MIN_PT_FRACTION; ///< 2nd hardest needs to e at least that fraction of hardest
    const double DELTA_RAP_MAX_DIJET; ///< max rapidity difference between the two jets
    const double LOG_SCALE_MAX;       ///< max value of for the log binning (abs)
    const unsigned int nRADII;        ///< number of radii under consideration
    const unsigned int nQs;           ///< number of scale values (Z ptmin) considered
    const double DELTA_RADII;         ///< radius step size
    const double PARTICLE_RAPMAX;     ///< maximal rapidity allowed for particles
    const double JET_RAPMAX;          ///< maximal rapidity allowed for jets

    MC_DIJET_PB_CH()
      : Analysis("MC_DIJET_PB_CH"),
        JET_MIN_PT_FRACTION(0.8),  // 2nd hardest is at least 0.8 * hardest
        DELTA_RAP_MAX_DIJET(1.0),
        LOG_SCALE_MAX(15.0),
        nRADII(5),
        nQs(5),
        DELTA_RADII(0.2),
        //PARTICLE_RAPMAX(2.5),
        PARTICLE_RAPMAX(2.5),
        JET_RAPMAX(1.5)
    {
      // avg of the two hardest has that minimum
      JET_AVG_PTMINS.push_back( 50.0);
      JET_AVG_PTMINS.push_back(100.0);
      JET_AVG_PTMINS.push_back(200.0);
      JET_AVG_PTMINS.push_back(400.0);
      JET_AVG_PTMINS.push_back(800.0);
    }

    void init() {
      FinalState fs(-PARTICLE_RAPMAX, PARTICLE_RAPMAX, 0.0*GeV);
      
      // for the jets
      VetoedFinalState jet_input(fs);
      jet_input.vetoNeutrinos();
      jet_input.addVetoPairId(PID::MUON);
      addProjection(jet_input, "JET_INPUT");

      // mMDT
      ca_wta_recluster = Recluster(JetDefinition(cambridge_algorithm, JetDefinition::max_allowable_R, WTA_pt_scheme),
                                   false, Recluster::keep_only_hardest);
      mmdt.reset(new contrib::ModifiedMassDropTagger(0.1));
      mmdt->set_grooming_mode();
      mmdt->set_reclustering(false);
      
      double Nbins = 100;
      double NbinsMulti = 100;
      //double NbinsMulti = 250;
      double MaxMulti = 100;
      double NbinsPt = 20;
      double MaxPt = 200; 
      _histGluonFractionPt = bookHisto1D("GluonFractionPt", 200, 0, 200);
      _histQuarkFractionPt = bookHisto1D("QuarkFractionPt", 200, 0, 200);
      _histGluonAndQuarkFractionPt = bookHisto1D("GluonAndQuarkFractionPt", 200, 0, 200);
      _histOthersThenGluonAndQuarkFractionPt = bookHisto1D("OthersThenGluonAndQuarkFractionPt", 200, 0, 200);
      _histPartonFractionPt = bookHisto1D("PartonFractionPt", 200, 0, 200);

      _histGluonMulti = bookHisto1D("GluonMulti", 10, 0, 10);
      _histQuarkMulti = bookHisto1D("QuarkMulti", 10, 0, 10);
      _histGluonAndQuarkMulti = bookHisto1D("GluonAndQuarkMulti", 10, 0, 10);
      _histOthersThenGluonAndQuarkMulti = bookHisto1D("OthersThenGluonAndQuarkMulti", 10, 0, 10);
      _histPartonMulti = bookHisto1D("PartonMulti", 10, 0, 10);

      _histPDGID = bookHisto1D("PDGID", 180, -90, 90);
      _histCONTROL_PT_RAP = bookHisto2D("CONTROL_PT_RAP", NbinsMulti, 0, MaxMulti, 100 ,-5,5);



      _histFastJets02PtSubLeading = bookHisto1D("FastJets02PtSubLeading", 50, 0, 200);
      _histFastJets02PtLeading = bookHisto1D("FastJets02PtLeading", 50, 0, 200);
      _histFastJets02PtReclust = bookHisto1D("FastJets02PtReclust", 50, 0, 200);
      
      _histFastJets02Pt = bookHisto1D("FastJets02Pt", 50, 0, 200);
      _histFastJets02Mult   = bookHisto1D("FastJets02Mult", 25, 0, 50);
      _histFastJets02E   = bookHisto1D("FastJets02E", 25, 0, 50);
      _histFastJets02Eta    = bookHisto1D("FastJets02Eta", 50, -5, 5);
      _histFastJets02Rapidity    = bookHisto1D("FastJets02Rapidity", 50, -5, 5);
      _histFastJets02Phi    = bookHisto1D("FastJets02Phi", 50, 0, TWOPI);

      _histFastJets02MultLam = bookHisto2D("FastJets02MultLam", NbinsMulti, 0.0, MaxMulti, NbinsPt, 0.0, MaxPt);  
      _histFastJets02PtLam = bookHisto2D("FastJets02PtLam", Nbins, 0.0, 1.0, NbinsPt, 0.0, MaxPt); 
      _histFastJets02LhaLam = bookHisto2D("FastJets02LhaLam", Nbins, 0.0, 1.0, NbinsPt, 0.0, MaxPt); 
      _histFastJets02WidthLam = bookHisto2D("FastJets02WidhtLam", Nbins, 0.0, 1.0, NbinsPt, 0.0, MaxPt); 
      _histFastJets02MassLam = bookHisto2D("FastJets02MassLam", Nbins, 0.0, 1.0, NbinsPt, 0.0, MaxPt);  

      _histFastJets02MultLam50 = bookHisto1D("FastJets02MultLam50", NbinsMulti, 0.0, MaxMulti);
      _histFastJets02PtLam50 = bookHisto1D("FastJets02PtLam50", Nbins, 0.0, 1.0);
      _histFastJets02LhaLam50 = bookHisto1D("FastJets02LhaLam50", Nbins, 0.0, 1.0);
      _histFastJets02WidthLam50 = bookHisto1D("FastJets02WidhtLam50", Nbins, 0.0, 1.0);
      _histFastJets02MassLam50 = bookHisto1D("FastJets02MassLam50", Nbins, 0.0, 1.0); 

      _histFastJets02MultLam100 = bookHisto1D("FastJets02MultLam100", NbinsMulti, 0.0, MaxMulti);
      _histFastJets02PtLam100 = bookHisto1D("FastJets02PtLam100", Nbins, 0.0, 1.0);
      _histFastJets02LhaLam100 = bookHisto1D("FastJets02LhaLam100", Nbins, 0.0, 1.0);
      _histFastJets02WidthLam100 = bookHisto1D("FastJets02WidhtLam100", Nbins, 0.0, 1.0);
      _histFastJets02MassLam100 = bookHisto1D("FastJets02MassLam100", Nbins, 0.0, 1.0); 

      _histFastJets02MultLam200 = bookHisto1D("FastJets02MultLam200", NbinsMulti, 0.0, MaxMulti);
      _histFastJets02PtLam200 = bookHisto1D("FastJets02PtLam200", Nbins, 0.0, 1.0);
      _histFastJets02LhaLam200 = bookHisto1D("FastJets02LhaLam200", Nbins, 0.0, 1.0);
      _histFastJets02WidthLam200 = bookHisto1D("FastJets02WidhtLam200", Nbins, 0.0, 1.0);
      _histFastJets02MassLam200 = bookHisto1D("FastJets02MassLam200", Nbins, 0.0, 1.0); 

      _histFastJets02MultLam400 = bookHisto1D("FastJets02MultLam400", NbinsMulti, 0.0, MaxMulti);
      _histFastJets02PtLam400 = bookHisto1D("FastJets02PtLam400", Nbins, 0.0, 1.0);
      _histFastJets02LhaLam400 = bookHisto1D("FastJets02LhaLam400", Nbins, 0.0, 1.0);
      _histFastJets02WidthLam400 = bookHisto1D("FastJets02WidhtLam400", Nbins, 0.0, 1.0);
      _histFastJets02MassLam400 = bookHisto1D("FastJets02MassLam400", Nbins, 0.0, 1.0);

      _histFastJets02MultLam800 = bookHisto1D("FastJets02MultLam800", NbinsMulti, 0.0, MaxMulti);
      _histFastJets02PtLam800 = bookHisto1D("FastJets02PtLam800", Nbins, 0.0, 1.0);
      _histFastJets02LhaLam800 = bookHisto1D("FastJets02LhaLam800", Nbins, 0.0, 1.0);
      _histFastJets02WidthLam800 = bookHisto1D("FastJets02WidhtLam800", Nbins, 0.0, 1.0);
      _histFastJets02MassLam800 = bookHisto1D("FastJets02MassLam800", Nbins, 0.0, 1.0);  

      _histFastJets04PtSubLeading = bookHisto1D("FastJets04PtSubLeading", 50, 0, 200);
      _histFastJets04PtLeading = bookHisto1D("FastJets04PtLeading", 50, 0, 200);
      _histFastJets04PtReclust = bookHisto1D("FastJets04PtReclust", 50, 0, 200);
      _histFastJets04Pt = bookHisto1D("FastJets04Pt", 50, 0, 200);
      _histFastJets04Mult   = bookHisto1D("FastJets04Mult", 25, 0, 50);
      _histFastJets04E   = bookHisto1D("FastJets04E", 25, 0, 50);
      _histFastJets04Eta    = bookHisto1D("FastJets04Eta", 50, -5, 5);
      _histFastJets04Rapidity    = bookHisto1D("FastJets04Rapidity", 50, -5, 5);
      _histFastJets04Phi    = bookHisto1D("FastJets04Phi", 50, 0, TWOPI);

      _histFastJets04MultLam = bookHisto2D("FastJets04MultLam", NbinsMulti, 0.0, MaxMulti, NbinsPt, 0.0, MaxPt);  
      _histFastJets04PtLam = bookHisto2D("FastJets04PtLam", Nbins, 0.0, 1.0, NbinsPt, 0.0, MaxPt); 
      _histFastJets04LhaLam = bookHisto2D("FastJets04LhaLam", Nbins, 0.0, 1.0, NbinsPt, 0.0, MaxPt); 
      _histFastJets04WidthLam = bookHisto2D("FastJets04WidhtLam", Nbins, 0.0, 1.0, NbinsPt, 0.0, MaxPt); 
      _histFastJets04MassLam = bookHisto2D("FastJets04MassLam", Nbins, 0.0, 1.0, NbinsPt, 0.0, MaxPt); 

      _histFastJets04MultLam50 = bookHisto1D("FastJets04MultLam50", NbinsMulti, 0.0, MaxMulti);
      _histFastJets04PtLam50 = bookHisto1D("FastJets04PtLam50", Nbins, 0.0, 1.0);
      _histFastJets04LhaLam50 = bookHisto1D("FastJets04LhaLam50", Nbins, 0.0, 1.0);
      _histFastJets04WidthLam50 = bookHisto1D("FastJets04WidhtLam50", Nbins, 0.0, 1.0);
      _histFastJets04MassLam50 = bookHisto1D("FastJets04MassLam50", Nbins, 0.0, 1.0); 

      _histFastJets04MultLam100 = bookHisto1D("FastJets04MultLam100", NbinsMulti, 0.0, MaxMulti);
      _histFastJets04PtLam100 = bookHisto1D("FastJets04PtLam100", Nbins, 0.0, 1.0);
      _histFastJets04LhaLam100 = bookHisto1D("FastJets04LhaLam100", Nbins, 0.0, 1.0);
      _histFastJets04WidthLam100 = bookHisto1D("FastJets04WidhtLam100", Nbins, 0.0, 1.0);
      _histFastJets04MassLam100 = bookHisto1D("FastJets04MassLam100", Nbins, 0.0, 1.0); 

      _histFastJets04MultLam200 = bookHisto1D("FastJets04MultLam200", NbinsMulti, 0.0, MaxMulti);
      _histFastJets04PtLam200 = bookHisto1D("FastJets04PtLam200", Nbins, 0.0, 1.0);
      _histFastJets04LhaLam200 = bookHisto1D("FastJets04LhaLam200", Nbins, 0.0, 1.0);
      _histFastJets04WidthLam200 = bookHisto1D("FastJets04WidhtLam200", Nbins, 0.0, 1.0);
      _histFastJets04MassLam200 = bookHisto1D("FastJets04MassLam200", Nbins, 0.0, 1.0); 

      _histFastJets04MultLam400 = bookHisto1D("FastJets04MultLam400", NbinsMulti, 0.0, MaxMulti);
      _histFastJets04PtLam400 = bookHisto1D("FastJets04PtLam400", Nbins, 0.0, 1.0);
      _histFastJets04LhaLam400 = bookHisto1D("FastJets04LhaLam400", Nbins, 0.0, 1.0);
      _histFastJets04WidthLam400 = bookHisto1D("FastJets04WidhtLam400", Nbins, 0.0, 1.0);
      _histFastJets04MassLam400 = bookHisto1D("FastJets04MassLam400", Nbins, 0.0, 1.0);

      _histFastJets04MultLam800 = bookHisto1D("FastJets04MultLam800", NbinsMulti, 0.0, MaxMulti);
      _histFastJets04PtLam800 = bookHisto1D("FastJets04PtLam800", Nbins, 0.0, 1.0);
      _histFastJets04LhaLam800 = bookHisto1D("FastJets04LhaLam800", Nbins, 0.0, 1.0);
      _histFastJets04WidthLam800 = bookHisto1D("FastJets04WidhtLam800", Nbins, 0.0, 1.0);
      _histFastJets04MassLam800 = bookHisto1D("FastJets04MassLam800", Nbins, 0.0, 1.0);  

      _histFastJets06PtSubLeading = bookHisto1D("FastJets06PtSubLeading", 50, 0, 200);
      _histFastJets06PtLeading = bookHisto1D("FastJets06PtLeading", 50, 0, 200);
      _histFastJets06PtReclust = bookHisto1D("FastJets06PtReclust", 50, 0, 200);
      _histFastJets06Pt = bookHisto1D("FastJets06Pt", 50, 0, 200);
      _histFastJets06Mult   = bookHisto1D("FastJets06Mult", 25, 0, 50);
      _histFastJets06E   = bookHisto1D("FastJets06E", 25, 0, 50);
      _histFastJets06Eta    = bookHisto1D("FastJets06Eta", 50, -5, 5);
      _histFastJets06Rapidity    = bookHisto1D("FastJets06Rapidity", 50, -5, 5);
      _histFastJets06Phi    = bookHisto1D("FastJets06Phi", 50, 0, TWOPI);

      _histFastJets06MultLam = bookHisto2D("FastJets06MultLam", NbinsMulti, 0.0, MaxMulti, NbinsPt, 0.0, MaxPt);  
      _histFastJets06PtLam = bookHisto2D("FastJets06PtLam", Nbins, 0.0, 1.0, NbinsPt, 0.0, MaxPt); 
      _histFastJets06LhaLam = bookHisto2D("FastJets06LhaLam", Nbins, 0.0, 1.0, NbinsPt, 0.0, MaxPt); 
      _histFastJets06WidthLam = bookHisto2D("FastJets06WidhtLam", Nbins, 0.0, 1.0, NbinsPt, 0.0, MaxPt); 
      _histFastJets06MassLam = bookHisto2D("FastJets06MassLam", Nbins, 0.0, 1.0, NbinsPt, 0.0, MaxPt); 

      _histFastJets06MultLam50 = bookHisto1D("FastJets06MultLam50", NbinsMulti, 0.0, MaxMulti);
      _histFastJets06PtLam50 = bookHisto1D("FastJets06PtLam50", Nbins, 0.0, 1.0);
      _histFastJets06LhaLam50 = bookHisto1D("FastJets06LhaLam50", Nbins, 0.0, 1.0);
      _histFastJets06WidthLam50 = bookHisto1D("FastJets06WidhtLam50", Nbins, 0.0, 1.0);
      _histFastJets06MassLam50 = bookHisto1D("FastJets06MassLam50", Nbins, 0.0, 1.0); 

      _histFastJets06MultLam100 = bookHisto1D("FastJets06MultLam100", NbinsMulti, 0.0, MaxMulti);
      _histFastJets06PtLam100 = bookHisto1D("FastJets06PtLam100", Nbins, 0.0, 1.0);
      _histFastJets06LhaLam100 = bookHisto1D("FastJets06LhaLam100", Nbins, 0.0, 1.0);
      _histFastJets06WidthLam100 = bookHisto1D("FastJets06WidhtLam100", Nbins, 0.0, 1.0);
      _histFastJets06MassLam100 = bookHisto1D("FastJets06MassLam100", Nbins, 0.0, 1.0); 

      _histFastJets06MultLam200 = bookHisto1D("FastJets06MultLam200", NbinsMulti, 0.0, MaxMulti);
      _histFastJets06PtLam200 = bookHisto1D("FastJets06PtLam200", Nbins, 0.0, 1.0);
      _histFastJets06LhaLam200 = bookHisto1D("FastJets06LhaLam200", Nbins, 0.0, 1.0);
      _histFastJets06WidthLam200 = bookHisto1D("FastJets06WidhtLam200", Nbins, 0.0, 1.0);
      _histFastJets06MassLam200 = bookHisto1D("FastJets06MassLam200", Nbins, 0.0, 1.0); 

      _histFastJets06MultLam400 = bookHisto1D("FastJets06MultLam400", NbinsMulti, 0.0, MaxMulti);
      _histFastJets06PtLam400 = bookHisto1D("FastJets06PtLam400", Nbins, 0.0, 1.0);
      _histFastJets06LhaLam400 = bookHisto1D("FastJets06LhaLam400", Nbins, 0.0, 1.0);
      _histFastJets06WidthLam400 = bookHisto1D("FastJets06WidhtLam400", Nbins, 0.0, 1.0);
      _histFastJets06MassLam400 = bookHisto1D("FastJets06MassLam400", Nbins, 0.0, 1.0);

      _histFastJets06MultLam800 = bookHisto1D("FastJets06MultLam800", NbinsMulti, 0.0, MaxMulti);
      _histFastJets06PtLam800 = bookHisto1D("FastJets06PtLam800", Nbins, 0.0, 1.0);
      _histFastJets06LhaLam800 = bookHisto1D("FastJets06LhaLam800", Nbins, 0.0, 1.0);
      _histFastJets06WidthLam800 = bookHisto1D("FastJets06WidhtLam800", Nbins, 0.0, 1.0);
      _histFastJets06MassLam800 = bookHisto1D("FastJets06MassLam800", Nbins, 0.0, 1.0);  

      _histFastJets08PtSubLeading = bookHisto1D("FastJets08PtSubLeading", 50, 0, 200);
      _histFastJets08PtLeading = bookHisto1D("FastJets08PtLeading", 50, 0, 200);
      _histFastJets08PtReclust = bookHisto1D("FastJets08PtReclust", 50, 0, 200);
      _histFastJets08Pt = bookHisto1D("FastJets08Pt", 50, 0, 200);
      _histFastJets08Mult   = bookHisto1D("FastJets08Mult", 25, 0, 50);
      _histFastJets08E   = bookHisto1D("FastJets08E", 25, 0, 50);
      _histFastJets08Eta    = bookHisto1D("FastJets08Eta", 50, -5, 5);
      _histFastJets08Rapidity    = bookHisto1D("FastJets08Rapidity", 50, -5, 5);
      _histFastJets08Phi    = bookHisto1D("FastJets08Phi", 50, 0, TWOPI);

      _histFastJets08MultLam = bookHisto2D("FastJets08MultLam", NbinsMulti, 0.0, MaxMulti, NbinsPt, 0.0, MaxPt);  
      _histFastJets08PtLam = bookHisto2D("FastJets08PtLam", Nbins, 0.0, 1.0, NbinsPt, 0.0, MaxPt); 
      _histFastJets08LhaLam = bookHisto2D("FastJets08LhaLam", Nbins, 0.0, 1.0, NbinsPt, 0.0, MaxPt); 
      _histFastJets08WidthLam = bookHisto2D("FastJets08WidhtLam", Nbins, 0.0, 1.0, NbinsPt, 0.0, MaxPt); 
      _histFastJets08MassLam = bookHisto2D("FastJets08MassLam", Nbins, 0.0, 1.0, NbinsPt, 0.0, MaxPt); 

      _histFastJets08MultLam50 = bookHisto1D("FastJets08MultLam50", NbinsMulti, 0.0, MaxMulti);
      _histFastJets08PtLam50 = bookHisto1D("FastJets08PtLam50", Nbins, 0.0, 1.0);
      _histFastJets08LhaLam50 = bookHisto1D("FastJets08LhaLam50", Nbins, 0.0, 1.0);
      _histFastJets08WidthLam50 = bookHisto1D("FastJets08WidhtLam50", Nbins, 0.0, 1.0);
      _histFastJets08MassLam50 = bookHisto1D("FastJets08MassLam50", Nbins, 0.0, 1.0); 

      _histFastJets08MultLam100 = bookHisto1D("FastJets08MultLam100", NbinsMulti, 0.0, MaxMulti);
      _histFastJets08PtLam100 = bookHisto1D("FastJets08PtLam100", Nbins, 0.0, 1.0);
      _histFastJets08LhaLam100 = bookHisto1D("FastJets08LhaLam100", Nbins, 0.0, 1.0);
      _histFastJets08WidthLam100 = bookHisto1D("FastJets08WidhtLam100", Nbins, 0.0, 1.0);
      _histFastJets08MassLam100 = bookHisto1D("FastJets08MassLam100", Nbins, 0.0, 1.0); 

      _histFastJets08MultLam200 = bookHisto1D("FastJets08MultLam200", NbinsMulti, 0.0, MaxMulti);
      _histFastJets08PtLam200 = bookHisto1D("FastJets08PtLam200", Nbins, 0.0, 1.0);
      _histFastJets08LhaLam200 = bookHisto1D("FastJets08LhaLam200", Nbins, 0.0, 1.0);
      _histFastJets08WidthLam200 = bookHisto1D("FastJets08WidhtLam200", Nbins, 0.0, 1.0);
      _histFastJets08MassLam200 = bookHisto1D("FastJets08MassLam200", Nbins, 0.0, 1.0); 

      _histFastJets08MultLam400 = bookHisto1D("FastJets08MultLam400", NbinsMulti, 0.0, MaxMulti);
      _histFastJets08PtLam400 = bookHisto1D("FastJets08PtLam400", Nbins, 0.0, 1.0);
      _histFastJets08LhaLam400 = bookHisto1D("FastJets08LhaLam400", Nbins, 0.0, 1.0);
      _histFastJets08WidthLam400 = bookHisto1D("FastJets08WidhtLam400", Nbins, 0.0, 1.0);
      _histFastJets08MassLam400 = bookHisto1D("FastJets08MassLam400", Nbins, 0.0, 1.0);

      _histFastJets08MultLam800 = bookHisto1D("FastJets08MultLam800", NbinsMulti, 0.0, MaxMulti);
      _histFastJets08PtLam800 = bookHisto1D("FastJets08PtLam800", Nbins, 0.0, 1.0);
      _histFastJets08LhaLam800 = bookHisto1D("FastJets08LhaLam800", Nbins, 0.0, 1.0);
      _histFastJets08WidthLam800 = bookHisto1D("FastJets08WidhtLam800", Nbins, 0.0, 1.0);
      _histFastJets08MassLam800 = bookHisto1D("FastJets08MassLam800", Nbins, 0.0, 1.0);  

      _histFastJets10PtSubLeading = bookHisto1D("FastJets10PtSubLeading", 50, 0, 200);
      _histFastJets10PtLeading = bookHisto1D("FastJets10PtLeading", 50, 0, 200);
      _histFastJets10PtReclust = bookHisto1D("FastJets10PtReclust", 50, 0, 200);
      _histFastJets10Pt = bookHisto1D("FastJets10Pt", 50, 0, 200);
      _histFastJets10Mult   = bookHisto1D("FastJets10Mult", 25, 0, 50);
      _histFastJets10E   = bookHisto1D("FastJets10E", 25, 0, 50);
      _histFastJets10Eta    = bookHisto1D("FastJets10Eta", 50, -5, 5);
      _histFastJets10Rapidity    = bookHisto1D("FastJets10Rapidity", 50, -5, 5);
      _histFastJets10Phi    = bookHisto1D("FastJets10Phi", 50, 0, TWOPI);

      _histFastJets10MultLam = bookHisto2D("FastJets10MultLam", NbinsMulti, 0.0, MaxMulti, NbinsPt, 0.0, MaxPt);  
      _histFastJets10PtLam = bookHisto2D("FastJets10PtLam", Nbins, 0.0, 1.0, NbinsPt, 0.0, MaxPt); 
      _histFastJets10LhaLam = bookHisto2D("FastJets10LhaLam", Nbins, 0.0, 1.0, NbinsPt, 0.0, MaxPt); 
      _histFastJets10WidthLam = bookHisto2D("FastJets10WidhtLam", Nbins, 0.0, 1.0, NbinsPt, 0.0, MaxPt); 
      _histFastJets10MassLam = bookHisto2D("FastJets10MassLam", Nbins, 0.0, 1.0, NbinsPt, 0.0, MaxPt); 

      _histFastJets10MultLam50 = bookHisto1D("FastJets10MultLam50", NbinsMulti, 0.0, MaxMulti);
      _histFastJets10PtLam50 = bookHisto1D("FastJets10PtLam50", Nbins, 0.0, 1.0);
      _histFastJets10LhaLam50 = bookHisto1D("FastJets10LhaLam50", Nbins, 0.0, 1.0);
      _histFastJets10WidthLam50 = bookHisto1D("FastJets10WidhtLam50", Nbins, 0.0, 1.0);
      _histFastJets10MassLam50 = bookHisto1D("FastJets10MassLam50", Nbins, 0.0, 1.0); 

      _histFastJets10MultLam100 = bookHisto1D("FastJets10MultLam100", NbinsMulti, 0.0, MaxMulti);
      _histFastJets10PtLam100 = bookHisto1D("FastJets10PtLam100", Nbins, 0.0, 1.0);
      _histFastJets10LhaLam100 = bookHisto1D("FastJets10LhaLam100", Nbins, 0.0, 1.0);
      _histFastJets10WidthLam100 = bookHisto1D("FastJets10WidhtLam100", Nbins, 0.0, 1.0);
      _histFastJets10MassLam100 = bookHisto1D("FastJets10MassLam100", Nbins, 0.0, 1.0); 

      _histFastJets10MultLam200 = bookHisto1D("FastJets10MultLam200", NbinsMulti, 0.0, MaxMulti);
      _histFastJets10PtLam200 = bookHisto1D("FastJets10PtLam200", Nbins, 0.0, 1.0);
      _histFastJets10LhaLam200 = bookHisto1D("FastJets10LhaLam200", Nbins, 0.0, 1.0);
      _histFastJets10WidthLam200 = bookHisto1D("FastJets10WidhtLam200", Nbins, 0.0, 1.0);
      _histFastJets10MassLam200 = bookHisto1D("FastJets10MassLam200", Nbins, 0.0, 1.0); 

      _histFastJets10MultLam400 = bookHisto1D("FastJets10MultLam400", NbinsMulti, 0.0, MaxMulti);
      _histFastJets10PtLam400 = bookHisto1D("FastJets10PtLam400", Nbins, 0.0, 1.0);
      _histFastJets10LhaLam400 = bookHisto1D("FastJets10LhaLam400", Nbins, 0.0, 1.0);
      _histFastJets10WidthLam400 = bookHisto1D("FastJets10WidhtLam400", Nbins, 0.0, 1.0);
      _histFastJets10MassLam400 = bookHisto1D("FastJets10MassLam400", Nbins, 0.0, 1.0);

      _histFastJets10MultLam800 = bookHisto1D("FastJets10MultLam800", NbinsMulti, 0.0, MaxMulti);
      _histFastJets10PtLam800 = bookHisto1D("FastJets10PtLam800", Nbins, 0.0, 1.0);
      _histFastJets10LhaLam800 = bookHisto1D("FastJets10LhaLam800", Nbins, 0.0, 1.0);
      _histFastJets10WidthLam800 = bookHisto1D("FastJets10WidhtLam800", Nbins, 0.0, 1.0);
      _histFastJets10MassLam800 = bookHisto1D("FastJets10MassLam800", Nbins, 0.0, 1.0);  

      ArrayOfHist[0][0] = _histFastJets02PtSubLeading;
      ArrayOfHist[0][1] = _histFastJets02PtLeading;
      ArrayOfHist[0][2] = _histFastJets02PtReclust;
      ArrayOfHist[0][3] = _histFastJets02Pt;
      ArrayOfHist[0][4] = _histFastJets02Mult;
      ArrayOfHist[0][5] = _histFastJets02E;
      ArrayOfHist[0][6] = _histFastJets02Eta;
      ArrayOfHist[0][7] = _histFastJets02Rapidity;
      ArrayOfHist[0][8] = _histFastJets02Phi;
      ArrayOfHist2[0][9] = _histFastJets02MultLam;
      ArrayOfHist2[0][10] = _histFastJets02PtLam;
      ArrayOfHist2[0][11] = _histFastJets02LhaLam;
      ArrayOfHist2[0][12] = _histFastJets02WidthLam;
      ArrayOfHist2[0][13] = _histFastJets02MassLam;

      ArrayOfHist[0][14] = _histFastJets02MultLam50;
      ArrayOfHist[0][15] = _histFastJets02PtLam50;
      ArrayOfHist[0][16] = _histFastJets02LhaLam50;
      ArrayOfHist[0][17] = _histFastJets02WidthLam50;
      ArrayOfHist[0][18] = _histFastJets02MassLam50;     
      ArrayOfHist[0][19] = _histFastJets02MultLam100;
      ArrayOfHist[0][20] = _histFastJets02PtLam100;
      ArrayOfHist[0][21] = _histFastJets02LhaLam100;
      ArrayOfHist[0][22] = _histFastJets02WidthLam100;
      ArrayOfHist[0][23] = _histFastJets02MassLam100;
      ArrayOfHist[0][24] = _histFastJets02MultLam200;
      ArrayOfHist[0][25] = _histFastJets02PtLam200;
      ArrayOfHist[0][26] = _histFastJets02LhaLam200;
      ArrayOfHist[0][27] = _histFastJets02WidthLam200;
      ArrayOfHist[0][28] = _histFastJets02MassLam200;
      ArrayOfHist[0][29] = _histFastJets02MultLam400;
      ArrayOfHist[0][30] = _histFastJets02PtLam400;
      ArrayOfHist[0][31] = _histFastJets02LhaLam400;
      ArrayOfHist[0][32] = _histFastJets02WidthLam400;
      ArrayOfHist[0][33] = _histFastJets02MassLam400;
      ArrayOfHist[0][34] = _histFastJets02MultLam800;
      ArrayOfHist[0][35] = _histFastJets02PtLam800;
      ArrayOfHist[0][36] = _histFastJets02LhaLam800;
      ArrayOfHist[0][37] = _histFastJets02WidthLam800;
      ArrayOfHist[0][38] = _histFastJets02MassLam800;

      ArrayOfHist[1][0] = _histFastJets04PtSubLeading;
      ArrayOfHist[1][1] = _histFastJets04PtLeading;
      ArrayOfHist[1][2] = _histFastJets04PtReclust;
      ArrayOfHist[1][3] = _histFastJets04Pt;
      ArrayOfHist[1][4] = _histFastJets04Mult;
      ArrayOfHist[1][5] = _histFastJets04E;
      ArrayOfHist[1][6] = _histFastJets04Eta;
      ArrayOfHist[1][7] = _histFastJets04Rapidity;
      ArrayOfHist[1][8] = _histFastJets04Phi;
      ArrayOfHist2[1][9] = _histFastJets04MultLam;
      ArrayOfHist2[1][10] = _histFastJets04PtLam;
      ArrayOfHist2[1][11] = _histFastJets04LhaLam;
      ArrayOfHist2[1][12] = _histFastJets04WidthLam;
      ArrayOfHist2[1][13] = _histFastJets04MassLam;

      ArrayOfHist[1][14] = _histFastJets04MultLam50;
      ArrayOfHist[1][15] = _histFastJets04PtLam50;
      ArrayOfHist[1][16] = _histFastJets04LhaLam50;
      ArrayOfHist[1][17] = _histFastJets04WidthLam50;
      ArrayOfHist[1][18] = _histFastJets04MassLam50;     
      ArrayOfHist[1][19] = _histFastJets04MultLam100;
      ArrayOfHist[1][20] = _histFastJets04PtLam100;
      ArrayOfHist[1][21] = _histFastJets04LhaLam100;
      ArrayOfHist[1][22] = _histFastJets04WidthLam100;
      ArrayOfHist[1][23] = _histFastJets04MassLam100;
      ArrayOfHist[1][24] = _histFastJets04MultLam200;
      ArrayOfHist[1][25] = _histFastJets04PtLam200;
      ArrayOfHist[1][26] = _histFastJets04LhaLam200;
      ArrayOfHist[1][27] = _histFastJets04WidthLam200;
      ArrayOfHist[1][28] = _histFastJets04MassLam200;
      ArrayOfHist[1][29] = _histFastJets04MultLam400;
      ArrayOfHist[1][30] = _histFastJets04PtLam400;
      ArrayOfHist[1][31] = _histFastJets04LhaLam400;
      ArrayOfHist[1][32] = _histFastJets04WidthLam400;
      ArrayOfHist[1][33] = _histFastJets04MassLam400;
      ArrayOfHist[1][34] = _histFastJets04MultLam800;
      ArrayOfHist[1][35] = _histFastJets04PtLam800;
      ArrayOfHist[1][36] = _histFastJets04LhaLam800;
      ArrayOfHist[1][37] = _histFastJets04WidthLam800;
      ArrayOfHist[1][38] = _histFastJets04MassLam800;
      
      ArrayOfHist[2][0] = _histFastJets06PtSubLeading;
      ArrayOfHist[2][1] = _histFastJets06PtLeading;
      ArrayOfHist[2][2] = _histFastJets06PtReclust;
      ArrayOfHist[2][3] = _histFastJets06Pt;
      ArrayOfHist[2][4] = _histFastJets06Mult;
      ArrayOfHist[2][5] = _histFastJets06E;
      ArrayOfHist[2][6] = _histFastJets06Eta;
      ArrayOfHist[2][7] = _histFastJets06Rapidity;
      ArrayOfHist[2][8] = _histFastJets06Phi;
      ArrayOfHist2[2][9] = _histFastJets06MultLam;
      ArrayOfHist2[2][10] = _histFastJets06PtLam;
      ArrayOfHist2[2][11] = _histFastJets06LhaLam;
      ArrayOfHist2[2][12] = _histFastJets06WidthLam;
      ArrayOfHist2[2][13] = _histFastJets06MassLam;

      ArrayOfHist[2][14] = _histFastJets06MultLam50;
      ArrayOfHist[2][15] = _histFastJets06PtLam50;
      ArrayOfHist[2][16] = _histFastJets06LhaLam50;
      ArrayOfHist[2][17] = _histFastJets06WidthLam50;
      ArrayOfHist[2][18] = _histFastJets06MassLam50;     
      ArrayOfHist[2][19] = _histFastJets06MultLam100;
      ArrayOfHist[2][20] = _histFastJets06PtLam100;
      ArrayOfHist[2][21] = _histFastJets06LhaLam100;
      ArrayOfHist[2][22] = _histFastJets06WidthLam100;
      ArrayOfHist[2][23] = _histFastJets06MassLam100;
      ArrayOfHist[2][24] = _histFastJets06MultLam200;
      ArrayOfHist[2][25] = _histFastJets06PtLam200;
      ArrayOfHist[2][26] = _histFastJets06LhaLam200;
      ArrayOfHist[2][27] = _histFastJets06WidthLam200;
      ArrayOfHist[2][28] = _histFastJets06MassLam200;
      ArrayOfHist[2][29] = _histFastJets06MultLam400;
      ArrayOfHist[2][30] = _histFastJets06PtLam400;
      ArrayOfHist[2][31] = _histFastJets06LhaLam400;
      ArrayOfHist[2][32] = _histFastJets06WidthLam400;
      ArrayOfHist[2][33] = _histFastJets06MassLam400;
      ArrayOfHist[2][34] = _histFastJets06MultLam800;
      ArrayOfHist[2][35] = _histFastJets06PtLam800;
      ArrayOfHist[2][36] = _histFastJets06LhaLam800;
      ArrayOfHist[2][37] = _histFastJets06WidthLam800;
      ArrayOfHist[2][38] = _histFastJets06MassLam800;
      
      ArrayOfHist[3][0] = _histFastJets08PtSubLeading;
      ArrayOfHist[3][1] = _histFastJets08PtLeading;
      ArrayOfHist[3][2] = _histFastJets08PtReclust;
      ArrayOfHist[3][3] = _histFastJets08Pt;
      ArrayOfHist[3][4] = _histFastJets08Mult;
      ArrayOfHist[3][5] = _histFastJets08E;
      ArrayOfHist[3][6] = _histFastJets08Eta;
      ArrayOfHist[3][7] = _histFastJets08Rapidity;
      ArrayOfHist[3][8] = _histFastJets08Phi;
      ArrayOfHist2[3][9] = _histFastJets08MultLam;
      ArrayOfHist2[3][10] = _histFastJets08PtLam;
      ArrayOfHist2[3][11] = _histFastJets08LhaLam;
      ArrayOfHist2[3][12] = _histFastJets08WidthLam;
      ArrayOfHist2[3][13] = _histFastJets08MassLam;

      ArrayOfHist[3][14] = _histFastJets08MultLam50;
      ArrayOfHist[3][15] = _histFastJets08PtLam50;
      ArrayOfHist[3][16] = _histFastJets08LhaLam50;
      ArrayOfHist[3][17] = _histFastJets08WidthLam50;
      ArrayOfHist[3][18] = _histFastJets08MassLam50;     
      ArrayOfHist[3][19] = _histFastJets08MultLam100;
      ArrayOfHist[3][20] = _histFastJets08PtLam100;
      ArrayOfHist[3][21] = _histFastJets08LhaLam100;
      ArrayOfHist[3][22] = _histFastJets08WidthLam100;
      ArrayOfHist[3][23] = _histFastJets08MassLam100;
      ArrayOfHist[3][24] = _histFastJets08MultLam200;
      ArrayOfHist[3][25] = _histFastJets08PtLam200;
      ArrayOfHist[3][26] = _histFastJets08LhaLam200;
      ArrayOfHist[3][27] = _histFastJets08WidthLam200;
      ArrayOfHist[3][28] = _histFastJets08MassLam200;
      ArrayOfHist[3][29] = _histFastJets08MultLam400;
      ArrayOfHist[3][30] = _histFastJets08PtLam400;
      ArrayOfHist[3][31] = _histFastJets08LhaLam400;
      ArrayOfHist[3][32] = _histFastJets08WidthLam400;
      ArrayOfHist[3][33] = _histFastJets08MassLam400;
      ArrayOfHist[3][34] = _histFastJets08MultLam800;
      ArrayOfHist[3][35] = _histFastJets08PtLam800;
      ArrayOfHist[3][36] = _histFastJets08LhaLam800;
      ArrayOfHist[3][37] = _histFastJets08WidthLam800;
      ArrayOfHist[3][38] = _histFastJets08MassLam800;
      
      ArrayOfHist[4][0] = _histFastJets10PtSubLeading;
      ArrayOfHist[4][1] = _histFastJets10PtLeading;
      ArrayOfHist[4][2] = _histFastJets10PtReclust;
      ArrayOfHist[4][3] = _histFastJets10Pt;
      ArrayOfHist[4][4] = _histFastJets10Mult;
      ArrayOfHist[4][5] = _histFastJets10E;
      ArrayOfHist[4][6] = _histFastJets10Eta;
      ArrayOfHist[4][7] = _histFastJets10Rapidity;
      ArrayOfHist[4][8] = _histFastJets10Phi;
      ArrayOfHist2[4][9] = _histFastJets10MultLam;
      ArrayOfHist2[4][10] = _histFastJets10PtLam;
      ArrayOfHist2[4][11] = _histFastJets10LhaLam;
      ArrayOfHist2[4][12] = _histFastJets10WidthLam;
      ArrayOfHist2[4][13] = _histFastJets10MassLam;

      ArrayOfHist[4][14] = _histFastJets10MultLam50;
      ArrayOfHist[4][15] = _histFastJets10PtLam50;
      ArrayOfHist[4][16] = _histFastJets10LhaLam50;
      ArrayOfHist[4][17] = _histFastJets10WidthLam50;
      ArrayOfHist[4][18] = _histFastJets10MassLam50;     
      ArrayOfHist[4][19] = _histFastJets10MultLam100;
      ArrayOfHist[4][20] = _histFastJets10PtLam100;
      ArrayOfHist[4][21] = _histFastJets10LhaLam100;
      ArrayOfHist[4][22] = _histFastJets10WidthLam100;
      ArrayOfHist[4][23] = _histFastJets10MassLam100;
      ArrayOfHist[4][24] = _histFastJets10MultLam200;
      ArrayOfHist[4][25] = _histFastJets10PtLam200;
      ArrayOfHist[4][26] = _histFastJets10LhaLam200;
      ArrayOfHist[4][27] = _histFastJets10WidthLam200;
      ArrayOfHist[4][28] = _histFastJets10MassLam200;
      ArrayOfHist[4][29] = _histFastJets10MultLam400;
      ArrayOfHist[4][30] = _histFastJets10PtLam400;
      ArrayOfHist[4][31] = _histFastJets10LhaLam400;
      ArrayOfHist[4][32] = _histFastJets10WidthLam400;
      ArrayOfHist[4][33] = _histFastJets10MassLam400;
      ArrayOfHist[4][34] = _histFastJets10MultLam800;
      ArrayOfHist[4][35] = _histFastJets10PtLam800;
      ArrayOfHist[4][36] = _histFastJets10LhaLam800;
      ArrayOfHist[4][37] = _histFastJets10WidthLam800;
      ArrayOfHist[4][38] = _histFastJets10MassLam800;

      //mmdt hists

            mmdt_histFastJets02PtSubLeading = bookHisto1D("mmdt_FastJets02PtSubLeading", 50, 0, 200);
      mmdt_histFastJets02PtLeading = bookHisto1D("mmdt_FastJets02PtLeading", 50, 0, 200);
      mmdt_histFastJets02PtReclust = bookHisto1D("mmdt_FastJets02PtReclust", 50, 0, 200);
      
      mmdt_histFastJets02Pt = bookHisto1D("mmdt_FastJets02Pt", 50, 0, 200);
      mmdt_histFastJets02Mult   = bookHisto1D("mmdt_FastJets02Mult", 25, 0, 50);
      mmdt_histFastJets02E   = bookHisto1D("mmdt_FastJets02E", 25, 0, 50);
      mmdt_histFastJets02Eta    = bookHisto1D("mmdt_FastJets02Eta", 50, -5, 5);
      mmdt_histFastJets02Rapidity    = bookHisto1D("mmdt_FastJets02Rapidity", 50, -5, 5);
      mmdt_histFastJets02Phi    = bookHisto1D("mmdt_FastJets02Phi", 50, 0, TWOPI);

      mmdt_histFastJets02MultLam = bookHisto2D("mmdt_FastJets02MultLam", NbinsMulti, 0.0, MaxMulti, NbinsPt, 0.0, MaxPt);  
      mmdt_histFastJets02PtLam = bookHisto2D("mmdt_FastJets02PtLam", Nbins, 0.0, 1.0, NbinsPt, 0.0, MaxPt); 
      mmdt_histFastJets02LhaLam = bookHisto2D("mmdt_FastJets02LhaLam", Nbins, 0.0, 1.0, NbinsPt, 0.0, MaxPt); 
      mmdt_histFastJets02WidthLam = bookHisto2D("mmdt_FastJets02WidhtLam", Nbins, 0.0, 1.0, NbinsPt, 0.0, MaxPt); 
      mmdt_histFastJets02MassLam = bookHisto2D("mmdt_FastJets02MassLam", Nbins, 0.0, 1.0, NbinsPt, 0.0, MaxPt);  

      mmdt_histFastJets02MultLam50 = bookHisto1D("mmdt_FastJets02MultLam50", NbinsMulti, 0.0, MaxMulti);
      mmdt_histFastJets02PtLam50 = bookHisto1D("mmdt_FastJets02PtLam50", Nbins, 0.0, 1.0);
      mmdt_histFastJets02LhaLam50 = bookHisto1D("mmdt_FastJets02LhaLam50", Nbins, 0.0, 1.0);
      mmdt_histFastJets02WidthLam50 = bookHisto1D("mmdt_FastJets02WidhtLam50", Nbins, 0.0, 1.0);
      mmdt_histFastJets02MassLam50 = bookHisto1D("mmdt_FastJets02MassLam50", Nbins, 0.0, 1.0); 

      mmdt_histFastJets02MultLam100 = bookHisto1D("mmdt_FastJets02MultLam100", NbinsMulti, 0.0, MaxMulti);
      mmdt_histFastJets02PtLam100 = bookHisto1D("mmdt_FastJets02PtLam100", Nbins, 0.0, 1.0);
      mmdt_histFastJets02LhaLam100 = bookHisto1D("mmdt_FastJets02LhaLam100", Nbins, 0.0, 1.0);
      mmdt_histFastJets02WidthLam100 = bookHisto1D("mmdt_FastJets02WidhtLam100", Nbins, 0.0, 1.0);
      mmdt_histFastJets02MassLam100 = bookHisto1D("mmdt_FastJets02MassLam100", Nbins, 0.0, 1.0); 

      mmdt_histFastJets02MultLam200 = bookHisto1D("mmdt_FastJets02MultLam200", NbinsMulti, 0.0, MaxMulti);
      mmdt_histFastJets02PtLam200 = bookHisto1D("mmdt_FastJets02PtLam200", Nbins, 0.0, 1.0);
      mmdt_histFastJets02LhaLam200 = bookHisto1D("mmdt_FastJets02LhaLam200", Nbins, 0.0, 1.0);
      mmdt_histFastJets02WidthLam200 = bookHisto1D("mmdt_FastJets02WidhtLam200", Nbins, 0.0, 1.0);
      mmdt_histFastJets02MassLam200 = bookHisto1D("mmdt_FastJets02MassLam200", Nbins, 0.0, 1.0); 

      mmdt_histFastJets02MultLam400 = bookHisto1D("mmdt_FastJets02MultLam400", NbinsMulti, 0.0, MaxMulti);
      mmdt_histFastJets02PtLam400 = bookHisto1D("mmdt_FastJets02PtLam400", Nbins, 0.0, 1.0);
      mmdt_histFastJets02LhaLam400 = bookHisto1D("mmdt_FastJets02LhaLam400", Nbins, 0.0, 1.0);
      mmdt_histFastJets02WidthLam400 = bookHisto1D("mmdt_FastJets02WidhtLam400", Nbins, 0.0, 1.0);
      mmdt_histFastJets02MassLam400 = bookHisto1D("mmdt_FastJets02MassLam400", Nbins, 0.0, 1.0);

      mmdt_histFastJets02MultLam800 = bookHisto1D("mmdt_FastJets02MultLam800", NbinsMulti, 0.0, MaxMulti);
      mmdt_histFastJets02PtLam800 = bookHisto1D("mmdt_FastJets02PtLam800", Nbins, 0.0, 1.0);
      mmdt_histFastJets02LhaLam800 = bookHisto1D("mmdt_FastJets02LhaLam800", Nbins, 0.0, 1.0);
      mmdt_histFastJets02WidthLam800 = bookHisto1D("mmdt_FastJets02WidhtLam800", Nbins, 0.0, 1.0);
      mmdt_histFastJets02MassLam800 = bookHisto1D("mmdt_FastJets02MassLam800", Nbins, 0.0, 1.0);  

      mmdt_histFastJets04PtSubLeading = bookHisto1D("mmdt_FastJets04PtSubLeading", 50, 0, 200);
      mmdt_histFastJets04PtLeading = bookHisto1D("mmdt_FastJets04PtLeading", 50, 0, 200);
      mmdt_histFastJets04PtReclust = bookHisto1D("mmdt_FastJets04PtReclust", 50, 0, 200);
      mmdt_histFastJets04Pt = bookHisto1D("mmdt_FastJets04Pt", 50, 0, 200);
      mmdt_histFastJets04Mult   = bookHisto1D("mmdt_FastJets04Mult", 25, 0, 50);
      mmdt_histFastJets04E   = bookHisto1D("mmdt_FastJets04E", 25, 0, 50);
      mmdt_histFastJets04Eta    = bookHisto1D("mmdt_FastJets04Eta", 50, -5, 5);
      mmdt_histFastJets04Rapidity    = bookHisto1D("mmdt_FastJets04Rapidity", 50, -5, 5);
      mmdt_histFastJets04Phi    = bookHisto1D("mmdt_FastJets04Phi", 50, 0, TWOPI);

      mmdt_histFastJets04MultLam = bookHisto2D("mmdt_FastJets04MultLam", NbinsMulti, 0.0, MaxMulti, NbinsPt, 0.0, MaxPt);  
      mmdt_histFastJets04PtLam = bookHisto2D("mmdt_FastJets04PtLam", Nbins, 0.0, 1.0, NbinsPt, 0.0, MaxPt); 
      mmdt_histFastJets04LhaLam = bookHisto2D("mmdt_FastJets04LhaLam", Nbins, 0.0, 1.0, NbinsPt, 0.0, MaxPt); 
      mmdt_histFastJets04WidthLam = bookHisto2D("mmdt_FastJets04WidhtLam", Nbins, 0.0, 1.0, NbinsPt, 0.0, MaxPt); 
      mmdt_histFastJets04MassLam = bookHisto2D("mmdt_FastJets04MassLam", Nbins, 0.0, 1.0, NbinsPt, 0.0, MaxPt); 

      mmdt_histFastJets04MultLam50 = bookHisto1D("mmdt_FastJets04MultLam50", NbinsMulti, 0.0, MaxMulti);
      mmdt_histFastJets04PtLam50 = bookHisto1D("mmdt_FastJets04PtLam50", Nbins, 0.0, 1.0);
      mmdt_histFastJets04LhaLam50 = bookHisto1D("mmdt_FastJets04LhaLam50", Nbins, 0.0, 1.0);
      mmdt_histFastJets04WidthLam50 = bookHisto1D("mmdt_FastJets04WidhtLam50", Nbins, 0.0, 1.0);
      mmdt_histFastJets04MassLam50 = bookHisto1D("mmdt_FastJets04MassLam50", Nbins, 0.0, 1.0); 

      mmdt_histFastJets04MultLam100 = bookHisto1D("mmdt_FastJets04MultLam100", NbinsMulti, 0.0, MaxMulti);
      mmdt_histFastJets04PtLam100 = bookHisto1D("mmdt_FastJets04PtLam100", Nbins, 0.0, 1.0);
      mmdt_histFastJets04LhaLam100 = bookHisto1D("mmdt_FastJets04LhaLam100", Nbins, 0.0, 1.0);
      mmdt_histFastJets04WidthLam100 = bookHisto1D("mmdt_FastJets04WidhtLam100", Nbins, 0.0, 1.0);
      mmdt_histFastJets04MassLam100 = bookHisto1D("mmdt_FastJets04MassLam100", Nbins, 0.0, 1.0); 

      mmdt_histFastJets04MultLam200 = bookHisto1D("mmdt_FastJets04MultLam200", NbinsMulti, 0.0, MaxMulti);
      mmdt_histFastJets04PtLam200 = bookHisto1D("mmdt_FastJets04PtLam200", Nbins, 0.0, 1.0);
      mmdt_histFastJets04LhaLam200 = bookHisto1D("mmdt_FastJets04LhaLam200", Nbins, 0.0, 1.0);
      mmdt_histFastJets04WidthLam200 = bookHisto1D("mmdt_FastJets04WidhtLam200", Nbins, 0.0, 1.0);
      mmdt_histFastJets04MassLam200 = bookHisto1D("mmdt_FastJets04MassLam200", Nbins, 0.0, 1.0); 

      mmdt_histFastJets04MultLam400 = bookHisto1D("mmdt_FastJets04MultLam400", NbinsMulti, 0.0, MaxMulti);
      mmdt_histFastJets04PtLam400 = bookHisto1D("mmdt_FastJets04PtLam400", Nbins, 0.0, 1.0);
      mmdt_histFastJets04LhaLam400 = bookHisto1D("mmdt_FastJets04LhaLam400", Nbins, 0.0, 1.0);
      mmdt_histFastJets04WidthLam400 = bookHisto1D("mmdt_FastJets04WidhtLam400", Nbins, 0.0, 1.0);
      mmdt_histFastJets04MassLam400 = bookHisto1D("mmdt_FastJets04MassLam400", Nbins, 0.0, 1.0);

      mmdt_histFastJets04MultLam800 = bookHisto1D("mmdt_FastJets04MultLam800", NbinsMulti, 0.0, MaxMulti);
      mmdt_histFastJets04PtLam800 = bookHisto1D("mmdt_FastJets04PtLam800", Nbins, 0.0, 1.0);
      mmdt_histFastJets04LhaLam800 = bookHisto1D("mmdt_FastJets04LhaLam800", Nbins, 0.0, 1.0);
      mmdt_histFastJets04WidthLam800 = bookHisto1D("mmdt_FastJets04WidhtLam800", Nbins, 0.0, 1.0);
      mmdt_histFastJets04MassLam800 = bookHisto1D("mmdt_FastJets04MassLam800", Nbins, 0.0, 1.0);  

      mmdt_histFastJets06PtSubLeading = bookHisto1D("mmdt_FastJets06PtSubLeading", 50, 0, 200);
      mmdt_histFastJets06PtLeading = bookHisto1D("mmdt_FastJets06PtLeading", 50, 0, 200);
      mmdt_histFastJets06PtReclust = bookHisto1D("mmdt_FastJets06PtReclust", 50, 0, 200);
      mmdt_histFastJets06Pt = bookHisto1D("mmdt_FastJets06Pt", 50, 0, 200);
      mmdt_histFastJets06Mult   = bookHisto1D("mmdt_FastJets06Mult", 25, 0, 50);
      mmdt_histFastJets06E   = bookHisto1D("mmdt_FastJets06E", 25, 0, 50);
      mmdt_histFastJets06Eta    = bookHisto1D("mmdt_FastJets06Eta", 50, -5, 5);
      mmdt_histFastJets06Rapidity    = bookHisto1D("mmdt_FastJets06Rapidity", 50, -5, 5);
      mmdt_histFastJets06Phi    = bookHisto1D("mmdt_FastJets06Phi", 50, 0, TWOPI);

      mmdt_histFastJets06MultLam = bookHisto2D("mmdt_FastJets06MultLam", NbinsMulti, 0.0, MaxMulti, NbinsPt, 0.0, MaxPt);  
      mmdt_histFastJets06PtLam = bookHisto2D("mmdt_FastJets06PtLam", Nbins, 0.0, 1.0, NbinsPt, 0.0, MaxPt); 
      mmdt_histFastJets06LhaLam = bookHisto2D("mmdt_FastJets06LhaLam", Nbins, 0.0, 1.0, NbinsPt, 0.0, MaxPt); 
      mmdt_histFastJets06WidthLam = bookHisto2D("mmdt_FastJets06WidhtLam", Nbins, 0.0, 1.0, NbinsPt, 0.0, MaxPt); 
      mmdt_histFastJets06MassLam = bookHisto2D("mmdt_FastJets06MassLam", Nbins, 0.0, 1.0, NbinsPt, 0.0, MaxPt); 

      mmdt_histFastJets06MultLam50 = bookHisto1D("mmdt_FastJets06MultLam50", NbinsMulti, 0.0, MaxMulti);
      mmdt_histFastJets06PtLam50 = bookHisto1D("mmdt_FastJets06PtLam50", Nbins, 0.0, 1.0);
      mmdt_histFastJets06LhaLam50 = bookHisto1D("mmdt_FastJets06LhaLam50", Nbins, 0.0, 1.0);
      mmdt_histFastJets06WidthLam50 = bookHisto1D("mmdt_FastJets06WidhtLam50", Nbins, 0.0, 1.0);
      mmdt_histFastJets06MassLam50 = bookHisto1D("mmdt_FastJets06MassLam50", Nbins, 0.0, 1.0); 

      mmdt_histFastJets06MultLam100 = bookHisto1D("mmdt_FastJets06MultLam100", NbinsMulti, 0.0, MaxMulti);
      mmdt_histFastJets06PtLam100 = bookHisto1D("mmdt_FastJets06PtLam100", Nbins, 0.0, 1.0);
      mmdt_histFastJets06LhaLam100 = bookHisto1D("mmdt_FastJets06LhaLam100", Nbins, 0.0, 1.0);
      mmdt_histFastJets06WidthLam100 = bookHisto1D("mmdt_FastJets06WidhtLam100", Nbins, 0.0, 1.0);
      mmdt_histFastJets06MassLam100 = bookHisto1D("mmdt_FastJets06MassLam100", Nbins, 0.0, 1.0); 

      mmdt_histFastJets06MultLam200 = bookHisto1D("mmdt_FastJets06MultLam200", NbinsMulti, 0.0, MaxMulti);
      mmdt_histFastJets06PtLam200 = bookHisto1D("mmdt_FastJets06PtLam200", Nbins, 0.0, 1.0);
      mmdt_histFastJets06LhaLam200 = bookHisto1D("mmdt_FastJets06LhaLam200", Nbins, 0.0, 1.0);
      mmdt_histFastJets06WidthLam200 = bookHisto1D("mmdt_FastJets06WidhtLam200", Nbins, 0.0, 1.0);
      mmdt_histFastJets06MassLam200 = bookHisto1D("mmdt_FastJets06MassLam200", Nbins, 0.0, 1.0); 

      mmdt_histFastJets06MultLam400 = bookHisto1D("mmdt_FastJets06MultLam400", NbinsMulti, 0.0, MaxMulti);
      mmdt_histFastJets06PtLam400 = bookHisto1D("mmdt_FastJets06PtLam400", Nbins, 0.0, 1.0);
      mmdt_histFastJets06LhaLam400 = bookHisto1D("mmdt_FastJets06LhaLam400", Nbins, 0.0, 1.0);
      mmdt_histFastJets06WidthLam400 = bookHisto1D("mmdt_FastJets06WidhtLam400", Nbins, 0.0, 1.0);
      mmdt_histFastJets06MassLam400 = bookHisto1D("mmdt_FastJets06MassLam400", Nbins, 0.0, 1.0);

      mmdt_histFastJets06MultLam800 = bookHisto1D("mmdt_FastJets06MultLam800", NbinsMulti, 0.0, MaxMulti);
      mmdt_histFastJets06PtLam800 = bookHisto1D("mmdt_FastJets06PtLam800", Nbins, 0.0, 1.0);
      mmdt_histFastJets06LhaLam800 = bookHisto1D("mmdt_FastJets06LhaLam800", Nbins, 0.0, 1.0);
      mmdt_histFastJets06WidthLam800 = bookHisto1D("mmdt_FastJets06WidhtLam800", Nbins, 0.0, 1.0);
      mmdt_histFastJets06MassLam800 = bookHisto1D("mmdt_FastJets06MassLam800", Nbins, 0.0, 1.0);  

      mmdt_histFastJets08PtSubLeading = bookHisto1D("mmdt_FastJets08PtSubLeading", 50, 0, 200);
      mmdt_histFastJets08PtLeading = bookHisto1D("mmdt_FastJets08PtLeading", 50, 0, 200);
      mmdt_histFastJets08PtReclust = bookHisto1D("mmdt_FastJets08PtReclust", 50, 0, 200);
      mmdt_histFastJets08Pt = bookHisto1D("mmdt_FastJets08Pt", 50, 0, 200);
      mmdt_histFastJets08Mult   = bookHisto1D("mmdt_FastJets08Mult", 25, 0, 50);
      mmdt_histFastJets08E   = bookHisto1D("mmdt_FastJets08E", 25, 0, 50);
      mmdt_histFastJets08Eta    = bookHisto1D("mmdt_FastJets08Eta", 50, -5, 5);
      mmdt_histFastJets08Rapidity    = bookHisto1D("mmdt_FastJets08Rapidity", 50, -5, 5);
      mmdt_histFastJets08Phi    = bookHisto1D("mmdt_FastJets08Phi", 50, 0, TWOPI);

      mmdt_histFastJets08MultLam = bookHisto2D("mmdt_FastJets08MultLam", NbinsMulti, 0.0, MaxMulti, NbinsPt, 0.0, MaxPt);  
      mmdt_histFastJets08PtLam = bookHisto2D("mmdt_FastJets08PtLam", Nbins, 0.0, 1.0, NbinsPt, 0.0, MaxPt); 
      mmdt_histFastJets08LhaLam = bookHisto2D("mmdt_FastJets08LhaLam", Nbins, 0.0, 1.0, NbinsPt, 0.0, MaxPt); 
      mmdt_histFastJets08WidthLam = bookHisto2D("mmdt_FastJets08WidhtLam", Nbins, 0.0, 1.0, NbinsPt, 0.0, MaxPt); 
      mmdt_histFastJets08MassLam = bookHisto2D("mmdt_FastJets08MassLam", Nbins, 0.0, 1.0, NbinsPt, 0.0, MaxPt); 

      mmdt_histFastJets08MultLam50 = bookHisto1D("mmdt_FastJets08MultLam50", NbinsMulti, 0.0, MaxMulti);
      mmdt_histFastJets08PtLam50 = bookHisto1D("mmdt_FastJets08PtLam50", Nbins, 0.0, 1.0);
      mmdt_histFastJets08LhaLam50 = bookHisto1D("mmdt_FastJets08LhaLam50", Nbins, 0.0, 1.0);
      mmdt_histFastJets08WidthLam50 = bookHisto1D("mmdt_FastJets08WidhtLam50", Nbins, 0.0, 1.0);
      mmdt_histFastJets08MassLam50 = bookHisto1D("mmdt_FastJets08MassLam50", Nbins, 0.0, 1.0); 

      mmdt_histFastJets08MultLam100 = bookHisto1D("mmdt_FastJets08MultLam100", NbinsMulti, 0.0, MaxMulti);
      mmdt_histFastJets08PtLam100 = bookHisto1D("mmdt_FastJets08PtLam100", Nbins, 0.0, 1.0);
      mmdt_histFastJets08LhaLam100 = bookHisto1D("mmdt_FastJets08LhaLam100", Nbins, 0.0, 1.0);
      mmdt_histFastJets08WidthLam100 = bookHisto1D("mmdt_FastJets08WidhtLam100", Nbins, 0.0, 1.0);
      mmdt_histFastJets08MassLam100 = bookHisto1D("mmdt_FastJets08MassLam100", Nbins, 0.0, 1.0); 

      mmdt_histFastJets08MultLam200 = bookHisto1D("mmdt_FastJets08MultLam200", NbinsMulti, 0.0, MaxMulti);
      mmdt_histFastJets08PtLam200 = bookHisto1D("mmdt_FastJets08PtLam200", Nbins, 0.0, 1.0);
      mmdt_histFastJets08LhaLam200 = bookHisto1D("mmdt_FastJets08LhaLam200", Nbins, 0.0, 1.0);
      mmdt_histFastJets08WidthLam200 = bookHisto1D("mmdt_FastJets08WidhtLam200", Nbins, 0.0, 1.0);
      mmdt_histFastJets08MassLam200 = bookHisto1D("mmdt_FastJets08MassLam200", Nbins, 0.0, 1.0); 

      mmdt_histFastJets08MultLam400 = bookHisto1D("mmdt_FastJets08MultLam400", NbinsMulti, 0.0, MaxMulti);
      mmdt_histFastJets08PtLam400 = bookHisto1D("mmdt_FastJets08PtLam400", Nbins, 0.0, 1.0);
      mmdt_histFastJets08LhaLam400 = bookHisto1D("mmdt_FastJets08LhaLam400", Nbins, 0.0, 1.0);
      mmdt_histFastJets08WidthLam400 = bookHisto1D("mmdt_FastJets08WidhtLam400", Nbins, 0.0, 1.0);
      mmdt_histFastJets08MassLam400 = bookHisto1D("mmdt_FastJets08MassLam400", Nbins, 0.0, 1.0);

      mmdt_histFastJets08MultLam800 = bookHisto1D("mmdt_FastJets08MultLam800", NbinsMulti, 0.0, MaxMulti);
      mmdt_histFastJets08PtLam800 = bookHisto1D("mmdt_FastJets08PtLam800", Nbins, 0.0, 1.0);
      mmdt_histFastJets08LhaLam800 = bookHisto1D("mmdt_FastJets08LhaLam800", Nbins, 0.0, 1.0);
      mmdt_histFastJets08WidthLam800 = bookHisto1D("mmdt_FastJets08WidhtLam800", Nbins, 0.0, 1.0);
      mmdt_histFastJets08MassLam800 = bookHisto1D("mmdt_FastJets08MassLam800", Nbins, 0.0, 1.0);  

      mmdt_histFastJets10PtSubLeading = bookHisto1D("mmdt_FastJets10PtSubLeading", 50, 0, 200);
      mmdt_histFastJets10PtLeading = bookHisto1D("mmdt_FastJets10PtLeading", 50, 0, 200);
      mmdt_histFastJets10PtReclust = bookHisto1D("mmdt_FastJets10PtReclust", 50, 0, 200);
      mmdt_histFastJets10Pt = bookHisto1D("mmdt_FastJets10Pt", 50, 0, 200);
      mmdt_histFastJets10Mult   = bookHisto1D("mmdt_FastJets10Mult", 25, 0, 50);
      mmdt_histFastJets10E   = bookHisto1D("mmdt_FastJets10E", 25, 0, 50);
      mmdt_histFastJets10Eta    = bookHisto1D("mmdt_FastJets10Eta", 50, -5, 5);
      mmdt_histFastJets10Rapidity    = bookHisto1D("mmdt_FastJets10Rapidity", 50, -5, 5);
      mmdt_histFastJets10Phi    = bookHisto1D("mmdt_FastJets10Phi", 50, 0, TWOPI);

      mmdt_histFastJets10MultLam = bookHisto2D("mmdt_FastJets10MultLam", NbinsMulti, 0.0, MaxMulti, NbinsPt, 0.0, MaxPt);  
      mmdt_histFastJets10PtLam = bookHisto2D("mmdt_FastJets10PtLam", Nbins, 0.0, 1.0, NbinsPt, 0.0, MaxPt); 
      mmdt_histFastJets10LhaLam = bookHisto2D("mmdt_FastJets10LhaLam", Nbins, 0.0, 1.0, NbinsPt, 0.0, MaxPt); 
      mmdt_histFastJets10WidthLam = bookHisto2D("mmdt_FastJets10WidhtLam", Nbins, 0.0, 1.0, NbinsPt, 0.0, MaxPt); 
      mmdt_histFastJets10MassLam = bookHisto2D("mmdt_FastJets10MassLam", Nbins, 0.0, 1.0, NbinsPt, 0.0, MaxPt); 

      mmdt_histFastJets10MultLam50 = bookHisto1D("mmdt_FastJets10MultLam50", NbinsMulti, 0.0, MaxMulti);
      mmdt_histFastJets10PtLam50 = bookHisto1D("mmdt_FastJets10PtLam50", Nbins, 0.0, 1.0);
      mmdt_histFastJets10LhaLam50 = bookHisto1D("mmdt_FastJets10LhaLam50", Nbins, 0.0, 1.0);
      mmdt_histFastJets10WidthLam50 = bookHisto1D("mmdt_FastJets10WidhtLam50", Nbins, 0.0, 1.0);
      mmdt_histFastJets10MassLam50 = bookHisto1D("mmdt_FastJets10MassLam50", Nbins, 0.0, 1.0); 

      mmdt_histFastJets10MultLam100 = bookHisto1D("mmdt_FastJets10MultLam100", NbinsMulti, 0.0, MaxMulti);
      mmdt_histFastJets10PtLam100 = bookHisto1D("mmdt_FastJets10PtLam100", Nbins, 0.0, 1.0);
      mmdt_histFastJets10LhaLam100 = bookHisto1D("mmdt_FastJets10LhaLam100", Nbins, 0.0, 1.0);
      mmdt_histFastJets10WidthLam100 = bookHisto1D("mmdt_FastJets10WidhtLam100", Nbins, 0.0, 1.0);
      mmdt_histFastJets10MassLam100 = bookHisto1D("mmdt_FastJets10MassLam100", Nbins, 0.0, 1.0); 

      mmdt_histFastJets10MultLam200 = bookHisto1D("mmdt_FastJets10MultLam200", NbinsMulti, 0.0, MaxMulti);
      mmdt_histFastJets10PtLam200 = bookHisto1D("mmdt_FastJets10PtLam200", Nbins, 0.0, 1.0);
      mmdt_histFastJets10LhaLam200 = bookHisto1D("mmdt_FastJets10LhaLam200", Nbins, 0.0, 1.0);
      mmdt_histFastJets10WidthLam200 = bookHisto1D("mmdt_FastJets10WidhtLam200", Nbins, 0.0, 1.0);
      mmdt_histFastJets10MassLam200 = bookHisto1D("mmdt_FastJets10MassLam200", Nbins, 0.0, 1.0); 

      mmdt_histFastJets10MultLam400 = bookHisto1D("mmdt_FastJets10MultLam400", NbinsMulti, 0.0, MaxMulti);
      mmdt_histFastJets10PtLam400 = bookHisto1D("mmdt_FastJets10PtLam400", Nbins, 0.0, 1.0);
      mmdt_histFastJets10LhaLam400 = bookHisto1D("mmdt_FastJets10LhaLam400", Nbins, 0.0, 1.0);
      mmdt_histFastJets10WidthLam400 = bookHisto1D("mmdt_FastJets10WidhtLam400", Nbins, 0.0, 1.0);
      mmdt_histFastJets10MassLam400 = bookHisto1D("mmdt_FastJets10MassLam400", Nbins, 0.0, 1.0);

      mmdt_histFastJets10MultLam800 = bookHisto1D("mmdt_FastJets10MultLam800", NbinsMulti, 0.0, MaxMulti);
      mmdt_histFastJets10PtLam800 = bookHisto1D("mmdt_FastJets10PtLam800", Nbins, 0.0, 1.0);
      mmdt_histFastJets10LhaLam800 = bookHisto1D("mmdt_FastJets10LhaLam800", Nbins, 0.0, 1.0);
      mmdt_histFastJets10WidthLam800 = bookHisto1D("mmdt_FastJets10WidhtLam800", Nbins, 0.0, 1.0);
      mmdt_histFastJets10MassLam800 = bookHisto1D("mmdt_FastJets10MassLam800", Nbins, 0.0, 1.0);

      mmdt_ArrayOfHist[0][0]   = mmdt_histFastJets02PtSubLeading;
      mmdt_ArrayOfHist[0][1]   = mmdt_histFastJets02PtLeading;
      mmdt_ArrayOfHist[0][2]   = mmdt_histFastJets02PtReclust;
      mmdt_ArrayOfHist[0][3]   = mmdt_histFastJets02Pt;
      mmdt_ArrayOfHist[0][4]   = mmdt_histFastJets02Mult;
      mmdt_ArrayOfHist[0][5]   = mmdt_histFastJets02E;
      mmdt_ArrayOfHist[0][6]   = mmdt_histFastJets02Eta;
      mmdt_ArrayOfHist[0][7]   = mmdt_histFastJets02Rapidity;
      mmdt_ArrayOfHist[0][8]   = mmdt_histFastJets02Phi;
      mmdt_ArrayOfHist2[0][9]  = mmdt_histFastJets02MultLam;
      mmdt_ArrayOfHist2[0][10] = mmdt_histFastJets02PtLam;
      mmdt_ArrayOfHist2[0][11] = mmdt_histFastJets02LhaLam;
      mmdt_ArrayOfHist2[0][12] = mmdt_histFastJets02WidthLam;
      mmdt_ArrayOfHist2[0][13] = mmdt_histFastJets02MassLam;

      mmdt_ArrayOfHist[0][14] = mmdt_histFastJets02MultLam50;
      mmdt_ArrayOfHist[0][15] = mmdt_histFastJets02PtLam50;
      mmdt_ArrayOfHist[0][16] = mmdt_histFastJets02LhaLam50;
      mmdt_ArrayOfHist[0][17] = mmdt_histFastJets02WidthLam50;
      mmdt_ArrayOfHist[0][18] = mmdt_histFastJets02MassLam50;     
      mmdt_ArrayOfHist[0][19] = mmdt_histFastJets02MultLam100;
      mmdt_ArrayOfHist[0][20] = mmdt_histFastJets02PtLam100;
      mmdt_ArrayOfHist[0][21] = mmdt_histFastJets02LhaLam100;
      mmdt_ArrayOfHist[0][22] = mmdt_histFastJets02WidthLam100;
      mmdt_ArrayOfHist[0][23] = mmdt_histFastJets02MassLam100;
      mmdt_ArrayOfHist[0][24] = mmdt_histFastJets02MultLam200;
      mmdt_ArrayOfHist[0][25] = mmdt_histFastJets02PtLam200;
      mmdt_ArrayOfHist[0][26] = mmdt_histFastJets02LhaLam200;
      mmdt_ArrayOfHist[0][27] = mmdt_histFastJets02WidthLam200;
      mmdt_ArrayOfHist[0][28] = mmdt_histFastJets02MassLam200;
      mmdt_ArrayOfHist[0][29] = mmdt_histFastJets02MultLam400;
      mmdt_ArrayOfHist[0][30] = mmdt_histFastJets02PtLam400;
      mmdt_ArrayOfHist[0][31] = mmdt_histFastJets02LhaLam400;
      mmdt_ArrayOfHist[0][32] = mmdt_histFastJets02WidthLam400;
      mmdt_ArrayOfHist[0][33] = mmdt_histFastJets02MassLam400;
      mmdt_ArrayOfHist[0][34] = mmdt_histFastJets02MultLam800;
      mmdt_ArrayOfHist[0][35] = mmdt_histFastJets02PtLam800;
      mmdt_ArrayOfHist[0][36] = mmdt_histFastJets02LhaLam800;
      mmdt_ArrayOfHist[0][37] = mmdt_histFastJets02WidthLam800;
      mmdt_ArrayOfHist[0][38] = mmdt_histFastJets02MassLam800;

      mmdt_ArrayOfHist[1][0]   = mmdt_histFastJets04PtSubLeading;
      mmdt_ArrayOfHist[1][1]   = mmdt_histFastJets04PtLeading;
      mmdt_ArrayOfHist[1][2]   = mmdt_histFastJets04PtReclust;
      mmdt_ArrayOfHist[1][3]   = mmdt_histFastJets04Pt;
      mmdt_ArrayOfHist[1][4]   = mmdt_histFastJets04Mult;
      mmdt_ArrayOfHist[1][5]   = mmdt_histFastJets04E;
      mmdt_ArrayOfHist[1][6]   = mmdt_histFastJets04Eta;
      mmdt_ArrayOfHist[1][7]   = mmdt_histFastJets04Rapidity;
      mmdt_ArrayOfHist[1][8]   = mmdt_histFastJets04Phi;
      mmdt_ArrayOfHist2[1][9]  = mmdt_histFastJets04MultLam;
      mmdt_ArrayOfHist2[1][10] = mmdt_histFastJets04PtLam;
      mmdt_ArrayOfHist2[1][11] = mmdt_histFastJets04LhaLam;
      mmdt_ArrayOfHist2[1][12] = mmdt_histFastJets04WidthLam;
      mmdt_ArrayOfHist2[1][13] = mmdt_histFastJets04MassLam;

      mmdt_ArrayOfHist[1][14] = mmdt_histFastJets04MultLam50;
      mmdt_ArrayOfHist[1][15] = mmdt_histFastJets04PtLam50;
      mmdt_ArrayOfHist[1][16] = mmdt_histFastJets04LhaLam50;
      mmdt_ArrayOfHist[1][17] = mmdt_histFastJets04WidthLam50;
      mmdt_ArrayOfHist[1][18] = mmdt_histFastJets04MassLam50;     
      mmdt_ArrayOfHist[1][19] = mmdt_histFastJets04MultLam100;
      mmdt_ArrayOfHist[1][20] = mmdt_histFastJets04PtLam100;
      mmdt_ArrayOfHist[1][21] = mmdt_histFastJets04LhaLam100;
      mmdt_ArrayOfHist[1][22] = mmdt_histFastJets04WidthLam100;
      mmdt_ArrayOfHist[1][23] = mmdt_histFastJets04MassLam100;
      mmdt_ArrayOfHist[1][24] = mmdt_histFastJets04MultLam200;
      mmdt_ArrayOfHist[1][25] = mmdt_histFastJets04PtLam200;
      mmdt_ArrayOfHist[1][26] = mmdt_histFastJets04LhaLam200;
      mmdt_ArrayOfHist[1][27] = mmdt_histFastJets04WidthLam200;
      mmdt_ArrayOfHist[1][28] = mmdt_histFastJets04MassLam200;
      mmdt_ArrayOfHist[1][29] = mmdt_histFastJets04MultLam400;
      mmdt_ArrayOfHist[1][30] = mmdt_histFastJets04PtLam400;
      mmdt_ArrayOfHist[1][31] = mmdt_histFastJets04LhaLam400;
      mmdt_ArrayOfHist[1][32] = mmdt_histFastJets04WidthLam400;
      mmdt_ArrayOfHist[1][33] = mmdt_histFastJets04MassLam400;
      mmdt_ArrayOfHist[1][34] = mmdt_histFastJets04MultLam800;
      mmdt_ArrayOfHist[1][35] = mmdt_histFastJets04PtLam800;
      mmdt_ArrayOfHist[1][36] = mmdt_histFastJets04LhaLam800;
      mmdt_ArrayOfHist[1][37] = mmdt_histFastJets04WidthLam800;
      mmdt_ArrayOfHist[1][38] = mmdt_histFastJets04MassLam800;
      
      mmdt_ArrayOfHist[2][0]   = mmdt_histFastJets06PtSubLeading;
      mmdt_ArrayOfHist[2][1]   = mmdt_histFastJets06PtLeading;
      mmdt_ArrayOfHist[2][2]   = mmdt_histFastJets06PtReclust;
      mmdt_ArrayOfHist[2][3]   = mmdt_histFastJets06Pt;
      mmdt_ArrayOfHist[2][4]   = mmdt_histFastJets06Mult;
      mmdt_ArrayOfHist[2][5]   = mmdt_histFastJets06E;
      mmdt_ArrayOfHist[2][6]   = mmdt_histFastJets06Eta;
      mmdt_ArrayOfHist[2][7]   = mmdt_histFastJets06Rapidity;
      mmdt_ArrayOfHist[2][8]   = mmdt_histFastJets06Phi;
      mmdt_ArrayOfHist2[2][9]  = mmdt_histFastJets06MultLam;
      mmdt_ArrayOfHist2[2][10] = mmdt_histFastJets06PtLam;
      mmdt_ArrayOfHist2[2][11] = mmdt_histFastJets06LhaLam;
      mmdt_ArrayOfHist2[2][12] = mmdt_histFastJets06WidthLam;
      mmdt_ArrayOfHist2[2][13] = mmdt_histFastJets06MassLam;

      mmdt_ArrayOfHist[2][14] = mmdt_histFastJets06MultLam50;
      mmdt_ArrayOfHist[2][15] = mmdt_histFastJets06PtLam50;
      mmdt_ArrayOfHist[2][16] = mmdt_histFastJets06LhaLam50;
      mmdt_ArrayOfHist[2][17] = mmdt_histFastJets06WidthLam50;
      mmdt_ArrayOfHist[2][18] = mmdt_histFastJets06MassLam50;     
      mmdt_ArrayOfHist[2][19] = mmdt_histFastJets06MultLam100;
      mmdt_ArrayOfHist[2][20] = mmdt_histFastJets06PtLam100;
      mmdt_ArrayOfHist[2][21] = mmdt_histFastJets06LhaLam100;
      mmdt_ArrayOfHist[2][22] = mmdt_histFastJets06WidthLam100;
      mmdt_ArrayOfHist[2][23] = mmdt_histFastJets06MassLam100;
      mmdt_ArrayOfHist[2][24] = mmdt_histFastJets06MultLam200;
      mmdt_ArrayOfHist[2][25] = mmdt_histFastJets06PtLam200;
      mmdt_ArrayOfHist[2][26] = mmdt_histFastJets06LhaLam200;
      mmdt_ArrayOfHist[2][27] = mmdt_histFastJets06WidthLam200;
      mmdt_ArrayOfHist[2][28] = mmdt_histFastJets06MassLam200;
      mmdt_ArrayOfHist[2][29] = mmdt_histFastJets06MultLam400;
      mmdt_ArrayOfHist[2][30] = mmdt_histFastJets06PtLam400;
      mmdt_ArrayOfHist[2][31] = mmdt_histFastJets06LhaLam400;
      mmdt_ArrayOfHist[2][32] = mmdt_histFastJets06WidthLam400;
      mmdt_ArrayOfHist[2][33] = mmdt_histFastJets06MassLam400;
      mmdt_ArrayOfHist[2][34] = mmdt_histFastJets06MultLam800;
      mmdt_ArrayOfHist[2][35] = mmdt_histFastJets06PtLam800;
      mmdt_ArrayOfHist[2][36] = mmdt_histFastJets06LhaLam800;
      mmdt_ArrayOfHist[2][37] = mmdt_histFastJets06WidthLam800;
      mmdt_ArrayOfHist[2][38] = mmdt_histFastJets06MassLam800;
      
      mmdt_ArrayOfHist[3][0]   = mmdt_histFastJets08PtSubLeading;
      mmdt_ArrayOfHist[3][1]   = mmdt_histFastJets08PtLeading;
      mmdt_ArrayOfHist[3][2]   = mmdt_histFastJets08PtReclust;
      mmdt_ArrayOfHist[3][3]   = mmdt_histFastJets08Pt;
      mmdt_ArrayOfHist[3][4]   = mmdt_histFastJets08Mult;
      mmdt_ArrayOfHist[3][5]   = mmdt_histFastJets08E;
      mmdt_ArrayOfHist[3][6]   = mmdt_histFastJets08Eta;
      mmdt_ArrayOfHist[3][7]   = mmdt_histFastJets08Rapidity;
      mmdt_ArrayOfHist[3][8]   = mmdt_histFastJets08Phi;
      mmdt_ArrayOfHist2[3][9]  = mmdt_histFastJets08MultLam;
      mmdt_ArrayOfHist2[3][10] = mmdt_histFastJets08PtLam;
      mmdt_ArrayOfHist2[3][11] = mmdt_histFastJets08LhaLam;
      mmdt_ArrayOfHist2[3][12] = mmdt_histFastJets08WidthLam;
      mmdt_ArrayOfHist2[3][13] = mmdt_histFastJets08MassLam;

      mmdt_ArrayOfHist[3][14] = mmdt_histFastJets08MultLam50;
      mmdt_ArrayOfHist[3][15] = mmdt_histFastJets08PtLam50;
      mmdt_ArrayOfHist[3][16] = mmdt_histFastJets08LhaLam50;
      mmdt_ArrayOfHist[3][17] = mmdt_histFastJets08WidthLam50;
      mmdt_ArrayOfHist[3][18] = mmdt_histFastJets08MassLam50;     
      mmdt_ArrayOfHist[3][19] = mmdt_histFastJets08MultLam100;
      mmdt_ArrayOfHist[3][20] = mmdt_histFastJets08PtLam100;
      mmdt_ArrayOfHist[3][21] = mmdt_histFastJets08LhaLam100;
      mmdt_ArrayOfHist[3][22] = mmdt_histFastJets08WidthLam100;
      mmdt_ArrayOfHist[3][23] = mmdt_histFastJets08MassLam100;
      mmdt_ArrayOfHist[3][24] = mmdt_histFastJets08MultLam200;
      mmdt_ArrayOfHist[3][25] = mmdt_histFastJets08PtLam200;
      mmdt_ArrayOfHist[3][26] = mmdt_histFastJets08LhaLam200;
      mmdt_ArrayOfHist[3][27] = mmdt_histFastJets08WidthLam200;
      mmdt_ArrayOfHist[3][28] = mmdt_histFastJets08MassLam200;
      mmdt_ArrayOfHist[3][29] = mmdt_histFastJets08MultLam400;
      mmdt_ArrayOfHist[3][30] = mmdt_histFastJets08PtLam400;
      mmdt_ArrayOfHist[3][31] = mmdt_histFastJets08LhaLam400;
      mmdt_ArrayOfHist[3][32] = mmdt_histFastJets08WidthLam400;
      mmdt_ArrayOfHist[3][33] = mmdt_histFastJets08MassLam400;
      mmdt_ArrayOfHist[3][34] = mmdt_histFastJets08MultLam800;
      mmdt_ArrayOfHist[3][35] = mmdt_histFastJets08PtLam800;
      mmdt_ArrayOfHist[3][36] = mmdt_histFastJets08LhaLam800;
      mmdt_ArrayOfHist[3][37] = mmdt_histFastJets08WidthLam800;
      mmdt_ArrayOfHist[3][38] = mmdt_histFastJets08MassLam800;
      
      mmdt_ArrayOfHist[4][0]   = mmdt_histFastJets10PtSubLeading;
      mmdt_ArrayOfHist[4][1]   = mmdt_histFastJets10PtLeading;
      mmdt_ArrayOfHist[4][2]   = mmdt_histFastJets10PtReclust;
      mmdt_ArrayOfHist[4][3]   = mmdt_histFastJets10Pt;
      mmdt_ArrayOfHist[4][4]   = mmdt_histFastJets10Mult;
      mmdt_ArrayOfHist[4][5]   = mmdt_histFastJets10E;
      mmdt_ArrayOfHist[4][6]   = mmdt_histFastJets10Eta;
      mmdt_ArrayOfHist[4][7]   = mmdt_histFastJets10Rapidity;
      mmdt_ArrayOfHist[4][8]   = mmdt_histFastJets10Phi;
      mmdt_ArrayOfHist2[4][9]  = mmdt_histFastJets10MultLam;
      mmdt_ArrayOfHist2[4][10] = mmdt_histFastJets10PtLam;
      mmdt_ArrayOfHist2[4][11] = mmdt_histFastJets10LhaLam;
      mmdt_ArrayOfHist2[4][12] = mmdt_histFastJets10WidthLam;
      mmdt_ArrayOfHist2[4][13] = mmdt_histFastJets10MassLam;

      mmdt_ArrayOfHist[4][14] = mmdt_histFastJets10MultLam50;
      mmdt_ArrayOfHist[4][15] = mmdt_histFastJets10PtLam50;
      mmdt_ArrayOfHist[4][16] = mmdt_histFastJets10LhaLam50;
      mmdt_ArrayOfHist[4][17] = mmdt_histFastJets10WidthLam50;
      mmdt_ArrayOfHist[4][18] = mmdt_histFastJets10MassLam50;     
      mmdt_ArrayOfHist[4][19] = mmdt_histFastJets10MultLam100;
      mmdt_ArrayOfHist[4][20] = mmdt_histFastJets10PtLam100;
      mmdt_ArrayOfHist[4][21] = mmdt_histFastJets10LhaLam100;
      mmdt_ArrayOfHist[4][22] = mmdt_histFastJets10WidthLam100;
      mmdt_ArrayOfHist[4][23] = mmdt_histFastJets10MassLam100;
      mmdt_ArrayOfHist[4][24] = mmdt_histFastJets10MultLam200;
      mmdt_ArrayOfHist[4][25] = mmdt_histFastJets10PtLam200;
      mmdt_ArrayOfHist[4][26] = mmdt_histFastJets10LhaLam200;
      mmdt_ArrayOfHist[4][27] = mmdt_histFastJets10WidthLam200;
      mmdt_ArrayOfHist[4][28] = mmdt_histFastJets10MassLam200;
      mmdt_ArrayOfHist[4][29] = mmdt_histFastJets10MultLam400;
      mmdt_ArrayOfHist[4][30] = mmdt_histFastJets10PtLam400;
      mmdt_ArrayOfHist[4][31] = mmdt_histFastJets10LhaLam400;
      mmdt_ArrayOfHist[4][32] = mmdt_histFastJets10WidthLam400;
      mmdt_ArrayOfHist[4][33] = mmdt_histFastJets10MassLam400;
      mmdt_ArrayOfHist[4][34] = mmdt_histFastJets10MultLam800;
      mmdt_ArrayOfHist[4][35] = mmdt_histFastJets10PtLam800;
      mmdt_ArrayOfHist[4][36] = mmdt_histFastJets10LhaLam800;
      mmdt_ArrayOfHist[4][37] = mmdt_histFastJets10WidthLam800;
      mmdt_ArrayOfHist[4][38] = mmdt_histFastJets10MassLam800;
  

    }

    //ofstream myfile;
    //ofstream //CheckEvent;
    //int Counter = 1;

void analyze(const Event& event) {
      //if (Counter == 1){
      //  //myfile.open ("other_pdgid.txt");
      //  //CheckEvent.open ("MC_DIJET_PB_CH_EventCheck.txt");
      //}
      //CheckEvent << "---------------EVENT NUMBER " << Counter << " ---------------" <<"\n";
      //CheckEvent << "Weight: " << event.weight() <<"\n";
      //Counter++;
      
      //double PtCut = 0.0;
      const int NumberOfRadiuses = 5;
      const double radius[NumberOfRadiuses] = {0.2,0.4,0.6,0.8,1.0};
      //string KTRadius[NumberOfRadiuses] = {"KT02","KT04","KT06","KT08","KT10"};
      //Jets jetAr[NumberOfRadiuses];
      const VetoedFinalState &fs = applyProjection<VetoedFinalState>(event,"JET_INPUT"); 
      vector<PseudoJet> particles;
      double Q = 0.0;
      int NumberOfGluons = 0;
      int NumberOfQuarks = 0;
      int NumberOfOthersThanGluonsAndQuars = 0;
      int NumberOfGluonAndQuark = 0;
      int NumberOfPartons = 0;
      particles.reserve(fs.particles().size());
      foreach (const Particle &p, fs.particles()){
        particles.push_back(p.pseudojet());
        Q += p.pT();//tady dodelat !!!
        if (p.pdgId() == 21) {
          NumberOfGluons++;
          _histGluonFractionPt->fill(p.pT(),event.weight());
        } else if (abs(p.pdgId()) < 7) {              
          NumberOfQuarks++;
          _histQuarkFractionPt->fill(p.pT(),event.weight());
        } else{
          NumberOfOthersThanGluonsAndQuars++;
          //if (p.pdgId() != 82){
          //  myfile << p.pdgId() <<"\n";
          //  }
          _histOthersThenGluonAndQuarkFractionPt->fill(p.pT(),event.weight());                      
        }
        if ((p.pdgId() == 21) || (abs(p.pdgId()) < 7)){
                NumberOfGluonAndQuark++;
                _histGluonAndQuarkFractionPt->fill(p.pT(), event.weight());          
        }
        NumberOfPartons++;
        _histPartonFractionPt->fill(p.pT(), event.weight());
        if (p.pdgId() == 9922212){
            _histPDGID->fill(30, event.weight());
        } else{
            _histPDGID->fill(p.pdgId(), event.weight());
        }
      }

      //if (NumberOfPartons != 0.0){
      //  _histGluonFractionPt->fill(Q,event.weight()*NumberOfGluons/NumberOfPartons);
      //}
      _histGluonMulti->fill(NumberOfGluons,event.weight());
      _histQuarkMulti->fill(NumberOfQuarks,event.weight());
      _histGluonAndQuarkMulti->fill(NumberOfGluonAndQuark,event.weight());
      _histOthersThenGluonAndQuarkMulti->fill(NumberOfOthersThanGluonsAndQuars,event.weight());
      _histPartonMulti->fill(NumberOfPartons,event.weight());

      double ptmin_jet = 2*JET_MIN_PT_FRACTION/(1+JET_MIN_PT_FRACTION)*JET_AVG_PTMINS[0]; // = cca 44 GeV, 
      //// for low pt double ptmin_jet = 0.0;


      for (size_t i = 0; i < NumberOfRadiuses; ++i) {
      JetDefinition jet_def(antikt_algorithm, radius[i]);
      vector<PseudoJet> jets = (SelectorNHardest(2) * SelectorAbsRapMax(JET_RAPMAX) * SelectorPtMin(ptmin_jet))(jet_def(particles));
      vector<PseudoJet> jets_no_pt_cut = (SelectorNHardest(2) * SelectorAbsRapMax(JET_RAPMAX) * SelectorPtMin(0.0))(jet_def(particles));
      if(jets_no_pt_cut.size()>=2){
        ArrayOfHist[i][0]->fill(jets_no_pt_cut[0].pt());
        ArrayOfHist[i][1]->fill(jets_no_pt_cut[1].pt());

      }

        if(jets.size()<2) continue;

        // impose the cuts
        PseudoJet orig_jet1 = jets[0];
        PseudoJet orig_jet2 = jets[1];

        // make sure we have something enough symmetric and close in rapidity
        if (orig_jet2.pt() / orig_jet1.pt() < JET_MIN_PT_FRACTION) continue; // comment for low pt
        if (std::abs(orig_jet1.rap()-orig_jet2.rap())>DELTA_RAP_MAX_DIJET) continue;

        // we need to pass the avgpt cut
        double avgpt = 0.5*(orig_jet1.pt() + orig_jet2.pt());
        unsigned int nQ=0;
        while ((nQ<nQs) && (avgpt>=JET_AVG_PTMINS[nQ])) nQ++;
        if (nQ == 0) continue;
        
        // grooming
        PseudoJet jet1 = ca_wta_recluster(orig_jet1);
        PseudoJet jet2 = ca_wta_recluster(orig_jet2);
        vector<PseudoJet> JetPair(2);
        JetPair[0]=jet1;
        JetPair[1]=jet2;

        PseudoJet mmdt_jet1 = (*mmdt)(jet1);
        PseudoJet mmdt_jet2 = (*mmdt)(jet2);
        vector<PseudoJet> mmdt_JetPair(2);
        mmdt_JetPair[0]=mmdt_jet1;
        mmdt_JetPair[1]=mmdt_jet2;

        double lambdaMult;
        double lambdaPt;
        double lambdaLha;
        double lambdaWidth;
        double lambdaMass;

        //
        for (int k=0; k<=1; k++) {
        ArrayOfHist[i][3]->fill(JetPair[k].pt()/GeV, event.weight());
        ArrayOfHist[i][8]->fill(JetPair[k].phi(), event.weight());
        ArrayOfHist[i][6]->fill(JetPair[k].eta() , event.weight());
        ArrayOfHist[i][5]->fill(JetPair[k].E()/GeV , event.weight());
        ArrayOfHist[i][7]->fill(JetPair[k].rap() , event.weight());
        lambdaMult = 0.0;
        lambdaPt = 0.0;
        lambdaLha = 0.0;
        lambdaWidth = 0.0;
        lambdaMass = 0.0;
        //CheckEvent << "JetNumber: " << k+1 << "\n" ;  
        for (const PseudoJet& p : JetPair[k].constituents()) 
					{ 
                  //CheckEvent << "Looping over constituents ***********" << "\n" ;  
                  //CheckEvent << "Pt: " << p.pt() << "\n" ;  
                  //CheckEvent << "JetPt: " << JetPair[k].pt() << "\n" ;  
                  //CheckEvent << "Radius: " << radius[i] << "\n" ;  
                  //CheckEvent << "Distance: " << sqrt(p.squared_distance(JetPair[k])) << "\n" ;  
                  lambdaLha=lambdaLha+(p.pt()/JetPair[k].pt())*pow(sqrt(p.squared_distance(JetPair[k]))/radius[i] ,0.5);
                  lambdaMult=lambdaMult+1.0; //ok 
                  lambdaPt=lambdaPt+(p.pt()/JetPair[k].pt())*(p.pt()/JetPair[k].pt()); // ok
                  lambdaWidth=lambdaWidth+(p.pt()/JetPair[k].pt())*(sqrt(p.squared_distance(JetPair[k]))/radius[i]);
                  lambdaMass=lambdaMass+(p.pt()/JetPair[k].pt())*pow(sqrt(p.squared_distance(JetPair[k]))/radius[i],2.0);
              

					}

          
            ArrayOfHist2[i][9]->fill(lambdaMult  , avgpt, event.weight());
            ArrayOfHist2[i][10]->fill(lambdaPt   , avgpt, event.weight());
            ArrayOfHist2[i][11]->fill(lambdaLha  , avgpt, event.weight());
            ArrayOfHist2[i][12]->fill(lambdaWidth, avgpt, event.weight());
            ArrayOfHist2[i][13]->fill(lambdaMass , avgpt, event.weight()); // average is good for now, maybee highest

            if (nQ == 1){
              //ArrayOfHist2[i][9]->fill(lambdaMult  , avgpt, event.weight());
              //ArrayOfHist2[i][10]->fill(lambdaPt   , avgpt, event.weight());
              //ArrayOfHist2[i][11]->fill(lambdaLha  , avgpt, event.weight());
              //ArrayOfHist2[i][12]->fill(lambdaWidth, avgpt, event.weight());
              //ArrayOfHist2[i][13]->fill(lambdaMass , avgpt, event.weight()); 
              //CheckEvent << "lambdaMult: " << lambdaMult << "\n" ;
              //CheckEvent << "lambdaLha: " << lambdaLha << "\n" ;
              //CheckEvent << "lambdaWidth: " << lambdaWidth << "\n" ;
              //CheckEvent << "lambdaMass: " << lambdaMass << "\n" ;
              //CheckEvent << "lambdaPt: " << lambdaPt << "\n" ;
              ArrayOfHist[i][14]->fill(lambdaMult,event.weight());
              ArrayOfHist[i][15]->fill(lambdaPt,event.weight());
              ArrayOfHist[i][16]->fill(lambdaLha,event.weight());
              ArrayOfHist[i][17]->fill(lambdaWidth,event.weight());
              ArrayOfHist[i][18]->fill(lambdaMass,event.weight());
            } else if (nQ == 2){

              //CheckEvent << "lambdaMult: " << lambdaMult << "\n" ;
              //CheckEvent << "lambdaMult: " << lambdaMult << "\n" ;
              //CheckEvent << "lambdaLha: " << lambdaLha << "\n" ;
              //CheckEvent << "lambdaLha: " << lambdaLha << "\n" ;
              //CheckEvent << "lambdaWidth: " << lambdaWidth << "\n" ;
              //CheckEvent << "lambdaWidth: " << lambdaWidth << "\n" ;
              //CheckEvent << "lambdaMass: " << lambdaMass << "\n" ;
              //CheckEvent << "lambdaMass: " << lambdaMass << "\n" ;
              //CheckEvent << "lambdaPt: " << lambdaPt << "\n" ;
              //CheckEvent << "lambdaPt: " << lambdaPt << "\n" ;

              ArrayOfHist[i][14]->fill(lambdaMult,event.weight());
              ArrayOfHist[i][15]->fill(lambdaPt,event.weight());
              ArrayOfHist[i][16]->fill(lambdaLha,event.weight());
              ArrayOfHist[i][17]->fill(lambdaWidth,event.weight());
              ArrayOfHist[i][18]->fill(lambdaMass,event.weight());

              ArrayOfHist[i][19]->fill(lambdaMult,event.weight());
              ArrayOfHist[i][20]->fill(lambdaPt,event.weight());
              ArrayOfHist[i][21]->fill(lambdaLha,event.weight());
              ArrayOfHist[i][22]->fill(lambdaWidth,event.weight());
              ArrayOfHist[i][23]->fill(lambdaMass,event.weight());
            } else if (nQ == 3){

              //CheckEvent << "lambdaMult: " << lambdaMult << "\n" ;
              //CheckEvent << "lambdaMult: " << lambdaMult << "\n" ;
              //CheckEvent << "lambdaMult: " << lambdaMult << "\n" ;
              //CheckEvent << "lambdaLha: " << lambdaLha << "\n" ;
              //CheckEvent << "lambdaLha: " << lambdaLha << "\n" ;
              //CheckEvent << "lambdaLha: " << lambdaLha << "\n" ;
              //CheckEvent << "lambdaWidth: " << lambdaWidth << "\n" ;
              //CheckEvent << "lambdaWidth: " << lambdaWidth << "\n" ;
              //CheckEvent << "lambdaWidth: " << lambdaWidth << "\n" ;
              //CheckEvent << "lambdaMass: " << lambdaMass << "\n" ;
              //CheckEvent << "lambdaMass: " << lambdaMass << "\n" ;
              //CheckEvent << "lambdaMass: " << lambdaMass << "\n" ;
              //CheckEvent << "lambdaPt: " << lambdaPt << "\n" ;
              //CheckEvent << "lambdaPt: " << lambdaPt << "\n" ;
              //CheckEvent << "lambdaPt: " << lambdaPt << "\n" ;
              ArrayOfHist[i][14]->fill(lambdaMult,event.weight());
              ArrayOfHist[i][15]->fill(lambdaPt,event.weight());
              ArrayOfHist[i][16]->fill(lambdaLha,event.weight());
              ArrayOfHist[i][17]->fill(lambdaWidth,event.weight());
              ArrayOfHist[i][18]->fill(lambdaMass,event.weight());

              ArrayOfHist[i][19]->fill(lambdaMult,event.weight());
              ArrayOfHist[i][20]->fill(lambdaPt,event.weight());
              ArrayOfHist[i][21]->fill(lambdaLha,event.weight());
              ArrayOfHist[i][22]->fill(lambdaWidth,event.weight());
              ArrayOfHist[i][23]->fill(lambdaMass,event.weight());

              ArrayOfHist[i][24]->fill(lambdaMult,event.weight());
              ArrayOfHist[i][25]->fill(lambdaPt,event.weight());
              ArrayOfHist[i][26]->fill(lambdaLha,event.weight());
              ArrayOfHist[i][27]->fill(lambdaWidth,event.weight());
              ArrayOfHist[i][28]->fill(lambdaMass,event.weight());
            } else if (nQ == 4){

              //CheckEvent << "lambdaMult: " << lambdaMult << "\n" ;
              //CheckEvent << "lambdaMult: " << lambdaMult << "\n" ;
              //CheckEvent << "lambdaMult: " << lambdaMult << "\n" ;
              //CheckEvent << "lambdaMult: " << lambdaMult << "\n" ;
              //CheckEvent << "lambdaLha: " << lambdaLha << "\n" ;
              //CheckEvent << "lambdaLha: " << lambdaLha << "\n" ;
              //CheckEvent << "lambdaLha: " << lambdaLha << "\n" ;
              //CheckEvent << "lambdaLha: " << lambdaLha << "\n" ;
              //CheckEvent << "lambdaWidth: " << lambdaWidth << "\n" ;
              //CheckEvent << "lambdaWidth: " << lambdaWidth << "\n" ;
              //CheckEvent << "lambdaWidth: " << lambdaWidth << "\n" ;
              //CheckEvent << "lambdaWidth: " << lambdaWidth << "\n" ;
              //CheckEvent << "lambdaMass: " << lambdaMass << "\n" ;
              //CheckEvent << "lambdaMass: " << lambdaMass << "\n" ;
              //CheckEvent << "lambdaMass: " << lambdaMass << "\n" ;
              //CheckEvent << "lambdaMass: " << lambdaMass << "\n" ;
              //CheckEvent << "lambdaPt: " << lambdaPt << "\n" ;
              //CheckEvent << "lambdaPt: " << lambdaPt << "\n" ;
              //CheckEvent << "lambdaPt: " << lambdaPt << "\n" ;
              //CheckEvent << "lambdaPt: " << lambdaPt << "\n" ;

              ArrayOfHist[i][14]->fill(lambdaMult,event.weight());
              ArrayOfHist[i][15]->fill(lambdaPt,event.weight());
              ArrayOfHist[i][16]->fill(lambdaLha,event.weight());
              ArrayOfHist[i][17]->fill(lambdaWidth,event.weight());
              ArrayOfHist[i][18]->fill(lambdaMass,event.weight());

              ArrayOfHist[i][19]->fill(lambdaMult,event.weight());
              ArrayOfHist[i][20]->fill(lambdaPt,event.weight());
              ArrayOfHist[i][21]->fill(lambdaLha,event.weight());
              ArrayOfHist[i][22]->fill(lambdaWidth,event.weight());
              ArrayOfHist[i][23]->fill(lambdaMass,event.weight());

              ArrayOfHist[i][24]->fill(lambdaMult,event.weight());
              ArrayOfHist[i][25]->fill(lambdaPt,event.weight());
              ArrayOfHist[i][26]->fill(lambdaLha,event.weight());
              ArrayOfHist[i][27]->fill(lambdaWidth,event.weight());
              ArrayOfHist[i][28]->fill(lambdaMass,event.weight());

              ArrayOfHist[i][29]->fill(lambdaMult,event.weight());
              ArrayOfHist[i][30]->fill(lambdaPt,event.weight());
              ArrayOfHist[i][31]->fill(lambdaLha,event.weight());
              ArrayOfHist[i][32]->fill(lambdaWidth,event.weight());
              ArrayOfHist[i][33]->fill(lambdaMass,event.weight());
            } else if (nQ == 5){

              //CheckEvent << "lambdaMult: " << lambdaMult << "\n" ;
              //CheckEvent << "lambdaMult: " << lambdaMult << "\n" ;
              //CheckEvent << "lambdaMult: " << lambdaMult << "\n" ;
              //CheckEvent << "lambdaMult: " << lambdaMult << "\n" ;
              //CheckEvent << "lambdaMult: " << lambdaMult << "\n" ;
              //CheckEvent << "lambdaLha: " << lambdaLha << "\n" ;
              //CheckEvent << "lambdaLha: " << lambdaLha << "\n" ;
              //CheckEvent << "lambdaLha: " << lambdaLha << "\n" ;
              //CheckEvent << "lambdaLha: " << lambdaLha << "\n" ;
              //CheckEvent << "lambdaLha: " << lambdaLha << "\n" ;
              //CheckEvent << "lambdaWidth: " << lambdaWidth << "\n" ;
              //CheckEvent << "lambdaWidth: " << lambdaWidth << "\n" ;
              //CheckEvent << "lambdaWidth: " << lambdaWidth << "\n" ;
              //CheckEvent << "lambdaWidth: " << lambdaWidth << "\n" ;
              //CheckEvent << "lambdaWidth: " << lambdaWidth << "\n" ;
              //CheckEvent << "lambdaMass: " << lambdaMass << "\n" ;
              //CheckEvent << "lambdaMass: " << lambdaMass << "\n" ;
              //CheckEvent << "lambdaMass: " << lambdaMass << "\n" ;
              //CheckEvent << "lambdaMass: " << lambdaMass << "\n" ;
              //CheckEvent << "lambdaMass: " << lambdaMass << "\n" ;
              //CheckEvent << "lambdaPt: " << lambdaPt << "\n" ;
              //CheckEvent << "lambdaPt: " << lambdaPt << "\n" ;
              //CheckEvent << "lambdaPt: " << lambdaPt << "\n" ;
              //CheckEvent << "lambdaPt: " << lambdaPt << "\n" ;
              //CheckEvent << "lambdaPt: " << lambdaPt << "\n" ;

              ArrayOfHist[i][14]->fill(lambdaMult,event.weight());
              ArrayOfHist[i][15]->fill(lambdaPt,event.weight());
              ArrayOfHist[i][16]->fill(lambdaLha,event.weight());
              ArrayOfHist[i][17]->fill(lambdaWidth,event.weight());
              ArrayOfHist[i][18]->fill(lambdaMass,event.weight());

              ArrayOfHist[i][19]->fill(lambdaMult,event.weight());
              ArrayOfHist[i][20]->fill(lambdaPt,event.weight());
              ArrayOfHist[i][21]->fill(lambdaLha,event.weight());
              ArrayOfHist[i][22]->fill(lambdaWidth,event.weight());
              ArrayOfHist[i][23]->fill(lambdaMass,event.weight());

              ArrayOfHist[i][24]->fill(lambdaMult,event.weight());
              ArrayOfHist[i][25]->fill(lambdaPt,event.weight());
              ArrayOfHist[i][26]->fill(lambdaLha,event.weight());
              ArrayOfHist[i][27]->fill(lambdaWidth,event.weight());
              ArrayOfHist[i][28]->fill(lambdaMass,event.weight());

              ArrayOfHist[i][29]->fill(lambdaMult,event.weight());
              ArrayOfHist[i][30]->fill(lambdaPt,event.weight());
              ArrayOfHist[i][31]->fill(lambdaLha,event.weight());
              ArrayOfHist[i][32]->fill(lambdaWidth,event.weight());
              ArrayOfHist[i][33]->fill(lambdaMass,event.weight());          

              ArrayOfHist[i][34]->fill(lambdaMult,event.weight());
              ArrayOfHist[i][35]->fill(lambdaPt,event.weight());
              ArrayOfHist[i][36]->fill(lambdaLha,event.weight());
              ArrayOfHist[i][37]->fill(lambdaWidth,event.weight());
              ArrayOfHist[i][38]->fill(lambdaMass,event.weight());
            }
         
          }
        // 
        //looping over groomed jets
        
        for (int k=0; k<=1; k++) {
        mmdt_ArrayOfHist[i][3]->fill(mmdt_JetPair[k].pt()/GeV, event.weight());
        mmdt_ArrayOfHist[i][8]->fill(mmdt_JetPair[k].phi(), event.weight());
        mmdt_ArrayOfHist[i][6]->fill(mmdt_JetPair[k].eta() , event.weight());
        mmdt_ArrayOfHist[i][5]->fill(mmdt_JetPair[k].E()/GeV , event.weight());
        mmdt_ArrayOfHist[i][7]->fill(mmdt_JetPair[k].rap() , event.weight());
        lambdaMult = 0.0;
        lambdaPt = 0.0;
        lambdaLha = 0.0;
        lambdaWidth = 0.0;
        lambdaMass = 0.0;
        for (const PseudoJet& p : mmdt_JetPair[k].constituents()) 
					{ 
                  lambdaLha=lambdaLha+(p.pt()/mmdt_JetPair[k].pt())*pow(sqrt(p.squared_distance(mmdt_JetPair[k]))/radius[i] ,0.5);
                  lambdaMult=lambdaMult+1.0; //ok 
                  lambdaPt=lambdaPt+(p.pt()/mmdt_JetPair[k].pt())*(p.pt()/mmdt_JetPair[k].pt()); // ok
                  lambdaWidth=lambdaWidth+(p.pt()/mmdt_JetPair[k].pt())*(sqrt(p.squared_distance(mmdt_JetPair[k]))/radius[i]);
                  lambdaMass=lambdaMass+(p.pt()/mmdt_JetPair[k].pt())*pow(sqrt(p.squared_distance(mmdt_JetPair[k]))/radius[i],2.0);
              

					}

          
            mmdt_ArrayOfHist2[i][9]->fill(lambdaMult  , 0.5*(mmdt_JetPair[0].pt() + mmdt_JetPair[1].pt()), event.weight());
            mmdt_ArrayOfHist2[i][10]->fill(lambdaPt   , 0.5*(mmdt_JetPair[0].pt() + mmdt_JetPair[1].pt()), event.weight());
            mmdt_ArrayOfHist2[i][11]->fill(lambdaLha  , 0.5*(mmdt_JetPair[0].pt() + mmdt_JetPair[1].pt()), event.weight());
            mmdt_ArrayOfHist2[i][12]->fill(lambdaWidth, 0.5*(mmdt_JetPair[0].pt() + mmdt_JetPair[1].pt()), event.weight());
            mmdt_ArrayOfHist2[i][13]->fill(lambdaMass , 0.5*(mmdt_JetPair[0].pt() + mmdt_JetPair[1].pt()), event.weight()); // average is good for now, maybee highest

            if (nQ == 1){
              mmdt_ArrayOfHist[i][14]->fill(lambdaMult,event.weight());
              mmdt_ArrayOfHist[i][15]->fill(lambdaPt,event.weight());
              mmdt_ArrayOfHist[i][16]->fill(lambdaLha,event.weight());
              mmdt_ArrayOfHist[i][17]->fill(lambdaWidth,event.weight());
              mmdt_ArrayOfHist[i][18]->fill(lambdaMass,event.weight());
            } else if (nQ == 2){

              mmdt_ArrayOfHist[i][14]->fill(lambdaMult,event.weight());
              mmdt_ArrayOfHist[i][15]->fill(lambdaPt,event.weight());
              mmdt_ArrayOfHist[i][16]->fill(lambdaLha,event.weight());
              mmdt_ArrayOfHist[i][17]->fill(lambdaWidth,event.weight());
              mmdt_ArrayOfHist[i][18]->fill(lambdaMass,event.weight());

              mmdt_ArrayOfHist[i][19]->fill(lambdaMult,event.weight());
              mmdt_ArrayOfHist[i][20]->fill(lambdaPt,event.weight());
              mmdt_ArrayOfHist[i][21]->fill(lambdaLha,event.weight());
              mmdt_ArrayOfHist[i][22]->fill(lambdaWidth,event.weight());
              mmdt_ArrayOfHist[i][23]->fill(lambdaMass,event.weight());
            } else if (nQ == 3){

              mmdt_ArrayOfHist[i][14]->fill(lambdaMult,event.weight());
              mmdt_ArrayOfHist[i][15]->fill(lambdaPt,event.weight());
              mmdt_ArrayOfHist[i][16]->fill(lambdaLha,event.weight());
              mmdt_ArrayOfHist[i][17]->fill(lambdaWidth,event.weight());
              mmdt_ArrayOfHist[i][18]->fill(lambdaMass,event.weight());

              mmdt_ArrayOfHist[i][19]->fill(lambdaMult,event.weight());
              mmdt_ArrayOfHist[i][20]->fill(lambdaPt,event.weight());
              mmdt_ArrayOfHist[i][21]->fill(lambdaLha,event.weight());
              mmdt_ArrayOfHist[i][22]->fill(lambdaWidth,event.weight());
              mmdt_ArrayOfHist[i][23]->fill(lambdaMass,event.weight());

              mmdt_ArrayOfHist[i][24]->fill(lambdaMult,event.weight());
              mmdt_ArrayOfHist[i][25]->fill(lambdaPt,event.weight());
              mmdt_ArrayOfHist[i][26]->fill(lambdaLha,event.weight());
              mmdt_ArrayOfHist[i][27]->fill(lambdaWidth,event.weight());
              mmdt_ArrayOfHist[i][28]->fill(lambdaMass,event.weight());
            } else if (nQ == 4){

              mmdt_ArrayOfHist[i][14]->fill(lambdaMult,event.weight());
              mmdt_ArrayOfHist[i][15]->fill(lambdaPt,event.weight());
              mmdt_ArrayOfHist[i][16]->fill(lambdaLha,event.weight());
              mmdt_ArrayOfHist[i][17]->fill(lambdaWidth,event.weight());
              mmdt_ArrayOfHist[i][18]->fill(lambdaMass,event.weight());

              mmdt_ArrayOfHist[i][19]->fill(lambdaMult,event.weight());
              mmdt_ArrayOfHist[i][20]->fill(lambdaPt,event.weight());
              mmdt_ArrayOfHist[i][21]->fill(lambdaLha,event.weight());
              mmdt_ArrayOfHist[i][22]->fill(lambdaWidth,event.weight());
              mmdt_ArrayOfHist[i][23]->fill(lambdaMass,event.weight());

              mmdt_ArrayOfHist[i][24]->fill(lambdaMult,event.weight());
              mmdt_ArrayOfHist[i][25]->fill(lambdaPt,event.weight());
              mmdt_ArrayOfHist[i][26]->fill(lambdaLha,event.weight());
              mmdt_ArrayOfHist[i][27]->fill(lambdaWidth,event.weight());
              mmdt_ArrayOfHist[i][28]->fill(lambdaMass,event.weight());

              mmdt_ArrayOfHist[i][29]->fill(lambdaMult,event.weight());
              mmdt_ArrayOfHist[i][30]->fill(lambdaPt,event.weight());
              mmdt_ArrayOfHist[i][31]->fill(lambdaLha,event.weight());
              mmdt_ArrayOfHist[i][32]->fill(lambdaWidth,event.weight());
              mmdt_ArrayOfHist[i][33]->fill(lambdaMass,event.weight());
            } else if (nQ == 5){

              mmdt_ArrayOfHist[i][14]->fill(lambdaMult,event.weight());
              mmdt_ArrayOfHist[i][15]->fill(lambdaPt,event.weight());
              mmdt_ArrayOfHist[i][16]->fill(lambdaLha,event.weight());
              mmdt_ArrayOfHist[i][17]->fill(lambdaWidth,event.weight());
              mmdt_ArrayOfHist[i][18]->fill(lambdaMass,event.weight());

              mmdt_ArrayOfHist[i][19]->fill(lambdaMult,event.weight());
              mmdt_ArrayOfHist[i][20]->fill(lambdaPt,event.weight());
              mmdt_ArrayOfHist[i][21]->fill(lambdaLha,event.weight());
              mmdt_ArrayOfHist[i][22]->fill(lambdaWidth,event.weight());
              mmdt_ArrayOfHist[i][23]->fill(lambdaMass,event.weight());

              mmdt_ArrayOfHist[i][24]->fill(lambdaMult,event.weight());
              mmdt_ArrayOfHist[i][25]->fill(lambdaPt,event.weight());
              mmdt_ArrayOfHist[i][26]->fill(lambdaLha,event.weight());
              mmdt_ArrayOfHist[i][27]->fill(lambdaWidth,event.weight());
              mmdt_ArrayOfHist[i][28]->fill(lambdaMass,event.weight());

              mmdt_ArrayOfHist[i][29]->fill(lambdaMult,event.weight());
              mmdt_ArrayOfHist[i][30]->fill(lambdaPt,event.weight());
              mmdt_ArrayOfHist[i][31]->fill(lambdaLha,event.weight());
              mmdt_ArrayOfHist[i][32]->fill(lambdaWidth,event.weight());
              mmdt_ArrayOfHist[i][33]->fill(lambdaMass,event.weight());          

              mmdt_ArrayOfHist[i][34]->fill(lambdaMult,event.weight());
              mmdt_ArrayOfHist[i][35]->fill(lambdaPt,event.weight());
              mmdt_ArrayOfHist[i][36]->fill(lambdaLha,event.weight());
              mmdt_ArrayOfHist[i][37]->fill(lambdaWidth,event.weight());
              mmdt_ArrayOfHist[i][38]->fill(lambdaMass,event.weight());
            }
         
          }//end of looping over groomed jets
      

      }

      /*
      
      for (size_t i = 0; i < NumberOfRadiuses; ++i) {
      jetAr[i] = apply<FastJets>(event,KTRadius[i]).jetsByPt(PtCut*GeV);
      }
      
        double lambdaMult;
        double lambdaPt;
        double lambdaLha;
        double lambdaWidth;
        double lambdaMass;

        bool Cycle = false;
        size_t k;
        Jet LeadingJet;
        Jet SubLeadingJet;

      for (size_t i = 0; i < NumberOfRadiuses; ++i) {
        // help cycle yo find leadinh and subleading jet


        k = 0;
        foreach (const Jet& jet_test, jetAr[i]) {
        if (k==0){
                LeadingJet = jet_test;
                }
        if (k==1){
                SubLeadingJet = jet_test;
                }
        k++;
        }
                
        if ((SubLeadingJet.pT()/LeadingJet.pT())<0.8){
          continue;
        }

        ArrayOfHist[i][4]->fill(jetAr[i].size(), event.weight());

        foreach (const Jet& jet, jetAr[i]) {
        ArrayOfHist[i][3]->fill(jet.pT()/GeV, event.weight());
        ArrayOfHist[i][8]->fill(jet.phi(), event.weight());
        ArrayOfHist[i][6]->fill(jet.eta() , event.weight());
        ArrayOfHist[i][5]->fill(jet.E()/GeV , event.weight());
        ArrayOfHist[i][7]->fill(jet.rap() , event.weight());
        lambdaMult = 0.0;
        lambdaPt = 0.0;
        lambdaLha = 0.0;
        lambdaWidth = 0.0;
        lambdaMass = 0.0;
            for (const Particle& p : jet.particles()) 
					{ 
                  Cycle = true;
                  lambdaLha=lambdaLha+(p.p()/jet.p())*pow(jet.angle(p.p3())/radius[i] ,0.5);
                  lambdaMult=lambdaMult+1.0;
                  //lambdaPt=lambdaPt+pow((p.p()/jet.p()),2.0);
                  //ArrayOfHist[i][10]->fill(p.p()/jet.p(),event.weight());
                  lambdaPt=lambdaPt+(p.p()/jet.p())*(p.p()/jet.p());
                  lambdaWidth=lambdaWidth+(p.p()/jet.p())*(jet.angle(p.p3())/radius[i]);
                  lambdaMass=lambdaMass+(p.p()/jet.p())*pow(jet.angle(p.p3())/radius[i],2.0);
              
					}
          if (Cycle == true){
            ArrayOfHist[i][9]->fill(lambdaMult,event.weight());
            ArrayOfHist[i][10]->fill(lambdaPt,event.weight());
            ArrayOfHist[i][11]->fill(lambdaLha,event.weight());
            ArrayOfHist[i][12]->fill(lambdaWidth,event.weight());
            ArrayOfHist[i][13]->fill(lambdaMass,event.weight());
            }
         
          }
          }

          */
     }



    void finalize() {
      //divide(_histGluonFractionPt , _histPartonFractionPt); ask !!!
      //divide(_histQuarkFractionPt , _histPartonFractionPt);
      //divide(_histGluonAndQuarkFractionPt , _histPartonFractionPt);
      //divide(_histOthersThenGluonAndQuarkFractionPt , _histPartonFractionPt);
      //divide(_histPartonFractionPt , _histPartonFractionPt);
      //for (int i = 1; i <= _histGluonFractionPt->NumBins(); i++){
      //    _histGluonFractionPt->bin(i)->height()
      //}
      normalize(_histPDGID);
      normalize(_histCONTROL_PT_RAP);
      normalize({_histGluonMulti, _histQuarkMulti, _histGluonAndQuarkMulti, _histOthersThenGluonAndQuarkMulti, _histPartonMulti});
      /* PB no normalized
      normalize({_histFastJets02PtReclust,_histFastJets02PtSubLeading,_histFastJets02PtLeading,_histFastJets02Pt, _histFastJets02Mult, _histFastJets02E, _histFastJets02Eta, _histFastJets02Rapidity, _histFastJets02Phi});
      normalize({_histFastJets04PtReclust,_histFastJets04PtSubLeading,_histFastJets04PtLeading,_histFastJets04Pt, _histFastJets04Mult, _histFastJets04E, _histFastJets04Eta, _histFastJets04Rapidity, _histFastJets04Phi});
      normalize({_histFastJets06PtReclust,_histFastJets06PtSubLeading,_histFastJets06PtLeading,_histFastJets06Pt, _histFastJets06Mult, _histFastJets06E, _histFastJets06Eta, _histFastJets06Rapidity, _histFastJets06Phi});
      normalize({_histFastJets08PtReclust,_histFastJets08PtSubLeading,_histFastJets08PtLeading,_histFastJets08Pt, _histFastJets08Mult, _histFastJets08E, _histFastJets08Eta, _histFastJets08Rapidity, _histFastJets08Phi});
      normalize({_histFastJets10PtReclust,_histFastJets10PtSubLeading,_histFastJets10PtLeading,_histFastJets10Pt, _histFastJets10Mult, _histFastJets10E, _histFastJets10Eta, _histFastJets10Rapidity, _histFastJets10Phi});

      //normalize({_histFastJets02MultLam,_histFastJets02PtLam,_histFastJets02LhaLam,_histFastJets02WidthLam,_histFastJets02MassLam});
      //normalize({_histFastJets04MultLam,_histFastJets04PtLam,_histFastJets04LhaLam,_histFastJets04WidthLam,_histFastJets04MassLam});
      //normalize({_histFastJets06MultLam,_histFastJets06PtLam,_histFastJets06LhaLam,_histFastJets06WidthLam,_histFastJets06MassLam});
      //normalize({_histFastJets08MultLam,_histFastJets08PtLam,_histFastJets08LhaLam,_histFastJets08WidthLam,_histFastJets08MassLam});
      //normalize({_histFastJets10MultLam,_histFastJets10PtLam,_histFastJets10LhaLam,_histFastJets10WidthLam,_histFastJets10MassLam});

      normalize({_histFastJets02MultLam50, _histFastJets02PtLam50,_histFastJets02LhaLam50,_histFastJets02WidthLam50,_histFastJets02MassLam50});
      normalize({_histFastJets04MultLam50, _histFastJets04PtLam50,_histFastJets04LhaLam50,_histFastJets04WidthLam50,_histFastJets04MassLam50});
      normalize({_histFastJets06MultLam50, _histFastJets06PtLam50,_histFastJets06LhaLam50,_histFastJets06WidthLam50,_histFastJets06MassLam50});
      normalize({_histFastJets08MultLam50, _histFastJets08PtLam50,_histFastJets08LhaLam50,_histFastJets08WidthLam50,_histFastJets08MassLam50});
      normalize({_histFastJets10MultLam50, _histFastJets10PtLam50,_histFastJets10LhaLam50,_histFastJets10WidthLam50,_histFastJets10MassLam50});
      normalize({_histFastJets02MultLam100, _histFastJets02PtLam100,_histFastJets02LhaLam100,_histFastJets02WidthLam100,_histFastJets02MassLam100});
      normalize({_histFastJets04MultLam100, _histFastJets04PtLam100,_histFastJets04LhaLam100,_histFastJets04WidthLam100,_histFastJets04MassLam100});
      normalize({_histFastJets06MultLam100, _histFastJets06PtLam100,_histFastJets06LhaLam100,_histFastJets06WidthLam100,_histFastJets06MassLam100});
      normalize({_histFastJets08MultLam100, _histFastJets08PtLam100,_histFastJets08LhaLam100,_histFastJets08WidthLam100,_histFastJets08MassLam100});
      normalize({_histFastJets10MultLam100, _histFastJets10PtLam100,_histFastJets10LhaLam100,_histFastJets10WidthLam100,_histFastJets10MassLam100});
      normalize({_histFastJets02MultLam200, _histFastJets02PtLam200,_histFastJets02LhaLam200,_histFastJets02WidthLam200,_histFastJets02MassLam200});
      normalize({_histFastJets04MultLam200, _histFastJets04PtLam200,_histFastJets04LhaLam200,_histFastJets04WidthLam200,_histFastJets04MassLam200});
      normalize({_histFastJets06MultLam200, _histFastJets06PtLam200,_histFastJets06LhaLam200,_histFastJets06WidthLam200,_histFastJets06MassLam200});
      normalize({_histFastJets08MultLam200, _histFastJets08PtLam200,_histFastJets08LhaLam200,_histFastJets08WidthLam200,_histFastJets08MassLam200});
      normalize({_histFastJets10MultLam200, _histFastJets10PtLam200,_histFastJets10LhaLam200,_histFastJets10WidthLam200,_histFastJets10MassLam200});
      normalize({_histFastJets02MultLam400, _histFastJets02PtLam400,_histFastJets02LhaLam400,_histFastJets02WidthLam400,_histFastJets02MassLam400});
      normalize({_histFastJets04MultLam400, _histFastJets04PtLam400,_histFastJets04LhaLam400,_histFastJets04WidthLam400,_histFastJets04MassLam400});
      normalize({_histFastJets06MultLam400, _histFastJets06PtLam400,_histFastJets06LhaLam400,_histFastJets06WidthLam400,_histFastJets06MassLam400});
      normalize({_histFastJets08MultLam400, _histFastJets08PtLam400,_histFastJets08LhaLam400,_histFastJets08WidthLam400,_histFastJets08MassLam400});
      normalize({_histFastJets10MultLam400, _histFastJets10PtLam400,_histFastJets10LhaLam400,_histFastJets10WidthLam400,_histFastJets10MassLam400});
      normalize({_histFastJets02MultLam800, _histFastJets02PtLam800,_histFastJets02LhaLam800,_histFastJets02WidthLam800,_histFastJets02MassLam800});
      normalize({_histFastJets04MultLam800, _histFastJets04PtLam800,_histFastJets04LhaLam800,_histFastJets04WidthLam800,_histFastJets04MassLam800});
      normalize({_histFastJets06MultLam800, _histFastJets06PtLam800,_histFastJets06LhaLam800,_histFastJets06WidthLam800,_histFastJets06MassLam800});
      normalize({_histFastJets08MultLam800, _histFastJets08PtLam800,_histFastJets08LhaLam800,_histFastJets08WidthLam800,_histFastJets08MassLam800});
      normalize({_histFastJets10MultLam800, _histFastJets10PtLam800,_histFastJets10LhaLam800,_histFastJets10WidthLam800,_histFastJets10MassLam800});
      */
    }


  private:
    Recluster ca_wta_recluster;
    SharedPtr<contrib::ModifiedMassDropTagger> mmdt;
    Histo1DPtr _histPDGID;
    Histo2DPtr _histCONTROL_PT_RAP;
    Histo1DPtr _histGluonFractionPt, _histQuarkFractionPt, _histGluonAndQuarkFractionPt, _histOthersThenGluonAndQuarkFractionPt, _histPartonFractionPt;
    Histo1DPtr _histGluonMulti, _histQuarkMulti, _histGluonAndQuarkMulti, _histOthersThenGluonAndQuarkMulti, _histPartonMulti;
    Histo1DPtr _histFastJets02PtReclust,_histFastJets02PtSubLeading,_histFastJets02PtLeading,_histFastJets02Pt, _histFastJets02Mult, _histFastJets02E, _histFastJets02Eta, _histFastJets02Rapidity, _histFastJets02Phi;
    Histo1DPtr _histFastJets04PtReclust,_histFastJets04PtSubLeading,_histFastJets04PtLeading,_histFastJets04Pt, _histFastJets04Mult, _histFastJets04E, _histFastJets04Eta, _histFastJets04Rapidity, _histFastJets04Phi;
    Histo1DPtr _histFastJets06PtReclust,_histFastJets06PtSubLeading,_histFastJets06PtLeading,_histFastJets06Pt, _histFastJets06Mult, _histFastJets06E, _histFastJets06Eta, _histFastJets06Rapidity, _histFastJets06Phi;
    Histo1DPtr _histFastJets08PtReclust,_histFastJets08PtSubLeading,_histFastJets08PtLeading,_histFastJets08Pt, _histFastJets08Mult, _histFastJets08E, _histFastJets08Eta, _histFastJets08Rapidity, _histFastJets08Phi;
    Histo1DPtr _histFastJets10PtReclust,_histFastJets10PtSubLeading,_histFastJets10PtLeading,_histFastJets10Pt, _histFastJets10Mult, _histFastJets10E, _histFastJets10Eta, _histFastJets10Rapidity, _histFastJets10Phi;

    Histo2DPtr _histFastJets02MultLam, _histFastJets02PtLam,_histFastJets02LhaLam,_histFastJets02WidthLam,_histFastJets02MassLam;
    Histo2DPtr _histFastJets04MultLam, _histFastJets04PtLam,_histFastJets04LhaLam,_histFastJets04WidthLam,_histFastJets04MassLam;
    Histo2DPtr _histFastJets06MultLam, _histFastJets06PtLam,_histFastJets06LhaLam,_histFastJets06WidthLam,_histFastJets06MassLam;
    Histo2DPtr _histFastJets08MultLam, _histFastJets08PtLam,_histFastJets08LhaLam,_histFastJets08WidthLam,_histFastJets08MassLam;
    Histo2DPtr _histFastJets10MultLam, _histFastJets10PtLam,_histFastJets10LhaLam,_histFastJets10WidthLam,_histFastJets10MassLam;





    //addition Q cuts
    Histo1DPtr _histFastJets02MultLam50, _histFastJets02PtLam50,_histFastJets02LhaLam50,_histFastJets02WidthLam50,_histFastJets02MassLam50;
    Histo1DPtr _histFastJets04MultLam50, _histFastJets04PtLam50,_histFastJets04LhaLam50,_histFastJets04WidthLam50,_histFastJets04MassLam50;
    Histo1DPtr _histFastJets06MultLam50, _histFastJets06PtLam50,_histFastJets06LhaLam50,_histFastJets06WidthLam50,_histFastJets06MassLam50;
    Histo1DPtr _histFastJets08MultLam50, _histFastJets08PtLam50,_histFastJets08LhaLam50,_histFastJets08WidthLam50,_histFastJets08MassLam50;
    Histo1DPtr _histFastJets10MultLam50, _histFastJets10PtLam50,_histFastJets10LhaLam50,_histFastJets10WidthLam50,_histFastJets10MassLam50;
    Histo1DPtr _histFastJets02MultLam100, _histFastJets02PtLam100,_histFastJets02LhaLam100,_histFastJets02WidthLam100,_histFastJets02MassLam100;
    Histo1DPtr _histFastJets04MultLam100, _histFastJets04PtLam100,_histFastJets04LhaLam100,_histFastJets04WidthLam100,_histFastJets04MassLam100;
    Histo1DPtr _histFastJets06MultLam100, _histFastJets06PtLam100,_histFastJets06LhaLam100,_histFastJets06WidthLam100,_histFastJets06MassLam100;
    Histo1DPtr _histFastJets08MultLam100, _histFastJets08PtLam100,_histFastJets08LhaLam100,_histFastJets08WidthLam100,_histFastJets08MassLam100;
    Histo1DPtr _histFastJets10MultLam100, _histFastJets10PtLam100,_histFastJets10LhaLam100,_histFastJets10WidthLam100,_histFastJets10MassLam100;
    Histo1DPtr _histFastJets02MultLam200, _histFastJets02PtLam200,_histFastJets02LhaLam200,_histFastJets02WidthLam200,_histFastJets02MassLam200;
    Histo1DPtr _histFastJets04MultLam200, _histFastJets04PtLam200,_histFastJets04LhaLam200,_histFastJets04WidthLam200,_histFastJets04MassLam200;
    Histo1DPtr _histFastJets06MultLam200, _histFastJets06PtLam200,_histFastJets06LhaLam200,_histFastJets06WidthLam200,_histFastJets06MassLam200;
    Histo1DPtr _histFastJets08MultLam200, _histFastJets08PtLam200,_histFastJets08LhaLam200,_histFastJets08WidthLam200,_histFastJets08MassLam200;
    Histo1DPtr _histFastJets10MultLam200, _histFastJets10PtLam200,_histFastJets10LhaLam200,_histFastJets10WidthLam200,_histFastJets10MassLam200;
    Histo1DPtr _histFastJets02MultLam400, _histFastJets02PtLam400,_histFastJets02LhaLam400,_histFastJets02WidthLam400,_histFastJets02MassLam400;
    Histo1DPtr _histFastJets04MultLam400, _histFastJets04PtLam400,_histFastJets04LhaLam400,_histFastJets04WidthLam400,_histFastJets04MassLam400;
    Histo1DPtr _histFastJets06MultLam400, _histFastJets06PtLam400,_histFastJets06LhaLam400,_histFastJets06WidthLam400,_histFastJets06MassLam400;
    Histo1DPtr _histFastJets08MultLam400, _histFastJets08PtLam400,_histFastJets08LhaLam400,_histFastJets08WidthLam400,_histFastJets08MassLam400;
    Histo1DPtr _histFastJets10MultLam400, _histFastJets10PtLam400,_histFastJets10LhaLam400,_histFastJets10WidthLam400,_histFastJets10MassLam400;
    Histo1DPtr _histFastJets02MultLam800, _histFastJets02PtLam800,_histFastJets02LhaLam800,_histFastJets02WidthLam800,_histFastJets02MassLam800;
    Histo1DPtr _histFastJets04MultLam800, _histFastJets04PtLam800,_histFastJets04LhaLam800,_histFastJets04WidthLam800,_histFastJets04MassLam800;
    Histo1DPtr _histFastJets06MultLam800, _histFastJets06PtLam800,_histFastJets06LhaLam800,_histFastJets06WidthLam800,_histFastJets06MassLam800;
    Histo1DPtr _histFastJets08MultLam800, _histFastJets08PtLam800,_histFastJets08LhaLam800,_histFastJets08WidthLam800,_histFastJets08MassLam800;
    Histo1DPtr _histFastJets10MultLam800, _histFastJets10PtLam800,_histFastJets10LhaLam800,_histFastJets10WidthLam800,_histFastJets10MassLam800;

    //mmdt

    Histo1DPtr mmdt_histFastJets02PtReclust,mmdt_histFastJets02PtSubLeading,mmdt_histFastJets02PtLeading,mmdt_histFastJets02Pt, mmdt_histFastJets02Mult, mmdt_histFastJets02E, mmdt_histFastJets02Eta, mmdt_histFastJets02Rapidity, mmdt_histFastJets02Phi;
    Histo1DPtr mmdt_histFastJets04PtReclust,mmdt_histFastJets04PtSubLeading,mmdt_histFastJets04PtLeading,mmdt_histFastJets04Pt, mmdt_histFastJets04Mult, mmdt_histFastJets04E, mmdt_histFastJets04Eta, mmdt_histFastJets04Rapidity, mmdt_histFastJets04Phi;
    Histo1DPtr mmdt_histFastJets06PtReclust,mmdt_histFastJets06PtSubLeading,mmdt_histFastJets06PtLeading,mmdt_histFastJets06Pt, mmdt_histFastJets06Mult, mmdt_histFastJets06E, mmdt_histFastJets06Eta, mmdt_histFastJets06Rapidity, mmdt_histFastJets06Phi;
    Histo1DPtr mmdt_histFastJets08PtReclust,mmdt_histFastJets08PtSubLeading,mmdt_histFastJets08PtLeading,mmdt_histFastJets08Pt, mmdt_histFastJets08Mult, mmdt_histFastJets08E, mmdt_histFastJets08Eta, mmdt_histFastJets08Rapidity, mmdt_histFastJets08Phi;
    Histo1DPtr mmdt_histFastJets10PtReclust,mmdt_histFastJets10PtSubLeading,mmdt_histFastJets10PtLeading,mmdt_histFastJets10Pt, mmdt_histFastJets10Mult, mmdt_histFastJets10E, mmdt_histFastJets10Eta, mmdt_histFastJets10Rapidity, mmdt_histFastJets10Phi;

    Histo2DPtr mmdt_histFastJets02MultLam, mmdt_histFastJets02PtLam,mmdt_histFastJets02LhaLam,mmdt_histFastJets02WidthLam,mmdt_histFastJets02MassLam;
    Histo2DPtr mmdt_histFastJets04MultLam, mmdt_histFastJets04PtLam,mmdt_histFastJets04LhaLam,mmdt_histFastJets04WidthLam,mmdt_histFastJets04MassLam;
    Histo2DPtr mmdt_histFastJets06MultLam, mmdt_histFastJets06PtLam,mmdt_histFastJets06LhaLam,mmdt_histFastJets06WidthLam,mmdt_histFastJets06MassLam;
    Histo2DPtr mmdt_histFastJets08MultLam, mmdt_histFastJets08PtLam,mmdt_histFastJets08LhaLam,mmdt_histFastJets08WidthLam,mmdt_histFastJets08MassLam;
    Histo2DPtr mmdt_histFastJets10MultLam, mmdt_histFastJets10PtLam,mmdt_histFastJets10LhaLam,mmdt_histFastJets10WidthLam,mmdt_histFastJets10MassLam;





    //addition Q cuts
    Histo1DPtr mmdt_histFastJets02MultLam50, mmdt_histFastJets02PtLam50,mmdt_histFastJets02LhaLam50,mmdt_histFastJets02WidthLam50,mmdt_histFastJets02MassLam50;
    Histo1DPtr mmdt_histFastJets04MultLam50, mmdt_histFastJets04PtLam50,mmdt_histFastJets04LhaLam50,mmdt_histFastJets04WidthLam50,mmdt_histFastJets04MassLam50;
    Histo1DPtr mmdt_histFastJets06MultLam50, mmdt_histFastJets06PtLam50,mmdt_histFastJets06LhaLam50,mmdt_histFastJets06WidthLam50,mmdt_histFastJets06MassLam50;
    Histo1DPtr mmdt_histFastJets08MultLam50, mmdt_histFastJets08PtLam50,mmdt_histFastJets08LhaLam50,mmdt_histFastJets08WidthLam50,mmdt_histFastJets08MassLam50;
    Histo1DPtr mmdt_histFastJets10MultLam50, mmdt_histFastJets10PtLam50,mmdt_histFastJets10LhaLam50,mmdt_histFastJets10WidthLam50,mmdt_histFastJets10MassLam50;
    Histo1DPtr mmdt_histFastJets02MultLam100, mmdt_histFastJets02PtLam100,mmdt_histFastJets02LhaLam100,mmdt_histFastJets02WidthLam100,mmdt_histFastJets02MassLam100;
    Histo1DPtr mmdt_histFastJets04MultLam100, mmdt_histFastJets04PtLam100,mmdt_histFastJets04LhaLam100,mmdt_histFastJets04WidthLam100,mmdt_histFastJets04MassLam100;
    Histo1DPtr mmdt_histFastJets06MultLam100, mmdt_histFastJets06PtLam100,mmdt_histFastJets06LhaLam100,mmdt_histFastJets06WidthLam100,mmdt_histFastJets06MassLam100;
    Histo1DPtr mmdt_histFastJets08MultLam100, mmdt_histFastJets08PtLam100,mmdt_histFastJets08LhaLam100,mmdt_histFastJets08WidthLam100,mmdt_histFastJets08MassLam100;
    Histo1DPtr mmdt_histFastJets10MultLam100, mmdt_histFastJets10PtLam100,mmdt_histFastJets10LhaLam100,mmdt_histFastJets10WidthLam100,mmdt_histFastJets10MassLam100;
    Histo1DPtr mmdt_histFastJets02MultLam200, mmdt_histFastJets02PtLam200,mmdt_histFastJets02LhaLam200,mmdt_histFastJets02WidthLam200,mmdt_histFastJets02MassLam200;
    Histo1DPtr mmdt_histFastJets04MultLam200, mmdt_histFastJets04PtLam200,mmdt_histFastJets04LhaLam200,mmdt_histFastJets04WidthLam200,mmdt_histFastJets04MassLam200;
    Histo1DPtr mmdt_histFastJets06MultLam200, mmdt_histFastJets06PtLam200,mmdt_histFastJets06LhaLam200,mmdt_histFastJets06WidthLam200,mmdt_histFastJets06MassLam200;
    Histo1DPtr mmdt_histFastJets08MultLam200, mmdt_histFastJets08PtLam200,mmdt_histFastJets08LhaLam200,mmdt_histFastJets08WidthLam200,mmdt_histFastJets08MassLam200;
    Histo1DPtr mmdt_histFastJets10MultLam200, mmdt_histFastJets10PtLam200,mmdt_histFastJets10LhaLam200,mmdt_histFastJets10WidthLam200,mmdt_histFastJets10MassLam200;
    Histo1DPtr mmdt_histFastJets02MultLam400, mmdt_histFastJets02PtLam400,mmdt_histFastJets02LhaLam400,mmdt_histFastJets02WidthLam400,mmdt_histFastJets02MassLam400;
    Histo1DPtr mmdt_histFastJets04MultLam400, mmdt_histFastJets04PtLam400,mmdt_histFastJets04LhaLam400,mmdt_histFastJets04WidthLam400,mmdt_histFastJets04MassLam400;
    Histo1DPtr mmdt_histFastJets06MultLam400, mmdt_histFastJets06PtLam400,mmdt_histFastJets06LhaLam400,mmdt_histFastJets06WidthLam400,mmdt_histFastJets06MassLam400;
    Histo1DPtr mmdt_histFastJets08MultLam400, mmdt_histFastJets08PtLam400,mmdt_histFastJets08LhaLam400,mmdt_histFastJets08WidthLam400,mmdt_histFastJets08MassLam400;
    Histo1DPtr mmdt_histFastJets10MultLam400, mmdt_histFastJets10PtLam400,mmdt_histFastJets10LhaLam400,mmdt_histFastJets10WidthLam400,mmdt_histFastJets10MassLam400;
    Histo1DPtr mmdt_histFastJets02MultLam800, mmdt_histFastJets02PtLam800,mmdt_histFastJets02LhaLam800,mmdt_histFastJets02WidthLam800,mmdt_histFastJets02MassLam800;
    Histo1DPtr mmdt_histFastJets04MultLam800, mmdt_histFastJets04PtLam800,mmdt_histFastJets04LhaLam800,mmdt_histFastJets04WidthLam800,mmdt_histFastJets04MassLam800;
    Histo1DPtr mmdt_histFastJets06MultLam800, mmdt_histFastJets06PtLam800,mmdt_histFastJets06LhaLam800,mmdt_histFastJets06WidthLam800,mmdt_histFastJets06MassLam800;
    Histo1DPtr mmdt_histFastJets08MultLam800, mmdt_histFastJets08PtLam800,mmdt_histFastJets08LhaLam800,mmdt_histFastJets08WidthLam800,mmdt_histFastJets08MassLam800;
    Histo1DPtr mmdt_histFastJets10MultLam800, mmdt_histFastJets10PtLam800,mmdt_histFastJets10LhaLam800,mmdt_histFastJets10WidthLam800,mmdt_histFastJets10MassLam800;

    //

    //Histo1DPtr ArrayOfHist[5][14];
    Histo1DPtr ArrayOfHist[5][39];
    Histo2DPtr ArrayOfHist2[5][39];
    Histo1DPtr mmdt_ArrayOfHist[5][39];
    Histo2DPtr mmdt_ArrayOfHist2[5][39];
  };

  DECLARE_RIVET_PLUGIN(MC_DIJET_PB_CH);

}

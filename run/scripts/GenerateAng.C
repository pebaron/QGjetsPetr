double GetDRCut(TString a){
    if (a.Contains("FastJets02")) return 0.4;
    if (a.Contains("FastJets04")) return 0.8;
    if (a.Contains("FastJets06")) return 1.2;
    if (a.Contains("FastJets08")) return 1.6;
    if (a.Contains("FastJets10")) return 2.0;
}

int IsIso(string s1, double eta1, double phi1, double eta2, double phi2) {
    double deta = eta1-eta2;
    double dphi = TVector2::Phi_mpi_pi(phi1-phi2);
    double DR = TMath::Sqrt( deta*deta+dphi*dphi );
    double DRCut;
    if (s1.find("FastJets02") != std::string::npos) DRCut = 0.4;
    if (s1.find("FastJets04") != std::string::npos) DRCut = 0.8;
    if (s1.find("FastJets06") != std::string::npos) DRCut = 1.2;
    if (s1.find("FastJets08") != std::string::npos) DRCut = 1.6;
    if (s1.find("FastJets10") != std::string::npos) DRCut = 2.0;
    if (DR < DRCut ) {
        return 0;
    }
    else{
        return 1;
    }
}

//int IsIso(TString AngName,double pt1, double eta1, double phi1, double e1,
//                            double pt2, double eta2, double phi2, double e2) {
//    TLorentzVector p1;
//    TLorentzVector p2;
//    p1.SetPtEtaPhiE(pt1, eta1, phi1, e1);
//    p2.SetPtEtaPhiE(pt2, eta2, phi2, e2);
//    if (p1.DeltaR(p2) < GetAngRCut(AngName.Data()) ) {
//        //cout << "Jets overlaps" << endl;
//        return 0;
//    }
//    else{
//        return 1;
//    }
//}

int GenerateAng(TString EnergyA = "900", TString EnergyB = "2360", bool Pythia = false){

    TFile * rfile;

    if (Pythia){
        rfile = new TFile(TString::Format("out_%s_%s_pythia.root", EnergyA.Data(), EnergyB.Data()), "read");
    }else{
        rfile = new TFile(TString::Format("out_%s_%s.root", EnergyA.Data(), EnergyB.Data()), "read");
    }
    TH2F * fracA = (TH2F*)rfile->Get(TString::Format("GluonFraction_%s", EnergyA.Data() ));
    TH2F * fracB = (TH2F*)rfile->Get(TString::Format("GluonFraction_%s", EnergyB.Data() ));

    double CutPtLow, CutPtUp, CutEtaLow, CutEtaUp;
    double ScaleA, ScaleB;

    vector<TString> Radii;
    vector<TString> Lambdas;
    vector<TString> Q;

    double DRCut;

    Q.push_back("50");
    Q.push_back("100");
    //Q.push_back("200");
    //Q.push_back("400");
    //Q.push_back("800");

    Radii.push_back("02");
    Radii.push_back("04");
    Radii.push_back("06");
    Radii.push_back("08");
    Radii.push_back("10");

    Lambdas.push_back("Mult");
    Lambdas.push_back("Pt");
    Lambdas.push_back("Lha");
    Lambdas.push_back("Width");
    Lambdas.push_back("Mass");

    vector<TString> JetAng;
    vector<TString> JetPt;
    vector<TString> JetEta;
    vector<TString> JetPhi;
    vector<TString> JetE;
    vector<TString> JetFraction;

    vector<TString> mmdt_JetAng;
    vector<TString> mmdt_JetPt;
    vector<TString> mmdt_JetEta;
    vector<TString> mmdt_JetPhi;
    vector<TString> mmdt_JetE;
    vector<TString> mmdt_JetFraction;

    std::map<TString, TTree*> TreeMapA;
    std::map<TString, TTree*> TreeMapB;

    std::map<TString, vector<TH1D*>> h_MapA_Quark;
    std::map<TString, vector<TH1D*>> h_MapB_Quark;

    std::map<TString, vector<TH1D*>> h_MapA_Gluon;
    std::map<TString, vector<TH1D*>> h_MapB_Gluon;

    std::map<TString, vector<TH1D*>> h_no_cut_Map_Gluon;
    std::map<TString, vector<TH1D*>> h_no_cut_Map_Quark;


    for (int j = 0; j < Lambdas.size();j++){
        for (int i = 0; i < Radii.size();i++){
            for (int k = 0; k < Q.size();k++){
                JetAng.push_back( TString::Format("FastJets%s%sLam%s", Radii[i].Data(), Lambdas[j].Data(), Q[k].Data() ) );
                JetPt.push_back( TString::Format("FastJets%sPt", Radii[i].Data() ) );
                JetEta.push_back( TString::Format("FastJets%sEta", Radii[i].Data() ) );
                JetPhi.push_back( TString::Format("FastJets%sPhi", Radii[i].Data() ) );
                JetE.push_back( TString::Format("FastJets%sE", Radii[i].Data() ) );
                JetFraction.push_back( TString::Format("FastJets%sFraction", Radii[i].Data() ) );
                

                mmdt_JetAng.push_back( TString::Format("mmdt_FastJets%s%sLam%s", Radii[i].Data(), Lambdas[j].Data(), Q[k].Data() ) );
                mmdt_JetPt.push_back(  TString::Format("mmdt_FastJets%sPt", Radii[i].Data() ) );
                mmdt_JetEta.push_back( TString::Format("mmdt_FastJets%sEta", Radii[i].Data() ) );
                mmdt_JetPhi.push_back( TString::Format("mmdt_FastJets%sPhi", Radii[i].Data() ) );
                mmdt_JetE.push_back( TString::Format("mmdt_FastJets%sE", Radii[i].Data() ) );
                mmdt_JetFraction.push_back( TString::Format("mmdt_FastJets%sFraction", Radii[i].Data() ) );
            }
        }
    }


    for (int i = 0; i<JetAng.size(); i++){
        TreeMapA[JetAng[i]]           = (TTree*)rfile->Get(TString::Format("%s_%s", JetAng[i].Data(), EnergyA.Data()));
        TreeMapA[JetPt[i]]            = (TTree*)rfile->Get(TString::Format("%s_%s", JetPt[i].Data(), EnergyA.Data()));
        TreeMapA[JetEta[i]]           = (TTree*)rfile->Get(TString::Format("%s_%s", JetEta[i].Data(), EnergyA.Data()));
        TreeMapA[JetPhi[i]]           = (TTree*)rfile->Get(TString::Format("%s_%s", JetPhi[i].Data(), EnergyA.Data()));
        TreeMapA[JetE[i]]             = (TTree*)rfile->Get(TString::Format("%s_%s", JetE[i].Data(), EnergyA.Data()));
        TreeMapA[JetFraction[i]]      = (TTree*)rfile->Get(TString::Format("%s_%s", JetFraction[i].Data(), EnergyA.Data()));
        TreeMapA[mmdt_JetAng[i]]      = (TTree*)rfile->Get(TString::Format("%s_%s", mmdt_JetAng[i].Data(), EnergyA.Data()));
        TreeMapA[mmdt_JetPt[i]]       = (TTree*)rfile->Get(TString::Format("%s_%s", mmdt_JetPt[i].Data(), EnergyA.Data()));
        TreeMapA[mmdt_JetEta[i]]      = (TTree*)rfile->Get(TString::Format("%s_%s", mmdt_JetEta[i].Data(), EnergyA.Data()));
        TreeMapA[mmdt_JetPhi[i]]      = (TTree*)rfile->Get(TString::Format("%s_%s", mmdt_JetPhi[i].Data(), EnergyA.Data()));
        TreeMapA[mmdt_JetE[i]]        = (TTree*)rfile->Get(TString::Format("%s_%s", mmdt_JetE[i].Data(), EnergyA.Data()));
        TreeMapA[mmdt_JetFraction[i]] = (TTree*)rfile->Get(TString::Format("%s_%s", mmdt_JetFraction[i].Data(), EnergyA.Data()));

        TreeMapB[JetAng[i]]           = (TTree*)rfile->Get(TString::Format("%s_%s", JetAng[i].Data(), EnergyB.Data()));
        TreeMapB[JetPt[i]]            = (TTree*)rfile->Get(TString::Format("%s_%s", JetPt[i].Data(), EnergyB.Data()));
        TreeMapB[JetEta[i]]           = (TTree*)rfile->Get(TString::Format("%s_%s", JetEta[i].Data(), EnergyB.Data()));
        TreeMapB[JetPhi[i]]           = (TTree*)rfile->Get(TString::Format("%s_%s", JetPhi[i].Data(), EnergyB.Data()));
        TreeMapB[JetE[i]]             = (TTree*)rfile->Get(TString::Format("%s_%s", JetE[i].Data(), EnergyB.Data()));
        TreeMapB[JetFraction[i]]      = (TTree*)rfile->Get(TString::Format("%s_%s", JetFraction[i].Data(), EnergyB.Data()));
        TreeMapB[mmdt_JetAng[i]]      = (TTree*)rfile->Get(TString::Format("%s_%s", mmdt_JetAng[i].Data(), EnergyB.Data()));
        TreeMapB[mmdt_JetPt[i]]       = (TTree*)rfile->Get(TString::Format("%s_%s", mmdt_JetPt[i].Data(), EnergyB.Data()));
        TreeMapB[mmdt_JetEta[i]]      = (TTree*)rfile->Get(TString::Format("%s_%s", mmdt_JetEta[i].Data(), EnergyB.Data()));
        TreeMapB[mmdt_JetPhi[i]]      = (TTree*)rfile->Get(TString::Format("%s_%s", mmdt_JetPhi[i].Data(), EnergyB.Data()));
        TreeMapB[mmdt_JetE[i]]        = (TTree*)rfile->Get(TString::Format("%s_%s", mmdt_JetE[i].Data(), EnergyB.Data()));
        TreeMapB[mmdt_JetFraction[i]] = (TTree*)rfile->Get(TString::Format("%s_%s", mmdt_JetFraction[i].Data(), EnergyB.Data()));

        TreeMapA[JetAng[i]]     ->AddFriend(TreeMapA[JetPt[i]]           );
        TreeMapA[JetAng[i]]     ->AddFriend(TreeMapA[JetEta[i]]          );
        TreeMapA[JetAng[i]]     ->AddFriend(TreeMapA[JetPhi[i]]          );
        TreeMapA[JetAng[i]]     ->AddFriend(TreeMapA[JetE[i]]            );
        TreeMapA[JetAng[i]]     ->AddFriend(TreeMapA[JetFraction[i]]     );
        TreeMapA[JetAng[i]]     ->AddFriend(TreeMapA[mmdt_JetAng[i]]     );
        TreeMapA[JetAng[i]]     ->AddFriend(TreeMapA[mmdt_JetPt[i]]      );
        TreeMapA[JetAng[i]]     ->AddFriend(TreeMapA[mmdt_JetEta[i]]     );
        TreeMapA[JetAng[i]]     ->AddFriend(TreeMapA[mmdt_JetE[i]]       );
        TreeMapA[JetAng[i]]     ->AddFriend(TreeMapA[mmdt_JetPhi[i]]     );
        TreeMapA[JetAng[i]]     ->AddFriend(TreeMapA[mmdt_JetFraction[i]]);

        TreeMapA[JetAng[i]]     ->AddFriend(TreeMapB[JetAng[i]]          );
        TreeMapA[JetAng[i]]     ->AddFriend(TreeMapB[JetPt[i]]           );
        TreeMapA[JetAng[i]]     ->AddFriend(TreeMapB[JetEta[i]]          );
        TreeMapA[JetAng[i]]     ->AddFriend(TreeMapB[JetPhi[i]]          );
        TreeMapA[JetAng[i]]     ->AddFriend(TreeMapB[JetE[i]]            );
        TreeMapA[JetAng[i]]     ->AddFriend(TreeMapB[JetFraction[i]]     );
        TreeMapA[JetAng[i]]     ->AddFriend(TreeMapB[mmdt_JetAng[i]]     );
        TreeMapA[JetAng[i]]     ->AddFriend(TreeMapB[mmdt_JetPt[i]]      );
        TreeMapA[JetAng[i]]     ->AddFriend(TreeMapB[mmdt_JetEta[i]]     );
        TreeMapA[JetAng[i]]     ->AddFriend(TreeMapB[mmdt_JetPhi[i]]     );
        TreeMapA[JetAng[i]]     ->AddFriend(TreeMapB[mmdt_JetE[i]]       );
        TreeMapA[JetAng[i]]     ->AddFriend(TreeMapB[mmdt_JetFraction[i]]);

        TreeMapA[mmdt_JetAng[i]]     ->AddFriend(TreeMapA[JetPt[i]]           );
        TreeMapA[mmdt_JetAng[i]]     ->AddFriend(TreeMapA[JetEta[i]]          );
        TreeMapA[mmdt_JetAng[i]]     ->AddFriend(TreeMapA[JetPhi[i]]          );
        TreeMapA[mmdt_JetAng[i]]     ->AddFriend(TreeMapA[JetE[i]]            );
        TreeMapA[mmdt_JetAng[i]]     ->AddFriend(TreeMapA[JetFraction[i]]     );
        TreeMapA[mmdt_JetAng[i]]     ->AddFriend(TreeMapA[JetAng[i]]     );
        TreeMapA[mmdt_JetAng[i]]     ->AddFriend(TreeMapA[mmdt_JetPt[i]]      );
        TreeMapA[mmdt_JetAng[i]]     ->AddFriend(TreeMapA[mmdt_JetEta[i]]     );
        TreeMapA[mmdt_JetAng[i]]     ->AddFriend(TreeMapA[mmdt_JetPhi[i]]     );
        TreeMapA[mmdt_JetAng[i]]     ->AddFriend(TreeMapA[mmdt_JetE[i]]       );
        TreeMapA[mmdt_JetAng[i]]     ->AddFriend(TreeMapA[mmdt_JetFraction[i]]);

        TreeMapA[mmdt_JetAng[i]]     ->AddFriend(TreeMapB[JetAng[i]]          );
        TreeMapA[mmdt_JetAng[i]]     ->AddFriend(TreeMapB[JetPt[i]]           );
        TreeMapA[mmdt_JetAng[i]]     ->AddFriend(TreeMapB[JetEta[i]]          );
        TreeMapA[mmdt_JetAng[i]]     ->AddFriend(TreeMapB[JetPhi[i]]          );
        TreeMapA[mmdt_JetAng[i]]     ->AddFriend(TreeMapB[JetE[i]]            );
        TreeMapA[mmdt_JetAng[i]]     ->AddFriend(TreeMapB[JetFraction[i]]     );
        TreeMapA[mmdt_JetAng[i]]     ->AddFriend(TreeMapB[JetAng[i]]     );
        TreeMapA[mmdt_JetAng[i]]     ->AddFriend(TreeMapB[mmdt_JetPt[i]]      );
        TreeMapA[mmdt_JetAng[i]]     ->AddFriend(TreeMapB[mmdt_JetEta[i]]     );
        TreeMapA[mmdt_JetAng[i]]     ->AddFriend(TreeMapB[mmdt_JetPhi[i]]     );
        TreeMapA[mmdt_JetAng[i]]     ->AddFriend(TreeMapB[mmdt_JetE[i]]       );
        TreeMapA[mmdt_JetAng[i]]     ->AddFriend(TreeMapB[mmdt_JetFraction[i]]);

        //
        TreeMapB[JetAng[i]]     ->AddFriend(TreeMapB[JetPt[i]]           );
        TreeMapB[JetAng[i]]     ->AddFriend(TreeMapB[JetEta[i]]          );
        TreeMapB[JetAng[i]]     ->AddFriend(TreeMapB[JetPhi[i]]          );
        TreeMapB[JetAng[i]]     ->AddFriend(TreeMapB[JetE[i]]            );
        TreeMapB[JetAng[i]]     ->AddFriend(TreeMapB[JetFraction[i]]     );
        TreeMapB[JetAng[i]]     ->AddFriend(TreeMapB[mmdt_JetAng[i]]     );
        TreeMapB[JetAng[i]]     ->AddFriend(TreeMapB[mmdt_JetPt[i]]      );
        TreeMapB[JetAng[i]]     ->AddFriend(TreeMapB[mmdt_JetEta[i]]     );
        TreeMapB[JetAng[i]]     ->AddFriend(TreeMapB[mmdt_JetPhi[i]]     );
        TreeMapB[JetAng[i]]     ->AddFriend(TreeMapB[mmdt_JetE[i]]       );
        TreeMapB[JetAng[i]]     ->AddFriend(TreeMapB[mmdt_JetFraction[i]]);

        TreeMapB[JetAng[i]]     ->AddFriend(TreeMapA[JetAng[i]]          );
        TreeMapB[JetAng[i]]     ->AddFriend(TreeMapA[JetPt[i]]           );
        TreeMapB[JetAng[i]]     ->AddFriend(TreeMapA[JetEta[i]]          );
        TreeMapB[JetAng[i]]     ->AddFriend(TreeMapA[JetPhi[i]]          );
        TreeMapB[JetAng[i]]     ->AddFriend(TreeMapA[JetE[i]]            );
        TreeMapB[JetAng[i]]     ->AddFriend(TreeMapA[JetFraction[i]]     );
        TreeMapB[JetAng[i]]     ->AddFriend(TreeMapA[mmdt_JetAng[i]]     );
        TreeMapB[JetAng[i]]     ->AddFriend(TreeMapA[mmdt_JetPt[i]]      );
        TreeMapB[JetAng[i]]     ->AddFriend(TreeMapA[mmdt_JetEta[i]]     );
        TreeMapB[JetAng[i]]     ->AddFriend(TreeMapA[mmdt_JetPhi[i]]     );
        TreeMapB[JetAng[i]]     ->AddFriend(TreeMapA[mmdt_JetE[i]]       );
        TreeMapB[JetAng[i]]     ->AddFriend(TreeMapA[mmdt_JetFraction[i]]);

        TreeMapB[mmdt_JetAng[i]]     ->AddFriend(TreeMapB[JetPt[i]]           );
        TreeMapB[mmdt_JetAng[i]]     ->AddFriend(TreeMapB[JetEta[i]]          );
        TreeMapB[mmdt_JetAng[i]]     ->AddFriend(TreeMapB[JetPhi[i]]          );
        TreeMapB[mmdt_JetAng[i]]     ->AddFriend(TreeMapB[JetE[i]]            );
        TreeMapB[mmdt_JetAng[i]]     ->AddFriend(TreeMapB[JetFraction[i]]     );
        TreeMapB[mmdt_JetAng[i]]     ->AddFriend(TreeMapB[JetAng[i]]     );
        TreeMapB[mmdt_JetAng[i]]     ->AddFriend(TreeMapB[mmdt_JetPt[i]]      );
        TreeMapB[mmdt_JetAng[i]]     ->AddFriend(TreeMapB[mmdt_JetEta[i]]     );
        TreeMapB[mmdt_JetAng[i]]     ->AddFriend(TreeMapB[mmdt_JetPhi[i]]     );
        TreeMapB[mmdt_JetAng[i]]     ->AddFriend(TreeMapB[mmdt_JetE[i]]       );
        TreeMapB[mmdt_JetAng[i]]     ->AddFriend(TreeMapB[mmdt_JetFraction[i]]);

        TreeMapB[mmdt_JetAng[i]]     ->AddFriend(TreeMapA[JetAng[i]]          );
        TreeMapB[mmdt_JetAng[i]]     ->AddFriend(TreeMapA[JetPt[i]]           );
        TreeMapB[mmdt_JetAng[i]]     ->AddFriend(TreeMapA[JetEta[i]]          );
        TreeMapB[mmdt_JetAng[i]]     ->AddFriend(TreeMapA[JetPhi[i]]          );
        TreeMapB[mmdt_JetAng[i]]     ->AddFriend(TreeMapA[JetE[i]]            );
        TreeMapB[mmdt_JetAng[i]]     ->AddFriend(TreeMapA[JetFraction[i]]     );
        TreeMapB[mmdt_JetAng[i]]     ->AddFriend(TreeMapA[JetAng[i]]     );
        TreeMapB[mmdt_JetAng[i]]     ->AddFriend(TreeMapA[mmdt_JetPt[i]]      );
        TreeMapB[mmdt_JetAng[i]]     ->AddFriend(TreeMapA[mmdt_JetEta[i]]     );
        TreeMapB[mmdt_JetAng[i]]     ->AddFriend(TreeMapA[mmdt_JetPhi[i]]     );
        TreeMapB[mmdt_JetAng[i]]     ->AddFriend(TreeMapA[mmdt_JetE[i]]       );
        TreeMapB[mmdt_JetAng[i]]     ->AddFriend(TreeMapA[mmdt_JetFraction[i]]);
        

    }

    double fracA_no_cut;// = fracA->ProjectionX()->GetBinContent(fracA->ProjectionX()->GetXaxis()->FindBin(55.5) ) / 10.;
    double fracB_no_cut;// = fracB->ProjectionX()->GetBinContent(fracB->ProjectionX()->GetXaxis()->FindBin(55.5) ) / 10.;
    double fracA_no_cut_mmdt;
    double fracB_no_cut_mmdt;

    TString Cut;
    TString CutSub;
    TString CutOver;
    TH1D * h;
    TH1D * h2;
    TH1D * h_sub;
    TH1D * h2_sub;

    TH1D * h_no_cutA;
    TH1D * h_no_cutA_mmdt;
    TH1D * h_no_cutB;
    TH1D * h_no_cutB_mmdt;
    
    TH1D * h_no_cutA_clone;
    TH1D * h_no_cutA_mmdt_clone;
    TH1D * h_no_cutB_clone;
    TH1D * h_no_cutB_mmdt_clone;

    vector<TH1D*> nocuts;
    //std::map<TString, vector<TH1D*>> h_no_cut_Map_Gluon;
    //std::map<TString, vector<TH1D*>> h_no_cut_Map_Quark;

    double NormFact1;
    double NormFact2;
    double NormFact3;
    double NormFact4;
    TString CutNorm; 
    TString CutExtraJets;
    int neg_index;
    TH1D * h_ptA;
    TH1D * h_ptB;
    TH1D * h_ptA_mmdt;
    TH1D * h_ptB_mmdt;
    TString Cut_ptA;
    TString Cut_ptB;
    TString Cut_ptA_mmdt;
    TString Cut_ptB_mmdt;
    for (int k = 0; k<JetAng.size(); k++){
    //for (int k = 4; k<5; k++){
    for (int i = 1; i<=fracA->GetXaxis()->GetNbins(); i++){//thinking of starting from 13th bin 52Pt
        neg_index = 5;
        for (int j = 6; j<=fracA->GetYaxis()->GetNbins(); j++){ //from 6 due to positive part of eta and averaging two jets pt and eta
        CutPtLow = fracA->GetXaxis()->GetBinLowEdge(i);
        CutPtUp = fracA->GetXaxis()->GetBinUpEdge(i);
        CutEtaLow = fracA->GetYaxis()->GetBinLowEdge(j);
        CutEtaUp = fracA->GetYaxis()->GetBinUpEdge(j);
        ScaleA = 0.5*(fracA->GetBinContent(i,j) + fracA->GetBinContent(i,neg_index));//6-5,7-4,8-3,9-2,10-1
        ScaleB = 0.5*(fracB->GetBinContent(i,j) + fracB->GetBinContent(i,neg_index));//6-5,7-4,8-3,9-2,10-1
        neg_index = neg_index -1;
            Cut = TString::Format("(%s.%s[0] >= %f)&&(%s.%s[0] < %f)&&(TMath::Abs(%s.%s[0])  >= %f)&&(TMath::Abs(%s.%s[0]) < %f)", 
                                    TreeMapA[JetPt[k]]->GetName(),JetPt[k].Data(),
                                    CutPtLow, 
                                    TreeMapA[JetPt[k]]->GetName(), JetPt[k].Data(), 
                                    CutPtUp,
                                    TreeMapA[JetEta[k]]->GetName(),JetEta[k].Data(), 
                                    CutEtaLow, 
                                    TreeMapA[JetEta[k]]->GetName(), JetEta[k].Data(), 
                                    CutEtaUp);
            Cut_ptA = TString::Format("%s.%s", TreeMapA[JetPt[k]]->GetName(), JetPt[k].Data());
            CutSub = Cut.Copy();
            CutSub.ReplaceAll("[0]", "[1]");
            DRCut = GetDRCut(JetAng[k].Data());
            CutOver = TString::Format("(TMath::Sqrt( TMath::Power(%s.%s[0]-%s.%s[1],2)+TMath::Power(TVector2::Phi_mpi_pi(%s.%s[0]-%s.%s[1]),2) ) >= %f)", 
            TreeMapA[JetEta[k]]->GetName(),JetEta[k].Data(),
            TreeMapA[JetEta[k]]->GetName(),JetEta[k].Data(),
            TreeMapA[JetPhi[k]]->GetName(),JetPhi[k].Data(),
            TreeMapA[JetPhi[k]]->GetName(),JetPhi[k].Data()
            , DRCut);
            Cut+=TString::Format("&&%s", CutOver.Data() );
            CutSub+=TString::Format("&&%s", CutOver.Data() );
            CutExtraJets = TString::Format("(@%s.size()<=2)", JetAng[k].Data() );
            Cut+=TString::Format("&&%s", CutExtraJets.Data() );
            CutSub+=TString::Format("&&%s", CutExtraJets.Data() );
            if ((i==1)&&(j==6)){
                CutNorm = TString::Format("(%s.%s >= 0.)&&(%s.%s < 200.)&&(TMath::Abs(%s.%s)  >= 0)&&(TMath::Abs(%s.%s) < 2.5)", 
                                    TreeMapA[JetPt[k]]->GetName(),JetPt[k].Data(),
                                    TreeMapA[JetPt[k]]->GetName(), JetPt[k].Data(), 
                                    TreeMapA[JetEta[k]]->GetName(),JetEta[k].Data(), 
                                    TreeMapA[JetEta[k]]->GetName(), JetEta[k].Data()
                                    );
                CutNorm+=TString::Format("&&%s", CutOver.Data() );
                CutNorm+=TString::Format("&&%s", CutExtraJets.Data() );

            }
            if (JetAng[k].Contains("MultLam")){
                TreeMapA[JetAng[k]]          ->Draw(TString::Format("%s[0] >> h_%s_%i_%i_%i(50,0,100)", JetAng[k].Data() , JetAng[k].Data(), i,j,k), Cut.Data() , "goff"); 
                TreeMapA[JetAng[k]]          ->Draw(TString::Format("%s[1] >> h_sub_%s_%i_%i_%i(50,0,100)", JetAng[k].Data() , JetAng[k].Data(), i,j,k), CutSub.Data() , "goff"); 
                if ((i==1)&&(j==6)) {
                    TreeMapA[JetAng[k]]->Draw(TString::Format("%s >> h_no_cut_%s(50,0,100)", JetAng[k].Data() , JetAng[k].Data()), CutNorm.Data() , "goff"); 
                    TreeMapA[JetAng[k]]->Draw(TString::Format("%s >> h_ptA(500,0,500)", Cut_ptA.Data()), CutNorm.Data(), "goff" );
                    }
            }else{
                TreeMapA[JetAng[k]]          ->Draw(TString::Format("%s[0] >> h_%s_%i_%i_%i(50,0,1)", JetAng[k].Data() , JetAng[k].Data(), i,j,k), Cut.Data() , "goff"); 
                TreeMapA[JetAng[k]]          ->Draw(TString::Format("%s[1] >> h_sub_%s_%i_%i_%i(50,0,1)", JetAng[k].Data() , JetAng[k].Data(), i,j,k), CutSub.Data() , "goff"); 
                if ((i==1)&&(j==6)) {
                    TreeMapA[JetAng[k]]->Draw(TString::Format("%s >> h_no_cut_%s(50,0,1)", JetAng[k].Data() , JetAng[k].Data()), CutNorm.Data() , "goff"); 
                    TreeMapA[JetAng[k]]->Draw(TString::Format("%s >> h_ptA(500,0,500)", Cut_ptA.Data()), CutNorm.Data(), "goff" );
                }
            }
            h = (TH1D*)gDirectory->Get(TString::Format("h_%s_%i_%i_%i", JetAng[k].Data(), i,j,k));
            h_sub = (TH1D*)gDirectory->Get(TString::Format("h_sub_%s_%i_%i_%i", JetAng[k].Data(), i,j,k));
            h->Add(h_sub);
            if ((i==1)&&(j==6)) {
                h_no_cutA=(TH1D*)gDirectory->Get(TString::Format("h_no_cut_%s", JetAng[k].Data()));
                NormFact1 = h_no_cutA->GetEntries();
                h_no_cutA->Scale(1./h_no_cutA->GetEntries());
                h_ptA = (TH1D*)gDirectory->Get("h_ptA");
                fracA_no_cut = fracA->ProjectionX()->GetBinContent(fracA->ProjectionX()->GetXaxis()->FindBin( h_ptA->GetMean() ) ) / 10.;
                cout << "Pt Mean A = " << h_ptA->GetMean() << endl;
            }
            //h->Scale(1./NormFact1);
            //if (h->GetEntries()>0) h->Scale(1./h->GetEntries());
            h2= (TH1D*)h->Clone(TString::Format("%s_clone", h->GetName()));
            

            if ((ScaleA-ScaleB)!=0) {h->Scale(-1*(ScaleB)/(ScaleA-ScaleB));}else{
                h->Scale(0.);
            };
            h_MapA_Quark[JetAng[k].Data()].push_back(h);
            if ((ScaleA-ScaleB)!=0) {h2->Scale((1-ScaleB)/(ScaleA-ScaleB));}else{
                h2->Scale(0);
            };
            h_MapA_Gluon[JetAng[k].Data()].push_back(h2);
            // continue here !!!
            //if (h->Integral()>0.){cout << h->Integral() <<endl;
            
            //cout << TreeMapA[JetAng[k]]->GetName() << "->Draw(" << JetAng[k] << ",\"" << Cut.Data() <<"\")" << endl;}
            Cut = TString::Format("(%s.%s[0] >= %f)&&(%s.%s[0] < %f)&&(TMath::Abs(%s.%s[0])  >= %f)&&(TMath::Abs(%s.%s[0]) < %f)", 
                                    TreeMapA[mmdt_JetPt[k]]->GetName(),mmdt_JetPt[k].Data(),
                                    CutPtLow, 
                                    TreeMapA[mmdt_JetPt[k]]->GetName(), mmdt_JetPt[k].Data(), 
                                    CutPtUp,
                                    TreeMapA[mmdt_JetEta[k]]->GetName(),mmdt_JetEta[k].Data(), 
                                    CutEtaLow, 
                                    TreeMapA[mmdt_JetEta[k]]->GetName(), mmdt_JetEta[k].Data(), 
                                    CutEtaUp);
            Cut_ptA_mmdt = TString::Format("%s.%s", TreeMapA[mmdt_JetPt[k]]->GetName(), mmdt_JetPt[k].Data());
            CutSub = Cut.Copy();
            CutSub.ReplaceAll("[0]", "[1]");
            DRCut = GetDRCut(mmdt_JetAng[k].Data());
            CutOver = TString::Format("(TMath::Sqrt( TMath::Power(%s.%s[0]-%s.%s[1],2)+TMath::Power(TVector2::Phi_mpi_pi(%s.%s[0]-%s.%s[1]),2) ) >= %f)", 
            TreeMapA[mmdt_JetEta[k]]->GetName(),mmdt_JetEta[k].Data(),
            TreeMapA[mmdt_JetEta[k]]->GetName(),mmdt_JetEta[k].Data(),
            TreeMapA[mmdt_JetPhi[k]]->GetName(),mmdt_JetPhi[k].Data(),
            TreeMapA[mmdt_JetPhi[k]]->GetName(),mmdt_JetPhi[k].Data()
            , DRCut);
            Cut+=TString::Format("&&%s", CutOver.Data() );
            CutSub+=TString::Format("&&%s", CutOver.Data() );
            CutExtraJets = TString::Format("(@%s.size()<=2)", mmdt_JetAng[k].Data() );
            Cut+=TString::Format("&&%s", CutExtraJets.Data() );
            CutSub+=TString::Format("&&%s", CutExtraJets.Data() );
            if ((i==1)&&(j==6)){
                CutNorm = TString::Format("(%s.%s >= 0.)&&(%s.%s < 200.)&&(TMath::Abs(%s.%s)  >= 0)&&(TMath::Abs(%s.%s) < 2.5)", 
                                    TreeMapA[mmdt_JetPt[k]]->GetName(),  mmdt_JetPt[k].Data(),
                                    TreeMapA[mmdt_JetPt[k]]->GetName(),  mmdt_JetPt[k].Data(), 
                                    TreeMapA[mmdt_JetEta[k]]->GetName(), mmdt_JetEta[k].Data(), 
                                    TreeMapA[mmdt_JetEta[k]]->GetName(), mmdt_JetEta[k].Data()
                                    );
                CutNorm+=TString::Format("&&%s", CutOver.Data() );
                CutNorm+=TString::Format("&&%s", CutExtraJets.Data() );
            }
            if (mmdt_JetAng[k].Contains("MultLam")){
                TreeMapA[mmdt_JetAng[k]]     ->Draw(TString::Format("%s[0] >> h_%s_%i_%i_%i(50,0,100)", mmdt_JetAng[k].Data() , mmdt_JetAng[k].Data(), i,j,k), Cut.Data() , "goff");
                TreeMapA[mmdt_JetAng[k]]     ->Draw(TString::Format("%s[1] >> h_sub_%s_%i_%i_%i(50,0,100)", mmdt_JetAng[k].Data() , mmdt_JetAng[k].Data(), i,j,k), CutSub.Data() , "goff");
                if ((i==1)&&(j==6)){
                    TreeMapA[mmdt_JetAng[k]]->Draw(TString::Format("%s >> h_no_cut_%s(50,0,100)", mmdt_JetAng[k].Data() , mmdt_JetAng[k].Data()), CutNorm.Data() , "goff"); 
                    TreeMapA[mmdt_JetAng[k]]->Draw(TString::Format("%s >> h_ptA_mmdt(500,0,500)", Cut_ptA_mmdt.Data()), CutNorm.Data(), "goff" );
                    }
            }else{
                TreeMapA[mmdt_JetAng[k]]     ->Draw(TString::Format("%s[0] >> h_%s_%i_%i_%i(50,0,1)", mmdt_JetAng[k].Data() , mmdt_JetAng[k].Data(), i,j,k), Cut.Data() , "goff");
                TreeMapA[mmdt_JetAng[k]]     ->Draw(TString::Format("%s[1] >> h_sub_%s_%i_%i_%i(50,0,1)", mmdt_JetAng[k].Data() , mmdt_JetAng[k].Data(), i,j,k), CutSub.Data() , "goff");
                if ((i==1)&&(j==6)){
                    TreeMapA[mmdt_JetAng[k]]->Draw(TString::Format("%s >> h_no_cut_%s(50,0,1)", mmdt_JetAng[k].Data() , mmdt_JetAng[k].Data()), CutNorm.Data() , "goff"); 
                    TreeMapA[mmdt_JetAng[k]]->Draw(TString::Format("%s >> h_ptA_mmdt(500,0,500)", Cut_ptA_mmdt.Data()), CutNorm.Data(), "goff" );
                    }
            }
            h = (TH1D*)gDirectory->Get(TString::Format("h_%s_%i_%i_%i", mmdt_JetAng[k].Data(), i,j,k));
            h_sub = (TH1D*)gDirectory->Get(TString::Format("h_sub_%s_%i_%i_%i", mmdt_JetAng[k].Data(), i,j,k));
            if ((i==1)&&(j==6)) {
                h_no_cutA_mmdt=(TH1D*)gDirectory->Get(TString::Format("h_no_cut_%s", mmdt_JetAng[k].Data()));
                NormFact2 = h_no_cutA_mmdt->GetEntries();
                h_no_cutA_mmdt->Scale(1./h_no_cutA_mmdt->GetEntries());
                h_ptA_mmdt = (TH1D*)gDirectory->Get("h_ptA_mmdt");
                fracA_no_cut_mmdt = fracA->ProjectionX()->GetBinContent(fracA->ProjectionX()->GetXaxis()->FindBin( h_ptA_mmdt->GetMean() ) ) / 10.;
                cout << "Pt Mean A mmdt = " << h_ptA_mmdt->GetMean() << endl;
            }
            h->Add(h_sub);
            //h->Scale(1./NormFact2);
            //if (h->GetEntries()>0) h->Scale(1./h->GetEntries());
            h2= (TH1D*)h->Clone(TString::Format("%s_clone", h->GetName()));
            if ((ScaleA-ScaleB)!=0) {h->Scale(-1*(ScaleB)/(ScaleA-ScaleB));}else{
                h->Scale(0.);
            };
            h_MapA_Quark[mmdt_JetAng[k].Data()].push_back(h);
            if ((ScaleA-ScaleB)!=0) {h2->Scale((1-ScaleB)/(ScaleA-ScaleB));}else{
                h2->Scale(0.);
            };
            h_MapA_Gluon[mmdt_JetAng[k].Data()].push_back(h2);
            Cut = TString::Format("(%s.%s[0] >= %f)&&(%s.%s[0] < %f)&&(TMath::Abs(%s.%s[0])  >= %f)&&(TMath::Abs(%s.%s[0]) < %f)", 
                                    TreeMapB[JetPt[k]]->GetName(),JetPt[k].Data(),
                                    CutPtLow, 
                                    TreeMapB[JetPt[k]]->GetName(), JetPt[k].Data(), 
                                    CutPtUp,
                                    TreeMapB[JetEta[k]]->GetName(),JetEta[k].Data(), 
                                    CutEtaLow, 
                                    TreeMapB[JetEta[k]]->GetName(), JetEta[k].Data(), 
                                    CutEtaUp);

            //TreeMapB[JetAng[k]]          ->Draw(JetAng[k]          .Data(), Cut.Data() , "goff");
            Cut_ptB = TString::Format("%s.%s", TreeMapB[JetPt[k]]->GetName(), JetPt[k].Data());
            CutSub = Cut.Copy();
            CutSub.ReplaceAll("[0]", "[1]");
            DRCut = GetDRCut(JetAng[k].Data());
            CutOver = TString::Format("(TMath::Sqrt( TMath::Power(%s.%s[0]-%s.%s[1],2)+TMath::Power(TVector2::Phi_mpi_pi(%s.%s[0]-%s.%s[1]),2) ) >= %f)", 
            TreeMapB[JetEta[k]]->GetName(),JetEta[k].Data(),
            TreeMapB[JetEta[k]]->GetName(),JetEta[k].Data(),
            TreeMapB[JetPhi[k]]->GetName(),JetPhi[k].Data(),
            TreeMapB[JetPhi[k]]->GetName(),JetPhi[k].Data()
            , DRCut);
            Cut+=TString::Format("&&%s", CutOver.Data() );
            CutSub+=TString::Format("&&%s", CutOver.Data() );
            CutExtraJets = TString::Format("(@%s.size()<=2)", JetAng[k].Data() );
            Cut+=TString::Format("&&%s", CutExtraJets.Data() );
            CutSub+=TString::Format("&&%s", CutExtraJets.Data() );
            if ((i==1)&&(j==6)){
                CutNorm = TString::Format("(%s.%s >= 0.)&&(%s.%s < 200.)&&(TMath::Abs(%s.%s)  >= 0)&&(TMath::Abs(%s.%s) < 2.5)", 
                                    TreeMapB[JetPt[k]]->GetName(),JetPt[k].Data(),
                                    TreeMapB[JetPt[k]]->GetName(), JetPt[k].Data(), 
                                    TreeMapB[JetEta[k]]->GetName(),JetEta[k].Data(), 
                                    TreeMapB[JetEta[k]]->GetName(), JetEta[k].Data()
                                    );
                CutNorm+=TString::Format("&&%s", CutOver.Data() );
                CutNorm+=TString::Format("&&%s", CutExtraJets.Data() );

            }
            if (JetAng[k].Contains("MultLam")){
                TreeMapB[JetAng[k]]          ->Draw(TString::Format("%s[0] >> hB_%s_%i_%i_%i(50,0,100)", JetAng[k].Data() , JetAng[k].Data(), i,j,k), Cut.Data() , "goff"); 
                TreeMapB[JetAng[k]]          ->Draw(TString::Format("%s[1] >> hB_sub_%s_%i_%i_%i(50,0,100)", JetAng[k].Data() , JetAng[k].Data(), i,j,k), CutSub.Data() , "goff"); 
                if ((i==1)&&(j==6)){
                    TreeMapB[JetAng[k]]->Draw(TString::Format("%s >> hB_no_cut_%s(50,0,100)", JetAng[k].Data() , JetAng[k].Data()), CutNorm.Data() , "goff"); 
                    TreeMapB[JetAng[k]]->Draw(TString::Format("%s >> h_ptB(500,0,500)", Cut_ptB.Data()), CutNorm.Data(), "goff" );
                    }
            } else{
                TreeMapB[JetAng[k]]          ->Draw(TString::Format("%s[0] >> hB_%s_%i_%i_%i(50,0,1)", JetAng[k].Data() , JetAng[k].Data(), i,j,k), Cut.Data() , "goff"); 
                TreeMapB[JetAng[k]]          ->Draw(TString::Format("%s[1] >> hB_sub_%s_%i_%i_%i(50,0,1)", JetAng[k].Data() , JetAng[k].Data(), i,j,k), CutSub.Data() , "goff"); 
                if ((i==1)&&(j==6)){
                    TreeMapB[JetAng[k]]->Draw(TString::Format("%s >> hB_no_cut_%s(50,0,1)", JetAng[k].Data() , JetAng[k].Data()), CutNorm.Data() , "goff"); 
                    TreeMapB[JetAng[k]]->Draw(TString::Format("%s >> h_ptB(500,0,500)", Cut_ptB.Data()), CutNorm.Data(), "goff" );
                    }
            }
            h = (TH1D*)gDirectory->Get(TString::Format("hB_%s_%i_%i_%i", JetAng[k].Data(), i,j,k));
            h_sub = (TH1D*)gDirectory->Get(TString::Format("hB_sub_%s_%i_%i_%i", JetAng[k].Data(), i,j,k));
            if ((i==1)&&(j==6)) {
                h_no_cutB=(TH1D*)gDirectory->Get(TString::Format("hB_no_cut_%s", JetAng[k].Data()));
                NormFact3 = h_no_cutB->GetEntries();
                h_no_cutB->Scale(1./h_no_cutB->GetEntries());
                h_ptB = (TH1D*)gDirectory->Get("h_ptB");
                fracB_no_cut = fracB->ProjectionX()->GetBinContent(fracB->ProjectionX()->GetXaxis()->FindBin( h_ptB->GetMean() ) ) / 10.;
                cout << "Pt Mean B = " << h_ptB->GetMean() << endl;
            }
            h->Add(h_sub);
            //h->Scale(1./NormFact3);
            //if (h->GetEntries()>0) h->Scale(1./h->GetEntries());
            h2= (TH1D*)h->Clone(TString::Format("%s_clone", h->GetName()));

            if ((ScaleA-ScaleB)!=0) {h->Scale((ScaleA)/(ScaleA-ScaleB));}else{
                h->Scale(0.);
            };
            h_MapB_Quark[JetAng[k].Data()].push_back(h);
            if ((ScaleA-ScaleB)!=0) {h2->Scale(-1.*(1-ScaleA)/(ScaleA-ScaleB));}else{
                h2->Scale(0.);
            };
            h_MapB_Gluon[JetAng[k].Data()].push_back(h2);
            Cut = TString::Format("(%s.%s[0] >= %f)&&(%s.%s[0] < %f)&&(TMath::Abs(%s.%s[0])  >= %f)&&(TMath::Abs(%s.%s[0]) < %f)", 
                        TreeMapB[mmdt_JetPt[k]]->GetName(),mmdt_JetPt[k].Data(),
                        CutPtLow, 
                        TreeMapB[mmdt_JetPt[k]]->GetName(), mmdt_JetPt[k].Data(), 
                        CutPtUp,
                        TreeMapB[mmdt_JetEta[k]]->GetName(),mmdt_JetEta[k].Data(), 
                        CutEtaLow, 
                        TreeMapB[mmdt_JetEta[k]]->GetName(), mmdt_JetEta[k].Data(), 
                        CutEtaUp);
            //TreeMapB[mmdt_JetAng[k]]     ->Draw(mmdt_JetAng[k]     .Data(), Cut.Data() , "goff");
            Cut_ptB_mmdt = TString::Format("%s.%s", TreeMapB[mmdt_JetPt[k]]->GetName(), mmdt_JetPt[k].Data());
            CutSub = Cut.Copy();
            CutSub.ReplaceAll("[0]", "[1]");
            DRCut = GetDRCut(mmdt_JetAng[k].Data());
            CutOver = TString::Format("(TMath::Sqrt( TMath::Power(%s.%s[0]-%s.%s[1],2)+TMath::Power(TVector2::Phi_mpi_pi(%s.%s[0]-%s.%s[1]),2) ) >= %f)", 
            TreeMapB[mmdt_JetEta[k]]->GetName(),mmdt_JetEta[k].Data(),
            TreeMapB[mmdt_JetEta[k]]->GetName(),mmdt_JetEta[k].Data(),
            TreeMapB[mmdt_JetPhi[k]]->GetName(),mmdt_JetPhi[k].Data(),
            TreeMapB[mmdt_JetPhi[k]]->GetName(),mmdt_JetPhi[k].Data()
            , DRCut);
            Cut+=TString::Format("&&%s", CutOver.Data() );
            CutSub+=TString::Format("&&%s", CutOver.Data() );
            CutExtraJets = TString::Format("(@%s.size()<=2)", mmdt_JetAng[k].Data() );
            Cut+=TString::Format("&&%s", CutExtraJets.Data() );
            CutSub+=TString::Format("&&%s", CutExtraJets.Data() );
            if ((i==1)&&(j==6)){
                CutNorm = TString::Format("(%s.%s >= 0.)&&(%s.%s < 200.)&&(TMath::Abs(%s.%s)  >= 0)&&(TMath::Abs(%s.%s) < 2.5)", 
                                    TreeMapB[mmdt_JetPt[k]]->GetName(),  mmdt_JetPt[k].Data(),
                                    TreeMapB[mmdt_JetPt[k]]->GetName(),  mmdt_JetPt[k].Data(), 
                                    TreeMapB[mmdt_JetEta[k]]->GetName(), mmdt_JetEta[k].Data(), 
                                    TreeMapB[mmdt_JetEta[k]]->GetName(), mmdt_JetEta[k].Data()
                                    );
                CutNorm+=TString::Format("&&%s", CutOver.Data() );
                CutNorm+=TString::Format("&&%s", CutExtraJets.Data() );

            }
            if (mmdt_JetAng[k].Contains("MultLam")){
                TreeMapB[mmdt_JetAng[k]]          ->Draw(TString::Format("%s[0] >> hB_%s_%i_%i_%i(50,0,100)", mmdt_JetAng[k].Data() , mmdt_JetAng[k].Data(), i,j,k), Cut.Data() , "goff"); 
                TreeMapB[mmdt_JetAng[k]]          ->Draw(TString::Format("%s[1] >> hB_sub_%s_%i_%i_%i(50,0,100)", mmdt_JetAng[k].Data() , mmdt_JetAng[k].Data(), i,j,k), CutSub.Data() , "goff"); 
                if ((i==1)&&(j==6)){
                    TreeMapB[mmdt_JetAng[k]]->Draw(TString::Format("%s >> hB_no_cut_%s(50,0,100)", mmdt_JetAng[k].Data() , mmdt_JetAng[k].Data()), CutNorm.Data() , "goff"); 
                    TreeMapB[mmdt_JetAng[k]]->Draw(TString::Format("%s >> h_ptB_mmdt(500,0,500)", Cut_ptB_mmdt.Data()), CutNorm.Data(), "goff" );
                    }
            }else{
                TreeMapB[mmdt_JetAng[k]]          ->Draw(TString::Format("%s[0] >> hB_%s_%i_%i_%i(50,0,1)", mmdt_JetAng[k].Data() , mmdt_JetAng[k].Data(), i,j,k), Cut.Data() , "goff"); 
                TreeMapB[mmdt_JetAng[k]]          ->Draw(TString::Format("%s[1] >> hB_sub_%s_%i_%i_%i(50,0,1)", mmdt_JetAng[k].Data() , mmdt_JetAng[k].Data(), i,j,k), CutSub.Data() , "goff"); 
                if ((i==1)&&(j==6)){
                    TreeMapB[mmdt_JetAng[k]]->Draw(TString::Format("%s >> hB_no_cut_%s(50,0,1)", mmdt_JetAng[k].Data() , mmdt_JetAng[k].Data()), CutNorm.Data() , "goff"); 
                    TreeMapB[mmdt_JetAng[k]]->Draw(TString::Format("%s >> h_ptB_mmdt(500,0,500)", Cut_ptB_mmdt.Data()), CutNorm.Data(), "goff" );
                }
            }
            h = (TH1D*)gDirectory->Get(TString::Format("hB_%s_%i_%i_%i", mmdt_JetAng[k].Data(), i,j,k));
            h_sub = (TH1D*)gDirectory->Get(TString::Format("hB_sub_%s_%i_%i_%i", mmdt_JetAng[k].Data(), i,j,k));
            if ((i==1)&&(j==6)) {
                h_no_cutB_mmdt =(TH1D*)gDirectory->Get(TString::Format("hB_no_cut_%s", mmdt_JetAng[k].Data()));
                NormFact4 = h_no_cutB_mmdt->GetEntries();
                h_no_cutB_mmdt->Scale(1./h_no_cutB_mmdt->GetEntries());
                h_ptB_mmdt = (TH1D*)gDirectory->Get("h_ptB_mmdt");
                fracB_no_cut_mmdt = fracB->ProjectionX()->GetBinContent(fracB->ProjectionX()->GetXaxis()->FindBin( h_ptB_mmdt->GetMean() ) ) / 10.;
                cout << "Pt Mean B mmdt = " << h_ptB_mmdt->GetMean() << endl;
            }
            h->Add(h_sub);
            //h->Scale(1./NormFact4);
            //if (h->GetEntries()>0) h->Scale(1./h->GetEntries());
            h2= (TH1D*)h->Clone(TString::Format("%s_clone", h->GetName()));
            if ((ScaleA-ScaleB)!=0) {h->Scale((ScaleA)/(ScaleA-ScaleB));}else{
                h->Scale(0.);
            };
            h_MapB_Quark[mmdt_JetAng[k].Data()].push_back(h);
            if ((ScaleA-ScaleB)!=0) {h2->Scale(-1.*(1-ScaleA)/(ScaleA-ScaleB));}else{
                h2->Scale(0.);
            };
            h_MapB_Gluon[mmdt_JetAng[k].Data()].push_back(h2);
            cout << i << " " << j << " " << k << "/" << JetAng.size() << endl;
            //no cut ang
                if ((i==1)&&(j==6)){
                    h_no_cutA_clone = (TH1D*)h_no_cutA->Clone(TString::Format("clone_%s", h_no_cutA->GetName()));
                    h_no_cutA_mmdt_clone = (TH1D*)h_no_cutA_mmdt->Clone(TString::Format("clone_%s", h_no_cutA_mmdt->GetName()));
                    h_no_cutB_clone = (TH1D*)h_no_cutB->Clone(TString::Format("clone_%s", h_no_cutB->GetName()));
                    h_no_cutB_mmdt_clone = (TH1D*)h_no_cutB_mmdt->Clone(TString::Format("clone_%s", h_no_cutB_mmdt->GetName()));
                    h_no_cutA_clone->Scale(-1.*fracB_no_cut);
                    h_no_cutA_mmdt_clone->Scale(-1.*fracB_no_cut_mmdt);
                    h_no_cutB_clone->Scale(fracA_no_cut);
                    h_no_cutB_mmdt_clone->Scale(fracA_no_cut_mmdt);

                    h_no_cutA_clone->Add(h_no_cutB_clone);
                    h_no_cutA_mmdt_clone->Add(h_no_cutB_mmdt_clone);

                    h_no_cutA_clone->Scale(fracA_no_cut-fracB_no_cut);
                    h_no_cutA_mmdt_clone->Scale(fracA_no_cut_mmdt-fracB_no_cut_mmdt);

                    h_no_cutA_clone->SetName( TString::Format("quark_%s", h_no_cutA_clone->GetName()));
                    h_no_cutA_mmdt_clone->SetName(TString::Format("quark_%s",h_no_cutA_mmdt_clone->GetName()));

                    nocuts.push_back(h_no_cutA_clone);
                    nocuts.push_back(h_no_cutA_mmdt_clone);

                    //
                    h_no_cutA->Scale(1.-fracB_no_cut);
                    h_no_cutA_mmdt->Scale(1.-fracB_no_cut_mmdt);
                    h_no_cutB->Scale(-1.*(1.-fracA_no_cut));
                    h_no_cutB_mmdt->Scale(-1.*(1.-fracA_no_cut_mmdt));

                    h_no_cutA->Add(h_no_cutB);
                    h_no_cutA_mmdt->Add(h_no_cutB_mmdt);

                    h_no_cutA->Scale(fracA_no_cut-fracB_no_cut);
                    h_no_cutA_mmdt->Scale(fracA_no_cut_mmdt-fracB_no_cut_mmdt);

                    h_no_cutA->SetName(TString::Format("gluon_%s",h_no_cutA->GetName()));
                    h_no_cutA_mmdt->SetName(TString::Format("gluon_%s",h_no_cutA_mmdt->GetName()));

                    nocuts.push_back(h_no_cutA);
                    nocuts.push_back(h_no_cutA_mmdt);



                }

            }

        }
    }

   TFile * output;
   if (Pythia){
       output = new TFile(TString::Format("qg_angs_%s_%s_pythia.root", EnergyA.Data(), EnergyB.Data() ), "recreate" );
   }else{
       output = new TFile(TString::Format("qg_angs_%s_%s.root", EnergyA.Data(), EnergyB.Data() ), "recreate" );
   }

   output->cd();

    
    THStack *hs_g;
    THStack *hs_q;
    THStack *hs_g_mmdt;
    THStack *hs_q_mmdt;
    THStack *diff_hs_g;
    THStack *diff_hs_q;
    THStack *diff_hs_g_mmdt;
    THStack *diff_hs_q_mmdt;
    TH1F * h_g;
    TH1F * h_q;
    TH1F * h_g_mmdt;
    TH1F * h_q_mmdt;

    TH1F * temp1;
    TH1F * temp2;
    TH1F * temp3;
    TH1F * temp4;
    for (int i = 0; i<JetAng.size(); i++){
    //for (int i = 4; i<5; i++){
        hs_g = new THStack(TString::Format("Final_gluon_%s", JetAng[i].Data() ),TString::Format("Final_gluon_%s", JetAng[i].Data() ));
        hs_q = new THStack(TString::Format("Final_quark_%s", JetAng[i].Data() ),TString::Format("Final_quark_%s", JetAng[i].Data() ));
        hs_g_mmdt = new THStack(TString::Format("Final_gluon_mmdt_%s", mmdt_JetAng[i].Data() ),TString::Format("Final_gluon_mmdt_%s", mmdt_JetAng[i].Data() ));
        hs_q_mmdt = new THStack(TString::Format("Final_quark_mmdt_%s", mmdt_JetAng[i].Data() ),TString::Format("Final_quark_mmdt_%s", mmdt_JetAng[i].Data() ));
    
        diff_hs_g = new THStack(TString::Format("Final_diff_gluon_%s", JetAng[i].Data() ),TString::Format("Final_gluon_%s", JetAng[i].Data() ));
        diff_hs_q = new THStack(TString::Format("Final_diff_quark_%s", JetAng[i].Data() ),TString::Format("Final_quark_%s", JetAng[i].Data() ));
        diff_hs_g_mmdt = new THStack(TString::Format("Final_diff_gluon_mmdt_%s", mmdt_JetAng[i].Data() ),TString::Format("Final_gluon_mmdt_%s", mmdt_JetAng[i].Data() ));
        diff_hs_q_mmdt = new THStack(TString::Format("Final_diff_quark_mmdt_%s", mmdt_JetAng[i].Data() ),TString::Format("Final_quark_mmdt_%s", mmdt_JetAng[i].Data() ));

        h_g =(TH1F*)h_MapA_Quark[JetAng[i]][0]->Clone();
        h_g ->SetName(TString::Format("gluon_%s", JetAng[i].Data() ));
        h_g ->SetTitle(TString::Format("gluon_%s", JetAng[i].Data() ));
        h_g->Reset();
        h_q =(TH1F*)h_MapA_Quark[JetAng[i]][0]->Clone();
        h_q ->SetName(TString::Format("quark_%s", JetAng[i].Data() ));
        h_q ->SetTitle(TString::Format("quark_%s", JetAng[i].Data() ));
        h_q->Reset();
        h_g_mmdt=(TH1F*)h_MapA_Quark[JetAng[i]][0]->Clone();
        h_g_mmdt ->SetName(TString::Format("gluon_mmdt_%s", mmdt_JetAng[i].Data() ));
        h_g_mmdt ->SetTitle(TString::Format("gluon_mmdt_%s", mmdt_JetAng[i].Data() ));
        h_g_mmdt->Reset();
        h_q_mmdt=(TH1F*)h_MapA_Quark[JetAng[i]][0]->Clone();
        h_q_mmdt ->SetName(TString::Format("quark_mmdt_%s", mmdt_JetAng[i].Data() ));
        h_q_mmdt ->SetTitle(TString::Format("quark_mmdt_%s", mmdt_JetAng[i].Data() ));
        h_q_mmdt->Reset();
        
        
        
        
        for (int j = 0; j<h_MapA_Quark[JetAng[i]].size(); j++){

            hs_q->Add(h_MapA_Quark[JetAng[i]][j]);
            hs_g->Add(h_MapA_Gluon[JetAng[i]][j]);
            hs_q->Add(h_MapB_Quark[JetAng[i]][j]);
            hs_g->Add(h_MapB_Gluon[JetAng[i]][j]);
            hs_q_mmdt->Add(h_MapA_Quark[mmdt_JetAng[i]][j]);
            hs_g_mmdt->Add(h_MapA_Gluon[mmdt_JetAng[i]][j]);
            hs_q_mmdt->Add(h_MapB_Quark[mmdt_JetAng[i]][j]);
            hs_g_mmdt->Add(h_MapB_Gluon[mmdt_JetAng[i]][j]);

            h_q->Add(h_MapA_Quark[JetAng[i]][j]);
            h_g->Add(h_MapA_Gluon[JetAng[i]][j]);
            h_q->Add(h_MapB_Quark[JetAng[i]][j]);
            h_g->Add(h_MapB_Gluon[JetAng[i]][j]);
            h_q_mmdt->Add(h_MapA_Quark[mmdt_JetAng[i]][j]);
            h_g_mmdt->Add(h_MapA_Gluon[mmdt_JetAng[i]][j]);
            h_q_mmdt->Add(h_MapB_Quark[mmdt_JetAng[i]][j]);
            h_g_mmdt->Add(h_MapB_Gluon[mmdt_JetAng[i]][j]);

            temp1 = (TH1F*)h_MapA_Quark[JetAng[i]][j]->Clone(TString::Format("cclone_%s", h_MapA_Quark[JetAng[i]][j]->GetName()));
            temp1->Add(h_MapB_Quark[JetAng[i]][j]);
            temp2 = (TH1F*)h_MapA_Gluon[JetAng[i]][j]->Clone(TString::Format("cclone_%s", h_MapA_Gluon[JetAng[i]][j]->GetName()));
            temp2->Add(h_MapB_Gluon[JetAng[i]][j]);
            temp3 = (TH1F*)h_MapA_Quark[mmdt_JetAng[i]][j]->Clone(TString::Format("cclone_%s", h_MapA_Quark[mmdt_JetAng[i]][j]->GetName()));
            temp3->Add(h_MapB_Quark[mmdt_JetAng[i]][j]);
            temp4 = (TH1F*)h_MapA_Gluon[mmdt_JetAng[i]][j]->Clone(TString::Format("cclone_%s", h_MapA_Gluon[mmdt_JetAng[i]][j]->GetName()));
            temp4->Add(h_MapB_Gluon[mmdt_JetAng[i]][j]);

            diff_hs_q->Add(temp1);
            diff_hs_g->Add(temp2);
            diff_hs_q_mmdt->Add(temp3);
            diff_hs_g_mmdt->Add(temp4);

            temp1->SetDirectory(nullptr);
            temp2->SetDirectory(nullptr);
            temp3->SetDirectory(nullptr);
            temp4->SetDirectory(nullptr);
        }
        hs_g->Write();
        hs_q->Write();
        hs_g_mmdt->Write();
        hs_q_mmdt->Write();

        diff_hs_g->Write();
        diff_hs_q->Write();
        diff_hs_g_mmdt->Write();
        diff_hs_q_mmdt->Write();
    }

    fracA->Write();
    fracB->Write();

    for (int i =0; i< nocuts.size(); i++){
        nocuts[i]->Write();
    }

    output->Write();
    output->Close();


    return 0;
}
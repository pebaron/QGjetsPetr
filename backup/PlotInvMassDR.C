//#include "./src/analysis/LorVector.h"

void ClearMap(std::map<TString, vector<double>> &mymap){
        auto it = mymap.begin();
        for(int k = 0; k < mymap.size(); k++){
        it->second.clear();
        it++;
        }
}

double ComputeInvariantMass(double pt1, double eta1, double phi1, double mass1, double pt2, double eta2, double phi2, double mass2) {
    const ROOT::Math::PtEtaPhiMVector p1(pt1, eta1, phi1, mass1);
    const ROOT::Math::PtEtaPhiMVector p2(pt2, eta2, phi2, mass2);
    return (p1 + p2).M();
}

//ML->Draw("ComputeInvariantMass(Large_jets[0].Pt(), Large_jets[0].Eta(), Large_jets[0].Phi(), Large_jets[0].M(),Large_jets[1].Pt(), Large_jets[1].Eta(), Large_jets[1].Phi(), Large_jets[1].M())", "", "hist")
//ML->Draw("ComputeInvariantMass(Large_jets[0].Pt(), Large_jets[0].Eta(), Large_jets[0].Phi(), Large_jets[0].M(),Large_jets[1].Pt(), Large_jets[1].Eta(), Large_jets[1].Phi(), Large_jets[1].M())", "(Large_jets[0].IsPtcl() && Large_jets[1].IsPtcl())", "hist")


int PlotInvMassDR(){
//    gSystem->Load("./install/lib/libGacrMLCore.so");
//    gSystem->Load("./install/lib/libGacrMLClassifier.so");
////gSystem->Load("./install/lib/libGacrMLCore.so");
////gSystem->Load("./install/lib/libGacrMLClassifier.so");
////gSystem->Load("./install/lib/libGacrMLAnalysis.so");
//    gSystem->Load("./install/lib/libGacrMLAnalysis.rootmap");
//    gSystem->Load("./install/lib/libGacrMLAnalysis_rdict.pcm");
//    gSystem->Load("./install/lib/libGacrMLAnalysis.so");

    TString FileName0="./build/analyzed_histos_merged_tag_1_delphes_low_pp2_4top_hadr_decay_tttt_SM_merged.root";
    TString FileName1="./build/analyzed_histos_merged_tag_1_delphes_low_pp2_4top_hadr_decay_tttt_Y0_1500_merged.root";
    TString FileName=FileName0.Data();
    TString FileName11=FileName1.Data();
    TFile * rfile = new TFile(FileName.Data(), "read");
    TFile * rfiley0 = new TFile(FileName11.Data(), "read");
    TTree * ML = (TTree*)rfile->Get("ML");
    TTree * MLy0 = (TTree*)rfiley0->Get("ML");
    
    vector<LorVector*> *lor;
    ML->SetBranchAddress("Large_jets", &lor);
    vector<LorVector*> *lor2;
    MLy0->SetBranchAddress("Large_jets", &lor2);
    int NDetLjets;
    JetInfo *cml;
    ML->SetBranchAddress("Info_det", &cml);
    int NDetLjetsy0;
    JetInfo *cy0;
    MLy0->SetBranchAddress("Info_det", &cy0);
    TString outname = "DRInvMass"
    TFile * out = new TFile(TString::Format("%s.root", outname.Data() ), "recreate");
    out->cd();
    TTree * tree = new TTree("tree", "tree");
    TH1D * inv_mass_SM       = new TH1D("inv_mass_SM", "inv_mass_SM", 100, 0, 4000.);
    TH1D * inv_mass_Y0       = new TH1D("inv_mass_Y0", "inv_mass_Y0", 100, 0, 4000.);
    TH1D * inv_mass_SM_stand = new TH1D("inv_mass_SM_stand", "inv_mass_SM_stand", 100, 0, 4000.);
    TH1D * inv_mass_Y0_stand = new TH1D("inv_mass_Y0_stand", "inv_mass_Y0_stand", 100, 0, 4000.);

    TH1D * ptcl_inv_mass_SM       = new TH1D("ptcl_inv_mass_SM", "ptcl_inv_mass_SM", 100, 0, 4000.);
    TH1D * ptcl_inv_mass_Y0       = new TH1D("ptcl_inv_mass_Y0", "ptcl_inv_mass_Y0", 100, 0, 4000.);
    TH1D * ptcl_inv_mass_SM_stand = new TH1D("ptcl_inv_mass_SM_stand", "ptcl_inv_mass_SM_stand", 100, 0, 4000.);
    TH1D * ptcl_inv_mass_Y0_stand = new TH1D("ptcl_inv_mass_Y0_stand", "ptcl_inv_mass_Y0_stand", 100, 0, 4000.);

    
    std::map<TString, TH1D*>  map_inv_mass_SM      ;
    std::map<TString, TH1D*>  map_inv_mass_Y0      ;
    std::map<TString, TH1D*>  map_inv_mass_SM_stand;
    std::map<TString, TH1D*>  map_inv_mass_Y0_stand;

    std::map<TString, TH1D*>  map_ptcl_inv_mass_SM      ;
    std::map<TString, TH1D*>  map_ptcl_inv_mass_Y0      ;
    std::map<TString, TH1D*>  map_ptcl_inv_mass_SM_stand;
    std::map<TString, TH1D*>  map_ptcl_inv_mass_Y0_stand;

    std::map<TString, vector<double>>  tree_map_inv_mass_SM      ;
    std::map<TString, vector<double>>  tree_map_inv_mass_Y0      ;
    std::map<TString, vector<double>>  tree_map_inv_mass_SM_stand;
    std::map<TString, vector<double>>  tree_map_inv_mass_Y0_stand;

    std::map<TString, vector<double>>  tree_map_ptcl_inv_mass_SM      ;
    std::map<TString, vector<double>>  tree_map_ptcl_inv_mass_Y0      ;
    std::map<TString, vector<double>>  tree_map_ptcl_inv_mass_SM_stand;
    std::map<TString, vector<double>>  tree_map_ptcl_inv_mass_Y0_stand;

    std::map<TString, vector<double>>  tree_map_DR_SM      ;
    std::map<TString, vector<double>>  tree_map_DR_Y0      ;
    std::map<TString, vector<double>>  tree_map_DR_SM_stand;
    std::map<TString, vector<double>>  tree_map_DR_Y0_stand;

    std::map<TString, vector<double>>  tree_map_ptcl_DR_SM      ;
    std::map<TString, vector<double>>  tree_map_ptcl_DR_Y0      ;
    std::map<TString, vector<double>>  tree_map_ptcl_DR_SM_stand;
    std::map<TString, vector<double>>  tree_map_ptcl_DR_Y0_stand;

    //tree_map_DR_SM
    //tree_map_DR_SM_stand
    //tree_map_ptcl_DR_SM
    //tree_map_ptcl_DR_SM_stand

    cout << ML->GetEntries() << endl;
    cout << MLy0->GetEntries() << endl;
    TString TempName;
    TString TempName1;
    TString TempName2;
    TString TempName3;
    TString TempName4;
    TString TempName1b;
    TString TempName2b;
    TString TempName3b;
    TString TempName4b;

    TString SomeName;
    
    double tempmass;

    bool Filling1 = false;
    bool Filling2 = false;
    bool Filling3 = false;
    bool Filling4 = false;

    for (int i = 0; i<ML->GetEntries();i++){
        ML->GetEntry(i);
        NDetLjets = cml->GetLargeJets();
        if (i % 1000 == 0){
            cout << "So far done " << 100*i/ML->GetEntries() << "\%" << endl;
        }
        
        if (lor->size() < 2) continue;
        if (lor->size() == 0) continue;
        for (int j = 0; j<lor->size();j++){
            for (int k = 0; k<lor->size();k++){
                if (j>k) {
                    if (lor[0].at(j)->IsDet() && lor[0].at(k)->IsDet() ){
                        if (lor[0].at(j)->mlToptag() && lor[0].at(k)->mlToptag()){
                        TempName = TString::Format("%s_%i_%i", inv_mass_SM->GetName(), j,k);
                        TempName1 = TString::Format("InvMass_%s",TempName.Data());
                        TempName1b = TString::Format("DR_%s",TempName.Data());
                        if (!map_inv_mass_SM[TempName.Data()]){
                        map_inv_mass_SM[TempName.Data()] = new TH1D(TempName.Data(), TempName.Data(), 100, 0, 4000);
                        tree->Branch(TempName1.Data(), &tree_map_inv_mass_SM[TempName1.Data()]);
                        tree->Branch(TempName1b.Data(), &tree_map_DR_SM[TempName1b.Data()]);
                        }
                        tempmass = ComputeInvariantMass(
                            lor[0].at(j)->Pt(), lor[0].at(j)->Eta(), lor[0].at(j)->Phi(), lor[0].at(j)->M(),
                            lor[0].at(k)->Pt(), lor[0].at(k)->Eta(), lor[0].at(k)->Phi(), lor[0].at(k)->M());
                        map_inv_mass_SM[TempName.Data()]->Fill( tempmass );
                        inv_mass_SM->Fill( tempmass );
                        tree_map_inv_mass_SM[TempName1.Data()].push_back( tempmass );
                        tree_map_DR_SM[TempName1b.Data()].push_back( lor[0].at(j)->DeltaR(lor[0].at(k)->GetTLorentzVector()) );
                        Filling1 = true;
                        }
                        if (lor[0].at(j)->Toptag() && lor[0].at(k)->Toptag()){
                        TempName = TString::Format("%s_%i_%i", inv_mass_SM_stand->GetName(), j,k);
                        TempName2 = TString::Format("InvMass_%s",TempName.Data());
                        TempName2b = TString::Format("DR_%s",TempName.Data());
                        if (!map_inv_mass_SM_stand[TempName.Data()]){
                        map_inv_mass_SM_stand[TempName.Data()] = new TH1D(TempName.Data(), TempName.Data(), 100, 0, 4000);
                        tree->Branch( TempName2.Data(), &tree_map_inv_mass_SM_stand[TempName2.Data()]);
                        tree->Branch( TempName2b.Data(), &tree_map_DR_SM_stand[TempName2b.Data()]);
                        }
                        tempmass = ComputeInvariantMass(
                            lor[0].at(j)->Pt(), lor[0].at(j)->Eta(), lor[0].at(j)->Phi(), lor[0].at(j)->M(),
                            lor[0].at(k)->Pt(), lor[0].at(k)->Eta(), lor[0].at(k)->Phi(), lor[0].at(k)->M()) ;
                        map_inv_mass_SM_stand[TempName.Data()]->Fill( tempmass );
                        inv_mass_SM_stand->Fill( tempmass );
                        tree_map_inv_mass_SM_stand[TempName2.Data()].push_back( tempmass );
                        tree_map_DR_SM_stand[TempName2b.Data()].push_back( lor[0].at(j)->DeltaR(lor[0].at(k)->GetTLorentzVector()) );
                        Filling2 = true;
                        }
                    }//here I ended last time
                    if (lor[0].at(j)->IsPtcl() && lor[0].at(k)->IsPtcl() && (j >= NDetLjets) && (k >= NDetLjets)  ){
                        if (lor[0].at(j)->mlToptag() && lor[0].at(k)->mlToptag()){
                            TempName = TString::Format("%s_%i_%i", ptcl_inv_mass_SM->GetName(), j-NDetLjets,k-NDetLjets);
                            TempName3 = TString::Format("InvMass_%s",TempName.Data());
                            TempName3b = TString::Format("DR_%s",TempName.Data());
                            if (!map_ptcl_inv_mass_SM[TempName.Data()]){
                                map_ptcl_inv_mass_SM[TempName.Data()] = new TH1D(TempName.Data(), TempName.Data(), 100, 0, 4000);
                                tree->Branch(TempName3.Data(), &tree_map_ptcl_inv_mass_SM[TempName3.Data()]);
                                tree->Branch(TempName3b.Data(), &tree_map_ptcl_DR_SM[TempName3b.Data()]);
                            }
                            tempmass = ComputeInvariantMass(
                            lor[0].at(j)->Pt(), lor[0].at(j)->Eta(), lor[0].at(j)->Phi(), lor[0].at(j)->M(),
                            lor[0].at(k)->Pt(), lor[0].at(k)->Eta(), lor[0].at(k)->Phi(), lor[0].at(k)->M()) ;
                            map_ptcl_inv_mass_SM[TempName.Data()]->Fill( tempmass );
                            ptcl_inv_mass_SM->Fill( tempmass );
                            tree_map_ptcl_inv_mass_SM[TempName3.Data()].push_back( tempmass );
                            tree_map_ptcl_DR_SM[TempName3b.Data()].push_back( lor[0].at(j)->DeltaR(lor[0].at(k)->GetTLorentzVector()) );
                            Filling3 = true;
                        }
                        if (lor[0].at(j)->Toptag() && lor[0].at(k)->Toptag()){
                            TempName = TString::Format("%s_%i_%i", ptcl_inv_mass_SM_stand->GetName(), j-NDetLjets,k-NDetLjets);
                            TempName4 = TString::Format("InvMass_%s",TempName.Data());
                            TempName4b = TString::Format("DR_%s",TempName.Data());
                            if (!map_ptcl_inv_mass_SM_stand[TempName.Data()]){
                                map_ptcl_inv_mass_SM_stand[TempName.Data()] = new TH1D(TempName.Data(), TempName.Data(), 100, 0, 4000);
                                tree->Branch(TempName4.Data(), &tree_map_ptcl_inv_mass_SM_stand[TempName4.Data()]);
                                tree->Branch(TempName4b.Data(), &tree_map_ptcl_DR_SM_stand[TempName4b.Data()]);
                            } 
                            tempmass = ComputeInvariantMass(
                            lor[0].at(j)->Pt(), lor[0].at(j)->Eta(), lor[0].at(j)->Phi(), lor[0].at(j)->M(),
                            lor[0].at(k)->Pt(), lor[0].at(k)->Eta(), lor[0].at(k)->Phi(), lor[0].at(k)->M()) ;
                            map_ptcl_inv_mass_SM_stand[TempName.Data()]->Fill( tempmass);
                            ptcl_inv_mass_SM_stand->Fill( tempmass );
                            tree_map_ptcl_inv_mass_SM_stand[TempName4.Data()].push_back( tempmass );
                            tree_map_ptcl_DR_SM_stand[TempName4b.Data()].push_back( lor[0].at(j)->DeltaR(lor[0].at(k)->GetTLorentzVector()) );
                            Filling4 = true;
                        }
                    }
                }
            }
        }
    if (Filling1 || Filling2 || Filling3 || Filling4){tree->Fill();}
    Filling1 = false;
    Filling2 = false;
    Filling3 = false;
    Filling4 = false;
    ClearMap(tree_map_DR_SM);
    ClearMap(tree_map_DR_SM_stand);
    ClearMap(tree_map_ptcl_DR_SM);
    ClearMap(tree_map_ptcl_DR_SM_stand);
    ClearMap(tree_map_DR_SM);
    ClearMap(tree_map_DR_SM_stand);
    ClearMap(tree_map_ptcl_DR_SM);
    ClearMap(tree_map_ptcl_DR_SM_stand);
    
    ClearMap(tree_map_inv_mass_SM);
    ClearMap(tree_map_inv_mass_SM_stand);
    ClearMap(tree_map_ptcl_inv_mass_SM);
    ClearMap(tree_map_ptcl_inv_mass_SM_stand);
    ClearMap(tree_map_inv_mass_SM);
    ClearMap(tree_map_inv_mass_SM_stand);
    ClearMap(tree_map_ptcl_inv_mass_SM);
    ClearMap(tree_map_ptcl_inv_mass_SM_stand);
    }

    for (int i = 0; i<MLy0->GetEntries();i++){
        MLy0->GetEntry(i);
        NDetLjetsy0 = cy0->GetLargeJets();
        if (i % 1000 == 0){
            cout << "So far done " << 100*i/MLy0->GetEntries() << "\%" << endl;
        }
        if (lor2->size() < 2) continue;
        if (lor2->size() == 0) continue;
        for (int j = 0; j<lor2->size();j++){
            for (int k = 0; k<lor2->size();k++){
                if (j>k) {
                    if (lor2[0].at(j)->IsDet() && lor2[0].at(k)->IsDet() ){
                        if (lor2[0].at(j)->mlToptag() && lor2[0].at(k)->mlToptag())    {
                            TempName = TString::Format("%s_%i_%i", inv_mass_Y0->GetName(), j,k);
                            TempName1 = TString::Format("InvMass_%s",TempName.Data());
                            TempName1b = TString::Format("DR_%s",TempName.Data());
                            if (!map_inv_mass_Y0[TempName.Data()]){
                                map_inv_mass_Y0[TempName.Data()] = new TH1D(TempName.Data(), TempName.Data(), 100, 0, 4000);
                                tree->Branch(TempName1.Data(), &tree_map_inv_mass_Y0[TempName1.Data()]);
                                tree->Branch(TempName1b.Data(), &tree_map_DR_Y0[TempName1b.Data()]);
                            }
                            tempmass = ComputeInvariantMass(
                            lor2[0].at(j)->Pt(), lor2[0].at(j)->Eta(), lor2[0].at(j)->Phi(), lor2[0].at(j)->M(),
                            lor2[0].at(k)->Pt(), lor2[0].at(k)->Eta(), lor2[0].at(k)->Phi(), lor2[0].at(k)->M()) ;
                            map_inv_mass_Y0[TempName.Data()]->Fill( tempmass );
                            inv_mass_Y0->Fill( tempmass );
                            tree_map_inv_mass_Y0[TempName1.Data()].push_back( tempmass );
                            tree_map_DR_Y0[TempName1b.Data()].push_back( lor2[0].at(j)->DeltaR(lor2[0].at(k)->GetTLorentzVector()) );
                            Filling1 = true;
                        }
                        if (lor2[0].at(j)->Toptag() && lor2[0].at(k)->Toptag())    {
                            TempName = TString::Format("%s_%i_%i", inv_mass_Y0_stand->GetName(), j,k);
                            TempName2 = TString::Format("InvMass_%s",TempName.Data());
                            TempName2b = TString::Format("DR_%s",TempName.Data());
                            if (!map_inv_mass_Y0_stand[TempName.Data()]){
                                map_inv_mass_Y0_stand[TempName.Data()] = new TH1D(TempName.Data(), TempName.Data(), 100, 0, 4000);
                                tree->Branch(TempName2b.Data(), &tree_map_DR_Y0_stand[TempName2b.Data()]);
                            }
                            tempmass = ComputeInvariantMass(
                            lor2[0].at(j)->Pt(), lor2[0].at(j)->Eta(), lor2[0].at(j)->Phi(), lor2[0].at(j)->M(),
                            lor2[0].at(k)->Pt(), lor2[0].at(k)->Eta(), lor2[0].at(k)->Phi(), lor2[0].at(k)->M()) ;
                            map_inv_mass_Y0_stand[TempName.Data()]->Fill( tempmass );
                            inv_mass_Y0_stand->Fill( tempmass );
                            tree_map_inv_mass_Y0_stand[TempName2.Data()].push_back( tempmass );
                            tree_map_DR_Y0_stand[TempName2b.Data()].push_back( lor2[0].at(j)->DeltaR(lor2[0].at(k)->GetTLorentzVector()) );
                            Filling2 = true;
                        }
                    }
                    if (lor2[0].at(j)->IsPtcl() && lor2[0].at(k)->IsPtcl() && (j >= NDetLjetsy0) && (k >= NDetLjetsy0)  ){
                        if (lor2[0].at(j)->mlToptag() && lor2[0].at(k)->mlToptag())    {
                            TempName = TString::Format("%s_%i_%i", ptcl_inv_mass_Y0->GetName(), j-NDetLjetsy0,k-NDetLjetsy0);
                            TempName3 = TString::Format("InvMass_%s",TempName.Data());
                            TempName3b = TString::Format("DR_%s",TempName.Data());
                            if (!map_ptcl_inv_mass_Y0[TempName.Data()]){
                                map_ptcl_inv_mass_Y0[TempName.Data()] = new TH1D(TempName.Data(), TempName.Data(), 100, 0, 4000);
                                tree->Branch(TempName3.Data(), &tree_map_ptcl_inv_mass_Y0[TempName3.Data()]);
                                tree->Branch(TempName3b.Data(), &tree_map_ptcl_DR_Y0[TempName3b.Data()]);
                            }
                            tempmass = ComputeInvariantMass(
                            lor2[0].at(j)->Pt(), lor2[0].at(j)->Eta(), lor2[0].at(j)->Phi(), lor2[0].at(j)->M(),
                            lor2[0].at(k)->Pt(), lor2[0].at(k)->Eta(), lor2[0].at(k)->Phi(), lor2[0].at(k)->M()) ;
                            map_ptcl_inv_mass_Y0[TempName.Data()]->Fill( tempmass );
                            ptcl_inv_mass_Y0->Fill( tempmass );
                            tree_map_ptcl_inv_mass_Y0[TempName3.Data()].push_back( tempmass );
                            tree_map_ptcl_DR_Y0[TempName3b.Data()].push_back( lor2[0].at(j)->DeltaR(lor2[0].at(k)->GetTLorentzVector()) );
                            Filling3 = true;
                        }
                        if (lor2[0].at(j)->Toptag() && lor2[0].at(k)->Toptag())    {
                            TempName = TString::Format("%s_%i_%i", ptcl_inv_mass_Y0_stand->GetName(), j-NDetLjetsy0,k-NDetLjetsy0);
                            TempName4 = TString::Format("InvMass_%s",TempName.Data());
                            TempName4b = TString::Format("DR_%s",TempName.Data());
                            if (!map_ptcl_inv_mass_Y0_stand[TempName.Data()]){
                                map_ptcl_inv_mass_Y0_stand[TempName.Data()] = new TH1D(TempName.Data(), TempName.Data(), 100, 0, 4000);
                                tree->Branch(TempName4.Data(), &tree_map_ptcl_inv_mass_Y0_stand[TempName4.Data()]);
                                tree->Branch(TempName4b.Data(), &tree_map_ptcl_DR_Y0_stand[TempName4b.Data()]);
                            }
                            tempmass = ComputeInvariantMass(
                            lor2[0].at(j)->Pt(), lor2[0].at(j)->Eta(), lor2[0].at(j)->Phi(), lor2[0].at(j)->M(),
                            lor2[0].at(k)->Pt(), lor2[0].at(k)->Eta(), lor2[0].at(k)->Phi(), lor2[0].at(k)->M());
                            map_ptcl_inv_mass_Y0_stand[TempName.Data()]->Fill( tempmass );
                            ptcl_inv_mass_Y0_stand->Fill( tempmass );
                            tree_map_ptcl_inv_mass_Y0_stand[TempName4.Data()].push_back( tempmass );
                            tree_map_ptcl_DR_Y0_stand[TempName4b.Data()].push_back( lor2[0].at(j)->DeltaR(lor2[0].at(k)->GetTLorentzVector()) );
                            Filling4 = true;
                        }
                    }
                }
            }
        }
        if (Filling1 || Filling2 || Filling3 || Filling4){tree->Fill();}
        Filling1 = false;
        Filling2 = false;
        Filling3 = false;
        Filling4 = false;
        

        ClearMap(tree_map_DR_Y0);
        ClearMap(tree_map_DR_Y0_stand);
        ClearMap(tree_map_ptcl_DR_Y0);
        ClearMap(tree_map_ptcl_DR_Y0_stand);
        ClearMap(tree_map_DR_Y0);
        ClearMap(tree_map_DR_Y0_stand);
        ClearMap(tree_map_ptcl_DR_Y0);
        ClearMap(tree_map_ptcl_DR_Y0_stand);

        ClearMap(tree_map_inv_mass_Y0);
        ClearMap(tree_map_inv_mass_Y0_stand);
        ClearMap(tree_map_ptcl_inv_mass_Y0);
        ClearMap(tree_map_ptcl_inv_mass_Y0_stand);
        ClearMap(tree_map_inv_mass_Y0);
        ClearMap(tree_map_inv_mass_Y0_stand);
        ClearMap(tree_map_ptcl_inv_mass_Y0);
        ClearMap(tree_map_ptcl_inv_mass_Y0_stand);
    }


    tree->Write();
    out->Write();
    out->Close();

    return 0;
}



    //weight tt + y0 ->tt  (4top) = sigma_y0tt/sigma_SM_tttt = 0.001319/0.002183 = 0.6042143838754008
    //number of events generated same for y0 and SM
    //double weight = 0.6042143838754008;


        //for (int j = 0; j<lor2->size();j++){
        //    for (int k = 0; k<lor2->size();k++){
    //MLy0->Draw("ComputeInvariantMass(Large_jets[0].Pt(), Large_jets[0].Eta(), Large_jets[0].Phi(), Large_jets[0].M(),Large_jets[1].Pt(), Large_jets[1].Eta(), Large_jets[1].Phi(), Large_jets[1].M())", "(Info_det.m_N_Ljet >=2)&&(Large_jets[0].IsDet())&&(Large_jets[1].IsDet())", "same");

    //ML->Draw(TString::Format("ComputeInvariantMass(Large_jets[%i].Pt(), Large_jets[%i].Eta(), Large_jets[%i].Phi(), Large_jets[%i].M(),Large_jets[%i].Pt(), Large_jets[%i].Eta(), Large_jets[%i].Phi(), Large_jets[%i].M())",l,l,l,l,m,m,m,m), TString::Format("(Info_det.m_N_Ljet >=2)&&(Large_jets[%i].IsDet())&&(Large_jets[%i].IsDet())", l,m) , "hist");

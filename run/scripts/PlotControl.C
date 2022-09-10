double GetDRCut(TString a){
    if (a.Contains("FastJets02")) return 0.4;
    if (a.Contains("FastJets04")) return 0.8;
    if (a.Contains("FastJets06")) return 1.2;
    if (a.Contains("FastJets08")) return 1.6;
    if (a.Contains("FastJets10")) return 2.0;
    return -1;
}

TString GetDRCutStr(TString a){
    if (a.Contains("FastJets02")) return "02";
    if (a.Contains("FastJets04")) return "04";
    if (a.Contains("FastJets06")) return "06";
    if (a.Contains("FastJets08")) return "08";
    if (a.Contains("FastJets10")) return "10";
    return "None";
}

int PlotControl(TString EnergyA = "7000", TString EnergyB = "13000", bool Pythia = false){
    
//    TString EnergyA = "7000";
//    TString EnergyB = "13000";
//    bool Pythia = false;
    TFile * rfile;
    TFile * rfilenompi;
    TFile * rfiletrimm;

    if (Pythia){
        rfile = new TFile(TString::Format("out_%s_%s_pythia.root", EnergyA.Data(), EnergyB.Data()), "read");
        rfilenompi = new TFile(TString::Format("out_noMPI_noISR_%s_%s_pythia.root", EnergyA.Data(), EnergyB.Data()), "read");
        rfiletrimm = new TFile(TString::Format("./trimmed/out_%s_%s.root", EnergyA.Data(), EnergyB.Data()), "read");
    }else{
        rfile = new TFile(TString::Format("out_%s_%s.root", EnergyA.Data(), EnergyB.Data()), "read");
        rfilenompi = new TFile(TString::Format("out_noMPI_noISR_%s_%s.root", EnergyA.Data(), EnergyB.Data()), "read");
        rfiletrimm = new TFile(TString::Format("./trimmed/out_%s_%s.root", EnergyA.Data(), EnergyB.Data()), "read");
    }

    vector<TString> Radii;
    vector<TString> Lambdas;
    vector<TString> Q;
    vector<TString> Energies;

    Radii.push_back("02");
    Radii.push_back("04");
    Radii.push_back("06");
    Radii.push_back("08");
    Radii.push_back("10");
    Lambdas.push_back("Mult");
    Q.push_back("50");
    Energies.push_back(EnergyA);
    Energies.push_back(EnergyB);

    vector<TString> JetAng;
    vector<TString> JetPt;
    vector<TString> JetEta;
    vector<TString> JetPhi;
    vector<TString> JetE;

    vector<TString> mmdt_JetAng;
    vector<TString> mmdt_JetPt;
    vector<TString> mmdt_JetEta;
    vector<TString> mmdt_JetPhi;
    vector<TString> mmdt_JetE;

    vector<TTree*> trees;
    vector<TTree*> treesnompi;
    vector<TTree*> treestrimm;
    TTree * tree;
    TTree * treenompi;
    TTree * treetrimm;
    TTree * pt_tree;
    TTree * pt_treenompi;
    TTree * pt_treetrimm;
    TTree * eta_tree;
    TTree * eta_treenompi;
    TTree * eta_treetrimm;
    TTree * phi_tree;
    TTree * phi_treenompi;
    TTree * phi_treetrimm;
    TTree * E_tree;
    TTree * E_treenompi;
    TTree * E_treetrimm;

    vector<TTree*> mmdt_trees;
    vector<TTree*> mmdt_treesnompi;
    vector<TTree*> mmdt_treestrimm;
    TTree * mmdt_tree;
    TTree * mmdt_treenompi;
    TTree * mmdt_treetrimm;
    TTree * mmdt_pt_tree;
    TTree * mmdt_pt_treenompi;
    TTree * mmdt_pt_treetrimm;
    TTree * mmdt_eta_tree;
    TTree * mmdt_eta_treenompi;
    TTree * mmdt_eta_treetrimm;
    TTree * mmdt_phi_tree;
    TTree * mmdt_phi_treenompi;
    TTree * mmdt_phi_treetrimm;
    TTree * mmdt_E_tree;
    TTree * mmdt_E_treenompi;
    TTree * mmdt_E_treetrimm;

    TString Check;

    for (int j = 0; j < Lambdas.size();j++){
        for (int i = 0; i < Radii.size();i++){
            for (int k = 0; k < Q.size();k++){
                JetAng.push_back( TString::Format("FastJets%s%sLam%s", Radii[i].Data(), Lambdas[j].Data(), Q[k].Data() ) );
                JetPt.push_back(  TString::Format("FastJets%sPt", Radii[i].Data() ) );
                JetEta.push_back( TString::Format("FastJets%sEta", Radii[i].Data() ) );
                JetPhi.push_back( TString::Format("FastJets%sPhi", Radii[i].Data() ) );
                JetE.push_back(   TString::Format("FastJets%sE", Radii[i].Data() ) );

                mmdt_JetAng.push_back( TString::Format("mmdt_FastJets%s%sLam%s", Radii[i].Data(), Lambdas[j].Data(), Q[k].Data() ) );
                mmdt_JetPt.push_back(  TString::Format("mmdt_FastJets%sPt", Radii[i].Data() ) );
                mmdt_JetEta.push_back( TString::Format("mmdt_FastJets%sEta", Radii[i].Data() ) );
                mmdt_JetPhi.push_back( TString::Format("mmdt_FastJets%sPhi", Radii[i].Data() ) );
                mmdt_JetE.push_back( TString::Format("mmdt_FastJets%sE", Radii[i].Data() ) );
                for (int l = 0; l < Energies.size();l++){
                    tree      =      (TTree*)rfile     ->Get(TString::Format("FastJets%s%sLam%s_%s", Radii[i].Data(), Lambdas[j].Data(), Q[k].Data(), Energies[l].Data() ));
                    treenompi = (TTree*)rfilenompi->Get(TString::Format("FastJets%s%sLam%s_%s", Radii[i].Data(), Lambdas[j].Data(), Q[k].Data(), Energies[l].Data() ));
                    treetrimm = (TTree*)rfiletrimm->Get(TString::Format("FastJets%s%sLam%s_%s", Radii[i].Data(), Lambdas[j].Data(), Q[k].Data(), Energies[l].Data() ));
                    pt_tree =      (TTree*)rfile     ->Get(  TString::Format("FastJets%sPt_%s", Radii[i].Data()  , Energies[l].Data() ));
                    pt_treenompi = (TTree*)rfilenompi->Get(  TString::Format("FastJets%sPt_%s", Radii[i].Data()  , Energies[l].Data() ));
                    pt_treetrimm = (TTree*)rfiletrimm->Get(  TString::Format("FastJets%sPt_%s", Radii[i].Data()  , Energies[l].Data() ));
                    eta_tree =      (TTree*)rfile     ->Get( TString::Format("FastJets%sEta_%s", Radii[i].Data() , Energies[l].Data() ));
                    eta_treenompi = (TTree*)rfilenompi->Get( TString::Format("FastJets%sEta_%s", Radii[i].Data() , Energies[l].Data() ));
                    eta_treetrimm = (TTree*)rfiletrimm->Get( TString::Format("FastJets%sEta_%s", Radii[i].Data() , Energies[l].Data() ));
                    phi_tree =      (TTree*)rfile     ->Get( TString::Format("FastJets%sPhi_%s", Radii[i].Data() , Energies[l].Data() ));
                    phi_treenompi = (TTree*)rfilenompi->Get( TString::Format("FastJets%sPhi_%s", Radii[i].Data() , Energies[l].Data() ));
                    phi_treetrimm = (TTree*)rfiletrimm->Get( TString::Format("FastJets%sPhi_%s", Radii[i].Data() , Energies[l].Data() ));
                    E_tree =      (TTree*)rfile     ->Get(   TString::Format("FastJets%sE_%s", Radii[i].Data()   , Energies[l].Data() ));
                    E_treenompi = (TTree*)rfilenompi->Get(   TString::Format("FastJets%sE_%s", Radii[i].Data()   , Energies[l].Data() ));
                    E_treetrimm = (TTree*)rfiletrimm->Get(   TString::Format("FastJets%sE_%s", Radii[i].Data()   , Energies[l].Data() ));

                    tree     ->AddFriend(pt_tree     );
                    treenompi->AddFriend(pt_treenompi);
                    treetrimm->AddFriend(pt_treetrimm);

                    tree     ->AddFriend(eta_tree     );
                    treenompi->AddFriend(eta_treenompi);
                    treetrimm->AddFriend(eta_treetrimm);

                    tree     ->AddFriend(phi_tree     );
                    treenompi->AddFriend(phi_treenompi);
                    treetrimm->AddFriend(phi_treetrimm);

                    tree     ->AddFriend(E_tree     );
                    treenompi->AddFriend(E_treenompi);
                    treetrimm->AddFriend(E_treetrimm);

                    trees.push_back(tree);
                    treesnompi.push_back(treenompi);
                    treestrimm.push_back(treetrimm);
                    
                    //mmdt
                    mmdt_tree      =      (TTree*)rfile->Get(TString::Format("mmdt_FastJets%s%sLam%s_%s", Radii[i].Data(), Lambdas[j].Data(), Q[k].Data(), Energies[l].Data() ));
                    mmdt_treenompi = (TTree*)rfilenompi->Get(TString::Format("mmdt_FastJets%s%sLam%s_%s", Radii[i].Data(), Lambdas[j].Data(), Q[k].Data(), Energies[l].Data() ));
                    mmdt_treetrimm = (TTree*)rfiletrimm->Get(TString::Format("mmdt_FastJets%s%sLam%s_%s", Radii[i].Data(), Lambdas[j].Data(), Q[k].Data(), Energies[l].Data() ));

                    mmdt_pt_tree =      (TTree*)rfile     ->Get(  TString::Format("mmdt_FastJets%sPt_%s", Radii[i].Data()  , Energies[l].Data() ));
                    mmdt_pt_treenompi = (TTree*)rfilenompi->Get(  TString::Format("mmdt_FastJets%sPt_%s", Radii[i].Data()  , Energies[l].Data() ));
                    mmdt_pt_treetrimm = (TTree*)rfiletrimm->Get(  TString::Format("mmdt_FastJets%sPt_%s", Radii[i].Data()  , Energies[l].Data() ));
                    mmdt_eta_tree =      (TTree*)rfile     ->Get( TString::Format("mmdt_FastJets%sEta_%s", Radii[i].Data() , Energies[l].Data() ));
                    mmdt_eta_treenompi = (TTree*)rfilenompi->Get( TString::Format("mmdt_FastJets%sEta_%s", Radii[i].Data() , Energies[l].Data() ));
                    mmdt_eta_treetrimm = (TTree*)rfiletrimm->Get( TString::Format("mmdt_FastJets%sEta_%s", Radii[i].Data() , Energies[l].Data() ));
                    mmdt_phi_tree =      (TTree*)rfile     ->Get( TString::Format("mmdt_FastJets%sPhi_%s", Radii[i].Data() , Energies[l].Data() ));
                    mmdt_phi_treenompi = (TTree*)rfilenompi->Get( TString::Format("mmdt_FastJets%sPhi_%s", Radii[i].Data() , Energies[l].Data() ));
                    mmdt_phi_treetrimm = (TTree*)rfiletrimm->Get( TString::Format("mmdt_FastJets%sPhi_%s", Radii[i].Data() , Energies[l].Data() ));
                    mmdt_E_tree =      (TTree*)rfile     ->Get(   TString::Format("mmdt_FastJets%sE_%s", Radii[i].Data()   , Energies[l].Data() ));
                    mmdt_E_treenompi = (TTree*)rfilenompi->Get(   TString::Format("mmdt_FastJets%sE_%s", Radii[i].Data()   , Energies[l].Data() ));
                    mmdt_E_treetrimm = (TTree*)rfiletrimm->Get(   TString::Format("mmdt_FastJets%sE_%s", Radii[i].Data()   , Energies[l].Data() ));

                    mmdt_tree     ->AddFriend(mmdt_pt_tree     );
                    mmdt_treenompi->AddFriend(mmdt_pt_treenompi);
                    mmdt_treetrimm->AddFriend(mmdt_pt_treetrimm);
                    mmdt_tree     ->AddFriend(mmdt_eta_tree     );
                    mmdt_treenompi->AddFriend(mmdt_eta_treenompi);
                    mmdt_treetrimm->AddFriend(mmdt_eta_treetrimm);
                    mmdt_tree     ->AddFriend(mmdt_phi_tree     );
                    mmdt_treenompi->AddFriend(mmdt_phi_treenompi);
                    mmdt_treetrimm->AddFriend(mmdt_phi_treetrimm);
                    mmdt_tree     ->AddFriend(mmdt_E_tree     );
                    mmdt_treenompi->AddFriend(mmdt_E_treenompi);
                    mmdt_treetrimm->AddFriend(mmdt_E_treetrimm);
                    mmdt_trees.push_back(     mmdt_tree);
                    mmdt_treesnompi.push_back(mmdt_treenompi);
                    mmdt_treestrimm.push_back( mmdt_treetrimm);
                }
                
            }
        }
    }

    TString CutOver;
    TString mmdt_CutOver;
    double DRCut;
    TString DRCutStr;
    TString Temp;
    TH1D* htemp;
    TH2D* htemp2;

    TFile * output;
   if (Pythia){
       output = new TFile(TString::Format("control_%s_%s_pythia.root", EnergyA.Data(), EnergyB.Data() ), "recreate" );
   }else{
       output = new TFile(TString::Format("control_%s_%s.root", EnergyA.Data(), EnergyB.Data() ), "recreate" );
   }

     output->cd();


    for (int i = 0 ; i < trees.size(); i++){
        DRCut = GetDRCut(trees[i]->GetName());
        DRCutStr = GetDRCutStr(trees[i]->GetName());

        CutOver = TString::Format("(TMath::Sqrt( TMath::Power(FastJets%sEta[0]-FastJets%sEta[1],2)+TMath::Power(TVector2::Phi_mpi_pi(FastJets%sPhi[0]-FastJets%sPhi[1]),2) ) >= %f)", 
            DRCutStr.Data(),
            DRCutStr.Data(),
            DRCutStr.Data(),
            DRCutStr.Data()
            , DRCut);
        CutOver = "";//do not have produced ntuples fro trimmed

        mmdt_CutOver = TString::Format("(TMath::Sqrt( TMath::Power(mmdt_FastJets%sEta[0]-mmdt_FastJets%sEta[1],2)+TMath::Power(TVector2::Phi_mpi_pi(mmdt_FastJets%sPhi[0]-mmdt_FastJets%sPhi[1]),2) ) >= %f)", 
            DRCutStr.Data(),
            DRCutStr.Data(),
            DRCutStr.Data(),
            DRCutStr.Data()
            , DRCut);
        mmdt_CutOver = ""; //do not have produced ntuples fro trimmed
        
        Temp = TString::Format("FastJets%sPt >> h_%s(250,0,250)", DRCutStr.Data(), trees[i]->GetName() );
    //FastJets10MassLam100_900->GetListOfBranches()->At(0)->GetName()
        trees[i]     ->Draw(TString::Format("%s >> h_%s(100,0,100)", trees[i]->GetListOfBranches()->At(0)->GetName(), trees[i]->GetName() ), CutOver.Data(), "goff");
        htemp = (TH1D*)gDirectory->Get(TString::Format("h_%s", trees[i]->GetName() ));
        htemp->Scale(1./htemp->Integral());
        treesnompi[i]->Draw(TString::Format("%s >> h_nompi_%s(100,0,100)", trees[i]->GetListOfBranches()->At(0)->GetName(), trees[i]->GetName() ), CutOver.Data(), "goff");
        htemp = (TH1D*)gDirectory->Get(TString::Format("h_nompi_%s", trees[i]->GetName() ));
        htemp->SetLineColor(2);
        htemp->Scale(1./htemp->Integral());
        treestrimm[i]->Draw(TString::Format("%s >> h_trim_%s(100,0,100)", trees[i]->GetListOfBranches()->At(0)->GetName(), trees[i]->GetName() ), CutOver.Data(), "goff");
        htemp = (TH1D*)gDirectory->Get(TString::Format("h_trim_%s", trees[i]->GetName() ));
        htemp->SetLineColor(4);
        htemp->Scale(1./htemp->Integral());
        //

        trees[i]     ->Draw(TString::Format("FastJets%sPt >> h_Pt_%s(250,0,250)", DRCutStr.Data(), trees[i]->GetName() ), CutOver.Data(), "goff");
        htemp = (TH1D*)gDirectory->Get(TString::Format("h_Pt_%s", trees[i]->GetName() ));
        htemp->Scale(1./htemp->Integral());
        treesnompi[i]->Draw(TString::Format("FastJets%sPt >> h_Pt_nompi_%s(250,0,250)", DRCutStr.Data(), trees[i]->GetName() ), CutOver.Data(), "goff");
        htemp = (TH1D*)gDirectory->Get(TString::Format("h_Pt_nompi_%s", trees[i]->GetName() ));
        htemp->SetLineColor(2);
        htemp->Scale(1./htemp->Integral());
        treestrimm[i]->Draw(TString::Format("FastJets%sPt >> h_Pt_trim_%s(250,0,250)", DRCutStr.Data(), trees[i]->GetName() ), CutOver.Data(), "goff");
        htemp = (TH1D*)gDirectory->Get(TString::Format("h_Pt_trim_%s", trees[i]->GetName() ));
        htemp->SetLineColor(4);
        htemp->Scale(1./htemp->Integral());
        trees[i]     ->Draw(TString::Format("FastJets%sEta >> h_Eta_%s(40,-2.5,2.5)", DRCutStr.Data(), trees[i]->GetName() ), CutOver.Data(), "goff");
        htemp = (TH1D*)gDirectory->Get(TString::Format("h_Eta_%s", trees[i]->GetName() ));
        htemp->Scale(1./htemp->Integral());
        treesnompi[i]->Draw(TString::Format("FastJets%sEta >> h_Eta_nompi_%s(40,-2.5,2.5)", DRCutStr.Data(), trees[i]->GetName() ), CutOver.Data(), "goff");
        htemp = (TH1D*)gDirectory->Get(TString::Format("h_Eta_nompi_%s", trees[i]->GetName() ));
        htemp->SetLineColor(2);
        htemp->Scale(1./htemp->Integral());
        treestrimm[i]->Draw(TString::Format("FastJets%sEta >> h_Eta_trim_%s(40,-2.5,2.5)", DRCutStr.Data(), trees[i]->GetName() ), CutOver.Data(), "goff");
        htemp = (TH1D*)gDirectory->Get(TString::Format("h_Eta_trim_%s", trees[i]->GetName() ));
        htemp->SetLineColor(4);
        htemp->Scale(1./htemp->Integral());
        trees[i]     ->Draw(TString::Format("FastJets%sEta:FastJets%sPt >> h_PtEta_%s(250,0,250,40,-2.5,2.5)",       DRCutStr.Data(),DRCutStr.Data(), trees[i]->GetName() ), CutOver.Data(), "goff");
        htemp2 = (TH2D*)gDirectory->Get(TString::Format("h_PtEta_%s", trees[i]->GetName() ));
        htemp2->Scale(1./htemp2->Integral());
        treesnompi[i]->Draw(TString::Format("FastJets%sEta:FastJets%sPt >> h_PtEta_nompi_%s(250,0,250,40,-2.5,2.5)", DRCutStr.Data(),DRCutStr.Data(), trees[i]->GetName() ), CutOver.Data(), "goff");
        htemp2 = (TH2D*)gDirectory->Get(TString::Format("h_PtEta_nompi_%s", trees[i]->GetName() ));
        htemp2->Scale(1./htemp2->Integral());
        treestrimm[i]->Draw(TString::Format("FastJets%sEta:FastJets%sPt >> h_PtEta_trim_%s(250,0,250,40,-2.5,2.5)",  DRCutStr.Data(),DRCutStr.Data(), trees[i]->GetName() ), CutOver.Data(), "goff");
        htemp2 = (TH2D*)gDirectory->Get(TString::Format("h_PtEta_trim_%s", trees[i]->GetName() ));
        htemp2->Scale(1./htemp2->Integral());

        //MMDT

        mmdt_trees[i]     ->Draw(TString::Format("%s >> h_%s(100,0,100)", mmdt_trees[i]->GetListOfBranches()->At(0)->GetName(), mmdt_trees[i]->GetName() ), CutOver.Data(), "goff");
        htemp = (TH1D*)gDirectory->Get(TString::Format("h_%s", mmdt_trees[i]->GetName() ));
        htemp->Scale(1./htemp->Integral());
        mmdt_treesnompi[i]->Draw(TString::Format("%s >> h_nompi_%s(100,0,100)", mmdt_trees[i]->GetListOfBranches()->At(0)->GetName(), mmdt_trees[i]->GetName() ), CutOver.Data(), "goff");
        htemp = (TH1D*)gDirectory->Get(TString::Format("h_nompi_%s", mmdt_trees[i]->GetName() ));
        htemp->SetLineColor(2);
        htemp->Scale(1./htemp->Integral());
        mmdt_treestrimm[i]->Draw(TString::Format("%s >> h_trim_%s(100,0,100)", mmdt_trees[i]->GetListOfBranches()->At(0)->GetName(), mmdt_trees[i]->GetName() ), CutOver.Data(), "goff");
        htemp = (TH1D*)gDirectory->Get(TString::Format("h_trim_%s", mmdt_trees[i]->GetName() ));
        htemp->SetLineColor(4);
        htemp->Scale(1./htemp->Integral());

        Temp = TString::Format("mmdt_FastJets%sPt >> h_%s(250,0,250)", DRCutStr.Data(), mmdt_trees[i]->GetName() );
        mmdt_trees[i]     ->Draw(TString::Format("mmdt_FastJets%sPt >> h_Pt_%s(250,0,250)", DRCutStr.Data(), mmdt_trees[i]->GetName() ), CutOver.Data(), "goff");
        htemp = (TH1D*)gDirectory->Get(TString::Format("h_Pt_%s", mmdt_trees[i]->GetName() ));
        htemp->Scale(1./htemp->Integral());
        mmdt_treesnompi[i]->Draw(TString::Format("mmdt_FastJets%sPt >> h_Pt_nompi_%s(250,0,250)", DRCutStr.Data(), mmdt_trees[i]->GetName() ), CutOver.Data(), "goff");
        htemp = (TH1D*)gDirectory->Get(TString::Format("h_Pt_nompi_%s", mmdt_trees[i]->GetName() ));
        htemp->SetLineColor(2);
        htemp->Scale(1./htemp->Integral());
        mmdt_treestrimm[i]->Draw(TString::Format("mmdt_FastJets%sPt >> h_Pt_trim_%s(250,0,250)", DRCutStr.Data(), mmdt_trees[i]->GetName() ), CutOver.Data(), "goff");
        htemp = (TH1D*)gDirectory->Get(TString::Format("h_Pt_trim_%s", mmdt_trees[i]->GetName() ));
        htemp->SetLineColor(4);
        htemp->Scale(1./htemp->Integral());
        mmdt_trees[i]     ->Draw(TString::Format("mmdt_FastJets%sEta >> h_Eta_%s(40,-2.5,2.5)", DRCutStr.Data(), mmdt_trees[i]->GetName() ), CutOver.Data(), "goff");
        htemp = (TH1D*)gDirectory->Get(TString::Format("h_Eta_%s", mmdt_trees[i]->GetName() ));
        htemp->Scale(1./htemp->Integral());
        mmdt_treesnompi[i]->Draw(TString::Format("mmdt_FastJets%sEta >> h_Eta_nompi_%s(40,-2.5,2.5)", DRCutStr.Data(), mmdt_trees[i]->GetName() ), CutOver.Data(), "goff");
        htemp = (TH1D*)gDirectory->Get(TString::Format("h_Eta_nompi_%s", mmdt_trees[i]->GetName() ));
        htemp->SetLineColor(2);
        htemp->Scale(1./htemp->Integral());
        mmdt_treestrimm[i]->Draw(TString::Format("mmdt_FastJets%sEta >> h_Eta_trim_%s(40,-2.5,2.5)", DRCutStr.Data(), mmdt_trees[i]->GetName() ), CutOver.Data(), "goff");
        htemp = (TH1D*)gDirectory->Get(TString::Format("h_Eta_trim_%s", mmdt_trees[i]->GetName() ));
        htemp->SetLineColor(4);
        htemp->Scale(1./htemp->Integral());
        mmdt_trees[i]     ->Draw(TString::Format("mmdt_FastJets%sEta:mmdt_FastJets%sPt >> h_PtEta_%s(250,0,250,40,-2.5,2.5)",       DRCutStr.Data(),DRCutStr.Data(), mmdt_trees[i]->GetName() ), CutOver.Data(), "goff");
        htemp2 = (TH2D*)gDirectory->Get(TString::Format("h_PtEta_%s", mmdt_trees[i]->GetName() ));
        htemp2->Scale(1./htemp2->Integral());
        mmdt_treesnompi[i]->Draw(TString::Format("mmdt_FastJets%sEta:mmdt_FastJets%sPt >> h_PtEta_nompi_%s(250,0,250,40,-2.5,2.5)", DRCutStr.Data(),DRCutStr.Data(), mmdt_trees[i]->GetName() ), CutOver.Data(), "goff");
        htemp2 = (TH2D*)gDirectory->Get(TString::Format("h_PtEta_nompi_%s", mmdt_trees[i]->GetName() ));
        htemp2->Scale(1./htemp2->Integral());
        mmdt_treestrimm[i]->Draw(TString::Format("mmdt_FastJets%sEta:mmdt_FastJets%sPt >> h_PtEta_trim_%s(250,0,250,40,-2.5,2.5)",  DRCutStr.Data(),DRCutStr.Data(), mmdt_trees[i]->GetName() ), CutOver.Data(), "goff");
        htemp2 = (TH2D*)gDirectory->Get(TString::Format("h_PtEta_trim_%s", mmdt_trees[i]->GetName() ));
        htemp2->Scale(1./htemp2->Integral());





    }

   
 
   output->Write();
   output->Close();

    return 0;
}
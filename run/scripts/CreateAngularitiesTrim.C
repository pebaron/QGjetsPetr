double GetFraction(double Pt, double Eta, TH2F * histo){
    return histo->GetBinContent( histo->GetXaxis()->FindBin(Pt), histo->GetYaxis()->FindBin(Eta) );
}

int CreateAngularitiesTrim(TString EnergyA = "900", TString EnergyB = "2360", bool Pythia = false){

    TFile * file_fractionA = new TFile(TString::Format("/disk0/QGjetsPetr/run/scripts/GluonFraction_%s.root", EnergyA.Data() ), "read");
    TFile * file_fractionB = new TFile(TString::Format("/disk0/QGjetsPetr/run/scripts/GluonFraction_%s.root", EnergyB.Data() ), "read");

    TH2F * fractionA = (TH2F*)file_fractionA->Get(TString::Format("GluonFraction_%s", EnergyA.Data() ));
    TH2F * fractionB = (TH2F*)file_fractionB->Get(TString::Format("GluonFraction_%s", EnergyB.Data() ));

    TFile * fileA;
    TFile * fileB;

    if (Pythia){
        fileA = new TFile(TString::Format("/disk0/QGjetsPetr/Petr_Pythia/trim_%s_hadr_pythia.root", EnergyA.Data() ), "read" );
        fileB = new TFile(TString::Format("/disk0/QGjetsPetr/Petr_Pythia/trim_%s_hadr_pythia.root", EnergyB.Data() ), "read" );
    }else{
        fileA = new TFile(TString::Format("/disk0/QGjetsPetr/run/files_test/trim_%s_hadr.root", EnergyA.Data() ), "read" );
        fileB = new TFile(TString::Format("/disk0/QGjetsPetr/run/files_test/trim_%s_hadr.root", EnergyB.Data() ), "read" );
    }

    TTree * treeA = (TTree*)fileA->Get("MC_DIJET_PB_CH");
    TTree * treeB = (TTree*)fileB->Get("MC_DIJET_PB_CH");

    TFile * output;
    if (Pythia){
        output = new TFile(TString::Format("/disk0/QGjetsPetr/run/scripts/out_trim_%s_%s_pythia.root", EnergyA.Data(), EnergyB.Data() ), "recreate");
    }else{
        output = new TFile(TString::Format("/disk0/QGjetsPetr/run/scripts/out_trim_%s_%s.root", EnergyA.Data(), EnergyB.Data() ), "recreate");
    }
    
    //TTree * tree_outA = new TTree(TString::Format("tree_%s", EnergyA.Data() ), TString::Format("tree_%s", EnergyA.Data() ) );
    //TTree * tree_outB = new TTree(TString::Format("tree_%s", EnergyB.Data() ), TString::Format("tree_%s", EnergyB.Data() ) );

    vector<TString> Radii;
    vector<TString> Lambdas;
    vector<TString> Q;

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


    std::map<TString, vector<double>*> Map_A_JetAng;
    std::map<TString, vector<double>*> Map_A_JetPt;
    std::map<TString, vector<double>*> Map_A_JetEta;
    std::map<TString, vector<double>*> Map_A_JetPhi;
    std::map<TString, vector<double>*> Map_A_JetE;
    std::map<TString, vector<double>*> Map_A_JetFraction;

    std::map<TString, vector<double>*> Map_B_JetAng;
    std::map<TString, vector<double>*> Map_B_JetPt;
    std::map<TString, vector<double>*> Map_B_JetEta;
    std::map<TString, vector<double>*> Map_B_JetPhi;
    std::map<TString, vector<double>*> Map_B_JetE;
    std::map<TString, vector<double>*> Map_B_JetFraction;

    std::map<TString, vector<double>*> Map_A_mmdt_JetAng;
    std::map<TString, vector<double>*> Map_A_mmdt_JetPt;
    std::map<TString, vector<double>*> Map_A_mmdt_JetEta;
    std::map<TString, vector<double>*> Map_A_mmdt_JetPhi;
    std::map<TString, vector<double>*> Map_A_mmdt_JetE;
    std::map<TString, vector<double>*> Map_A_mmdt_JetFraction;

    std::map<TString, vector<double>*> Map_B_mmdt_JetAng;
    std::map<TString, vector<double>*> Map_B_mmdt_JetPt;
    std::map<TString, vector<double>*> Map_B_mmdt_JetEta;
    std::map<TString, vector<double>*> Map_B_mmdt_JetPhi;
    std::map<TString, vector<double>*> Map_B_mmdt_JetE;
    std::map<TString, vector<double>*> Map_B_mmdt_JetFraction;


    //

    std::map<TString, TBranch*> br_Map_A_JetAng;
    std::map<TString, TBranch*> br_Map_A_JetPt;
    std::map<TString, TBranch*> br_Map_A_JetEta;
    std::map<TString, TBranch*> br_Map_A_JetPhi;
    std::map<TString, TBranch*> br_Map_A_JetE;
    std::map<TString, TBranch*> br_Map_A_JetFraction;
    std::map<TString, TBranch*> br_Map_B_JetAng;
    std::map<TString, TBranch*> br_Map_B_JetPt;
    std::map<TString, TBranch*> br_Map_B_JetEta;
    std::map<TString, TBranch*> br_Map_B_JetPhi;
    std::map<TString, TBranch*> br_Map_B_JetE;
    std::map<TString, TBranch*> br_Map_B_JetFraction;
    std::map<TString, TBranch*> br_Map_A_mmdt_JetAng;
    std::map<TString, TBranch*> br_Map_A_mmdt_JetPt;
    std::map<TString, TBranch*> br_Map_A_mmdt_JetEta;
    std::map<TString, TBranch*> br_Map_A_mmdt_JetPhi;
    std::map<TString, TBranch*> br_Map_A_mmdt_JetE;
    std::map<TString, TBranch*> br_Map_A_mmdt_JetFraction;
    std::map<TString, TBranch*> br_Map_B_mmdt_JetAng;
    std::map<TString, TBranch*> br_Map_B_mmdt_JetPt;
    std::map<TString, TBranch*> br_Map_B_mmdt_JetEta;
    std::map<TString, TBranch*> br_Map_B_mmdt_JetPhi;
    std::map<TString, TBranch*> br_Map_B_mmdt_JetE;
    std::map<TString, TBranch*> br_Map_B_mmdt_JetFraction;

    std::map<TString, TTree*> tree_br_Map_A_JetAng;
    std::map<TString, TTree*> tree_br_Map_A_JetPt;
    std::map<TString, TTree*> tree_br_Map_A_JetEta;
    std::map<TString, TTree*> tree_br_Map_A_JetPhi;
    std::map<TString, TTree*> tree_br_Map_A_JetE;
    std::map<TString, TTree*> tree_br_Map_A_JetFraction;
    std::map<TString, TTree*> tree_br_Map_B_JetAng;
    std::map<TString, TTree*> tree_br_Map_B_JetPt;
    std::map<TString, TTree*> tree_br_Map_B_JetEta;
    std::map<TString, TTree*> tree_br_Map_B_JetPhi;
    std::map<TString, TTree*> tree_br_Map_B_JetE;
    std::map<TString, TTree*> tree_br_Map_B_JetFraction;
    std::map<TString, TTree*> tree_br_Map_A_mmdt_JetAng;
    std::map<TString, TTree*> tree_br_Map_A_mmdt_JetPt;
    std::map<TString, TTree*> tree_br_Map_A_mmdt_JetEta;
    std::map<TString, TTree*> tree_br_Map_A_mmdt_JetPhi;
    std::map<TString, TTree*> tree_br_Map_A_mmdt_JetE;
    std::map<TString, TTree*> tree_br_Map_A_mmdt_JetFraction;
    std::map<TString, TTree*> tree_br_Map_B_mmdt_JetAng;
    std::map<TString, TTree*> tree_br_Map_B_mmdt_JetPt;
    std::map<TString, TTree*> tree_br_Map_B_mmdt_JetEta;
    std::map<TString, TTree*> tree_br_Map_B_mmdt_JetPhi;
    std::map<TString, TTree*> tree_br_Map_B_mmdt_JetE;
    std::map<TString, TTree*> tree_br_Map_B_mmdt_JetFraction;
    

    for (int i = 0; i < Radii.size();i++){
        for (int j = 0; j < Lambdas.size();j++){
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

    for (int i = 0; i < JetAng.size();i++){
        treeA->SetBranchAddress(JetAng[i].Data(), &Map_A_JetAng[JetAng[i].Data()]);
        treeA->SetBranchAddress(JetPt[i].Data() , &Map_A_JetPt[JetPt[i].Data() ]);
        treeA->SetBranchAddress(JetEta[i].Data(), &Map_A_JetEta[JetEta[i].Data()]);
        treeA->SetBranchAddress(JetPhi[i].Data(), &Map_A_JetPhi[JetPhi[i].Data()]);
        treeA->SetBranchAddress(JetE[i].Data(), &Map_A_JetE[JetE[i].Data()]);
        treeB->SetBranchAddress(JetAng[i].Data(), &Map_B_JetAng[JetAng[i].Data()]);
        treeB->SetBranchAddress(JetPt[i].Data() , &Map_B_JetPt[JetPt[i].Data() ]);
        treeB->SetBranchAddress(JetEta[i].Data(), &Map_B_JetEta[JetEta[i].Data()]);
        treeB->SetBranchAddress(JetPhi[i].Data(), &Map_B_JetPhi[JetPhi[i].Data()]);
        treeB->SetBranchAddress(JetE[i].Data(), &Map_B_JetE[JetE[i].Data()]);


        treeA->SetBranchAddress(mmdt_JetAng[i].Data(), &Map_A_mmdt_JetAng[mmdt_JetAng[i].Data()]);
        treeA->SetBranchAddress(mmdt_JetPt[i].Data() , &Map_A_mmdt_JetPt[ mmdt_JetPt[i].Data() ]);
        treeA->SetBranchAddress(mmdt_JetEta[i].Data(), &Map_A_mmdt_JetEta[mmdt_JetEta[i].Data()]);
        treeA->SetBranchAddress(mmdt_JetPhi[i].Data(), &Map_A_mmdt_JetPhi[mmdt_JetPhi[i].Data()]);
        treeA->SetBranchAddress(mmdt_JetE[i].Data(), &Map_A_mmdt_JetE[mmdt_JetE[i].Data()]);
        treeB->SetBranchAddress(mmdt_JetAng[i].Data(), &Map_B_mmdt_JetAng[mmdt_JetAng[i].Data()]);
        treeB->SetBranchAddress(mmdt_JetPt[i].Data() , &Map_B_mmdt_JetPt[ mmdt_JetPt[i].Data() ]);
        treeB->SetBranchAddress(mmdt_JetEta[i].Data(), &Map_B_mmdt_JetEta[mmdt_JetEta[i].Data()]);
        treeB->SetBranchAddress(mmdt_JetPhi[i].Data(), &Map_B_mmdt_JetPhi[mmdt_JetPhi[i].Data()]);
        treeB->SetBranchAddress(mmdt_JetE[i].Data(), &Map_B_mmdt_JetE[mmdt_JetE[i].Data()]);


    
    tree_br_Map_A_JetAng[JetAng[i].Data()] =               new TTree(TString::Format("%s_%s", JetAng[i].Data()     ,EnergyA.Data()), TString::Format("%s_%s", JetAng[i].Data()     ,EnergyA.Data()) );
    tree_br_Map_A_JetPt[JetPt[i].Data()]   =               new TTree(TString::Format("%s_%s", JetPt[i].Data()      ,EnergyA.Data()), TString::Format("%s_%s", JetPt[i].Data()      ,EnergyA.Data()) );
    tree_br_Map_A_JetEta[JetEta[i].Data()] =               new TTree(TString::Format("%s_%s", JetEta[i].Data()     ,EnergyA.Data()), TString::Format("%s_%s", JetEta[i].Data()     ,EnergyA.Data()) );
    tree_br_Map_A_JetPhi[JetPhi[i].Data()] =               new TTree(TString::Format("%s_%s", JetPhi[i].Data()     ,EnergyA.Data()), TString::Format("%s_%s", JetPhi[i].Data()     ,EnergyA.Data()) );
    tree_br_Map_A_JetE[JetE[i].Data()] =                   new TTree(TString::Format("%s_%s", JetE[i].Data()       ,EnergyA.Data()), TString::Format("%s_%s", JetE[i].Data()       ,EnergyA.Data()) );
    tree_br_Map_A_JetFraction[JetFraction[i].Data()] =     new TTree(TString::Format("%s_%s", JetFraction[i].Data(),EnergyA.Data()), TString::Format("%s_%s", JetFraction[i].Data(),EnergyA.Data()) );
    tree_br_Map_B_JetAng[JetAng[i].Data()] =               new TTree(TString::Format("%s_%s", JetAng[i].Data()     ,EnergyB.Data()), TString::Format("%s_%s", JetAng[i].Data()     ,EnergyB.Data()) );
    tree_br_Map_B_JetPt[JetPt[i].Data() ]  =               new TTree(TString::Format("%s_%s", JetPt[i].Data()      ,EnergyB.Data()), TString::Format("%s_%s", JetPt[i].Data()      ,EnergyB.Data()) );
    tree_br_Map_B_JetEta[JetEta[i].Data()] =               new TTree(TString::Format("%s_%s", JetEta[i].Data()     ,EnergyB.Data()), TString::Format("%s_%s", JetEta[i].Data()     ,EnergyB.Data()) );
    tree_br_Map_B_JetPhi[JetPhi[i].Data()] =               new TTree(TString::Format("%s_%s", JetPhi[i].Data()     ,EnergyB.Data()), TString::Format("%s_%s", JetPhi[i].Data()     ,EnergyB.Data()) );
    tree_br_Map_B_JetE[JetE[i].Data()]     =               new TTree(TString::Format("%s_%s", JetE[i].Data()       ,EnergyB.Data()), TString::Format("%s_%s", JetE[i].Data()       ,EnergyB.Data()) );
    tree_br_Map_B_JetFraction[JetFraction[i].Data()] =     new TTree(TString::Format("%s_%s", JetFraction[i].Data(),EnergyB.Data()), TString::Format("%s_%s", JetFraction[i].Data(),EnergyB.Data()) );

    tree_br_Map_A_mmdt_JetAng[mmdt_JetAng[i].Data()] =               new TTree(TString::Format("%s_%s", mmdt_JetAng[i].Data()     ,EnergyA.Data()), TString::Format("%s_%s", mmdt_JetAng[i].Data()     ,EnergyA.Data())  );
    tree_br_Map_A_mmdt_JetPt[mmdt_JetPt[i].Data()]   =               new TTree(TString::Format("%s_%s", mmdt_JetPt[i].Data()      ,EnergyA.Data()), TString::Format("%s_%s", mmdt_JetPt[i].Data()      ,EnergyA.Data())  );
    tree_br_Map_A_mmdt_JetEta[mmdt_JetEta[i].Data()] =               new TTree(TString::Format("%s_%s", mmdt_JetEta[i].Data()     ,EnergyA.Data()), TString::Format("%s_%s", mmdt_JetEta[i].Data()     ,EnergyA.Data())  );
    tree_br_Map_A_mmdt_JetPhi[mmdt_JetPhi[i].Data()] =               new TTree(TString::Format("%s_%s", mmdt_JetPhi[i].Data()     ,EnergyA.Data()), TString::Format("%s_%s", mmdt_JetPhi[i].Data()     ,EnergyA.Data())  );
    tree_br_Map_A_mmdt_JetE[mmdt_JetE[i].Data()]     =               new TTree(TString::Format("%s_%s", mmdt_JetE[i].Data()       ,EnergyA.Data()), TString::Format("%s_%s", mmdt_JetE[i].Data()       ,EnergyA.Data())  );
    tree_br_Map_A_mmdt_JetFraction[mmdt_JetFraction[i].Data()] =     new TTree(TString::Format("%s_%s", mmdt_JetFraction[i].Data(),EnergyA.Data()), TString::Format("%s_%s", mmdt_JetFraction[i].Data(),EnergyA.Data())  );
    tree_br_Map_B_mmdt_JetAng[mmdt_JetAng[i].Data()] =               new TTree(TString::Format("%s_%s", mmdt_JetAng[i].Data()     ,EnergyB.Data()), TString::Format("%s_%s", mmdt_JetAng[i].Data()     ,EnergyB.Data())  );
    tree_br_Map_B_mmdt_JetPt[mmdt_JetPt[i].Data()]   =               new TTree(TString::Format("%s_%s", mmdt_JetPt[i].Data()      ,EnergyB.Data()), TString::Format("%s_%s", mmdt_JetPt[i].Data()      ,EnergyB.Data())  );
    tree_br_Map_B_mmdt_JetEta[mmdt_JetEta[i].Data()] =               new TTree(TString::Format("%s_%s", mmdt_JetEta[i].Data()     ,EnergyB.Data()), TString::Format("%s_%s", mmdt_JetEta[i].Data()     ,EnergyB.Data())  );
    tree_br_Map_B_mmdt_JetPhi[mmdt_JetPhi[i].Data()] =               new TTree(TString::Format("%s_%s", mmdt_JetPhi[i].Data()     ,EnergyB.Data()), TString::Format("%s_%s", mmdt_JetPhi[i].Data()     ,EnergyB.Data())  );
    tree_br_Map_B_mmdt_JetE[mmdt_JetE[i].Data()]     =               new TTree(TString::Format("%s_%s", mmdt_JetE[i].Data()       ,EnergyB.Data()), TString::Format("%s_%s", mmdt_JetE[i].Data()       ,EnergyB.Data())  );
    tree_br_Map_B_mmdt_JetFraction[mmdt_JetFraction[i].Data()] =     new TTree(TString::Format("%s_%s", mmdt_JetFraction[i].Data(),EnergyB.Data()), TString::Format("%s_%s", mmdt_JetFraction[i].Data(),EnergyB.Data())  );


    br_Map_A_JetAng[JetAng[i].Data()] =               tree_br_Map_A_JetAng[JetAng[i].Data()]           ->Branch(TString::Format("%s",JetAng[i].Data()), &Map_A_JetAng[JetAng[i].Data()]);
    br_Map_A_JetPt[JetPt[i].Data()]   =               tree_br_Map_A_JetPt[JetPt[i].Data()]             ->Branch(TString::Format("%s",JetPt[i].Data()) , &Map_A_JetPt[JetPt[i].Data() ]);
    br_Map_A_JetEta[JetEta[i].Data()] =               tree_br_Map_A_JetEta[JetEta[i].Data()]           ->Branch(TString::Format("%s",JetEta[i].Data()), &Map_A_JetEta[JetEta[i].Data()]);
    br_Map_A_JetPhi[JetPhi[i].Data()] =               tree_br_Map_A_JetPhi[JetPhi[i].Data()]           ->Branch(TString::Format("%s",JetPhi[i].Data()), &Map_A_JetPhi[JetPhi[i].Data()]);
    br_Map_A_JetE[JetE[i].Data()]     =               tree_br_Map_A_JetE[JetE[i].Data()]               ->Branch(TString::Format("%s",JetE[i].Data()), &Map_A_JetE[JetE[i].Data()]);
    br_Map_A_JetFraction[JetFraction[i].Data()] =     tree_br_Map_A_JetFraction[JetFraction[i].Data()] ->Branch(TString::Format("%s",JetFraction[i].Data()), &Map_A_JetFraction[JetFraction[i].Data()]);
    br_Map_B_JetAng[JetAng[i].Data()] =               tree_br_Map_B_JetAng[JetAng[i].Data()]           ->Branch(TString::Format("%s",JetAng[i].Data()), &Map_B_JetAng[JetAng[i].Data()]);
    br_Map_B_JetPt[JetPt[i].Data() ]  =               tree_br_Map_B_JetPt[JetPt[i].Data() ]            ->Branch(TString::Format("%s",JetPt[i].Data()) , &Map_B_JetPt[JetPt[i].Data() ]);
    br_Map_B_JetEta[JetEta[i].Data()] =               tree_br_Map_B_JetEta[JetEta[i].Data()]           ->Branch(TString::Format("%s",JetEta[i].Data()), &Map_B_JetEta[JetEta[i].Data()]);
    br_Map_B_JetPhi[JetPhi[i].Data()] =               tree_br_Map_B_JetPhi[JetPhi[i].Data()]           ->Branch(TString::Format("%s",JetPhi[i].Data()), &Map_B_JetPhi[JetPhi[i].Data()]);
    br_Map_B_JetE[JetE[i].Data()]     =               tree_br_Map_B_JetE[JetE[i].Data()]               ->Branch(TString::Format("%s",JetE[i].Data()), &Map_B_JetE[JetE[i].Data()]);
    br_Map_B_JetFraction[JetFraction[i].Data()] =     tree_br_Map_B_JetFraction[JetFraction[i].Data()] ->Branch(TString::Format("%s",JetFraction[i].Data()), &Map_B_JetFraction[JetFraction[i].Data()]);

    br_Map_A_mmdt_JetAng[mmdt_JetAng[i].Data()] =               tree_br_Map_A_mmdt_JetAng[mmdt_JetAng[i].Data()]           ->Branch(TString::Format("%s",mmdt_JetAng[i].Data()), &Map_A_mmdt_JetAng[mmdt_JetAng[i].Data()]);
    br_Map_A_mmdt_JetPt[mmdt_JetPt[i].Data()]   =               tree_br_Map_A_mmdt_JetPt[mmdt_JetPt[i].Data()]             ->Branch(TString::Format("%s",mmdt_JetPt[i].Data() ), &Map_A_mmdt_JetPt[ mmdt_JetPt[i].Data() ]);
    br_Map_A_mmdt_JetEta[mmdt_JetEta[i].Data()] =               tree_br_Map_A_mmdt_JetEta[mmdt_JetEta[i].Data()]           ->Branch(TString::Format("%s",mmdt_JetEta[i].Data()), &Map_A_mmdt_JetEta[mmdt_JetEta[i].Data()]);
    br_Map_A_mmdt_JetPhi[mmdt_JetPhi[i].Data()] =               tree_br_Map_A_mmdt_JetPhi[mmdt_JetPhi[i].Data()]           ->Branch(TString::Format("%s",mmdt_JetPhi[i].Data()), &Map_A_mmdt_JetPhi[mmdt_JetPhi[i].Data()]);
    br_Map_A_mmdt_JetE[mmdt_JetE[i].Data()]     =               tree_br_Map_A_mmdt_JetE[mmdt_JetE[i].Data()]               ->Branch(TString::Format("%s",mmdt_JetE[i].Data()), &Map_A_mmdt_JetE[mmdt_JetE[i].Data()]);
    br_Map_A_mmdt_JetFraction[mmdt_JetFraction[i].Data()] =     tree_br_Map_A_mmdt_JetFraction[mmdt_JetFraction[i].Data()] ->Branch(TString::Format("%s",mmdt_JetFraction[i].Data()), &Map_A_mmdt_JetFraction[mmdt_JetFraction[i].Data()]);
    br_Map_B_mmdt_JetAng[mmdt_JetAng[i].Data()] =               tree_br_Map_B_mmdt_JetAng[mmdt_JetAng[i].Data()]           ->Branch(TString::Format("%s",mmdt_JetAng[i].Data()), &Map_B_mmdt_JetAng[mmdt_JetAng[i].Data()]);
    br_Map_B_mmdt_JetPt[mmdt_JetPt[i].Data()]   =               tree_br_Map_B_mmdt_JetPt[mmdt_JetPt[i].Data()]             ->Branch(TString::Format("%s",mmdt_JetPt[i].Data() ), &Map_B_mmdt_JetPt[ mmdt_JetPt[i].Data() ]);
    br_Map_B_mmdt_JetEta[mmdt_JetEta[i].Data()] =               tree_br_Map_B_mmdt_JetEta[mmdt_JetEta[i].Data()]           ->Branch(TString::Format("%s",mmdt_JetEta[i].Data()), &Map_B_mmdt_JetEta[mmdt_JetEta[i].Data()]);
    br_Map_B_mmdt_JetPhi[mmdt_JetPhi[i].Data()] =               tree_br_Map_B_mmdt_JetPhi[mmdt_JetPhi[i].Data()]           ->Branch(TString::Format("%s",mmdt_JetPhi[i].Data()), &Map_B_mmdt_JetPhi[mmdt_JetPhi[i].Data()]);
    br_Map_B_mmdt_JetE[mmdt_JetE[i].Data()]     =               tree_br_Map_B_mmdt_JetE[mmdt_JetE[i].Data()]               ->Branch(TString::Format("%s",mmdt_JetE[i].Data()), &Map_B_mmdt_JetE[mmdt_JetE[i].Data()]);
    br_Map_B_mmdt_JetFraction[mmdt_JetFraction[i].Data()] =     tree_br_Map_B_mmdt_JetFraction[mmdt_JetFraction[i].Data()] ->Branch(TString::Format("%s",mmdt_JetFraction[i].Data()), &Map_B_mmdt_JetFraction[mmdt_JetFraction[i].Data()]);

        

    }
    
    
    bool Fill = false;
    for (int i = 0; i < treeA->GetEntries();i++){
    //for (int i = 0; i < 100000;i++){
        treeA->GetEntry(i);
        if (i % 10000 == 0){
            cout << "Processing tree A " << i << "/" << treeA->GetEntries() << endl;
            //cout << "Processing " << i << "/1 000 000" << endl;
        }
        for (int j = 0 ; j < JetAng.size(); j++){
            //cout << JetAng[j].Data() << " " << Map_A_JetAng[JetAng[j].Data()]->size() << endl;
            for (int k = 0 ; k < Map_A_JetAng[JetAng[j].Data()]->size(); k++){
                //cout << "k = " << k << endl;
                //cout << JetAng[j].Data() << " = " << Map_A_JetAng[JetAng[j].Data()]->at(k) << endl;
                //cout << JetPt[j].Data() << " = " << Map_A_JetPt[JetPt[j].Data()]->at(k) << endl;
                //cout << JetEta[j].Data() << " = " << Map_A_JetEta[JetEta[j].Data()]->at(k) << endl;
                //cout << "Jet fraction = " << GetFraction(Map_A_JetPt[JetPt[j].Data()]->at(k), Map_A_JetEta[JetEta[j].Data()]->at(k), fractionA) << endl;
                Map_A_JetFraction[JetFraction[j].Data()]->push_back(
                    GetFraction(Map_A_JetPt[JetPt[j].Data()]->at(k), Map_A_JetEta[JetEta[j].Data()]->at(k), fractionA)
                                                                            );
                Fill = true;
            }
            if (Map_A_JetAng[JetAng[j].Data()]->size() > 0 ) tree_br_Map_A_JetAng[JetAng[j].Data()] ->Fill();
            if (Map_A_JetAng[JetAng[j].Data()]->size() > 0 ) tree_br_Map_A_JetPt[JetPt[j].Data()] ->Fill();
            if (Map_A_JetAng[JetAng[j].Data()]->size() > 0 ) tree_br_Map_A_JetEta[JetEta[j].Data()] ->Fill();
            if (Map_A_JetAng[JetAng[j].Data()]->size() > 0 ) tree_br_Map_A_JetPhi[JetPhi[j].Data()] ->Fill();
            if (Map_A_JetAng[JetAng[j].Data()]->size() > 0 ) tree_br_Map_A_JetE[JetE[j].Data()] ->Fill();
            if (Map_A_JetAng[JetAng[j].Data()]->size() > 0 ) {
                                                        tree_br_Map_A_JetFraction[JetFraction[j].Data()] ->Fill();
                                                        Map_A_JetFraction[JetFraction[j].Data()]->clear();
                                                             }
            for (int k = 0 ; k < Map_A_mmdt_JetAng[mmdt_JetAng[j].Data()]->size(); k++){
                //cout << "mmdt k = " << k << endl;
                //cout << mmdt_JetAng[j].Data() << " = " << Map_A_mmdt_JetAng[mmdt_JetAng[j].Data()]->at(k) << endl;
                //cout << mmdt_JetPt[j].Data() << " = " << Map_A_mmdt_JetPt[mmdt_JetPt[j].Data()]->at(k) << endl;
                //cout << mmdt_JetEta[j].Data() << " = " << Map_A_mmdt_JetEta[mmdt_JetEta[j].Data()]->at(k) << endl;
                //cout << "Jet fraction = " << GetFraction(Map_A_mmdt_JetPt[mmdt_JetPt[j].Data()]->at(k), Map_A_mmdt_JetEta[mmdt_JetEta[j].Data()]->at(k), fractionA) << endl;
                Map_A_mmdt_JetFraction[mmdt_JetFraction[j].Data()]->push_back(
                    GetFraction(Map_A_mmdt_JetPt[mmdt_JetPt[j].Data()]->at(k), Map_A_mmdt_JetEta[mmdt_JetEta[j].Data()]->at(k), fractionA)
                                                                            );
                Fill = true;
            }
            if (Map_A_mmdt_JetAng[mmdt_JetAng[j].Data()]->size() > 0 ) tree_br_Map_A_mmdt_JetAng[mmdt_JetAng[j].Data()] ->Fill();
            if (Map_A_mmdt_JetAng[mmdt_JetAng[j].Data()]->size() > 0 ) tree_br_Map_A_mmdt_JetPt[ mmdt_JetPt[j].Data()] ->Fill();
            if (Map_A_mmdt_JetAng[mmdt_JetAng[j].Data()]->size() > 0 ) tree_br_Map_A_mmdt_JetEta[mmdt_JetEta[j].Data()] ->Fill();
            if (Map_A_mmdt_JetAng[mmdt_JetAng[j].Data()]->size() > 0 ) tree_br_Map_A_mmdt_JetPhi[mmdt_JetPhi[j].Data()] ->Fill();
            if (Map_A_mmdt_JetAng[mmdt_JetAng[j].Data()]->size() > 0 ) tree_br_Map_A_mmdt_JetE[mmdt_JetE[j].Data()] ->Fill();
            if (Map_A_mmdt_JetAng[mmdt_JetAng[j].Data()]->size() > 0 ) {
                                                        tree_br_Map_A_mmdt_JetFraction[mmdt_JetFraction[j].Data()] ->Fill();
                                                        Map_A_mmdt_JetFraction[mmdt_JetFraction[j].Data()]->clear();
                                                             }
        }
        //if (Fill ) tree_outA->Fill();
        Fill = false;
        for (int j = 0 ; j < JetAng.size(); j++){
            for (int k = 0 ; k < Map_A_JetAng[JetAng[j].Data()]->size(); k++){
                Map_A_JetFraction[JetFraction[j].Data()]->clear();
            }
            for (int k = 0 ; k < Map_A_mmdt_JetAng[mmdt_JetAng[j].Data()]->size(); k++){
                Map_A_mmdt_JetFraction[mmdt_JetFraction[j].Data()]->clear();
            }

        }


    }

    //tree_outA->Write();

    for (int i = 0; i < treeB->GetEntries();i++){
    //for (int i = 0; i < 100000;i++){
        treeB->GetEntry(i);
        if (i % 10000 == 0){
            cout << "Processing tree B " << i << "/" << treeB->GetEntries() << endl;
            //cout << "Processing " << i << "/1 000 000" << endl;
        }
        for (int j = 0 ; j < JetAng.size(); j++){
            //cout << JetAng[j].Data() << " " << Map_B_JetAng[JetAng[j].Data()]->size() << endl;
            for (int k = 0 ; k < Map_B_JetAng[JetAng[j].Data()]->size(); k++){
                //cout << "k = " << k << endl;
                //cout << JetAng[j].Data() << " = " << Map_B_JetAng[JetAng[j].Data()]->at(k) << endl;
                //cout << JetPt[j].Data() << " = " << Map_B_JetPt[JetPt[j].Data()]->at(k) << endl;
                //cout << JetEta[j].Data() << " = " << Map_B_JetEta[JetEta[j].Data()]->at(k) << endl;
                //cout << "Jet fraction = " << GetFraction(Map_B_JetPt[JetPt[j].Data()]->at(k), Map_B_JetEta[JetEta[j].Data()]->at(k), fractionA) << endl;
                Map_B_JetFraction[JetFraction[j].Data()]->push_back(
                    GetFraction(Map_B_JetPt[JetPt[j].Data()]->at(k), Map_B_JetEta[JetEta[j].Data()]->at(k), fractionA)
                                                                            );
                Fill = true;
            }
            if (Map_B_JetAng[JetAng[j].Data()]->size() > 0 ) tree_br_Map_B_JetAng[JetAng[j].Data()] ->Fill();
            if (Map_B_JetAng[JetAng[j].Data()]->size() > 0 ) tree_br_Map_B_JetPt[JetPt[j].Data()] ->Fill();
            if (Map_B_JetAng[JetAng[j].Data()]->size() > 0 ) tree_br_Map_B_JetEta[JetEta[j].Data()] ->Fill();
            if (Map_B_JetAng[JetAng[j].Data()]->size() > 0 ) tree_br_Map_B_JetPhi[JetPhi[j].Data()] ->Fill();
            if (Map_B_JetAng[JetAng[j].Data()]->size() > 0 ) tree_br_Map_B_JetE[JetE[j].Data()] ->Fill();
            if (Map_B_JetAng[JetAng[j].Data()]->size() > 0 ) {
                                                        tree_br_Map_B_JetFraction[JetFraction[j].Data()] ->Fill();
                                                        Map_B_JetFraction[JetFraction[j].Data()]->clear();
                                                             }
            for (int k = 0 ; k < Map_B_mmdt_JetAng[mmdt_JetAng[j].Data()]->size(); k++){
                //cout << "mmdt k = " << k << endl;
                //cout << mmdt_JetAng[j].Data() << " = " << Map_B_mmdt_JetAng[mmdt_JetAng[j].Data()]->at(k) << endl;
                //cout << mmdt_JetPt[j].Data() << " = " << Map_B_mmdt_JetPt[mmdt_JetPt[j].Data()]->at(k) << endl;
                //cout << mmdt_JetEta[j].Data() << " = " << Map_B_mmdt_JetEta[mmdt_JetEta[j].Data()]->at(k) << endl;
                //cout << "Jet fraction = " << GetFraction(Map_B_mmdt_JetPt[mmdt_JetPt[j].Data()]->at(k), Map_B_mmdt_JetEta[mmdt_JetEta[j].Data()]->at(k), fractionA) << endl;
                Map_B_mmdt_JetFraction[mmdt_JetFraction[j].Data()]->push_back(
                    GetFraction(Map_B_mmdt_JetPt[mmdt_JetPt[j].Data()]->at(k), Map_B_mmdt_JetEta[mmdt_JetEta[j].Data()]->at(k), fractionB)
                                                                            );
                Fill = true;
            }
            if (Map_B_mmdt_JetAng[mmdt_JetAng[j].Data()]->size() > 0 ) tree_br_Map_B_mmdt_JetAng[mmdt_JetAng[j].Data()] ->Fill();
            if (Map_B_mmdt_JetAng[mmdt_JetAng[j].Data()]->size() > 0 ) tree_br_Map_B_mmdt_JetPt[ mmdt_JetPt[j].Data()] ->Fill();
            if (Map_B_mmdt_JetAng[mmdt_JetAng[j].Data()]->size() > 0 ) tree_br_Map_B_mmdt_JetEta[mmdt_JetEta[j].Data()] ->Fill();
            if (Map_B_mmdt_JetAng[mmdt_JetAng[j].Data()]->size() > 0 ) tree_br_Map_B_mmdt_JetPhi[mmdt_JetPhi[j].Data()] ->Fill();
            if (Map_B_mmdt_JetAng[mmdt_JetAng[j].Data()]->size() > 0 ) tree_br_Map_B_mmdt_JetE[mmdt_JetE[j].Data()] ->Fill();
            if (Map_B_mmdt_JetAng[mmdt_JetAng[j].Data()]->size() > 0 ) {
                                                        tree_br_Map_B_mmdt_JetFraction[mmdt_JetFraction[j].Data()] ->Fill();
                                                        Map_B_mmdt_JetFraction[mmdt_JetFraction[j].Data()]->clear();
                                                             }
            //if (Map_B_JetAng[JetAng[j].Data()]->size() > 0) tree_outB->Fill();
        }
        //if (Fill) tree_outB->Fill();
        Fill = false;
        for (int j = 0 ; j < JetAng.size(); j++){
            for (int k = 0 ; k < Map_B_JetAng[JetAng[j].Data()]->size(); k++){
                Map_B_JetFraction[JetFraction[j].Data()]->clear();
            }
            for (int k = 0 ; k < Map_B_mmdt_JetAng[mmdt_JetAng[j].Data()]->size(); k++){
                Map_B_mmdt_JetFraction[mmdt_JetFraction[j].Data()]->clear();
            }

        }


    }

    //tree_outB->Write();
    fractionA->Write();
    fractionB->Write();
    
    output->Write();

    return 0;
}

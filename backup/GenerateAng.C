int GenerateAng(TString EnergyA = "900", TString EnergyB = "2360"){

    TFile * rfile = new TFile(TString::Format("out_test_%s_%s.root", EnergyA.Data(), EnergyB.Data()), "read");

    TH2F * fracA = (TH2F*)rfile->Get(TString::Format("GluonFraction_%s", EnergyA.Data() ));
    TH2F * fracB = (TH2F*)rfile->Get(TString::Format("GluonFraction_%s", EnergyB.Data() ));

    double CutPtLow, CutPtUp, CutEtaLow, CutEtaUp;
    double ScaleA, ScaleB;

    vector<TString> Radii;
    vector<TString> Lambdas;
    vector<TString> Q;

    Q.push_back("50");
    //Q.push_back("100");
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
    vector<TString> JetFraction;

    vector<TString> mmdt_JetAng;
    vector<TString> mmdt_JetPt;
    vector<TString> mmdt_JetEta;
    vector<TString> mmdt_JetFraction;

    std::map<TString, TTree*> TreeMapA;
    std::map<TString, TTree*> TreeMapB;

    std::map<TString, vector<TH1D*>> h_MapA_Quark;
    std::map<TString, vector<TH1D*>> h_MapB_Quark;

    std::map<TString, vector<TH1D*>> h_MapA_Gluon;
    std::map<TString, vector<TH1D*>> h_MapB_Gluon;

    std::map<TString, vector<TH1D*>> h_no_cut_Map_Gluon;
    std::map<TString, vector<TH1D*>> h_no_cut_Map_Quark;


    for (int i = 0; i < Radii.size();i++){
        for (int j = 0; j < Lambdas.size();j++){
            for (int k = 0; k < Q.size();k++){
                JetAng.push_back( TString::Format("FastJets%s%sLam%s", Radii[i].Data(), Lambdas[j].Data(), Q[k].Data() ) );
                JetPt.push_back( TString::Format("FastJets%sPt", Radii[i].Data() ) );
                JetEta.push_back( TString::Format("FastJets%sEta", Radii[i].Data() ) );
                JetFraction.push_back( TString::Format("FastJets%sFraction", Radii[i].Data() ) );
                

                mmdt_JetAng.push_back( TString::Format("mmdt_FastJets%s%sLam%s", Radii[i].Data(), Lambdas[j].Data(), Q[k].Data() ) );
                mmdt_JetPt.push_back(  TString::Format("mmdt_FastJets%sPt", Radii[i].Data() ) );
                mmdt_JetEta.push_back( TString::Format("mmdt_FastJets%sEta", Radii[i].Data() ) );
                mmdt_JetFraction.push_back( TString::Format("mmdt_FastJets%sFraction", Radii[i].Data() ) );
            }
        }
    }


    for (int i = 0; i<JetAng.size(); i++){
        TreeMapA[JetAng[i]]           = (TTree*)rfile->Get(TString::Format("%s_%s", JetAng[i].Data(), EnergyA.Data()));
        TreeMapA[JetPt[i]]            = (TTree*)rfile->Get(TString::Format("%s_%s", JetPt[i].Data(), EnergyA.Data()));
        TreeMapA[JetEta[i]]           = (TTree*)rfile->Get(TString::Format("%s_%s", JetEta[i].Data(), EnergyA.Data()));
        TreeMapA[JetFraction[i]]      = (TTree*)rfile->Get(TString::Format("%s_%s", JetFraction[i].Data(), EnergyA.Data()));
        TreeMapA[mmdt_JetAng[i]]      = (TTree*)rfile->Get(TString::Format("%s_%s", mmdt_JetAng[i].Data(), EnergyA.Data()));
        TreeMapA[mmdt_JetPt[i]]       = (TTree*)rfile->Get(TString::Format("%s_%s", mmdt_JetPt[i].Data(), EnergyA.Data()));
        TreeMapA[mmdt_JetEta[i]]      = (TTree*)rfile->Get(TString::Format("%s_%s", mmdt_JetEta[i].Data(), EnergyA.Data()));
        TreeMapA[mmdt_JetFraction[i]] = (TTree*)rfile->Get(TString::Format("%s_%s", mmdt_JetFraction[i].Data(), EnergyA.Data()));

        TreeMapB[JetAng[i]]           = (TTree*)rfile->Get(TString::Format("%s_%s", JetAng[i].Data(), EnergyB.Data()));
        TreeMapB[JetPt[i]]            = (TTree*)rfile->Get(TString::Format("%s_%s", JetPt[i].Data(), EnergyB.Data()));
        TreeMapB[JetEta[i]]           = (TTree*)rfile->Get(TString::Format("%s_%s", JetEta[i].Data(), EnergyB.Data()));
        TreeMapB[JetFraction[i]]      = (TTree*)rfile->Get(TString::Format("%s_%s", JetFraction[i].Data(), EnergyB.Data()));
        TreeMapB[mmdt_JetAng[i]]      = (TTree*)rfile->Get(TString::Format("%s_%s", mmdt_JetAng[i].Data(), EnergyB.Data()));
        TreeMapB[mmdt_JetPt[i]]       = (TTree*)rfile->Get(TString::Format("%s_%s", mmdt_JetPt[i].Data(), EnergyB.Data()));
        TreeMapB[mmdt_JetEta[i]]      = (TTree*)rfile->Get(TString::Format("%s_%s", mmdt_JetEta[i].Data(), EnergyB.Data()));
        TreeMapB[mmdt_JetFraction[i]] = (TTree*)rfile->Get(TString::Format("%s_%s", mmdt_JetFraction[i].Data(), EnergyB.Data()));

        TreeMapA[JetAng[i]]     ->AddFriend(TreeMapA[JetPt[i]]           );
        TreeMapA[JetAng[i]]     ->AddFriend(TreeMapA[JetEta[i]]          );
        TreeMapA[JetAng[i]]     ->AddFriend(TreeMapA[JetFraction[i]]     );
        TreeMapA[JetAng[i]]     ->AddFriend(TreeMapA[mmdt_JetAng[i]]     );
        TreeMapA[JetAng[i]]     ->AddFriend(TreeMapA[mmdt_JetPt[i]]      );
        TreeMapA[JetAng[i]]     ->AddFriend(TreeMapA[mmdt_JetEta[i]]     );
        TreeMapA[JetAng[i]]     ->AddFriend(TreeMapA[mmdt_JetFraction[i]]);

        TreeMapA[JetAng[i]]     ->AddFriend(TreeMapB[JetAng[i]]          );
        TreeMapA[JetAng[i]]     ->AddFriend(TreeMapB[JetPt[i]]           );
        TreeMapA[JetAng[i]]     ->AddFriend(TreeMapB[JetEta[i]]          );
        TreeMapA[JetAng[i]]     ->AddFriend(TreeMapB[JetFraction[i]]     );
        TreeMapA[JetAng[i]]     ->AddFriend(TreeMapB[mmdt_JetAng[i]]     );
        TreeMapA[JetAng[i]]     ->AddFriend(TreeMapB[mmdt_JetPt[i]]      );
        TreeMapA[JetAng[i]]     ->AddFriend(TreeMapB[mmdt_JetEta[i]]     );
        TreeMapA[JetAng[i]]     ->AddFriend(TreeMapB[mmdt_JetFraction[i]]);

        TreeMapA[mmdt_JetAng[i]]     ->AddFriend(TreeMapA[JetPt[i]]           );
        TreeMapA[mmdt_JetAng[i]]     ->AddFriend(TreeMapA[JetEta[i]]          );
        TreeMapA[mmdt_JetAng[i]]     ->AddFriend(TreeMapA[JetFraction[i]]     );
        TreeMapA[mmdt_JetAng[i]]     ->AddFriend(TreeMapA[JetAng[i]]     );
        TreeMapA[mmdt_JetAng[i]]     ->AddFriend(TreeMapA[mmdt_JetPt[i]]      );
        TreeMapA[mmdt_JetAng[i]]     ->AddFriend(TreeMapA[mmdt_JetEta[i]]     );
        TreeMapA[mmdt_JetAng[i]]     ->AddFriend(TreeMapA[mmdt_JetFraction[i]]);

        TreeMapA[mmdt_JetAng[i]]     ->AddFriend(TreeMapB[JetAng[i]]          );
        TreeMapA[mmdt_JetAng[i]]     ->AddFriend(TreeMapB[JetPt[i]]           );
        TreeMapA[mmdt_JetAng[i]]     ->AddFriend(TreeMapB[JetEta[i]]          );
        TreeMapA[mmdt_JetAng[i]]     ->AddFriend(TreeMapB[JetFraction[i]]     );
        TreeMapA[mmdt_JetAng[i]]     ->AddFriend(TreeMapB[JetAng[i]]     );
        TreeMapA[mmdt_JetAng[i]]     ->AddFriend(TreeMapB[mmdt_JetPt[i]]      );
        TreeMapA[mmdt_JetAng[i]]     ->AddFriend(TreeMapB[mmdt_JetEta[i]]     );
        TreeMapA[mmdt_JetAng[i]]     ->AddFriend(TreeMapB[mmdt_JetFraction[i]]);

        //
        TreeMapB[JetAng[i]]     ->AddFriend(TreeMapB[JetPt[i]]           );
        TreeMapB[JetAng[i]]     ->AddFriend(TreeMapB[JetEta[i]]          );
        TreeMapB[JetAng[i]]     ->AddFriend(TreeMapB[JetFraction[i]]     );
        TreeMapB[JetAng[i]]     ->AddFriend(TreeMapB[mmdt_JetAng[i]]     );
        TreeMapB[JetAng[i]]     ->AddFriend(TreeMapB[mmdt_JetPt[i]]      );
        TreeMapB[JetAng[i]]     ->AddFriend(TreeMapB[mmdt_JetEta[i]]     );
        TreeMapB[JetAng[i]]     ->AddFriend(TreeMapB[mmdt_JetFraction[i]]);

        TreeMapB[JetAng[i]]     ->AddFriend(TreeMapA[JetAng[i]]          );
        TreeMapB[JetAng[i]]     ->AddFriend(TreeMapA[JetPt[i]]           );
        TreeMapB[JetAng[i]]     ->AddFriend(TreeMapA[JetEta[i]]          );
        TreeMapB[JetAng[i]]     ->AddFriend(TreeMapA[JetFraction[i]]     );
        TreeMapB[JetAng[i]]     ->AddFriend(TreeMapA[mmdt_JetAng[i]]     );
        TreeMapB[JetAng[i]]     ->AddFriend(TreeMapA[mmdt_JetPt[i]]      );
        TreeMapB[JetAng[i]]     ->AddFriend(TreeMapA[mmdt_JetEta[i]]     );
        TreeMapB[JetAng[i]]     ->AddFriend(TreeMapA[mmdt_JetFraction[i]]);

        TreeMapB[mmdt_JetAng[i]]     ->AddFriend(TreeMapB[JetPt[i]]           );
        TreeMapB[mmdt_JetAng[i]]     ->AddFriend(TreeMapB[JetEta[i]]          );
        TreeMapB[mmdt_JetAng[i]]     ->AddFriend(TreeMapB[JetFraction[i]]     );
        TreeMapB[mmdt_JetAng[i]]     ->AddFriend(TreeMapB[JetAng[i]]     );
        TreeMapB[mmdt_JetAng[i]]     ->AddFriend(TreeMapB[mmdt_JetPt[i]]      );
        TreeMapB[mmdt_JetAng[i]]     ->AddFriend(TreeMapB[mmdt_JetEta[i]]     );
        TreeMapB[mmdt_JetAng[i]]     ->AddFriend(TreeMapB[mmdt_JetFraction[i]]);

        TreeMapB[mmdt_JetAng[i]]     ->AddFriend(TreeMapA[JetAng[i]]          );
        TreeMapB[mmdt_JetAng[i]]     ->AddFriend(TreeMapA[JetPt[i]]           );
        TreeMapB[mmdt_JetAng[i]]     ->AddFriend(TreeMapA[JetEta[i]]          );
        TreeMapB[mmdt_JetAng[i]]     ->AddFriend(TreeMapA[JetFraction[i]]     );
        TreeMapB[mmdt_JetAng[i]]     ->AddFriend(TreeMapA[JetAng[i]]     );
        TreeMapB[mmdt_JetAng[i]]     ->AddFriend(TreeMapA[mmdt_JetPt[i]]      );
        TreeMapB[mmdt_JetAng[i]]     ->AddFriend(TreeMapA[mmdt_JetEta[i]]     );
        TreeMapB[mmdt_JetAng[i]]     ->AddFriend(TreeMapA[mmdt_JetFraction[i]]);
        

    }

    double fracA_no_cut = fracA->ProjectionX()->GetBinContent(fracA->ProjectionX()->GetXaxis()->FindBin(55.5) ) / 10.;
    double fracB_no_cut = fracB->ProjectionX()->GetBinContent(fracB->ProjectionX()->GetXaxis()->FindBin(55.5) ) / 10.;

    TString Cut;
    TH1D * h;
    TH1D * h2;

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
    int neg_index;
    for (int k = 0; k<JetAng.size(); k++){
    //for (int k = 0; k<1; k++){
    for (int i = 1; i<=fracA->GetXaxis()->GetNbins(); i++){
        neg_index = 5;
        for (int j = 6; j<=fracA->GetYaxis()->GetNbins(); j++){ //from 6 due to positive part of eta and averaging two jets pt and eta
        CutPtLow = fracA->GetXaxis()->GetBinLowEdge(i);
        CutPtUp = fracA->GetXaxis()->GetBinUpEdge(i);
        CutEtaLow = fracA->GetYaxis()->GetBinLowEdge(j);
        CutEtaUp = fracA->GetYaxis()->GetBinUpEdge(j);
        ScaleA = 0.5*(fracA->GetBinContent(i,j) + fracA->GetBinContent(i,neg_index));//6-5,7-4,8-3,9-2,10-1
        ScaleB = 0.5*(fracB->GetBinContent(i,j) + fracB->GetBinContent(i,neg_index));//6-5,7-4,8-3,9-2,10-1
        neg_index = neg_index -1;
            Cut = TString::Format("(0.5*(%s.%s[0]+%s.%s[1]) > %f)&&(0.5*(%s.%s[0]+%s.%s[1]) < %f)&&(0.5*(TMath::Abs(%s.%s[0]) + TMath::Abs(%s.%s[1]))  > %f)&&(0.5*(TMath::Abs(%s.%s[0]) + TMath::Abs(%s.%s[1])) < %f)", 
                                    TreeMapA[JetPt[k]]->GetName(),JetPt[k].Data(),TreeMapA[JetPt[k]]->GetName(),JetPt[k].Data(),
                                    CutPtLow, 
                                    TreeMapA[JetPt[k]]->GetName(), JetPt[k].Data(), TreeMapA[JetPt[k]]->GetName(), JetPt[k].Data(), 
                                    CutPtUp,
                                    TreeMapA[JetEta[k]]->GetName(),JetEta[k].Data(), TreeMapA[JetEta[k]]->GetName(),JetEta[k].Data(), 
                                    CutEtaLow, 
                                    TreeMapA[JetEta[k]]->GetName(), JetEta[k].Data(), TreeMapA[JetEta[k]]->GetName(), JetEta[k].Data(), 
                                    CutEtaUp);
            
            //Cut = "";
            if (JetAng[k].Contains("MultLam")){
                TreeMapA[JetAng[k]]          ->Draw(TString::Format("%s >> h_%s_%i_%i_%i(50,0,100)", JetAng[k].Data() , JetAng[k].Data(), i,j,k), Cut.Data() , "goff"); 
                if ((i==1)&&(j==6)) TreeMapA[JetAng[k]]->Draw(TString::Format("%s >> h_no_cut_%s(50,0,100)", JetAng[k].Data() , JetAng[k].Data()), "" , "goff"); 
            }else{
                TreeMapA[JetAng[k]]          ->Draw(TString::Format("%s >> h_%s_%i_%i_%i(50,0,1)", JetAng[k].Data() , JetAng[k].Data(), i,j,k), Cut.Data() , "goff"); 
                if ((i==1)&&(j==6)) TreeMapA[JetAng[k]]->Draw(TString::Format("%s >> h_no_cut_%s(50,0,1)", JetAng[k].Data() , JetAng[k].Data()), "" , "goff"); 
            }
            h = (TH1D*)gDirectory->Get(TString::Format("h_%s_%i_%i_%i", JetAng[k].Data(), i,j,k));
            h2= (TH1D*)h->Clone(TString::Format("%s_clone", h->GetName()));
            if ((i==1)&&(j==6)) h_no_cutA=(TH1D*)gDirectory->Get(TString::Format("h_no_cut_%s", JetAng[k].Data()));

            if ((ScaleA-ScaleB)!=0) {h->Scale(-1*(ScaleB)/(ScaleA-ScaleB));}else{
                h->Scale(0.);
            };
            h_MapA_Quark[JetAng[k].Data()].push_back(h);
            if ((ScaleA-ScaleB)!=0) {h2->Scale((1-ScaleB)/(ScaleA-ScaleB));}else{
                h2->Scale(0);
            };
            h_MapA_Gluon[JetAng[k].Data()].push_back(h2);

            //if (h->Integral()>0.){cout << h->Integral() <<endl;
            //cout << TreeMapA[JetAng[k]]->GetName() << "->Draw(" << JetAng[k] << ",\"" << Cut.Data() <<"\")" << endl;}
            Cut = TString::Format("(0.5*(%s.%s[0]+%s.%s[1]) > %f)&&(0.5*(%s.%s[0]+%s.%s[1]) < %f)&&(0.5*(TMath::Abs(%s.%s[0]) + TMath::Abs(%s.%s[1]))  > %f)&&(0.5*(TMath::Abs(%s.%s[0]) + TMath::Abs(%s.%s[1])) < %f)", 
                                    TreeMapA[mmdt_JetPt[k]]->GetName(),mmdt_JetPt[k].Data(),TreeMapA[mmdt_JetPt[k]]->GetName(),mmdt_JetPt[k].Data(),
                                    CutPtLow, 
                                    TreeMapA[mmdt_JetPt[k]]->GetName(), mmdt_JetPt[k].Data(), TreeMapA[mmdt_JetPt[k]]->GetName(), mmdt_JetPt[k].Data(), 
                                    CutPtUp,
                                    TreeMapA[mmdt_JetEta[k]]->GetName(),mmdt_JetEta[k].Data(), TreeMapA[mmdt_JetEta[k]]->GetName(),mmdt_JetEta[k].Data(), 
                                    CutEtaLow, 
                                    TreeMapA[mmdt_JetEta[k]]->GetName(), mmdt_JetEta[k].Data(), TreeMapA[mmdt_JetEta[k]]->GetName(), mmdt_JetEta[k].Data(), 
                                    CutEtaUp);
            //Cut = TString::Format("(%s.%s > %f)&&(%s.%s < %f)&&(%s.%s > %f)&&(%s.%s < %f)", 
            //            TreeMapA[mmdt_JetPt[k]]->GetName(),mmdt_JetPt[k].Data(), CutPtLow, TreeMapA[mmdt_JetPt[k]]->GetName(), mmdt_JetPt[k].Data(), CutPtUp,
            //            TreeMapA[mmdt_JetEta[k]]->GetName(),mmdt_JetEta[k].Data(), CutEtaLow, TreeMapA[mmdt_JetEta[k]]->GetName(), mmdt_JetEta[k].Data(), CutEtaUp);
            if (mmdt_JetAng[k].Contains("MultLam")){
                TreeMapA[mmdt_JetAng[k]]     ->Draw(TString::Format("%s >> h_%s_%i_%i_%i(50,0,100)", mmdt_JetAng[k].Data() , mmdt_JetAng[k].Data(), i,j,k), Cut.Data() , "goff");
                if ((i==1)&&(j==6))TreeMapA[mmdt_JetAng[k]]->Draw(TString::Format("%s >> h_no_cut_%s(50,0,100)", mmdt_JetAng[k].Data() , mmdt_JetAng[k].Data()), "" , "goff"); 
            }else{
                TreeMapA[mmdt_JetAng[k]]     ->Draw(TString::Format("%s >> h_%s_%i_%i_%i(50,0,1)", mmdt_JetAng[k].Data() , mmdt_JetAng[k].Data(), i,j,k), Cut.Data() , "goff");
                if ((i==1)&&(j==6))TreeMapA[mmdt_JetAng[k]]->Draw(TString::Format("%s >> h_no_cut_%s(50,0,1)", mmdt_JetAng[k].Data() , mmdt_JetAng[k].Data()), "" , "goff"); 
            }
            h = (TH1D*)gDirectory->Get(TString::Format("h_%s_%i_%i_%i", mmdt_JetAng[k].Data(), i,j,k));
            h2= (TH1D*)h->Clone(TString::Format("%s_clone", h->GetName()));
            if ((i==1)&&(j==6)) h_no_cutA_mmdt=(TH1D*)gDirectory->Get(TString::Format("h_no_cut_%s", mmdt_JetAng[k].Data()));
            if ((ScaleA-ScaleB)!=0) {h->Scale(-1*(ScaleB)/(ScaleA-ScaleB));}else{
                h->Scale(0.);
            };
            h_MapA_Quark[mmdt_JetAng[k].Data()].push_back(h);
            if ((ScaleA-ScaleB)!=0) {h2->Scale((1-ScaleB)/(ScaleA-ScaleB));}else{
                h2->Scale(0.);
            };
            h_MapA_Gluon[mmdt_JetAng[k].Data()].push_back(h2);
            //Cut = TString::Format("(%s.%s > %f)&&(%s.%s < %f)&&(%s.%s > %f)&&(%s.%s < %f)", 
            //            TreeMapB[JetPt[k]]->GetName(),JetPt[k].Data(), CutPtLow, TreeMapB[JetPt[k]]->GetName(), JetPt[k].Data(), CutPtUp,
            //            TreeMapB[JetEta[k]]->GetName(),JetEta[k].Data(), CutEtaLow, TreeMapB[JetEta[k]]->GetName(), JetEta[k].Data(), CutEtaUp);

            Cut = TString::Format("(0.5*(%s.%s[0]+%s.%s[1]) > %f)&&(0.5*(%s.%s[0]+%s.%s[1]) < %f)&&(0.5*(TMath::Abs(%s.%s[0]) + TMath::Abs(%s.%s[1]))  > %f)&&(0.5*(TMath::Abs(%s.%s[0]) + TMath::Abs(%s.%s[1])) < %f)", 
                                    TreeMapB[JetPt[k]]->GetName(),JetPt[k].Data(),TreeMapB[JetPt[k]]->GetName(),JetPt[k].Data(),
                                    CutPtLow, 
                                    TreeMapB[JetPt[k]]->GetName(), JetPt[k].Data(), TreeMapB[JetPt[k]]->GetName(), JetPt[k].Data(), 
                                    CutPtUp,
                                    TreeMapB[JetEta[k]]->GetName(),JetEta[k].Data(), TreeMapB[JetEta[k]]->GetName(),JetEta[k].Data(), 
                                    CutEtaLow, 
                                    TreeMapB[JetEta[k]]->GetName(), JetEta[k].Data(), TreeMapB[JetEta[k]]->GetName(), JetEta[k].Data(), 
                                    CutEtaUp);

            //TreeMapB[JetAng[k]]          ->Draw(JetAng[k]          .Data(), Cut.Data() , "goff");
            if (JetAng[k].Contains("MultLam")){
                TreeMapB[JetAng[k]]          ->Draw(TString::Format("%s >> hB_%s_%i_%i_%i(50,0,100)", JetAng[k].Data() , JetAng[k].Data(), i,j,k), Cut.Data() , "goff"); 
                if ((i==1)&&(j==6))TreeMapB[JetAng[k]]->Draw(TString::Format("%s >> hB_no_cut_%s(50,0,100)", JetAng[k].Data() , JetAng[k].Data()), "" , "goff"); 
            } else{
                TreeMapB[JetAng[k]]          ->Draw(TString::Format("%s >> hB_%s_%i_%i_%i(50,0,1)", JetAng[k].Data() , JetAng[k].Data(), i,j,k), Cut.Data() , "goff"); 
                if ((i==1)&&(j==6))TreeMapB[JetAng[k]]->Draw(TString::Format("%s >> hB_no_cut_%s(50,0,1)", JetAng[k].Data() , JetAng[k].Data()), "" , "goff"); 
            }
            h = (TH1D*)gDirectory->Get(TString::Format("hB_%s_%i_%i_%i", JetAng[k].Data(), i,j,k));
            h2= (TH1D*)h->Clone(TString::Format("%s_clone", h->GetName()));
            if ((i==1)&&(j==6)) h_no_cutB=(TH1D*)gDirectory->Get(TString::Format("hB_no_cut_%s", JetAng[k].Data()));

            if ((ScaleA-ScaleB)!=0) {h->Scale((ScaleA)/(ScaleA-ScaleB));}else{
                h->Scale(0.);
            };
            h_MapB_Quark[JetAng[k].Data()].push_back(h);
            if ((ScaleA-ScaleB)!=0) {h2->Scale(-1.*(1-ScaleA)/(ScaleA-ScaleB));}else{
                h2->Scale(0.);
            };
            h_MapB_Gluon[JetAng[k].Data()].push_back(h2);
            //HERE CARRY ON !!! take other parts of quark and gluon angularities
            //Cut = TString::Format("(%s.%s > %f)&&(%s.%s < %f)&&(%s.%s > %f)&&(%s.%s < %f)", 
            //            TreeMapB[mmdt_JetPt[k]]->GetName(),mmdt_JetPt[k].Data(), CutPtLow, TreeMapB[mmdt_JetPt[k]]->GetName(), mmdt_JetPt[k].Data(), CutPtUp,
            //            TreeMapB[mmdt_JetEta[k]]->GetName(),mmdt_JetEta[k].Data(), CutEtaLow, TreeMapB[mmdt_JetEta[k]]->GetName(), mmdt_JetEta[k].Data(), CutEtaUp);
            Cut = TString::Format("(0.5*(%s.%s[0]+%s.%s[1]) > %f)&&(0.5*(%s.%s[0]+%s.%s[1]) < %f)&&(0.5*(TMath::Abs(%s.%s[0]) + TMath::Abs(%s.%s[1]))  > %f)&&(0.5*(TMath::Abs(%s.%s[0]) + TMath::Abs(%s.%s[1])) < %f)", 
                        TreeMapB[mmdt_JetPt[k]]->GetName(),mmdt_JetPt[k].Data(),TreeMapB[mmdt_JetPt[k]]->GetName(),mmdt_JetPt[k].Data(),
                        CutPtLow, 
                        TreeMapB[mmdt_JetPt[k]]->GetName(), mmdt_JetPt[k].Data(), TreeMapB[mmdt_JetPt[k]]->GetName(), mmdt_JetPt[k].Data(), 
                        CutPtUp,
                        TreeMapB[mmdt_JetEta[k]]->GetName(),mmdt_JetEta[k].Data(), TreeMapB[mmdt_JetEta[k]]->GetName(),mmdt_JetEta[k].Data(), 
                        CutEtaLow, 
                        TreeMapB[mmdt_JetEta[k]]->GetName(), mmdt_JetEta[k].Data(), TreeMapB[mmdt_JetEta[k]]->GetName(), mmdt_JetEta[k].Data(), 
                        CutEtaUp);
            //TreeMapB[mmdt_JetAng[k]]     ->Draw(mmdt_JetAng[k]     .Data(), Cut.Data() , "goff");
            if (mmdt_JetAng[k].Contains("MultLam")){
                TreeMapB[mmdt_JetAng[k]]          ->Draw(TString::Format("%s >> hB_%s_%i_%i_%i(50,0,100)", mmdt_JetAng[k].Data() , mmdt_JetAng[k].Data(), i,j,k), Cut.Data() , "goff"); 
                if ((i==1)&&(j==6))TreeMapB[mmdt_JetAng[k]]->Draw(TString::Format("%s >> hB_no_cut_%s(50,0,100)", mmdt_JetAng[k].Data() , mmdt_JetAng[k].Data()), "" , "goff"); 
            }else{
                TreeMapB[mmdt_JetAng[k]]          ->Draw(TString::Format("%s >> hB_%s_%i_%i_%i(50,0,1)", mmdt_JetAng[k].Data() , mmdt_JetAng[k].Data(), i,j,k), Cut.Data() , "goff"); 
                if ((i==1)&&(j==6))TreeMapB[mmdt_JetAng[k]]->Draw(TString::Format("%s >> hB_no_cut_%s(50,0,1)", mmdt_JetAng[k].Data() , mmdt_JetAng[k].Data()), "" , "goff"); 
            }
            h = (TH1D*)gDirectory->Get(TString::Format("hB_%s_%i_%i_%i", mmdt_JetAng[k].Data(), i,j,k));
            h2= (TH1D*)h->Clone(TString::Format("%s_clone", h->GetName()));

            if ((i==1)&&(j==6)) h_no_cutB_mmdt =(TH1D*)gDirectory->Get(TString::Format("hB_no_cut_%s", mmdt_JetAng[k].Data()));
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
                    h_no_cutA_mmdt_clone->Scale(-1.*fracB_no_cut);
                    h_no_cutB_clone->Scale(fracA_no_cut);
                    h_no_cutB_mmdt_clone->Scale(fracA_no_cut);

                    h_no_cutA_clone->Add(h_no_cutB_clone);
                    h_no_cutA_mmdt_clone->Add(h_no_cutB_mmdt_clone);

                    h_no_cutA_clone->Scale(fracA_no_cut-fracB_no_cut);
                    h_no_cutA_mmdt_clone->Scale(fracA_no_cut-fracB_no_cut);

                    h_no_cutA_clone->SetName( TString::Format("quark_%s", h_no_cutA_clone->GetName()));
                    h_no_cutA_mmdt_clone->SetName(TString::Format("quark_%s",h_no_cutA_mmdt_clone->GetName()));

                    nocuts.push_back(h_no_cutA_clone);
                    nocuts.push_back(h_no_cutA_mmdt_clone);

                    //
                    h_no_cutA->Scale(1.-fracB_no_cut);
                    h_no_cutA_mmdt->Scale(1.-fracB_no_cut);
                    h_no_cutB->Scale(-1.*(1.-fracA_no_cut));
                    h_no_cutB_mmdt->Scale(-1.*(1.-fracA_no_cut));

                    h_no_cutA->Add(h_no_cutB);
                    h_no_cutA_mmdt->Add(h_no_cutB_mmdt);

                    h_no_cutA->Scale(fracA_no_cut-fracB_no_cut);
                    h_no_cutA_mmdt->Scale(fracA_no_cut-fracB_no_cut);

                    h_no_cutA->SetName(TString::Format("gluon_%s",h_no_cutA->GetName()));
                    h_no_cutA_mmdt->SetName(TString::Format("gluon_%s",h_no_cutA_mmdt->GetName()));

                    nocuts.push_back(h_no_cutA);
                    nocuts.push_back(h_no_cutA_mmdt);



                }

            }

        }
    }

   TFile * output = new TFile(TString::Format("qg_angs_%s_%s.root", EnergyA.Data(), EnergyB.Data() ), "recreate" );
   output->cd();

    
    THStack *hs_g;
    THStack *hs_q;
    THStack *hs_g_mmdt;
    THStack *hs_q_mmdt;
    TH1F * h_g;
    TH1F * h_q;
    TH1F * h_g_mmdt;
    TH1F * h_q_mmdt;
    for (int i = 0; i<JetAng.size(); i++){
    //for (int i = 0; i<1; i++){
        hs_g = new THStack(TString::Format("Final_gluon_%s", JetAng[i].Data() ),TString::Format("Final_gluon_%s", JetAng[i].Data() ));
        hs_q = new THStack(TString::Format("Final_quark_%s", JetAng[i].Data() ),TString::Format("Final_quark_%s", JetAng[i].Data() ));
        hs_g_mmdt = new THStack(TString::Format("Final_gluon_mmdt_%s", mmdt_JetAng[i].Data() ),TString::Format("Final_gluon_mmdt_%s", mmdt_JetAng[i].Data() ));
        hs_q_mmdt = new THStack(TString::Format("Final_quark_mmdt_%s", mmdt_JetAng[i].Data() ),TString::Format("Final_quark_mmdt_%s", mmdt_JetAng[i].Data() ));
    
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

            if (h_MapA_Quark[JetAng[i]][j]->Integral()!=0) hs_q->Add(h_MapA_Quark[JetAng[i]][j]);
            if (h_MapA_Gluon[JetAng[i]][j]->Integral()!=0) hs_g->Add(h_MapA_Gluon[JetAng[i]][j]);
            if (h_MapB_Quark[JetAng[i]][j]->Integral()!=0) hs_q->Add(h_MapB_Quark[JetAng[i]][j]);
            if (h_MapB_Gluon[JetAng[i]][j]->Integral()!=0) hs_g->Add(h_MapB_Gluon[JetAng[i]][j]);
            if (h_MapA_Quark[mmdt_JetAng[i]][j]->Integral()!=0) hs_q_mmdt->Add(h_MapA_Quark[mmdt_JetAng[i]][j]);
            if (h_MapA_Gluon[mmdt_JetAng[i]][j]->Integral()!=0) hs_g_mmdt->Add(h_MapA_Gluon[mmdt_JetAng[i]][j]);
            if (h_MapB_Quark[mmdt_JetAng[i]][j]->Integral()!=0) hs_q_mmdt->Add(h_MapB_Quark[mmdt_JetAng[i]][j]);
            if (h_MapB_Gluon[mmdt_JetAng[i]][j]->Integral()!=0) hs_g_mmdt->Add(h_MapB_Gluon[mmdt_JetAng[i]][j]);

            if (h_MapA_Quark[JetAng[i]][j]->Integral()!=0) h_q->Add(h_MapA_Quark[JetAng[i]][j]);
            if (h_MapA_Gluon[JetAng[i]][j]->Integral()!=0) h_g->Add(h_MapA_Gluon[JetAng[i]][j]);
            if (h_MapB_Quark[JetAng[i]][j]->Integral()!=0) h_q->Add(h_MapB_Quark[JetAng[i]][j]);
            if (h_MapB_Gluon[JetAng[i]][j]->Integral()!=0) h_g->Add(h_MapB_Gluon[JetAng[i]][j]);
            if (h_MapA_Quark[mmdt_JetAng[i]][j]->Integral()!=0) h_q_mmdt->Add(h_MapA_Quark[mmdt_JetAng[i]][j]);
            if (h_MapA_Gluon[mmdt_JetAng[i]][j]->Integral()!=0) h_g_mmdt->Add(h_MapA_Gluon[mmdt_JetAng[i]][j]);
            if (h_MapB_Quark[mmdt_JetAng[i]][j]->Integral()!=0) h_q_mmdt->Add(h_MapB_Quark[mmdt_JetAng[i]][j]);
            if (h_MapB_Gluon[mmdt_JetAng[i]][j]->Integral()!=0) h_g_mmdt->Add(h_MapB_Gluon[mmdt_JetAng[i]][j]);
        }
        hs_g->Write();
        hs_q->Write();
        hs_g_mmdt->Write();
        hs_q_mmdt->Write();
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
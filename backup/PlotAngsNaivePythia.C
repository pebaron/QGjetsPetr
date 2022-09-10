TString GetAngName(TString a){
    if (a.Contains("Mult") ) return "#lambda^{0}_{0}";
    if (a.Contains("Lha")  ) return "#lambda^{1}_{0.5}";
    if (a.Contains("Wid")  ) return "#lambda^{1}_{1}";
    if (a.Contains("Mass") ) return "#lambda^{1}_{2}";
    if (a.Contains("Pt")   ) return "#lambda^{2}_{0}";
}

TString GetAngR(TString a){
    if (a.Contains("FastJets02")) return "0.2";
    if (a.Contains("FastJets04")) return "0.4";
    if (a.Contains("FastJets06")) return "0.6";
    if (a.Contains("FastJets08")) return "0.8";
    if (a.Contains("FastJets10")) return "1.0";
}


double GetInt(TH1F* h){
    double integral;
    for (int i = 1; i<=h->GetXaxis()->GetNbins(); i++){
        if (h->GetBinContent(i)>=0){
            integral+=h->GetBinContent(i);
        }
        //else{
        //    integral+=(-1.)*h->GetBinContent(i);
        //}
    }
return integral;
}

int PlotAngsNaivePythia(){

std::map<TString, TFile*> nominal;
std::map<TString, TFile*> nominalNoMPINoISR;

nominalNoMPINoISR["2360_13000"] = new TFile("qg_angs_noMPI_noISR_2360_13000_pythia.root","read");
nominalNoMPINoISR["2360_7000"] = new TFile("qg_angs_noMPI_noISR_2360_7000_pythia.root","read");
nominalNoMPINoISR["7000_13000"] = new TFile("qg_angs_noMPI_noISR_7000_13000_pythia.root","read");
nominalNoMPINoISR["900_13000"] = new TFile("qg_angs_noMPI_noISR_900_13000_pythia.root","read");
nominalNoMPINoISR["900_2360"] = new TFile("qg_angs_noMPI_noISR_900_2360_pythia.root","read");
nominalNoMPINoISR["900_7000"] = new TFile("qg_angs_noMPI_noISR_900_7000_pythia.root","read");
nominal["2360_13000"] = new TFile("qg_angs_2360_13000_pythia.root","read");
nominal["2360_7000"]  = new TFile("qg_angs_2360_7000_pythia.root","read");
nominal["7000_13000"] = new TFile("qg_angs_7000_13000_pythia.root","read");
nominal["900_13000"]  = new TFile("qg_angs_900_13000_pythia.root","read");
nominal["900_2360"]   = new TFile("qg_angs_900_2360_pythia.root","read");
nominal["900_7000"]   = new TFile("qg_angs_900_7000_pythia.root","read");

vector<TString> Energies;

Energies.push_back("2360_13000");
Energies.push_back("2360_7000");
Energies.push_back("7000_13000");
Energies.push_back("900_13000");
Energies.push_back("900_2360");
Energies.push_back("900_7000");

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

    vector<TString> quark_JetAng;
    vector<TString> gluon_JetAng;

    vector<TString> mmdt_quark_JetAng;
    vector<TString> mmdt_gluon_JetAng;

    for (int i = 0; i < Radii.size();i++){
        for (int j = 0; j < Lambdas.size();j++){
            for (int k = 0; k < Q.size();k++){
            quark_JetAng.push_back( TString::Format("quark_clone_h_no_cut_FastJets%s%sLam%s", Radii[i].Data(), Lambdas[j].Data(), Q[k].Data() ) );
            gluon_JetAng.push_back( TString::Format("gluon_h_no_cut_FastJets%s%sLam%s", Radii[i].Data(), Lambdas[j].Data(), Q[k].Data() ) );
            mmdt_quark_JetAng.push_back( TString::Format("quark_clone_h_no_cut_mmdt_FastJets%s%sLam%s", Radii[i].Data(), Lambdas[j].Data(), Q[k].Data() ) );
            mmdt_gluon_JetAng.push_back( TString::Format("gluon_h_no_cut_mmdt_FastJets%s%sLam%s", Radii[i].Data(), Lambdas[j].Data(), Q[k].Data() ) );
            }
        }
    }

    TH1F * hq_2360_13000;
    TH1F * hq_2360_7000;
    TH1F * hq_7000_13000;
    TH1F * hq_900_13000;
    TH1F * hq_900_2360;
    TH1F * hq_900_7000;
    TH1F * hg_2360_13000;
    TH1F * hg_2360_7000;
    TH1F * hg_7000_13000;
    TH1F * hg_900_13000;
    TH1F * hg_900_2360;
    TH1F * hg_900_7000;
    TH1F * hq_mmdt_2360_13000;
    TH1F * hq_mmdt_2360_7000;
    TH1F * hq_mmdt_7000_13000;
    TH1F * hq_mmdt_900_13000;
    TH1F * hq_mmdt_900_2360;
    TH1F * hq_mmdt_900_7000;
    TH1F * hg_mmdt_2360_13000;
    TH1F * hg_mmdt_2360_7000;
    TH1F * hg_mmdt_7000_13000;
    TH1F * hg_mmdt_900_13000;
    TH1F * hg_mmdt_900_2360;
    TH1F * hg_mmdt_900_7000;

    TH1F * NoMPI_hq_2360_13000;
    TH1F * NoMPI_hq_2360_7000;
    TH1F * NoMPI_hq_7000_13000;
    TH1F * NoMPI_hq_900_13000;
    TH1F * NoMPI_hq_900_2360;
    TH1F * NoMPI_hq_900_7000;
    TH1F * NoMPI_hg_2360_13000;
    TH1F * NoMPI_hg_2360_7000;
    TH1F * NoMPI_hg_7000_13000;
    TH1F * NoMPI_hg_900_13000;
    TH1F * NoMPI_hg_900_2360;
    TH1F * NoMPI_hg_900_7000;
    TH1F * NoMPI_hq_mmdt_2360_13000;
    TH1F * NoMPI_hq_mmdt_2360_7000;
    TH1F * NoMPI_hq_mmdt_7000_13000;
    TH1F * NoMPI_hq_mmdt_900_13000;
    TH1F * NoMPI_hq_mmdt_900_2360;
    TH1F * NoMPI_hq_mmdt_900_7000;
    TH1F * NoMPI_hg_mmdt_2360_13000;
    TH1F * NoMPI_hg_mmdt_2360_7000;
    TH1F * NoMPI_hg_mmdt_7000_13000;
    TH1F * NoMPI_hg_mmdt_900_13000;
    TH1F * NoMPI_hg_mmdt_900_2360;
    TH1F * NoMPI_hg_mmdt_900_7000;

    TH1F * hq;
    TH1F * hg;
    TH1F * mmdt_hq;
    TH1F * mmdt_hg;

    TH1F * No_MPI_hq;
    TH1F * No_MPI_hg;
    TH1F * No_MPI_mmdt_hq;
    TH1F * No_MPI_mmdt_hg;

    vector<TH1F*> quark;
    vector<TH1F*> gluon;
    vector<TH1F*> mmdt_quark;
    vector<TH1F*> mmdt_gluon;

    vector<TH1F*> No_MPI_quark;
    vector<TH1F*> No_MPI_gluon;
    vector<TH1F*> No_MPI_mmdt_quark;
    vector<TH1F*> No_MPI_mmdt_gluon;

    vector<vector<TH1F*>> vec_quark;
    vector<vector<TH1F*>> vec_gluon;
    vector<vector<TH1F*>> vec_mmdt_quark;
    vector<vector<TH1F*>> vec_mmdt_gluon;

    vector<vector<TH1F*>> vec_No_MPI_quark;
    vector<vector<TH1F*>> vec_No_MPI_gluon;
    vector<vector<TH1F*>> vec_No_MPI_mmdt_quark;
    vector<vector<TH1F*>> vec_No_MPI_mmdt_gluon;

    vector<TH1F*> all;

    for (int i = 0; i < quark_JetAng.size();i++){
    //for (int i = 0; i < 1;i++){
        for (int j = 0; j < Energies.size();j++){
            //cout << Energies[j].Data() << " " << gluon_JetAng[i] << endl;
            hq=(TH1F*)nominal[Energies[j].Data()]->Get(quark_JetAng[i]);
            hq->SetName(TString::Format("%s_%s", Energies[j].Data(), hq->GetName()));
            hq->SetTitle(TString::Format("%s_%s", Energies[j].Data(), hq->GetTitle()));


            hg=(TH1F*)nominal[Energies[j].Data()]->Get(gluon_JetAng[i]);
            hg->SetName(TString::Format("%s_%s", Energies[j].Data(), hg->GetName()));
            hg->SetTitle(TString::Format("%s_%s", Energies[j].Data(), hg->GetTitle()));

            mmdt_hq=(TH1F*)nominal[Energies[j].Data()]->Get(mmdt_quark_JetAng[i]);
            mmdt_hq->SetName(TString::Format("%s_%s", Energies[j].Data(), mmdt_hq->GetName()));
            mmdt_hq->SetTitle(TString::Format("%s_%s", Energies[j].Data(), mmdt_hq->GetTitle()));

            mmdt_hg=(TH1F*)nominal[Energies[j].Data()]->Get(mmdt_gluon_JetAng[i]);
            mmdt_hg->SetName(TString::Format("%s_%s", Energies[j].Data(), mmdt_hg->GetName()));
            mmdt_hg->SetTitle(TString::Format("%s_%s", Energies[j].Data(), mmdt_hg->GetTitle()));

            //
            No_MPI_hq=(TH1F*)nominalNoMPINoISR[Energies[j].Data()]->Get(quark_JetAng[i]);
            No_MPI_hq->SetName(TString::Format("%s_%s", Energies[j].Data(), No_MPI_hq->GetName()));
            No_MPI_hq->SetTitle(TString::Format("%s_%s", Energies[j].Data(), No_MPI_hq->GetTitle()));

            No_MPI_hg=(TH1F*)nominalNoMPINoISR[Energies[j].Data()]->Get(gluon_JetAng[i]);
            No_MPI_hg->SetName(TString::Format("%s_%s", Energies[j].Data(), No_MPI_hg->GetName()));
            No_MPI_hg->SetTitle(TString::Format("%s_%s", Energies[j].Data(), No_MPI_hg->GetTitle()));

            No_MPI_mmdt_hq=(TH1F*)nominalNoMPINoISR[Energies[j].Data()]->Get(mmdt_quark_JetAng[i]);
            No_MPI_mmdt_hq->SetName(TString::Format("%s_%s", Energies[j].Data(), No_MPI_mmdt_hq->GetName()));
            No_MPI_mmdt_hq->SetTitle(TString::Format("%s_%s", Energies[j].Data(), No_MPI_mmdt_hq->GetTitle()));

            No_MPI_mmdt_hg=(TH1F*)nominalNoMPINoISR[Energies[j].Data()]->Get(mmdt_gluon_JetAng[i]);
            No_MPI_mmdt_hg->SetName(TString::Format("%s_%s", Energies[j].Data(), No_MPI_mmdt_hg->GetName()));
            No_MPI_mmdt_hg->SetTitle(TString::Format("%s_%s", Energies[j].Data(), No_MPI_mmdt_hg->GetTitle()));

            quark.push_back(hq);
            gluon.push_back(hg);
            mmdt_quark.push_back(mmdt_hq);
            mmdt_gluon.push_back(mmdt_hg);
            No_MPI_quark.push_back(No_MPI_hq);
            No_MPI_gluon.push_back(No_MPI_hg);
            No_MPI_mmdt_quark.push_back(No_MPI_mmdt_hq);
            No_MPI_mmdt_gluon.push_back(No_MPI_mmdt_hg);

            all.push_back(hq);
            all.push_back(hg);
            all.push_back(mmdt_hq);
            all.push_back(mmdt_hg);
            all.push_back(No_MPI_hq);
            all.push_back(No_MPI_hg);
            all.push_back(No_MPI_mmdt_hq);
            all.push_back(No_MPI_mmdt_hg);
    
        }

        vec_quark.push_back(quark);
        vec_gluon.push_back(gluon);
        vec_mmdt_quark.push_back(mmdt_quark);
        vec_mmdt_gluon.push_back(mmdt_gluon);
        vec_No_MPI_quark.push_back(No_MPI_quark);
        vec_No_MPI_gluon.push_back(No_MPI_gluon);
        vec_No_MPI_mmdt_quark.push_back(No_MPI_mmdt_quark);
        vec_No_MPI_mmdt_gluon.push_back(No_MPI_mmdt_gluon);
        quark.clear();
        gluon.clear();
        mmdt_quark.clear();
        mmdt_gluon.clear();
        No_MPI_quark.clear();
        No_MPI_gluon.clear();
        No_MPI_mmdt_quark.clear();
        No_MPI_mmdt_gluon.clear();
    }

    vector<TCanvas*> cans;
    vector<TCanvas*> cans2;
    TCanvas * cantemp;
    TCanvas * cantemp2;
    double max_q, max_g;
    double noMPI_max_q, noMPI_max_g;
    vector<double> min;
    TString CanName;
    TString CanName2;    
    TLegend * leg;
    TLegend * leg2;
    TString LegName;
    TString LegName2;    

    for (int i=0;i<vec_quark.size();i++){
        cantemp = new TCanvas(TString::Format("can_%s", vec_quark[i][0]->GetName()), TString::Format("can_%s", vec_quark[i][0]->GetName()), 0, 0, 1600,1600 );
        cans.push_back(cantemp);
        cans[i]->cd();
        TString AngName = GetAngName(vec_quark[i][0]->GetName());
        vec_quark[i][0]->GetXaxis()->SetTitle(AngName.Data());
        vec_quark[i][0]->GetYaxis()->SetTitle("Events / Norm.");
        vec_gluon[i][0]->GetXaxis()->SetTitle(AngName.Data());
        vec_gluon[i][0]->GetYaxis()->SetTitle("Events / Norm.");
        for (int j=0;j<vec_quark[i].size();j++){
            //leg->AddEntry(vec_quark[i][j], TString::Format("%s", vec_quark[i][j]->GetName() ));
            //leg->AddEntry(vec_No_MPI_quark[i][j], TString::Format("%s", vec_No_MPI_quark[i][j]->GetName() ));
            //leg->AddEntry(vec_gluon[i][j], TString::Format("%s", vec_gluon[i][j]->GetName() ));
            //leg->AddEntry(vec_No_MPI_gluon[i][j], TString::Format("%s", vec_No_MPI_gluon[i][j]->GetName() ));
            vec_quark[i][j]->SetLineColor(kPink -j);
            vec_gluon[i][j]->SetLineColor(kAzure-j);
            vec_quark[i][j]->SetMarkerSize(0);
            vec_gluon[i][j]->SetMarkerSize(0);
            vec_quark[i][j]->SetLineWidth(2);
            vec_gluon[i][j]->SetLineWidth(2);

            vec_No_MPI_quark[i][j]->SetMarkerColor(kPink -j);
            vec_No_MPI_gluon[i][j]->SetMarkerColor(kAzure-j);
            vec_No_MPI_quark[i][j]->SetMarkerSize(1);
            vec_No_MPI_gluon[i][j]->SetMarkerSize(1);
            vec_No_MPI_quark[i][j]->SetLineWidth(0);
            vec_No_MPI_gluon[i][j]->SetLineWidth(0);
            vec_No_MPI_quark[i][j]->SetLineStyle(2);
            vec_No_MPI_gluon[i][j]->SetLineStyle(2);
            if (j==0){
                cans[i]->cd();
                vec_quark[i][0]->Scale(1./GetInt(vec_quark[i][0]));
                max_q = vec_quark[i][0]->GetMaximum();
                vec_gluon[i][0]->Scale(1./GetInt(vec_gluon[i][0]));
                max_g = vec_gluon[i][0]->GetMaximum();

                vec_No_MPI_quark[i][0]->Scale(1./GetInt(vec_No_MPI_quark[i][0]));
                noMPI_max_q = vec_No_MPI_quark[i][0]->GetMaximum();
                vec_No_MPI_gluon[i][0]->Scale(1./GetInt(vec_No_MPI_gluon[i][0]));
                noMPI_max_g = vec_No_MPI_gluon[i][0]->GetMaximum();
                if (max_q > max_g){
                    vec_quark[i][0]->SetMaximum(1.5*vec_quark[i][0]->GetMaximum());
                    vec_quark[i][0]->Draw("hist e1");
                    vec_gluon[i][0]->Draw("hist e1 same");
                    vec_No_MPI_quark[i][0]->Draw("hist e1 same");
                    vec_No_MPI_gluon[i][0]->Draw("hist e1 same");
                }else{
                    vec_gluon[i][0]->SetMaximum(1.5*vec_gluon[i][0]->GetMaximum());
                    vec_gluon[i][0]->Draw("hist e1");
                    vec_quark[i][0]->Draw("hist e1 same");
                    vec_No_MPI_quark[i][0]->Draw("hist e1 same");
                    vec_No_MPI_gluon[i][0]->Draw("hist e1 same");
                }
            }else{
                vec_quark[i][j]->Scale(max_q/vec_quark[i][j]->GetMaximum() );
                vec_quark[i][j]->Draw("hist e1 same");
                vec_gluon[i][j]->Scale(max_g/vec_gluon[i][j]->GetMaximum() );
                vec_gluon[i][j]->Draw("hist e1 same");

                vec_No_MPI_quark[i][j]->Scale(noMPI_max_q/vec_No_MPI_quark[i][j]->GetMaximum() );
                vec_No_MPI_quark[i][j]->Draw("hist e1 same");
                vec_No_MPI_gluon[i][j]->Scale(noMPI_max_g/vec_No_MPI_gluon[i][j]->GetMaximum() );
                vec_No_MPI_gluon[i][j]->Draw("hist e1 same");
            }

            min.push_back(vec_quark[i][j]->GetBinContent(vec_quark[i][j]->GetMinimumBin()) + vec_quark[i][j]->GetBinError(vec_quark[i][j]->GetMinimumBin()) ); //here to
            min.push_back(vec_gluon[i][j]->GetBinContent(vec_gluon[i][j]->GetMinimumBin()) + vec_gluon[i][j]->GetBinError(vec_gluon[i][j]->GetMinimumBin()) ); //here to
            min.push_back(vec_No_MPI_quark[i][j]->GetBinContent(vec_No_MPI_quark[i][j]->GetMinimumBin()) + vec_No_MPI_quark[i][j]->GetBinError(vec_No_MPI_quark[i][j]->GetMinimumBin()) );
            min.push_back(vec_No_MPI_gluon[i][j]->GetBinContent(vec_No_MPI_gluon[i][j]->GetMinimumBin()) + vec_No_MPI_gluon[i][j]->GetBinError(vec_No_MPI_gluon[i][j]->GetMinimumBin()) );

        
        } 
        vec_quark[i][0]->SetMinimum(*std::min_element(std::begin(min), std::end(min))*2.)   ;
        vec_gluon[i][0]->SetMinimum(*std::min_element(std::begin(min), std::end(min))*2.)   ;
        gPad->Modified();
        gPad->Update();
        leg = new TLegend(0.59,0.43,0.998,0.91);
        leg->SetBorderSize(0);
        leg->SetFillStyle(0);
        //leg->SetTextSize(0.02);
        for (int j=0;j<vec_quark[i].size();j++){
            LegName = vec_quark[i][j]->GetName();
            LegName = LegName.ReplaceAll("_", " ");
            TObjArray *tx = LegName.Tokenize(" ");
            TString sleg0 = ((TObjString *)(tx->At(0)))->String();
            TString sleg1 = ((TObjString *)(tx->At(1)))->String();
            TString sleg2 = ((TObjString *)(tx->At(2)))->String();
            TString sleg3 = ((TObjString *)(tx->At(3)))->String();
            leg->AddEntry(vec_quark[i][j], TString::Format("%s ang. using %s-%s GeV",sleg2.Data(), sleg0.Data(), sleg1.Data() ));
        }
        for (int j=0;j<vec_quark[i].size();j++){
            LegName = vec_No_MPI_quark[i][j]->GetName();
            LegName = LegName.ReplaceAll("_", " ");
            TObjArray *tx = LegName.Tokenize(" ");
            TString sleg0 = ((TObjString *)(tx->At(0)))->String();
            TString sleg1 = ((TObjString *)(tx->At(1)))->String();
            TString sleg2 = ((TObjString *)(tx->At(2)))->String();
            TString sleg3 = ((TObjString *)(tx->At(3)))->String();
            leg->AddEntry(vec_No_MPI_quark[i][j], TString::Format("%s ang. (no MPI no ISR) using %s-%s GeV",sleg2.Data(), sleg0.Data(), sleg1.Data() ));
        }
        for (int j=0;j<vec_quark[i].size();j++){
            LegName = vec_gluon[i][j]->GetName();
            LegName = LegName.ReplaceAll("_", " ");
            TObjArray *tx = LegName.Tokenize(" ");
            TString sleg0 = ((TObjString *)(tx->At(0)))->String();
            TString sleg1 = ((TObjString *)(tx->At(1)))->String();
            TString sleg2 = ((TObjString *)(tx->At(2)))->String();
            TString sleg3 = ((TObjString *)(tx->At(3)))->String();
            leg->AddEntry(vec_gluon[i][j], TString::Format("%s ang. using %s-%s GeV",sleg2.Data(), sleg0.Data(), sleg1.Data() ));
        }
        for (int j=0;j<vec_quark[i].size();j++){
            LegName = vec_No_MPI_gluon[i][j]->GetName();
            LegName = LegName.ReplaceAll("_", " ");
            TObjArray *tx = LegName.Tokenize(" ");
            TString sleg0 = ((TObjString *)(tx->At(0)))->String();
            TString sleg1 = ((TObjString *)(tx->At(1)))->String();
            TString sleg2 = ((TObjString *)(tx->At(2)))->String();
            TString sleg3 = ((TObjString *)(tx->At(3)))->String();
            leg->AddEntry(vec_No_MPI_gluon[i][j], TString::Format("%s ang. (no MPI no ISR) using %s-%s GeV",sleg2.Data(), sleg0.Data(), sleg1.Data() ));
        }
        leg->AddEntry((TObject*)0, TString::Format("Jet R = %s", GetAngR(vec_quark[i][0]->GetName()).Data() ), "");
        leg->AddEntry((TObject*)0, TString::Format("Angularity %s", GetAngName(vec_quark[i][0]->GetName()).Data() ), "");
        leg->Draw("same");
        min.clear();
        //mmdt
        cantemp2 = new TCanvas(TString::Format("can_%s", vec_mmdt_quark[i][0]->GetName()), TString::Format("can_%s", vec_mmdt_quark[i][0]->GetName()), 0, 0, 1600,1600 );
        cans2.push_back(cantemp2);
        cans2[i]->cd();
        AngName = TString::Format("mmdt %s", AngName.Data());
        vec_mmdt_quark[i][0]->GetXaxis()->SetTitle(AngName.Data());
        vec_mmdt_quark[i][0]->GetYaxis()->SetTitle("Events / Norm.");
        vec_mmdt_gluon[i][0]->GetXaxis()->SetTitle(AngName.Data());
        vec_mmdt_gluon[i][0]->GetYaxis()->SetTitle("Events / Norm.");
        for (int j=0;j<vec_mmdt_quark[i].size();j++){
            vec_mmdt_quark[i][j]->SetLineColor(kPink -j);
            vec_mmdt_gluon[i][j]->SetLineColor(kAzure -j);
            vec_mmdt_quark[i][j]->SetMarkerSize(0);
            vec_mmdt_gluon[i][j]->SetMarkerSize(0);
            vec_mmdt_quark[i][j]->SetLineWidth(2);
            vec_mmdt_gluon[i][j]->SetLineWidth(2);

            vec_No_MPI_mmdt_quark[i][j]->SetMarkerColor(kPink -j);
            vec_No_MPI_mmdt_gluon[i][j]->SetMarkerColor(kAzure -j);
            vec_No_MPI_mmdt_quark[i][j]->SetMarkerSize(1);
            vec_No_MPI_mmdt_gluon[i][j]->SetMarkerSize(1);
            vec_No_MPI_mmdt_quark[i][j]->SetLineWidth(0);
            vec_No_MPI_mmdt_gluon[i][j]->SetLineWidth(0);
            vec_No_MPI_mmdt_quark[i][j]->SetLineStyle(2);
            vec_No_MPI_mmdt_gluon[i][j]->SetLineStyle(2);
            if (j==0){
                cans2[i]->cd();
                vec_mmdt_quark[i][0]->Scale(1./GetInt(vec_mmdt_quark[i][0]));
                max_q = vec_mmdt_quark[i][0]->GetMaximum();
                vec_mmdt_gluon[i][0]->Scale(1./GetInt(vec_mmdt_gluon[i][0]));
                max_g = vec_mmdt_gluon[i][0]->GetMaximum();

                vec_No_MPI_mmdt_quark[i][0]->Scale(1./GetInt(vec_No_MPI_mmdt_quark[i][0]));
                noMPI_max_q = vec_No_MPI_mmdt_quark[i][0]->GetMaximum();
                vec_No_MPI_mmdt_gluon[i][0]->Scale(1./GetInt(vec_No_MPI_mmdt_gluon[i][0]));
                noMPI_max_g = vec_No_MPI_mmdt_gluon[i][0]->GetMaximum();
                if (max_q > max_g){
                    vec_mmdt_quark[i][0]->SetMaximum(1.3*vec_mmdt_quark[i][0]->GetMaximum());
                    vec_mmdt_quark[i][0]->Draw("hist e1");
                    vec_mmdt_gluon[i][0]->Draw("hist e1 same");
                    vec_No_MPI_mmdt_quark[i][0]->Draw("hist e1 same");
                    vec_No_MPI_mmdt_gluon[i][0]->Draw("hist e1 same");
                }else{
                    vec_mmdt_gluon[i][0]->SetMaximum(1.3*vec_mmdt_gluon[i][0]->GetMaximum());
                    vec_mmdt_gluon[i][0]->Draw("hist e1");
                    vec_mmdt_quark[i][0]->Draw("hist e1 same");
                    vec_No_MPI_mmdt_quark[i][0]->Draw("hist e1 same");
                    vec_No_MPI_mmdt_gluon[i][0]->Draw("hist e1 same");
                }
            }else{
                vec_mmdt_quark[i][j]->Scale(max_q/vec_mmdt_quark[i][j]->GetMaximum() );
                vec_mmdt_quark[i][j]->Draw("hist e1 same");
                vec_mmdt_gluon[i][j]->Scale(max_g/vec_mmdt_gluon[i][j]->GetMaximum() );
                vec_mmdt_gluon[i][j]->Draw("hist e1 same");

                vec_No_MPI_mmdt_quark[i][j]->Scale(noMPI_max_q/vec_No_MPI_mmdt_quark[i][j]->GetMaximum() );
                vec_No_MPI_mmdt_quark[i][j]->Draw("hist e1 same");
                vec_No_MPI_mmdt_gluon[i][j]->Scale(noMPI_max_g/vec_No_MPI_mmdt_gluon[i][j]->GetMaximum() );
                vec_No_MPI_mmdt_gluon[i][j]->Draw("hist e1 same");
            }

            min.push_back(vec_mmdt_quark[i][j]->GetMinimum());
            min.push_back(vec_mmdt_gluon[i][j]->GetMinimum());
            min.push_back(vec_No_MPI_mmdt_quark[i][j]->GetMinimum());
            min.push_back(vec_No_MPI_mmdt_gluon[i][j]->GetMinimum());

            min.push_back(vec_mmdt_quark[i][j]->GetBinContent(vec_mmdt_quark[i][j]->GetMinimumBin()) + vec_mmdt_quark[i][j]->GetBinError(vec_mmdt_quark[i][j]->GetMinimumBin()) ); //here to
            min.push_back(vec_mmdt_gluon[i][j]->GetBinContent(vec_mmdt_gluon[i][j]->GetMinimumBin()) + vec_mmdt_gluon[i][j]->GetBinError(vec_mmdt_gluon[i][j]->GetMinimumBin()) ); //here to
            min.push_back(vec_No_MPI_mmdt_quark[i][j]->GetBinContent(vec_No_MPI_mmdt_quark[i][j]->GetMinimumBin()) + vec_No_MPI_mmdt_quark[i][j]->GetBinError(vec_No_MPI_mmdt_quark[i][j]->GetMinimumBin()) );
            min.push_back(vec_No_MPI_mmdt_gluon[i][j]->GetBinContent(vec_No_MPI_mmdt_gluon[i][j]->GetMinimumBin()) + vec_No_MPI_mmdt_gluon[i][j]->GetBinError(vec_No_MPI_mmdt_gluon[i][j]->GetMinimumBin()) );

        
        } 
        vec_mmdt_quark[i][0]->SetMinimum(*std::min_element(std::begin(min), std::end(min))*2)   ;
        vec_mmdt_gluon[i][0]->SetMinimum(*std::min_element(std::begin(min), std::end(min))*2)   ;
        min.clear();
        leg2 = new TLegend(0.59,0.43,0.998,0.91);
        leg2->SetBorderSize(0);
        leg2->SetFillStyle(0);
        //leg2->SetTextSize(0.02);
        for (int j=0;j<vec_quark[i].size();j++){
            LegName = vec_quark[i][j]->GetName();
            LegName = LegName.ReplaceAll("_", " ");
            TObjArray *tx = LegName.Tokenize(" ");
            TString sleg20 = ((TObjString *)(tx->At(0)))->String();
            TString sleg21 = ((TObjString *)(tx->At(1)))->String();
            TString sleg22 = ((TObjString *)(tx->At(2)))->String();
            TString sleg23 = ((TObjString *)(tx->At(3)))->String();
            leg2->AddEntry(vec_quark[i][j], TString::Format("%s ang. using %s-%s GeV",sleg22.Data(), sleg20.Data(), sleg21.Data() ));
        }
        for (int j=0;j<vec_quark[i].size();j++){
            LegName = vec_No_MPI_quark[i][j]->GetName();
            LegName = LegName.ReplaceAll("_", " ");
            TObjArray *tx = LegName.Tokenize(" ");
            TString sleg20 = ((TObjString *)(tx->At(0)))->String();
            TString sleg21 = ((TObjString *)(tx->At(1)))->String();
            TString sleg22 = ((TObjString *)(tx->At(2)))->String();
            TString sleg23 = ((TObjString *)(tx->At(3)))->String();
            leg2->AddEntry(vec_No_MPI_quark[i][j], TString::Format("%s ang. (no MPI no ISR) using %s-%s GeV",sleg22.Data(), sleg20.Data(), sleg21.Data() ));
        }
        for (int j=0;j<vec_quark[i].size();j++){
            LegName = vec_gluon[i][j]->GetName();
            LegName = LegName.ReplaceAll("_", " ");
            TObjArray *tx = LegName.Tokenize(" ");
            TString sleg20 = ((TObjString *)(tx->At(0)))->String();
            TString sleg21 = ((TObjString *)(tx->At(1)))->String();
            TString sleg22 = ((TObjString *)(tx->At(2)))->String();
            TString sleg23 = ((TObjString *)(tx->At(3)))->String();
            leg2->AddEntry(vec_gluon[i][j], TString::Format("%s ang. using %s-%s GeV",sleg22.Data(), sleg20.Data(), sleg21.Data() ));
        }
        for (int j=0;j<vec_quark[i].size();j++){
            LegName = vec_No_MPI_gluon[i][j]->GetName();
            LegName = LegName.ReplaceAll("_", " ");
            TObjArray *tx = LegName.Tokenize(" ");
            TString sleg20 = ((TObjString *)(tx->At(0)))->String();
            TString sleg21 = ((TObjString *)(tx->At(1)))->String();
            TString sleg22 = ((TObjString *)(tx->At(2)))->String();
            TString sleg23 = ((TObjString *)(tx->At(3)))->String();
            leg2->AddEntry(vec_No_MPI_gluon[i][j], TString::Format("%s ang. (no MPI no ISR) using %s-%s GeV",sleg22.Data(), sleg20.Data(), sleg21.Data() ));
        }
        leg2->AddEntry((TObject*)0, TString::Format("Jet R = %s", GetAngR(vec_quark[i][0]->GetName()).Data() ), "");
        leg2->AddEntry((TObject*)0, TString::Format("Angularity mmdt %s", GetAngName(vec_quark[i][0]->GetName()).Data() ), "");
        leg2->Draw("same");

        CanName=cans[i]->GetName();
        CanName=CanName.ReplaceAll("can_", "");
        CanName=CanName.ReplaceAll("2360_13000_", "");
        CanName=CanName.ReplaceAll("mmdt_mmdt_", "");
        CanName=CanName.ReplaceAll("quark_", "");
        CanName=CanName.ReplaceAll("__", "");
        cans[i]->SaveAs(TString::Format("./angs1D_pythia/1D_%s.png", CanName.Data()));
        cans[i]->SaveAs(TString::Format("./angs1D_pythia/1D_%s.pdf", CanName.Data()));
        cans2[i]->SaveAs(TString::Format("./angs1D_pythia/1D_mmdt_%s.png", CanName.Data()));
        cans2[i]->SaveAs(TString::Format("./angs1D_pythia/1D_mmdt_%s.pdf", CanName.Data()));



    }
    


    return 0;
}
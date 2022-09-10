TString GetRStr(TString a){
    if (a.Contains("02")) return "0.2";
    if (a.Contains("04")) return "0.4";
    if (a.Contains("06")) return "0.6";
    if (a.Contains("08")) return "0.8";
    if (a.Contains("10")) return "1.0";
    return "None";
}



int PlotControl(TString EnergyA = "900", TString EnergyB = "13000", TString Radius = "10"){
    TFile * rfile = new TFile(TString::Format("control_%s_%s.root", EnergyA.Data(), EnergyB.Data()), "read");

    TString hname_defau_A       = TString::Format("h_FastJets%sMultLam50_%s", Radius.Data(),  EnergyA.Data());
    TString hname_defau_B       = TString::Format("h_FastJets%sMultLam50_%s", Radius.Data(),  EnergyB.Data());
    TString hname_nompi_A       = TString::Format("h_nompi_FastJets%sMultLam50_%s", Radius.Data(),  EnergyA.Data());
    TString hname_nompi_B       = TString::Format("h_nompi_FastJets%sMultLam50_%s", Radius.Data(),  EnergyB.Data());
    TString hname_trimm_A       = TString::Format("h_trim_FastJets%sMultLam50_%s", Radius.Data(),  EnergyA.Data());
    TString hname_trimm_B       = TString::Format("h_trim_FastJets%sMultLam50_%s", Radius.Data(),  EnergyB.Data());


    TString hname_defau_PtA       = TString::Format("h_Pt_FastJets%sMultLam50_%s", Radius.Data(),  EnergyA.Data());
    TString hname_defau_PtB       = TString::Format("h_Pt_FastJets%sMultLam50_%s", Radius.Data(),  EnergyB.Data());
    TString hname_nompi_PtA       = TString::Format("h_Pt_nompi_FastJets%sMultLam50_%s", Radius.Data(),  EnergyA.Data());
    TString hname_nompi_PtB       = TString::Format("h_Pt_nompi_FastJets%sMultLam50_%s", Radius.Data(),  EnergyB.Data());
    TString hname_trimm_PtA       = TString::Format("h_Pt_trim_FastJets%sMultLam50_%s", Radius.Data(),  EnergyA.Data());
    TString hname_trimm_PtB       = TString::Format("h_Pt_trim_FastJets%sMultLam50_%s", Radius.Data(),  EnergyB.Data());
    TString hname_defau_EtaA      = TString::Format("h_Eta_FastJets%sMultLam50_%s", Radius.Data(),  EnergyA.Data());
    TString hname_defau_EtaB      = TString::Format("h_Eta_FastJets%sMultLam50_%s", Radius.Data(),  EnergyB.Data());
    TString hname_nompi_EtaA      = TString::Format("h_Eta_nompi_FastJets%sMultLam50_%s", Radius.Data(),  EnergyA.Data());
    TString hname_nompi_EtaB      = TString::Format("h_Eta_nompi_FastJets%sMultLam50_%s", Radius.Data(),  EnergyB.Data());
    TString hname_trimm_EtaA      = TString::Format("h_Eta_trim_FastJets%sMultLam50_%s", Radius.Data(),  EnergyA.Data());
    TString hname_trimm_EtaB      = TString::Format("h_Eta_trim_FastJets%sMultLam50_%s", Radius.Data(),  EnergyB.Data());
    TString mmdt_hname_defau_PtA  = TString::Format("h_Pt_mmdt_FastJets%sMultLam50_%s", Radius.Data(),  EnergyA.Data());
    TString mmdt_hname_defau_PtB  = TString::Format("h_Pt_mmdt_FastJets%sMultLam50_%s", Radius.Data(),  EnergyB.Data());
    TString mmdt_hname_nompi_PtA  = TString::Format("h_Pt_nompi_mmdt_FastJets%sMultLam50_%s", Radius.Data(),  EnergyA.Data());
    TString mmdt_hname_nompi_PtB  = TString::Format("h_Pt_nompi_mmdt_FastJets%sMultLam50_%s", Radius.Data(),  EnergyB.Data());
    TString mmdt_hname_trimm_PtA  = TString::Format("h_Pt_trim_mmdt_FastJets%sMultLam50_%s", Radius.Data(),  EnergyA.Data());
    TString mmdt_hname_trimm_PtB  = TString::Format("h_Pt_trim_mmdt_FastJets%sMultLam50_%s", Radius.Data(),  EnergyB.Data());

    TString mmdt_hname_defau_A  = TString::Format("h_mmdt_FastJets%sMultLam50_%s", Radius.Data(),  EnergyA.Data());
    TString mmdt_hname_defau_B  = TString::Format("h_mmdt_FastJets%sMultLam50_%s", Radius.Data(),  EnergyB.Data());
    TString mmdt_hname_nompi_A  = TString::Format("h_nompi_mmdt_FastJets%sMultLam50_%s", Radius.Data(),  EnergyA.Data());
    TString mmdt_hname_nompi_B  = TString::Format("h_nompi_mmdt_FastJets%sMultLam50_%s", Radius.Data(),  EnergyB.Data());
    TString mmdt_hname_trimm_A  = TString::Format("h_trim_mmdt_FastJets%sMultLam50_%s", Radius.Data(),  EnergyA.Data());
    TString mmdt_hname_trimm_B  = TString::Format("h_trim_mmdt_FastJets%sMultLam50_%s", Radius.Data(),  EnergyB.Data());

    TString mmdt_hname_defau_EtaA = TString::Format("h_Eta_mmdt_FastJets%sMultLam50_%s", Radius.Data(),  EnergyA.Data());
    TString mmdt_hname_defau_EtaB = TString::Format("h_Eta_mmdt_FastJets%sMultLam50_%s", Radius.Data(),  EnergyB.Data());
    TString mmdt_hname_nompi_EtaA = TString::Format("h_Eta_nompi_mmdt_FastJets%sMultLam50_%s", Radius.Data(),  EnergyA.Data());
    TString mmdt_hname_nompi_EtaB = TString::Format("h_Eta_nompi_mmdt_FastJets%sMultLam50_%s", Radius.Data(),  EnergyB.Data());
    TString mmdt_hname_trimm_EtaA = TString::Format("h_Eta_trim_mmdt_FastJets%sMultLam50_%s", Radius.Data(),  EnergyA.Data());
    TString mmdt_hname_trimm_EtaB = TString::Format("h_Eta_trim_mmdt_FastJets%sMultLam50_%s", Radius.Data(),  EnergyB.Data());


    TH1D* h_defau_A       = (TH1D*)rfile->Get(hname_defau_A      .Data() );
    TH1D* h_defau_B       = (TH1D*)rfile->Get(hname_defau_B      .Data() );
    TH1D* h_nompi_A       = (TH1D*)rfile->Get(hname_nompi_A      .Data() );
    TH1D* h_nompi_B       = (TH1D*)rfile->Get(hname_nompi_B      .Data() );
    TH1D* h_trimm_A       = (TH1D*)rfile->Get(hname_trimm_A      .Data() );
    TH1D* h_trimm_B       = (TH1D*)rfile->Get(hname_trimm_B      .Data() );

    TH1D* h_defau_PtA       = (TH1D*)rfile->Get(hname_defau_PtA      .Data() );
    TH1D* h_defau_PtB       = (TH1D*)rfile->Get(hname_defau_PtB      .Data() );
    TH1D* h_nompi_PtA       = (TH1D*)rfile->Get(hname_nompi_PtA      .Data() );
    TH1D* h_nompi_PtB       = (TH1D*)rfile->Get(hname_nompi_PtB      .Data() );
    TH1D* h_trimm_PtA       = (TH1D*)rfile->Get(hname_trimm_PtA      .Data() );
    TH1D* h_trimm_PtB       = (TH1D*)rfile->Get(hname_trimm_PtB      .Data() );
    TH1D* h_defau_EtaA      = (TH1D*)rfile->Get(hname_defau_EtaA     .Data() );
    TH1D* h_defau_EtaB      = (TH1D*)rfile->Get(hname_defau_EtaB     .Data() );
    TH1D* h_nompi_EtaA      = (TH1D*)rfile->Get(hname_nompi_EtaA     .Data() );
    TH1D* h_nompi_EtaB      = (TH1D*)rfile->Get(hname_nompi_EtaB     .Data() );
    TH1D* h_trimm_EtaA      = (TH1D*)rfile->Get(hname_trimm_EtaA     .Data() );
    TH1D* h_trimm_EtaB      = (TH1D*)rfile->Get(hname_trimm_EtaB     .Data() );

    TH1D* mmdt_h_defau_A  = (TH1D*)rfile->Get(mmdt_hname_defau_A .Data() );
    TH1D* mmdt_h_defau_B  = (TH1D*)rfile->Get(mmdt_hname_defau_B .Data() );
    TH1D* mmdt_h_nompi_A  = (TH1D*)rfile->Get(mmdt_hname_nompi_A .Data() );
    TH1D* mmdt_h_nompi_B  = (TH1D*)rfile->Get(mmdt_hname_nompi_B .Data() );
    TH1D* mmdt_h_trimm_A  = (TH1D*)rfile->Get(mmdt_hname_trimm_A .Data() );
    TH1D* mmdt_h_trimm_B  = (TH1D*)rfile->Get(mmdt_hname_trimm_B .Data() );

    TH1D* mmdt_h_defau_PtA  = (TH1D*)rfile->Get(mmdt_hname_defau_PtA .Data() );
    TH1D* mmdt_h_defau_PtB  = (TH1D*)rfile->Get(mmdt_hname_defau_PtB .Data() );
    TH1D* mmdt_h_nompi_PtA  = (TH1D*)rfile->Get(mmdt_hname_nompi_PtA .Data() );
    TH1D* mmdt_h_nompi_PtB  = (TH1D*)rfile->Get(mmdt_hname_nompi_PtB .Data() );
    TH1D* mmdt_h_trimm_PtA  = (TH1D*)rfile->Get(mmdt_hname_trimm_PtA .Data() );
    TH1D* mmdt_h_trimm_PtB  = (TH1D*)rfile->Get(mmdt_hname_trimm_PtB .Data() );
    TH1D* mmdt_h_defau_EtaA = (TH1D*)rfile->Get(mmdt_hname_defau_EtaA.Data() );
    TH1D* mmdt_h_defau_EtaB = (TH1D*)rfile->Get(mmdt_hname_defau_EtaB.Data() );
    TH1D* mmdt_h_nompi_EtaA = (TH1D*)rfile->Get(mmdt_hname_nompi_EtaA.Data() );
    TH1D* mmdt_h_nompi_EtaB = (TH1D*)rfile->Get(mmdt_hname_nompi_EtaB.Data() );
    TH1D* mmdt_h_trimm_EtaA = (TH1D*)rfile->Get(mmdt_hname_trimm_EtaA.Data() );
    TH1D* mmdt_h_trimm_EtaB = (TH1D*)rfile->Get(mmdt_hname_trimm_EtaB.Data() );

    mmdt_h_defau_A ->SetLineStyle(2);
    mmdt_h_defau_B ->SetLineStyle(2);
    mmdt_h_nompi_A ->SetLineStyle(2);
    mmdt_h_nompi_B ->SetLineStyle(2);
    mmdt_h_trimm_A ->SetLineStyle(2);
    mmdt_h_trimm_B ->SetLineStyle(2);

    mmdt_h_defau_PtA ->SetLineStyle(2);
    mmdt_h_defau_PtB ->SetLineStyle(2);
    mmdt_h_nompi_PtA ->SetLineStyle(2);
    mmdt_h_nompi_PtB ->SetLineStyle(2);
    mmdt_h_trimm_PtA ->SetLineStyle(2);
    mmdt_h_trimm_PtB ->SetLineStyle(2);
    mmdt_h_defau_EtaA->SetLineStyle(2);
    mmdt_h_defau_EtaB->SetLineStyle(2);
    mmdt_h_nompi_EtaA->SetLineStyle(2);
    mmdt_h_nompi_EtaB->SetLineStyle(2);
    mmdt_h_trimm_EtaA->SetLineStyle(2);
    mmdt_h_trimm_EtaB->SetLineStyle(2);

    h_defau_A      ->SetLineColor(1);
    h_nompi_A      ->SetLineColor(2);
    h_trimm_A      ->SetLineColor(4);

    h_defau_PtA      ->SetLineColor(1);
    h_nompi_PtA      ->SetLineColor(2);
    h_trimm_PtA      ->SetLineColor(4);
    h_defau_EtaA     ->SetLineColor(1);
    h_nompi_EtaA     ->SetLineColor(2);
    h_trimm_EtaA     ->SetLineColor(4);
    mmdt_h_defau_PtA ->SetLineColor(1);
    mmdt_h_nompi_PtA ->SetLineColor(2);
    mmdt_h_trimm_PtA ->SetLineColor(4);

    mmdt_h_defau_A ->SetLineColor(1);
    mmdt_h_nompi_A ->SetLineColor(2);
    mmdt_h_trimm_A ->SetLineColor(4);

    mmdt_h_defau_EtaA->SetLineColor(1);
    mmdt_h_nompi_EtaA->SetLineColor(2);
    mmdt_h_trimm_EtaA->SetLineColor(4);

    h_defau_B      ->SetLineColor(1);
    h_nompi_B      ->SetLineColor(2);
    h_trimm_B      ->SetLineColor(4);
    
    h_defau_PtB      ->SetLineColor(1);
    h_nompi_PtB      ->SetLineColor(2);
    h_trimm_PtB      ->SetLineColor(4);
    h_defau_EtaB     ->SetLineColor(1);
    h_nompi_EtaB     ->SetLineColor(2);
    h_trimm_EtaB     ->SetLineColor(4);

    mmdt_h_defau_B ->SetLineColor(1);
    mmdt_h_nompi_B ->SetLineColor(2);
    mmdt_h_trimm_B ->SetLineColor(4);

    mmdt_h_defau_PtB ->SetLineColor(1);
    mmdt_h_nompi_PtB ->SetLineColor(2);
    mmdt_h_trimm_PtB ->SetLineColor(4);
    mmdt_h_defau_EtaB->SetLineColor(1);
    mmdt_h_nompi_EtaB->SetLineColor(2);
    mmdt_h_trimm_EtaB->SetLineColor(4);

    TLegend * leg = new TLegend(0.64,0.64,0.88,0.88);
    leg->SetBorderSize(0);
    leg->AddEntry(h_defau_A     , "Default" , "l");
    leg->AddEntry(h_nompi_A     , "NoMpi" , "l");
    leg->AddEntry(h_trimm_A     , "Trimmed" , "l");
    leg->AddEntry(mmdt_h_defau_A, "mmdt Default" , "l");
    leg->AddEntry(mmdt_h_nompi_A, "mmdt NoMpi" , "l");
    leg->AddEntry(mmdt_h_trimm_A, "mmdt Trimmed" , "l");
    leg->AddEntry((TObject*)0,  TString::Format("Energy = %s GeV", EnergyA.Data() ) , "");
    leg->AddEntry((TObject*)0,  TString::Format("R = %s", GetRStr(Radius).Data() ) , "");
    

    TLegend * legB = new TLegend(0.64,0.64,0.88,0.88);
    legB->SetBorderSize(0);
    legB->AddEntry(h_defau_A     , "Default" , "l");
    legB->AddEntry(h_nompi_A     , "NoMpi" , "l");
    legB->AddEntry(h_trimm_A     , "Trimmed" , "l");
    legB->AddEntry(mmdt_h_defau_A, "mmdt Default" , "l");
    legB->AddEntry(mmdt_h_nompi_A, "mmdt NoMpi" , "l");
    legB->AddEntry(mmdt_h_trimm_A, "mmdt Trimmed" , "l");
    legB->AddEntry((TObject*)0,  TString::Format("Energy = %s GeV", EnergyB.Data() ) , "");
    legB->AddEntry((TObject*)0,  TString::Format("R = %s", GetRStr(Radius).Data() ) , "");

    TCanvas * canMultA = new TCanvas( TString::Format("Mult_%s" , EnergyA.Data()), TString::Format("Mult_%s" , EnergyA.Data()), 0,0,1600,1600);
    canMultA->cd();
    vector<double> maxs;
    maxs.push_back(h_defau_A     ->GetMaximum());
    maxs.push_back(h_nompi_A     ->GetMaximum());
    maxs.push_back(h_trimm_A     ->GetMaximum());
    maxs.push_back(mmdt_h_defau_A->GetMaximum());
    maxs.push_back(mmdt_h_nompi_A->GetMaximum());
    maxs.push_back(mmdt_h_trimm_A->GetMaximum());
    h_defau_A->SetMaximum(*max_element(maxs.begin(), maxs.end()) *1.3);
    maxs.clear();

    h_defau_A->GetXaxis()->SetTitle("Multiplicity of jets");
    h_defau_A->GetYaxis()->SetTitle("Events / Integral");
    h_defau_A     ->Draw("hist same");
    h_nompi_A     ->Draw("hist same");
    h_trimm_A     ->Draw("hist same");
    mmdt_h_defau_A->Draw("hist same");
    mmdt_h_nompi_A->Draw("hist same");
    mmdt_h_trimm_A->Draw("hist same");
    leg->Draw("same");
    TCanvas * canMultB = new TCanvas( TString::Format("Mult_%s" , EnergyB.Data()), TString::Format("Mult_%s" , EnergyB.Data()), 0,0,1600,1600);
    canMultB->cd();
    maxs.push_back(h_defau_B     ->GetMaximum());
    maxs.push_back(h_nompi_B     ->GetMaximum());
    maxs.push_back(h_trimm_B     ->GetMaximum());
    maxs.push_back(mmdt_h_defau_B->GetMaximum());
    maxs.push_back(mmdt_h_nompi_B->GetMaximum());
    maxs.push_back(mmdt_h_trimm_B->GetMaximum());
    h_defau_B->SetMaximum(*max_element(maxs.begin(), maxs.end()) *1.3);
    maxs.clear();
    h_defau_B->GetXaxis()->SetTitle("Multiplicity of jets");
    h_defau_B->GetYaxis()->SetTitle("Events / Integral");
    h_defau_B->Draw("hist same");
    h_nompi_B->Draw("hist same");
    h_trimm_B->Draw("hist same");
    mmdt_h_defau_B->Draw("hist same");
    mmdt_h_nompi_B->Draw("hist same");
    mmdt_h_trimm_B->Draw("hist same");
    legB->Draw("same");
    TCanvas * canptA = new TCanvas( TString::Format("Pt_%s" , EnergyA.Data()), TString::Format("Pt_%s" , EnergyA.Data()), 0,0,1600,1600);
    canptA->cd();
    maxs.push_back(h_defau_PtA     ->GetMaximum());
    maxs.push_back(h_nompi_PtA     ->GetMaximum());
    maxs.push_back(h_trimm_PtA     ->GetMaximum());
    maxs.push_back(mmdt_h_defau_PtA->GetMaximum());
    maxs.push_back(mmdt_h_nompi_PtA->GetMaximum());
    maxs.push_back(mmdt_h_trimm_PtA->GetMaximum());
    h_defau_PtA->SetMaximum(*max_element(maxs.begin(), maxs.end()) *1.3);
    maxs.clear();
    h_defau_PtA->GetXaxis()->SetTitle("p_{T} GeV");
    h_defau_PtA->GetYaxis()->SetTitle("Events / Integral");
    h_defau_PtA->Draw("hist same");
    h_nompi_PtA->Draw("hist same");
    h_trimm_PtA->Draw("hist same");
    mmdt_h_defau_PtA->Draw("hist same");
    mmdt_h_nompi_PtA->Draw("hist same");
    mmdt_h_trimm_PtA->Draw("hist same");
    leg->Draw("same");
    TCanvas * canptB = new TCanvas( TString::Format("Pt_%s" , EnergyB.Data()), TString::Format("Pt_%s" , EnergyB.Data()), 0,0,1600,1600);
    canptB->cd();
    maxs.push_back(h_defau_PtB     ->GetMaximum());
    maxs.push_back(h_nompi_PtB     ->GetMaximum());
    maxs.push_back(h_trimm_PtB     ->GetMaximum());
    maxs.push_back(mmdt_h_defau_PtB->GetMaximum());
    maxs.push_back(mmdt_h_nompi_PtB->GetMaximum());
    maxs.push_back(mmdt_h_trimm_PtB->GetMaximum());
    h_defau_PtB->SetMaximum(*max_element(maxs.begin(), maxs.end()) *1.3);
    maxs.clear();
    h_defau_PtB->GetXaxis()->SetTitle("p_{T} GeV");
    h_defau_PtB->GetYaxis()->SetTitle("Events / Integral");
    h_defau_PtB->Draw("hist same");
    h_nompi_PtB->Draw("hist same");
    h_trimm_PtB->Draw("hist same");
    mmdt_h_defau_PtB->Draw("hist same");
    mmdt_h_nompi_PtB->Draw("hist same");
    mmdt_h_trimm_PtB->Draw("hist same");
    legB->Draw("same");
    TCanvas * canEtaA = new TCanvas(TString::Format("Eta_%s", EnergyA.Data()), TString::Format("Eta_%s", EnergyA.Data()), 0,0,1600,1600);
    canEtaA->cd();
    maxs.push_back(h_defau_EtaA     ->GetMaximum());
    maxs.push_back(h_nompi_EtaA     ->GetMaximum());
    maxs.push_back(h_trimm_EtaA     ->GetMaximum());
    maxs.push_back(mmdt_h_defau_EtaA->GetMaximum());
    maxs.push_back(mmdt_h_nompi_EtaA->GetMaximum());
    maxs.push_back(mmdt_h_trimm_EtaA->GetMaximum());
    h_defau_EtaA->SetMaximum(*max_element(maxs.begin(), maxs.end()) *1.3);
    maxs.clear();
    h_defau_EtaA->GetXaxis()->SetTitle("#eta");
    h_defau_EtaA->GetYaxis()->SetTitle("Events / Integral");
    h_defau_EtaA->Draw("hist same");
    h_nompi_EtaA->Draw("hist same");
    h_trimm_EtaA->Draw("hist same");
    mmdt_h_defau_EtaA->Draw("hist same");
    mmdt_h_nompi_EtaA->Draw("hist same");
    mmdt_h_trimm_EtaA->Draw("hist same");
    leg->Draw("same");
    TCanvas * canEtaB = new TCanvas(TString::Format("Eta_%s", EnergyB.Data()), TString::Format("Eta_%s", EnergyB.Data()), 0,0,1600,1600);
    canEtaB->cd();
    maxs.push_back(h_defau_EtaB     ->GetMaximum());
    maxs.push_back(h_nompi_EtaB     ->GetMaximum());
    maxs.push_back(h_trimm_EtaB     ->GetMaximum());
    maxs.push_back(mmdt_h_defau_EtaB->GetMaximum());
    maxs.push_back(mmdt_h_nompi_EtaB->GetMaximum());
    maxs.push_back(mmdt_h_trimm_EtaB->GetMaximum());
    h_defau_EtaB->SetMaximum(*max_element(maxs.begin(), maxs.end()) *1.3);
    maxs.clear();
    h_defau_EtaB->GetXaxis()->SetTitle("#eta");
    h_defau_EtaB->GetYaxis()->SetTitle("Events / Integral");
    h_defau_EtaB->Draw("hist same");
    h_nompi_EtaB->Draw("hist same");
    h_trimm_EtaB->Draw("hist same");
    mmdt_h_defau_EtaB->Draw("hist same");
    mmdt_h_nompi_EtaB->Draw("hist same");
    mmdt_h_trimm_EtaB->Draw("hist same");
    legB->Draw("same");

    canMultA->SaveAs(TString::Format("./QGcontrol/R%s_%s.png", Radius.Data(), canMultA->GetName()  ));
    canptA->SaveAs(TString::Format("./QGcontrol/R%s_%s.png", Radius.Data(), canptA->GetName()  ));
    canEtaA->SaveAs(TString::Format("./QGcontrol/R%s_%s.png", Radius.Data(), canEtaA->GetName()  ));
    canMultB->SaveAs(TString::Format("./QGcontrol/R%s_%s.png", Radius.Data(), canMultB->GetName()  ));
    canptB->SaveAs(TString::Format("./QGcontrol/R%s_%s.png", Radius.Data(), canptB->GetName()  ));
    canEtaB->SaveAs(TString::Format("./QGcontrol/R%s_%s.png", Radius.Data(), canEtaB->GetName()  ));

    canMultA->SaveAs(TString::Format("./QGcontrol/R%s_%s.pdf", Radius.Data(), canMultA->GetName()  ));
    canptA->SaveAs(TString::Format("./QGcontrol/R%s_%s.pdf", Radius.Data(), canptA->GetName()  ));
    canEtaA->SaveAs(TString::Format("./QGcontrol/R%s_%s.pdf", Radius.Data(), canEtaA->GetName()  ));
    canMultB->SaveAs(TString::Format("./QGcontrol/R%s_%s.pdf", Radius.Data(), canMultB->GetName()  ));
    canptB->SaveAs(TString::Format("./QGcontrol/R%s_%s.pdf", Radius.Data(), canptB->GetName()  ));
    canEtaB->SaveAs(TString::Format("./QGcontrol/R%s_%s.pdf", Radius.Data(), canEtaB->GetName()  ));


    
    return 0;

}
float ComputeInvariantMass(float pt1, float eta1, float phi1, float mass1, float pt2, float eta2, float phi2, float mass2) {
    const ROOT::Math::PtEtaPhiMVector p1(pt1, eta1, phi1, mass1);
    const ROOT::Math::PtEtaPhiMVector p2(pt2, eta2, phi2, mass2);
    return (p1 + p2).M();
}

int CompareShapes(TString Cut = "", float YMax = 0.12){

    //analyzed_histos_boosted_QCD_ptj1j2min60_ptj1j2max200.root
    //analyzed_histos_boosted_QCD_ptj1min200_ptj2min60max200.root
    //analyzed_histos_boosted_Zprime.root
    //analyzed_histos_boosted_Y0_w100G.root
    //analyzed_histos_boosted_QCD_pp_2b2j_LO_matched_ptj1j2min200.root
    //analyzed_histos_boosted_Y0.root
    //analyzed_histos_delphes_SMtt_closure.root
    TFile * fileSM = new TFile("analyzed_histos_delphes_pp2_4top_hadr_decay_tttt_SM.root", "read");
    TFile * fileY0 = new TFile("analyzed_histos_delphes_pp2_4top_hadr_decay_tty0_to_jets.root", "read");
    //TFile * fileY0 = new TFile("analyzed_histos_boosted_Y0.root", "read");
    //TFile * fileY0 = new TFile("analyzed_histos_boosted_Zprime.root", "read");
    //TFile * fileY0 = new TFile("analyzed_histos_boosted_Y0_w100G.root", "read");

    
    TTree * TTree_ML_SM = (TTree*)fileSM->Get("TTree_ML");
    TTree * TTree_ML_Y0 = (TTree*)fileY0->Get("TTree_ML");

    vector<Double_t> bins = {0.,100.,200.,300.,400.,500.,600.,700.,800.,900.,1000.};

    TH1D * inv_mass_SM_01 = new TH1D("inv_mass_SM_01", "inv_mass_SM_01", 100, 0, 4000.);
    TH1D * inv_mass_Y0_01 = new TH1D("inv_mass_Y0_01", "inv_mass_Y0_01", 100, 0, 4000.);
    TH1D * inv_mass_SM_02 = new TH1D("inv_mass_SM_02", "inv_mass_SM_02", 100, 0, 4000.);
    TH1D * inv_mass_Y0_02 = new TH1D("inv_mass_Y0_02", "inv_mass_Y0_02", 100, 0, 4000.);
    TH1D * inv_mass_SM_03 = new TH1D("inv_mass_SM_03", "inv_mass_SM_03", 100, 0, 4000.);
    TH1D * inv_mass_Y0_03 = new TH1D("inv_mass_Y0_03", "inv_mass_Y0_03", 100, 0, 4000.);
    TH1D * inv_mass_SM_12 = new TH1D("inv_mass_SM_12", "inv_mass_SM_12", 100, 0, 4000.);
    TH1D * inv_mass_Y0_12 = new TH1D("inv_mass_Y0_12", "inv_mass_Y0_12", 100, 0, 4000.);
    TH1D * inv_mass_SM_13 = new TH1D("inv_mass_SM_13", "inv_mass_SM_13", 100, 0, 4000.);
    TH1D * inv_mass_Y0_13 = new TH1D("inv_mass_Y0_13", "inv_mass_Y0_13", 100, 0, 4000.);
    TH1D * inv_mass_SM_23 = new TH1D("inv_mass_SM_23", "inv_mass_SM_23", 100, 0, 4000.);
    TH1D * inv_mass_Y0_23 = new TH1D("inv_mass_Y0_23", "inv_mass_Y0_23", 100, 0, 4000.);

    //TH1D * inv_mass_Y0_01 = new TH1D("inv_mass_Y0_01", "inv_mass_Y0_01", 100, 0, 4000.);
    //TH1D * inv_mass_Y0_02 = new TH1D("inv_mass_Y0_02", "inv_mass_Y0_02", 100, 0, 4000.);
    //TH1D * inv_mass_Y0_03 = new TH1D("inv_mass_Y0_03", "inv_mass_Y0_03", 100, 0, 4000.);
    //TH1D * inv_mass_Y0_12 = new TH1D("inv_mass_Y0_12", "inv_mass_Y0_12", 100, 0, 4000.);
    //TH1D * inv_mass_Y0_13 = new TH1D("inv_mass_Y0_13", "inv_mass_Y0_13", 100, 0, 4000.);
    //TH1D * inv_mass_Y0_23 = new TH1D("inv_mass_Y0_23", "inv_mass_Y0_23", 100, 0, 4000.);

    
    TTree_ML_SM->Draw("ComputeInvariantMass(MLParticleLJetPt[0], MLParticleLJetEta[0], MLParticleLJetPhi[0], MLParticleLJetMass[0], MLParticleLJetPt[1], MLParticleLJetEta[1], MLParticleLJetPhi[1], MLParticleLJetMass[1]) >> inv_mass_SM_01", Cut.Data(), "goff");
    TTree_ML_Y0->Draw("ComputeInvariantMass(MLParticleLJetPt[0], MLParticleLJetEta[0], MLParticleLJetPhi[0], MLParticleLJetMass[0], MLParticleLJetPt[1], MLParticleLJetEta[1], MLParticleLJetPhi[1], MLParticleLJetMass[1]) >> inv_mass_Y0_01", Cut.Data(), "goff");
    TTree_ML_SM->Draw("ComputeInvariantMass(MLParticleLJetPt[0], MLParticleLJetEta[0], MLParticleLJetPhi[0], MLParticleLJetMass[0], MLParticleLJetPt[2], MLParticleLJetEta[2], MLParticleLJetPhi[2], MLParticleLJetMass[2]) >> inv_mass_SM_02", Cut.Data(), "goff");
    TTree_ML_Y0->Draw("ComputeInvariantMass(MLParticleLJetPt[0], MLParticleLJetEta[0], MLParticleLJetPhi[0], MLParticleLJetMass[0], MLParticleLJetPt[2], MLParticleLJetEta[2], MLParticleLJetPhi[2], MLParticleLJetMass[2]) >> inv_mass_Y0_02", Cut.Data(), "goff");
    TTree_ML_SM->Draw("ComputeInvariantMass(MLParticleLJetPt[0], MLParticleLJetEta[0], MLParticleLJetPhi[0], MLParticleLJetMass[0], MLParticleLJetPt[3], MLParticleLJetEta[3], MLParticleLJetPhi[3], MLParticleLJetMass[3]) >> inv_mass_SM_03", Cut.Data(), "goff");
    TTree_ML_Y0->Draw("ComputeInvariantMass(MLParticleLJetPt[0], MLParticleLJetEta[0], MLParticleLJetPhi[0], MLParticleLJetMass[0], MLParticleLJetPt[3], MLParticleLJetEta[3], MLParticleLJetPhi[3], MLParticleLJetMass[3]) >> inv_mass_Y0_03", Cut.Data(), "goff");
    TTree_ML_SM->Draw("ComputeInvariantMass(MLParticleLJetPt[1], MLParticleLJetEta[1], MLParticleLJetPhi[1], MLParticleLJetMass[1], MLParticleLJetPt[2], MLParticleLJetEta[2], MLParticleLJetPhi[2], MLParticleLJetMass[2]) >> inv_mass_SM_12", Cut.Data(), "goff");
    TTree_ML_Y0->Draw("ComputeInvariantMass(MLParticleLJetPt[1], MLParticleLJetEta[1], MLParticleLJetPhi[1], MLParticleLJetMass[1], MLParticleLJetPt[2], MLParticleLJetEta[2], MLParticleLJetPhi[2], MLParticleLJetMass[2]) >> inv_mass_Y0_12", Cut.Data(), "goff");
    TTree_ML_SM->Draw("ComputeInvariantMass(MLParticleLJetPt[1], MLParticleLJetEta[1], MLParticleLJetPhi[1], MLParticleLJetMass[1], MLParticleLJetPt[3], MLParticleLJetEta[3], MLParticleLJetPhi[3], MLParticleLJetMass[3]) >> inv_mass_SM_13", Cut.Data(), "goff");
    TTree_ML_Y0->Draw("ComputeInvariantMass(MLParticleLJetPt[1], MLParticleLJetEta[1], MLParticleLJetPhi[1], MLParticleLJetMass[1], MLParticleLJetPt[3], MLParticleLJetEta[3], MLParticleLJetPhi[3], MLParticleLJetMass[3]) >> inv_mass_Y0_13", Cut.Data(), "goff");
    TTree_ML_SM->Draw("ComputeInvariantMass(MLParticleLJetPt[2], MLParticleLJetEta[2], MLParticleLJetPhi[2], MLParticleLJetMass[2], MLParticleLJetPt[3], MLParticleLJetEta[3], MLParticleLJetPhi[3], MLParticleLJetMass[3]) >> inv_mass_SM_23", Cut.Data(), "goff");
    TTree_ML_Y0->Draw("ComputeInvariantMass(MLParticleLJetPt[2], MLParticleLJetEta[2], MLParticleLJetPhi[2], MLParticleLJetMass[2], MLParticleLJetPt[3], MLParticleLJetEta[3], MLParticleLJetPhi[3], MLParticleLJetMass[3]) >> inv_mass_Y0_23", Cut.Data(), "goff");

    inv_mass_Y0_01->SetLineColor(1);
    inv_mass_Y0_02->SetLineColor(2);
    inv_mass_Y0_03->SetLineColor(3);
    inv_mass_Y0_12->SetLineColor(4);
    inv_mass_Y0_13->SetLineColor(6);
    inv_mass_Y0_23->SetLineColor(7);

    inv_mass_SM_01->SetLineStyle(2);
    inv_mass_SM_02->SetLineStyle(2);
    inv_mass_SM_03->SetLineStyle(2);
    inv_mass_SM_12->SetLineStyle(2);
    inv_mass_SM_13->SetLineStyle(2);
    inv_mass_SM_23->SetLineStyle(2);

    inv_mass_SM_01->SetLineColor(1);
    inv_mass_SM_02->SetLineColor(2);
    inv_mass_SM_03->SetLineColor(3);
    inv_mass_SM_12->SetLineColor(4);
    inv_mass_SM_13->SetLineColor(6);
    inv_mass_SM_23->SetLineColor(7);
    TLegend * leg = new TLegend(0.4,0.4,0.86,0.86);

    leg->AddEntry(inv_mass_SM_01, "dijet inv. mass SM jet_01");
    leg->AddEntry(inv_mass_SM_02, "dijet inv. mass SM jet_02");
    leg->AddEntry(inv_mass_SM_03, "dijet inv. mass SM jet_03");
    leg->AddEntry(inv_mass_SM_12, "dijet inv. mass SM jet_12");
    leg->AddEntry(inv_mass_SM_13, "dijet inv. mass SM jet_13");
    leg->AddEntry(inv_mass_SM_23, "dijet inv. mass SM jet_23");

    leg->AddEntry(inv_mass_Y0_01, "dijet inv. mass Y0 jet_01");
    leg->AddEntry(inv_mass_Y0_02, "dijet inv. mass Y0 jet_02");
    leg->AddEntry(inv_mass_Y0_03, "dijet inv. mass Y0 jet_03");
    leg->AddEntry(inv_mass_Y0_12, "dijet inv. mass Y0 jet_12");
    leg->AddEntry(inv_mass_Y0_13, "dijet inv. mass Y0 jet_13");
    leg->AddEntry(inv_mass_Y0_23, "dijet inv. mass Y0 jet_23");

    TCanvas * can = new TCanvas("shapes", "shapes", 0,0,1600,1600);
    can->cd();
    gStyle->SetOptStat(0);
    
    inv_mass_SM_01->SetMinimum(0.);
    inv_mass_Y0_01->SetMinimum(0.);
    inv_mass_SM_02->SetMinimum(0.);
    inv_mass_Y0_02->SetMinimum(0.);
    inv_mass_SM_03->SetMinimum(0.);
    inv_mass_Y0_03->SetMinimum(0.);
    inv_mass_SM_12->SetMinimum(0.);
    inv_mass_Y0_12->SetMinimum(0.);
    inv_mass_SM_13->SetMinimum(0.);
    inv_mass_Y0_13->SetMinimum(0.);
    inv_mass_SM_23->SetMinimum(0.);
    inv_mass_Y0_23->SetMinimum(0.);

    inv_mass_SM_01->Scale(1./inv_mass_SM_01->Integral());
    inv_mass_Y0_01->Scale(1./inv_mass_Y0_01->Integral());
    inv_mass_SM_02->Scale(1./inv_mass_SM_02->Integral());
    inv_mass_Y0_02->Scale(1./inv_mass_Y0_02->Integral());
    inv_mass_SM_03->Scale(1./inv_mass_SM_03->Integral());
    inv_mass_Y0_03->Scale(1./inv_mass_Y0_03->Integral());
    inv_mass_SM_12->Scale(1./inv_mass_SM_12->Integral());
    inv_mass_Y0_12->Scale(1./inv_mass_Y0_12->Integral());
    inv_mass_SM_13->Scale(1./inv_mass_SM_13->Integral());
    inv_mass_Y0_13->Scale(1./inv_mass_Y0_13->Integral());
    inv_mass_SM_23->Scale(1./inv_mass_SM_23->Integral());
    inv_mass_Y0_23->Scale(1./inv_mass_Y0_23->Integral());

    inv_mass_SM_01->SetMaximum(YMax);
    inv_mass_Y0_01->SetMaximum(YMax);
    inv_mass_SM_02->SetMaximum(YMax);
    inv_mass_Y0_02->SetMaximum(YMax);
    inv_mass_SM_03->SetMaximum(YMax);
    inv_mass_Y0_03->SetMaximum(YMax);
    inv_mass_SM_12->SetMaximum(YMax);
    inv_mass_Y0_12->SetMaximum(YMax);
    inv_mass_SM_13->SetMaximum(YMax);
    inv_mass_Y0_13->SetMaximum(YMax);
    inv_mass_SM_23->SetMaximum(YMax);
    inv_mass_Y0_23->SetMaximum(YMax);
    
    inv_mass_SM_01->GetYaxis()->SetRangeUser(0.,YMax);
    inv_mass_Y0_01->GetYaxis()->SetRangeUser(0.,YMax);
    inv_mass_SM_02->GetYaxis()->SetRangeUser(0.,YMax);
    inv_mass_Y0_02->GetYaxis()->SetRangeUser(0.,YMax);
    inv_mass_SM_03->GetYaxis()->SetRangeUser(0.,YMax);
    inv_mass_Y0_03->GetYaxis()->SetRangeUser(0.,YMax);
    inv_mass_SM_12->GetYaxis()->SetRangeUser(0.,YMax);
    inv_mass_Y0_12->GetYaxis()->SetRangeUser(0.,YMax);
    inv_mass_SM_13->GetYaxis()->SetRangeUser(0.,YMax);
    inv_mass_Y0_13->GetYaxis()->SetRangeUser(0.,YMax);
    inv_mass_SM_23->GetYaxis()->SetRangeUser(0.,YMax);
    inv_mass_Y0_23->GetYaxis()->SetRangeUser(0.,YMax);

    inv_mass_SM_01->SetTitle("");
    inv_mass_SM_01->Draw("hist e1 same");
    inv_mass_Y0_01->Draw("hist e1 same");
    inv_mass_SM_02->Draw("hist e1 same");
    inv_mass_Y0_02->Draw("hist e1 same");
    inv_mass_SM_03->Draw("hist e1 same");
    inv_mass_Y0_03->Draw("hist e1 same");
    inv_mass_SM_12->Draw("hist e1 same");
    inv_mass_Y0_12->Draw("hist e1 same");
    inv_mass_SM_13->Draw("hist e1 same");
    inv_mass_Y0_13->Draw("hist e1 same");
    inv_mass_SM_23->Draw("hist e1 same");
    inv_mass_Y0_23->Draw("hist e1 same");

    leg->SetBorderSize(0);
    leg->Draw("same");
    Cut = Cut.ReplaceAll(" ", "_");
    Cut = Cut.ReplaceAll("&&", "and");
    Cut = Cut.ReplaceAll("=", "eq");
    Cut = Cut.ReplaceAll(">", "gr");
    Cut = Cut.ReplaceAll("<", "sm");
    Cut = Cut.ReplaceAll("||", "or");
    Cut = Cut.ReplaceAll("(", "_lb_");
    Cut = Cut.ReplaceAll(")", "_rb_");
    Cut = TString::Format("_%s",Cut.Data());
    can->SaveAs(TString::Format("Spectra%s.pdf", Cut.Data()));
    can->SaveAs(TString::Format("Spectra%s.png", Cut.Data()));
    /*
    
    TString P0tr = "MLParticleLJetPt[0]";
    TString P0z = "MLParticleLJetPt[0]*(1./(TMath::Tan(2*TMath::ATan(TMath::Exp(-1.*MLParticleLJetEta[0])  ))))";
    //TString P0 = "MLParticleLJetPt[0]*(1.+1./(TMath::Tan(2*TMath::ATan(TMath::Exp(-1.*MLParticleLJetEta[0])  ))))";
    TString P0 = TString::Format("TMath::Sqrt(TMath::Power((%s) + (%s), 2))", P0tr.Data(), P0z.Data());
    
    TString M0 = "MLParticleLJetMass[0]";
    TString E0 = TString::Format("TMath::Sqrt((%s)*(%s) + (%s)*(%s))", P0.Data(), P0.Data(), M0.Data(), M0.Data() );

    TString P1tr = "MLParticleLJetPt[1]";
    TString P1z = "MLParticleLJetPt[1]*(1./(TMath::Tan(2*TMath::ATan(TMath::Exp(-1.*MLParticleLJetEta[1])  ))))";
    //TString P1 = "MLParticleLJetPt[1]*(1.+1./(TMath::Tan(2*TMath::ATan(TMath::Exp(-1.*MLParticleLJetEta[1])  ))))";
    TString P1 = TString::Format("TMath::Sqrt(TMath::Power((%s) + (%s), 2))", P1tr.Data(), P1z.Data());
    TString M1 = "MLParticleLJetMass[1]";
    TString E1 = TString::Format("TMath::Sqrt((%s)*(%s) + (%s)*(%s))", P1.Data(), P1.Data(), M1.Data(), M1.Data() );

    TString P2tr = "MLParticleLJetPt[2]";
    TString P2z = "MLParticleLJetPt[2]*(1./(TMath::Tan(2*TMath::ATan(TMath::Exp(-1.*MLParticleLJetEta[2])  ))))";
    //TString P2 = "MLParticleLJetPt[2]*(1.+1./(TMath::Tan(2*TMath::ATan(TMath::Exp(-1.*MLParticleLJetEta[2])  ))))";
    TString P2 = TString::Format("TMath::Sqrt(TMath::Power((%s) + (%s), 2))", P2tr.Data(), P2z.Data());
    TString M2 = "MLParticleLJetMass[2]";
    TString E2 = TString::Format("TMath::Sqrt((%s)*(%s) + (%s)*(%s))", P2.Data(), P2.Data(), M2.Data(), M2.Data() );

    TString P3tr = "MLParticleLJetPt[3]";
    TString P3z = "MLParticleLJetPt[3]*(1./(TMath::Tan(2*TMath::ATan(TMath::Exp(-1.*MLParticleLJetEta[3])  ))))";
    //TString P3 = "MLParticleLJetPt[3]*(1.+1./(TMath::Tan(2*TMath::ATan(TMath::Exp(-1.*MLParticleLJetEta[3])  ))))";
    TString P3 = TString::Format("TMath::Sqrt(TMath::Power((%s) + (%s), 2))", P3tr.Data(), P3z.Data());
    TString M3 = "MLParticleLJetMass[3]";
    TString E3 = TString::Format("TMath::Sqrt((%s)*(%s) + (%s)*(%s))", P3.Data(), P3.Data(), M3.Data(), M3.Data() );

    ////TTree_ML_Y0->Draw("MLParticleLJetMass", "MLParticleLJetML_TopTag == 1.");
    //TTree_ML_Y0->Draw(TString::Format("TMath::Sqrt( TMath::Power((%s) + (%s), 2) + TMath::Power((%s)-(%s),2) )", E0.Data(), E1.Data(), P0.Data(), P1.Data() ), "(MLParticleLJetML_TopTag == 1.)");
    //TTree_ML_Y0->Draw(TString::Format("TMath::Sqrt( TMath::Power((%s) + (%s), 2) + TMath::Power((%s)-(%s),2) )", E0.Data(), E2.Data(), P0.Data(), P2.Data() ), "(MLParticleLJetML_TopTag == 1.)", "same");
    //TTree_ML_Y0->Draw(TString::Format("TMath::Sqrt( TMath::Power((%s) + (%s), 2) + TMath::Power((%s)-(%s),2) )", E0.Data(), E3.Data(), P0.Data(), P3.Data() ), "(MLParticleLJetML_TopTag == 1.)", "same");
    //TTree_ML_Y0->Draw(TString::Format("TMath::Sqrt( TMath::Power((%s) + (%s), 2) + TMath::Power((%s)-(%s),2) )", E1.Data(), E2.Data(), P1.Data(), P2.Data() ), "(MLParticleLJetML_TopTag == 1.)", "same");
    ///TTree_ML_Y0->Draw(TString::Format("TMath::Sqrt( TMath::Power((%s) + (%s), 2) - TMath::Power(%s + %s, 2) - TMath::Power(%s + %s, 2)  )", E0.Data(), E1.Data(), P0tr.Data(), P1tr.Data(), P0z.Data(), P1z.Data() ), "(MLParticleLJetML_TopTag >= 0)&&(MLParticleLJetN == 2)", "");
    ///TTree_ML_SM->Draw(TString::Format("TMath::Sqrt( TMath::Power((%s) + (%s), 2) - TMath::Power(%s + %s, 2) - TMath::Power(%s + %s, 2)  )", E0.Data(), E1.Data(), P0tr.Data(), P1tr.Data(), P0z.Data(), P1z.Data() ), "(MLParticleLJetML_TopTag >= 0)&&(MLParticleLJetN == 2)", "same");
    */
 
    

    
    
    return 0;
}
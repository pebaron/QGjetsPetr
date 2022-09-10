

void AtlasExample3(TString InputFile1="",TString InputFile2="",TString InputFile3="", TString XTitle="p_{T} [GeV]", TString ExtraText="",TString YTitle="Efficiency", TString RatioTitle="Data / MC  ", int CanInt = 0){
   gROOT->SetStyle("ATLAS");
   TFile * File_Mu_Reco_Pt1 = new TFile(InputFile1, "read");
   TFile * File_Mu_Reco_Pt2 = new TFile(InputFile2, "read");
   TFile * File_Mu_Reco_Pt3 = new TFile(InputFile3, "read");
   TGraphAsymmErrors*  Mu_Reco_Pt_Eff_Data1 = (TGraphAsymmErrors*)File_Mu_Reco_Pt1->Get("Data");
   TGraphAsymmErrors*  Mu_Reco_Pt_Eff_MC1 = (TGraphAsymmErrors*)File_Mu_Reco_Pt1->Get("MC_+_data_overlay");
   TGraphAsymmErrors*  Mu_Reco_Pt_Sca_Data_div_MC1 = (TGraphAsymmErrors*)File_Mu_Reco_Pt1->Get("ratio_Data");
   TGraphAsymmErrors*  Mu_Reco_Pt_Eff_Data2 = (TGraphAsymmErrors*)File_Mu_Reco_Pt2->Get("Data");
   TGraphAsymmErrors*  Mu_Reco_Pt_Eff_MC2 = (TGraphAsymmErrors*)File_Mu_Reco_Pt2->Get("MC_+_data_overlay");
   TGraphAsymmErrors*  Mu_Reco_Pt_Sca_Data_div_MC2 = (TGraphAsymmErrors*)File_Mu_Reco_Pt2->Get("ratio_Data");
   TGraphAsymmErrors*  Mu_Reco_Pt_Eff_Data3 = (TGraphAsymmErrors*)File_Mu_Reco_Pt3->Get("Data");
   TGraphAsymmErrors*  Mu_Reco_Pt_Eff_MC3 = (TGraphAsymmErrors*)File_Mu_Reco_Pt3->Get("MC_+_data_overlay");
   TGraphAsymmErrors*  Mu_Reco_Pt_Sca_Data_div_MC3 = (TGraphAsymmErrors*)File_Mu_Reco_Pt3->Get("ratio_Data");
   //Canvases
   TCanvas *c1 = new TCanvas(TString::Format("c_%i", CanInt), TString::Format("c_%i", CanInt), 800, 800);
   TPad * pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
   pad1->SetBottomMargin(0)  ;
   pad1->Draw();
   c1->cd()  ;
   TPad * pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
   pad2->SetTopMargin(0)  ;
   pad2->SetBottomMargin(0.3);
   pad2->Draw();
   pad1->cd();
   Mu_Reco_Pt_Eff_Data1->GetYaxis()->SetRangeUser(0.75,1.25);
   Mu_Reco_Pt_Eff_Data1->GetXaxis()->SetTitle("");
   Mu_Reco_Pt_Eff_Data1->GetYaxis()->SetTitle(YTitle);
   Mu_Reco_Pt_Eff_Data1->SetLineColor(1);
   Mu_Reco_Pt_Eff_Data1->SetMarkerColor(1);
   Mu_Reco_Pt_Eff_Data1->GetXaxis()->SetLabelSize(0.0);
   Mu_Reco_Pt_Eff_Data1->Draw("PA");
   Mu_Reco_Pt_Eff_MC1->GetYaxis()->SetRangeUser(0.75,1.25);
   Mu_Reco_Pt_Eff_MC1->SetLineColor(2);
   Mu_Reco_Pt_Eff_MC1->SetMarkerColor(2);
   Mu_Reco_Pt_Eff_MC1->SetMarkerStyle(24);
   Mu_Reco_Pt_Eff_MC1->Draw("P same");
   Mu_Reco_Pt_Eff_MC2->SetLineColor(4);
   Mu_Reco_Pt_Eff_MC2->SetMarkerColor(4);
   Mu_Reco_Pt_Eff_MC2->Draw("P same");
   Mu_Reco_Pt_Eff_MC3->SetLineColor(kGreen);
   Mu_Reco_Pt_Eff_MC3->SetMarkerColor(kGreen);
   Mu_Reco_Pt_Eff_MC3->Draw("P same");
   TLatex * l = new TLatex();
   l->SetNDC();
   l->SetTextColor(1);
   l->DrawLatex(0.2, 0.87, "#bf{#it{ATLAS}} Internal ");
   TLatex * l2 = new TLatex();
   l2->SetNDC();
   l2->SetTextColor(1);
   l2->DrawLatex(0.2, 0.82, "#sqrt{s}=8.16 TeV, 170 nb^{-1}");
   TLatex * l3 = new TLatex();
   l3->SetNDC();
   l3->SetTextColor(1);
   l3->DrawLatex(0.2, 0.77, ExtraText);
   TLegend *legend = new TLegend(0.6,0.6,0.9,0.9);
   legend->AddEntry(Mu_Reco_Pt_Eff_Data1,"Data","lp");
   legend->AddEntry(Mu_Reco_Pt_Eff_MC2  ,"MC loose", "lp");
   legend->AddEntry(Mu_Reco_Pt_Eff_MC1  ,"MC medium", "lp");
   legend->AddEntry(Mu_Reco_Pt_Eff_MC3  ,"MC tight", "lp");
   legend->Draw("same");
   pad2->cd();
   Mu_Reco_Pt_Sca_Data_div_MC1->GetXaxis()->SetTitleSize(0.153);
   Mu_Reco_Pt_Sca_Data_div_MC1->GetXaxis()->SetTitleOffset(0.9);
   Mu_Reco_Pt_Sca_Data_div_MC1->GetXaxis()->SetLabelSize(0.12);
   Mu_Reco_Pt_Sca_Data_div_MC1->GetYaxis()->SetTitleSize(0.153);
   Mu_Reco_Pt_Sca_Data_div_MC1->GetYaxis()->SetTitleOffset(0.45);
   Mu_Reco_Pt_Sca_Data_div_MC1->GetYaxis()->SetLabelSize(0.12);
   Mu_Reco_Pt_Sca_Data_div_MC1->GetYaxis()->SetNdivisions(505);
   Mu_Reco_Pt_Sca_Data_div_MC1->GetXaxis()->SetTitle(XTitle);
   Mu_Reco_Pt_Sca_Data_div_MC1->GetYaxis()->SetTitle(RatioTitle);
   Mu_Reco_Pt_Sca_Data_div_MC1->GetYaxis()->SetRangeUser(0.75,1.25);
   TLine * line = new TLine(Mu_Reco_Pt_Sca_Data_div_MC1->GetXaxis()->GetXmin(),1.0,Mu_Reco_Pt_Sca_Data_div_MC1->GetXaxis()->GetXmax(),1.0);
   line->SetLineStyle(2);
   line->SetLineColor(38);
   //gPad->SetLogy(1);
   //line->Draw();
   Mu_Reco_Pt_Sca_Data_div_MC1->SetLineColor(2);
   Mu_Reco_Pt_Sca_Data_div_MC1->SetMarkerColor(2);
   Mu_Reco_Pt_Sca_Data_div_MC1->Draw("PA");
   Mu_Reco_Pt_Sca_Data_div_MC2->SetLineColor(4);
   Mu_Reco_Pt_Sca_Data_div_MC2->SetMarkerColor(4);
   Mu_Reco_Pt_Sca_Data_div_MC2->Draw("P same");
   Mu_Reco_Pt_Sca_Data_div_MC3->SetLineColor(kGreen);
   Mu_Reco_Pt_Sca_Data_div_MC3->SetMarkerColor(kGreen);
   Mu_Reco_Pt_Sca_Data_div_MC3->Draw("P same");
   //Mu_Reco_Pt_Sca_Data_div_MC2->Draw("P same");
   //Mu_Reco_Pt_Sca_Data_div_MC3->Draw("P same");
   line->Draw("same");
   //c1->Update();
   InputFile1.ReplaceAll(".","_");
   InputFile1.ReplaceAll("HighPtMuon","Muon");
   if (InputFile1.Contains("pPb")){
      c1->Print(TString::Format("%s_pPb_final.pdf",InputFile1.Data()));
      c1->Print(TString::Format("%s_pPb_final.png",InputFile1.Data()));
   }
   if (InputFile1.Contains("Pbp")){
      c1->Print(TString::Format("%s_Pbp_final.pdf",InputFile1.Data()));
      c1->Print(TString::Format("%s_Pbp_final.png",InputFile1.Data()));
   }
   
}

void CheckPlot(TString MyDir = "eff_reco_pPb_MC4MCtag", TString MyVar="PtNoVar", TString XTitle = "p_{T} [GeV]"){

TFile * dataCalo0 = new TFile("data_2016_B_and_C_grp16_v01_p3903_calo0.root", "read");
TFile * dataCalo1 = new TFile("data_2016_B_and_C_grp16_v01_p3903_calo1.root", "read");
TFile * MoC4Calo0 = new TFile("MC_overlay_sample4MCtag_calo0.root", "read");
TFile * MoC4Calo1 = new TFile("MC_overlay_sample4MCtag_calo1.root", "read");
TFile * MoC5Calo0 = new TFile("MC_overlay_sample5MCtag_calo0.root", "read");
TFile * MoC5Calo1 = new TFile("MC_overlay_sample5MCtag_calo1.root", "read");
TFile * MoC6Calo0 = new TFile("MC_overlay_sample6MCtag_calo0.root", "read");
TFile * MoC6Calo1 = new TFile("MC_overlay_sample6MCtag_calo1.root", "read");
TFile * MoC7Calo0 = new TFile("MC_overlay_sample7MCtag_calo0.root", "read");
TFile * MoC7Calo1 = new TFile("MC_overlay_sample7MCtag_calo1.root", "read");
   
TH1D * h_dataCalo0 = (TH1D*)dataCalo0->Get("ZmumuTPReco/CaloProbes_AllPt10/OC/MediumMuons/Probe/CaloProbes_AllPt10_OC_MediumMuons_Probe_Eta");
TH1D * h_dataCalo1 = (TH1D*)dataCalo1->Get("ZmumuTPReco/CaloProbes_AllPt10/OC/MediumMuons/Probe/CaloProbes_AllPt10_OC_MediumMuons_Probe_Eta");
TH1D * h_MoC4Calo0 = (TH1D*)MoC4Calo0->Get("ZmumuTPReco/CaloProbes_AllPt10/OC/MediumMuons/Probe/CaloProbes_AllPt10_OC_MediumMuons_Probe_Eta");
TH1D * h_MoC4Calo1 = (TH1D*)MoC4Calo1->Get("ZmumuTPReco/CaloProbes_AllPt10/OC/MediumMuons/Probe/CaloProbes_AllPt10_OC_MediumMuons_Probe_Eta");
TH1D * h_MoC5Calo0 = (TH1D*)MoC5Calo0->Get("ZmumuTPReco/CaloProbes_AllPt10/OC/MediumMuons/Probe/CaloProbes_AllPt10_OC_MediumMuons_Probe_Eta");
TH1D * h_MoC5Calo1 = (TH1D*)MoC5Calo1->Get("ZmumuTPReco/CaloProbes_AllPt10/OC/MediumMuons/Probe/CaloProbes_AllPt10_OC_MediumMuons_Probe_Eta");
TH1D * h_MoC6Calo0 = (TH1D*)MoC6Calo0->Get("ZmumuTPReco/CaloProbes_AllPt10/OC/MediumMuons/Probe/CaloProbes_AllPt10_OC_MediumMuons_Probe_Eta");
TH1D * h_MoC6Calo1 = (TH1D*)MoC6Calo1->Get("ZmumuTPReco/CaloProbes_AllPt10/OC/MediumMuons/Probe/CaloProbes_AllPt10_OC_MediumMuons_Probe_Eta");
TH1D * h_MoC7Calo0 = (TH1D*)MoC7Calo0->Get("ZmumuTPReco/CaloProbes_AllPt10/OC/MediumMuons/Probe/CaloProbes_AllPt10_OC_MediumMuons_Probe_Eta");
TH1D * h_MoC7Calo1 = (TH1D*)MoC7Calo1->Get("ZmumuTPReco/CaloProbes_AllPt10/OC/MediumMuons/Probe/CaloProbes_AllPt10_OC_MediumMuons_Probe_Eta");

TCanvas *can = new TCanvas("CheckPlot", "CheckPlot", 1200, 1200);
can->cd();
h_dataCalo1->SetLineStyle(2);
h_MoC4Calo1->SetLineStyle(2);
h_MoC5Calo1->SetLineStyle(2);
h_MoC6Calo1->SetLineStyle(2);
h_MoC7Calo1->SetLineStyle(2);

h_dataCalo0->SetLineColor(1);
h_dataCalo1->SetLineColor(1);
h_MoC4Calo0->SetLineColor(kRed);
h_MoC4Calo1->SetLineColor(kRed);
h_MoC5Calo0->SetLineColor(kBlue);
h_MoC5Calo1->SetLineColor(kBlue);
h_MoC6Calo0->SetLineColor(kGreen);
h_MoC6Calo1->SetLineColor(kGreen);
h_MoC7Calo0->SetLineColor(kViolet);
h_MoC7Calo1->SetLineColor(kViolet);

h_dataCalo0->Scale(1.0/h_dataCalo0->Integral());
h_dataCalo1->Scale(1.0/h_dataCalo1->Integral());
h_MoC4Calo0->Scale(1.0/h_MoC4Calo0->Integral());
h_MoC4Calo1->Scale(1.0/h_MoC4Calo1->Integral());
h_MoC5Calo0->Scale(1.0/h_MoC5Calo0->Integral());
h_MoC5Calo1->Scale(1.0/h_MoC5Calo1->Integral());
h_MoC6Calo0->Scale(1.0/h_MoC6Calo0->Integral());
h_MoC6Calo1->Scale(1.0/h_MoC6Calo1->Integral());
h_MoC7Calo0->Scale(1.0/h_MoC7Calo0->Integral());
h_MoC7Calo1->Scale(1.0/h_MoC7Calo1->Integral());

h_MoC4Calo1->SetMaximum(1.5*h_MoC4Calo1->GetMaximum());
h_MoC4Calo1->GetYaxis()->SetTitle(TString::Format("%s / Integral", h_MoC4Calo1->GetYaxis()->GetTitle() ));
h_MoC4Calo1->Draw("hist same");
h_MoC4Calo0->Draw("hist same");
h_MoC5Calo1->Draw("hist same");
h_MoC5Calo0->Draw("hist same");
h_MoC6Calo1->Draw("hist same");
h_MoC6Calo0->Draw("hist same");
h_MoC7Calo1->Draw("hist same");
h_MoC7Calo0->Draw("hist same");
h_dataCalo0->Draw("hist same");
h_dataCalo1->Draw("hist same");

TLegend * leg = new TLegend(0.368,0.55,0.71,0.89);

leg->AddEntry(h_dataCalo0, "data probe_matched_CaloTag = 0", "l");
leg->AddEntry(h_MoC4Calo0, "MC no. 4 probe_matched_CaloTag = 0", "l");
leg->AddEntry(h_MoC5Calo0, "MC no. 5 probe_matched_CaloTag = 0", "l");
leg->AddEntry(h_MoC6Calo0, "MC no. 6 probe_matched_CaloTag = 0", "l");
leg->AddEntry(h_MoC7Calo0, "MC no. 7 probe_matched_CaloTag = 0", "l");


leg->AddEntry(h_dataCalo1, "data probe_matched_CaloTag = 1", "l");
leg->AddEntry(h_MoC4Calo1, "MC no. 4 probe_matched_CaloTag = 1", "l");
leg->AddEntry(h_MoC5Calo1, "MC no. 5 probe_matched_CaloTag = 1", "l");
leg->AddEntry(h_MoC6Calo1, "MC no. 6 probe_matched_CaloTag = 1", "l");
leg->AddEntry(h_MoC7Calo1, "MC no. 7 probe_matched_CaloTag = 1", "l");

leg->Draw("same");

can->SaveAs("MediumProbesAllPt10.pdf");

can->SaveAs("MediumProbesAllPt10.png");

}

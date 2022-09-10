int CheckAODs(TString FileName1="outAOD_MC_off.root", TString FileName2="outDAOD_DataB_off.root"){
   gROOT->SetStyle("ATLAS");
   TFile * MoCaFile = new TFile(FileName1.Data(), "read");
   TFile * DataFile = new TFile(FileName2.Data(), "read");


   TH2D* h_MoCa = (TH2D*)MoCaFile->Get("h2_CaloMuonIDTag_eta");
   TH2D* h_Data = (TH2D*)DataFile->Get("h2_CaloMuonIDTag_eta");

   TH1D* h_MoCa_eta = (TH1D*)MoCaFile->Get("h_eta");
   TH1D* h_Data_eta = (TH1D*)DataFile->Get("h_eta");

   TH1D* h_MoCa_eta_tagged = (TH1D*)MoCaFile->Get("h_eta_tageged");
   TH1D* h_Data_eta_tagged = (TH1D*)DataFile->Get("h_eta_tageged");

   h_MoCa->GetYaxis()->SetRangeUser(0.0,35.0);
   h_Data->GetYaxis()->SetRangeUser(0.0,35.0);

   TLine * line = new TLine(-2.7,10.0,2.7,10.0);
   line->SetLineColor(2);
   line->SetLineWidth(4);

   TArrow * arrow = new TArrow(-2.6,10.0,-2.6,20.0,0.02,"|>");//"Cut MuonSelectionTool.cxx L1317"
   arrow->SetAngle(60);
   arrow->SetLineWidth(4);
   arrow->SetLineColor(2);
   //rowr5->SetFillStyle(3008);
   arrow->SetFillColor(2);
   //arrow->Draw();
   //arrow->SetAngle(60);
   //arrow->SetLineColor(2);
   //arrow->SetLineWidth(2);
   //arrow->SetFillColor(2);

   TLatex * mytext = new TLatex(-2.5, 13.0, "(CaloMuonIDTag > 10) MuonSelectionTool.cxx L-1317");


   TCanvas * can = new TCanvas("can", "can", 0,0,1800,2700);
   can->Divide(2,2);
   can->cd(1);
   gPad->SetRightMargin(0.15);
   gPad->SetTopMargin(0.1);
   h_Data->SetTitle("Data");
   TLatex * title1 = new TLatex(-0.4,36.0,"Data");
   title1->SetTextSize(0.08);
   h_Data->GetXaxis()->SetTitle("#eta");
   h_Data->GetYaxis()->SetTitle("CaloMuonIDTag");
   h_Data->Draw("colz");
   title1->Draw("same");
   line->Draw("same");
   arrow->Draw();
   mytext->Draw("same");


   can->cd(2);
   gPad->SetRightMargin(0.15);
   gPad->SetTopMargin(0.1);
   h_MoCa->SetTitle("MC");
   TLatex * title2 = new TLatex(-2.0,36.0,"MC overlay xAOD");
   title2->SetTextSize(0.08);
   h_MoCa->GetXaxis()->SetTitle("#eta");
   h_MoCa->GetYaxis()->SetTitle("CaloMuonIDTag");
   h_MoCa->Draw("colz");
   title2->Draw("same");
   line->Draw("same");
   arrow->Draw();
   mytext->Draw("same");

   TLegend *leg = new TLegend(0.65,0.65,0.85,0.85);
   leg->AddEntry(h_Data_eta, "matched_CaloTag = 0", "l");
   leg->AddEntry(h_Data_eta_tagged, "matched_CaloTag = 1", "l");
   leg->SetFillStyle(0);
   leg->SetBorderSize(0);

   can->cd(3);
   gPad->SetTopMargin(0.1);
   h_Data_eta->SetTitle("Data");
   h_Data_eta->GetXaxis()->SetTitle("#eta");
   h_Data_eta->GetYaxis()->SetTitle("Events");
   h_Data_eta->SetMaximum(h_Data_eta->GetMaximum()*1.3);
   h_Data_eta->Draw("hist");
   h_Data_eta_tagged->SetLineColor(2);
   h_Data_eta_tagged->Draw("hist same");
   TLatex * title3 = new TLatex(-0.4,150.0,"Data");
   title3->SetTextSize(0.08);
   title3->Draw("same");
   leg->Draw("same");
   can->cd(4);
   gPad->SetTopMargin(0.1);
   h_MoCa_eta->SetTitle("MC");
   h_MoCa_eta->GetXaxis()->SetTitle("#eta");
   h_MoCa_eta->GetYaxis()->SetTitle("Events");
   h_MoCa_eta->SetMaximum(h_MoCa_eta->GetMaximum()*1.3);
   h_MoCa_eta->Draw("hist");
   h_MoCa_eta_tagged->SetLineColor(2);
   h_MoCa_eta_tagged->Draw("hist same");
   TLatex * title4 = new TLatex(-2.0,620.0,"MC overlay xAOD");
   title4->SetTextSize(0.08);
   title4->Draw("same");
   leg->Draw("same");  
   can->SaveAs("CaloMuonIDTag.pdf");
   can->SaveAs("CaloMuonIDTag.png");

   return 0;
}
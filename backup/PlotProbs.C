int PlotProbs(TString FileName = "probs_infile_analyzed_histos_boosted_QCD_pp_2b2j_LO_matched_ptj1j2min200.root"){

    TFile * rfile = new TFile(FileName.Data(), "read");
    FileName = FileName.ReplaceAll(".root", "");
    TH2D * h_DiLL_vs_perLLLL   = (TH2D*)rfile->Get("h_DiLL_vs_perLLLL");
    TH2D * h_FourLLLL_vs_perLL = (TH2D*)rfile->Get("h_FourLLLL_vs_perLL");

    TCanvas * can1 = new TCanvas("can1", "can1", 0,0,1600,1000);
    can1->cd();
    can1->SetRightMargin(0.15);
    gStyle->SetOptStat(0);
    h_DiLL_vs_perLLLL->GetXaxis()->SetTitle("Assigned probability max(ll ll)");
    h_DiLL_vs_perLLLL->GetYaxis()->SetTitle("Not Assigned probability llll");
    h_DiLL_vs_perLLLL->GetZaxis()->SetTitle("Events");
    gPad->SetLogz(1);
    h_DiLL_vs_perLLLL->Draw("colz");

    TCanvas * can2 = new TCanvas("can2", "can2", 0,0,1600,1000);
    can2->cd();
    can2->SetRightMargin(0.15);
    gStyle->SetOptStat(0);
    h_FourLLLL_vs_perLL->GetXaxis()->SetTitle("Assigned probability llll");
    h_FourLLLL_vs_perLL->GetYaxis()->SetTitle("Not Assigned probability max(ll ll)");
    h_FourLLLL_vs_perLL->GetZaxis()->SetTitle("Events");
    gPad->SetLogz(1);
    h_FourLLLL_vs_perLL->Draw("colz");

    can1->SaveAs(TString::Format("./probs_plots/h_DiLL_vs_perLLLL_%s.pdf", FileName.Data()) );
    can2->SaveAs(TString::Format("./probs_plots/h_FourLLLL_vs_perLL_%s.pdf", FileName.Data()) );
    can1->SaveAs(TString::Format("./probs_plots/h_DiLL_vs_perLLLL_%s.png", FileName.Data()) );
    can2->SaveAs(TString::Format("./probs_plots/h_FourLLLL_vs_perLL_%s.png", FileName.Data()) );

    return 0;    
}
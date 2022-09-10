int Compare(TString h1Name = "ML/DetectorTopMass", TString h2Name="2B0S/DetectorTopMass"){
    TFile * filey0 = new TFile("analyzed_histos_delphes_Y0tttt.root","read");
    TFile * fileSM = new TFile("analyzed_histos_delphes_SMtttt.root","read");

    TH1D * hy0 = (TH1D*)filey0->Get(h1Name.Data());
    TH1D * hsm = (TH1D*)fileSM->Get(h2Name.Data());

    hy0->SetLineColor(2);

    TCanvas * can = new TCanvas("can", "can", 0,0,1600,1600);
    can->cd();

    if (hy0->GetMaximum() >= hsm->GetMaximum()){
        hy0->Draw("hist");
        hsm->Draw("hist same");
    }else{
        hsm->Draw("hist");
        hy0->Draw("hist same");
    }
    
    TLegend * leg = new TLegend(0.65,0.65,0.88,0.88);
    leg->SetBorderSize(0);
    leg->AddEntry(hy0, "tttt y0 allhad", "l");
    leg->AddEntry(hsm, "tttt SM allhad", "l");
    leg->Draw("same");  

    TString out = h2Name.Data();
    out = out.ReplaceAll("/", "_");
    can->SaveAs(TString::Format("./MLcomp/%s.pdf", out.Data() ));
    can->SaveAs(TString::Format("./MLcomp/%s.png", out.Data() ));

return 0;
}
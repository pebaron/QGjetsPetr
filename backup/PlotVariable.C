int PlotVariable(TString Variable="h_deltaR",TString Moca="pPbMCNo0_eff.root", TString Data="data_eff.root", TString Mocapp="pp_eff.root", TString Datapp="ppdata_eff.root"){
    TFile * mocafile = new TFile(Moca.Data(), "read");
    TFile * datafile = new TFile(Data.Data(), "read");
    TFile * mocappfile = new TFile(Mocapp.Data(), "read");
    TFile * datappfile = new TFile(Datapp.Data(), "read");

    TH1D * moca = (TH1D*)mocafile->Get(Variable.Data());
    TH1D * data = (TH1D*)datafile->Get(Variable.Data());
    TH1D * mocapp = (TH1D*)mocappfile->Get(Variable.Data());
    TH1D * datapp = (TH1D*)datappfile->Get(Variable.Data());

    vector<double> maxy(4);
    maxy[0] = moca->GetMaximum();
    maxy[1] = data->GetMaximum();
    maxy[2] = mocapp->GetMaximum();
    maxy[3] = datapp->GetMaximum();

    //double maxy = *max_element(maxy.begin(), maxy.end());

    moca->Scale(1.0/moca->GetMaximum());
    data->Scale(1.0/data->GetMaximum());
    mocapp->Scale(1.0/mocapp->GetMaximum());
    datapp->Scale(1.0/datapp->GetMaximum());

    moca->SetMaximum(1.3);
    moca->SetMinimum(0.0);

    moca->SetLineColor(2);
    mocapp->SetLineColor(2);
    mocapp->SetLineStyle(2);
    datapp->SetLineStyle(2);
    TCanvas * can = new TCanvas("can", "can", 0,0,1600,1600);
    can->cd();
    moca->GetXaxis()->SetTitle(Variable.Data());
    moca->Draw("hist same");
    data->Draw("hist same");
    mocapp->Draw("hist same");
    datapp->Draw("hist same");

    TLegend * leg = new TLegend(0.65,0.65,0.85,0.85);
    leg->AddEntry(moca, "pPb MC", "l");
    leg->AddEntry(data, "pPb data", "l");
    leg->AddEntry(mocapp, "pp MC", "l");
    leg->AddEntry(datapp, "pp data", "l");
    leg->Draw("same");
    can->SaveAs(TString::Format("%s,pdf", Variable.Data()));
    can->SaveAs(TString::Format("%s,png", Variable.Data()));
    return 0 ;
}
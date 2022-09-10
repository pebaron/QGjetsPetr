int PlotVariable2(TString Variable="tag_eta",bool Logy=false ,TString TreeName="ZmumuTPMerged/Trees/MuonProbes_OC/TPTree_MuonProbes_OC", TString Moca="pPbMCNo0_16.root", TString Data="data_test.root"){
    TFile * mocafile = new TFile(Moca.Data(), "read");
    TFile * datafile = new TFile(Data.Data(), "read");
    //TFile * mocappfile = new TFile(Mocapp.Data(), "read");
    //TFile * datappfile = new TFile(Datapp.Data(), "read");
    TTree * tree1 = (TTree*)mocafile->Get(TreeName.Data());
//    tree1->Print();
    TTree * tree2 = (TTree*)datafile->Get(TreeName.Data());
    //tree2->Print();
    tree1->Draw(Variable.Data(), "", "Q");
    TH1 *moca_temp = (TH1*)gPad->GetPrimitive("htemp")->Clone("moca_temp"); 
    tree2->Draw(Variable.Data(), "", "Q");
    TH1 *data_temp = (TH1*)gPad->GetPrimitive("htemp")->Clone("data_temp"); 

    vector<double> maxx(2);
    vector<double> minx(2);

    minx[0] = moca_temp->GetXaxis()->GetXmin();
    minx[1] = data_temp->GetXaxis()->GetXmin();
    maxx[0] = moca_temp->GetXaxis()->GetXmax();
    maxx[1] = data_temp->GetXaxis()->GetXmax();

    vector<double> bins(2);
    bins[0] = moca_temp->GetXaxis()->GetNbins();
    bins[1] = data_temp->GetXaxis()->GetNbins();
    
    TH1D *moca = new TH1D("moca", "moca", (int)*max_element(bins.begin(), bins.end()), *min_element(minx.begin(), minx.end()), *max_element(maxx.begin(), maxx.end()) );
    TH1D *data = (TH1D*)moca->Clone("data"); 
    data->Reset();

    tree1->Draw(TString::Format("%s >> moca", Variable.Data()), "", "Q");
    tree2->Draw(TString::Format("%s >> data", Variable.Data()), "", "Q");
    //TH1D * moca = (TH1D*)mocafile->Get(Variable.Data());
    //TH1D * data = (TH1D*)datafile->Get(Variable.Data());
    //TH1D * mocapp = (TH1D*)mocappfile->Get(Variable.Data());
    //TH1D * datapp = (TH1D*)datappfile->Get(Variable.Data());

    vector<double> maxy(2);
    maxy[0] = moca->GetMaximum();
    maxy[1] = data->GetMaximum();
    //maxy[2] = mocapp->GetMaximum();
    //maxy[3] = datapp->GetMaximum();


    moca->Scale(1.0/moca->GetMaximum());
    data->Scale(1.0/data->GetMaximum());
    //mocapp->Scale(1.0/mocapp->GetMaximum());
    //datapp->Scale(1.0/datapp->GetMaximum());
    
    moca->SetLineColor(2);
 //   mocapp->SetLineColor(2);
//    mocapp->SetLineStyle(2);
//    datapp->SetLineStyle(2);
    TCanvas * can = new TCanvas("can", "can", 0,0,1600,1600);
    can->cd();
    if (Logy==false){
        moca->SetMaximum(1.3);
        moca->SetMinimum(0.0);
    }else{
        moca->SetMaximum(100);
        moca->SetMinimum(1e-3);
        gPad->SetLogy();

    }

    moca->GetXaxis()->SetTitle(Variable.Data());
    moca->SetLineWidth(4);
    moca->Draw("hist e1");
    data->Draw("hist e1 same");
  //  mocapp->Draw("hist same");
  //  datapp->Draw("hist same");

    TLegend * leg = new TLegend(0.65,0.65,0.85,0.85);
    leg->AddEntry(moca, "pPb MC", "l");
    leg->AddEntry(data, "pPb data", "l");
 // leg->AddEntry(mocapp, "pp MC", "l");
 //   leg->AddEntry(datapp, "pp data", "l");
    leg->Draw("same");

    gSystem->Exec(TString::Format("mkdir -vp %s",   TreeName.Data() ) );

    //TString x = TreeName;
    //TObjArray *tx = x.Tokenize("/");
    //tx->Print();
    //TString temp;
    //for (Int_t i = 0; i < tx->GetEntries(); i++){
    //    temp = ((TObjString *)(tx->At(i)))->String();
    //    gSystem->Exec(TString::Format("mkdir %s",   temp.Data() ) );
    //    gSystem->Exec(TString::Format("cd %s", temp.Data() ) );
    //} 
    if (Logy==false){
    can->SaveAs(TString::Format("./comp/%s/%s.pdf", TreeName.Data(),Variable.Data()));
    can->SaveAs(TString::Format("./comp/%s/%s.png", TreeName.Data(),Variable.Data()));
    }else{
    can->SaveAs(TString::Format("./comp/%s/%s_log.pdf", TreeName.Data(),Variable.Data()));
    can->SaveAs(TString::Format("./comp/%s/%s_log.png", TreeName.Data(),Variable.Data()));
    }
    gSystem->Exec("cd ~/testarea");
    return 0 ;
}

int PlotEff(TString Moca="pPbMCNo1.root", TString Data="data.root", TString Variable = "var_eta", TString CutAll = "(abs(var_eta) < 2.5)", TString CutMatch = "(var_HLT_mu15)", int nbins = 22, float xmin = -2.7, float xmax = 2.7){

    TFile * mocafile = new TFile(Moca.Data(), "read");
    TFile * datafile = new TFile(Data.Data(), "read");

    CutMatch = TString::Format("(%s)&&(%s)",CutAll.Data(),CutMatch.Data());

    TH1D * h_nom_mc = new TH1D("h_nom_mc","",nbins, xmin, xmax);
    TH1D * h_denom_mc = new TH1D("h_denom_mc","",nbins, xmin, xmax);
    TH1D * h_nom_data = new TH1D("h_nom_data","",nbins, xmin, xmax);
    TH1D * h_denom_data = new TH1D("h_denom_data","",nbins, xmin, xmax);

    TTree * tree = (TTree*)mocafile->Get("Muons");
    tree->Draw(TString::Format("%s >> h_nom_mc", Variable.Data()),CutMatch.Data(), "Q");
    //TH1 *h_nom_mc = (TH1*)gPad->GetPrimitive("htemp")->Clone("h_nom_mc");
    tree->Draw(TString::Format("%s >> h_denom_mc", Variable.Data()),CutAll.Data(), "Q");
    //TH1 *h_denom_mc = (TH1*)gPad->GetPrimitive("htemp")->Clone("h_denom_mc");
    TEfficiency * moca = new TEfficiency ( *h_nom_mc, *h_denom_mc); 

    TTree * tree_data = (TTree*)datafile->Get("Muons");
    tree_data->Draw(TString::Format("%s >> h_nom_data", Variable.Data()),CutMatch.Data(), "Q");
    //TH1 *h_nom_data = (TH1*)gPad->GetPrimitive("htemp")->Clone("h_nom_data");
    tree_data->Draw(TString::Format("%s >> h_denom_data", Variable.Data()),CutAll.Data(), "Q");
    //TH1 *h_denom_data = (TH1*)gPad->GetPrimitive("htemp")->Clone("h_denom_data");
    
    //h_denom_data->Draw("hist e1");
    //h_nom_data->SetLineColor(4);
    //h_nom_data->Draw("hist e1 same");

    TEfficiency * data = new TEfficiency ( *h_nom_data, *h_denom_data); 
    moca->SetName("moca");
    data->SetName("data");
    //moca->GetYaxis()->SetRangeUser(0.,1.);
    moca->SetMarkerColor(2);
    moca->SetLineColor(2);
    TCanvas * can = new TCanvas("can", "can", 0,0,1600,1600);
    can->cd();
    moca->Draw();
    gPad->Update(); 
    auto graph = moca->GetPaintedGraph(); 
    graph->SetMinimum(0.0);
    graph->SetMaximum(1.5); 
    graph->GetXaxis()->SetRangeUser(-2.5,2.5);
    graph->GetXaxis()->SetTitle("#eta");
    graph->GetYaxis()->SetTitle("Eff. HLT_mu15");
    graph->Draw("AP e1");
    gPad->Update(); 
    data->Draw("P same e1");
    TLegend * leg = new TLegend(0.68,0.74,0.889,0.92);
    leg->AddEntry(graph, "pPb MC");
    leg->AddEntry(data, "pPb data");
    leg->Draw("same");
    can->SaveAs("HLT_mu15.pdf");
    can->SaveAs("HLT_mu15.png");
    
    return 0 ;
}
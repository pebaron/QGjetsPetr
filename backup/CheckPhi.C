int CheckPhi(){


    TChain * chain1 = new TChain("ZmumuTPMerged/Trees/IDProbes_OC/TPTree_IDProbes_OC");
    //chain1->Add("group.perf-muons.27612997.EXT0._000002.NTUP_MCPTP_file1.root");
    //chain1->Add("group.perf-muons.27612997.EXT0._000001.NTUP_MCPTP_file1b.root");
    TChain * chain2 = new TChain("ZmumuTPMerged/Trees/IDProbes_OC/TPTree_IDProbes_OC");
    //chain2->Add("group.perf-muons.27612988.EXT0._000001.NTUP_MCPTP_file2.root");
    //chain2->Add("group.perf-muons.27612988.EXT0._000002.NTUP_MCPTP_file2b.root");
    //chain2->Add("group.perf-muons.27612988.EXT0._000003.NTUP_MCPTP_file2c.root");
    TChain * chain3 = new TChain("ZmumuTPMerged/Trees/IDProbes_OC/TPTree_IDProbes_OC");
    //chain3->Add("group.perf-muons.27613005.EXT0._000001.NTUP_MCPTP_file3.root");
    //chain3->Add("group.perf-muons.27613005.EXT0._000002.NTUP_MCPTP_file3b.root");
    TChain * chain4 = new TChain("ZmumuTPMerged/Trees/IDProbes_OC/TPTree_IDProbes_OC");
    //chain4->Add("group.perf-muons.27612980.EXT0._000001.NTUP_MCPTP_file4.root");
    //chain4->Add("group.perf-muons.27612980.EXT0._000002.NTUP_MCPTP_file4b.root");

    chain1->Add("group.perf-muons.27612997.EXT0._000002.NTUP_MCPTP.root");
    chain1->Add("group.perf-muons.27612997.EXT0._000001.NTUP_MCPTP.root");
    chain2->Add("group.perf-muons.27612988.EXT0._000001.NTUP_MCPTP.root");
    chain2->Add("group.perf-muons.27612988.EXT0._000002.NTUP_MCPTP.root");
    chain2->Add("group.perf-muons.27612988.EXT0._000003.NTUP_MCPTP.root");
    chain3->Add("group.perf-muons.27613005.EXT0._000001.NTUP_MCPTP.root");
    chain3->Add("group.perf-muons.27613005.EXT0._000002.NTUP_MCPTP.root");
    chain4->Add("group.perf-muons.27612980.EXT0._000001.NTUP_MCPTP.root");
    chain4->Add("group.perf-muons.27612980.EXT0._000002.NTUP_MCPTP.root");

    TChain * chain5 = new TChain("ZmumuTPMerged/Trees/IDProbes_OC/TPTree_IDProbes_OC");
    chain5->Add("./B/group.perf-muons.27586517.EXT0._000010.NTUP_MCPTP.root");
    chain5->Add("./B/group.perf-muons.27586517.EXT0._000014.NTUP_MCPTP.root");
    chain5->Add("./B/group.perf-muons.27586517.EXT0._000005.NTUP_MCPTP.root");
    chain5->Add("./B/group.perf-muons.27586517.EXT0._000003.NTUP_MCPTP.root");
    chain5->Add("./B/group.perf-muons.27586517.EXT0._000007.NTUP_MCPTP.root");
    chain5->Add("./B/group.perf-muons.27586517.EXT0._000017.NTUP_MCPTP.root");
    chain5->Add("./B/group.perf-muons.27586517.EXT0._000016.NTUP_MCPTP.root");
    chain5->Add("./B/group.perf-muons.27586517.EXT0._000004.NTUP_MCPTP.root");
    chain5->Add("./B/group.perf-muons.27586517.EXT0._000012.NTUP_MCPTP.root");
    chain5->Add("./B/group.perf-muons.27586517.EXT0._000001.NTUP_MCPTP.root");
    chain5->Add("./B/group.perf-muons.27586517.EXT0._000015.NTUP_MCPTP.root");
    chain5->Add("./B/group.perf-muons.27586517.EXT0._000008.NTUP_MCPTP.root");
    chain5->Add("./B/group.perf-muons.27586517.EXT0._000002.NTUP_MCPTP.root");
    chain5->Add("./B/group.perf-muons.27586517.EXT0._000009.NTUP_MCPTP.root");

    TChain * chain6 = new TChain("ZmumuTPMerged/Trees/IDProbes_OC/TPTree_IDProbes_OC");
    chain6->Add("./C/group.perf-muons.27586519.EXT0._000014.NTUP_MCPTP.root");
    chain6->Add("./C/group.perf-muons.27586519.EXT0._000006.NTUP_MCPTP.root");
    chain6->Add("./C/group.perf-muons.27586519.EXT0._000010.NTUP_MCPTP.root");
    chain6->Add("./C/group.perf-muons.27586519.EXT0._000004.NTUP_MCPTP.root");
    chain6->Add("./C/group.perf-muons.27586519.EXT0._000013.NTUP_MCPTP.root");
    chain6->Add("./C/group.perf-muons.27586519.EXT0._000002.NTUP_MCPTP.root");
    chain6->Add("./C/group.perf-muons.27586519.EXT0._000003.NTUP_MCPTP.root");
    chain6->Add("./C/group.perf-muons.27586519.EXT0._000008.NTUP_MCPTP.root");
    chain6->Add("./C/group.perf-muons.27586519.EXT0._000001.NTUP_MCPTP.root");
    chain6->Add("./C/group.perf-muons.27586519.EXT0._000012.NTUP_MCPTP.root");
    chain6->Add("./C/group.perf-muons.27586519.EXT0._000009.NTUP_MCPTP.root");
    chain6->Add("./C/group.perf-muons.27586519.EXT0._000011.NTUP_MCPTP.root");
    chain6->Add("./C/group.perf-muons.27586519.EXT0._000005.NTUP_MCPTP.root");
    chain6->Add("./C/group.perf-muons.27586519.EXT0._000017.NTUP_MCPTP.root");
    chain6->Add("./C/group.perf-muons.27586519.EXT0._000018.NTUP_MCPTP.root");
    chain6->Add("./C/group.perf-muons.27586519.EXT0._000019.NTUP_MCPTP.root");
    chain6->Add("./C/group.perf-muons.27586519.EXT0._000020.NTUP_MCPTP.root");
    chain6->Add("./C/group.perf-muons.27586519.EXT0._000021.NTUP_MCPTP.root");
    chain6->Add("./C/group.perf-muons.27586519.EXT0._000023.NTUP_MCPTP.root");
    chain6->Add("./C/group.perf-muons.27586519.EXT0._000024.NTUP_MCPTP.root");
    chain6->Add("./C/group.perf-muons.27586519.EXT0._000025.NTUP_MCPTP.root");
    chain6->Add("./C/group.perf-muons.27586519.EXT0._000026.NTUP_MCPTP.root");
    chain6->Add("./C/group.perf-muons.27586519.EXT0._000027.NTUP_MCPTP.root");
    chain6->Add("./C/group.perf-muons.27586519.EXT0._000028.NTUP_MCPTP.root");

    
    chain1->Draw("dilep_mll >> h1(50,60000,120000)", "", "goff");
    //chain1->Draw("tag_phi:tag_eta", "", "colz");
    TCanvas* can = new TCanvas();
    can->cd();
    //chain6->Draw("tag_phi:tag_eta", "", "colz");
    chain2->Draw("dilep_mll >> h2 (50,60000,120000)", "", "goff");
    chain3->Draw("dilep_mll >> h3 (50,60000,120000)", "", "goff");
    chain4->Draw("dilep_mll >> h4 (50,60000,120000)", "", "goff");
    chain5->Draw("dilep_mll >> h5 (50,60000,120000)", "", "goff");
    chain6->Draw("dilep_mll >> h6 (50,60000,120000)", "", "goff");
    TH1D* h1 = (TH1D*)gDirectory->Get("h1");
    TH1D* h2 = (TH1D*)gDirectory->Get("h2");
    TH1D* h3 = (TH1D*)gDirectory->Get("h3");
    TH1D* h4 = (TH1D*)gDirectory->Get("h4");
    TH1D* h5 = (TH1D*)gDirectory->Get("h5");
    TH1D* h6 = (TH1D*)gDirectory->Get("h6");
// 
    h1->SetLineColor(kRed);
    h2->SetLineColor(kRed);
    h3->SetLineColor(kRed);
    h4->SetLineColor(kRed);
// 
// 
// 
    cout << h1->Integral() << endl;
    cout << h2->Integral() << endl;
    cout << h3->Integral() << endl;
    cout << h4->Integral() << endl;
    cout << h5->Integral() << endl;
    cout << h6->Integral() << endl;
// 
// 
    h2->Scale(h1->Integral()/h2->Integral());
    h3->Scale(h1->Integral()/h3->Integral());
    h4->Scale(h1->Integral()/h4->Integral());
    h5->Scale(h1->Integral()/h5->Integral());
    h6->Scale(h1->Integral()/h6->Integral());
    
// 
    // 

    h1->SetMarkerSize(0);
    h2->SetMarkerSize(0);
    h3->SetMarkerSize(0);
    h4->SetMarkerSize(0);

    h1->SetLineColor(kBlue);
    h2->SetLineColor(kPink);
    h3->SetLineColor(kPink);
    h4->SetLineColor(kBlue);

    
    h3->SetLineStyle(2);
    h2->SetLineStyle(2);
    h1->GetXaxis()->SetTitle("dilep_mll");
    h1->Draw("hist e1 same");
    h2->Draw("hist e1 same");
    h3->Draw("hist e1 same");
    h4->Draw("hist e1 same");
    // h5->Draw("hist e1 same");
    // h6->Draw("hist e1 same");
// 
    return 0;

}
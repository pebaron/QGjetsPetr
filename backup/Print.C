int Print(TString FileName="pPbMCNo0_0_impact.root", TString TreeName="ZmumuTPMerged/Trees/MuonProbes_OC/TPTree_MuonProbes_OC"){
    TFile * rfile = new TFile(FileName.Data(), "read");
    TTree * mytree = (TTree*)rfile->Get(TreeName.Data());
    mytree->Print();
    return 0;
}
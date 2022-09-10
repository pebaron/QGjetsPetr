void CheckNtuple(TString FileName="ntuple_0.root"){
   TFile * rfile = new TFile(FileName.Data(), "read");
   TTree * tree = (TTree*)rfile->Get("ZmumuTPMerged/Trees/MuonProbes_OC/TPTree_MuonProbes_OC");
   TCanvas * can = new TCanvas("can", "can", 0,0,1200,1200);
   can->Divide(2,1);
   can->cd(1);
   tree->Draw("probe_eta","probe_matched_CaloTag");
   can->cd(2);
   tree->Draw("probe_matched_HLT_mu15");
   return 0;
}
int PlotFromTTree(TString FileName, TString TTreeName, TString Variable1, TString Variable2){
TFile * rfile = new TFile(FileName.Data(), "read");
TTree * tree = (TTree*)rfile->Get(TTreeName.Data());
FileName = FileName.ReplaceAll(".root", "");
TCanvas * can = new TCanvas(TString::Format("file_%s_tree_%s_variables_%s_vs_%s", FileName.Data(), TTreeName.Data(), Variable1.Data(), Variable2.Data() ));
can->cd();
can->SetRightMargin(0.15);
tree->Draw(TString::Format("%s:%s", Variable1.Data(), Variable2.Data() ), TString::Format("((%s > -98)&&(%s > -98))", Variable1.Data(), Variable2.Data() ) , "colz") ;

can->SaveAs(TString::Format("./treeplots/%s.png",can->GetName() ));
can->SaveAs(TString::Format("./treeplots/%s.pdf",can->GetName() ));

return 0;
}
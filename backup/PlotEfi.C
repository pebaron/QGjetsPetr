int PlotEfi(TString Name, TString FileName = "muonTruthEfficiency_mc.root"){
       TFile * f1 = new TFile(FileName.Data(), "read");    
       TIter next(f1->GetListOfKeys());
       TKey *key;
       TCanvas * c1 = new TCanvas("can", "can", 0.,0.,1200.,800.);
       //c1->Print("hsimple.pdf[");
       c1->cd();
       gStyle->SetOptTitle(1);
       TH1F *h = (TH1F*)f1->Get(Name.Data());
       TGraphAsymmErrors *h2 = (TGraphAsymmErrors *)((TEfficiency*)f1->Get(Name.Data()))->CreateGraph();
       //TH1F *h = (TH1F*)h0->Clone("clone");
       h2->SetTitle(h->GetName());
       h2->GetXaxis()->SetRangeUser(h2->GetPointX(0) - h2->GetErrorXlow(0), h2->GetPointX(h2->GetN()-1) + h2->GetErrorXhigh(h2->GetN()-1) );
       h2->SetMaximum(1.0);
       TString hTitle = h->GetName();
       if (hTitle.Contains("eta")){
           h2->SetMinimum(0.815);
       }else if (hTitle.Contains("pt")){
        h2->SetMinimum(0.89);
       }else if (hTitle.Contains("phi")){
        h2->SetMinimum(0.865);
       }
       h2->Draw("AP");

       FileName = FileName.ReplaceAll(".root", "");
;
       c1->SaveAs(TString::Format("muonTruthEfficiency/%s_%s.png", FileName.Data(), h->GetName()));
       c1->SaveAs(TString::Format("muonTruthEfficiency/%s_%s.pdf", FileName.Data(), h->GetName()));
       ///.while ((key = (TKey*)next())) {
       ///.   TClass *cl = gROOT->GetClass(key->GetClassName());
       ///.   //if (!cl->InheritsFrom("TF1")) continue;
       ///.   TH1F *h = (TH1F*)key->ReadObj();
       ///.   cout << h->GetName() << endl;
       ///.   ////h->SetTitle(h->GetName());
       ///.   ////h->Draw();
       ///.   ////c1->SaveAs(TString::Format("muonTruthEfficiency/%s.png", h->GetName()));
       ///.   ////c1->SaveAs(TString::Format("muonTruthEfficiency/%s.pdf", h->GetName()));
       ///.   //break;
       ///.}
       //c1->Print("hsimple.pdf]");
  
    return 0;
}
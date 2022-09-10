int DrawThree(TString file1 = "./average_pt/qg_angs_900_2360.root",TString file2 = "qg_angs_900_2360_50perc.root",
              TString Var1 = "gluon_FastJets10MultLam50", TString Var2 = "gluon_FastJets10MultLam50"){

TFile * rfile1 = new TFile(file1.Data(), "read");
TFile * rfile2 = new TFile(file2.Data(), "read");

TH1F * h  = (TH1F*)rfile1->Get(Var1.Data() );
TH1F * h2 = (TH1F*)rfile2->Get(Var2.Data() );
h2->Scale(h->GetMaximum()/h2->GetMaximum());
//h2->Scale(1./h2->Integral());
//h->Scale(1./h->Integral());
h->SetLineColor(kBlack);
h2->SetLineColor(kRed);
h ->SetMarkerSize(0);
h2 ->SetMarkerSize(0);
h ->SetLineStyle(2);
h->SetMaximum(1.5*h->GetMaximum());
h->Draw("hist e1");
h2->Draw("hist e1 same");
TLegend * leg = new TLegend(0.2,0.75,0.88,0.88);
leg->SetBorderSize(0);
leg->SetFillStyle(0);
leg->AddEntry(h, TString::Format("2D approach - %s", h->GetName()));
leg->AddEntry(h2, TString::Format("2D approach (increased p_{T} by 50 %s) - %s", "\%",h2->GetName()));
leg->SetTextSize(0.025); 
leg->Draw("same");

return 0;

}

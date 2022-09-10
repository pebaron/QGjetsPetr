int PlotEfiAll(TString Name, TString FileName = "muonTruthEfficiency_mc.root"){

        TString FileName2 = "muonTruthEfficiency_AODs_361107_e6430.root";
        TString FileName3 = "muonTruthEfficiency_AODs_361107_e6431.root";
        TString FileName4 = "muonTruthEfficiency_AODs_420067_pn.root";
        TString FileName5 = "muonTruthEfficiency_AODs_420068_np.root";

       TFile * f1 = new TFile( FileName.Data(), "read");    
       TFile * f2 = new TFile(FileName2.Data(), "read");    
       TFile * f3 = new TFile(FileName3.Data(), "read");    
       TFile * f4 = new TFile(FileName4.Data(), "read");    
       TFile * f5 = new TFile(FileName5.Data(), "read");    



       TIter next(f1->GetListOfKeys());
       TKey *key;
       TCanvas * c1 = new TCanvas("can", "can", 0.,0.,1200.,800.);
       //c1->Print("hsimple.pdf[");
       c1->cd();
       gStyle->SetOptTitle(1);
       gStyle->SetOptStat(0);
        gPad->SetRightMargin(0.1);
        gPad->SetLeftMargin(0.1);
        gPad->SetBottomMargin(0.15);
        gPad->SetTopMargin(0.12);
       TH1F *h = (TH1F*)f1->Get(Name.Data());
       //TH1F *h2 = (TH1F*)f2->Get(Name.Data());
       //TH1F *h3 = (TH1F*)f3->Get(Name.Data());
       //TH1F *h4 = (TH1F*)f4->Get(Name.Data());
       //TH1F *h5 = (TH1F*)f5->Get(Name.Data());
       TGraphAsymmErrors *h2 = (TGraphAsymmErrors *)((TEfficiency*)f1->Get(Name.Data()))->CreateGraph();
       TGraphAsymmErrors *h22 = (TGraphAsymmErrors *)((TEfficiency*)f2->Get(Name.Data()))->CreateGraph();
       TGraphAsymmErrors *h23 = (TGraphAsymmErrors *)((TEfficiency*)f3->Get(Name.Data()))->CreateGraph();
       TGraphAsymmErrors *h24 = (TGraphAsymmErrors *)((TEfficiency*)f4->Get(Name.Data()))->CreateGraph();
       TGraphAsymmErrors *h25 = (TGraphAsymmErrors *)((TEfficiency*)f5->Get(Name.Data()))->CreateGraph();
       //TH1F *h = (TH1F*)h0->Clone("clone");
       ////h2->SetTitle(h->GetName());
       h2->SetTitle("");
       h2->GetXaxis()->SetRangeUser(h2->GetPointX(0) - h2->GetErrorXlow(0), h2->GetPointX(h2->GetN()-1) + h2->GetErrorXhigh(h2->GetN()-1) );
       h2->GetYaxis()->SetTitle("Efficiency");
       h2->GetXaxis()->SetTitleOffset(1.);
       h2->GetYaxis()->SetTitleOffset(1.05);
       h2->SetMaximum(1.3);
       TString hTitle = h->GetName();
       if (hTitle.Contains("eta")){
        h2->SetMinimum(0.85);
        h2->SetMaximum(1.0);
       }else if (hTitle.Contains("pt")){
        h2->SetMinimum(0.85);
        h2->SetMaximum(1.0);
       }else if (hTitle.Contains("phi")){
        h2->SetMinimum(0.85);
        h2->SetMaximum(1.0);
       }
       
       if (hTitle.Contains("Calo")) h2->SetMinimum(0.7);

       h2 ->SetLineColor(1);
       h22->SetLineColor(2);
       h23->SetLineColor(3);
       h24->SetLineColor(4);
       h25->SetLineColor(kMagenta);
       h2 ->SetLineWidth(2);
       h22->SetLineWidth(2);
       h23->SetLineWidth(2);
       h24->SetLineWidth(2);
       h25->SetLineWidth(2);
        double myx = 0.57;
        double myy = 0.57;
        double myx2 = 0.86;
        double myy2 = 0.86;
       if (hTitle.Contains("pt")){
           myx = 0.128548;
           myy = 0.177606;
           myx2 = 0.419;
           myy2 = 0.468468;
           h2 ->GetXaxis()->SetRangeUser(0,500);
       }
       if (hTitle.Contains("eta")){
           myx = 0.355;
           myy = 0.184;
           myx2 = 0.6448;
           myy2 = 0.4749;
           //h2 ->GetXaxis()->SetRangeUser(0,500);
       }
       if (hTitle.Contains("phi")){
           myx = 0.128548;
           myy = 0.177606;
           myx2 = 0.419;
           myy2 = 0.468468;
           //h2 ->GetXaxis()->SetRangeUser(0,500);
       }
       TLegend *leg = new TLegend(myx,myy,myx2,myy2);
       leg->AddEntry(h2,  "MC all", "l");
       leg->AddEntry(h22, "MC 361107_e6430", "l");
       leg->AddEntry(h23, "MC 361107_e6431", "l");
       leg->AddEntry(h24, "MC 420067_pn", "l");
       leg->AddEntry(h25, "MC 420068_np", "l");
       
       h2 ->Draw("AP");
       h22->Draw("P same");
       h23->Draw("P same");
       h24->Draw("P same");
       h25->Draw("P same");
        TString HelpString = h->GetName();
       leg->Draw("same");
       TLatex * l ;
       TLatex * l2;
        TObjArray *tx = HelpString.Tokenize("_");
       TString one = (((TObjString *)(tx->At(0)))->String());
       TString two = (((TObjString *)(tx->At(1)))->String());
       TString three = (((TObjString *)(tx->At(2)))->String());
       TString four  = (((TObjString *)(tx->At(3)))->String());
        TLatex * t ;
        TLatex * t2;
       if (HelpString.Contains("eta") && (!HelpString.Contains("Barrel"))){
        l = new TLatex(-2.5, 1.335,"#bf{#it{ATLAS}} Internal ");
        l2 = new TLatex(-2.5, 1.305,"pPb #sqrt{s}=8.16 TeV, 165 nb^{-1}");
        t = new TLatex( 0., 1.335,TString::Format("%s %s", one.Data(), three.Data() ) );
       t2 = new TLatex( 0., 1.305,two.Data() );
       } else if (HelpString.Contains("eta") && (HelpString.Contains("Barrel"))){
            l = new TLatex(-1.03, 1.335,"#bf{#it{ATLAS}} Internal ");
            l2 = new TLatex(-1.03, 1.305,"pPb #sqrt{s}=8.16 TeV, 165 nb^{-1}");
             t = new TLatex( 0.2, 1.335,TString::Format("%s %s", one.Data(), three.Data() ) );
            t2 = new TLatex( 0.2, 1.305,two.Data() );
       } else if (HelpString.Contains("pt") ){
           l = new TLatex(15., 1.335,"#bf{#it{ATLAS}} Internal ");
           l2 = new TLatex(15., 1.305,"pPb #sqrt{s}=8.16 TeV, 165 nb^{-1}");
            t = new TLatex( 500., 1.335,TString::Format("%s %s", one.Data(), three.Data() ) );
            t2 = new TLatex( 500., 1.305,two.Data() );
       } else if (HelpString.Contains("phi") ){
           l = new TLatex(-3.1, 1.335,"#bf{#it{ATLAS}} Internal ");
            l2 = new TLatex(-3.1, 1.305,"pPb #sqrt{s}=8.16 TeV, 165 nb^{-1}");
             t = new TLatex( 0., 1.335,TString::Format("%s %s", one.Data(), three.Data() ) );
            t2 = new TLatex( 0., 1.305,two.Data() );
       }
       l ->Draw("same");
       l2->Draw("same");
    
       
       
       t->Draw("same");
       t2->Draw("same");
       //t2 = new TLatex(0.5, 3.2,TString::Format("%s %s", latex.Data(), ""));

       FileName = FileName.ReplaceAll(".root", "");
;
       c1->SaveAs(TString::Format("muonTruthEfficiency/allmc_%s.png",  h->GetName()));
       c1->SaveAs(TString::Format("muonTruthEfficiency/allmc_%s.pdf",  h->GetName()));
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
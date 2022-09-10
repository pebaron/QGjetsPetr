int ControlPlot2(TString FileName0="pp.root", TString FileName1="pPbMCNo0.root", TString var1 = "quality", TString var2 = "eta", TString Opt = "colz", TString Cut = "", bool HistoPlot=false, bool Normalize=true, bool Log=false){
   // e.g. root -l "./ControlPlot.C(\"ppdata.root\",\"pp.root\",\"pPbMCNo1.root\",\"data.root\",\"var_eta\", \"var_eta\", \"hist e1\", \"(var_quality==2)&&(abs(var_eta)<3.0)\", 1)"
   //      root -l "./ControlPlot.C(\"ppdata.root\",\"pp.root\",\"pPbMCNo1.root\",\"data.root\",\"var_phi\", \"var_eta\", \"lego2d\", \"(abs(var_eta)<3.0)\", 0)"
   gROOT->SetStyle("ATLAS");
   TFile * MCppFile = new TFile(FileName0.Data(), "read");
   TFile * MoCaFile = new TFile(FileName1.Data(), "read");

   TTree * MCpptree = (TTree*)MCppFile->Get("Muons");
   TTree * MoCatree = (TTree*)MoCaFile->Get("Muons");

   TString ToPlot;

   vector<double> maxx(2);
   vector<double> minx(2);

   vector<double> maxY(2);
   vector<double> minY(2);

   vector<double> bins(2);
   vector<double> binsY(2);
   TH1* myh0_temp;
   TH1* myh_temp;
   TH1* myh0;
   TH1* myh;

   if (HistoPlot){
      ToPlot=var1.Data();
      MCpptree->Draw(ToPlot.Data(), Cut.Data(), "Q");
      myh0_temp = (TH1*)gPad->GetPrimitive("htemp")->Clone("MCpp"); 
      MoCatree->Draw(ToPlot.Data(), Cut.Data(), "Q");
      myh_temp = (TH1*)gPad->GetPrimitive("htemp")->Clone("MC");

         minx[0] = myh0_temp->GetXaxis()->GetXmin();
         minx[1] = myh_temp->GetXaxis()->GetXmin();
         maxx[0] = myh0_temp->GetXaxis()->GetXmax();
         maxx[1] = myh_temp->GetXaxis()->GetXmax();

      bins[0] = myh0_temp->GetXaxis()->GetNbins();
      bins[1] = myh_temp->GetXaxis()->GetNbins();
      myh0 = new TH1D("myh0", "myh0", (int)*max_element(bins.begin(), bins.end()), *min_element(minx.begin(), minx.end()), *max_element(maxx.begin(), maxx.end()) );
      myh = (TH1D*)myh0->Clone("myh"); 
       myh->Reset();


   }else{
      ToPlot = TString::Format("%s:%s", var1.Data(), var2.Data());
      MCpptree->Draw(ToPlot.Data(), Cut.Data(), "Q");
      myh0_temp = (TH2*)gPad->GetPrimitive("htemp")->Clone("MCpp"); 
      MoCatree->Draw(ToPlot.Data(), Cut.Data(), "Q");
      myh_temp = (TH2*)gPad->GetPrimitive("htemp")->Clone("MC");

         minx[0] = myh0_temp->GetXaxis()->GetXmin();
         minx[1] = myh_temp->GetXaxis()->GetXmin();
         maxx[0] = myh0_temp->GetXaxis()->GetXmax();
         maxx[1] = myh_temp->GetXaxis()->GetXmax();

      minY[0] = myh0_temp->GetYaxis()->GetXmin();
      minY[1] = myh_temp->GetYaxis()->GetXmin();
      maxY[0] = myh0_temp->GetYaxis()->GetXmax();
      maxY[1] = myh_temp->GetYaxis()->GetXmax();
      bins[0] = myh0_temp->GetXaxis()->GetNbins();
      bins[1] = myh_temp->GetXaxis()->GetNbins();
      binsY[0] = myh0_temp->GetYaxis()->GetNbins();
      binsY[1] = myh_temp->GetYaxis()->GetNbins();
      myh0 = new TH2D("myh0", "myh0", (int)*max_element(bins.begin(), bins.end()), *min_element(minx.begin(), minx.end()), *max_element(maxx.begin(), maxx.end()),                                        (int)*max_element(binsY.begin(), binsY.end()), *min_element(minY.begin(), minY.end()), *max_element(maxY.begin(), maxY.end()) );
       myh = (TH2D*)myh0->Clone("myh"); 
       myh->Reset();

   } 

   
    MCpptree->Draw(TString::Format("%s >> myh0", ToPlot.Data()), "", "Q");
    MoCatree->Draw(TString::Format("%s >> myh", ToPlot.Data()), "", "Q");
    myh0->GetXaxis()->SetTitle(ToPlot.Data());
    myh->GetXaxis()->SetTitle(ToPlot.Data());

    if ((Log) && (HistoPlot)){
       myh0->GetXaxis()->SetMaxDigits(2);
       myh0->GetYaxis()->SetTitle("Events / Integral");
       myh->GetYaxis()->SetTitle("Events / Integral");
    } else if ((Log) && (!HistoPlot)){
       myh0->GetZaxis()->SetTitle("Events / Integral");
       myh->GetZaxis()->SetTitle("Events / Integral");
       myh0->GetYaxis()->SetTitle(var2.Data());
       myh->GetYaxis()->SetTitle(var2.Data());
    } else if (HistoPlot){
       myh0->GetXaxis()->SetMaxDigits(2);
       myh0->GetYaxis()->SetTitle("Events");
       myh->GetYaxis()->SetTitle("Events");
    } else{
       myh0->GetZaxis()->SetTitle("Events");
       myh->GetZaxis()->SetTitle("Events");
       myh0->GetYaxis()->SetTitle(var2.Data());
       myh->GetYaxis()->SetTitle(var2.Data());
    }


   vector<double> maxy(2);
   if ((myh->Integral() != 0.0)&&(Normalize)){
         myh->Scale(1.0/myh->Integral());
      } else{
         std::cout << "Warning data not normalized." << std::endl;
      }
   if ((myh0->Integral() != 0.0)&&(Normalize)){
         myh0->Scale(1.0/myh0->Integral());
      } else{
         std::cout << "Warning data not normalized." << std::endl;
      }
   
   
   maxy[0] = myh0->GetMaximum();
   maxy[1] = myh->GetMaximum();

   TCanvas * can = new TCanvas("can", "can", 0,0,1800,1800);

   if (HistoPlot){
      can->cd();
      if (Cut.EqualTo("")){
         myh->GetXaxis()->SetTitle(TString::Format("%s",myh->GetXaxis()->GetTitle() ));
      }else{
         myh->GetXaxis()->SetTitle(TString::Format("%s, cut: %s",myh->GetXaxis()->GetTitle(), Cut.Data() ));
      }
      if (!HistoPlot){
         myh->GetYaxis()->SetTitle(TString::Format("%s",myh->GetYaxis()->GetTitle() ));
      }
      
      myh->SetMarkerSize(0);  
      myh->SetLineColor(2);
      myh->SetMaximum(  *max_element(maxy.begin(), maxy.end()) * 1.5);
      if (Log){
         gPad->SetLogy();
         myh->SetMaximum(myh->GetMaximum()*100);
         }
      myh->Draw(Opt.Data());
 
 
      myh0->SetMarkerSize(0);  
      myh0->SetLineColor(kBlack);  
      myh0->Draw(TString::Format("%s same", Opt.Data()) );
      
      TLegend * leg = new TLegend(0.65,0.65,0.85,0.85);
      leg->AddEntry(myh, "pPb MC", "l");
      leg->AddEntry(myh0, "pp MC", "l");
      leg->SetBorderSize(0);
      leg->Draw("same");
   } else{
      can->Divide(2,1);
      can->cd(1);
      if (Log){gPad->SetLogz();}
      if (Cut.EqualTo("")){
         myh->GetXaxis()->SetTitle(TString::Format("%s - %s", "pPb MC",myh->GetXaxis()->GetTitle() ));
         myh0->GetXaxis()->SetTitle(TString::Format("%s - %s", "pp MC",myh0->GetXaxis()->GetTitle() ));
      }else{
         myh->GetXaxis()->SetTitle(TString::Format("%s - %s, cut: %s","pPb MC" , myh->GetXaxis()->GetTitle(), Cut.Data() ));
         myh0->GetXaxis()->SetTitle(TString::Format("%s - %s, cut: %s","pp MC" , myh0->GetXaxis()->GetTitle(), Cut.Data() ));
      }
      if (!HistoPlot){
         myh->GetYaxis()->SetTitle(TString::Format("%s - %s", "pPb MC",myh->GetYaxis()->GetTitle() ));
         myh0->GetYaxis()->SetTitle(TString::Format("%s - %s", "pp MC",myh0->GetYaxis()->GetTitle() ));
      }
      myh->SetMaximum(  *max_element(maxy.begin(), maxy.end()) * 1.1);
      myh->Draw(Opt.Data());
      can->cd(2);
      if (Log){gPad->SetLogz();}
      myh0->SetMaximum(  *max_element(maxy.begin(), maxy.end()) * 1.1);
      myh0->Draw(Opt.Data());
      
   };
   can->SaveAs(TString::Format("./checkplots/%s_%s_%s_%i.pdf", var1.Data(), var2.Data(), Cut.Data(),(int)HistoPlot));
   can->SaveAs(TString::Format("./checkplots/%s_%s_%s_%i.png", var1.Data(), var2.Data(), Cut.Data(),(int)HistoPlot));
   return 0;
}
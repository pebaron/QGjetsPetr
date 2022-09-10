int ControlPlot(TString FileName4="ppdata.root",TString FileName0="pp.root", TString FileName1="pPbMCNo0.root", TString FileName2="data.root", TString var1 = "quality", TString var2 = "eta", TString Opt = "colz", TString Cut = "", bool HistoPlot=false, bool Normalize=true, bool Log=false){
   // e.g. root -l "./ControlPlot.C(\"ppdata.root\",\"pp.root\",\"pPbMCNo1.root\",\"data.root\",\"var_eta\", \"var_eta\", \"hist e1\", \"(var_quality==2)&&(abs(var_eta)<3.0)\", 1)"
   //      root -l "./ControlPlot.C(\"ppdata.root\",\"pp.root\",\"pPbMCNo1.root\",\"data.root\",\"var_phi\", \"var_eta\", \"lego2d\", \"(abs(var_eta)<3.0)\", 0)"
   gROOT->SetStyle("ATLAS");
   TFile * DappFile = new TFile(FileName4.Data(), "read");
   TFile * MCppFile = new TFile(FileName0.Data(), "read");
   TFile * MoCaFile = new TFile(FileName1.Data(), "read");
   TFile * DataFile = new TFile(FileName2.Data(), "read");

   TTree * Dapptree = (TTree*)DappFile->Get("Muons");
   TTree * MCpptree = (TTree*)MCppFile->Get("Muons");
   TTree * MoCatree = (TTree*)MoCaFile->Get("Muons");
   TTree * Datatree = (TTree*)DataFile->Get("Muons");

   TString ToPlot;
   if (HistoPlot){
      ToPlot=var1.Data();
   }else{
      ToPlot = TString::Format("%s:%s", var1.Data(), var2.Data());
   }
   Dapptree->Draw(ToPlot.Data(), Cut.Data(), "Q");
   TH2 *myh3 = (TH2*)gPad->GetPrimitive("htemp")->Clone("Dapp"); 
   MCpptree->Draw(ToPlot.Data(), Cut.Data(), "Q");
   TH2 *myh0 = (TH2*)gPad->GetPrimitive("htemp")->Clone("MCpp"); 
   MoCatree->Draw(ToPlot.Data(), Cut.Data(), "Q");
   TH2 *myh = (TH2*)gPad->GetPrimitive("htemp")->Clone("MC"); 
   Datatree->Draw(ToPlot.Data(), Cut.Data(), "Q");
   TH2 *myh2 = (TH2*)gPad->GetPrimitive("htemp")->Clone("Data"); 
   vector<double> maxy(4);
   if ((myh->Integral() != 0.0)&&(Normalize)){
         myh->Scale(1.0/myh->Integral());
      } else{
         std::cout << "Warning data not normalized." << std::endl;
      }
   if ((myh2->Integral() != 0.0)&&(Normalize)){
         myh2->Scale(1.0/myh2->Integral());
      } else{
         std::cout << "Warning data not normalized." << std::endl;
      }
   if ((myh0->Integral() != 0.0)&&(Normalize)){
         myh0->Scale(1.0/myh0->Integral());
      } else{
         std::cout << "Warning data not normalized." << std::endl;
      }
   if ((myh3->Integral() != 0.0)&&(Normalize)){
         myh3->Scale(1.0/myh3->Integral());
      } else{
         std::cout << "Warning data not normalized." << std::endl;
      }
   
   maxy[0] = myh0->GetMaximum();
   maxy[1] = myh->GetMaximum();
   maxy[2] = myh2->GetMaximum();
   maxy[3] = myh3->GetMaximum();
   //auto MAXY = *std::max_element(std::begin(maxy), std::end(maxy));

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
      if (Log){gPad->SetLogy();}
      myh->Draw(Opt.Data());
 
      myh2->SetMarkerSize(0);  
      myh2->Draw(TString::Format("%s same", Opt.Data()) );
 
      myh0->SetMarkerSize(0);  
      myh0->SetLineColor(kGreen);  
      myh0->Draw(TString::Format("%s same", Opt.Data()) );
      
      myh3->SetMarkerSize(0);  
      myh3->SetLineColor(kBlue);  
      myh3->Draw(TString::Format("%s same", Opt.Data()) );

      TLegend * leg = new TLegend(0.65,0.65,0.85,0.85);
      leg->AddEntry(myh2, "pPb Data", "l");
      leg->AddEntry(myh, "pPb MC", "l");
      leg->AddEntry(myh3, "pp Data", "l");
      leg->AddEntry(myh0, "pp MC", "l");
      leg->SetBorderSize(0);
      leg->Draw("same");
   } else{
      can->Divide(2,2);
      can->cd(1);
      if (Log){gPad->SetLogz();}
      if (Cut.EqualTo("")){
         myh->GetXaxis()->SetTitle(TString::Format("%s - %s", "pPb MC",myh->GetXaxis()->GetTitle() ));
         myh2->GetXaxis()->SetTitle(TString::Format("%s - %s", "pPb Data",myh2->GetXaxis()->GetTitle() ));
         myh0->GetXaxis()->SetTitle(TString::Format("%s - %s", "pp MC",myh0->GetXaxis()->GetTitle() ));
         myh3->GetXaxis()->SetTitle(TString::Format("%s - %s", "pp Data",myh3->GetXaxis()->GetTitle() ));
      }else{
         myh->GetXaxis()->SetTitle(TString::Format("%s - %s, cut: %s","pPb MC" , myh->GetXaxis()->GetTitle(), Cut.Data() ));
         myh2->GetXaxis()->SetTitle(TString::Format("%s - %s, cut: %s","pPb Data" , myh2->GetXaxis()->GetTitle(), Cut.Data() ));
         myh0->GetXaxis()->SetTitle(TString::Format("%s - %s, cut: %s","pp MC" , myh0->GetXaxis()->GetTitle(), Cut.Data() ));
         myh3->GetXaxis()->SetTitle(TString::Format("%s - %s, cut: %s","pp Data" , myh3->GetXaxis()->GetTitle(), Cut.Data() ));
      }
      if (!HistoPlot){
         myh->GetYaxis()->SetTitle(TString::Format("%s - %s", "pPb MC",myh->GetYaxis()->GetTitle() ));
         myh2->GetYaxis()->SetTitle(TString::Format("%s - %s", "pPb Data",myh2->GetYaxis()->GetTitle() ));
         myh0->GetYaxis()->SetTitle(TString::Format("%s - %s", "pp MC",myh0->GetYaxis()->GetTitle() ));
         myh3->GetYaxis()->SetTitle(TString::Format("%s - %s", "pp Data",myh3->GetYaxis()->GetTitle() ));
      }
      myh->SetMaximum(  *max_element(maxy.begin(), maxy.end()) * 1.1);
      myh->Draw(Opt.Data());
      can->cd(2);
      if (Log){gPad->SetLogz();}
      myh2->SetMaximum(  *max_element(maxy.begin(), maxy.end()) * 1.1);
      myh2->Draw(Opt.Data());
      can->cd(3);
      if (Log){gPad->SetLogz();}
      myh0->SetMaximum(  *max_element(maxy.begin(), maxy.end()) * 1.1);
      myh0->Draw(Opt.Data());
      can->cd(4);
      if (Log){gPad->SetLogz();}
      myh3->SetMaximum(  *max_element(maxy.begin(), maxy.end()) * 1.1);
      myh3->Draw(Opt.Data());
   };
   can->SaveAs(TString::Format("%s_%s_%s_%i.pdf", var1.Data(), var2.Data(), Cut.Data(),(int)HistoPlot));
   can->SaveAs(TString::Format("%s_%s_%s_%i.png", var1.Data(), var2.Data(), Cut.Data(),(int)HistoPlot));
   return 0;
}
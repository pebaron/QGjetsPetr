TString GetR(TString var){
if (var.Contains("FastJets02")) return "02";
if (var.Contains("FastJets04")) return "04";
if (var.Contains("FastJets06")) return "06";
if (var.Contains("FastJets08")) return "08";
if (var.Contains("FastJets10")) return "10";
    return "";
}

TFile * fracA;
TFile * fracB;
TH2F *  frA ;
TH2F *  frB ;

double ScaleMe(double Pt, double Eta, int Energy ,int EnergyA = 900, int EnergyB = 7000, int gluon = 1){
    if (Pt >= 200.) return 0.;
    if (TMath::Abs(Eta) >= 2.5) return 0.;

    if (gluon==1){
        if (Energy == EnergyA){
            return (1. - frB->GetBinContent(frB->GetXaxis()->FindBin(Pt), frB->GetYaxis()->FindBin(Eta))) /
            (frA->GetBinContent(frA->GetXaxis()->FindBin(Pt), frA->GetYaxis()->FindBin(Eta)) - frB->GetBinContent(frB->GetXaxis()->FindBin(Pt), frB->GetYaxis()->FindBin(Eta)));
        }            
        if (Energy == EnergyB){
            return (1. - frA->GetBinContent(frA->GetXaxis()->FindBin(Pt), frA->GetYaxis()->FindBin(Eta))) /
            (frA->GetBinContent(frA->GetXaxis()->FindBin(Pt), frA->GetYaxis()->FindBin(Eta)) - frB->GetBinContent(frB->GetXaxis()->FindBin(Pt), frB->GetYaxis()->FindBin(Eta)));
        }
    }else{
        if (Energy == EnergyA){
            return (frB->GetBinContent(frB->GetXaxis()->FindBin(Pt), frB->GetYaxis()->FindBin(Eta))) /
            (frA->GetBinContent(frA->GetXaxis()->FindBin(Pt), frA->GetYaxis()->FindBin(Eta)) - frB->GetBinContent(frB->GetXaxis()->FindBin(Pt), frB->GetYaxis()->FindBin(Eta)));
        }
        if (Energy == EnergyB){
            return (frA->GetBinContent(frA->GetXaxis()->FindBin(Pt), frA->GetYaxis()->FindBin(Eta))) /
            (frA->GetBinContent(frA->GetXaxis()->FindBin(Pt), frA->GetYaxis()->FindBin(Eta)) - frB->GetBinContent(frB->GetXaxis()->FindBin(Pt), frB->GetYaxis()->FindBin(Eta)));
        }

    }
    return 0;
    
}

int Plot2D(TString EnergyA = "900", TString EnergyB = "7000", 
          TString Var1 = "FastJets10MultLam50", TString Var2 = "FastJets10LhaLam50"){

    TFile * rfile = new TFile(TString::Format("out_%s_%s_pythia.root", EnergyA.Data(), EnergyB.Data()), "read");

    fracA = new TFile(TString::Format("GluonFraction_%s.root", EnergyA.Data()), "read");
    fracB = new TFile(TString::Format("GluonFraction_%s.root", EnergyB.Data()), "read");
    frA   = (TH2F*)fracA->Get(TString::Format("GluonFraction_%s",EnergyA.Data()));
    frB   = (TH2F*)fracB->Get(TString::Format("GluonFraction_%s",EnergyB.Data()));

    

    TTree * treeAvar1 = (TTree*)rfile->Get(TString::Format("%s_%s", Var1.Data(), EnergyA.Data() ));
    TTree * treeAvar2 = (TTree*)rfile->Get(TString::Format("%s_%s", Var2.Data(), EnergyA.Data() ));
    TTree * treeAPt   = (TTree*)rfile->Get(TString::Format("FastJets%sPt_%s", GetR(Var1).Data(), EnergyA.Data() ));
    TTree * treeAEta  = (TTree*)rfile->Get(TString::Format("FastJets%sEta_%s", GetR(Var1).Data(), EnergyA.Data() ));

    TTree * treeBvar1 = (TTree*)rfile->Get(TString::Format("%s_%s", Var1.Data(), EnergyB.Data() ));
    TTree * treeBvar2 = (TTree*)rfile->Get(TString::Format("%s_%s", Var2.Data(), EnergyB.Data() ));
    TTree * treeBPt = (TTree*)rfile->Get(TString::Format("FastJets%sPt_%s", GetR(Var1).Data(), EnergyB.Data() ));
    TTree * treeBEta = (TTree*)rfile->Get(TString::Format("FastJets%sEta_%s", GetR(Var1).Data(), EnergyB.Data() ));

    
    treeAvar1->AddFriend(treeAvar2);
    treeAvar1->AddFriend(treeAPt  );
    treeAvar1->AddFriend(treeAEta );

    treeBvar1->AddFriend(treeBvar2);
    treeBvar1->AddFriend(treeBPt  );
    treeBvar1->AddFriend(treeBEta );

    TString Bins;
    if (Var1.Contains("Mult")){ Bins = "(100,0,100,100,0,1)";}
    if (Var2.Contains("Mult")){ Bins = "(100,0,1,100,0,100)";}
    if ((!Var1.Contains("Mult"))&&(!Var2.Contains("Mult"))){ Bins = "(100,0,1,100,0,1)";}

    TString ToDraw ;
    TString ToCut  ;

    ToDraw = TString::Format("%s_%s.%s:%s_%s.%s >> hg_A%s", Var2.Data(), EnergyA.Data(), Var2.Data(), Var1.Data(), EnergyA.Data(), Var1.Data(), Bins.Data() );
    ToCut  = TString::Format("%s_%s.%s*(ScaleMe(FastJets%sPt_%s.FastJets%sPt,FastJets%sEta_%s.FastJets%sEta,%s, %s, %s))", 
            //Var2.Data(), EnergyA.Data(), Var2.Data(), 
            Var1.Data(), EnergyA.Data(), Var1.Data(),
            GetR(Var1).Data(), EnergyA.Data(), GetR(Var1).Data(),  
            GetR(Var1).Data(), EnergyA.Data(), GetR(Var1).Data(),  
            EnergyA.Data(),
            EnergyA.Data(),
            EnergyB.Data() );

    cout << "hg_A" << endl;
    cout << ToDraw.Data() << endl;
    cout << ToCut.Data() << endl;
    treeAvar1->Draw(ToDraw.Data(), ToCut.Data(), "goff");
    //TCanvas * can = new TCanvas();
    
    ToDraw = TString::Format("%s_%s.%s:%s_%s.%s >> hg_B%s", Var2.Data(), EnergyB.Data(), Var2.Data(), Var1.Data(), EnergyB.Data(), Var1.Data(), Bins.Data() );
    ToCut  = TString::Format("%s_%s.%s*(ScaleMe(FastJets%sPt_%s.FastJets%sPt,FastJets%sEta_%s.FastJets%sEta,%s, %s, %s))", 
            //Var2.Data(), EnergyA.Data(), Var2.Data(), 
            Var1.Data(), EnergyB.Data(), Var1.Data(),
            GetR(Var1).Data(), EnergyB.Data(), GetR(Var1).Data(),  
            GetR(Var1).Data(), EnergyB.Data(), GetR(Var1).Data(),  
            EnergyB.Data(),
            EnergyA.Data(),
            EnergyB.Data() );
    //ToCut = "";
    treeBvar1->Draw(ToDraw.Data(), ToCut.Data(), "goff");

    // quark 

    ToDraw = TString::Format("%s_%s.%s:%s_%s.%s >> hq_A%s", Var2.Data(), EnergyA.Data(), Var2.Data(), Var1.Data(), EnergyA.Data(), Var1.Data(), Bins.Data() );
    ToCut  = TString::Format("%s_%s.%s*(ScaleMe(FastJets%sPt_%s.FastJets%sPt,FastJets%sEta_%s.FastJets%sEta,%s, %s, %s, 0))", 
            //Var2.Data(), EnergyA.Data(), Var2.Data(), 
            Var1.Data(), EnergyA.Data(), Var1.Data(),
            GetR(Var1).Data(), EnergyA.Data(), GetR(Var1).Data(),  
            GetR(Var1).Data(), EnergyA.Data(), GetR(Var1).Data(),  
            EnergyA.Data(),
            EnergyA.Data(),
            EnergyB.Data() );

    treeAvar1->Draw(ToDraw.Data(), ToCut.Data(), "goff");

    ToDraw = TString::Format("%s_%s.%s:%s_%s.%s >> hq_B%s", Var2.Data(), EnergyB.Data(), Var2.Data(), Var1.Data(), EnergyB.Data(), Var1.Data(), Bins.Data() );
    ToCut  = TString::Format("%s_%s.%s*(ScaleMe(FastJets%sPt_%s.FastJets%sPt,FastJets%sEta_%s.FastJets%sEta,%s, %s, %s, 0))", 
            //Var2.Data(), EnergyA.Data(), Var2.Data(), 
            Var1.Data(), EnergyB.Data(), Var1.Data(),
            GetR(Var1).Data(), EnergyB.Data(), GetR(Var1).Data(),  
            GetR(Var1).Data(), EnergyB.Data(), GetR(Var1).Data(),  
            EnergyB.Data(),
            EnergyA.Data(),
            EnergyB.Data() );
    //ToCut = "";
    treeBvar1->Draw(ToDraw.Data(), ToCut.Data(), "goff");

    //get vars

    TH2D * hg_A = (TH2D*)gDirectory->Get("hg_A");
    TH2D * hg_B = (TH2D*)gDirectory->Get("hg_B");
    hg_A->Scale(1./hg_A->GetEntries());
    hg_B->Scale(1./hg_B->GetEntries());
    hg_A->Add(hg_B, -1.);
    TCanvas * can = new TCanvas("can","can", 0,0,1600,1600);
    can->Divide(2,2);
    can->cd(1);
    gPad->SetRightMargin(0.15);
    hg_A->SetTitle("Gluon");
    hg_A->SetName("Gluon");
    hg_A->GetXaxis()->SetTitle(Var1.Data());
    hg_A->GetYaxis()->SetTitle(Var2.Data());
    hg_A->Draw("colz");
    can->Modified(); can->Update();
    gPad->Modified(); gPad->Update();
    TH2F * hg_A_can = (TH2F*)gDirectory->Get("Gluon");
    TPaveText * pt1 = (TPaveText *)hg_A_can->GetListOfFunctions()->FindObject("stats");
    pt1->SetX1NDC(0.59);
    pt1->SetX2NDC(0.835);
    pt1->SetY1NDC(0.709);
    pt1->SetY2NDC(0.88);
    can->Modified(); can->Update();
    gPad->Modified(); gPad->Update();


    TH2D * hq_A = (TH2D*)gDirectory->Get("hq_A");
    TH2D * hq_B = (TH2D*)gDirectory->Get("hq_B");
    hq_A->Scale(1./hq_A->GetEntries());
    hq_B->Scale(1./hq_B->GetEntries());
    hq_B->Add(hq_A, -1.);
    can->cd(2);
    gPad->SetRightMargin(0.15);
    hq_B->SetTitle("Quark");
    hq_B->SetName("Quark");
    hq_B->GetXaxis()->SetTitle(Var1.Data());
    hq_B->GetYaxis()->SetTitle(Var2.Data());
    hq_B->Draw("colz");   

    can->Modified(); can->Update();
    gPad->Modified(); gPad->Update();
    TH2F * hq_B_can = (TH2F*)gDirectory->Get("Quark");
    TPaveText * pt2 = (TPaveText *)hq_B_can->GetListOfFunctions()->FindObject("stats");
    pt2->SetX1NDC(0.59);
    pt2->SetX2NDC(0.835);
    pt2->SetY1NDC(0.709);
    pt2->SetY2NDC(0.88);
    can->Modified(); can->Update();
    gPad->Modified(); gPad->Update();

    can->cd(3);
    gPad->SetRightMargin(0.15);
    TH2F * hg_AX = (TH2F*)hg_A->ProjectionX(TString::Format("gluon_%s", Var1.Data()));
    hg_AX->SetLineColor(kBlue);
    hg_AX->SetStats(0);
    hg_AX->SetTitle("ProjectionX");
    
    TH2F * hq_BX = (TH2F*)hq_B->ProjectionX(TString::Format("quark_%s", Var1.Data()));
    hq_BX->SetLineColor(kRed);
    hq_BX->SetStats(0);
    hq_BX->SetTitle("ProjectionX");
    
    vector<double> maxs;
    maxs.push_back(hg_AX->GetMaximum());
    maxs.push_back(hq_BX->GetMaximum());

    vector<double> mins;
    mins.push_back(hg_AX->GetMinimum());
    mins.push_back(hq_BX->GetMinimum());

    double maxy = *max_element(maxs.begin(), maxs.end());
    double miny = *min_element(mins.begin(), mins.end());

    hg_AX->SetMaximum(1.3*maxy);
    hg_AX->SetMinimum(1.3*miny);

    //hg_AX->Scale(hg_AX->GetMaximum()/maxy);
    //hq_BX->Scale(hq_BX->GetMaximum()/maxy);

    hg_AX->Draw("hist e1");
    hq_BX->Draw("hist e1 same");

    //add legend
    TLegend * leg = new TLegend(0.57,0.69,0.74,0.84);
    leg->SetBorderSize(0);
    leg->AddEntry(hg_AX, "Gluon");
    leg->AddEntry(hq_BX, "Quark");
    leg->Draw("same");

    can->cd(4);
    gPad->SetRightMargin(0.15);
    TH2F * hg_AY = (TH2F*)hg_A->ProjectionY(TString::Format("gluon_%s", Var2.Data()));
    hg_AY->SetLineColor(kBlue);
    hg_AY->SetStats(0);
    hg_AY->SetTitle("ProjectionY");
    
    TH2F * hq_BY = (TH2F*)hq_B->ProjectionY(TString::Format("quark_%s", Var2.Data()));
    hq_BY->SetLineColor(kRed);
    hq_BY->SetStats(0);
    hq_BY->SetTitle("ProjectionY");
    
    vector<double> maxs2;
    maxs2.push_back(hg_AY->GetMaximum());
    maxs2.push_back(hq_BY->GetMaximum());

    vector<double> mins2;
    mins2.push_back(hg_AY->GetMinimum());
    mins2.push_back(hq_BY->GetMinimum());

    double maxy2 = *max_element(maxs2.begin(), maxs2.end());
    double miny2 = *min_element(mins2.begin(), mins2.end());

    hg_AY->SetMaximum(1.3*maxy2);
    hg_AY->SetMinimum(1.3*miny2);

    hg_AY->Draw("hist e1");
    hq_BY->Draw("hist e1 same");

    TLegend * leg2 = new TLegend(0.57,0.69,0.74,0.84);
    leg2->SetBorderSize(0);
    leg2->AddEntry(hg_AY, "Gluon");
    leg2->AddEntry(hq_BY, "Quark");
    leg2->Draw("same");


    return 0;
}
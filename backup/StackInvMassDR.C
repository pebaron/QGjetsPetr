#include "TAxis.h"
#include "TH1.h"
#include "TArrayD.h"

void ScaleAxis(TAxis *a, Double_t (*Scale)(Double_t))
{
  if (!a) return; // just a precaution
  if (a->GetXbins()->GetSize())
    {
      // an axis with variable bins
      // note: bins must remain in increasing order, hence the "Scale"
      // function must be strictly (monotonically) increasing
      TArrayD X(*(a->GetXbins()));
      for(Int_t i = 0; i < X.GetSize(); i++) X[i] = Scale(X[i]);
      a->Set((X.GetSize() - 1), X.GetArray()); // new Xbins
    }
  else
    {
      // an axis with fix bins
      // note: we modify Xmin and Xmax only, hence the "Scale" function
      // must be linear (and Xmax must remain greater than Xmin)
      a->Set( a->GetNbins(),
              Scale(a->GetXmin()), // new Xmin
              Scale(a->GetXmax()) ); // new Xmax
    }
  return;
}

Double_t ScaleX(Double_t x)
{
  Double_t v;
  v =  x/1000.; // "linear scaling" function example
  return v;
}

void ScaleXaxis(TH1 *h, Double_t (*Scale)(Double_t))
{
  if (!h) return; // just a precaution
  ScaleAxis(h->GetXaxis(), Scale);
  return;
}

void ScaleXaxisStack(THStack *h, Double_t (*Scale)(Double_t))
{
  if (!h) return; // just a precaution
  ScaleAxis(h->GetXaxis(), Scale);
  return;
}
// run root -l StackInvMass.C , at the end interchange saving options!
int StackInvMassDR(TString Combination = "_1_0", TString CombinationPtcl = "_1_0", TString DRCut1 = "3.10", TString DRCut2 = "3.18"){
    TFile * rfile = new TFile("DRInvMass.root", "read");
    
    //TH1D * inv_mass_SM            = (TH1D*)rfile->Get(TString::Format("inv_mass_SM%s",Combination.Data() ) );
    //TH1D * inv_mass_Y0            = (TH1D*)rfile->Get(TString::Format("inv_mass_Y0%s",Combination.Data() ) );
    //TH1D * inv_mass_SM_stand      = (TH1D*)rfile->Get(TString::Format("inv_mass_SM_stand%s",Combination.Data() ) );
    //TH1D * inv_mass_Y0_stand      = (TH1D*)rfile->Get(TString::Format("inv_mass_Y0_stand%s",Combination.Data() ) );
    //TH1D * ptcl_inv_mass_SM       = (TH1D*)rfile->Get(TString::Format("ptcl_inv_mass_SM%s",CombinationPtcl.Data() ) );
    //TH1D * ptcl_inv_mass_Y0       = (TH1D*)rfile->Get(TString::Format("ptcl_inv_mass_Y0%s",CombinationPtcl.Data() ) );
    //TH1D * ptcl_inv_mass_SM_stand = (TH1D*)rfile->Get(TString::Format("ptcl_inv_mass_SM_stand%s",CombinationPtcl.Data() ) );
    //TH1D * ptcl_inv_mass_Y0_stand = (TH1D*)rfile->Get(TString::Format("ptcl_inv_mass_Y0_stand%s",CombinationPtcl.Data() ) );

    TTree * tree = (TTree*)rfile->Get("tree");

    TH1D * inv_mass_SM            = new TH1D(TString::Format("InvMass_inv_mass_SM%s",Combination.Data() ), TString::Format("InvMass_inv_mass_SM%s",Combination.Data() ), 100,0,4000);
    TH1D * inv_mass_Y0            = new TH1D(TString::Format("InvMass_inv_mass_Y0%s",Combination.Data() ), TString::Format("InvMass_inv_mass_Y0%s",Combination.Data() ), 100,0,4000);
    TH1D * inv_mass_SM_stand      = new TH1D(TString::Format("InvMass_inv_mass_SM_stand%s",Combination.Data() ), TString::Format("InvMass_inv_mass_SM_stand%s",Combination.Data() ), 100,0,4000);
    TH1D * inv_mass_Y0_stand      = new TH1D(TString::Format("InvMass_inv_mass_Y0_stand%s",Combination.Data() ), TString::Format("InvMass_inv_mass_Y0_stand%s",Combination.Data() ), 100,0,4000);
    TH1D * ptcl_inv_mass_SM       = new TH1D(TString::Format("InvMass_ptcl_inv_mass_SM%s",CombinationPtcl.Data() ), TString::Format("InvMass_ptcl_inv_mass_SM%s",CombinationPtcl.Data() ), 100,0,4000);
    TH1D * ptcl_inv_mass_Y0       = new TH1D(TString::Format("InvMass_ptcl_inv_mass_Y0%s",CombinationPtcl.Data() ), TString::Format("InvMass_ptcl_inv_mass_Y0%s",CombinationPtcl.Data() ), 100,0,4000);
    TH1D * ptcl_inv_mass_SM_stand = new TH1D(TString::Format("InvMass_ptcl_inv_mass_SM_stand%s",CombinationPtcl.Data() ), TString::Format("InvMass_ptcl_inv_mass_SM_stand%s",CombinationPtcl.Data() ), 100,0,4000);
    TH1D * ptcl_inv_mass_Y0_stand = new TH1D(TString::Format("InvMass_ptcl_inv_mass_Y0_stand%s",CombinationPtcl.Data() ), TString::Format("InvMass_ptcl_inv_mass_Y0_stand%s",CombinationPtcl.Data() ), 100,0,4000);

    TString TS_inv_mass_SM            =  TString::Format("InvMass_inv_mass_SM%s",Combination.Data() );
    TString TS_inv_mass_Y0            =  TString::Format("InvMass_inv_mass_Y0%s",Combination.Data() );
    TString TS_inv_mass_SM_stand      =  TString::Format("InvMass_inv_mass_SM_stand%s",Combination.Data() );
    TString TS_inv_mass_Y0_stand      =  TString::Format("InvMass_inv_mass_Y0_stand%s",Combination.Data() );
    TString TS_ptcl_inv_mass_SM       =  TString::Format("InvMass_ptcl_inv_mass_SM%s",CombinationPtcl.Data() );
    TString TS_ptcl_inv_mass_Y0       =  TString::Format("InvMass_ptcl_inv_mass_Y0%s",CombinationPtcl.Data() );
    TString TS_ptcl_inv_mass_SM_stand =  TString::Format("InvMass_ptcl_inv_mass_SM_stand%s",CombinationPtcl.Data() );
    TString TS_ptcl_inv_mass_Y0_stand =  TString::Format("InvMass_ptcl_inv_mass_Y0_stand%s",CombinationPtcl.Data() );

    TString TS_DR_SM            =  TString::Format("DR_inv_mass_SM%s",Combination.Data() );
    TString TS_DR_Y0            =  TString::Format("DR_inv_mass_Y0%s",Combination.Data() );
    TString TS_DR_SM_stand      =  TString::Format("DR_inv_mass_SM_stand%s",Combination.Data() );
    TString TS_DR_Y0_stand      =  TString::Format("DR_inv_mass_Y0_stand%s",Combination.Data() );
    TString TS_ptcl_DR_SM       =  TString::Format("DR_ptcl_inv_mass_SM%s",CombinationPtcl.Data() );
    TString TS_ptcl_DR_Y0       =  TString::Format("DR_ptcl_inv_mass_Y0%s",CombinationPtcl.Data() );
    TString TS_ptcl_DR_SM_stand =  TString::Format("DR_ptcl_inv_mass_SM_stand%s",CombinationPtcl.Data() );
    TString TS_ptcl_DR_Y0_stand =  TString::Format("DR_ptcl_inv_mass_Y0_stand%s",CombinationPtcl.Data() );

    tree->Draw(TString::Format("%s >> %s",TS_inv_mass_SM           .Data(), TS_inv_mass_SM           .Data() ),TString::Format("((%s>%s)&&(%s<%s))", TS_DR_SM           .Data(), DRCut1.Data(),  TS_DR_SM           .Data(), DRCut2.Data() ), "goff");
    tree->Draw(TString::Format("%s >> %s",TS_inv_mass_Y0           .Data(), TS_inv_mass_Y0           .Data() ),TString::Format("((%s>%s)&&(%s<%s))", TS_DR_Y0           .Data(), DRCut1.Data(),  TS_DR_Y0           .Data(), DRCut2.Data() ), "goff");
    tree->Draw(TString::Format("%s >> %s",TS_inv_mass_SM_stand     .Data(), TS_inv_mass_SM_stand     .Data() ),TString::Format("((%s>%s)&&(%s<%s))", TS_DR_SM_stand     .Data(), DRCut1.Data(),  TS_DR_SM_stand     .Data(), DRCut2.Data() ), "goff");
    tree->Draw(TString::Format("%s >> %s",TS_inv_mass_Y0_stand     .Data(), TS_inv_mass_Y0_stand     .Data() ),TString::Format("((%s>%s)&&(%s<%s))", TS_DR_Y0_stand     .Data(), DRCut1.Data(),  TS_DR_Y0_stand     .Data(), DRCut2.Data() ), "goff");
    tree->Draw(TString::Format("%s >> %s",TS_ptcl_inv_mass_SM      .Data(), TS_ptcl_inv_mass_SM      .Data() ),TString::Format("((%s>%s)&&(%s<%s))", TS_ptcl_DR_SM      .Data(), DRCut1.Data(),  TS_ptcl_DR_SM      .Data(), DRCut2.Data() ), "goff");
    tree->Draw(TString::Format("%s >> %s",TS_ptcl_inv_mass_Y0      .Data(), TS_ptcl_inv_mass_Y0      .Data() ),TString::Format("((%s>%s)&&(%s<%s))", TS_ptcl_DR_Y0      .Data(), DRCut1.Data(),  TS_ptcl_DR_Y0      .Data(), DRCut2.Data() ), "goff");
    tree->Draw(TString::Format("%s >> %s",TS_ptcl_inv_mass_SM_stand.Data(), TS_ptcl_inv_mass_SM_stand.Data() ),TString::Format("((%s>%s)&&(%s<%s))", TS_ptcl_DR_SM_stand.Data(), DRCut1.Data(),  TS_ptcl_DR_SM_stand.Data(), DRCut2.Data() ), "goff");
    tree->Draw(TString::Format("%s >> %s",TS_ptcl_inv_mass_Y0_stand.Data(), TS_ptcl_inv_mass_Y0_stand.Data() ),TString::Format("((%s>%s)&&(%s<%s))", TS_ptcl_DR_Y0_stand.Data(), DRCut1.Data(),  TS_ptcl_DR_Y0_stand.Data(), DRCut2.Data() ), "goff");

    cout << "Integral is = " << inv_mass_Y0->Integral() << endl;
    double weight = 0.075;
    inv_mass_Y0 ->Scale(weight);
    inv_mass_Y0_stand ->Scale(weight);
    ptcl_inv_mass_Y0 ->Scale(weight);
    ptcl_inv_mass_Y0_stand ->Scale(weight);


    double norm_ml_det     = inv_mass_SM->Integral() + 
                             inv_mass_Y0->Integral();
    double norm_stand_det  = inv_mass_SM_stand->Integral() +
                             inv_mass_Y0_stand->Integral(); 
    double norm_ml_ptcl     = ptcl_inv_mass_SM->Integral() + 
                              ptcl_inv_mass_Y0->Integral();
    double norm_stand_ptcl  = ptcl_inv_mass_SM_stand->Integral() +
                              ptcl_inv_mass_Y0_stand->Integral(); 

    inv_mass_SM->Scale(1./norm_ml_det);
    inv_mass_Y0->Scale(1./norm_ml_det);
    inv_mass_SM_stand->Scale(1./norm_stand_det);
    inv_mass_Y0_stand->Scale(1./norm_stand_det);
    ptcl_inv_mass_SM->Scale(1./norm_ml_ptcl);
    ptcl_inv_mass_Y0->Scale(1./norm_ml_ptcl);
    ptcl_inv_mass_SM_stand->Scale(1./norm_stand_ptcl);
    ptcl_inv_mass_Y0_stand->Scale(1./norm_stand_ptcl);

    THStack *hs_ml_det;
    THStack *hs_stand_det;
    THStack *hs_ml_ptcl;
    THStack *hs_stand_ptcl;
    if (Combination.EqualTo("")){
    hs_ml_det     = new THStack("hs_ml_det",";m_{JJ} [GeV];Events / (Int._{tty_{0}} + Int._{SMtttt})");
    hs_stand_det  = new THStack("hs_stand_det",";m_{JJ} [GeV];Events / (Int._{tty_{0}} + Int._{SMtttt})");
    }else{
    hs_ml_det     = new THStack("hs_ml_det",TString::Format(";m_{%c%c} [GeV];Events / (Int._{tty_{0}} + Int._{SMtttt})",Combination[1], Combination[3]));
    hs_stand_det  = new THStack("hs_stand_det",TString::Format(";m_{%c%c} [GeV];Events / (Int._{tty_{0}} + Int._{SMtttt})",Combination[1], Combination[3]) );
    }
    if (CombinationPtcl.EqualTo("")){
    hs_ml_ptcl    = new THStack("hs_ml_ptcl",";m_{JJ} [GeV];Events / (Int._{tty_{0}} + Int._{SMtttt})");
    hs_stand_ptcl = new THStack("hs_stand_ptcl",";m_{JJ} [GeV];Events / (Int._{tty_{0}} + Int._{SMtttt})");
    }else{
    hs_ml_ptcl    = new THStack("hs_ml_ptcl",TString::Format(";m_{%c%c} [GeV];Events / (Int._{tty_{0}} + Int._{SMtttt})", CombinationPtcl[1], CombinationPtcl[3]));
    hs_stand_ptcl = new THStack("hs_stand_ptcl",TString::Format(";m_{%c%c} [GeV];Events / (Int._{tty_{0}} + Int._{SMtttt})", CombinationPtcl[1], CombinationPtcl[3]));
    }

    TH1D * inv_mass_SM_stand_clone      = (TH1D*)inv_mass_SM_stand->     Clone(TString::Format("%s_clone", inv_mass_SM_stand->     GetName() ));
    TH1D * inv_mass_Y0_stand_clone      = (TH1D*)inv_mass_Y0_stand->     Clone(TString::Format("%s_clone", inv_mass_Y0_stand->     GetName() ));
    TH1D * ptcl_inv_mass_SM_stand_clone = (TH1D*)ptcl_inv_mass_SM_stand->Clone(TString::Format("%s_clone", ptcl_inv_mass_SM_stand->GetName() ));
    TH1D * ptcl_inv_mass_Y0_stand_clone = (TH1D*)ptcl_inv_mass_Y0_stand->Clone(TString::Format("%s_clone", ptcl_inv_mass_Y0_stand->GetName() ));

    inv_mass_SM_stand_clone     ->SetLineStyle(2);
    inv_mass_Y0_stand_clone     ->SetLineStyle(2);
    ptcl_inv_mass_SM_stand_clone->SetLineStyle(2);
    ptcl_inv_mass_Y0_stand_clone->SetLineStyle(2);
    inv_mass_SM_stand_clone->Add(inv_mass_Y0_stand_clone);
    ptcl_inv_mass_SM_stand_clone->Add(ptcl_inv_mass_Y0_stand_clone);

    inv_mass_SM_stand_clone->SetMarkerStyle(52);
    ptcl_inv_mass_SM_stand_clone->SetMarkerStyle(52);
    
    
    //inv_mass_SM_stand->SetLineStyle(2);
    //ptcl_inv_mass_SM_stand->SetLineStyle(2);
    

    inv_mass_SM->           SetFillColor(kBlue);
    inv_mass_SM->           SetLineColor(kBlue);
    inv_mass_Y0->           SetFillColor(kRed);
    inv_mass_Y0->           SetLineColor(kRed);
    //inv_mass_SM_stand->     SetFillColor(kBlue);
    //inv_mass_Y0_stand->     SetFillColor(kRed);
    ptcl_inv_mass_SM->      SetFillColor(kBlue);
    ptcl_inv_mass_Y0->      SetFillColor(kRed);
    ptcl_inv_mass_SM->      SetLineColor(kBlue);
    ptcl_inv_mass_Y0->      SetLineColor(kRed);
    //ptcl_inv_mass_SM_stand->SetFillColor(kBlue);
    //ptcl_inv_mass_Y0_stand->SetFillColor(kRed);

    hs_ml_det->Add(inv_mass_SM);
    hs_ml_det->Add(inv_mass_Y0);
    hs_stand_det->Add(inv_mass_SM_stand_clone);
    hs_stand_det->Add(inv_mass_Y0_stand_clone);
    hs_ml_ptcl->Add(ptcl_inv_mass_SM);
    hs_ml_ptcl->Add(ptcl_inv_mass_Y0);
    hs_stand_ptcl->Add(ptcl_inv_mass_SM_stand_clone);
    hs_stand_ptcl->Add(ptcl_inv_mass_Y0_stand_clone);

    TCanvas *cs = new TCanvas("DRcs","DRcs",0,0,1600,1600);
    TCanvas *cs2 = new TCanvas("DRcs2","DRcs2",0,0,1600,1600);
    TLegend * leg = new TLegend(0.65,0.65,0.88,0.88);
    leg->SetBorderSize(0);
    leg->AddEntry(inv_mass_SM, "ML tagging SMtttt", "f");
    leg->AddEntry(inv_mass_SM_stand, "Stand. tagging SMtttt", "l");
    leg->AddEntry(inv_mass_Y0, "ML tagging y_{0}tt", "f");
    leg->AddEntry(inv_mass_SM_stand_clone, "Stand. tagging y_{0}tt", "l");
    leg->AddEntry((TObject*)0, TString::Format("Weight (y_{0}tt) = %.2f", weight), "");
    leg->AddEntry((TObject*)0, TString::Format("%s < #Delta R < %s", DRCut1.Data(), DRCut2.Data()), "");
    

    TText T; T.SetTextFont(42); T.SetTextAlign(21);
 //   cs->Divide(2,1);
    //cs->cd(1); hs_ml_det->Draw("hist"); T.DrawTextNDC(.55,.96,"ML tagging - detector level");     
    if (Combination.EqualTo("")&&CombinationPtcl.EqualTo("")){
        cs->cd(); 
        hs_ml_det->SetMaximum(0.1);
        hs_ml_det->Draw("hist"); 
        inv_mass_SM_stand_clone->Draw("hist same");
        inv_mass_SM_stand->Draw("hist same");
        leg->Draw("same");
        cs2->cd(); 
        hs_ml_ptcl->SetMaximum(0.1);
        hs_ml_ptcl->Draw("hist"); //T.DrawTextNDC(.55,.96,"Particle level");
        ptcl_inv_mass_SM_stand_clone->Draw("hist same");
        ptcl_inv_mass_SM_stand->Draw("hist same");
        leg->Draw("same");
        cs->SaveAs(TString::Format("./todel/det_%s.pdf",inv_mass_SM_stand->GetName() ));//
        cs->SaveAs(TString::Format("./todel/det_%s.png",inv_mass_SM_stand->GetName() ));//
        cs->SaveAs(TString::Format("./invmass/det_%s.pdf",inv_mass_SM_stand->GetName() ));//
        cs->SaveAs(TString::Format("./invmass/det_%s.png",inv_mass_SM_stand->GetName() ));//
        cs2->SaveAs(TString::Format("./invmass/%s.pdf", ptcl_inv_mass_SM_stand->GetName() ));
        cs2->SaveAs(TString::Format("./invmass/%s.png", ptcl_inv_mass_SM_stand->GetName() ));
    } else if (Combination.EqualTo("")){
        cs2->cd(); 
        hs_ml_ptcl->SetMaximum(0.1);
        hs_ml_ptcl->Draw("hist"); //T.DrawTextNDC(.55,.96,"Particle level");
        ptcl_inv_mass_SM_stand_clone->Draw("hist same");
        ptcl_inv_mass_SM_stand->Draw("hist same");
        leg->Draw("same");
        cs2->SaveAs(TString::Format("./todel/%s.pdf", ptcl_inv_mass_SM_stand->GetName() ));
        cs2->SaveAs(TString::Format("./todel/%s.png", ptcl_inv_mass_SM_stand->GetName() ));
        cs2->SaveAs(TString::Format("./invmass/%s.pdf", ptcl_inv_mass_SM_stand->GetName() ));
        cs2->SaveAs(TString::Format("./invmass/%s.png", ptcl_inv_mass_SM_stand->GetName() ));
    } else if (CombinationPtcl.EqualTo("")){
        cs->cd(); 
        hs_ml_det->SetMaximum(0.1);
        hs_ml_det->Draw("hist"); 
        inv_mass_SM_stand_clone->Draw("hist same");
        inv_mass_SM_stand->Draw("hist same");
        leg->Draw("same");
        cs->SaveAs(TString::Format("./todel/det_%s.pdf",inv_mass_SM_stand->GetName() ));//
        cs->SaveAs(TString::Format("./todel/det_%s.png",inv_mass_SM_stand->GetName() ));//
        cs->SaveAs(TString::Format("./invmass/det_%s.pdf",inv_mass_SM_stand->GetName() ));//
        cs->SaveAs(TString::Format("./invmass/det_%s.png",inv_mass_SM_stand->GetName() ));//
    } else{
        cs->cd(); 
        hs_ml_det->SetMaximum(0.1);
        hs_ml_det->Draw("hist"); 
        inv_mass_SM_stand_clone->Draw("hist same");
        inv_mass_SM_stand->Draw("hist same");
        leg->Draw("same");
        cs2->cd(); 
        hs_ml_ptcl->SetMaximum(0.1);
        hs_ml_ptcl->Draw("hist"); //T.DrawTextNDC(.55,.96,"Particle level");
        ptcl_inv_mass_SM_stand_clone->Draw("hist same");
        ptcl_inv_mass_SM_stand->Draw("hist same");
        leg->Draw("same");
        cs->SaveAs(TString::Format( "./todel/det_%s.pdf",inv_mass_SM_stand->GetName() ));//
        cs->SaveAs(TString::Format( "./todel/det_%s.png",inv_mass_SM_stand->GetName() ));//
        cs->SaveAs(TString::Format( "./invmassDR/DR_%s_%s_det_%s.pdf",DRCut1.Data(), DRCut2.Data(), inv_mass_SM_stand->GetName() ));//
        cs->SaveAs(TString::Format( "./invmassDR/DR_%s_%s_det_%s.png",DRCut1.Data(), DRCut2.Data(), inv_mass_SM_stand->GetName() ));//
        cs2->SaveAs(TString::Format("./invmassDR/DR_%s_%s_%s.pdf",    DRCut1.Data(), DRCut2.Data(), ptcl_inv_mass_SM_stand->GetName() ));
        cs2->SaveAs(TString::Format("./invmassDR/DR_%s_%s_%s.png",    DRCut1.Data(), DRCut2.Data(), ptcl_inv_mass_SM_stand->GetName() ));
    }
     //cs->SaveAs("invmass_det.pdf");
    //cs->SaveAs("invmass_det.png");

    //cs->cd(4); hs_stand_ptcl->Draw("hist"); T.DrawTextNDC(.55,.96,"Standard tagging - detector level");
    //cs->cd(3); hs_stand_ptcl->Draw("hist same"); //T.DrawTextNDC(.55,.96,"Standard tagging - detector level");

    return 0;
}
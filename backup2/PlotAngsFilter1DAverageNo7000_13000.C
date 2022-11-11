double SeparationPower(TGraphAsymmErrors * a, TGraphAsymmErrors * b){
    int n = a->GetN();
    Double_t ax[n],ay[n];
    Double_t bx[n],by[n];
    double power = 0;

    
    double IntegralA = 0.;
    double IntegralB = 0.;
    

    for(Int_t i=0; i<n; i++) {
        a->GetPoint(i,ax[i],ay[i]); 
        b->GetPoint(i,bx[i],by[i]); 
        if (ay[i]<0) ay[i] = 0.;
        if (by[i]<0) by[i] = 0.;
        IntegralA+=ay[i];//*(a->GetErrorXlow(i)+a->GetErrorXhigh(i) );
        IntegralB+=by[i];//*(b->GetErrorXlow(i)+b->GetErrorXhigh(i) );
    }
    cout << IntegralA << endl;
    cout << IntegralB << endl;
    for(Int_t i=0; i<n; i++) {
        a->GetPoint(i,ax[i],ay[i]); 
        b->GetPoint(i,bx[i],by[i]); 
        ay[i]/=IntegralA;
        by[i]/=IntegralB;
        if (ay[i]<0) ay[i] = 0.;
        if (by[i]<0) by[i] = 0.;
        //if (TMath::Abs(ay[i]-by[i]) < 0.01) continue;
        if ( isnan(TMath::Power(ay[i]-by[i],2.)/( ay[i]+by[i] )  ) ) continue;
        power+=0.5*TMath::Power(ay[i]-by[i],2.)/( ay[i]+by[i] );
    //cout<<i<<"th element of X array: "<<ax[i]<<endl;
    //cout<<i<<"th element of Y array: "<<ay[i]<<endl;
}

return power;
}

TGraphAsymmErrors * GetAverage2(vector<TH1F*> hists){
    TH1F * h = (TH1F*)hists[0]->Clone(TString::Format("%s_average", hists[0]->GetName()));
    h->Reset();
    TH1F * h_low = (TH1F*)hists[0]->Clone(TString::Format("%s_low_average", hists[0]->GetName()));
    h_low->Reset();
    double Average;
    double max;
    double min;
    vector<double> maxenv;
    vector<double> minenv;

    const Int_t n = h->GetXaxis()->GetNbins();
   Double_t x[n]   ;
   Double_t y[n]   ;
   Double_t exl[n] ;
   Double_t eyl[n] ;
   Double_t exh[n] ;
   Double_t eyh[n] ;
    for (size_t i = 1; i <= hists[0]->GetXaxis()->GetNbins(); i++)
    {
        maxenv.clear();
        minenv.clear();
        Average = 0.;
        for (size_t j = 0; j < hists.size(); j++)
        {
            Average+=hists[j]->GetBinContent(i);
            maxenv.push_back(hists[j]->GetBinContent(i));
            minenv.push_back(hists[j]->GetBinContent(i));
        }
        Average/=hists.size();
        h->SetBinContent(i,Average);
        h_low->SetBinContent(i,Average);
        max = *max_element(maxenv.begin(), maxenv.end());
        min = *min_element(minenv.begin(), minenv.end());

        //h->SetBinError(i, max);
        //h_low->SetBinError(i, min);
        eyh[i-1] = TMath::Abs(max - Average);
        eyl[i-1] = TMath::Abs(min - Average);
        
    }
   

   for (size_t i = 0; i < n; i++)
   {
      x[i] = h->GetBinCenter(i+1);
      y[i] = h->GetBinContent(i+1);
    exl[i] = h->GetBinWidth(i+1)/2.;//h->GetBinCenter(i+1) - h->GetBinLowEdge(i+1);
    //eyl[i] = h_low->GetBinError(i+1);
    exh[i] = h->GetBinWidth(i+1)/2.;
    //eyh[i] = h->GetBinError(i+1);
   }
   
   auto gr = new TGraphAsymmErrors(n,x,y,exl,exh,eyl,eyh);
   gr->SetName(TString::Format("g_%s",h->GetName())); 
   //gr->SetTitle("TGraphAsymmErrors Example");
   //gr->SetMarkerColor(4);
   //gr->SetMarkerStyle(21);
   //gr->Draw("ALP");
   return gr;
}


TGraphAsymmErrors * GetAverage(vector<TH1F*> hists){
    cout << "testinA" << endl;
    TH1F * h = (TH1F*)hists[0]->Clone(TString::Format("%s_average", hists[0]->GetName()));
    h->Reset();
    cout << "testinB" << endl;
    TH1F * h_low = (TH1F*)hists[0]->Clone(TString::Format("%s_low_average", hists[0]->GetName()));
    h_low->Reset();
    cout << "testin" << endl;
    double Average;
    double max;
    double min;
    vector<double> maxenv;
    vector<double> minenv;

    const Int_t n = h->GetXaxis()->GetNbins();
   Double_t x[n]   ;
   Double_t y[n]   ;
   Double_t exl[n] ;
   Double_t eyl[n] ;
   Double_t exh[n] ;
   Double_t eyh[n] ;
    for (size_t i = 1; i <= hists[0]->GetXaxis()->GetNbins(); i++)
    {
        maxenv.clear();
        minenv.clear();
        Average = 0.;
        for (size_t j = 0; j < hists.size(); j++)
        {
            Average+=hists[j]->GetBinContent(i);
            maxenv.push_back(hists[j]->GetBinContent(i) + hists[j]->GetBinError(i));
            minenv.push_back(hists[j]->GetBinContent(i) - hists[j]->GetBinError(i));
        }
        Average/=hists.size();
        h->SetBinContent(i,Average);
        h_low->SetBinContent(i,Average);
        max = *max_element(maxenv.begin(), maxenv.end());
        min = *min_element(minenv.begin(), minenv.end());

        //h->SetBinError(i, max);
        //h_low->SetBinError(i, min);
        eyh[i-1] = TMath::Abs(max - Average);
        eyl[i-1] = TMath::Abs(min - Average);
        
    }
   

   for (size_t i = 0; i < n; i++)
   {
      x[i] = h->GetBinCenter(i+1);
      y[i] = h->GetBinContent(i+1);
    exl[i] = h->GetBinWidth(i+1)/2.;//h->GetBinCenter(i+1) - h->GetBinLowEdge(i+1);
    //eyl[i] = h_low->GetBinError(i+1);
    exh[i] = h->GetBinWidth(i+1)/2.;
    //eyh[i] = h->GetBinError(i+1);
   }
   
   auto gr = new TGraphAsymmErrors(n,x,y,exl,exh,eyl,eyh);
   gr->SetName(TString::Format("g_%s",h->GetName())); 
   //gr->SetTitle("TGraphAsymmErrors Example");
   //gr->SetMarkerColor(4);
   //gr->SetMarkerStyle(21);
   //gr->Draw("ALP");
   return gr;
}

TH1F * FilterStack(THStack * st){
    TH1F * h;
    TH1F * h2;
    TH1F * htemp;
    TH1F * htemp2;
    TString s_htemp;
    TString s_htemp2;
    double CutEntries = 0   ;
    bool first = true;
    TString temp = st->GetTitle();
////    cout << "Working on " << st->GetTitle() << endl;
    for (int i = 0; i < st->GetHists()->GetLast(); i++){
        htemp = (TH1F*)st->GetHists()->At(i);
        htemp2 = (TH1F*)st->GetHists()->At(i+1);
        s_htemp = htemp->GetName();
        s_htemp2 = htemp2->GetName();
        s_htemp.ReplaceAll("h_", "hB_");

        if ((s_htemp.EqualTo(s_htemp2)) && (htemp->GetEntries() > CutEntries) && (htemp2->GetEntries() > CutEntries) ){
            if (first){
                h = (TH1F*)htemp->Clone(TString::Format("%s_cut", st->GetName()));
                h2 = (TH1F*)htemp2->Clone(TString::Format("%s_cut2", st->GetName()));
                //if (temp.Contains("MPI")){
                    //h->Scale(1./h->GetEntries());
                    //htemp2->Scale(1./htemp2->GetEntries());
 ////                                   cout << "Found first pair " << htemp->GetName() << " " << htemp->Integral() << " --- " << htemp2->GetName() << " " << htemp2->Integral() <<  ", diff = " << htemp->Integral() - htemp2->Integral() << endl;
                //}
                ////h->Add(htemp2);
                //cout << "Found first pair " << htemp->GetName() << " " << htemp->Integral() << " --- " << htemp2->GetName() << " " << htemp2->Integral() <<  ", diff = " << htemp->Integral() - htemp2->Integral() << endl;
                i++;
                first = false;
            } else{
                //cout << "Found pair " << htemp->GetName() << " " << htemp->Integral() << " --- " << htemp2->GetName() << " " << htemp2->Integral() << ", diff = " << htemp->Integral() - htemp2->Integral() << endl;
                //if (temp.Contains("MPI")){
                    //htemp->Scale( 1./htemp->GetEntries());
                    //htemp2->Scale(1./htemp2->GetEntries());
 ////                   cout << "Found pair " << htemp->GetName() << " " << htemp->Integral() << " --- " << htemp2->GetName() << " " << htemp2->Integral() << ", diff = " << htemp->Integral() - htemp2->Integral() << endl;
                //}
                h->Add(htemp);
                h2->Add(htemp2);
                i++;
            }
            
        }
    }
    //h->SetName(st->GetName());
    //for (int i = 0; i <= st->GetHists()->GetLast(); i++){
    //    if (i==0) {htemp = (TH1F*)st->GetHists()->At(i);}else{
    //        htemp->Add((TH1F*)st->GetHists()->At(i));
    //    }
    //    
    //}
    h->Scale(1./h->GetEntries());
    h2->Scale(1./h2->GetEntries());
    h->Add(h2);

    h->SetTitle(st->GetTitle());
    return h;
}

TString GetAngName(TString a){
    if (a.Contains("Mult") ) return "#lambda^{0}_{0}";
    if (a.Contains("Lha")  ) return "#lambda^{1}_{0.5}";
    if (a.Contains("Wid")  ) return "#lambda^{1}_{1}";
    if (a.Contains("Mass") ) return "#lambda^{1}_{2}";
    if (a.Contains("Pt")   ) return "#lambda^{2}_{0}";
    return "";
}

TString GetAngR(TString a){
    if (a.Contains("FastJets02")) return "0.2";
    if (a.Contains("FastJets04")) return "0.4";
    if (a.Contains("FastJets06")) return "0.6";
    if (a.Contains("FastJets08")) return "0.8";
    if (a.Contains("FastJets10")) return "1.0";
    return "";
}


double GetInt(TH1F* h){
    double integral;
    for (int i = 1; i<=h->GetXaxis()->GetNbins(); i++){
        ////if (h->GetBinContent(i)>=0){
            integral+=TMath::Abs(h->GetBinContent(i));
        ////}
        
    }
return integral;
//return 1.;
}

double GetMax(vector<TH1F*> h, vector<TH1F*> h2){
    vector<double> maxs;
    for (int i = 0;i<h.size();i++){
        h[i] ->Scale(1./GetInt(h[i]));
        h2[i]->Scale(1./GetInt(h2[i]));
        //maxs.push_back(h[i] ->GetMaximum());
        //maxs.push_back(h2[i]->GetMaximum());
for (size_t j = 0; j < h[i]->GetXaxis()->GetNbins(); j++)
        {
            maxs.push_back(h[i]->GetBinContent(j)+ h[i]->GetBinError(j));
            maxs.push_back(h2[i]->GetBinContent(j)+ h2[i]->GetBinError(j));
        }
    }
    double max = *max_element(maxs.begin(), maxs.end());
    return max;
}

int PlotAngsFilter1DAverageNo7000_13000(int Pythia = 0, TString QPar = "50"){

std::map<TString, TFile*> nominal;
std::map<TString, TFile*> nominalNoMPINoISR;

TString Path = TString::Format("/media/petr/DATADRIVE1/Users/petrb/Documents/result_pt_mean_Q%s/",QPar.Data());

if (Pythia == 1){
    nominalNoMPINoISR["2360_13000"] = new TFile(TString::Format("%sqg_angs_noMPI_noISR_2360_13000_pythia.root", Path.Data() ) ,"read");
    nominalNoMPINoISR["2360_7000"] = new TFile(TString::Format("%sqg_angs_noMPI_noISR_2360_7000_pythia.root", Path.Data() ) ,"read");
    nominalNoMPINoISR["7000_13000"] = new TFile(TString::Format("%sqg_angs_noMPI_noISR_7000_13000_pythia.root", Path.Data() ) ,"read");
    nominalNoMPINoISR["900_13000"] = new TFile(TString::Format("%sqg_angs_noMPI_noISR_900_13000_pythia.root", Path.Data() ) ,"read");
    nominalNoMPINoISR["900_2360"] = new TFile(TString::Format("%sqg_angs_noMPI_noISR_900_2360_pythia.root", Path.Data() ) ,"read");
    nominalNoMPINoISR["900_7000"] = new TFile(TString::Format("%sqg_angs_noMPI_noISR_900_7000_pythia.root", Path.Data() ) ,"read");
    nominal["2360_13000"] = new TFile(TString::Format("%sqg_angs_2360_13000_pythia.root", Path.Data() ) ,"read");
    nominal["2360_7000"]  = new TFile(TString::Format("%sqg_angs_2360_7000_pythia.root", Path.Data() ) ,"read");
    nominal["7000_13000"] = new TFile(TString::Format("%sqg_angs_7000_13000_pythia.root", Path.Data() ) ,"read");
    nominal["900_13000"]  = new TFile(TString::Format("%sqg_angs_900_13000_pythia.root", Path.Data() ) ,"read");
    nominal["900_2360"]   = new TFile(TString::Format("%sqg_angs_900_2360_pythia.root", Path.Data() ) ,"read");
    nominal["900_7000"]   = new TFile(TString::Format("%sqg_angs_900_7000_pythia.root", Path.Data() ) ,"read");
}else{
nominalNoMPINoISR["2360_13000"] = new TFile(TString::Format("%sqg_angs_noMPI_noISR_2360_13000.root", Path.Data() ) ,"read");
nominalNoMPINoISR["2360_7000"] = new TFile(TString::Format("%sqg_angs_noMPI_noISR_2360_7000.root", Path.Data() ) ,"read");
nominalNoMPINoISR["7000_13000"] = new TFile(TString::Format("%sqg_angs_noMPI_noISR_7000_13000.root", Path.Data() ) ,"read");
nominalNoMPINoISR["900_13000"] = new TFile(TString::Format("%sqg_angs_noMPI_noISR_900_13000.root", Path.Data() ) ,"read");
nominalNoMPINoISR["900_2360"] = new TFile(TString::Format("%sqg_angs_noMPI_noISR_900_2360.root", Path.Data() ) ,"read");
nominalNoMPINoISR["900_7000"] = new TFile(TString::Format("%sqg_angs_noMPI_noISR_900_7000.root", Path.Data() ) ,"read");
nominal["2360_13000"] = new TFile(TString::Format("%sqg_angs_2360_13000.root", Path.Data() ) ,"read");
nominal["2360_7000"]  = new TFile(TString::Format("%sqg_angs_2360_7000.root", Path.Data() ) ,"read");
nominal["7000_13000"] = new TFile(TString::Format("%sqg_angs_7000_13000.root", Path.Data() ) ,"read");
nominal["900_13000"]  = new TFile(TString::Format("%sqg_angs_900_13000.root", Path.Data() ) ,"read");
nominal["900_2360"]   = new TFile(TString::Format("%sqg_angs_900_2360.root", Path.Data() ) ,"read");
nominal["900_7000"]   = new TFile(TString::Format("%sqg_angs_900_7000.root", Path.Data() ) ,"read");
}

vector<TString> Energies;

Energies.push_back("2360_13000");
Energies.push_back("2360_7000");
//Energies.push_back("7000_13000");
Energies.push_back("900_13000");
Energies.push_back("900_2360");
Energies.push_back("900_7000");

    vector<TString> Radii;
    vector<TString> Lambdas;
    vector<TString> Q;

    Q.push_back(QPar.Data());
    //Q.push_back("50");
    //Q.push_back("100");
    //Q.push_back("200");
    //Q.push_back("400");
    //Q.push_back("800");

    Radii.push_back("02");
    Radii.push_back("04");
    Radii.push_back("06");
    Radii.push_back("08");
    Radii.push_back("10");

    Lambdas.push_back("Mult");
    Lambdas.push_back("Pt");
    Lambdas.push_back("Lha");
    Lambdas.push_back("Width");
    Lambdas.push_back("Mass");

    vector<TString> quark_JetAng;
    vector<TString> gluon_JetAng;

    vector<TString> mmdt_quark_JetAng;
    vector<TString> mmdt_gluon_JetAng;

    for (int i = 0; i < Radii.size();i++){
        for (int j = 0; j < Lambdas.size();j++){
            for (int k = 0; k < Q.size();k++){
             quark_JetAng.push_back( TString::Format("quark_clone_h_no_cut_FastJets%s%sLam%s", Radii[i].Data(), Lambdas[j].Data(), Q[k].Data() ) );
             gluon_JetAng.push_back( TString::Format("gluon_h_no_cut_FastJets%s%sLam%s", Radii[i].Data(), Lambdas[j].Data(), Q[k].Data() ) );
             mmdt_quark_JetAng.push_back( TString::Format("quark_clone_h_no_cut_mmdt_FastJets%s%sLam%s", Radii[i].Data(), Lambdas[j].Data(), Q[k].Data() ) );
             mmdt_gluon_JetAng.push_back( TString::Format("gluon_h_no_cut_mmdt_FastJets%s%sLam%s", Radii[i].Data(), Lambdas[j].Data(), Q[k].Data() ) );

            }
        }
    }

    TH1F * hq_2360_13000;
    TH1F * hq_2360_7000;
    TH1F * hq_7000_13000;
    TH1F * hq_900_13000;
    TH1F * hq_900_2360;
    TH1F * hq_900_7000;
    TH1F * hg_2360_13000;
    TH1F * hg_2360_7000;
    TH1F * hg_7000_13000;
    TH1F * hg_900_13000;
    TH1F * hg_900_2360;
    TH1F * hg_900_7000;
    TH1F * hq_mmdt_2360_13000;
    TH1F * hq_mmdt_2360_7000;
    TH1F * hq_mmdt_7000_13000;
    TH1F * hq_mmdt_900_13000;
    TH1F * hq_mmdt_900_2360;
    TH1F * hq_mmdt_900_7000;
    TH1F * hg_mmdt_2360_13000;
    TH1F * hg_mmdt_2360_7000;
    TH1F * hg_mmdt_7000_13000;
    TH1F * hg_mmdt_900_13000;
    TH1F * hg_mmdt_900_2360;
    TH1F * hg_mmdt_900_7000;

    TH1F * NoMPI_hq_2360_13000;
    TH1F * NoMPI_hq_2360_7000;
    TH1F * NoMPI_hq_7000_13000;
    TH1F * NoMPI_hq_900_13000;
    TH1F * NoMPI_hq_900_2360;
    TH1F * NoMPI_hq_900_7000;
    TH1F * NoMPI_hg_2360_13000;
    TH1F * NoMPI_hg_2360_7000;
    TH1F * NoMPI_hg_7000_13000;
    TH1F * NoMPI_hg_900_13000;
    TH1F * NoMPI_hg_900_2360;
    TH1F * NoMPI_hg_900_7000;
    TH1F * NoMPI_hq_mmdt_2360_13000;
    TH1F * NoMPI_hq_mmdt_2360_7000;
    TH1F * NoMPI_hq_mmdt_7000_13000;
    TH1F * NoMPI_hq_mmdt_900_13000;
    TH1F * NoMPI_hq_mmdt_900_2360;
    TH1F * NoMPI_hq_mmdt_900_7000;
    TH1F * NoMPI_hg_mmdt_2360_13000;
    TH1F * NoMPI_hg_mmdt_2360_7000;
    TH1F * NoMPI_hg_mmdt_7000_13000;
    TH1F * NoMPI_hg_mmdt_900_13000;
    TH1F * NoMPI_hg_mmdt_900_2360;
    TH1F * NoMPI_hg_mmdt_900_7000;

    TH1F * hq;
    TH1F * hg;
    TH1F * mmdt_hq;
    TH1F * mmdt_hg;
    TH1F * No_MPI_hq;
    TH1F * No_MPI_hg;
    TH1F * No_MPI_mmdt_hq;
    TH1F * No_MPI_mmdt_hg;

    THStack * st_hq;
    THStack * st_hg;
    THStack * st_mmdt_hq;
    THStack * st_mmdt_hg;
    THStack * st_No_MPI_hq;
    THStack * st_No_MPI_hg;
    THStack * st_No_MPI_mmdt_hq;
    THStack * st_No_MPI_mmdt_hg;

    vector<TH1F*> quark;
    vector<TH1F*> gluon;
    vector<TH1F*> mmdt_quark;
    vector<TH1F*> mmdt_gluon;

    vector<TH1F*> No_MPI_quark;
    vector<TH1F*> No_MPI_gluon;
    vector<TH1F*> No_MPI_mmdt_quark;
    vector<TH1F*> No_MPI_mmdt_gluon;

    vector<vector<TH1F*>> vec_quark;
    vector<vector<TH1F*>> vec_gluon;
    vector<vector<TH1F*>> vec_mmdt_quark;
    vector<vector<TH1F*>> vec_mmdt_gluon;

    vector<vector<TH1F*>> vec_No_MPI_quark;
    vector<vector<TH1F*>> vec_No_MPI_gluon;
    vector<vector<TH1F*>> vec_No_MPI_mmdt_quark;
    vector<vector<TH1F*>> vec_No_MPI_mmdt_gluon;

    vector<TH1F*> all;

    for (int i = 0; i < quark_JetAng.size();i++){
    //for (int i = 0; i < 1;i++){
        for (int j = 0; j < Energies.size();j++){
                        //cout << Energies[j].Data() << " " << gluon_JetAng[i] << endl;
             hq=(TH1F*)nominal[Energies[j].Data()]->Get(quark_JetAng[i]);
             hq->SetName(TString::Format("%s_%s", Energies[j].Data(), hq->GetName()));
             hq->SetTitle(TString::Format("%s_%s", Energies[j].Data(), hq->GetTitle()));
 
 
             hg=(TH1F*)nominal[Energies[j].Data()]->Get(gluon_JetAng[i]);
             hg->SetName(TString::Format("%s_%s", Energies[j].Data(), hg->GetName()));
             hg->SetTitle(TString::Format("%s_%s", Energies[j].Data(), hg->GetTitle()));
 
             mmdt_hq=(TH1F*)nominal[Energies[j].Data()]->Get(mmdt_quark_JetAng[i]);
             mmdt_hq->SetName(TString::Format("%s_%s", Energies[j].Data(), mmdt_hq->GetName()));
             mmdt_hq->SetTitle(TString::Format("%s_%s", Energies[j].Data(), mmdt_hq->GetTitle()));
 
             mmdt_hg=(TH1F*)nominal[Energies[j].Data()]->Get(mmdt_gluon_JetAng[i]);
             mmdt_hg->SetName(TString::Format("%s_%s", Energies[j].Data(), mmdt_hg->GetName()));
             mmdt_hg->SetTitle(TString::Format("%s_%s", Energies[j].Data(), mmdt_hg->GetTitle()));


            //
             No_MPI_hq=(TH1F*)nominalNoMPINoISR[Energies[j].Data()]->Get(quark_JetAng[i]);
             No_MPI_hq->SetName(TString::Format("%s_%s_NoMPI_NoISR", Energies[j].Data(), No_MPI_hq->GetName()));
             No_MPI_hq->SetTitle(TString::Format("%s_%s_NoMPI_NoISR", Energies[j].Data(), No_MPI_hq->GetTitle()));
 
             No_MPI_hg=(TH1F*)nominalNoMPINoISR[Energies[j].Data()]->Get(gluon_JetAng[i]);
             No_MPI_hg->SetName(TString::Format("%s_%s_NoMPI_NoISR", Energies[j].Data(), No_MPI_hg->GetName()));
             No_MPI_hg->SetTitle(TString::Format("%s_%s_NoMPI_NoISR", Energies[j].Data(), No_MPI_hg->GetTitle()));
 
             No_MPI_mmdt_hq=(TH1F*)nominalNoMPINoISR[Energies[j].Data()]->Get(mmdt_quark_JetAng[i]);
             No_MPI_mmdt_hq->SetName(TString::Format("%s_%s_NoMPI_NoISR", Energies[j].Data(), No_MPI_mmdt_hq->GetName()));
             No_MPI_mmdt_hq->SetTitle(TString::Format("%s_%s_NoMPI_NoISR", Energies[j].Data(), No_MPI_mmdt_hq->GetTitle()));
 
             No_MPI_mmdt_hg=(TH1F*)nominalNoMPINoISR[Energies[j].Data()]->Get(mmdt_gluon_JetAng[i]);
             No_MPI_mmdt_hg->SetName(TString::Format("%s_%s_NoMPI_NoISR", Energies[j].Data(), No_MPI_mmdt_hg->GetName()));
             No_MPI_mmdt_hg->SetTitle(TString::Format("%s_%s_NoMPI_NoISR", Energies[j].Data(), No_MPI_mmdt_hg->GetTitle()));


            
            quark.push_back(hq);
            gluon.push_back(hg);
            mmdt_quark.push_back(mmdt_hq);
            mmdt_gluon.push_back(mmdt_hg);
            No_MPI_quark.push_back(No_MPI_hq);
            No_MPI_gluon.push_back(No_MPI_hg);
            No_MPI_mmdt_quark.push_back(No_MPI_mmdt_hq);
            No_MPI_mmdt_gluon.push_back(No_MPI_mmdt_hg);

            all.push_back(hq);
            all.push_back(hg);
            all.push_back(mmdt_hq);
            all.push_back(mmdt_hg);
            all.push_back(No_MPI_hq);
            all.push_back(No_MPI_hg);
            all.push_back(No_MPI_mmdt_hq);
            all.push_back(No_MPI_mmdt_hg);
    
        }

        vec_quark.push_back(quark);
        vec_gluon.push_back(gluon);
        vec_mmdt_quark.push_back(mmdt_quark);
        vec_mmdt_gluon.push_back(mmdt_gluon);
        vec_No_MPI_quark.push_back(No_MPI_quark);
        vec_No_MPI_gluon.push_back(No_MPI_gluon);
        vec_No_MPI_mmdt_quark.push_back(No_MPI_mmdt_quark);
        vec_No_MPI_mmdt_gluon.push_back(No_MPI_mmdt_gluon);
        quark.clear();
        gluon.clear();
        mmdt_quark.clear();
        mmdt_gluon.clear();
        No_MPI_quark.clear();
        No_MPI_gluon.clear();
        No_MPI_mmdt_quark.clear();
        No_MPI_mmdt_gluon.clear();
    }

    vector<TCanvas*> cans;
    vector<TCanvas*> cans2;
    TCanvas * cantemp;
    TCanvas * cantemp2;
    double max_q, max_g;
    double noMPI_max_q, noMPI_max_g;
    vector<double> min;
    TString CanName;
    TString CanName2;    
    TLegend * leg;
    TLegend * leg2;
    TString LegName;
    TString LegName2;    
    double maxq; 
    double maxg; 

    TFile * output = new TFile("/media/petr/DATADRIVE1/Users/petrb/Documents/angs_herwig1D_average_no7000_13000.root", "recreate");
    output->cd();

    vector<TH1F*> hists_quark;
    vector<TH1F*> hists_gluon;
    vector<TH1F*> hists_No_MPI_quark;
    vector<TH1F*> hists_No_MPI_gluon;
    
    TGraphAsymmErrors * average_gluon;
    TGraphAsymmErrors * average_quark;
    TGraphAsymmErrors * average_gluon2;
    TGraphAsymmErrors * average_quark2;

    TGraphAsymmErrors * average_No_MPI_gluon;
    TGraphAsymmErrors * average_No_MPI_quark;
    TGraphAsymmErrors * average_No_MPI_gluon2;
    TGraphAsymmErrors * average_No_MPI_quark2;
    double power;

    for (int i=0;i<vec_quark.size();i++){
        cantemp = new TCanvas(TString::Format("can_%s", vec_quark[i][0]->GetName()), TString::Format("can_%s", vec_quark[i][0]->GetName()), 0, 0, 1600,1000 );
        cans.push_back(cantemp);
        hists_quark.clear();
        hists_gluon.clear();
        hists_No_MPI_quark.clear();
        hists_No_MPI_gluon.clear();
        cans[i]->cd();
        TString AngName = GetAngName(vec_quark[i][0]->GetName());
        vec_quark[i][0]->GetXaxis()->SetTitle(AngName.Data());
        vec_quark[i][0]->GetYaxis()->SetTitle("Events / Norm.");
        vec_gluon[i][0]->GetXaxis()->SetTitle(AngName.Data());
        vec_gluon[i][0]->GetYaxis()->SetTitle("Events / Norm.");
        maxq = GetMax(vec_quark[i], vec_No_MPI_quark[i]);
        maxg = GetMax(vec_gluon[i], vec_No_MPI_gluon[i]);
        for (int j=0;j<vec_quark[i].size();j++){
            //leg->AddEntry(vec_quark[i][j], TString::Format("%s", vec_quark[i][j]->GetName() ));
            //leg->AddEntry(vec_No_MPI_quark[i][j], TString::Format("%s", vec_No_MPI_quark[i][j]->GetName() ));
            //leg->AddEntry(vec_gluon[i][j], TString::Format("%s", vec_gluon[i][j]->GetName() ));
            //leg->AddEntry(vec_No_MPI_gluon[i][j], TString::Format("%s", vec_No_MPI_gluon[i][j]->GetName() ));
            vec_quark[i][j]->SetLineColor(kMagenta -j);
            vec_gluon[i][j]->SetLineColor(kAzure-j);
            vec_quark[i][j]->SetLineStyle(j+1);
            vec_gluon[i][j]->SetLineStyle(j+1);
            vec_quark[i][j]->SetMarkerSize(0);
            vec_gluon[i][j]->SetMarkerSize(0);
            vec_quark[i][j]->SetLineWidth(2);
            vec_gluon[i][j]->SetLineWidth(2);

            vec_No_MPI_quark[i][j]->SetMarkerColor(kMagenta -j);
            vec_No_MPI_gluon[i][j]->SetMarkerColor(kAzure-j);
            vec_No_MPI_quark[i][j]->SetMarkerStyle(20);
            vec_No_MPI_gluon[i][j]->SetMarkerStyle(20);
            vec_No_MPI_quark[i][j]->SetLineWidth(0);
            vec_No_MPI_gluon[i][j]->SetLineWidth(0);
            vec_No_MPI_quark[i][j]->SetLineStyle(2);
            vec_No_MPI_gluon[i][j]->SetLineStyle(2);
            // if (j==0){
                // cans[i]->cd();
                // vec_quark[i][0]->Scale(1./GetInt(vec_quark[i][0]));
                // max_q = vec_quark[i][0]->GetMaximum();
                // vec_gluon[i][0]->Scale(1./GetInt(vec_gluon[i][0]));
                // max_g = vec_gluon[i][0]->GetMaximum();
// 
                // vec_No_MPI_quark[i][0]->Scale(1./GetInt(vec_No_MPI_quark[i][0]));
                // noMPI_max_q = vec_No_MPI_quark[i][0]->GetMaximum();
                // vec_No_MPI_gluon[i][0]->Scale(1./GetInt(vec_No_MPI_gluon[i][0]));
                // noMPI_max_g = vec_No_MPI_gluon[i][0]->GetMaximum();
                // if (max_q > max_g){
                    // vec_quark[i][0]->SetMaximum(1.5*vec_quark[i][0]->GetMaximum());
                    // vec_quark[i][0]->Draw("hist e1");
                    // vec_gluon[i][0]->Draw("hist e1 same");
                    // vec_No_MPI_quark[i][0]->Draw("p same");
                    // vec_No_MPI_gluon[i][0]->Draw("p same");
                // }else{
                    // vec_gluon[i][0]->SetMaximum(1.5*vec_gluon[i][0]->GetMaximum());
                    // vec_gluon[i][0]->Draw("hist e1");
                    // vec_quark[i][0]->Draw("hist e1 same");
                    // vec_No_MPI_quark[i][0]->Draw("p same");
                    // vec_No_MPI_gluon[i][0]->Draw("p same");
                // }
            //}else{
                cans[i]->cd();
                gPad->SetLeftMargin(0.15);
                gStyle->SetOptStat(0);
                vec_quark[i][j]->Scale(maxq/vec_quark[i][j]->GetMaximum() );
                if (maxq > maxg) vec_quark[i][j]->SetMaximum(1.5*maxq);
                if (maxq <= maxg) vec_quark[i][j]->SetMaximum(1.5*maxg);
                vec_quark[i][j]->SetTitle("");
                hists_quark.push_back(vec_quark[i][j]);
                vec_quark[i][j]->SetLineColor(kWhite);
                vec_quark[i][j]->Draw("hist e1 same");
                vec_quark[i][j]->Write();
                vec_gluon[i][j]->Scale(maxg/vec_gluon[i][j]->GetMaximum() );
                hists_gluon.push_back(vec_gluon[i][j]);
                vec_gluon[i][j]->SetLineColor(kWhite);
                vec_gluon[i][j]->Draw("hist e1 same");
                vec_gluon[i][j]->Write();

                

                vec_No_MPI_quark[i][j]->Scale(maxq/vec_No_MPI_quark[i][j]->GetMaximum() );
                //vec_No_MPI_quark[i][j]->SetLineColor(0);
                //vec_No_MPI_quark[i][j]->Draw("p same");
                hists_No_MPI_quark.push_back(vec_No_MPI_quark[i][j]);
                vec_No_MPI_quark[i][j]->Write();
                vec_No_MPI_gluon[i][j]->Scale(maxg/vec_No_MPI_gluon[i][j]->GetMaximum() );
                //vec_No_MPI_quark[i][j]->SetLineColor(0);
                //vec_No_MPI_gluon[i][j]->Draw("p same");
                hists_No_MPI_gluon.push_back(vec_No_MPI_gluon[i][j]);
                vec_No_MPI_gluon[i][j]->Write();
                //cout << "quark Chi2 " << vec_quark[i][j]->GetName() << vec_quark[i][j]->Chi2Test(vec_No_MPI_quark[i][j], "CHI2/NDF") << endl;
                //cout << "gluon Chi2 " << vec_gluon[i][j]->GetName() << vec_gluon[i][j]->Chi2Test(vec_No_MPI_gluon[i][j], "CHI2/NDF") << endl;
                //cout << "Delta      " << vec_quark[i][j]->GetName() << vec_quark[i][j]->Chi2Test(vec_No_MPI_quark[i][j], "CHI2/NDF") << endl;
            //}

            min.push_back(vec_quark[i][j]->GetBinContent(vec_quark[i][j]->GetMinimumBin()) - vec_quark[i][j]->GetBinError(vec_quark[i][j]->GetMinimumBin()) ); //here to
            min.push_back(vec_gluon[i][j]->GetBinContent(vec_gluon[i][j]->GetMinimumBin()) - vec_gluon[i][j]->GetBinError(vec_gluon[i][j]->GetMinimumBin()) ); //here to
            min.push_back(vec_No_MPI_quark[i][j]->GetBinContent(vec_No_MPI_quark[i][j]->GetMinimumBin()) - vec_No_MPI_quark[i][j]->GetBinError(vec_No_MPI_quark[i][j]->GetMinimumBin()) );
            min.push_back(vec_No_MPI_gluon[i][j]->GetBinContent(vec_No_MPI_gluon[i][j]->GetMinimumBin()) - vec_No_MPI_gluon[i][j]->GetBinError(vec_No_MPI_gluon[i][j]->GetMinimumBin()) );

        } 

        average_quark = GetAverage(hists_quark);
        average_gluon = GetAverage(hists_gluon);
        average_quark2 = GetAverage2(hists_quark);
        average_gluon2 = GetAverage2(hists_gluon);
        average_gluon->SetLineColor(kBlue);
        average_quark->SetLineColor(kRed);
        average_gluon2->SetLineColor(kBlue);
        average_quark2->SetLineColor(kRed);
cout << "test1" << endl;
        average_No_MPI_quark = GetAverage(hists_No_MPI_quark);
        cout << "test2" << endl;
        average_No_MPI_gluon = GetAverage(hists_No_MPI_gluon);
        average_No_MPI_quark2 = GetAverage2(hists_No_MPI_quark);
        average_No_MPI_gluon2 = GetAverage2(hists_No_MPI_gluon);
        
        average_No_MPI_gluon->SetLineColor(kAzure + 10 );
        average_No_MPI_quark->SetLineColor(kMagenta);
        average_No_MPI_gluon2->SetLineColor(kAzure + 10 );
        average_No_MPI_quark2->SetLineColor(kMagenta);

    
        vec_quark[i][0]->SetMinimum(*std::min_element(std::begin(min), std::end(min))*1.2)   ;
        vec_gluon[i][0]->SetMinimum(*std::min_element(std::begin(min), std::end(min))*1.2)   ;
        if (maxq > maxg)  vec_mmdt_quark[i][0]->SetMaximum(1.5*maxq);
        if (maxq <= maxg) vec_mmdt_gluon[i][0]->SetMaximum(1.5*maxg);
        
        average_No_MPI_quark->SetFillColor(kMagenta);
        average_No_MPI_gluon->SetFillColor(kAzure + 10 -2);
        average_No_MPI_quark2->SetFillColor(kMagenta-2);
        average_No_MPI_gluon2->SetFillColor(kAzure + 10 -4);
        average_No_MPI_quark->SetFillStyle(3004);
        average_No_MPI_gluon->SetFillStyle(3004);
        average_No_MPI_quark2->SetFillStyle(3004);
        average_No_MPI_gluon2->SetFillStyle(3004);
        //average_No_MPI_quark->Draw("C2 same");// tyto jsou filly
        //average_No_MPI_gluon->Draw("2C same");// tyto jsou filly
        //average_No_MPI_quark2->Draw("2C same");
        //average_No_MPI_quark2->Draw("p same");
        //average_No_MPI_gluon2->Draw("2C same");
        //average_No_MPI_gluon2->Draw("p same");

        average_No_MPI_quark2->Draw("C2 same");
        average_No_MPI_quark2->Draw("2C same");
        average_No_MPI_gluon2->Draw("C2 same");
        average_No_MPI_gluon2->Draw("2C same");
        average_No_MPI_quark->Draw("p same");// tyto jsou filly
        average_No_MPI_gluon->Draw("p same");// tyto jsou filly

        average_quark->SetFillColor(kRed);
        average_gluon->SetFillColor(kBlue);
        average_quark2->SetFillColor(kRed);
        average_gluon2->SetFillColor(kBlue);
        average_quark->SetFillStyle(3005);
        average_gluon->SetFillStyle(3005);
        average_quark2->SetFillStyle(3005);
        average_gluon2->SetFillStyle(3005);
        //average_quark->Draw("C2 same");
        //average_gluon->Draw("2C same");
        //average_quark2->Draw("2C same");
        //average_quark2->Draw("p same");
        //average_gluon2->Draw("2C same");
        //average_gluon2->Draw("p same");

        average_quark2->Draw("C2 same");
        average_quark2->Draw("2C same");
        average_gluon2->Draw("C2 same");
        average_gluon2->Draw("2C same");
        average_quark->Draw("p same");// tyto jsou filly
        average_gluon->Draw("p same");// tyto jsou filly

        
        gPad->Modified();
        gPad->Update();
        leg = new TLegend(0.55,0.5,0.86,0.86);
        leg->SetBorderSize(0);
        leg->SetFillStyle(0);
        leg->SetTextSize(0.025);
        leg->AddEntry(average_quark, "Average of quark ang.");
        //leg->AddEntry(average_quark, "Average of quark ang. with unc.");
        leg->AddEntry(average_gluon, "Average of gluon ang.");
        //leg->AddEntry(average_gluon, "Average of gluon ang. with unc.");
        leg->AddEntry(average_No_MPI_quark, "Average of quark ang. No MPI No ISR");
        leg->AddEntry(average_No_MPI_gluon, "Average of gluon ang. No MPI No ISR");
        power = SeparationPower(average_gluon, average_quark);
        leg->AddEntry((TObject*)0, TString::Format("#Delta = %0.2f", power ), "");
        leg->AddEntry((TObject*)0, TString::Format("#Delta quark to no MPI = %0.4f", SeparationPower(average_quark, average_No_MPI_quark)), "");
        leg->AddEntry((TObject*)0, TString::Format("#Delta gluon to no MPI = %0.4f", SeparationPower(average_gluon, average_No_MPI_gluon)), "");
        //leg->AddEntry((TObject*)0, TString::Format("#Delta_{comb.} = %0.2f", power / ( SeparationPower(average_quark, average_No_MPI_quark) + SeparationPower(average_gluon, average_No_MPI_gluon) ) ) , "");
        leg->AddEntry((TObject*)0, TString::Format("Jet R = %s", GetAngR(vec_quark[i][0]->GetName()).Data() ), "");
        leg->AddEntry((TObject*)0, TString::Format("Angularity %s", GetAngName(vec_quark[i][0]->GetName()).Data() ), "");
        //leg->AddEntry((TObject*)0, "MMDT" , "");
        leg->AddEntry((TObject*)0, TString::Format("Q = %s GeV", QPar.Data() ), "");
        if (Pythia==1){
            leg->AddEntry((TObject*)0, "Pythia", "");
        }else{
            leg->AddEntry((TObject*)0, "Herwig", "");    
        }
        leg->AddEntry((TObject*)0, "" , "");
        leg->AddEntry((TObject*)0, TString::Format("#Delta_{comb.} = %0.2f", power / ( SeparationPower(average_quark, average_No_MPI_quark) + SeparationPower(average_gluon, average_No_MPI_gluon) ) ) , "");
        leg->Draw("same");
        min.clear();
        cans[i]->SetName(TString::Format("%s_%s_", ((TString)TString::Format("%0.f", power / ( SeparationPower(average_quark, average_No_MPI_quark) + SeparationPower(average_gluon, average_No_MPI_gluon) ) )).Data(), cans[i]->GetName() ));
        //mmdt
        cantemp2 = new TCanvas(TString::Format("can_%s", vec_mmdt_quark[i][0]->GetName()), TString::Format("can_%s", vec_mmdt_quark[i][0]->GetName()), 0, 0, 1600,1000 );
        cans2.push_back(cantemp2);
        cans2[i]->cd();
        gPad->SetLeftMargin(0.15);
        gStyle->SetOptStat(0);
        AngName = TString::Format("mmdt %s", AngName.Data());
        vec_mmdt_quark[i][0]->GetXaxis()->SetTitle(AngName.Data());
        vec_mmdt_quark[i][0]->GetYaxis()->SetTitle("Events / Norm.");
        vec_mmdt_gluon[i][0]->GetXaxis()->SetTitle(AngName.Data());
        vec_mmdt_gluon[i][0]->GetYaxis()->SetTitle("Events / Norm.");
        maxq = GetMax(vec_mmdt_quark[i], vec_No_MPI_mmdt_quark[i]);
        maxg = GetMax(vec_mmdt_gluon[i], vec_No_MPI_mmdt_gluon[i]);
        
        
        for (int j=0;j<vec_mmdt_quark[i].size();j++){
            vec_mmdt_quark[i][j]->SetLineColor(kMagenta -j);
            vec_mmdt_gluon[i][j]->SetLineColor(kAzure -j);
            vec_mmdt_quark[i][j]->SetLineStyle(j+1);
            vec_mmdt_gluon[i][j]->SetLineStyle(j+1);
            vec_mmdt_quark[i][j]->SetMarkerSize(0);
            vec_mmdt_gluon[i][j]->SetMarkerSize(0);
            vec_mmdt_quark[i][j]->SetLineWidth(2);
            vec_mmdt_gluon[i][j]->SetLineWidth(2);

            vec_No_MPI_mmdt_quark[i][j]->SetMarkerColor(kMagenta -j);
            vec_No_MPI_mmdt_gluon[i][j]->SetMarkerColor(kAzure -j);
            vec_No_MPI_mmdt_quark[i][j]->SetMarkerStyle(20);
            vec_No_MPI_mmdt_gluon[i][j]->SetMarkerStyle(20);
            vec_No_MPI_mmdt_quark[i][j]->SetLineWidth(0);
            vec_No_MPI_mmdt_gluon[i][j]->SetLineWidth(0);
            vec_No_MPI_mmdt_quark[i][j]->SetLineStyle(2);
            vec_No_MPI_mmdt_gluon[i][j]->SetLineStyle(2);
            // if (j==0){
                // cans2[i]->cd();
                // vec_mmdt_quark[i][0]->Scale(1./GetInt(vec_mmdt_quark[i][0]));
                // max_q = vec_mmdt_quark[i][0]->GetMaximum();
                // vec_mmdt_gluon[i][0]->Scale(1./GetInt(vec_mmdt_gluon[i][0]));
                // // max_g = vec_mmdt_gluon[i][0]->GetMaximum();

                // vec_No_MPI_mmdt_quark[i][0]->Scale(1./GetInt(vec_No_MPI_mmdt_quark[i][0]));
                // noMPI_max_q = vec_No_MPI_mmdt_quark[i][0]->GetMaximum();
                // vec_No_MPI_mmdt_gluon[i][0]->Scale(1./GetInt(vec_No_MPI_mmdt_gluon[i][0]));
                // noMPI_max_g = vec_No_MPI_mmdt_gluon[i][0]->GetMaximum();
                // if (max_q > max_g){
                    // vec_mmdt_quark[i][0]->SetMaximum(1.3*vec_mmdt_quark[i][0]->GetMaximum());
                    // vec_mmdt_quark[i][0]->Draw("hist e1");
                    // vec_mmdt_gluon[i][0]->Draw("hist e1 same");
                    // vec_No_MPI_mmdt_quark[i][0]->Draw("p same");
                    // vec_No_MPI_mmdt_gluon[i][0]->Draw("p same");
                // }else{
                    // vec_mmdt_gluon[i][0]->SetMaximum(1.3*vec_mmdt_gluon[i][0]->GetMaximum());
                    // vec_mmdt_gluon[i][0]->Draw("hist e1");
                    // vec_mmdt_quark[i][0]->Draw("hist e1 same");
                    // vec_No_MPI_mmdt_quark[i][0]->Draw("p same");
                    // vec_No_MPI_mmdt_gluon[i][0]->Draw("p same");
                // }
           // }else{
                vec_mmdt_quark[i][j]->Scale(maxq/vec_mmdt_quark[i][j]->GetMaximum() );
                if (maxq > maxg) vec_mmdt_quark[i][j]->SetMaximum(1.5*maxq);
                if (maxq <= maxg) vec_mmdt_quark[i][j]->SetMaximum(1.5*maxg);
                vec_mmdt_quark[i][j]->SetTitle("");
                vec_mmdt_quark[i][j]->Draw("hist e1 same");
                vec_mmdt_quark[i][j]->Write();
                vec_mmdt_gluon[i][j]->Scale(maxg/vec_mmdt_gluon[i][j]->GetMaximum() );
                vec_mmdt_gluon[i][j]->Draw("hist e1 same");
                vec_mmdt_gluon[i][j]->Write();

                vec_No_MPI_mmdt_quark[i][j]->Scale(maxq/vec_No_MPI_mmdt_quark[i][j]->GetMaximum() );
                //vec_No_MPI_mmdt_quark[i][j]->Draw("p same");
                vec_No_MPI_mmdt_quark[i][j]->Write();
                vec_No_MPI_mmdt_gluon[i][j]->Scale(maxg/vec_No_MPI_mmdt_gluon[i][j]->GetMaximum() );
                //vec_No_MPI_mmdt_gluon[i][j]->Draw("p same");
                vec_No_MPI_mmdt_gluon[i][j]->Write();
           // }

            min.push_back(vec_mmdt_quark[i][j]->GetMinimum());
            min.push_back(vec_mmdt_gluon[i][j]->GetMinimum());
            //min.push_back(vec_No_MPI_mmdt_quark[i][j]->GetMinimum());
            //min.push_back(vec_No_MPI_mmdt_gluon[i][j]->GetMinimum());

            min.push_back(vec_mmdt_quark[i][j]->GetBinContent(vec_mmdt_quark[i][j]->GetMinimumBin()) + vec_mmdt_quark[i][j]->GetBinError(vec_mmdt_quark[i][j]->GetMinimumBin()) ); //here to
            min.push_back(vec_mmdt_gluon[i][j]->GetBinContent(vec_mmdt_gluon[i][j]->GetMinimumBin()) + vec_mmdt_gluon[i][j]->GetBinError(vec_mmdt_gluon[i][j]->GetMinimumBin()) ); //here to
            //min.push_back(vec_No_MPI_mmdt_quark[i][j]->GetBinContent(vec_No_MPI_mmdt_quark[i][j]->GetMinimumBin()) + vec_No_MPI_mmdt_quark[i][j]->GetBinError(vec_No_MPI_mmdt_quark[i][j]->GetMinimumBin()) );
            //min.push_back(vec_No_MPI_mmdt_gluon[i][j]->GetBinContent(vec_No_MPI_mmdt_gluon[i][j]->GetMinimumBin()) + vec_No_MPI_mmdt_gluon[i][j]->GetBinError(vec_No_MPI_mmdt_gluon[i][j]->GetMinimumBin()) );

        
        } 
        vec_mmdt_quark[i][0]->SetMinimum(*std::min_element(std::begin(min), std::end(min))*2)   ;
        vec_mmdt_gluon[i][0]->SetMinimum(*std::min_element(std::begin(min), std::end(min))*2)   ;
        min.clear();
        leg2 = new TLegend(0.5,0.43,0.86,0.86);
        leg2->SetBorderSize(0);
        leg2->SetFillStyle(0);
        //leg2->SetTextSize(0.02);
        for (int j=0;j<vec_quark[i].size();j++){
            LegName = vec_quark[i][j]->GetName();
            LegName = LegName.ReplaceAll("_", " ");
            TObjArray *tx = LegName.Tokenize(" ");
            TString sleg20 = ((TObjString *)(tx->At(0)))->String();
            TString sleg21 = ((TObjString *)(tx->At(1)))->String();
            //TString sleg22 = ((TObjString *)(tx->At(2)))->String();
            TString sleg22 = "Quark";//
            TString sleg23 = ((TObjString *)(tx->At(3)))->String();
            leg2->AddEntry(vec_quark[i][j], TString::Format("%s ang. using %s-%s GeV",sleg22.Data(), sleg20.Data(), sleg21.Data() ));
        }
        for (int j=0;j<vec_quark[i].size();j++){
            LegName = vec_No_MPI_quark[i][j]->GetName();
            LegName = LegName.ReplaceAll("_", " ");
            TObjArray *tx = LegName.Tokenize(" ");
            TString sleg20 = ((TObjString *)(tx->At(0)))->String();
            TString sleg21 = ((TObjString *)(tx->At(1)))->String();
            //TString sleg22 = ((TObjString *)(tx->At(2)))->String();
            TString sleg22 = "Quark";//
            TString sleg23 = ((TObjString *)(tx->At(3)))->String();
            leg2->AddEntry(vec_No_MPI_quark[i][j], TString::Format("%s ang. (no MPI no ISR) using %s-%s GeV",sleg22.Data(), sleg20.Data(), sleg21.Data() ));
        }
        for (int j=0;j<vec_quark[i].size();j++){
            LegName = vec_gluon[i][j]->GetName();
            LegName = LegName.ReplaceAll("_", " ");
            TObjArray *tx = LegName.Tokenize(" ");
            TString sleg20 = ((TObjString *)(tx->At(0)))->String();
            TString sleg21 = ((TObjString *)(tx->At(1)))->String();
            //TString sleg22 = ((TObjString *)(tx->At(2)))->String();
            TString sleg22 = "Gluon";//
            TString sleg23 = ((TObjString *)(tx->At(3)))->String();
            leg2->AddEntry(vec_gluon[i][j], TString::Format("%s ang. using %s-%s GeV",sleg22.Data(), sleg20.Data(), sleg21.Data() ));
        }
        for (int j=0;j<vec_quark[i].size();j++){
            LegName = vec_No_MPI_gluon[i][j]->GetName();
            LegName = LegName.ReplaceAll("_", " ");
            TObjArray *tx = LegName.Tokenize(" ");
            TString sleg20 = ((TObjString *)(tx->At(0)))->String();
            TString sleg21 = ((TObjString *)(tx->At(1)))->String();
            //TString sleg22 = ((TObjString *)(tx->At(2)))->String();
            TString sleg22 = "Gluon";//
            TString sleg23 = ((TObjString *)(tx->At(3)))->String();
            leg2->AddEntry(vec_No_MPI_gluon[i][j], TString::Format("%s ang. (no MPI no ISR) using %s-%s GeV",sleg22.Data(), sleg20.Data(), sleg21.Data() ));
        }
        leg2->AddEntry((TObject*)0, TString::Format("Jet R = %s", GetAngR(vec_quark[i][0]->GetName()).Data() ), "");
        leg2->AddEntry((TObject*)0, TString::Format("Angularity mmdt %s", GetAngName(vec_quark[i][0]->GetName()).Data() ), "");
        leg2->Draw("same");

        CanName=cans[i]->GetName();
        CanName=CanName.ReplaceAll("can_", "");
        CanName=CanName.ReplaceAll("2360_13000_", "");
        CanName=CanName.ReplaceAll("mmdt_mmdt_", "");
        CanName=CanName.ReplaceAll("quark_", "");
        CanName=CanName.ReplaceAll("__", "");

        if (Pythia==1){
            cans[i]->SaveAs(TString::Format("./angs1D_filter_herwig_average_no_7000_13000/1D_%s_pythia_average.png", CanName.Data()));
            cans[i]->SaveAs(TString::Format("./angs1D_filter_herwig_average_no_7000_13000/1D_%s_pythia_average.pdf", CanName.Data()));
        }else{
            cans[i]->SaveAs(TString::Format("./angs1D_filter_herwig_average_no_7000_13000/1D_%s_herwig_average.png", CanName.Data()));
            cans[i]->SaveAs(TString::Format("./angs1D_filter_herwig_average_no_7000_13000/1D_%s_herwig_average.pdf", CanName.Data()));
        }
        
        //cans2[i]->SaveAs(TString::Format("./angs1D_filter_herwig_average/1D_mmdt_%s_herwig_average.png", CanName.Data()));
        //cans2[i]->SaveAs(TString::Format("./angs1D_filter_herwig_average/1D_mmdt_%s_herwig_average.pdf", CanName.Data()));


    }
    
    output->Write();

    return 0;
}
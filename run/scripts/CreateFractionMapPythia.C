int CreateFractionMapPythia(TString Energy = "900"){

    TString Path = "/disk0/QGjetsPetr/Petr_Pythia";
    vector<TString> FileNames;






















if (Energy.Contains("900")){
FileNames.push_back(TString::Format("%s/QGjets_900GeV_nohadr_withMPI_and_part_shower_3/test.root",Path.Data()));
//FileNames.push_back(TString::Format("%s/QGjets_900GeV_nohadr_withMPI_and_part_shower_7/test.root",Path.Data()));
//FileNames.push_back(TString::Format("%s/QGjets_900GeV_nohadr_withMPI_and_part_shower_8/test.root",Path.Data()));
//FileNames.push_back(TString::Format("%s/QGjets_900GeV_nohadr_withMPI_and_part_shower_9/test.root",Path.Data()));
//FileNames.push_back(TString::Format("%s/QGjets_900GeV_nohadr_withMPI_and_part_shower_6/test.root",Path.Data()));
//FileNames.push_back(TString::Format("%s/QGjets_900GeV_nohadr_withMPI_and_part_shower_5/test.root",Path.Data()));
//FileNames.push_back(TString::Format("%s/QGjets_900GeV_nohadr_withMPI_and_part_shower_4/test.root",Path.Data()));
//FileNames.push_back(TString::Format("%s/QGjets_900GeV_nohadr_withMPI_and_part_shower_1/test.root",Path.Data()));
//FileNames.push_back(TString::Format("%s/QGjets_900GeV_nohadr_withMPI_and_part_shower_10/test.root",Path.Data()));
//FileNames.push_back(TString::Format("%s/QGjets_900GeV_nohadr_withMPI_and_part_shower_2/test.root",Path.Data()));
}

if (Energy.Contains("2360")){
FileNames.push_back(TString::Format("%s/QGjets_2360GeV_nohadr_withMPI_and_part_shower_3/test.root",Path.Data()));
//FileNames.push_back(TString::Format("%s/QGjets_2360GeV_nohadr_withMPI_and_part_shower_7/test.root",Path.Data()));
//FileNames.push_back(TString::Format("%s/QGjets_2360GeV_nohadr_withMPI_and_part_shower_8/test.root",Path.Data()));
//FileNames.push_back(TString::Format("%s/QGjets_2360GeV_nohadr_withMPI_and_part_shower_9/test.root",Path.Data()));
//FileNames.push_back(TString::Format("%s/QGjets_2360GeV_nohadr_withMPI_and_part_shower_6/test.root",Path.Data()));
//FileNames.push_back(TString::Format("%s/QGjets_2360GeV_nohadr_withMPI_and_part_shower_5/test.root",Path.Data()));
//FileNames.push_back(TString::Format("%s/QGjets_2360GeV_nohadr_withMPI_and_part_shower_4/test.root",Path.Data()));
//FileNames.push_back(TString::Format("%s/QGjets_2360GeV_nohadr_withMPI_and_part_shower_1/test.root",Path.Data()));
//FileNames.push_back(TString::Format("%s/QGjets_2360GeV_nohadr_withMPI_and_part_shower_10/test.root",Path.Data()));
//FileNames.push_back(TString::Format("%s/QGjets_2360GeV_nohadr_withMPI_and_part_shower_2/test.root",Path.Data()));
}
if (Energy.Contains("7000")){
FileNames.push_back(TString::Format("%s/QGjets_7TeV_nohadr_withMPI_and_part_shower_3/test.root",Path.Data()));
FileNames.push_back(TString::Format("%s/QGjets_7TeV_nohadr_withMPI_and_part_shower_7/test.root",Path.Data()));
FileNames.push_back(TString::Format("%s/QGjets_7TeV_nohadr_withMPI_and_part_shower_8/test.root",Path.Data()));
FileNames.push_back(TString::Format("%s/QGjets_7TeV_nohadr_withMPI_and_part_shower_9/test.root",Path.Data()));
FileNames.push_back(TString::Format("%s/QGjets_7TeV_nohadr_withMPI_and_part_shower_6/test.root",Path.Data()));
FileNames.push_back(TString::Format("%s/QGjets_7TeV_nohadr_withMPI_and_part_shower_5/test.root",Path.Data()));
FileNames.push_back(TString::Format("%s/QGjets_7TeV_nohadr_withMPI_and_part_shower_4/test.root",Path.Data()));
FileNames.push_back(TString::Format("%s/QGjets_7TeV_nohadr_withMPI_and_part_shower_1/test.root",Path.Data()));
FileNames.push_back(TString::Format("%s/QGjets_7TeV_nohadr_withMPI_and_part_shower_10/test.root",Path.Data()));
FileNames.push_back(TString::Format("%s/QGjets_7TeV_nohadr_withMPI_and_part_shower_2/test.root",Path.Data()));
}
if (Energy.Contains("13000")){
FileNames.push_back(TString::Format("%s/QGjets_13TeV_nohadr_withMPI_and_part_shower_3/test.root",Path.Data()));
FileNames.push_back(TString::Format("%s/QGjets_13TeV_nohadr_withMPI_and_part_shower_7/test.root",Path.Data()));
FileNames.push_back(TString::Format("%s/QGjets_13TeV_nohadr_withMPI_and_part_shower_8/test.root",Path.Data()));
FileNames.push_back(TString::Format("%s/QGjets_13TeV_nohadr_withMPI_and_part_shower_9/test.root",Path.Data()));
FileNames.push_back(TString::Format("%s/QGjets_13TeV_nohadr_withMPI_and_part_shower_6/test.root",Path.Data()));
FileNames.push_back(TString::Format("%s/QGjets_13TeV_nohadr_withMPI_and_part_shower_5/test.root",Path.Data()));
FileNames.push_back(TString::Format("%s/QGjets_13TeV_nohadr_withMPI_and_part_shower_4/test.root",Path.Data()));
FileNames.push_back(TString::Format("%s/QGjets_13TeV_nohadr_withMPI_and_part_shower_1/test.root",Path.Data()));
FileNames.push_back(TString::Format("%s/QGjets_13TeV_nohadr_withMPI_and_part_shower_10/test.root",Path.Data()));
FileNames.push_back(TString::Format("%s/QGjets_13TeV_nohadr_withMPI_and_part_shower_2/test.root",Path.Data()));
}



TFile * rfile;
TTree * tree;
//Double_t xbins[9] = {0,25,50,75,100,125,150,175,200};
//Double_t xbins[100] = {0,   2,   4,   6,   8,  10,  12,  14,  16,  18,  20,  22,  24,
//        26,  28,  30,  32,  34,  36,  38,  40,  42,  44,  46,  48,  50,
//        52,  54,  56,  58,  60,  62,  64,  66,  68,  70,  72,  74,  76,
//        78,  80,  82,  84,  86,  88,  90,  92,  94,  96,  98, 100, 102,
//       104, 106, 108, 110, 112, 114, 116, 118, 120, 122, 124, 126, 128,
//       130, 132, 134, 136, 138, 140, 142, 144, 146, 148, 150, 152, 154,
//       156, 158, 160, 162, 164, 166, 168, 170, 172, 174, 176, 178, 180,
//       182, 184, 186, 188, 190, 192, 194, 196, 198};

Double_t xbins[51] = { 0,   4,   8,  12,  16,  20,  24,  28,  32,  36,  40,  44,  48,
        52,  56,  60,  64,  68,  72,  76,  80,  84,  88,  92,  96, 100,
       104, 108, 112, 116, 120, 124, 128, 132, 136, 140, 144, 148, 152,
       156, 160, 164, 168, 172, 176, 180, 184, 188, 192, 196, 200};
//Double_t ybins[7] = {-2.5,-1.5,-1.0,0.,1.,1.5, 2.5};
Double_t ybins[11] = {-2.5, -2. , -1.5, -1. , -0.5,  0. ,  0.5,  1. ,  1.5,  2. , 2.5};
TH2F * nom  ;// = new TH2F("nom", "nom",       sizeof(xbins)/sizeof(Double_t)-1, xbins, sizeof(ybins)/sizeof(Double_t)-1, ybins);
TH2F * denom;// = new TH2F("denom", "denom", sizeof(xbins)/sizeof(Double_t)-1, xbins, sizeof(ybins)/sizeof(Double_t)-1, ybins);
TH2F * final = new TH2F("final", "final", sizeof(xbins)/sizeof(Double_t)-1, xbins, sizeof(ybins)/sizeof(Double_t)-1, ybins);
TH2F * finalden = new TH2F("finalden", "finalden", sizeof(xbins)/sizeof(Double_t)-1, xbins, sizeof(ybins)/sizeof(Double_t)-1, ybins);

int wind_dn;
int wind_up;
TString Cut;
TString Cut2;
TString ToDraw1;
TString ToDraw2;
for (int i = 0; i < FileNames.size(); i++){
    wind_dn = i*25;
    wind_up = i*25 + 25;
    rfile = new TFile(FileNames[i].Data(), "read");
    tree = (TTree*)rfile->Get("MC_DIJET_PB_CH");
    nom   = new TH2F(TString::Format("nom_%i", i) , TString::Format("nom_%i", i)  ,       sizeof(xbins)/sizeof(Double_t)-1, xbins, sizeof(ybins)/sizeof(Double_t)-1, ybins);
    denom = new TH2F(TString::Format("denom_%i",i), TString::Format("denom_%i",i) , sizeof(xbins)/sizeof(Double_t)-1, xbins, sizeof(ybins)/sizeof(Double_t)-1, ybins);
    Cut =  "";//TString::Format("(GluonFractionPt > %i)&&(GluonFractionPt <= %i)", wind_dn, wind_up);
    Cut2 = "";//TString::Format("(GluonAndQuarkFractionPt > %i)&&(GluonAndQuarkFractionPt <= %i)", wind_dn, wind_up);
    ToDraw1 = TString::Format("GluonFractionEta:GluonFractionPt>>%s", nom->GetName());
    ToDraw2 = TString::Format("GluonAndQuarkFractionEta:GluonAndQuarkFractionPt>>%s", denom->GetName());
    tree->Draw(ToDraw1.Data(), Cut.Data(), "goff");
    tree->Draw(ToDraw2.Data(), Cut2.Data(), "goff");

    //nom->GetXaxis()->SetLimits(wind_dn, wind_up);
    //nom->GetYaxis()->SetLimits(-2.5, 2.5);
    //denom->GetXaxis()->SetLimits(wind_dn, wind_up);
    //denom->GetYaxis()->SetLimits(-2.5, 2.5);
    cout << i << endl;
    cout <<   nom->Integral() << endl;
    cout << denom->Integral() << endl;
    //nom->Divide(denom);
    final->Add(nom);
    finalden->Add(denom);
}

//TCanvas * can = new TCanvas("can", "can", 0,0,1600,1600);
//can->cd();

//final->Draw("colz text");

//TCanvas * can2 = new TCanvas("can2", "can2", 0,0,1600,1600);
//can2->cd();
//finalden->Draw("colz text");

//TEfficiency * eff = new TEfficiency(*final   , *finalden   );
//final->Divide(finalden);
TFile * out = new TFile(TString::Format("GluonFraction_%s_pythia.root", Energy.Data() ), "recreate");
out->cd();
final->SetName(TString::Format("NomGluonFraction_%s", Energy.Data() ));
final->SetTitle(TString::Format("NomGluonFraction_%s", Energy.Data() ));
finalden->SetName(TString::Format("DenomGluonFraction_%s", Energy.Data() ));
finalden->SetTitle(TString::Format("DenomGluonFraction_%s", Energy.Data() ));
TH2F * fraction = (TH2F*)final->Clone(TString::Format("GluonFraction_%s", Energy.Data() ));
fraction->SetTitle(TString::Format("GluonFraction_%s", Energy.Data() ));
fraction->Sumw2(1);
finalden->Sumw2(1);
fraction->Divide(finalden);

final->Write();
finalden->Write();
fraction->Write();
out->Write();
out->Close();

    return 0;
}
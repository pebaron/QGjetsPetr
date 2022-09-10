int CreateTestTrig(){
    TFile * rfile = new TFile("out_trig_all_stats.root", "recreate");
    // for now rfile->mkdir("Loose");    
    rfile->mkdir("Medium");
    // for now rfile->mkdir("Tight");
    // for now rfile->mkdir("HighPt");
    
    // for now rfile->mkdir("Loose/PeriodB");    
    // for now rfile->mkdir("Loose/PeriodC");
    rfile->mkdir("Medium/PeriodBC");
    // for now rfile->mkdir("Medium/PeriodC");
    // for now rfile->mkdir("Tight/PeriodB");
    // for now rfile->mkdir("Tight/PeriodC");
    // for now rfile->mkdir("HighPt/PeriodB");
    // for now rfile->mkdir("HighPt/PeriodC");

//just for now    rfile->mkdir("Loose/PeriodB/HLT_mu15");
//just for now    rfile->mkdir("Loose/PeriodC/HLT_mu15");
//just for now    rfile->mkdir("Medium/PeriodB/HLT_mu15");
//just for now    rfile->mkdir("Medium/PeriodC/HLT_mu15");
//just for now    rfile->mkdir("Tight/PeriodB/HLT_mu15");
//just for now    rfile->mkdir("Tight/PeriodC/HLT_mu15");
//just for now    rfile->mkdir("HighPt/PeriodB/HLT_mu15");
//just for now    rfile->mkdir("HighPt/PeriodC/HLT_mu15");

// just for now     rfile->mkdir("Loose/PeriodB/HLT_mu15_L1MU6");
// just for now     rfile->mkdir("Loose/PeriodC/HLT_mu15_L1MU6");
// just for now     rfile->mkdir("Medium/PeriodB/HLT_mu15_L1MU6");
// just for now     rfile->mkdir("Medium/PeriodC/HLT_mu15_L1MU6");
// just for now     rfile->mkdir("Tight/PeriodB/HLT_mu15_L1MU6");
// just for now     rfile->mkdir("Tight/PeriodC/HLT_mu15_L1MU6");
// just for now     rfile->mkdir("HighPt/PeriodB/HLT_mu15_L1MU6");
// just for now     rfile->mkdir("HighPt/PeriodC/HLT_mu15_L1MU6");
// just for now 
// just for now     rfile->mkdir("Loose/PeriodB/HLT_mu15_L1MU10");
// just for now     rfile->mkdir("Loose/PeriodC/HLT_mu15_L1MU10");
// just for now     rfile->mkdir("Medium/PeriodB/HLT_mu15_L1MU10");
// just for now     rfile->mkdir("Medium/PeriodC/HLT_mu15_L1MU10");
// just for now     rfile->mkdir("Tight/PeriodB/HLT_mu15_L1MU10");
// just for now     rfile->mkdir("Tight/PeriodC/HLT_mu15_L1MU10");
// just for now     rfile->mkdir("HighPt/PeriodB/HLT_mu15_L1MU10");
// just for now     rfile->mkdir("HighPt/PeriodC/HLT_mu15_L1MU10");

    //for now rfile->mkdir("Loose/PeriodB/HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10");
    //for now rfile->mkdir("Loose/PeriodC/HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10");
    //for now rfile->mkdir("Medium/PeriodB/HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10");
    rfile->mkdir("Medium/PeriodBC/HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10");
    //for now rfile->mkdir("Medium/PeriodC/HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10");
    //for now rfile->mkdir("Tight/PeriodB/HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10");
    //for now rfile->mkdir("Tight/PeriodC/HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10");
    //for now rfile->mkdir("HighPt/PeriodB/HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10");
    //for now rfile->mkdir("HighPt/PeriodC/HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10");


TH2F * eff_etaphi_fine_barrel_data_nominal;
TH2F * eff_etaphi_fine_barrel_data_stat_up;
TH2F * eff_etaphi_fine_barrel_data_stat_down;
TH2F * eff_etaphi_fine_barrel_mc_nominal;
TH2F * eff_etaphi_fine_barrel_mc_stat_up;
TH2F * eff_etaphi_fine_barrel_mc_stat_down;
TH2F * eff_etaphi_fine_barrel_mc_syst_up;
TH2F * eff_etaphi_fine_barrel_mc_syst_down;
TH2F * eff_etaphi_coarse_barrel_data_nominal;
TH2F * eff_etaphi_coarse_barrel_data_stat_up;
TH2F * eff_etaphi_coarse_barrel_data_stat_down;
TH2F * eff_etaphi_coarse_barrel_mc_nominal;
TH2F * eff_etaphi_coarse_barrel_mc_stat_up;
TH2F * eff_etaphi_coarse_barrel_mc_stat_down;
TH2F * eff_etaphi_coarse_barrel_mc_syst_up;
TH2F * eff_etaphi_coarse_barrel_mc_syst_down;
TH2F * eff_etaphi_fine_endcap_data_nominal;
TH2F * eff_etaphi_fine_endcap_data_stat_up;
TH2F * eff_etaphi_fine_endcap_data_stat_down;
TH2F * eff_etaphi_fine_endcap_mc_nominal;
TH2F * eff_etaphi_fine_endcap_mc_stat_up;
TH2F * eff_etaphi_fine_endcap_mc_stat_down;
TH2F * eff_etaphi_fine_endcap_mc_syst_up;
TH2F * eff_etaphi_fine_endcap_mc_syst_down;
TH2F * eff_etaphi_coarse_endcap_data_nominal;
TH2F * eff_etaphi_coarse_endcap_data_stat_up;
TH2F * eff_etaphi_coarse_endcap_data_stat_down;
TH2F * eff_etaphi_coarse_endcap_mc_nominal;
TH2F * eff_etaphi_coarse_endcap_mc_stat_up;
TH2F * eff_etaphi_coarse_endcap_mc_stat_down;
TH2F * eff_etaphi_coarse_endcap_mc_syst_up;
TH2F * eff_etaphi_coarse_endcap_mc_syst_down;


//eff_etaphi_fine_barrel_data_nominal
//eff_etaphi_fine_barrel_data_stat_up
//eff_etaphi_fine_barrel_data_stat_down
//eff_etaphi_fine_barrel_mc_nominal
//eff_etaphi_fine_barrel_mc_stat_up
//eff_etaphi_fine_barrel_mc_stat_down
//eff_etaphi_fine_barrel_mc_syst_up
//eff_etaphi_fine_barrel_mc_syst_down
//eff_etaphi_coarse_barrel_data_nominal
//eff_etaphi_coarse_barrel_data_stat_up
//eff_etaphi_coarse_barrel_data_stat_down
//eff_etaphi_coarse_barrel_mc_nominal
//eff_etaphi_coarse_barrel_mc_stat_up
//eff_etaphi_coarse_barrel_mc_stat_down
//eff_etaphi_coarse_barrel_mc_syst_up
//eff_etaphi_coarse_barrel_mc_syst_down
//eff_etaphi_fine_endcap_data_nominal
//eff_etaphi_fine_endcap_data_stat_up
//eff_etaphi_fine_endcap_data_stat_down
//eff_etaphi_fine_endcap_mc_nominal
//eff_etaphi_fine_endcap_mc_stat_up
//eff_etaphi_fine_endcap_mc_stat_down
//eff_etaphi_fine_endcap_mc_syst_up
//eff_etaphi_fine_endcap_mc_syst_down
//eff_etaphi_coarse_endcap_data_nominal
//eff_etaphi_coarse_endcap_data_stat_up
//eff_etaphi_coarse_endcap_data_stat_down
//eff_etaphi_coarse_endcap_mc_nominal
//eff_etaphi_coarse_endcap_mc_stat_up
//eff_etaphi_coarse_endcap_mc_stat_down
//eff_etaphi_coarse_endcap_mc_syst_up
//eff_etaphi_coarse_endcap_mc_syst_down


    vector<TString> WPs;
    //WPs.push_back("Loose");
    WPs.push_back("Medium");
    //WPs.push_back("Tight");
    //WPs.push_back("HighPt");

    vector<TString> Periods;
    //for now Periods.push_back("PeriodB");
    //for now Periods.push_back("PeriodC");
    Periods.push_back("PeriodBC");

    vector<TString> Triggers;
    // just for now Triggers.push_back("HLT_mu15");
    // just for now Triggers.push_back("HLT_mu15_L1MU6");
    // just for now Triggers.push_back("HLT_mu15_L1MU10");
    Triggers.push_back("HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10");

    vector<TString> Triggers_read;
    //just for now Triggers_read.push_back("HLT_mu15");
    //just for now Triggers_read.push_back("HLT_mu15_L1MU6");
    //just for now Triggers_read.push_back("HLT_mu15_L1MU10");
    Triggers_read.push_back("HLT_mu15_comb");

    vector<TString> Detector;
    Detector.push_back("Endcap");
    Detector.push_back("Barrel");

    vector<TString> DataMC;
    DataMC.push_back("MC");
    DataMC.push_back("Data");

    vector<TString> Binning;
    Binning.push_back("fine");
    Binning.push_back("coarse");


    TString TempPath;
    TString HistName;
    TString HistNameUP;
    TString HistNameDN;
    TString HistNameUPSYS;
    TString HistNameDNSYS;

    TH2F * Nominal;
    TH2F * NominalSTATUP;
    TH2F * NominalSTATDN;
    TH2F * NominalSYSTUP;
    TH2F * NominalSYSTDN;

    TString Name_Nominal;
    TString Name_NominalSTATUP;
    TString Name_NominalSTATDN;
    TString Name_NominalSYSTUP;
    TString Name_NominalSYSTDN;

    TFile * tempfile_nom;
    TFile * tempfile_up;
    TFile * tempfile_dn;
    TFile * tempfile_upsys;
    TFile * tempfile_dnsys;

    TString BinTemp;

    for (int i=0; i<WPs.size();i++){
        for (int j=0; j<Periods.size();j++){
            for (int k=0; k<Triggers.size();k++){
                TempPath = TString::Format("%s/%s/%s", WPs[i].Data(), Periods[j].Data(), Triggers[k].Data() );
                rfile->cd(TempPath.Data());
                cout << TempPath.Data() << endl;
                for (int l=0; l<Detector.size();l++){
                    for (int m=0; m<DataMC.size();m++){
                        for (int n=0; n<Binning.size();n++){
                            if (Binning[n].Contains("fine")){
                                BinTemp = "coarse";
                                //previously was dir eff_trig_pPb2D_coarse_v9
                                HistName = TString::Format("new_SFs_v8/eff_trig_pPb2D_pub_all_stat/Eff_etaphi_%s_%s_Quality%s_%s_%s_%sEfficiency_noDDBkg.root", BinTemp.Data(), Detector[l].Data(), WPs[i].Data(), Detector[l].Data(), Triggers_read[k].Data(), DataMC[m].Data());
                                HistNameUP = TString::Format("new_SFs_v8/eff_trig_pPb2D_pub_all_stat/Eff_etaphi_%s_%s_Quality%s_%s_%s_%sEfficiency_STAT_1UP_noDDBkg.root", BinTemp.Data(), Detector[l].Data(), WPs[i].Data(), Detector[l].Data(), Triggers_read[k].Data(), DataMC[m].Data());
                                HistNameDN = TString::Format("new_SFs_v8/eff_trig_pPb2D_pub_all_stat/Eff_etaphi_%s_%s_Quality%s_%s_%s_%sEfficiency_STAT_1DN_noDDBkg.root", BinTemp.Data(), Detector[l].Data(), WPs[i].Data(), Detector[l].Data(), Triggers_read[k].Data(), DataMC[m].Data());
                                HistNameUPSYS = TString::Format("new_SFs_v8/eff_trig_pPb2D_pub_all_stat/Eff_etaphi_%s_%s_Quality%s_%s_%s_%sEfficiency_TOTSYS_1UP_noDDBkg.root", BinTemp.Data(), Detector[l].Data(), WPs[i].Data(), Detector[l].Data(), Triggers_read[k].Data(), DataMC[m].Data());
                                HistNameDNSYS = TString::Format("new_SFs_v8/eff_trig_pPb2D_pub_all_stat/Eff_etaphi_%s_%s_Quality%s_%s_%s_%sEfficiency_TOTSYS_1DN_noDDBkg.root", BinTemp.Data(), Detector[l].Data(), WPs[i].Data(), Detector[l].Data(), Triggers_read[k].Data(), DataMC[m].Data());
                            } else{
                                HistName = TString::Format("new_SFs_v8/eff_trig_pPb2D_pub_all_stat/Eff_etaphi_%s_%s_Quality%s_%s_%s_%sEfficiency_noDDBkg.root", Binning[n].Data(), Detector[l].Data(), WPs[i].Data(), Detector[l].Data(), Triggers_read[k].Data(), DataMC[m].Data());
                                HistNameUP = TString::Format("new_SFs_v8/eff_trig_pPb2D_pub_all_stat/Eff_etaphi_%s_%s_Quality%s_%s_%s_%sEfficiency_STAT_1UP_noDDBkg.root", Binning[n].Data(), Detector[l].Data(), WPs[i].Data(), Detector[l].Data(), Triggers_read[k].Data(), DataMC[m].Data());
                                HistNameDN = TString::Format("new_SFs_v8/eff_trig_pPb2D_pub_all_stat/Eff_etaphi_%s_%s_Quality%s_%s_%s_%sEfficiency_STAT_1DN_noDDBkg.root", Binning[n].Data(), Detector[l].Data(), WPs[i].Data(), Detector[l].Data(), Triggers_read[k].Data(), DataMC[m].Data());
                                HistNameUPSYS = TString::Format("new_SFs_v8/eff_trig_pPb2D_pub_all_stat/Eff_etaphi_%s_%s_Quality%s_%s_%s_%sEfficiency_TOTSYS_1UP_noDDBkg.root", Binning[n].Data(), Detector[l].Data(), WPs[i].Data(), Detector[l].Data(), Triggers_read[k].Data(), DataMC[m].Data());
                                HistNameDNSYS = TString::Format("new_SFs_v8/eff_trig_pPb2D_pub_all_stat/Eff_etaphi_%s_%s_Quality%s_%s_%s_%sEfficiency_TOTSYS_1DN_noDDBkg.root", Binning[n].Data(), Detector[l].Data(), WPs[i].Data(), Detector[l].Data(), Triggers_read[k].Data(), DataMC[m].Data());
                                
                            }
                        cout << HistName.Data() << endl;
                        cout << HistNameUP.Data() << endl;
                        cout << HistNameDN.Data() << endl;

                        tempfile_nom   = new TFile(HistName.Data(), "read");
                        tempfile_up    = new TFile(HistNameUP.Data(), "read");
                        tempfile_dn    = new TFile(HistNameDN.Data(), "read");                        
                        tempfile_upsys = new TFile(HistNameUPSYS.Data(), "read");
                        tempfile_dnsys = new TFile(HistNameDNSYS.Data(), "read");                        
                        // safe fine as coarse fo AnalysisTop
                        //if (Binning[n].Contains("fine")){
                        if (false){
                            Name_Nominal       = TString::Format("eff_etaphi_coarse_%s_%s_nominal", Detector[l].Data(), DataMC[m].Data());
                            Name_NominalSTATUP = TString::Format("eff_etaphi_coarse_%s_%s_stat_up", Detector[l].Data(), DataMC[m].Data());
                            Name_NominalSTATDN = TString::Format("eff_etaphi_coarse_%s_%s_stat_down", Detector[l].Data(), DataMC[m].Data());
                            Name_NominalSYSTUP = TString::Format("eff_etaphi_coarse_%s_%s_syst_up", Detector[l].Data(), DataMC[m].Data());
                            Name_NominalSYSTDN = TString::Format("eff_etaphi_coarse_%s_%s_syst_down", Detector[l].Data(), DataMC[m].Data());
                        }else{
                            Name_Nominal       = TString::Format("eff_etaphi_%s_%s_%s_nominal", Binning[n].Data(), Detector[l].Data(), DataMC[m].Data());
                            Name_NominalSTATUP = TString::Format("eff_etaphi_%s_%s_%s_stat_up", Binning[n].Data(), Detector[l].Data(), DataMC[m].Data());
                            Name_NominalSTATDN = TString::Format("eff_etaphi_%s_%s_%s_stat_down", Binning[n].Data(), Detector[l].Data(), DataMC[m].Data());
                            Name_NominalSYSTUP = TString::Format("eff_etaphi_%s_%s_%s_syst_up", Binning[n].Data(), Detector[l].Data(), DataMC[m].Data());
                            Name_NominalSYSTDN = TString::Format("eff_etaphi_%s_%s_%s_syst_down", Binning[n].Data(), Detector[l].Data(), DataMC[m].Data());
                        }

                        Name_Nominal.ToLower();
                        Name_NominalSTATUP.ToLower();
                        Name_NominalSTATDN.ToLower();
                        Name_NominalSYSTUP.ToLower();
                        Name_NominalSYSTDN.ToLower();

                        cout << Name_Nominal.Data() << endl;
                        cout << Name_NominalSTATUP.Data() << endl;
                        cout << Name_NominalSTATDN.Data() << endl;

                        Nominal = (TH2F*)tempfile_nom->Get("SF");
                        NominalSTATUP = (TH2F*)tempfile_up->Get("SF");
                        NominalSTATDN = (TH2F*)tempfile_dn->Get("SF");
                        NominalSYSTUP = (TH2F*)tempfile_upsys->Get("SF");
                        NominalSYSTDN = (TH2F*)tempfile_dnsys->Get("SF");
                        

                        Nominal->SetName(Name_Nominal.Data());
                        NominalSTATUP->SetName(Name_NominalSTATUP.Data());
                        NominalSTATDN->SetName(Name_NominalSTATDN.Data());
                        NominalSYSTUP->SetName(Name_NominalSYSTUP.Data());
                        NominalSYSTDN->SetName(Name_NominalSYSTDN.Data());

                        for (int o=1; o<=Nominal->GetXaxis()->GetNbins();o++){
                            for (int p=1; p<=Nominal->GetYaxis()->GetNbins();p++){
                                NominalSTATUP->SetBinContent(o,p, Nominal->GetBinContent(o,p) * (1. + NominalSTATUP->GetBinContent(o,p)/100. ) );
                                NominalSTATDN->SetBinContent(o,p, Nominal->GetBinContent(o,p) * (1. - NominalSTATDN->GetBinContent(o,p)/100. ) );
                                NominalSYSTUP->SetBinContent(o,p, Nominal->GetBinContent(o,p) * (1. + NominalSYSTUP->GetBinContent(o,p)/100. ) );
                                NominalSYSTDN->SetBinContent(o,p, Nominal->GetBinContent(o,p) * (1. - NominalSYSTDN->GetBinContent(o,p)/100. ) );
                                //76.5625*(1.+7.41711/100.)
                                //effUP/DOWN = GetBinContent() * (1.+ GetBinContent_UP/DOWN()/100.);
                            }
                        }

                        rfile->cd(TempPath.Data());
                        Nominal->Write();
                        NominalSTATUP->Write();
                        NominalSTATDN->Write();
                        NominalSYSTUP->Write();
                        NominalSYSTDN->Write();

                        //if (DataMC[m].Contains("MC")){
                        //    NominalSYSTUP = (TH2F*)NominalSTATUP->Clone(Name_NominalSYSTUP.Data());
                        //    NominalSYSTDN = (TH2F*)NominalSTATDN->Clone(Name_NominalSYSTDN.Data());
                        //    cout << Name_NominalSYSTUP.Data() << endl;
                        //    cout << Name_NominalSYSTDN.Data() << endl;
                        //    NominalSYSTUP->Write();
                        //    NominalSYSTDN->Write();
                        //    }

                        tempfile_nom  ->Close();
                        tempfile_up   ->Close();
                        tempfile_dn   ->Close();
                        tempfile_upsys->Close();
                        tempfile_dnsys->Close();


                        }
                    }
                }
                cout << "------------" << endl;

            }
        }
    }

    

/*


    for (int i; i<myvect.size();i++){
rfile->cd(myvect[i]);
    if (myvect.Data() == "Loose/PeriodB/HLT_mu15") || (myvect.Data() == "Loose/PeriodC/HLT_mu15"){
        eff_trig_pPb_Barrel/Eff_etaphi_coarse_Barrel_QualityLoose_Barrel_HLT_mu15_MCEfficiency_noDDBkg.root
        eff_trig_pPb_Barrel/Eff_etaphi_coarse_Barrel_QualityLoose_Barrel_HLT_mu15_MCEfficiency_STAT_1DN_noDDBkg.root
        eff_trig_pPb_Barrel/Eff_etaphi_coarse_Barrel_QualityLoose_Barrel_HLT_mu15_MCEfficiency_STAT_1UP_noDDBkg.root
        eff_trig_pPb_Barrel/Eff_etaphi_fine_Barrel_QualityLoose_Barrel_HLT_mu15_MCEfficiency_noDDBkg.root
        eff_trig_pPb_Barrel/Eff_etaphi_fine_Barrel_QualityLoose_Barrel_HLT_mu15_MCEfficiency_STAT_1DN_noDDBkg.root
        eff_trig_pPb_Barrel/Eff_etaphi_fine_Barrel_QualityLoose_Barrel_HLT_mu15_MCEfficiency_STAT_1UP_noDDBkg.root

        eff_trig_pPb_Barrel/Eff_etaphi_coarse_Barrel_QualityLoose_Barrel_HLT_mu15_DataEfficiency_noDDBkg.root
        eff_trig_pPb_Barrel/Eff_etaphi_coarse_Barrel_QualityLoose_Barrel_HLT_mu15_DataEfficiency_STAT_1DN_noDDBkg.root
        eff_trig_pPb_Barrel/Eff_etaphi_coarse_Barrel_QualityLoose_Barrel_HLT_mu15_DataEfficiency_STAT_1UP_noDDBkg.root
        eff_trig_pPb_Barrel/Eff_etaphi_fine_Barrel_QualityLoose_Barrel_HLT_mu15_DataEfficiency_noDDBkg.root
        eff_trig_pPb_Barrel/Eff_etaphi_fine_Barrel_QualityLoose_Barrel_HLT_mu15_DataEfficiency_STAT_1DN_noDDBkg.root
        eff_trig_pPb_Barrel/Eff_etaphi_fine_Barrel_QualityLoose_Barrel_HLT_mu15_DataEfficiency_STAT_1UP_noDDBkg.root

        eff_trig_pPb_Endcap/Eff_etaphi_coarse_Endcap_QualityLoose_Endcap_HLT_mu15_MCEfficiency_noDDBkg.root
        eff_trig_pPb_Endcap/Eff_etaphi_coarse_Endcap_QualityLoose_Endcap_HLT_mu15_MCEfficiency_STAT_1DN_noDDBkg.root
        eff_trig_pPb_Endcap/Eff_etaphi_coarse_Endcap_QualityLoose_Endcap_HLT_mu15_MCEfficiency_STAT_1UP_noDDBkg.root
        eff_trig_pPb_Endcap/Eff_etaphi_fine_Endcap_QualityLoose_Endcap_HLT_mu15_MCEfficiency_noDDBkg.root
        eff_trig_pPb_Endcap/Eff_etaphi_fine_Endcap_QualityLoose_Endcap_HLT_mu15_MCEfficiency_STAT_1DN_noDDBkg.root
        eff_trig_pPb_Endcap/Eff_etaphi_fine_Endcap_QualityLoose_Endcap_HLT_mu15_MCEfficiency_STAT_1UP_noDDBkg.root

        eff_trig_pPb_Endcap/Eff_etaphi_coarse_Endcap_QualityLoose_Endcap_HLT_mu15_DataEfficiency_noDDBkg.root
        eff_trig_pPb_Endcap/Eff_etaphi_coarse_Endcap_QualityLoose_Endcap_HLT_mu15_DataEfficiency_STAT_1DN_noDDBkg.root
        eff_trig_pPb_Endcap/Eff_etaphi_coarse_Endcap_QualityLoose_Endcap_HLT_mu15_DataEfficiency_STAT_1UP_noDDBkg.root
        eff_trig_pPb_Endcap/Eff_etaphi_fine_Endcap_QualityLoose_Endcap_HLT_mu15_DataEfficiency_noDDBkg.root
        eff_trig_pPb_Endcap/Eff_etaphi_fine_Endcap_QualityLoose_Endcap_HLT_mu15_DataEfficiency_STAT_1DN_noDDBkg.root
        eff_trig_pPb_Endcap/Eff_etaphi_fine_Endcap_QualityLoose_Endcap_HLT_mu15_DataEfficiency_STAT_1UP_noDDBkg.root


    }

eff_etaphi_fine_barrel_data_nominal_clone->Write();
eff_etaphi_fine_barrel_data_stat_up_clone->Write();
eff_etaphi_fine_barrel_data_stat_down_clone->Write();
eff_etaphi_fine_barrel_mc_nominal_clone->Write();
eff_etaphi_fine_barrel_mc_stat_up_clone->Write();
eff_etaphi_fine_barrel_mc_stat_down_clone->Write();
eff_etaphi_fine_barrel_mc_syst_up_clone->Write();
eff_etaphi_fine_barrel_mc_syst_down_clone->Write();
eff_etaphi_coarse_barrel_data_nominal_clone->Write();
eff_etaphi_coarse_barrel_data_stat_up_clone->Write();
eff_etaphi_coarse_barrel_data_stat_down_clone->Write();
eff_etaphi_coarse_barrel_mc_nominal_clone->Write();
eff_etaphi_coarse_barrel_mc_stat_up_clone->Write();
eff_etaphi_coarse_barrel_mc_stat_down_clone->Write();
eff_etaphi_coarse_barrel_mc_syst_up_clone->Write();
eff_etaphi_coarse_barrel_mc_syst_down_clone->Write();
eff_etaphi_fine_endcap_data_nominal_clone->Write();
eff_etaphi_fine_endcap_data_stat_up_clone->Write();
eff_etaphi_fine_endcap_data_stat_down_clone->Write();
eff_etaphi_fine_endcap_mc_nominal_clone->Write();
eff_etaphi_fine_endcap_mc_stat_up_clone->Write();
eff_etaphi_fine_endcap_mc_stat_down_clone->Write();
eff_etaphi_fine_endcap_mc_syst_up_clone->Write();
eff_etaphi_fine_endcap_mc_syst_down_clone->Write();
eff_etaphi_coarse_endcap_data_nominal_clone->Write();
eff_etaphi_coarse_endcap_data_stat_up_clone->Write();
eff_etaphi_coarse_endcap_data_stat_down_clone->Write();
eff_etaphi_coarse_endcap_mc_nominal_clone->Write();
eff_etaphi_coarse_endcap_mc_stat_up_clone->Write();
eff_etaphi_coarse_endcap_mc_stat_down_clone->Write();
eff_etaphi_coarse_endcap_mc_syst_up_clone->Write();
eff_etaphi_coarse_endcap_mc_syst_down_clone->Write();
    }
*/

    rfile->Write();
    rfile->Close();
    return 0;
}
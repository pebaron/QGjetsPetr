
double FindMin(TH2D *h, TH2D *h2){
    double min = -99.;
    double min2 = -99.;
    for (int i = 1; i <= 4; i++){
        if (i==2) continue;
        if (i==3) continue;
        for (int j = 1; j <= h->GetYaxis()->GetNbins(); j++){
            if (h->GetBinContent(i,j)>0.){
                if (min == -99.){
                    min = h->GetBinContent(i,j);
                }
                if (h->GetBinContent(i,j)<min){
                    min = h->GetBinContent(i,j);
                }
            }
        }
    }

    for (int i = 2; i <= 3; i++){
        for (int j = 1; j <= h2->GetYaxis()->GetNbins(); j++){
            if (h2->GetBinContent(i,j)>0.){
                if (min2 == -99.){
                    min2 = h2->GetBinContent(i,j);
                }
                if (h2->GetBinContent(i,j)<min){
                    min2 = h2->GetBinContent(i,j);
                }
            }
        }
    }

    if (min < min2) return min;
    if (min2 <= min) return min2;

    return 0.;

}

double FindMax(TH2D *h, TH2D *h2){
    double min = -99.;
    double min2 = -99.;
    for (int i = 1; i <= 4; i++){
        if (i==2) continue;
        if (i==3) continue;
        for (int j = 1; j <= h->GetYaxis()->GetNbins(); j++){
            if (h->GetBinContent(i,j)>0.){
                if (min == -99.){
                    min = h->GetBinContent(i,j);
                }
                if (h->GetBinContent(i,j)>min){
                    min = h->GetBinContent(i,j);
                }
            }
        }
    }

    for (int i = 2; i <= 3; i++){
        for (int j = 1; j <= h2->GetYaxis()->GetNbins(); j++){
            if (h2->GetBinContent(i,j)>0.){
                if (min2 == -99.){
                    min2 = h2->GetBinContent(i,j);
                }
                if (h2->GetBinContent(i,j)>min){
                    min2 = h2->GetBinContent(i,j);
                }
            }
        }
    }

    if (min < min2) return min2;
    if (min2 >= min) return min;

    //if (h->GetMaximum() > h2->GetMaximum() ) return h->GetMaximum();
    //if (h->GetMaximum() <= h2->GetMaximum() ) return h2->GetMaximum();
    return 1.1;

}


int PlotTrigger(TString Input = "./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Endcap_QualityMedium_Endcap_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_ScaleFactor_noDDBkg.root"){

vector<TString> FileList;
FileList.push_back(Input.Data());
////FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Endcap_QualityMedium_Endcap_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_ScaleFactor_noDDBkg.root");
////FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Endcap_QualityMedium_Endcap_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_ScaleFactor_HI_dphill_SYS_1DN_noDDBkg.root");
////FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Endcap_QualityMedium_Endcap_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_ScaleFactor_HI_dphill_SYS_1UP_noDDBkg.root");
////FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Endcap_QualityMedium_Endcap_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_ScaleFactor_HI_mupos_SYS_1DN_noDDBkg.root");
////FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Endcap_QualityMedium_Endcap_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_ScaleFactor_HI_mupos_SYS_1UP_noDDBkg.root");
////FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Endcap_QualityMedium_Endcap_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_ScaleFactor_HI_muneg_SYS_1DN_noDDBkg.root");
////FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Endcap_QualityMedium_Endcap_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_ScaleFactor_HI_muneg_SYS_1UP_noDDBkg.root");
////FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Endcap_QualityMedium_Endcap_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_ScaleFactor_HI_ptdw_SYS_1DN_noDDBkg.root");
////FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Endcap_QualityMedium_Endcap_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_ScaleFactor_HI_ptdw_SYS_1UP_noDDBkg.root");
////FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Endcap_QualityMedium_Endcap_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_ScaleFactor_HI_ptup_SYS_1DN_noDDBkg.root");
////FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Endcap_QualityMedium_Endcap_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_ScaleFactor_HI_ptup_SYS_1UP_noDDBkg.root");
////FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Endcap_QualityMedium_Endcap_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_ScaleFactor_HI_mll_SYS_1DN_noDDBkg.root");
////FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Endcap_QualityMedium_Endcap_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_ScaleFactor_HI_mll_SYS_1UP_noDDBkg.root");
////FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Endcap_QualityMedium_Endcap_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_ScaleFactor_HI_noIP_SYS_1DN_noDDBkg.root");
////FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Endcap_QualityMedium_Endcap_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_ScaleFactor_HI_noIP_SYS_1UP_noDDBkg.root");
////FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Endcap_QualityMedium_Endcap_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_ScaleFactor_HI_isoTightTrackOnly_SYS_1DN_noDDBkg.root");
////FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Endcap_QualityMedium_Endcap_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_ScaleFactor_HI_isoTightTrackOnly_SYS_1UP_noDDBkg.root");
////FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Endcap_QualityMedium_Endcap_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_ScaleFactor_HI_isoTight_SYS_1DN_noDDBkg.root");
////FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Endcap_QualityMedium_Endcap_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_ScaleFactor_HI_isoTight_SYS_1UP_noDDBkg.root");
////FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Endcap_QualityMedium_Endcap_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_ScaleFactor_STAT_1DN_noDDBkg.root");
////FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Endcap_QualityMedium_Endcap_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_ScaleFactor_STAT_1UP_noDDBkg.root");
////FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Endcap_QualityMedium_Endcap_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_ScaleFactor_TOTSYS_1DN_noDDBkg.root");
////FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Endcap_QualityMedium_Endcap_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_ScaleFactor_TOTSYS_1UP_noDDBkg.root");
////FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Endcap_QualityMedium_Endcap_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_DataEfficiency_noDDBkg.root");
////FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Endcap_QualityMedium_Endcap_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_DataEfficiency_HI_dphill_SYS_1DN_noDDBkg.root");
////FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Endcap_QualityMedium_Endcap_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_DataEfficiency_HI_dphill_SYS_1UP_noDDBkg.root");
////FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Endcap_QualityMedium_Endcap_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_DataEfficiency_HI_mupos_SYS_1DN_noDDBkg.root");
////FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Endcap_QualityMedium_Endcap_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_DataEfficiency_HI_mupos_SYS_1UP_noDDBkg.root");
////FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Endcap_QualityMedium_Endcap_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_DataEfficiency_HI_muneg_SYS_1DN_noDDBkg.root");
////FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Endcap_QualityMedium_Endcap_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_DataEfficiency_HI_muneg_SYS_1UP_noDDBkg.root");
////FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Endcap_QualityMedium_Endcap_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_DataEfficiency_HI_ptdw_SYS_1DN_noDDBkg.root");
////FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Endcap_QualityMedium_Endcap_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_DataEfficiency_HI_ptdw_SYS_1UP_noDDBkg.root");
////FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Endcap_QualityMedium_Endcap_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_DataEfficiency_HI_ptup_SYS_1DN_noDDBkg.root");
////FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Endcap_QualityMedium_Endcap_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_DataEfficiency_HI_ptup_SYS_1UP_noDDBkg.root");
////FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Endcap_QualityMedium_Endcap_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_DataEfficiency_HI_mll_SYS_1DN_noDDBkg.root");
////FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Endcap_QualityMedium_Endcap_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_DataEfficiency_HI_mll_SYS_1UP_noDDBkg.root");
////FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Endcap_QualityMedium_Endcap_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_DataEfficiency_HI_noIP_SYS_1DN_noDDBkg.root");
////FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Endcap_QualityMedium_Endcap_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_DataEfficiency_HI_noIP_SYS_1UP_noDDBkg.root");
////FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Endcap_QualityMedium_Endcap_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_DataEfficiency_HI_isoTightTrackOnly_SYS_1DN_noDDBkg.root");
////FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Endcap_QualityMedium_Endcap_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_DataEfficiency_HI_isoTightTrackOnly_SYS_1UP_noDDBkg.root");
////FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Endcap_QualityMedium_Endcap_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_DataEfficiency_HI_isoTight_SYS_1DN_noDDBkg.root");
////FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Endcap_QualityMedium_Endcap_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_DataEfficiency_HI_isoTight_SYS_1UP_noDDBkg.root");
////FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Endcap_QualityMedium_Endcap_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_DataEfficiency_STAT_1DN_noDDBkg.root");
////FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Endcap_QualityMedium_Endcap_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_DataEfficiency_STAT_1UP_noDDBkg.root");
////FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Endcap_QualityMedium_Endcap_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_DataEfficiency_TOTSYS_1DN_noDDBkg.root");
////FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Endcap_QualityMedium_Endcap_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_DataEfficiency_TOTSYS_1UP_noDDBkg.root");
////FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Endcap_QualityMedium_Endcap_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_MCEfficiency_noDDBkg.root");
////FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Endcap_QualityMedium_Endcap_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_MCEfficiency_HI_dphill_SYS_1DN_noDDBkg.root");
////FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Endcap_QualityMedium_Endcap_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_MCEfficiency_HI_dphill_SYS_1UP_noDDBkg.root");
////FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Endcap_QualityMedium_Endcap_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_MCEfficiency_HI_mupos_SYS_1DN_noDDBkg.root");
////FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Endcap_QualityMedium_Endcap_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_MCEfficiency_HI_mupos_SYS_1UP_noDDBkg.root");
////FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Endcap_QualityMedium_Endcap_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_MCEfficiency_HI_muneg_SYS_1DN_noDDBkg.root");
////FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Endcap_QualityMedium_Endcap_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_MCEfficiency_HI_muneg_SYS_1UP_noDDBkg.root");
////FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Endcap_QualityMedium_Endcap_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_MCEfficiency_HI_ptdw_SYS_1DN_noDDBkg.root");
////FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Endcap_QualityMedium_Endcap_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_MCEfficiency_HI_ptdw_SYS_1UP_noDDBkg.root");
////FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Endcap_QualityMedium_Endcap_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_MCEfficiency_HI_ptup_SYS_1DN_noDDBkg.root");
////FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Endcap_QualityMedium_Endcap_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_MCEfficiency_HI_ptup_SYS_1UP_noDDBkg.root");
////FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Endcap_QualityMedium_Endcap_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_MCEfficiency_HI_mll_SYS_1DN_noDDBkg.root");
////FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Endcap_QualityMedium_Endcap_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_MCEfficiency_HI_mll_SYS_1UP_noDDBkg.root");
////FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Endcap_QualityMedium_Endcap_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_MCEfficiency_HI_noIP_SYS_1DN_noDDBkg.root");
////FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Endcap_QualityMedium_Endcap_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_MCEfficiency_HI_noIP_SYS_1UP_noDDBkg.root");
////FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Endcap_QualityMedium_Endcap_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_MCEfficiency_HI_isoTightTrackOnly_SYS_1DN_noDDBkg.root");
////FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Endcap_QualityMedium_Endcap_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_MCEfficiency_HI_isoTightTrackOnly_SYS_1UP_noDDBkg.root");
////FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Endcap_QualityMedium_Endcap_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_MCEfficiency_HI_isoTight_SYS_1DN_noDDBkg.root");
////FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Endcap_QualityMedium_Endcap_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_MCEfficiency_HI_isoTight_SYS_1UP_noDDBkg.root");
////FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Endcap_QualityMedium_Endcap_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_MCEfficiency_STAT_1DN_noDDBkg.root");
////FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Endcap_QualityMedium_Endcap_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_MCEfficiency_STAT_1UP_noDDBkg.root");
////FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Endcap_QualityMedium_Endcap_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_MCEfficiency_TOTSYS_1DN_noDDBkg.root");
////FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Endcap_QualityMedium_Endcap_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_MCEfficiency_TOTSYS_1UP_noDDBkg.root");
/*
FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Barrel_QualityMedium_Barrel_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_ScaleFactor_noDDBkg.root");
FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Barrel_QualityMedium_Barrel_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_ScaleFactor_HI_dphill_SYS_1DN_noDDBkg.root");
FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Barrel_QualityMedium_Barrel_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_ScaleFactor_HI_dphill_SYS_1UP_noDDBkg.root");
FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Barrel_QualityMedium_Barrel_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_ScaleFactor_HI_mupos_SYS_1DN_noDDBkg.root");
FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Barrel_QualityMedium_Barrel_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_ScaleFactor_HI_mupos_SYS_1UP_noDDBkg.root");
FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Barrel_QualityMedium_Barrel_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_ScaleFactor_HI_muneg_SYS_1DN_noDDBkg.root");
FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Barrel_QualityMedium_Barrel_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_ScaleFactor_HI_muneg_SYS_1UP_noDDBkg.root");
FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Barrel_QualityMedium_Barrel_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_ScaleFactor_HI_ptdw_SYS_1DN_noDDBkg.root");
FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Barrel_QualityMedium_Barrel_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_ScaleFactor_HI_ptdw_SYS_1UP_noDDBkg.root");
FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Barrel_QualityMedium_Barrel_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_ScaleFactor_HI_ptup_SYS_1DN_noDDBkg.root");
FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Barrel_QualityMedium_Barrel_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_ScaleFactor_HI_ptup_SYS_1UP_noDDBkg.root");
FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Barrel_QualityMedium_Barrel_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_ScaleFactor_HI_mll_SYS_1DN_noDDBkg.root");
FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Barrel_QualityMedium_Barrel_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_ScaleFactor_HI_mll_SYS_1UP_noDDBkg.root");
FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Barrel_QualityMedium_Barrel_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_ScaleFactor_HI_noIP_SYS_1DN_noDDBkg.root");
FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Barrel_QualityMedium_Barrel_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_ScaleFactor_HI_noIP_SYS_1UP_noDDBkg.root");
FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Barrel_QualityMedium_Barrel_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_ScaleFactor_HI_isoTightTrackOnly_SYS_1DN_noDDBkg.root");
FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Barrel_QualityMedium_Barrel_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_ScaleFactor_HI_isoTightTrackOnly_SYS_1UP_noDDBkg.root");
FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Barrel_QualityMedium_Barrel_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_ScaleFactor_HI_isoTight_SYS_1DN_noDDBkg.root");
FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Barrel_QualityMedium_Barrel_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_ScaleFactor_HI_isoTight_SYS_1UP_noDDBkg.root");
FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Barrel_QualityMedium_Barrel_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_ScaleFactor_STAT_1DN_noDDBkg.root");
FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Barrel_QualityMedium_Barrel_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_ScaleFactor_STAT_1UP_noDDBkg.root");
FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Barrel_QualityMedium_Barrel_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_ScaleFactor_TOTSYS_1DN_noDDBkg.root");
FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Barrel_QualityMedium_Barrel_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_ScaleFactor_TOTSYS_1UP_noDDBkg.root");
FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Barrel_QualityMedium_Barrel_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_DataEfficiency_noDDBkg.root");
FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Barrel_QualityMedium_Barrel_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_DataEfficiency_HI_dphill_SYS_1DN_noDDBkg.root");
FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Barrel_QualityMedium_Barrel_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_DataEfficiency_HI_dphill_SYS_1UP_noDDBkg.root");
FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Barrel_QualityMedium_Barrel_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_DataEfficiency_HI_mupos_SYS_1DN_noDDBkg.root");
FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Barrel_QualityMedium_Barrel_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_DataEfficiency_HI_mupos_SYS_1UP_noDDBkg.root");
FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Barrel_QualityMedium_Barrel_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_DataEfficiency_HI_muneg_SYS_1DN_noDDBkg.root");
FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Barrel_QualityMedium_Barrel_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_DataEfficiency_HI_muneg_SYS_1UP_noDDBkg.root");
FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Barrel_QualityMedium_Barrel_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_DataEfficiency_HI_ptdw_SYS_1DN_noDDBkg.root");
FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Barrel_QualityMedium_Barrel_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_DataEfficiency_HI_ptdw_SYS_1UP_noDDBkg.root");
FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Barrel_QualityMedium_Barrel_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_DataEfficiency_HI_ptup_SYS_1DN_noDDBkg.root");
FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Barrel_QualityMedium_Barrel_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_DataEfficiency_HI_ptup_SYS_1UP_noDDBkg.root");
FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Barrel_QualityMedium_Barrel_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_DataEfficiency_HI_mll_SYS_1DN_noDDBkg.root");
FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Barrel_QualityMedium_Barrel_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_DataEfficiency_HI_mll_SYS_1UP_noDDBkg.root");
FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Barrel_QualityMedium_Barrel_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_DataEfficiency_HI_noIP_SYS_1DN_noDDBkg.root");
FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Barrel_QualityMedium_Barrel_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_DataEfficiency_HI_noIP_SYS_1UP_noDDBkg.root");
FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Barrel_QualityMedium_Barrel_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_DataEfficiency_HI_isoTightTrackOnly_SYS_1DN_noDDBkg.root");
FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Barrel_QualityMedium_Barrel_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_DataEfficiency_HI_isoTightTrackOnly_SYS_1UP_noDDBkg.root");
FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Barrel_QualityMedium_Barrel_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_DataEfficiency_HI_isoTight_SYS_1DN_noDDBkg.root");
FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Barrel_QualityMedium_Barrel_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_DataEfficiency_HI_isoTight_SYS_1UP_noDDBkg.root");
FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Barrel_QualityMedium_Barrel_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_DataEfficiency_STAT_1DN_noDDBkg.root");
FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Barrel_QualityMedium_Barrel_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_DataEfficiency_STAT_1UP_noDDBkg.root");
FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Barrel_QualityMedium_Barrel_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_DataEfficiency_TOTSYS_1DN_noDDBkg.root");
FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Barrel_QualityMedium_Barrel_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_DataEfficiency_TOTSYS_1UP_noDDBkg.root");
FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Barrel_QualityMedium_Barrel_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_MCEfficiency_noDDBkg.root");
FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Barrel_QualityMedium_Barrel_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_MCEfficiency_HI_dphill_SYS_1DN_noDDBkg.root");
FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Barrel_QualityMedium_Barrel_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_MCEfficiency_HI_dphill_SYS_1UP_noDDBkg.root");
FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Barrel_QualityMedium_Barrel_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_MCEfficiency_HI_mupos_SYS_1DN_noDDBkg.root");
FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Barrel_QualityMedium_Barrel_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_MCEfficiency_HI_mupos_SYS_1UP_noDDBkg.root");
FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Barrel_QualityMedium_Barrel_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_MCEfficiency_HI_muneg_SYS_1DN_noDDBkg.root");
FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Barrel_QualityMedium_Barrel_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_MCEfficiency_HI_muneg_SYS_1UP_noDDBkg.root");
FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Barrel_QualityMedium_Barrel_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_MCEfficiency_HI_ptdw_SYS_1DN_noDDBkg.root");
FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Barrel_QualityMedium_Barrel_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_MCEfficiency_HI_ptdw_SYS_1UP_noDDBkg.root");
FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Barrel_QualityMedium_Barrel_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_MCEfficiency_HI_ptup_SYS_1DN_noDDBkg.root");
FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Barrel_QualityMedium_Barrel_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_MCEfficiency_HI_ptup_SYS_1UP_noDDBkg.root");
FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Barrel_QualityMedium_Barrel_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_MCEfficiency_HI_mll_SYS_1DN_noDDBkg.root");
FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Barrel_QualityMedium_Barrel_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_MCEfficiency_HI_mll_SYS_1UP_noDDBkg.root");
FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Barrel_QualityMedium_Barrel_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_MCEfficiency_HI_noIP_SYS_1DN_noDDBkg.root");
FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Barrel_QualityMedium_Barrel_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_MCEfficiency_HI_noIP_SYS_1UP_noDDBkg.root");
FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Barrel_QualityMedium_Barrel_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_MCEfficiency_HI_isoTightTrackOnly_SYS_1DN_noDDBkg.root");
FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Barrel_QualityMedium_Barrel_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_MCEfficiency_HI_isoTightTrackOnly_SYS_1UP_noDDBkg.root");
FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Barrel_QualityMedium_Barrel_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_MCEfficiency_HI_isoTight_SYS_1DN_noDDBkg.root");
FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Barrel_QualityMedium_Barrel_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_MCEfficiency_HI_isoTight_SYS_1UP_noDDBkg.root");
FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Barrel_QualityMedium_Barrel_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_MCEfficiency_STAT_1DN_noDDBkg.root");
FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Barrel_QualityMedium_Barrel_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_MCEfficiency_STAT_1UP_noDDBkg.root");
FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Barrel_QualityMedium_Barrel_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_MCEfficiency_TOTSYS_1DN_noDDBkg.root");
FileList.push_back("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/Eff_etaphi_coarse_Barrel_QualityMedium_Barrel_HLT_mu15_OR_HLT_mu15_L1MU6_OR_HLT_mu15_L1MU10_MCEfficiency_TOTSYS_1UP_noDDBkg.root");
*/
TFile * rfile;
TFile * rfileBarrel;
TH2D * h;
TH2D * h_clone;
TH2D * hBarrel;
vector<TCanvas*> Cans;
TCanvas * can;
TString CanName;
TString NameBarrel;
TString Zaxis;
Int_t x,y,z;
Int_t MaxBin;
TLatex * t;
TLatex * t2;
TString latex;

for (int i = 0; i < FileList.size();i++){
//for (int i = 0; i < 1;i++){
    rfile = new TFile(FileList[i].Data(), "read");
    h = (TH2D*)rfile->Get("SF");
    CanName = FileList[i].Data();
    //CanName = CanName.ReplaceAll("./new_SFs_v8/eff_trig_pPb2D_coarse_v9/", "");
    CanName = CanName.ReplaceAll("./new_SFs_v8/eff_trig_pPb2D_pub_all_stat/", "");
    CanName = CanName.ReplaceAll(".root", "");
    can = new TCanvas(CanName.Data(), CanName.Data(), 0, 0, 1600, 1600);
    h->SetName(TString::Format("h_%s", CanName.Data() ));  
    can->cd();
    gStyle->SetOptStat(0);
    gPad->SetRightMargin(0.3);
    gPad->SetLeftMargin(0.1);
    gPad->SetBottomMargin(0.1);
    gPad->SetTopMargin(0.1);
    h->GetYaxis()->SetTitleOffset(0.9);
    h->GetXaxis()->SetTitleOffset(1.);
    h->GetZaxis()->SetTitleOffset(1.2);
    //h->GetZaxis()->SetMaxDigits(3);
    Zaxis = h->GetZaxis()->GetTitle();
    Zaxis = Zaxis.ReplaceAll("uncert","unc");
    Zaxis = Zaxis.ReplaceAll("Efficiency","Eff.");
    Zaxis = Zaxis.ReplaceAll("ScaleFactor","SF");
    //h->SetTitle(Zaxis.Data());
    h->GetZaxis()->SetTitle(Zaxis.Data());

    NameBarrel = FileList[i].ReplaceAll("Endcap", "Barrel");
    cout << NameBarrel.Data() << endl;
    rfileBarrel = new TFile(NameBarrel.Data(), "read");
    hBarrel = (TH2D*)rfileBarrel->Get("SF");
    hBarrel->SetName(TString::Format("hBarrel_%s", CanName.Data() ));  
    hBarrel->GetYaxis()->SetTitleOffset(0.9);
    hBarrel->GetXaxis()->SetTitleOffset(1.);
    hBarrel->GetZaxis()->SetTitleOffset(1.2);
    //hBarrel->SetTitle(hBarrel->GetZaxis()->GetTitle());
    hBarrel->GetZaxis()->SetTitle("");
    //h->SetMaximum(FindMax(h,hBarrel));
    //h->SetMinimum(FindMin(h,hBarrel));
    //cout << h->GetName() << endl;
    //cout << FindMax(h,hBarrel) << endl;
    //cout << FindMin(h,hBarrel) << endl;
    h_clone = (TH2D*)h->Clone(TString::Format("%s_slone", h->GetName()));
    for (int k = 2; k <= 3; k++){
        for (int l = 1; l <= h_clone->GetYaxis()->GetNbins(); l++){
            h_clone->SetBinContent(k,l, hBarrel->GetBinContent(k-1,l) );
        }
    }


    MaxBin = h_clone->GetMaximumBin();
    h_clone->GetBinXYZ(MaxBin, x, y, z);
    h_clone->SetMaximum(h_clone->GetBinContent(x,y));
    MaxBin = h_clone->GetMinimumBin();
    h_clone->GetBinXYZ(MaxBin, x, y, z);
    h_clone->SetMinimum(h_clone->GetBinContent(x,y));
    h_clone->GetYaxis()->SetTitleOffset(0.9);
    h_clone->GetXaxis()->SetTitleOffset(1.);
    h_clone->GetZaxis()->SetTitleOffset(1.2);
    h_clone->GetZaxis()->SetTitle(Zaxis.Data());
    //h_clone->SetTitle(h->GetName());
    latex = h->GetName();
    latex = latex.ReplaceAll("h_Eff_etaphi_coarse_Endcap_QualityMedium_Endcap_HLT_mu15_comb_", "");
    latex = latex.ReplaceAll("_", " ");
    latex = latex.ReplaceAll("noDDBkg", "");
    latex = latex.ReplaceAll("Efficiency", " Eff.");
    latex = latex.ReplaceAll("ScaleFactor", "SF");
    //latex = latex.ReplaceAll("Endcap", "");
    //latex = latex.ReplaceAll("  ", " ");
    //latex = latex.ReplaceAll("MediumQuality", "");
    t = new TLatex( 0.5, 3.6,"Medium WP, HLT_mu15_comb");
    t2 = new TLatex(0.5, 3.2,TString::Format("%s %s", latex.Data(), ""));
    TLatex * l = new TLatex(-2.5, 3.6,"#bf{#it{ATLAS}} Internal ");
    TLatex * l2 = new TLatex(-2.5, 3.2,"pPb #sqrt{s}=8.16 TeV, 165 nb^{-1}");

    h_clone->SetMarkerColor(2);
    //h_clone->SetMarkerSize(1.3);
    h_clone->SetMarkerSize(2.5);
    
    gStyle->SetPaintTextFormat("0.2f");
    h_clone->Draw("colz text");
    t->Draw("same");
    t2->Draw("same");
    l->Draw("same");
    l2->Draw("same");
    //TLatex * l = new TLatex();
    //l->SetNDC();
    //l->SetTextColor(1);
    //l->DrawLatex(0.2, 0.95, "#bf{#it{ATLAS}} Internal ");
    //TLatex * l2 = new TLatex();
    //l2->SetNDC();
    //l2->SetTextColor(1);
    //l2->DrawLatex(0.2, 0.9, "#sqrt{s}=8.16 TeV, 170 nb^{-1}");
    //TLatex * l3 = new TLatex();
    //l3->SetNDC();
    //l3->SetTextColor(1);
    //l3->DrawLatex(0.2, 0.77, ExtraText);
    //hBarrel->Draw("colz text same");
    can->RedrawAxis();
    TPaletteAxis *palette = (TPaletteAxis*)h_clone->GetListOfFunctions()->FindObject("palette");
    if (palette) {
      palette->SetX1NDC(0.71);
      palette->SetY1NDC(0.1);
      palette->SetX2NDC(0.76);
      palette->SetY2NDC(0.9);
      gPad->Modified(); gPad->Update(); // make sure it's really (re)drawn
    }
    TPaletteAxis *palette2 = (TPaletteAxis*)h_clone->GetListOfFunctions()->FindObject("palette");
    if (palette2) {
      palette2->SetX1NDC(0.71);
      palette2->SetY1NDC(0.1);
      palette2->SetX2NDC(0.76);
      palette2->SetY2NDC(0.9);
      gPad->Modified(); gPad->Update(); // make sure it's really (re)drawn
    }
    Cans.push_back(can);

}

for (int i = 0; i < Cans.size();i++){
    //Cans[i]->SaveAs(TString::Format("./trigger/%s.png", Cans[i]->GetName() ));
    //Cans[i]->SaveAs(TString::Format("./trigger/%s.pdf", Cans[i]->GetName() ));
    Cans[i]->SaveAs(TString::Format("./trigger_all_stats/%s.png", Cans[i]->GetName() ));
    Cans[i]->SaveAs(TString::Format("./trigger_all_stats/%s.pdf", Cans[i]->GetName() ));
}

    return 0;
}
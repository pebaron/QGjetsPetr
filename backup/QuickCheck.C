int QuickCheck(){
    TFile * file1 = new TFile("eff_trig_pPb_barrel/Eff_etaphi_fine_Barrel_QualityHighPt_Barrel_HLT_mu15_DataEfficiency_noDDBkg.root ", "read");
    TFile * file1err = new TFile("eff_trig_pPb_barrel/Eff_etaphi_fine_Barrel_QualityHighPt_Barrel_HLT_mu15_DataEfficiency_STAT_1UP_noDDBkg.root", "read");
    TFile * file2err = new TFile("eff_trig_pPb_barrel/Eff_etaphi_fine_Barrel_QualityHighPt_Barrel_HLT_mu15_DataEfficiency_STAT_1DN_noDDBkg.root", "read");

    TH2D * nominal = (TH2D*) file1->Get("SF");
    TH2D * err = (TH2D*) file1err->Get("SF");
    TH2D * err2 = (TH2D*) file2err->Get("SF");

    cout << nominal->GetBinContent(1,1) << " unc: " << nominal->GetBinError(1,1) << endl;
    cout << err->GetBinContent(1,1) << endl; //" unc: " << nominal->GetBinError(1,1) << endl;
    cout << err2->GetBinContent(1,1) << endl; //" unc: " << nominal->GetBinError(1,1) << endl;

    //76.5625*(1.+7.41711/100.)
    //effUP/DOWN = GetBinContent() * (1.+ GetBinContent_UP/DOWN()/100.);

    return 0;

     

}
int CheckPt(){

    TFile * file1 = new TFile("/disk0/QGjetsPetr/run/files_test/temp/Energy_900_NEvt_500000_Seed_61972970_PtWindow_50_PDF_MMHT2014lo68cl_nohadr/Energy_900_NEvt_500000_Seed_61972970_PtWindow_50_PDF_MMHT2014lo68cl_nohadr-S61972970.root", "read");
    TFile * file2 = new TFile("/disk0/QGjetsPetr/run/files_test/temp/Hadr_Pt_Test_Energy_900_NEvt_200000_Seed_61972970_PtWindow_50_PDF_MMHT2014lo68cl_hadr/Hadr_Pt_Test_Energy_900_NEvt_200000_Seed_61972970_PtWindow_50_PDF_MMHT2014lo68cl_hadr-S61972970.root", "read");

    TTree * tree1 = (TTree*)file1->Get("MC_DIJET_PB_CH");
    TTree * tree2 = (TTree*)file2->Get("MC_DIJET_PB_CH");
    tree1->SetName("MC_DIJET_PB_CH_nohadr");
    tree2->SetName("MC_DIJET_PB_CH_hadr");

    tree1->AddFriend(tree2);

    //tree1->Draw("MC_DIJET_PB_CH_nohadr.QuarkFractionEta[0]:MC_DIJET_PB_CH_hadr.no_cut_FastJets10Eta[0]", "(MC_DIJET_PB_CH_hadr.no_cut_FastJets10Pt>44)&&(0.5*(MC_DIJET_PB_CH_hadr.no_cut_FastJets10Pt[0]+MC_DIJET_PB_CH_hadr.no_cut_FastJets10Pt[0])<50.)", "colz");
    tree1->Draw("MC_DIJET_PB_CH_nohadr.GluonAndQuarkFractionPt[0]:MC_DIJET_PB_CH_hadr.no_cut_FastJets10Pt[0]", "(MC_DIJET_PB_CH_nohadr.GluonAndQuarkFractionEta[0] > 0)&&(MC_DIJET_PB_CH_hadr.no_cut_FastJets10Eta[0] > 0)", "colz");

    return 0;
}
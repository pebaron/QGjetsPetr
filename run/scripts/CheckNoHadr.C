int CheckNoHadr(){
      TChain * chain = new TChain("MC_DIJET_PB_CH");

chain->Add("../files_test/Energy_13000_NEvt_500000_Seed_61972970_PtWindow_175_PDF_MMHT2014lo68cl_nohadr/test.root");
chain->Add("../files_test/Energy_13000_NEvt_500000_Seed_61972970_PtWindow_125_PDF_MMHT2014lo68cl_nohadr/test.root");
chain->Add("../files_test/Energy_13000_NEvt_500000_Seed_61972970_PtWindow_150_PDF_MMHT2014lo68cl_nohadr/test.root");
chain->Add("../files_test/Energy_13000_NEvt_500000_Seed_61972970_PtWindow_75_PDF_MMHT2014lo68cl_nohadr/test.root");
chain->Add("../files_test/Energy_13000_NEvt_500000_Seed_61972970_PtWindow_100_PDF_MMHT2014lo68cl_nohadr/test.root");
chain->Add("../files_test/Energy_13000_NEvt_500000_Seed_61972970_PtWindow_50_PDF_MMHT2014lo68cl_nohadr/test.root");
chain->Add("../files_test/Energy_13000_NEvt_500000_Seed_61972970_PtWindow_25_PDF_MMHT2014lo68cl_nohadr/test.root");
chain->Add("../files_test/Energy_13000_NEvt_500000_Seed_61972970_PtWindow_0_PDF_MMHT2014lo68cl_nohadr/test.root");

return 0;


}
int GetBining(){
  TFile * myfile = new TFile("muontrigger_sf_2016_mc16a_v05.root","read");
  TH2F * etaphi_fine_endcap = (TH2F*)myfile->Get("Medium/PeriodB/HLT_mu15/eff_etaphi_fine_endcap_data_nominal") ;
  TH2F * etaphi_fine_barrel = (TH2F*)myfile->Get("Medium/PeriodB/HLT_mu15/eff_etaphi_fine_barrel_data_nominal") ;
  TH2F * etaphi_coarse_barrel = (TH2F*)myfile->Get("Medium/PeriodB/HLT_mu15/eff_etaphi_coarse_barrel_data_nominal") ;
  TH2F * etaphi_coarse_endcap = (TH2F*)myfile->Get("Medium/PeriodB/HLT_mu15/eff_etaphi_coarse_endcap_data_nominal") ;

  //vector<Double_t> xbins = {0.0, 0.223027, 0.251356, 0.286209, 0.329087, 0.381838, 0.446737, 0.52658, 0.624807, 0.745654, 0.894328, 1.07724, 1.30226, 1.57911, 1.9197, 2.33872, 2.85423, 3.48844, 4.26869, 5.22861, 6.40957, 7.86247, 9.64993, 11.849, 14.5544, 17.8828, 21.9776, 27.0153, 33.2131, 40.838, 50.2187, 61.7595, 75.9578, 93.4254, 114.915, 141.354, 173.88, 213.896, 263.127, 323.694, 398.207, 489.879, 602.66, 741.41, 912.111, 1122.12, 1380.48, 1698.34, 2089.4, 2570.5, 3162.38, 3890.55, 4786.4, 5888.54, 7244.46, 8912.61, 10964.9, 13489.7, 16596, 20417.5, 25119, 30903.1, 38019, 46773.6, 57544.1, 70794.7, 87096.5, 107152, 131826, 162181, 199526, 245471, 301995, 371535, 457088, 562341, 691831, 851138, 1.04713e+06, 1.28825e+06, 1.58489e+06, 1.94984e+06, 2.39883e+06, 2.95121e+06, 3.63078e+06, 4.46684e+06, 5.49541e+06, 6.76083e+06, 8.31764e+06, 1.02329e+07, 1.25893e+07, 1.54882e+07, 1.90546e+07, 2.34423e+07, 2.88403e+07, 3.54813e+07, 4.36516e+07, 5.37032e+07, 6.60693e+07, 8.12831e+07, 1e+08};

  //x-title Probe #eta
  //y-title Probe #phi
  for (int i=1; i<= etaphi_fine_endcap->GetXaxis()->GetNbins();i++){
    if (i ==1){
      cout << "vector<Double_t> etaphi_fine_endcap_xbins = {" ;
    }
    if (i < etaphi_fine_endcap->GetXaxis()->GetNbins()){
      cout << etaphi_fine_endcap->GetXaxis()->GetBinLowEdge(i) << " ";
    }else{
      cout << etaphi_fine_endcap->GetXaxis()->GetBinLowEdge(i) << " ";
      cout << etaphi_fine_endcap->GetXaxis()->GetBinUpEdge(i) << "}; " << endl;
    }
    
  }

  for (int i=1; i<= etaphi_fine_endcap->GetYaxis()->GetNbins();i++){
    if (i ==1){
      cout << "vector<Double_t> etaphi_fine_endcap_ybins = {" ;
    }
    if (i < etaphi_fine_endcap->GetYaxis()->GetNbins()){
      cout << etaphi_fine_endcap->GetYaxis()->GetBinLowEdge(i) << " ";
    }else{
      cout << etaphi_fine_endcap->GetYaxis()->GetBinLowEdge(i) << " ";
      cout << etaphi_fine_endcap->GetYaxis()->GetBinUpEdge(i) << "}; " << endl;
    }
    
  }

//barrel 
  for (int i=1; i<= etaphi_fine_barrel->GetXaxis()->GetNbins();i++){
    if (i ==1){
      cout << "vector<Double_t> etaphi_fine_barrel_xbins = {" ;
    }
    if (i < etaphi_fine_barrel->GetXaxis()->GetNbins()){
      cout << etaphi_fine_barrel->GetXaxis()->GetBinLowEdge(i) << " ";
    }else{
      cout << etaphi_fine_barrel->GetXaxis()->GetBinLowEdge(i) << " ";
      cout << etaphi_fine_barrel->GetXaxis()->GetBinUpEdge(i) << "}; " << endl;
    }
    
  }

  for (int i=1; i<= etaphi_fine_barrel->GetYaxis()->GetNbins();i++){
    if (i ==1){
      cout << "vector<Double_t> etaphi_fine_barrel_ybins = {" ;
    }
    if (i < etaphi_fine_barrel->GetYaxis()->GetNbins()){
      cout << etaphi_fine_barrel->GetYaxis()->GetBinLowEdge(i) << " ";
    }else{
      cout << etaphi_fine_barrel->GetYaxis()->GetBinLowEdge(i) << " ";
      cout << etaphi_fine_barrel->GetYaxis()->GetBinUpEdge(i) << "}; " << endl;
    }
    
  }
// and coarse binning

  for (int i=1; i<= etaphi_coarse_endcap->GetXaxis()->GetNbins();i++){
    if (i ==1){
      cout << "vector<Double_t> etaphi_coarse_endcap_xbins = {" ;
    }
    if (i < etaphi_coarse_endcap->GetXaxis()->GetNbins()){
      cout << etaphi_coarse_endcap->GetXaxis()->GetBinLowEdge(i) << " ";
    }else{
      cout << etaphi_coarse_endcap->GetXaxis()->GetBinLowEdge(i) << " ";
      cout << etaphi_coarse_endcap->GetXaxis()->GetBinUpEdge(i) << "}; " << endl;
    }
    
  }

  for (int i=1; i<= etaphi_coarse_endcap->GetYaxis()->GetNbins();i++){
    if (i ==1){
      cout << "vector<Double_t> etaphi_coarse_endcap_ybins = {" ;
    }
    if (i < etaphi_coarse_endcap->GetYaxis()->GetNbins()){
      cout << etaphi_coarse_endcap->GetYaxis()->GetBinLowEdge(i) << " ";
    }else{
      cout << etaphi_coarse_endcap->GetYaxis()->GetBinLowEdge(i) << " ";
      cout << etaphi_coarse_endcap->GetYaxis()->GetBinUpEdge(i) << "}; " << endl;
    }
    
  }

//barrel 
  for (int i=1; i<= etaphi_coarse_barrel->GetXaxis()->GetNbins();i++){
    if (i ==1){
      cout << "vector<Double_t> etaphi_coarse_barrel_xbins = {" ;
    }
    if (i < etaphi_coarse_barrel->GetXaxis()->GetNbins()){
      cout << etaphi_coarse_barrel->GetXaxis()->GetBinLowEdge(i) << " ";
    }else{
      cout << etaphi_coarse_barrel->GetXaxis()->GetBinLowEdge(i) << " ";
      cout << etaphi_coarse_barrel->GetXaxis()->GetBinUpEdge(i) << "}; " << endl;
    }
    
  }

  for (int i=1; i<= etaphi_coarse_barrel->GetYaxis()->GetNbins();i++){
    if (i ==1){
      cout << "vector<Double_t> etaphi_coarse_barrel_ybins = {" ;
    }
    if (i < etaphi_coarse_barrel->GetYaxis()->GetNbins()){
      cout << etaphi_coarse_barrel->GetYaxis()->GetBinLowEdge(i) << " ";
    }else{
      cout << etaphi_coarse_barrel->GetYaxis()->GetBinLowEdge(i) << " ";
      cout << etaphi_coarse_barrel->GetYaxis()->GetBinUpEdge(i) << "}; " << endl;
    }
    
  }


    cout << "---------------------------" << endl;
  return 0;
}
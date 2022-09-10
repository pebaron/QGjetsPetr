int PlotTagEffs(TString FileName="analyzed_histos_delphes_SMtt_closure.root"){

    TFile * rfile = new TFile(FileName.Data(), "read");
    TFile * rfileQCD1 = new TFile("analyzed_histos_boosted_QCD_ptj1j2min60_ptj1j2max200.root", "read");
    TFile * rfileQCD2 = new TFile("analyzed_histos_boosted_QCD_ptj1min200_ptj2min60max200.root", "read");
    TFile * rfileQCD3 = new TFile("analyzed_histos_boosted_QCD_pp_2b2j_LO_matched_ptj1j2min200.root", "read");   
    

    TTree * stand_tree = (TTree*)rfile->Get("TTree_TagHistos");
    TTree * ML_tree = (TTree*)rfile->Get("TTree_ML_TagHistos");

    vector<Double_t> bins = {0.,100.,200.,300.,400.,500.,600.,700.,800.,900.,1000.};

    TH1D * Real_ML_nom;
    TH1D * Real_ML_denom;
    TH1D * Fake_ML_nom;
    TH1D * Fake_ML_denom;
    TH1D * Real_Stand_nom;
    TH1D * Real_Stand_denom;
    TH1D * Fake_Stand_nom;
    TH1D * Fake_Stand_denom;

    //QCD
    TH1D * QCD1_Real_ML_nom;
    TH1D * QCD1_Real_ML_denom;
    TH1D * QCD1_Fake_ML_nom;
    TH1D * QCD1_Fake_ML_denom;
    TH1D * QCD1_Real_Stand_nom;
    TH1D * QCD1_Real_Stand_denom;
    TH1D * QCD1_Fake_Stand_nom;
    TH1D * QCD1_Fake_Stand_denom;

    TH1D * QCD2_Real_ML_nom;
    TH1D * QCD2_Real_ML_denom;
    TH1D * QCD2_Fake_ML_nom;
    TH1D * QCD2_Fake_ML_denom;
    TH1D * QCD2_Real_Stand_nom;
    TH1D * QCD2_Real_Stand_denom;
    TH1D * QCD2_Fake_Stand_nom;
    TH1D * QCD2_Fake_Stand_denom;

    TH1D * QCD3_Real_ML_nom;
    TH1D * QCD3_Real_ML_denom;
    TH1D * QCD3_Fake_ML_nom;
    TH1D * QCD3_Fake_ML_denom;
    TH1D * QCD3_Real_Stand_nom;
    TH1D * QCD3_Real_Stand_denom;
    TH1D * QCD3_Fake_Stand_nom;
    TH1D * QCD3_Fake_Stand_denom;

    TTree * QCD1_stand_tree = (TTree*)rfileQCD1->Get("TTree_TagHistos");
    TTree * QCD1_ML_tree = (TTree*)rfileQCD1->Get("TTree_ML_TagHistos");
    TTree * QCD2_stand_tree = (TTree*)rfileQCD2->Get("TTree_TagHistos");
    TTree * QCD2_ML_tree = (TTree*)rfileQCD2->Get("TTree_ML_TagHistos");
    TTree * QCD3_stand_tree = (TTree*)rfileQCD3->Get("TTree_TagHistos");
    TTree * QCD3_ML_tree = (TTree*)rfileQCD3->Get("TTree_ML_TagHistos");

    TString QCD1_ML_TagMatched          ; //e.g.  ML_WTagWtruthMatchedLjetsPtParticle
    TString QCD1_ML_notTagMatched       ; //e.g.  ML_notWTagWtruthMatchedLjetsPtParticle
    TString QCD1_ML_TagNonMatched       ; //e.g.  ML_WTagnonWMatchedLjetsPtParticle
    TString QCD1_ML_notTagNonMatched    ; //e.g.  ML_notWTagnonWMatchedLjetsPtParticle
    TString QCD1_Stand_TagMatched       ; //e.g.  ML_WTagWtruthMatchedLjetsPtParticle
    TString QCD1_Stand_notTagMatched    ; //e.g.  ML_notWTagWtruthMatchedLjetsPtParticle
    TString QCD1_Stand_TagNonMatched    ; //e.g.  ML_WTagnonWMatchedLjetsPtParticle
    TString QCD1_Stand_notTagNonMatched ; //e.g.  ML_notWTagnonWMatchedLjetsPtParticle

    TString QCD2_ML_TagMatched          ; //e.g.  ML_WTagWtruthMatchedLjetsPtParticle
    TString QCD2_ML_notTagMatched       ; //e.g.  ML_notWTagWtruthMatchedLjetsPtParticle
    TString QCD2_ML_TagNonMatched       ; //e.g.  ML_WTagnonWMatchedLjetsPtParticle
    TString QCD2_ML_notTagNonMatched    ; //e.g.  ML_notWTagnonWMatchedLjetsPtParticle
    TString QCD2_Stand_TagMatched       ; //e.g.  ML_WTagWtruthMatchedLjetsPtParticle
    TString QCD2_Stand_notTagMatched    ; //e.g.  ML_notWTagWtruthMatchedLjetsPtParticle
    TString QCD2_Stand_TagNonMatched    ; //e.g.  ML_WTagnonWMatchedLjetsPtParticle
    TString QCD2_Stand_notTagNonMatched ; //e.g.  ML_notWTagnonWMatchedLjetsPtParticle

    TString QCD3_ML_TagMatched          ; //e.g.  ML_WTagWtruthMatchedLjetsPtParticle
    TString QCD3_ML_notTagMatched       ; //e.g.  ML_notWTagWtruthMatchedLjetsPtParticle
    TString QCD3_ML_TagNonMatched       ; //e.g.  ML_WTagnonWMatchedLjetsPtParticle
    TString QCD3_ML_notTagNonMatched    ; //e.g.  ML_notWTagnonWMatchedLjetsPtParticle
    TString QCD3_Stand_TagMatched       ; //e.g.  ML_WTagWtruthMatchedLjetsPtParticle
    TString QCD3_Stand_notTagMatched    ; //e.g.  ML_notWTagWtruthMatchedLjetsPtParticle
    TString QCD3_Stand_TagNonMatched    ; //e.g.  ML_WTagnonWMatchedLjetsPtParticle
    TString QCD3_Stand_notTagNonMatched ; //e.g.  ML_notWTagnonWMatchedLjetsPtParticle
    //end of QCD

    vector<TString> level;
    level.push_back("Detector");
    level.push_back("Particle");
    vector<TString> particle;
    particle.push_back("Top");
    particle.push_back("W");


    TString ML_TagMatched          ; //e.g.  ML_WTagWtruthMatchedLjetsPtParticle
    TString ML_notTagMatched       ; //e.g.  ML_notWTagWtruthMatchedLjetsPtParticle
    TString ML_TagNonMatched       ; //e.g.  ML_WTagnonWMatchedLjetsPtParticle
    TString ML_notTagNonMatched    ; //e.g.  ML_notWTagnonWMatchedLjetsPtParticle
    TString Stand_TagMatched       ; //e.g.  ML_WTagWtruthMatchedLjetsPtParticle
    TString Stand_notTagMatched    ; //e.g.  ML_notWTagWtruthMatchedLjetsPtParticle
    TString Stand_TagNonMatched    ; //e.g.  ML_WTagnonWMatchedLjetsPtParticle
    TString Stand_notTagNonMatched ; //e.g.  ML_notWTagnonWMatchedLjetsPtParticle

    vector<TH1D*> ML_histos;
    vector<TH1D*> Stand_histos;

    vector<TH1D*> QCD1_ML_histos;
    vector<TH1D*> QCD1_Stand_histos;
    vector<TH1D*> QCD2_ML_histos;
    vector<TH1D*> QCD2_Stand_histos;
    vector<TH1D*> QCD3_ML_histos;
    vector<TH1D*> QCD3_Stand_histos;

    vector<TCanvas*> Cans;
    TCanvas * TempCan;
    vector<TLegend*> Legs;
    TLegend * TempLeg;

    TEfficiency * Eff_Real_ML_nom   ;
    TEfficiency * Eff_Fake_ML_nom   ;
    TEfficiency * Eff_Real_Stand_nom;
    TEfficiency * Eff_Fake_Stand_nom;

    TEfficiency * QCD_Eff_Real_ML_nom   ;
    TEfficiency * QCD_Eff_Fake_ML_nom   ;
    TEfficiency * QCD_Eff_Real_Stand_nom;
    TEfficiency * QCD_Eff_Fake_Stand_nom;

    FileName = FileName.ReplaceAll(".root" ,"");

    Double_t x, y;

    for (int i = 0; i < level.size();i++){
        for (int j = 0; j < particle.size();j++){
            if (particle[j].Contains("Top")){
                ML_TagMatched          = TString::Format("ML_TagHistosML_%sTagttruthMatchedLjetsPt%s_denser", particle[j].Data(), level[i].Data() );
                ML_notTagMatched       = TString::Format("ML_TagHistosML_not%sTagttruthMatchedLjetsPt%s_denser", particle[j].Data(), level[i].Data() );
                ML_TagNonMatched       = TString::Format("ML_TagHistosML_%sTagnontMatchedLjetsPt%s_denser", particle[j].Data(), level[i].Data() );
                ML_notTagNonMatched    = TString::Format("ML_TagHistosML_not%sTagnontMatchedLjetsPt%s_denser", particle[j].Data(), level[i].Data() );
                Stand_TagMatched       = TString::Format("TagHistos%sTagttruthMatchedLjetsPt%s_denser", particle[j].Data(), level[i].Data() );
                Stand_notTagMatched    = TString::Format("TagHistosnot%sTagttruthMatchedLjetsPt%s_denser", particle[j].Data(), level[i].Data() );
                Stand_TagNonMatched    = TString::Format("TagHistos%sTagnontMatchedLjetsPt%s_denser", particle[j].Data(), level[i].Data() );
                Stand_notTagNonMatched = TString::Format("TagHistosnot%sTagnontMatchedLjetsPt%s_denser", particle[j].Data(), level[i].Data() );

                QCD1_ML_TagMatched          = TString::Format("QCD1_ML_TagHistosML_%sTagttruthMatchedLjetsPt%s_denser", particle[j].Data(), level[i].Data() );
                QCD1_ML_notTagMatched       = TString::Format("QCD1_ML_TagHistosML_not%sTagttruthMatchedLjetsPt%s_denser", particle[j].Data(), level[i].Data() );
                QCD1_ML_TagNonMatched       = TString::Format("QCD1_ML_TagHistosML_%sTagnontMatchedLjetsPt%s_denser", particle[j].Data(), level[i].Data() );
                QCD1_ML_notTagNonMatched    = TString::Format("QCD1_ML_TagHistosML_not%sTagnontMatchedLjetsPt%s_denser", particle[j].Data(), level[i].Data() );
                QCD1_Stand_TagMatched       = TString::Format("QCD1_TagHistos%sTagttruthMatchedLjetsPt%s_denser", particle[j].Data(), level[i].Data() );
                QCD1_Stand_notTagMatched    = TString::Format("QCD1_TagHistosnot%sTagttruthMatchedLjetsPt%s_denser", particle[j].Data(), level[i].Data() );
                QCD1_Stand_TagNonMatched    = TString::Format("QCD1_TagHistos%sTagnontMatchedLjetsPt%s_denser", particle[j].Data(), level[i].Data() );
                QCD1_Stand_notTagNonMatched = TString::Format("QCD1_TagHistosnot%sTagnontMatchedLjetsPt%s_denser", particle[j].Data(), level[i].Data() );

                QCD2_ML_TagMatched          = TString::Format("QCD2_ML_TagHistosML_%sTagttruthMatchedLjetsPt%s_denser", particle[j].Data(), level[i].Data() );
                QCD2_ML_notTagMatched       = TString::Format("QCD2_ML_TagHistosML_not%sTagttruthMatchedLjetsPt%s_denser", particle[j].Data(), level[i].Data() );
                QCD2_ML_TagNonMatched       = TString::Format("QCD2_ML_TagHistosML_%sTagnontMatchedLjetsPt%s_denser", particle[j].Data(), level[i].Data() );
                QCD2_ML_notTagNonMatched    = TString::Format("QCD2_ML_TagHistosML_not%sTagnontMatchedLjetsPt%s_denser", particle[j].Data(), level[i].Data() );
                QCD2_Stand_TagMatched       = TString::Format("QCD2_TagHistos%sTagttruthMatchedLjetsPt%s_denser", particle[j].Data(), level[i].Data() );
                QCD2_Stand_notTagMatched    = TString::Format("QCD2_TagHistosnot%sTagttruthMatchedLjetsPt%s_denser", particle[j].Data(), level[i].Data() );
                QCD2_Stand_TagNonMatched    = TString::Format("QCD2_TagHistos%sTagnontMatchedLjetsPt%s_denser", particle[j].Data(), level[i].Data() );
                QCD2_Stand_notTagNonMatched = TString::Format("QCD2_TagHistosnot%sTagnontMatchedLjetsPt%s_denser", particle[j].Data(), level[i].Data() );

                QCD3_ML_TagMatched          = TString::Format("QCD3_ML_TagHistosML_%sTagttruthMatchedLjetsPt%s_denser", particle[j].Data(), level[i].Data() );
                QCD3_ML_notTagMatched       = TString::Format("QCD3_ML_TagHistosML_not%sTagttruthMatchedLjetsPt%s_denser", particle[j].Data(), level[i].Data() );
                QCD3_ML_TagNonMatched       = TString::Format("QCD3_ML_TagHistosML_%sTagnontMatchedLjetsPt%s_denser", particle[j].Data(), level[i].Data() );
                QCD3_ML_notTagNonMatched    = TString::Format("QCD3_ML_TagHistosML_not%sTagnontMatchedLjetsPt%s_denser", particle[j].Data(), level[i].Data() );
                QCD3_Stand_TagMatched       = TString::Format("QCD3_TagHistos%sTagttruthMatchedLjetsPt%s_denser", particle[j].Data(), level[i].Data() );
                QCD3_Stand_notTagMatched    = TString::Format("QCD3_TagHistosnot%sTagttruthMatchedLjetsPt%s_denser", particle[j].Data(), level[i].Data() );
                QCD3_Stand_TagNonMatched    = TString::Format("QCD3_TagHistos%sTagnontMatchedLjetsPt%s_denser", particle[j].Data(), level[i].Data() );
                QCD3_Stand_notTagNonMatched = TString::Format("QCD3_TagHistosnot%sTagnontMatchedLjetsPt%s_denser", particle[j].Data(), level[i].Data() );
            }else{
                ML_TagMatched          = TString::Format("ML_TagHistosML_%sTag%struthMatchedLjetsPt%s_denser", particle[j].Data(), particle[j].Data(), level[i].Data() );
                ML_notTagMatched       = TString::Format("ML_TagHistosML_not%sTag%struthMatchedLjetsPt%s_denser", particle[j].Data(), particle[j].Data(), level[i].Data() );
                ML_TagNonMatched       = TString::Format("ML_TagHistosML_%sTagnon%sMatchedLjetsPt%s_denser", particle[j].Data(), particle[j].Data(), level[i].Data() );
                ML_notTagNonMatched    = TString::Format("ML_TagHistosML_not%sTagnon%sMatchedLjetsPt%s_denser", particle[j].Data(), particle[j].Data(), level[i].Data() );
                Stand_TagMatched       = TString::Format("TagHistos%sTag%struthMatchedLjetsPt%s_denser", particle[j].Data(), particle[j].Data(), level[i].Data() );
                Stand_notTagMatched    = TString::Format("TagHistosnot%sTag%struthMatchedLjetsPt%s_denser", particle[j].Data(), particle[j].Data(), level[i].Data() );
                Stand_TagNonMatched    = TString::Format("TagHistos%sTagnon%sMatchedLjetsPt%s_denser", particle[j].Data(), particle[j].Data(), level[i].Data() );
                Stand_notTagNonMatched = TString::Format("TagHistosnot%sTagnon%sMatchedLjetsPt%s_denser", particle[j].Data(), particle[j].Data(), level[i].Data() );

                QCD1_ML_TagMatched          = TString::Format("QCD1_ML_TagHistosML_%sTagttruthMatchedLjetsPt%s_denser", particle[j].Data(), level[i].Data() );
                QCD1_ML_notTagMatched       = TString::Format("QCD1_ML_TagHistosML_not%sTagttruthMatchedLjetsPt%s_denser", particle[j].Data(), level[i].Data() );
                QCD1_ML_TagNonMatched       = TString::Format("QCD1_ML_TagHistosML_%sTagnontMatchedLjetsPt%s_denser", particle[j].Data(), level[i].Data() );
                QCD1_ML_notTagNonMatched    = TString::Format("QCD1_ML_TagHistosML_not%sTagnontMatchedLjetsPt%s_denser", particle[j].Data(), level[i].Data() );
                QCD1_Stand_TagMatched       = TString::Format("QCD1_TagHistos%sTagttruthMatchedLjetsPt%s_denser", particle[j].Data(), level[i].Data() );
                QCD1_Stand_notTagMatched    = TString::Format("QCD1_TagHistosnot%sTagttruthMatchedLjetsPt%s_denser", particle[j].Data(), level[i].Data() );
                QCD1_Stand_TagNonMatched    = TString::Format("QCD1_TagHistos%sTagnontMatchedLjetsPt%s_denser", particle[j].Data(), level[i].Data() );
                QCD1_Stand_notTagNonMatched = TString::Format("QCD1_TagHistosnot%sTagnontMatchedLjetsPt%s_denser", particle[j].Data(), level[i].Data() );

                QCD2_ML_TagMatched          = TString::Format("QCD2_ML_TagHistosML_%sTagttruthMatchedLjetsPt%s_denser", particle[j].Data(), level[i].Data() );
                QCD2_ML_notTagMatched       = TString::Format("QCD2_ML_TagHistosML_not%sTagttruthMatchedLjetsPt%s_denser", particle[j].Data(), level[i].Data() );
                QCD2_ML_TagNonMatched       = TString::Format("QCD2_ML_TagHistosML_%sTagnontMatchedLjetsPt%s_denser", particle[j].Data(), level[i].Data() );
                QCD2_ML_notTagNonMatched    = TString::Format("QCD2_ML_TagHistosML_not%sTagnontMatchedLjetsPt%s_denser", particle[j].Data(), level[i].Data() );
                QCD2_Stand_TagMatched       = TString::Format("QCD2_TagHistos%sTagttruthMatchedLjetsPt%s_denser", particle[j].Data(), level[i].Data() );
                QCD2_Stand_notTagMatched    = TString::Format("QCD2_TagHistosnot%sTagttruthMatchedLjetsPt%s_denser", particle[j].Data(), level[i].Data() );
                QCD2_Stand_TagNonMatched    = TString::Format("QCD2_TagHistos%sTagnontMatchedLjetsPt%s_denser", particle[j].Data(), level[i].Data() );
                QCD2_Stand_notTagNonMatched = TString::Format("QCD2_TagHistosnot%sTagnontMatchedLjetsPt%s_denser", particle[j].Data(), level[i].Data() );

                QCD3_ML_TagMatched          = TString::Format("QCD3_ML_TagHistosML_%sTagttruthMatchedLjetsPt%s_denser", particle[j].Data(), level[i].Data() );
                QCD3_ML_notTagMatched       = TString::Format("QCD3_ML_TagHistosML_not%sTagttruthMatchedLjetsPt%s_denser", particle[j].Data(), level[i].Data() );
                QCD3_ML_TagNonMatched       = TString::Format("QCD3_ML_TagHistosML_%sTagnontMatchedLjetsPt%s_denser", particle[j].Data(), level[i].Data() );
                QCD3_ML_notTagNonMatched    = TString::Format("QCD3_ML_TagHistosML_not%sTagnontMatchedLjetsPt%s_denser", particle[j].Data(), level[i].Data() );
                QCD3_Stand_TagMatched       = TString::Format("QCD3_TagHistos%sTagttruthMatchedLjetsPt%s_denser", particle[j].Data(), level[i].Data() );
                QCD3_Stand_notTagMatched    = TString::Format("QCD3_TagHistosnot%sTagttruthMatchedLjetsPt%s_denser", particle[j].Data(), level[i].Data() );
                QCD3_Stand_TagNonMatched    = TString::Format("QCD3_TagHistos%sTagnontMatchedLjetsPt%s_denser", particle[j].Data(), level[i].Data() );
                QCD3_Stand_notTagNonMatched = TString::Format("QCD3_TagHistosnot%sTagnontMatchedLjetsPt%s_denser", particle[j].Data(), level[i].Data() );
            }
        

        Real_ML_nom = new TH1D(ML_TagMatched.Data(), ML_TagMatched.Data(), bins.size() -1 , bins.data() );
        Real_ML_denom = (TH1D*)Real_ML_nom->Clone(ML_notTagMatched.Data() );
        Real_ML_denom->Reset();
        Fake_ML_nom = new TH1D(ML_TagNonMatched.Data(), ML_TagNonMatched.Data(), bins.size() -1 , bins.data() );
        Fake_ML_denom = (TH1D*)Fake_ML_nom->Clone(ML_notTagNonMatched.Data());
        Fake_ML_denom->Reset();

        Real_Stand_nom = new TH1D(Stand_TagMatched.Data(), Stand_TagMatched.Data(), bins.size() -1 , bins.data() );
        Real_Stand_denom = (TH1D*)Real_Stand_nom->Clone(Stand_notTagMatched.Data() );
        Real_Stand_denom->Reset();
        Fake_Stand_nom = new TH1D(Stand_TagNonMatched.Data(), Stand_TagNonMatched.Data(), bins.size() -1 , bins.data() );
        Fake_Stand_denom = (TH1D*)Fake_Stand_nom->Clone(Stand_notTagNonMatched.Data());
        Fake_Stand_denom->Reset();

        //QCD
        QCD1_Real_ML_nom = new TH1D(QCD1_ML_TagMatched.Data(), ML_TagMatched.Data(), bins.size() -1 , bins.data() );
        QCD1_Real_ML_denom = (TH1D*)QCD1_Real_ML_nom->Clone(QCD1_ML_notTagMatched.Data() );

        QCD1_Fake_ML_nom = new TH1D(QCD1_ML_TagNonMatched.Data(), ML_TagNonMatched.Data(), bins.size() -1 , bins.data() );
        QCD1_Fake_ML_denom = (TH1D*)QCD1_Fake_ML_nom->Clone(QCD1_ML_notTagNonMatched.Data());

        QCD1_Real_Stand_nom = new TH1D(QCD1_Stand_TagMatched.Data(), Stand_TagMatched.Data(), bins.size() -1 , bins.data() );
        QCD1_Real_Stand_denom = (TH1D*)QCD1_Real_Stand_nom->Clone(QCD1_Stand_notTagMatched.Data() );

        QCD1_Fake_Stand_nom = new TH1D(QCD1_Stand_TagNonMatched.Data(), Stand_TagNonMatched.Data(), bins.size() -1 , bins.data() );
        QCD1_Fake_Stand_denom = (TH1D*)QCD1_Fake_Stand_nom->Clone(QCD1_Stand_notTagNonMatched.Data());

        QCD2_Real_ML_nom = new TH1D(QCD2_ML_TagMatched.Data(), ML_TagMatched.Data(), bins.size() -1 , bins.data() );
        QCD2_Real_ML_denom = (TH1D*)QCD2_Real_ML_nom->Clone(QCD2_ML_notTagMatched.Data() );

        QCD2_Fake_ML_nom = new TH1D(QCD2_ML_TagNonMatched.Data(), ML_TagNonMatched.Data(), bins.size() -1 , bins.data() );
        QCD2_Fake_ML_denom = (TH1D*)QCD2_Fake_ML_nom->Clone(QCD2_ML_notTagNonMatched.Data());

        QCD2_Real_Stand_nom = new TH1D(QCD2_Stand_TagMatched.Data(), Stand_TagMatched.Data(), bins.size() -1 , bins.data() );
        QCD2_Real_Stand_denom = (TH1D*)QCD2_Real_Stand_nom->Clone(QCD2_Stand_notTagMatched.Data() );
        
        QCD2_Fake_Stand_nom = new TH1D(QCD2_Stand_TagNonMatched.Data(), Stand_TagNonMatched.Data(), bins.size() -1 , bins.data() );
        QCD2_Fake_Stand_denom = (TH1D*)QCD2_Fake_Stand_nom->Clone(QCD2_Stand_notTagNonMatched.Data());
        
        QCD3_Real_ML_nom = new TH1D(QCD3_ML_TagMatched.Data(), ML_TagMatched.Data(), bins.size() -1 , bins.data() );
        QCD3_Real_ML_denom = (TH1D*)QCD3_Real_ML_nom->Clone(QCD3_ML_notTagMatched.Data() );
        
        QCD3_Fake_ML_nom = new TH1D(QCD3_ML_TagNonMatched.Data(), ML_TagNonMatched.Data(), bins.size() -1 , bins.data() );
        QCD3_Fake_ML_denom = (TH1D*)QCD3_Fake_ML_nom->Clone(QCD3_ML_notTagNonMatched.Data());

        QCD3_Real_Stand_nom = new TH1D(QCD3_Stand_TagMatched.Data(), Stand_TagMatched.Data(), bins.size() -1 , bins.data() );
        QCD3_Real_Stand_denom = (TH1D*)QCD3_Real_Stand_nom->Clone(QCD3_Stand_notTagMatched.Data() );
        
        QCD3_Fake_Stand_nom = new TH1D(QCD3_Stand_TagNonMatched.Data(), Stand_TagNonMatched.Data(), bins.size() -1 , bins.data() );
        QCD3_Fake_Stand_denom = (TH1D*)QCD3_Fake_Stand_nom->Clone(QCD3_Stand_notTagNonMatched.Data());
        // eof QCD

        ML_histos.push_back(Real_ML_nom);
        ML_histos.push_back(Real_ML_denom);
        ML_histos.push_back(Fake_ML_nom);
        ML_histos.push_back(Fake_ML_denom);
        Stand_histos.push_back(Real_Stand_nom);
        Stand_histos.push_back(Real_Stand_denom);
        Stand_histos.push_back(Fake_Stand_nom);
        Stand_histos.push_back(Fake_Stand_denom);

        QCD1_ML_histos.push_back(QCD1_Real_ML_nom);
        QCD1_ML_histos.push_back(QCD1_Real_ML_denom);
        QCD1_ML_histos.push_back(QCD1_Fake_ML_nom);
        QCD1_ML_histos.push_back(QCD1_Fake_ML_denom);
        QCD1_Stand_histos.push_back(QCD1_Real_Stand_nom);
        QCD1_Stand_histos.push_back(QCD1_Real_Stand_denom);
        QCD1_Stand_histos.push_back(QCD1_Fake_Stand_nom);
        QCD1_Stand_histos.push_back(QCD1_Fake_Stand_denom);

        QCD2_ML_histos.push_back(QCD2_Real_ML_nom);
        QCD2_ML_histos.push_back(QCD2_Real_ML_denom);
        QCD2_ML_histos.push_back(QCD2_Fake_ML_nom);
        QCD2_ML_histos.push_back(QCD2_Fake_ML_denom);
        QCD2_Stand_histos.push_back(QCD2_Real_Stand_nom);
        QCD2_Stand_histos.push_back(QCD2_Real_Stand_denom);
        QCD2_Stand_histos.push_back(QCD2_Fake_Stand_nom);
        QCD2_Stand_histos.push_back(QCD2_Fake_Stand_denom);

        QCD3_ML_histos.push_back(QCD3_Real_ML_nom);
        QCD3_ML_histos.push_back(QCD3_Real_ML_denom);
        QCD3_ML_histos.push_back(QCD3_Fake_ML_nom);
        QCD3_ML_histos.push_back(QCD3_Fake_ML_denom);
        QCD3_Stand_histos.push_back(QCD3_Real_Stand_nom);
        QCD3_Stand_histos.push_back(QCD3_Real_Stand_denom);
        QCD3_Stand_histos.push_back(QCD3_Fake_Stand_nom);
        QCD3_Stand_histos.push_back(QCD3_Fake_Stand_denom);

        for (int i = 0; i < ML_histos.size(); i++){

            cout << Stand_histos[i]->GetName() << endl;
            cout << ML_histos[i]->GetName() << endl;
            stand_tree->Draw(TString::Format("%s >> %s",Stand_histos[i]->GetName(), Stand_histos[i]->GetName() ), "", "goff");
            ML_tree->Draw(TString::Format("%s >> %s", ML_histos[i]->GetName(), ML_histos[i]->GetName() ), "", "goff");
            QCD1_stand_tree->Draw(TString::Format("%s >> %s",Stand_histos[i]->GetName(), QCD1_Stand_histos[i]->GetName() ), "", "goff");
            QCD1_ML_tree->Draw(TString::Format("%s >> %s", ML_histos[i]->GetName(), QCD1_ML_histos[i]->GetName() ), "", "goff");
            QCD2_stand_tree->Draw(TString::Format("%s >> %s",Stand_histos[i]->GetName(), QCD2_Stand_histos[i]->GetName() ), "", "goff");
            QCD2_ML_tree->Draw(TString::Format("%s >> %s", ML_histos[i]->GetName(), QCD2_ML_histos[i]->GetName() ), "", "goff");
            QCD3_stand_tree->Draw(TString::Format("%s >> %s",Stand_histos[i]->GetName(), QCD3_Stand_histos[i]->GetName() ), "", "goff");
            QCD3_ML_tree->Draw(TString::Format("%s >> %s", ML_histos[i]->GetName(), QCD3_ML_histos[i]->GetName() ), "", "goff");
            cout << Stand_histos[i]->Integral() << endl;
            cout << ML_histos[i]->Integral() << endl;
        }   

        Real_ML_denom->Add(Real_ML_nom);
        Fake_ML_denom->Add(Fake_ML_nom);
        Real_Stand_denom->Add(Real_Stand_nom);
        Fake_Stand_denom->Add(Fake_Stand_nom);

        QCD1_Real_ML_nom->Add(QCD2_Real_ML_nom);
        QCD1_Fake_ML_nom->Add(QCD2_Fake_ML_nom);
        QCD1_Real_Stand_nom->Add(QCD2_Real_Stand_nom);
        QCD1_Fake_Stand_nom->Add(QCD2_Fake_Stand_nom);
        QCD1_Real_ML_nom->Add(QCD3_Real_ML_nom);
        QCD1_Fake_ML_nom->Add(QCD3_Fake_ML_nom);
        QCD1_Real_Stand_nom->Add(QCD3_Real_Stand_nom);
        QCD1_Fake_Stand_nom->Add(QCD3_Fake_Stand_nom);

        QCD1_Real_ML_denom->Add(QCD2_Real_ML_denom);
        QCD1_Fake_ML_denom->Add(QCD2_Fake_ML_denom);
        QCD1_Real_Stand_denom->Add(QCD2_Real_Stand_denom);
        QCD1_Fake_Stand_denom->Add(QCD2_Fake_Stand_denom);
        QCD1_Real_ML_denom->Add(QCD3_Real_ML_denom);
        QCD1_Fake_ML_denom->Add(QCD3_Fake_ML_denom);
        QCD1_Real_Stand_denom->Add(QCD3_Real_Stand_denom);
        QCD1_Fake_Stand_denom->Add(QCD3_Fake_Stand_denom);

        QCD1_Real_ML_denom->Add(QCD1_Real_ML_nom);
        QCD1_Fake_ML_denom->Add(QCD1_Fake_ML_nom);
        QCD1_Real_Stand_denom->Add(QCD1_Real_Stand_nom);
        QCD1_Fake_Stand_denom->Add(QCD1_Fake_Stand_nom);


        //Real_ML_nom   ->Divide(Real_ML_denom);
        //Fake_ML_nom   ->Divide(Fake_ML_denom);
        //Real_Stand_nom->Divide(Real_Stand_denom);
        //Fake_Stand_nom->Divide(Fake_Stand_denom);

        Eff_Real_ML_nom    = new TEfficiency(*Real_ML_nom   , *Real_ML_denom   );
        Eff_Fake_ML_nom    = new TEfficiency(*Fake_ML_nom   , *Fake_ML_denom   );
        Eff_Real_Stand_nom = new TEfficiency(*Real_Stand_nom, *Real_Stand_denom);
        Eff_Fake_Stand_nom = new TEfficiency(*Fake_Stand_nom, *Fake_Stand_denom);

        QCD_Eff_Real_ML_nom    = new TEfficiency(*QCD1_Real_ML_nom   , *QCD1_Real_ML_denom   );
        QCD_Eff_Fake_ML_nom    = new TEfficiency(*QCD1_Fake_ML_nom   , *QCD1_Fake_ML_denom   );
        QCD_Eff_Real_Stand_nom = new TEfficiency(*QCD1_Real_Stand_nom, *QCD1_Real_Stand_denom);
        QCD_Eff_Fake_Stand_nom = new TEfficiency(*QCD1_Fake_Stand_nom, *QCD1_Fake_Stand_denom);

        TempCan = new TCanvas(TString::Format("temp_%s_%s_%s_RealEff", FileName.Data(), particle[j].Data(), level[i].Data() ));
        TempCan->cd();
        Eff_Real_ML_nom   ->Draw();
        gPad->Update();
        auto gEff_Real_ML_nom    = Eff_Real_ML_nom   ->GetPaintedGraph();
        TempCan->Clear();
        TempCan->cd();
        Eff_Fake_ML_nom->Draw();
        gPad->Update();
        auto gEff_Fake_ML_nom    = Eff_Fake_ML_nom   ->GetPaintedGraph();
        TempCan->Clear();
        TempCan->cd();
        Eff_Real_Stand_nom->Draw();
        gPad->Update();
        auto gEff_Real_Stand_nom = Eff_Real_Stand_nom->GetPaintedGraph();
        TempCan->Clear();
        TempCan->cd();
        Eff_Fake_Stand_nom->Draw();
        gPad->Update();
        auto gEff_Fake_Stand_nom = Eff_Fake_Stand_nom->GetPaintedGraph();
        TempCan->Clear();
        //QCD
        TempCan->cd();
        QCD_Eff_Real_ML_nom   ->Draw();
        gPad->Update();
        auto gQCD_Eff_Real_ML_nom    = QCD_Eff_Real_ML_nom   ->GetPaintedGraph();
        TempCan->Clear();
        TempCan->cd();
        QCD_Eff_Fake_ML_nom->Draw();
        gPad->Update();
        auto gQCD_Eff_Fake_ML_nom    = QCD_Eff_Fake_ML_nom   ->GetPaintedGraph();
        TempCan->Clear();
        TempCan->cd();
        QCD_Eff_Real_Stand_nom->Draw();
        gPad->Update();
        auto gQCD_Eff_Real_Stand_nom = QCD_Eff_Real_Stand_nom->GetPaintedGraph();
        TempCan->Clear();
        TempCan->cd();
        QCD_Eff_Fake_Stand_nom->Draw();
        gPad->Update();
        auto gQCD_Eff_Fake_Stand_nom = QCD_Eff_Fake_Stand_nom->GetPaintedGraph();

        for (int k = 0 ; k< gEff_Real_ML_nom->GetN(); k++){
            gEff_Real_ML_nom   ->GetPoint(k,x,y);
            if (y == 0.) gEff_Real_ML_nom->RemovePoint(k);
            gEff_Fake_ML_nom   ->GetPoint(k,x,y);
            if (y == 0.) gEff_Fake_ML_nom->RemovePoint(k);
            gEff_Real_Stand_nom->GetPoint(k,x,y);
            if (y == 0.) gEff_Real_Stand_nom->RemovePoint(k);
            gEff_Fake_Stand_nom->GetPoint(k,x,y);
            if (y == 0.) gEff_Fake_Stand_nom->RemovePoint(k);

            gQCD_Eff_Real_ML_nom   ->GetPoint(k,x,y);
            if (y == 0.) gQCD_Eff_Real_ML_nom->RemovePoint(k);
            gQCD_Eff_Fake_ML_nom   ->GetPoint(k,x,y);
            if (y == 0.) gQCD_Eff_Fake_ML_nom->RemovePoint(k);
            gQCD_Eff_Real_Stand_nom->GetPoint(k,x,y);
            if (y == 0.) gQCD_Eff_Real_Stand_nom->RemovePoint(k);
            gQCD_Eff_Fake_Stand_nom->GetPoint(k,x,y);
            if (y == 0.) gQCD_Eff_Fake_Stand_nom->RemovePoint(k);
        }


        gEff_Real_ML_nom->GetXaxis()->SetTitle("Large-R jet p_{T} [GeV]");
        gEff_Real_ML_nom->GetXaxis()->SetTitleOffset(1.2);
        gEff_Real_ML_nom->SetLineColor(kRed);
        gEff_Real_ML_nom->SetLineWidth(1);
        gEff_Real_ML_nom->SetLineStyle(1);

        gEff_Real_Stand_nom->GetXaxis()->SetTitle("Large-R jet p_{T} [GeV]");
        gEff_Real_Stand_nom->GetXaxis()->SetTitleOffset(1.2);
        gEff_Real_Stand_nom->SetLineColor(kRed);
        gEff_Real_Stand_nom->SetLineWidth(1);
        gEff_Real_Stand_nom->SetLineStyle(2);

        gEff_Fake_ML_nom->GetXaxis()->SetTitle("Large-R jet p_{T} [GeV]");
        gEff_Fake_ML_nom->GetXaxis()->SetTitleOffset(1.2);
        gEff_Fake_ML_nom->SetLineColor(kBlue);
        gEff_Fake_ML_nom->SetLineWidth(1);
        gEff_Fake_ML_nom->SetLineStyle(1);

        gEff_Fake_Stand_nom->GetXaxis()->SetTitle("Large-R jet p_{T} [GeV]");
        gEff_Fake_Stand_nom->GetXaxis()->SetTitleOffset(1.2);
        gEff_Fake_Stand_nom->SetLineColor(kBlue);
        gEff_Fake_Stand_nom->SetLineWidth(1);
        gEff_Fake_Stand_nom->SetLineStyle(2);

        //QCD
        gQCD_Eff_Real_ML_nom->GetXaxis()->SetTitle("Large-R jet p_{T} [GeV]");
        gQCD_Eff_Real_ML_nom->GetXaxis()->SetTitleOffset(1.2);
        gQCD_Eff_Real_ML_nom->SetLineColor(kBlue);
        gQCD_Eff_Real_ML_nom->SetLineWidth(1);
        gQCD_Eff_Real_ML_nom->SetLineStyle(1);

        gQCD_Eff_Real_Stand_nom->GetXaxis()->SetTitle("Large-R jet p_{T} [GeV]");
        gQCD_Eff_Real_Stand_nom->GetXaxis()->SetTitleOffset(1.2);
        gQCD_Eff_Real_Stand_nom->SetLineColor(kBlue);
        gQCD_Eff_Real_Stand_nom->SetLineWidth(1);
        gQCD_Eff_Real_Stand_nom->SetLineStyle(2);

        gQCD_Eff_Fake_ML_nom->GetXaxis()->SetTitle("Large-R jet p_{T} [GeV]");
        gQCD_Eff_Fake_ML_nom->GetXaxis()->SetTitleOffset(1.2);
        gQCD_Eff_Fake_ML_nom->SetLineColor(kBlue);
        gQCD_Eff_Fake_ML_nom->SetLineWidth(1);
        gQCD_Eff_Fake_ML_nom->SetLineStyle(1);

        gQCD_Eff_Fake_Stand_nom->GetXaxis()->SetTitle("Large-R jet p_{T} [GeV]");
        gQCD_Eff_Fake_Stand_nom->GetXaxis()->SetTitleOffset(1.2);
        gQCD_Eff_Fake_Stand_nom->SetLineColor(kBlue);
        gQCD_Eff_Fake_Stand_nom->SetLineWidth(1);
        gQCD_Eff_Fake_Stand_nom->SetLineStyle(2);


        TempCan = new TCanvas(TString::Format("%s_%s_%s_RealEff", FileName.Data(), particle[j].Data(), level[i].Data() ));
        TempCan->cd();
        gStyle->SetOptStat(0);
        gEff_Real_ML_nom ->GetXaxis()->SetRangeUser(bins[0], bins[bins.size()-1]);
        gEff_Real_ML_nom ->SetMinimum(0.);
        gEff_Real_ML_nom ->SetMaximum(1.);
        gEff_Real_ML_nom ->SetTitle("");
        gEff_Real_ML_nom   ->Draw("AP e1");
        //Fake_ML_nom   ->Draw("hist same");
        gEff_Real_Stand_nom->Draw("P same e1");

        gQCD_Eff_Fake_ML_nom   ->Draw("P same e1");
        gQCD_Eff_Fake_Stand_nom->Draw("P same e1");
        gPad->Update();

        //Fake_Stand_nom->Draw("hist same");
        TempLeg = new TLegend(0.65,0.65,0.86,0.86);
        TempLeg->AddEntry(gEff_Real_ML_nom, "Real Eff. ML", "lp");
        TempLeg->AddEntry(gEff_Real_Stand_nom, "Real Eff. Stand.", "lp");
        TempLeg->AddEntry(gQCD_Eff_Fake_ML_nom, "QCD Fake Eff. ML", "lp");
        TempLeg->AddEntry(gQCD_Eff_Fake_Stand_nom, "QCD Fake Eff. Stand.", "lp");
        TempLeg->SetBorderSize(0);
        TempLeg->Draw("same");
        Legs.push_back(TempLeg);


        Cans.push_back(TempCan);

        ML_histos.clear();
        Stand_histos.clear();
        QCD1_ML_histos.clear();
        QCD1_Stand_histos.clear();
        QCD2_ML_histos.clear();
        QCD2_Stand_histos.clear();
        QCD3_ML_histos.clear();
        QCD3_Stand_histos.clear();
        }
    }

    TCanvas * can1 = new TCanvas(TString::Format("%s_TaggingMigrations", FileName.Data() ));
    TCanvas * can2 = new TCanvas(TString::Format("%s_TaggingStandMigrations", FileName.Data() ));
    TCanvas * can3 = new TCanvas(TString::Format("%s_TaggingMLvsStandMigrations", FileName.Data() ));


    TH2D* TaggingMigrations = (TH2D*)rfile->Get("TaggingMigrations");
    TH2D* TaggingStandMigrations = (TH2D*)rfile->Get("TaggingMLvsStandMigrations");
    TH2D* TaggingMLvsStandMigrations = (TH2D*)rfile->Get("TaggingStandMigrations");

    can1->cd();
    gStyle->SetPaintTextFormat("0.2f");
    gPad->SetLeftMargin(0.15);
    gPad->SetRightMargin(0.1);
    TaggingMigrations->SetMarkerSize(2);
    TaggingMigrations->SetMinimum(0.);
    TaggingMigrations->SetMaximum(1.);
    TaggingMigrations->SetTitle("");
    TaggingMigrations->Draw("colz text");
    Cans.push_back(can1);

    can2->cd();
    gStyle->SetPaintTextFormat("0.2f");
    gPad->SetLeftMargin(0.15);
    gPad->SetRightMargin(0.1);
    TaggingStandMigrations->SetMarkerSize(2);
    TaggingStandMigrations->SetMinimum(0.);
    TaggingStandMigrations->SetMaximum(1.);
    TaggingStandMigrations->SetTitle("");
    TaggingStandMigrations->Draw("colz text");
    Cans.push_back(can2);

    can3->cd();
    gStyle->SetPaintTextFormat("0.2f");
    gPad->SetLeftMargin(0.15);
    gPad->SetRightMargin(0.1);
    TaggingMLvsStandMigrations->SetMarkerSize(2);
    TaggingMLvsStandMigrations->SetMinimum(0.);
    TaggingMLvsStandMigrations->SetMaximum(1.);
    TaggingMLvsStandMigrations->SetTitle("");
    TaggingMLvsStandMigrations->Draw("colz text");
    Cans.push_back(can3);

    for (int i = 0;i < Cans.size();i++){
        Cans[i]->SaveAs(TString::Format("./png/%s.png", Cans[i]->GetName() ));
        Cans[i]->SaveAs(TString::Format("./pdf/%s.pdf", Cans[i]->GetName() ));
    }

    return 0;
}
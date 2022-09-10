class HistoMaker
{

    // class to hold histograms for each of the reco, particle, reco && particle (binned in reco or particle:) levels

//private:


public:

    map<TString, float>     _HistoMapTTreeVals;

HistoMaker(){};
~HistoMaker(){};
map<TString, float> GetMap(){ return _HistoMapTTreeVals;};
};



void dosth(map<TString, float> &b){
    b["hello"] = 3;
}

int test(){
    map<TString, float> a;
    HistoMaker *h = new HistoMaker();
    map<TString, float> c = h->GetMap();
    
    c["hello"] = 5.;
    dosth(h->_HistoMapTTreeVals);
    cout << h->GetMap()["hello"] << endl;

    TFile * rfile = new TFile("test.root", "recreate");


    TTree * tree = new TTree("test", "test");
    vector<double> vec;

    tree->Branch("test", &vec);

    vec.push_back(1.);
    vec.push_back(2.);
    vec.push_back(3.);
    //vec.clear();
    tree->Fill();
    vec.clear();
    vec.push_back(5.);
    vec.push_back(6.);
    vec.push_back(7.);
    tree->Fill();
    tree->Write();
    

    cout << "Tree GetEntries() = " << tree->GetEntries() << endl;

    // /for (Int_t i=0; i<tree->GetEntries(); i++)
    // /{
    // /   Long64_t tentry = t->LoadTree(i);
    // /   tree->GetBranch("test")->GetEntry(tentry);
    // /   
    // /}
    tree->Write();
    
    return 0;
}
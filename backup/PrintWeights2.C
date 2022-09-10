double a = 0;

double Sum(double w){a+=w;return w;}

int PrintWeights2(TString FileName){
    TFile * rfile = new TFile(FileName.Data(), "read");
    TTree * mc_weights = (TTree*)rfile->Get("mc_weights");
    
    mc_weights->Draw("Sum(Default)");
    cout << "Number of entries = " << mc_weights->GetEntries() << endl;
    cout << "Sum of weights = " << a << endl;
    cout << "WeightNormalisation = " << endl;
    //mc_weights->Scan("WeightNormalisation");

    return 0;
}
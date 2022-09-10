double GetDiff(TH1D * h, TH1D * h2){
double sum = 0;
for (int i = 1; i<h->GetXaxis()->GetNbins();i++){
sum+=TMath::Abs(h->GetBinContent(i)-h2->GetBinContent(i));
}
return sum;
}

int CheckChi2(TString val="test"){

TFile *_file0 = TFile::Open("out_900_13000.root");
TFile *_file1 = TFile::Open("out_noMPI_noISR_900_13000.root");


TTree * nompipt = (TTree*)_file1->Get("FastJets10Pt_13000");
TTree * trimpt = (TTree*)_file0->Get("FastJets10Pt_13000");
trimpt->SetName("trimpt");
nompipt->SetName("nompipt");
TTree * nompi = (TTree*)_file1->Get("FastJets10MultLam50_13000");
TTree * trim = (TTree*)_file0->Get("FastJets10MultLam50_13000");
trim->SetName("trim");
nompi->SetName("nompi");
trim->AddFriend(nompi);
trim->AddFriend(nompipt);
trim->AddFriend(trimpt);
trim->Draw("trim.FastJets10MultLam50 >> h_trim(100,0,100)", "", "goff");
trim->Draw("nompi.FastJets10MultLam50 >> h_nompi(100,0,100)", "", "goff");
TH1D * h_trim = (TH1D*)gDirectory->Get("h_trim");
TH1D * h_nompi = (TH1D*)gDirectory->Get("h_nompi");


h_trim->Scale(h_nompi->GetMaximum()/ h_trim->GetMaximum());
h_trim->Scale(1./h_trim->Integral());
h_nompi->Scale(1./h_nompi->Integral());
TCanvas * can1 = new TCanvas("can1", "can1", 0,0,800,800);
can1->cd();
h_trim->Draw("hist e1");
h_nompi->SetLineColor(1);
h_nompi->Draw("hist e1 same");
TCanvas * can = new TCanvas("can", "can", 0,0,800,800);
can->cd();
trim->Draw("trimpt.FastJets10Pt >> h_trimpt(200,0,200)", "", "goff");
trim->Draw("nompipt.FastJets10Pt >> h_nompipt(200,0,200)", "", "goff");
TH1D * h_trimpt = (TH1D*)gDirectory->Get("h_trimpt");
TH1D * h_nompipt = (TH1D*)gDirectory->Get("h_nompipt");

h_trimpt->Scale(h_nompipt->GetMaximum()/ h_trimpt->GetMaximum());
h_trimpt->Scale(1./h_trimpt->Integral());
h_nompipt->Scale(1./h_nompipt->Integral());

h_trimpt->Draw("hist e1");
h_nompipt->SetLineColor(1);
h_nompipt->Draw("hist e1 same");
cout << "differece pt = " << GetDiff(h_trimpt,h_nompipt) << endl;
cout << "differece ptmu = " << h_nompipt->GetMean() - h_trimpt->GetMean() << endl;
cout << "differece ptstd = " << h_nompipt->GetStdDev() - h_trimpt->GetStdDev() << endl;
cout << "--------------" << endl;
cout << "differece mult = " << GetDiff(h_trim,h_nompi) << endl;
cout << "differece mult mu = " << h_nompi->GetMean() - h_trim->GetMean() << endl;
cout << "differece mult std = " << h_nompi->GetStdDev() - h_trim->GetStdDev() << endl;

can->SaveAs(TString::Format("./pngs/pt_%s.png", val.Data() ));
can->SaveAs(TString::Format("./pngs/pt_%s.pdf", val.Data() ));
can->SaveAs(TString::Format("./pngs/mult_%s.png", val.Data() ));
can->SaveAs(TString::Format("./pngs/mult_%s.pdf", val.Data() ));








return 0;
}

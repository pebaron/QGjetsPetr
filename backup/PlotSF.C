int PlotSF(TString WP = "Medium", TString WhatToPlot = "SF"){

TFile * file0 = new TFile(TString::Format("./SFFiles_MC0/Reco_%s_Z.root",WP.Data()), "read");
TFile * file1 = new TFile(TString::Format("./SFFiles_MC1/Reco_%s_Z.root",WP.Data()), "read");
TFile * file2 = new TFile(TString::Format("./SFFiles_MC2/Reco_%s_Z.root",WP.Data()), "read");
TFile * file3 = new TFile(TString::Format("./SFFiles_MC3/Reco_%s_Z.root",WP.Data()), "read");

TH2F * h0 = (TH2F*)file0->Get(TString::Format("%s_0", WhatToPlot.Data()) );
TH2F * h1 = (TH2F*)file1->Get(TString::Format("%s_1", WhatToPlot.Data()) );
TH2F * h2 = (TH2F*)file2->Get(TString::Format("%s_2", WhatToPlot.Data()) );
TH2F * h3 = (TH2F*)file3->Get(TString::Format("%s_3", WhatToPlot.Data()) );

h0->GetZaxis()->SetRangeUser(0.8,1.2);
h1->GetZaxis()->SetRangeUser(0.8,1.2);
h2->GetZaxis()->SetRangeUser(0.8,1.2);
h3->GetZaxis()->SetRangeUser(0.8,1.2);

TCanvas * can = new TCanvas("can", "can", 0,0,1600,1600);
can->Divide(2,2);
can->cd(1);
gPad->SetRightMargin(0.15);
h0->Draw("colz");
can->cd(2);
gPad->SetRightMargin(0.15);
h1->Draw("colz");
can->cd(3);
gPad->SetRightMargin(0.15);
h2->Draw("colz");
can->cd(4);
gPad->SetRightMargin(0.15);
h3->Draw("colz");

can->SaveAs(TString::Format("%s_%s.png", WP.Data(), WhatToPlot.Data() ));
can->SaveAs(TString::Format("%s_%s.pdf", WP.Data(), WhatToPlot.Data() ));

return 0;

}
int Test(){
    TH1D * h = new TH1D("nom", "nom", 10,0,10);
    TH1D * h2 = new TH1D("denom", "denom", 10,0,10);

    for (int i = 0 ; i<100; i++){
        h->Fill(2);
        h->Fill(3);
    }
    for (int i = 0 ; i<1000; i++){
        h2->Fill(2);
        h2->Fill(3);
    }
    //h->Draw("hist e1");
    //h2->Draw("hist e1 same");
    TEfficiency * data = new TEfficiency ( *h, *h2); 
    data->Draw();
    return 0;
};
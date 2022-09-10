int BuildTree(){
   Int_t           Category;
   Int_t           Age;

   TTree *tree = new TTree("T","CERN 1988 staff data");
   tree->Branch("Category",&Category,"Category/I");
   tree->Branch("Age",&Age,"Age/I");
   for (int i = 0; i< 100; i++){
      Category = i+30.0;
      Age = i -20.0;
      tree->Fill();
   }
   return 0;
}
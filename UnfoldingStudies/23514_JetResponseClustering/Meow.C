{
   TFile F1("MC.root");
   TFile F2("MCSumE.root");

   TTree *T1 = (TTree *)F1.Get("UnfoldingTree");
   TTree *T2 = (TTree *)F2.Get("UnfoldingTree");

   T1->SetMarkerStyle(20);
   T1->SetLineWidth(2);
   T2->SetMarkerStyle(20);
   T2->SetLineWidth(2);

   T1->Draw("Max$(GenJetE)>>A1", "", "");
   T2->Draw("Max$(GenJetE)>>A2", "1.5262468673783047", "same");
}

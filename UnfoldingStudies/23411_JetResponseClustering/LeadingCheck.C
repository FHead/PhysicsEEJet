{
   TFile F1("MCPythia8Leading.root");
   TFile F2("MCPythia8SumE.root");

   TH1D H1("H1", ";Leading E;", 100, 0, 46);
   TH1D H2("H2", ";Leading E;", 100, 0, 46);

   H1.SetStats(0);
   H2.SetStats(0);

   TTree *T1 = (TTree *)F1.Get("UnfoldingTree");
   TTree *T2 = (TTree *)F2.Get("UnfoldingTree");

   T1->Draw("GenJetE[0]>>H1");
   T2->Draw("GenJetE[0]>>H2");

   H1.SetLineColor(kBlack);
   H2.SetLineColor(kRed);

   H1.DrawNormalized();
   H2.DrawNormalized("same");
}

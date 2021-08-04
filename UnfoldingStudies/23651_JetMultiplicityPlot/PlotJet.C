{
   TFile F1("Data.root");
   TFile F2("MC.root");

   TH1D H1("H1", ";N(Jet E > 10);a.u.", 10, 0, 10);
   TH1D H2("H2", ";;", 10, 0, 10);

   TTree *T1 = (TTree *)F1.Get("UnfoldingTree");
   TTree *T2 = (TTree *)F2.Get("UnfoldingTree");

   TCanvas Canvas;

   T1->Draw("Sum$(RecoJetE>10&&RecoJetTheta>0.2*3.14159&&RecoJetTheta<0.8*3.14159)>>H1", "", "");
   T2->Draw("Sum$(RecoJetE>10&&RecoJetTheta>0.2*3.14159&&RecoJetTheta<0.8*3.14159)>>H2", "", "");

   H1.SetStats(0);

   H1.Scale(1 / H1.Integral());
   H2.Scale(1 / H2.Integral());

   H1.SetLineColor(kBlue);
   H1.SetMarkerColor(kBlue);
   H1.SetLineWidth(2);
   H1.SetMarkerSize(2);
   H2.SetLineColor(kRed);
   H2.SetMarkerColor(kRed);
   H2.SetLineWidth(2);
   H2.SetMarkerSize(2);

   H1.Draw();
   H2.Draw("same");

   TLegend Legend(0.55, 0.80, 0.85, 0.65);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.SetFillStyle(0);
   Legend.SetBorderSize(0);
   Legend.AddEntry(&H1, "Data", "pl");
   Legend.AddEntry(&H2, "Simulation", "pl");
   Legend.Draw();

   Canvas.SetLogy();

   Canvas.SaveAs("NJet.pdf");
}

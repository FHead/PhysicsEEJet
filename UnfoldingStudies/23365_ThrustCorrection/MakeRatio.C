{
   TChain Chain1("tgen", "tgen");
   TChain Chain2("tgenBefore", "tgenBefore");

   for(int i = 1; i <= 40; i++)
   {
      Chain1.AddFile(Form("SamplesMC/LEP1MC1994_recons_aftercut-%03d.root", i));
      Chain2.AddFile(Form("SamplesMC/LEP1MC1994_recons_aftercut-%03d.root", i));
   }

   TFile OutputFile("ThrustCorrection.root", "RECREATE");

   TH1D H1("H1", ";Thrust;", 42, 0.58, 1.00);
   TH1D H2("H2", ";Thrust;", 42, 0.58, 1.00);

   H1.SetStats(0);
   H2.SetStats(0);

   TCanvas Canvas;

   Chain1.Draw("Thrust>>H1", "passesSTheta");
   Chain2.Draw("Thrust>>H2", "", "same");

   H1.Write();
   H2.Write();

   H1.Scale(1 / H1.Integral() / 0.01);
   H2.Scale(1 / H2.Integral() / 0.01);

   H1.SetMarkerColor(kRed);
   H1.SetLineColor(kRed);

   Canvas.SaveAs("Thrust.pdf");

   TH1D *HR = (TH1D *)H2.Clone("HR");
   HR->Divide(&H1);

   HR->GetYaxis()->SetTitle("Ratio GenBefore/Gen");
   HR->Draw("");

   HR->SetMinimum(0.8);
   HR->SetMaximum(1.2);

   Canvas.SaveAs("ThrustRatio.pdf");

   HR->Write();

   OutputFile.Close();
}


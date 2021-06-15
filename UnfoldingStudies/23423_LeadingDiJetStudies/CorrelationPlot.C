{
   TCanvas Canvas;

   TH2D H1("H1", ";E_{sum} (GeV);Leading Jet #theta (#pi)", 100, 0, 91.2, 100, 0.2, 0.8);
   UnfoldingTree->Draw("GenJetTheta[0]/3.14159:GenSumE020>>H1", "", "colz");
   H1.SetStats(0);
   Canvas.SaveAs("LeadingJetThetaSumE.pdf");

   TH2D H2("H2", ";E^{hybrid}_{sum} (GeV);Leading Jet #theta (#pi)", 100, 0, 91.2, 100, 0.2, 0.8);
   UnfoldingTree->Draw("GenJetTheta[0]/3.14159:GenHybridE020>>H2", "", "colz");
   H2.SetStats(0);
   Canvas.SaveAs("LeadingJetThetaHybridE.pdf");
}


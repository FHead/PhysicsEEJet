{
   TFile F0("Input/DataJetENominal.root");
   TFile F1("Input/DataJetELargeThetaGap.root");

   TH1D *H0 = (TH1D *)F0.Get("HInput");
   TH1D *H1 = (TH1D *)F1.Get("HInput");

   H1->Scale(1.1612);

   H1->Divide(H0);

   H1->SetStats(0);
   H1->SetLineWidth(2);
   H1->SetLineColor(kBlack);
   H1->SetMarkerStyle(20);
   H1->SetMarkerColor(kBlack);

   H1->Draw();

   H1->GetYaxis()->SetRangeUser(0.8, 1.2);

   c1->SaveAs("ThetaGapRecoCheck.pdf");
}

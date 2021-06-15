{
   UnfoldingTree->SetMarkerStyle(20);
   UnfoldingTree->Draw("abs(RecoHybridE/GenHybridE-1)*sqrt(3.1415926535/2)*100:GenHybridE>>htemp(50,0,91.2)", "", "prof");
   htemp->SetStats(0);
   htemp->GetXaxis()->SetTitle("Gen E_{sum}^{hybrid} (GeV)");
   htemp->GetYaxis()->SetTitle("Reco E_{sum}^{hybrid} Resolution (%)");
   htemp->SetTitle("");
   htemp->SetMaximum(35);
   htemp->SetLineWidth(2);
   htemp->SetLineColor(1);
   c1->SetGridx();
   c1->SetGridy();
   c1->SaveAs("HybridESumResolution.pdf");
}


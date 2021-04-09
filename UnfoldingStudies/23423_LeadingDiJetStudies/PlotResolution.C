{
   UnfoldingTree->SetMarkerStyle(20);
   UnfoldingTree->Draw("abs(RecoESum/GenESum-1)*sqrt(3.1415926535/2):GenESum", "", "prof");
   htemp->SetStats(0);
   htemp->GetXaxis()->SetTitle("Gen SumE");
   htemp->GetYaxis()->SetTitle("\"Reco SumE Resolution\"");
   htemp->SetTitle("");
   htemp->SetMaximum(0.25);
   c1->SetGridx();
   c1->SetGridy();
   c1->SaveAs("ESumResolution.pdf");
}


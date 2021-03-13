#include <iostream>
using namespace std;

#include "TH1D.h"
#include "TH2D.h"
#include "TFile.h"
#include "TCanvas.h"

#include "SetStyle.h"
#include "PlotHelper4.h"

int main(int argc, char *argv[])
{
   SetThesisStyle();

   TFile F23345("../23345_JetResponseClustering/MC.root");
   TFile F23351("../23351_UnfoldingPreparation/Output/MCJetPNominal.root");

   F23345.ls();
   F23351.ls();

   TH1D *HGen23345 = (TH1D *)F23345.Get("HGenJetPBinned");
   TH1D *HGen23351 = (TH1D *)F23351.Get("HMCGen");
   TH1D *HReco23345 = (TH1D *)F23345.Get("HRecoJetPBinned");
   TH1D *HReco23351 = (TH1D *)F23351.Get("HMCReco");
   TH2D *HResponse23345 = (TH2D *)F23345.Get("H2DJetPBinned");
   TH2D *HResponse23351 = (TH2D *)F23351.Get("HResponse");

   HResponse23345->Fill(0.0, 0.0, 0.0);

   HGen23351->SetLineColor(kRed);

   PdfFileHelper PdfFile("Comparison.pdf");
   PdfFile.AddTextPage("Debugging gen jets");

   TCanvas Canvas;

   HGen23345->Draw();
   HGen23351->Draw("same");

   PdfFile.AddCanvas(Canvas);

   HGen23345->Draw();
   HGen23351->Draw("same");

   Canvas.SetLogy(true);
   PdfFile.AddCanvas(Canvas);

   PdfFile.AddPlot(HResponse23345, "colz", false, true);
   PdfFile.AddPlot(HResponse23351, "colz", false, true);

   HReco23345->Draw();
   HReco23351->Draw("same");

   Canvas.SetLogy(false);
   PdfFile.AddCanvas(Canvas);

   HReco23345->Draw();
   HReco23351->Draw("same");

   Canvas.SetLogy(true);
   PdfFile.AddCanvas(Canvas);

   /*
   HResponse23351->Divide(HResponse23345);
   HResponse23351->SetMaximum(1.15);
   HResponse23351->SetMinimum(0.95);
   PdfFile.AddPlot(HResponse23351, "colz", false, false);
   */

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   F23345.Close();
   F23351.Close();

   return 0;
}



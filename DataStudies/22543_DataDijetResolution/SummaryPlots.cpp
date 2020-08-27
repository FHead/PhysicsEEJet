#include <iostream>
#include <cmath>
using namespace std;

#include "TH1D.h"
#include "TCanvas.h"
#include "TH2D.h"
#include "TLegend.h"

#include "DataHelper.h"
#include "CommandLine.h"
#include "SetStyle.h"

#include "JetCorrector.h"

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   string MCState = CL.Get("MC");
   string DataState = CL.Get("Data");
   string Output = CL.Get("Output");
   string JERFile = CL.Get("JER");

   DataHelper DHFile("DijetResult.dh");

   int NBins = 6;
   double Bins[] = {0.50, 0.55, 0.60, 0.65, 0.70, 0.75, 0.80};

   TH1D HMC35("HMC35", ";#theta (#pi);Jet resolution from MC studies", NBins, Bins);
   TH1D HMC40("HMC40", ";#theta (#pi);Jet resolution from MC studies", NBins, Bins);
   TH1D HMC45("HMC45", ";#theta (#pi);Jet resolution from MC studies", NBins, Bins);
   TH1D HMCDijet("HMCDijet", ";#theta (#pi);Jet resolution from dijet", NBins, Bins);
   TH1D HDataDijet("HDataDijet", ";#theta (#pi);Jet resolution from dijet", NBins, Bins);

   HMC35.SetStats(0);
   HMC40.SetStats(0);
   HMC45.SetStats(0);
   HMCDijet.SetStats(0);
   HDataDijet.SetStats(0);

   JetCorrector JER(JERFile);

   for(int i = 0; i < NBins; i++)
   {
      JER.SetJetP(35);
      JER.SetJetTheta(HMC35.GetBinCenter(i + 1) * M_PI);
      JER.SetJetPhi(0);
      HMC35.SetBinContent(i + 1, JER.GetCorrection());

      JER.SetJetP(40);
      JER.SetJetTheta(HMC40.GetBinCenter(i + 1) * M_PI);
      JER.SetJetPhi(0);
      HMC40.SetBinContent(i + 1, JER.GetCorrection());

      JER.SetJetP(45);
      JER.SetJetTheta(HMC45.GetBinCenter(i + 1) * M_PI);
      JER.SetJetPhi(0);
      HMC45.SetBinContent(i + 1, JER.GetCorrection());

      HMCDijet.SetBinContent(i + 1, DHFile[MCState][Form("B%dJRMS",i)].GetDouble());
      HMCDijet.SetBinError(i + 1, DHFile[MCState][Form("B%dJRMSE",i)].GetDouble());
      HDataDijet.SetBinContent(i + 1, DHFile[DataState][Form("B%dJRMS",i)].GetDouble());
      HDataDijet.SetBinError(i + 1, DHFile[DataState][Form("B%dJRMSE",i)].GetDouble());
   }

   TH2D HWorld("HWorld", ";#theta (#pi);Jet resolution", NBins, Bins, 100, 0.08, 0.20);
   HWorld.SetStats(0);

   TLegend Legend(0.15, 0.15, 0.45, 0.45);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.SetBorderSize(0);
   Legend.SetFillStyle(0);
   Legend.AddEntry(&HMC35, "MC (P = 35 GeV)", "l");
   Legend.AddEntry(&HMC40, "MC (P = 40 GeV)", "l");
   Legend.AddEntry(&HMC45, "MC (P = 45 GeV)", "l");
   Legend.AddEntry(&HMCDijet, "MC dijet", "lp");
   Legend.AddEntry(&HDataDijet, "Data dijet", "lp");

   HMC35.SetLineWidth(2);
   HMC35.SetLineColor(kCyan);
   HMC40.SetLineWidth(2);
   HMC40.SetLineColor(kBlue);
   HMC45.SetLineWidth(2);
   HMC45.SetLineColor(kYellow + 3);
   HMCDijet.SetLineWidth(2);
   HMCDijet.SetLineColor(kRed);
   HMCDijet.SetMarkerSize(2);
   HMCDijet.SetMarkerColor(kRed);
   HDataDijet.SetLineWidth(2);
   HDataDijet.SetLineColor(kGreen + 3);
   HDataDijet.SetMarkerSize(2);
   HDataDijet.SetMarkerColor(kGreen + 3);

   TCanvas Canvas;

   HWorld.Draw("axis");
   HMC35.Draw("same");
   HMC40.Draw("same");
   HMC45.Draw("same");
   HMCDijet.Draw("same");
   HDataDijet.Draw("same");

   Legend.Draw();

   Canvas.SaveAs(Output.c_str());

   HDataDijet.Divide(&HMCDijet);

   HDataDijet.SetMinimum(0.98);
   HDataDijet.SetMaximum(1.05);
   HDataDijet.GetYaxis()->SetTitle("Data/MC ratio");
   HDataDijet.Draw();

   Canvas.SaveAs(("Ratio" + Output).c_str());

   return 0;
}





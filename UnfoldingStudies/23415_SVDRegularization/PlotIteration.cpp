#include <iostream>
using namespace std;

#include "TH1D.h"
#include "TFile.h"
#include "TGraph.h"
#include "TCanvas.h"

#include "CommandLine.h"
#include "PlotHelper4.h"
#include "SetStyle.h"

int main(int argc, char *argv[]);
double CalculateChi2(TH1D *H1, TH1D *H2, int IgnoreBin = 0, bool UseError = true);

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   string InputFileName  = CL.Get("Input");
   string OutputFileName = CL.Get("Output");
   int PointsToIgnore    = CL.GetInt("Ignore");
   string Reference      = CL.Get("Reference", "HMCTruth");

   vector<double> Regularization{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 32, 34, 36, 38, 40, 42, 44, 46, 48, 50, 52, 54, 56, 58, 60, 62, 64, 66, 68, 70, 80, 90, 100, 125, 150};

   TGraph Graph;
   TGraph GraphD;

   PdfFileHelper PdfFile(OutputFileName);
   PdfFile.AddTextPage("Regularization scan");

   TFile InputFile(InputFileName.c_str());

   TH1D *HMCMeasured = (TH1D *)InputFile.Get("HMCTruth");
   TH1D *HInput = (TH1D *)InputFile.Get("HInput");
   double ScalingFactor = HInput->Integral() / HMCMeasured->Integral();

   TH1D *HMCTruth = (TH1D *)InputFile.Get(Reference.c_str());
   HMCTruth->Scale(ScalingFactor);
   HMCTruth->SetStats(0);
   HMCTruth->SetLineColor(kBlack);
   HMCTruth->SetLineWidth(2);

   for(double D : Regularization)
   {
      TH1D *HUnfolded = (TH1D *)InputFile.Get(Form("HUnfoldedSVD%.1f", D));
      if(HUnfolded == nullptr)
         continue;

      double Chi2 = CalculateChi2(HMCTruth, HUnfolded, PointsToIgnore, true);
      double D2 = CalculateChi2(HMCTruth, HUnfolded, PointsToIgnore, false);

      Graph.SetPoint(Graph.GetN(), D, Chi2);
      GraphD.SetPoint(GraphD.GetN(), D, D2);

      TCanvas Canvas;
      HMCTruth->SetTitle(Form("Regularization %.1f", D));
      HMCTruth->Draw("hist");
      HUnfolded->SetMarkerStyle(20);
      HUnfolded->Draw("same");
      PdfFile.AddCanvas(Canvas);
      Canvas.SetLogy();
      PdfFile.AddCanvas(Canvas);
   }

   InputFile.Close();

   PdfFile.AddTextPage("Summary plots");

   Graph.SetNameTitle("GChi2", "Chi2");
   GraphD.SetNameTitle("GD2", "D2");

   PdfFile.AddPlot(Graph, "apl");
   PdfFile.AddPlot(Graph, "apl", false, false, true, true);
   PdfFile.AddPlot(Graph, "apl", true, false, true, true);
   PdfFile.AddPlot(GraphD, "apl");
   PdfFile.AddPlot(GraphD, "apl", false, false, true, true);
   PdfFile.AddPlot(GraphD, "apl", true, false, true, true);

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

double CalculateChi2(TH1D *H1, TH1D *H2, int IgnoreBin, bool UseError)
{
   if(H1 == nullptr)
      return 0;
   if(H2 == nullptr)
      return 0;

   int N = H1->GetNbinsX();

   double Chi2 = 0;

   for(int i = IgnoreBin + 1; i <= N; i++)
   {
      double V1 = H1->GetBinContent(i);
      double V2 = H2->GetBinContent(i);
      double E1 = H1->GetBinError(i);
      double E2 = H2->GetBinError(i);

      double D = V1 - V2;
      double Chi = (V1 - V2) / sqrt(E1 * E1 + E2 * E2);
      if(V1 == 0 && V2 == 0)
         continue;

      if(UseError == true)
         Chi2 = Chi2 + Chi * Chi;
      else
         Chi2 = Chi2 + D * D;
   }

   if(Chi2 != Chi2)
      return 0;

   return Chi2;
}





#include <iostream>
using namespace std;

#include "TH1D.h"
#include "TFile.h"
#include "TGraph.h"

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

   vector<int> Iteration{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 15, 20, 25, 30, 40, 50, 60, 70, 80, 90, 100, 125, 150, 175, 200, 250, 300, 350, 400, 450, 500};

   TGraph Graph;
   TGraph GraphD;

   TFile InputFile(InputFileName.c_str());

   TH1D *HMCTruth = (TH1D *)InputFile.Get(Reference.c_str());

   for(int i : Iteration)
   {
      TH1D *HUnfolded = (TH1D *)InputFile.Get(Form("HUnfoldedBayes%d", i));
      double Chi2 = CalculateChi2(HMCTruth, HUnfolded, PointsToIgnore, true);
      double D2 = CalculateChi2(HMCTruth, HUnfolded, PointsToIgnore, false);

      Graph.SetPoint(Graph.GetN(), i, Chi2);
      GraphD.SetPoint(GraphD.GetN(), i, D2);
   }

   InputFile.Close();

   PdfFileHelper PdfFile(OutputFileName);
   PdfFile.AddTextPage("Iteration scan");

   PdfFile.AddPlot(Graph, "apl");
   PdfFile.AddPlot(Graph, "apl", true, false, true, true);
   PdfFile.AddPlot(GraphD, "apl");
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





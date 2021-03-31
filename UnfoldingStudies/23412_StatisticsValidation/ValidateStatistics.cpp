#include <vector>
#include <iostream>
using namespace std;

#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TMatrixD.h"

#include "PlotHelper4.h"
#include "CommandLine.h"
#include "SetStyle.h"

int main(int argc, char *argv[]);
double CalculateSimpleChi2(TH1D *HMCTruth, TH1D *HUnfolded, int IgnoreBin = 0);

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   vector<string> InputFileNames = CL.GetStringVector("Input");
   string OutputFileName         = CL.Get("Output");
   string Method                 = CL.Get("Method", "UnfoldedBayes14");
   int IgnoreBin                 = CL.GetInt("IgnoreBin", 0);

   int BinCount = 0;
   if(InputFileNames.size() > 0)
   {
      TFile File(InputFileNames[0].c_str());
      TH1D *H = (TH1D *)File.Get("HMCTruth");
      BinCount = H->GetNbinsX();
      File.Close();
   }
   
   TH2D HPull("HPull", ";Bin;Pull", BinCount, 0, BinCount, 100, -5, 5);
   TH1D HPull1D("HPull1D", ";Pull;", 100, -5, 5);

   for(string FileName : InputFileNames)
   {
      TFile File(FileName.c_str());

      TH1D *HUnfolded = (TH1D *)File.Get(("H" + Method).c_str());
      TMatrixD Covariance = *((TMatrixD *)File.Get(("M" + Method).c_str()));

      TH1D *HTruth = (TH1D *)File.Get("HMCTruth");

      double SimpleChi2 = CalculateSimpleChi2(HTruth, HUnfolded, IgnoreBin);

      cout << SimpleChi2 << endl;

      for(int i = 1; i <= BinCount; i++)
      {
         double V1 = HUnfolded->GetBinContent(i);
         double V2 = HTruth->GetBinContent(i);
         double E = HUnfolded->GetBinError(i);
         HPull.Fill(i - 1, (V1 - V2) / E);

         if(i > IgnoreBin)
            HPull1D.Fill((V1 - V2) / E);
      }

      File.Close();
   }

   PdfFileHelper PdfFile(OutputFileName);
   PdfFile.AddTextPage("Statistics validation");

   PdfFile.AddPlot(HPull, "colz");
   PdfFile.AddPlot(HPull1D, "");

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

double CalculateSimpleChi2(TH1D *HMCTruth, TH1D *HUnfolded, int IgnoreBin)
{
   if(HMCTruth == nullptr || HUnfolded == nullptr)
      return 0;

   double Chi2 = 0;

   for(int i = IgnoreBin; i <= HMCTruth->GetNbinsX(); i++)
   {
      double V1 = HMCTruth->GetBinContent(i);
      double V2 = HUnfolded->GetBinContent(i);
      double E  = HUnfolded->GetBinError(i);

      Chi2 = Chi2 + (V1 - V2) * (V1 - V2) / E / E;
   }

   return Chi2;
}



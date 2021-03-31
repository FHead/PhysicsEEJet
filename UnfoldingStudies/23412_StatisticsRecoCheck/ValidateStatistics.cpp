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

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   vector<string> InputFileNames = CL.GetStringVector("Input");
   string OutputFileName         = CL.Get("Output");

   int BinCount = 0;
   if(InputFileNames.size() > 0)
   {
      TFile File(InputFileNames[0].c_str());
      TH1D *H = (TH1D *)File.Get("HShapeReco");
      BinCount = H->GetNbinsX();
      File.Close();
   }
   
   TH2D HRatio("HRatio", ";Bin;Ratio", BinCount, 0, BinCount, 100, 0.95, 1.05);

   for(string FileName : InputFileNames)
   {
      TFile File(FileName.c_str());

      TH1D *HSampled = (TH1D *)File.Get("HDataReco");
      TH1D *HTruth = (TH1D *)File.Get("HShapeReco");

      for(int i = 1; i <= BinCount; i++)
      {
         double V1 = HSampled->GetBinContent(i);
         double V2 = HTruth->GetBinContent(i);
         HRatio.Fill(i - 1, V1 / V2);
      }

      File.Close();
   }

   PdfFileHelper PdfFile(OutputFileName);
   PdfFile.AddTextPage("Statistics validation");

   PdfFile.AddPlot(HRatio, "colz");

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}


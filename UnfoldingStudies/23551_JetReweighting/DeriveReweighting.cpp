#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

#include "TCanvas.h"
#include "TH1D.h"
#include "TFile.h"
#include "TGraphAsymmErrors.h"
#include "TF1.h"

#include "CommandLine.h"
#include "DataHelper.h"
#include "PlotHelper4.h"
#include "SetStyle.h"

int main(int argc, char *argv[]);
vector<double> DetectBins(TH1D *HMin, TH1D *HMax);

int main(int argc, char *argv[])
{
   SetThumbStyle();

   CommandLine CL(argc, argv);

   string DataInputFileName = CL.Get("DataInput");
   string DataHistogramName = CL.Get("DataName");
   string MCInputFileName   = CL.Get("MCInput");
   string MCHistogramName   = CL.Get("MCName");

   string DHFileName        = CL.Get("DHFile", "Reweight.dh");
   string State             = CL.Get("State", "NominalReweight");

   TFile DataFile(DataInputFileName.c_str());
   TFile MCFile(MCInputFileName.c_str());

   TH1D *HData = (TH1D *)DataFile.Get(DataHistogramName.c_str());
   TH1D *HMC   = (TH1D *)MCFile.Get(MCHistogramName.c_str());

   vector<double> GenBins
      = DetectBins((TH1D *)DataFile.Get("HGenPrimaryBinMin"), (TH1D *)DataFile.Get("HGenPrimaryBinMax"));
   int PrimaryBinCount = GenBins.size() - 1;

   TGraphAsymmErrors G;

   string FormulaString = "0";

   double DataTotal = 0, MCTotal = 0;
   for(int iB = 0; iB < PrimaryBinCount; iB++)
   {
      DataTotal = DataTotal + HData->GetBinContent(iB + 1);
      MCTotal = MCTotal + HMC->GetBinContent(iB + 1);
   }

   for(int iB = 0; iB < PrimaryBinCount; iB++)
   {
      double BinCenter = (GenBins[iB] + GenBins[iB+1]) / 2;
      if(iB == 0)
         BinCenter = GenBins[1] - (GenBins[2] - GenBins[1]) / 2;
      if(iB == PrimaryBinCount - 1)
         BinCenter = GenBins[PrimaryBinCount-1] + (GenBins[PrimaryBinCount-1] - GenBins[PrimaryBinCount-2]) / 2;

      double X          = BinCenter;
      double DataY      = HData->GetBinContent(iB + 1) / DataTotal;
      double MCY        = HMC->GetBinContent(iB + 1) / MCTotal;
      double DataYError = HData->GetBinError(iB + 1) / DataTotal;
      double MCYError   = HMC->GetBinError(iB + 1) / MCTotal;

      if(MCY > 0)
      {
         double Ratio = DataY / MCY;
         double DataRelError = DataYError / DataY;
         double MCRelError = MCYError / MCY;
         double RelError = sqrt(DataRelError * DataRelError + MCRelError * MCRelError);

         int Index = G.GetN();
         G.SetPoint(Index, X, Ratio);
         G.SetPointError(Index, 0, 0, Ratio * RelError, Ratio * RelError);

         FormulaString = FormulaString
            + "+" + to_string(Ratio) + "*(x>" + to_string(GenBins[iB]) + "&&x<=" + to_string(GenBins[iB+1]) + ")";
      }
   }

   G.GetXaxis()->SetTitle("Jet Energy (GeV)");
   G.GetYaxis()->SetTitle("Ratio");

   PdfFileHelper PdfFile("ReweightingMeow.pdf");
   PdfFile.AddTextPage("Meow");

   PdfFile.AddPlot(G, "ap");

   TF1 F("F", FormulaString.c_str(), 0, 100);

   TCanvas Canvas;

   G.Draw("ap");
   F.Draw("same");

   PdfFile.AddCanvas(Canvas);

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   MCFile.Close();
   DataFile.Close();
   
   DataHelper DHFile(DHFileName);

   DHFile[State]["Formula"] = FormulaString;
   DHFile[State]["N"] = 0;

   DHFile.SaveToFile(DHFileName);

   return 0;
}

vector<double> DetectBins(TH1D *HMin, TH1D *HMax)
{
   if(HMin == nullptr || HMax == nullptr)
      return vector<double>{};

   vector<pair<double, double>> Bins;

   for(int i = 1; i <= HMin->GetNbinsX(); i++)
      Bins.push_back(pair<double, double>(HMin->GetBinContent(i), HMax->GetBinContent(i)));

   sort(Bins.begin(), Bins.end());
   auto iterator = unique(Bins.begin(), Bins.end());
   Bins.erase(iterator, Bins.end());

   vector<double> Result;
   for(auto iterator : Bins)
   {
      Result.push_back(iterator.first);
      Result.push_back(iterator.second);
   }

   sort(Result.begin(), Result.end());
   auto iterator2 = unique(Result.begin(), Result.end());
   Result.erase(iterator2, Result.end());

   return Result;
}


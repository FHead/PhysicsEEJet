#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
using namespace std;

#include "TFile.h"
#include "TH1D.h"
#include "TF1.h"

#include "CommandLine.h"
#include "DataHelper.h"
#include "PlotHelper4.h"
#include "Code/DrawRandom.h"
#include "SetStyle.h"

int main(int argc, char *argv[]);
vector<double> DetectBins(TH1D *HMin, TH1D *HMax);

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   string InputFileName   = CL.Get("Input");
   string State           = CL.Get("State");
   string BinningFileName = CL.Get("Binning");
   string OutputFileName  = CL.Get("Output");

   DataHelper DHFile(InputFileName);

   TF1 Function("Function", DHFile[State]["Formula"].GetString().c_str());

   TFile File(BinningFileName.c_str());
   vector<double> GenBins
      = DetectBins((TH1D *)File.Get("HGenPrimaryBinMin"), (TH1D *)File.Get("HGenPrimaryBinMax"));
   vector<double> BinningBins
      = DetectBins((TH1D *)File.Get("HGenBinningBinMin"), (TH1D *)File.Get("HGenBinningBinMax"));
   File.Close();

   int PrimaryBinCount = GenBins.size() - 1;
   int BinningBinCount = BinningBins.size() - 1;

   int N = DHFile[State]["N"].GetInteger();
   vector<double> P(N);
   vector<double> E(N);
   for(int i = 0; i < N; i++)
   {
      P[i] = DHFile[State]["P"+to_string(i)].GetDouble();
      E[i] = sqrt(DHFile[State]["C_"+to_string(i)+"_"+to_string(i)].GetDouble());
   }

   int Tries = 100000;

   TFile OutputFile(OutputFileName.c_str(), "RECREATE");

   int TotalBinCount = PrimaryBinCount * BinningBinCount;
   TH1D HNominal("HNominal", "", TotalBinCount, 0, TotalBinCount);
   TH1D HUp("HUp", "", TotalBinCount, 0, TotalBinCount);
   TH1D HDown("HDown", "", TotalBinCount, 0, TotalBinCount);
   TH1D HSymmetrized("HSymmetrized", "", TotalBinCount, 0, TotalBinCount);

   for(int iB = 0; iB < PrimaryBinCount; iB++)
   {
      double BinCenter = (GenBins[iB] + GenBins[iB+1]) / 2;
      if(iB == 0)
         BinCenter = GenBins[1] - (GenBins[2] - GenBins[1]) / 2;
      if(iB == PrimaryBinCount - 1)
         BinCenter = GenBins[PrimaryBinCount-1] + (GenBins[PrimaryBinCount-1] - GenBins[PrimaryBinCount-2]) / 2;

      vector<double> Values;
      for(int iT = 0; iT < Tries; iT++)
      {
         for(int iP = 0; iP < N; iP++)
            Function.SetParameter(iP, DrawGaussian(P[iP], E[iP]));
         Values.push_back(Function.Eval(BinCenter));
      }
      sort(Values.begin(), Values.end());

      for(int iP = 0; iP < N; iP++)
         Function.SetParameter(iP, P[iP]);

      double Min = Values[Values.size()*0.1585];
      double Max = Values[Values.size()*0.8415];
      double Value = Function.Eval(BinCenter);

      for(int i = 0; i < BinningBinCount; i++)
      {
         HNominal.SetBinContent(i * PrimaryBinCount + iB + 1, Value);
         HUp.SetBinContent(i * PrimaryBinCount + iB + 1, Max);
         HDown.SetBinContent(i * PrimaryBinCount + iB + 1, Min);
         HSymmetrized.SetBinContent(i * PrimaryBinCount + iB + 1, Value + (Max - Min) / 2);
         
         HNominal.SetBinError(i * PrimaryBinCount + iB + 1, 0);
         HUp.SetBinError(i * PrimaryBinCount + iB + 1, 0);
         HDown.SetBinError(i * PrimaryBinCount + iB + 1, 0);
         HSymmetrized.SetBinError(i * PrimaryBinCount + iB + 1, 0);
      }
   }

   HNominal.SetStats(0);
   HUp.SetStats(0);
   HDown.SetStats(0);
   HSymmetrized.SetStats(0);

   HNominal.Write();
   HUp.Write();
   HDown.Write();
   HSymmetrized.Write();

   PdfFileHelper PdfFile(OutputFileName + ".pdf");
   PdfFile.AddTextPage("Uncertainty from fits");

   TCanvas Canvas;

   HNominal.Draw();
   HUp.Draw("same");
   HDown.Draw("same");

   PdfFile.AddCanvas(Canvas);

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   OutputFile.Close();

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





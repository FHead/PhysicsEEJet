#include <iostream>
using namespace std;

#include "TFile.h"
#include "TH1D.h"
#include "TTree.h"
#include "TF1.h"

#include "CommandLine.h"
#include "CustomAssert.h"
#include "PlotHelper4.h"
#include "DataHelper.h"
#include "SetStyle.h"
#include "Code/TauHelperFunctions3.h"

int main(int argc, char *argv[]);
vector<double> DetectBins(TH1D *HMin, TH1D *HMax);
int FindBin(vector<double> &Bins, int Value);

int main(int argc, char *argv[])
{
   SetThumbStyle();

   CommandLine CL(argc, argv);

   string InputFileName    = CL.Get("Input");
   string BinningFileName  = CL.Get("Binning");
   string ReweightFileName = CL.Get("Reweight");
   string ReweightState    = CL.Get("State");
   string OutputBase       = CL.Get("OutputBase", "Meow");
   bool DoSum              = CL.GetBool("LeadingDiJetSum", false);

   DataHelper DHFile(ReweightFileName);
   TF1 F("F", DHFile[ReweightState]["Formula"].GetString().c_str());
   int NParameter = DHFile[ReweightState]["N"].GetInteger();
   for(int i = 0; i < NParameter; i++)
      F.SetParameter(i, DHFile[ReweightState]["P"+to_string(i)].GetDouble());

   TFile BinningFile(BinningFileName.c_str());
   vector<double> GenBins
      = DetectBins((TH1D *)BinningFile.Get("HGenPrimaryBinMin"), (TH1D *)BinningFile.Get("HGenPrimaryBinMax"));
   int BinCount = GenBins.size() - 1;
   BinningFile.Close();

   TFile InputFile(InputFileName.c_str());

   TTree *Tree = (TTree *)InputFile.Get("UnfoldingTree");
   Assert(Tree != nullptr, "Input tree is null!  Bailing out...");

   int NGenJets = 0;
   vector<float> *GenJetPX = nullptr;
   vector<float> *GenJetPY = nullptr;
   vector<float> *GenJetPZ = nullptr;
   vector<float> *GenJetE = nullptr;

   Tree->SetBranchAddress("NGenJets", &NGenJets);
   Tree->SetBranchAddress("GenJetPX", &GenJetPX);
   Tree->SetBranchAddress("GenJetPY", &GenJetPY);
   Tree->SetBranchAddress("GenJetPZ", &GenJetPZ);
   Tree->SetBranchAddress("GenJetE",  &GenJetE);

   TFile OutputFile((OutputBase + ".root").c_str(), "RECREATE");

   TH1D HWeight("HWeight", ";Event weight;", 100, 0, 10);
   TH1D HOriginal("HOriginal", ";Bin index;", BinCount, 0, BinCount);
   TH1D HVariation("HVariation", ";Bin index;", BinCount, 0, BinCount);
   TH1D HRatio("HRatio", ";Bin index;", BinCount, 0, BinCount);

   int EntryCount = Tree->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      Tree->GetEntry(iE);

      double EventWeight = 1;

      for(int iJ = 0; iJ < NGenJets; iJ++)
         EventWeight = EventWeight * F.Eval((*GenJetE)[iJ]);

      HWeight.Fill(EventWeight);

      if(NGenJets < 2)
         continue;

      FourVector Jet1((*GenJetE)[0], (*GenJetPX)[0], (*GenJetPY)[0], (*GenJetPZ)[0]);
      FourVector Jet2((*GenJetE)[1], (*GenJetPX)[1], (*GenJetPY)[1], (*GenJetPZ)[1]);

      if(Jet1.GetTheta() < 0.2 * M_PI || Jet1.GetTheta() > 0.8 * M_PI)
         continue;
      if(Jet2.GetTheta() < 0.2 * M_PI || Jet2.GetTheta() > 0.8 * M_PI)
         continue;

      if(DoSum == false)
      {
         int B1 = FindBin(GenBins, Jet1[0]);
         int B2 = FindBin(GenBins, Jet2[0]);

         HOriginal.AddBinContent(B1 + 1, 1);
         HOriginal.AddBinContent(B2 + 1, 1);
         HVariation.AddBinContent(B1 + 1, EventWeight);
         HVariation.AddBinContent(B2 + 1, EventWeight);
      }
      else
      {
         int B = FindBin(GenBins, Jet1[0] + Jet2[0]);
         HOriginal.AddBinContent(B + 1, 1);
         HVariation.AddBinContent(B + 1, EventWeight);
      }
   }

   for(int i = 1; i <= BinCount; i++)
      HRatio.SetBinContent(i, HVariation.GetBinContent(i) / HOriginal.GetBinContent(i));

   PdfFileHelper PdfFile(OutputBase + ".pdf");

   PdfFile.AddPlot(HWeight, "", true);

   HOriginal.SetStats(0);
   HVariation.SetStats(0);
   HVariation.SetLineColor(kRed);
   HRatio.SetStats(0);

   TCanvas Canvas;
   HOriginal.Draw();
   HVariation.Draw("same");
   PdfFile.AddCanvas(Canvas);

   HRatio.GetYaxis()->SetRangeUser(0.75, 1.25);
   PdfFile.AddPlot(HRatio);

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   HWeight.Write();
   HOriginal.Write();
   HVariation.Write();
   HRatio.Write();

   OutputFile.Close();

   InputFile.Close();

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

int FindBin(vector<double> &Bins, int Value)
{
   for(int i = 0; i < (int)Bins.size() - 1; i++)
      if(Bins[i] < Value && Value <= Bins[i+1])
         return i;
   return 0;
}

#include <iostream>
#include <vector>
using namespace std;

#include "TH1D.h"
#include "TFile.h"

#include "CustomAssert.h"
#include "CommandLine.h"

int main(int argc, char *argv[]);
vector<double> DetectBins(TH1D *HMin, TH1D *HMax);
void SelfNormalize(TH1D *H, int NormalizationGroupSize = -1);
void AddQuadrature(TH1D &HTotalPlus, TH1D &HTotalMinus, TH1D &HNominal, TH1D &HVariation);
void DoBridging(TH1D *HB, TH1D *H, int Pattern = 0);
void DoBridgingPattern1(TH1D *HB, TH1D *H);
void DoBridgingPattern2(TH1D *HB, TH1D *H);
void DoBridgingPattern3(TH1D *HB, TH1D *H);

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);

   vector<string> BaseFileNames      = CL.GetStringVector("BaseInput");
   vector<string> FileNames          = CL.GetStringVector("Input");
   vector<string> BaseHistogramNames = CL.GetStringVector("BaseHistogram");
   vector<string> HistogramNames     = CL.GetStringVector("Histogram");
   vector<string> Labels             = CL.GetStringVector("Label");
   vector<int> Groupings             = CL.GetIntVector("Group");
   vector<int> Bridging              = CL.GetIntVector("Bridging");
   vector<double> ExtraScaling       = CL.GetDoubleVector("ExtraScaling");
   string BinMappingFileName         = CL.Get("BinMapping");
   string OutputFileName             = CL.Get("Output");
   bool DoSelfNormalize              = CL.GetBool("DoSelfNormalize", false);

   Assert(FileNames.size() > 0, "No file names specified");
   Assert(FileNames.size() == HistogramNames.size(), "Inconsistent file name and histogram name");
   Assert(FileNames.size() == Labels.size(), "Inconsistent file name and label name");
   Assert(FileNames.size() == Groupings.size(), "Unknown uncertainty grouping");
   Assert(FileNames.size() == BaseFileNames.size(), "Inconsistent file name and base file name");
   Assert(FileNames.size() == BaseHistogramNames.size(), "Inconsistent file name and base histogram name");

   if(ExtraScaling.size() < FileNames.size())
      ExtraScaling.insert(ExtraScaling.end(), FileNames.size() - ExtraScaling.size(), 1);

   TFile OutputFile(OutputFileName.c_str(), "RECREATE");

   TFile BinMappingFile(BinMappingFileName.c_str());

   OutputFile.cd();
   BinMappingFile.Get("HGenPrimaryBinMin")->Clone()->Write();
   BinMappingFile.Get("HGenPrimaryBinMax")->Clone()->Write();
   BinMappingFile.Get("HGenBinningBinMin")->Clone()->Write();
   BinMappingFile.Get("HGenBinningBinMax")->Clone()->Write();
   BinMappingFile.Get("HRecoPrimaryBinMin")->Clone()->Write();
   BinMappingFile.Get("HRecoPrimaryBinMax")->Clone()->Write();
   BinMappingFile.Get("HRecoBinningBinMin")->Clone()->Write();
   BinMappingFile.Get("HRecoBinningBinMax")->Clone()->Write();
   BinMappingFile.Get("HMatchedPrimaryBinMin")->Clone()->Write();
   BinMappingFile.Get("HMatchedPrimaryBinMax")->Clone()->Write();
   BinMappingFile.Get("HMatchedBinningBinMin")->Clone()->Write();
   BinMappingFile.Get("HMatchedBinningBinMax")->Clone()->Write();
   
   int NormalizationGroupSize = DetectBins((TH1D *)BinMappingFile.Get("HGenPrimaryBinMin"), (TH1D *)BinMappingFile.Get("HGenPrimaryBinMax")).size() - 1;
   cout << "Detected group size = " << NormalizationGroupSize << endl;

   BinMappingFile.Close();

   TH1D *HTotalPlus = nullptr;
   TH1D *HTotalMinus = nullptr;

   int N = FileNames.size();

   for(int i = 0; i < N; i++)
   {
      TFile File(FileNames[i].c_str());
      TFile BaseFile(BaseFileNames[i].c_str());

      TH1D *H = (TH1D *)File.Get(HistogramNames[i].c_str());
      TH1D *HB = (TH1D *)BaseFile.Get(BaseHistogramNames[i].c_str());

      if(H != nullptr && HB != nullptr)
      {
         OutputFile.cd();
         TH1D *HCloned = (TH1D *)H->Clone(Form("H%s", Labels[i].c_str()));
         TH1D *HBCloned = (TH1D *)HB->Clone(Form("H%sBase", Labels[i].c_str()));

         HCloned->Scale(ExtraScaling[i]);

         if(HTotalPlus == nullptr && HTotalMinus == nullptr)
         {
            HTotalPlus = (TH1D *)HCloned->Clone("HTotalPlus");
            HTotalMinus = (TH1D *)HCloned->Clone("HTotalMinus");
            HTotalPlus->Reset();
            HTotalMinus->Reset();
         }
         if(DoSelfNormalize == true)
         {
            SelfNormalize(HCloned, NormalizationGroupSize);
            SelfNormalize(HBCloned, NormalizationGroupSize);
         }
         if(Bridging[i] > 0)
            DoBridging(HBCloned, HCloned, Bridging[i]);
         HCloned->Write();
         HBCloned->Write();

         if(Groupings[i] == 1)
            AddQuadrature(*HTotalPlus, *HTotalMinus, *HBCloned, *HCloned);
      }

      File.Close();
   }

   HTotalPlus->Write();
   HTotalMinus->Write();

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

void SelfNormalize(TH1D *H, int NormalizationGroupSize)
{
   if(H == nullptr)
      return;
   
   int BinningCount = H->GetNbinsX() / NormalizationGroupSize;
   if(BinningCount <= 0)
      BinningCount = 1;

   cout << H->GetNbinsX() << " " << NormalizationGroupSize << " " << BinningCount << endl;

   for(int iB = 0; iB < BinningCount; iB++)
   {
      double Total = 0;
      for(int i = 0; i < NormalizationGroupSize; i++)
         Total = Total + H->GetBinContent(i + 1 + iB * NormalizationGroupSize);
      
      for(int i = 0; i < NormalizationGroupSize; i++)
      {
         H->SetBinContent(i + 1 + iB * NormalizationGroupSize, H->GetBinContent(i + 1 + iB * NormalizationGroupSize) / Total);
         H->SetBinError(i + 1 + iB * NormalizationGroupSize, H->GetBinError(i + 1 + iB * NormalizationGroupSize) / Total);
      }
   }
}

void AddQuadrature(TH1D &HTotalPlus, TH1D &HTotalMinus, TH1D &HNominal, TH1D &HVariation)
{
   for(int i = 1; i <= HNominal.GetNbinsX(); i++)
   {
      double VN = HNominal.GetBinContent(i);
      double VV = HVariation.GetBinContent(i);
      
      if(VN == 0)
         continue;

      double Ratio = VV / VN - 1;

      double TotalPlus = HTotalPlus.GetBinContent(i);
      double TotalMinus = HTotalMinus.GetBinContent(i);

      TotalPlus = sqrt(TotalPlus * TotalPlus + Ratio * Ratio);
      TotalMinus = sqrt(TotalMinus * TotalMinus + Ratio * Ratio);

      HTotalPlus.SetBinContent(i, TotalPlus);
      HTotalMinus.SetBinContent(i, -TotalMinus);
   }
}

void DoBridging(TH1D *HB, TH1D *H, int Pattern)
{
   if(Pattern == 0)
      return;

   if(Pattern == 1)
      DoBridgingPattern1(HB, H);
   if(Pattern == 2)
      DoBridgingPattern2(HB, H);
   if(Pattern == 3)
      DoBridgingPattern3(HB, H);
}

void DoBridgingPattern1(TH1D *HB, TH1D *H)
{
   if(HB == nullptr || H == nullptr)
      return;

   int N = HB->GetNbinsX();
   vector<double> V(N);
   for(int i = 1; i <= N; i++)
      V[i-1] = fabs(H->GetBinContent(i) / HB->GetBinContent(i) - 1);

   double StartFraction = 0.5;
   int DecreaseBin = -1;
   for(int i = StartFraction * N; i < N - 1; i++)
   {
      if(V[i] > V[i-1])
      {
         DecreaseBin = i;
         break;
      }
   }

   if(DecreaseBin < 0)
      return;

   for(int i = DecreaseBin + 1; i < N - 2; i++)
      V[i] = V[DecreaseBin] + (V[N-1] - V[DecreaseBin]) / (N - 1 - DecreaseBin) * (i - DecreaseBin);

   for(int i = 1; i <= N; i++)
      H->SetBinContent(i, HB->GetBinContent(i) * (1 + V[i-1]));
}

void DoBridgingPattern2(TH1D *HB, TH1D *H)
{
   int Ignore = 1;

   if(HB == nullptr || H == nullptr)
      return;

   int N = HB->GetNbinsX();
   vector<double> V(N);
   for(int i = 1; i <= N; i++)
      V[i-1] = H->GetBinContent(i) / HB->GetBinContent(i) - 1;

   vector<int> Maximum(N);
   for(int i = 1; i < N - 1 - Ignore; i++)
   {
      if(V[i] > V[i-1] && V[i] > V[i+1] && V[i] > 0)
         Maximum[i] = 1;
      if(V[i] < V[i-1] && V[i] < V[i+1] && V[i] < 0)
         Maximum[i] = -1;
   }
   if(V[N-1-Ignore] > V[N-2-Ignore] && V[N-1-Ignore] > 0)
      Maximum[N-1-Ignore] = 1;
   if(V[N-1-Ignore] < V[N-2-Ignore] && V[N-1-Ignore] < 0)
      Maximum[N-1-Ignore] = -1;

   for(int i = 0; i < N; i++)
      V[i] = fabs(V[i]);

   int Start = -1;
   for(int i = 0; i < N; i++)
   {
      if(Maximum[i] == 0)
         continue;

      if(Start < 0)
      {
         Start = i;
         continue;
      }

      if(Maximum[Start] == Maximum[i])
      {
         Start = i;
         continue;
      }

      for(int j = Start + 1; j < i; j++)
         V[j] = V[Start] + (V[i] - V[Start]) / (i - Start) * (j - Start);
      Start = i;
   }   
   
   for(int i = 1; i <= N; i++)
      H->SetBinContent(i, HB->GetBinContent(i) * (1 + V[i-1]));
}

void DoBridgingPattern3(TH1D *HB, TH1D *H)
{
   int Ignore = 1;

   if(HB == nullptr || H == nullptr)
      return;

   int N = HB->GetNbinsX();
   vector<double> V(N);
   for(int i = 1; i <= N; i++)
      V[i-1] = H->GetBinContent(i) / HB->GetBinContent(i) - 1;

   vector<int> Maximum(N);
   for(int i = 1; i < N - 1 - Ignore; i++)
   {
      if(V[i] > V[i-1] && V[i] > V[i+1] && V[i] > 0)
         Maximum[i] = 1;
      if(V[i] < V[i-1] && V[i] < V[i+1] && V[i] < 0)
         Maximum[i] = -1;
   }
   if(V[N-1-Ignore] > V[N-2-Ignore] && V[N-1-Ignore] > 0)
      Maximum[N-1-Ignore] = 1;
   if(V[N-1-Ignore] < V[N-2-Ignore] && V[N-1-Ignore] < 0)
      Maximum[N-1-Ignore] = -1;

   for(int i = 0; i < N; i++)
      V[i] = fabs(V[i]);

   int Start = -1;
   for(int i = 0; i < N; i++)
   {
      if(Maximum[i] == 0)
         continue;

      if(Start < 0)
      {
         Start = i;
         continue;
      }

      if(Maximum[Start] == Maximum[i])
      {
         Start = i;
         continue;
      }

      for(int j = Start + 1; j < i; j++)
         V[j] = V[Start] + (V[i] - V[Start]) / (i - Start) * (j - Start);
      Start = i;
   }

   for(int i = N - 1; i >= 0; i--)
   {
      if(Maximum[i] == 0)
         continue;

      for(int j = i; j < N; j++)
         V[j] = V[i];
      break;
   }
   
   for(int i = 1; i <= N; i++)
      H->SetBinContent(i, HB->GetBinContent(i) * (1 + V[i-1]));
}


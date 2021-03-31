#include <iostream>
#include <cstdlib>
using namespace std;

#include "TFile.h"
#include "TH2D.h"
#include "TH1D.h"
#include "TKey.h"

#include "CommandLine.h"
#include "Code/DrawRandom.h"

int main(int argc, char *argv[]);
double GetRandom(TH1D *H);

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);

   string MCFileName = CL.Get("MC");
   string ShapeFileName = CL.Get("Shape");
   string OutputFileName = CL.Get("Output");
   string YieldFileName = CL.Get("Yield", ShapeFileName);
   double TargetFraction = CL.GetDouble("Fraction", 1.00);
   double RandomSeed = CL.GetDouble("Seed", 31426);

   srand(RandomSeed);

   TFile OutputFile(OutputFileName.c_str(), "RECREATE");

   TFile MCFile(MCFileName.c_str());

   TIter Iter(MCFile.GetListOfKeys());
   for(TKey *Key = (TKey *)Iter(); Key != nullptr; Key = (TKey *)Iter())
   {
      if(Key->ReadObj()->GetName() == TString("HDataReco"))
         continue;
      if(Key->ReadObj()->GetName() == TString("HMCGen"))
         continue;

      OutputFile.cd();
      Key->ReadObj()->Clone()->Write();
   }

   MCFile.Close();

   TFile YieldFile(YieldFileName.c_str());
   double TargetEventCount = ((TH1D *)YieldFile.Get("HDataReco"))->Integral() * TargetFraction;
   int ActualEvent = DrawPoisson(TargetEventCount);
   YieldFile.Close();
   
   TFile ShapeFile(ShapeFileName.c_str());

   OutputFile.cd();
   ShapeFile.Get("HMCGen")->Clone()->Write();

   TH1D *HShape = (TH1D *)ShapeFile.Get("HDataReco");
   TH1D *HNewData = (TH1D *)HShape->Clone();
   HNewData->Reset();
   for(int i = 0; i < ActualEvent; i++)
      HNewData->Fill(GetRandom(HShape));
   HNewData->SetName("HDataReco");
   HNewData->Write();

   HShape->SetName("HShapeReco");
   HShape->Write();

   ShapeFile.Close();

   OutputFile.Close();

   return 0;
}

double GetRandom(TH1D *H)
{
   if(H == nullptr)
      return 0;

   double Value = DrawRandom(0, H->Integral());

   double SoFar = 0;
   for(int i = 1; i <= H->GetNbinsX(); i++)
   {
      SoFar = SoFar + H->GetBinContent(i);
      if(SoFar >= Value)
         return H->GetBinCenter(i);
   }

   return 0;
}





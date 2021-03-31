#include <iostream>
using namespace std;

#include "TFile.h"
#include "TH2D.h"
#include "TH1D.h"
#include "TKey.h"

#include "CommandLine.h"
#include "Code/DrawRandom.h"

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);

   string MCFileName       = CL.Get("MC");
   string OutputFileName   = CL.Get("Output");
   string YieldFileName    = CL.Get("Yield", MCFileName);
   double TargetFraction   = CL.GetDouble("Fraction", 1.00);
   string GenFileName      = CL.Get("Gen", MCFileName);
   string GenHistogramName = CL.Get("GenHistogram", "HMCGen");

   TFile OutputFile(OutputFileName.c_str(), "RECREATE");

   TFile YieldFile(YieldFileName.c_str());
   double TargetEventCount = ((TH1D *)YieldFile.Get("HDataReco"))->Integral() * TargetFraction;
   YieldFile.Close();
   
   TFile MCFile(MCFileName.c_str());
   TFile GenFile(GenFileName.c_str());

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

   TH2D *HResponse = (TH2D *)MCFile.Get("HResponse");
   TH1D *HMCTruth  = (TH1D *)GenFile.Get(GenHistogramName.c_str());
   
   TH2D *HNormalizedResponse = (TH2D *)HResponse->Clone("HNormalizedResponse");
   HNormalizedResponse->Reset();

   OutputFile.cd();
   HMCTruth->Clone("HMCGen")->Write();

   TH1D *HDataReco = (TH1D *)MCFile.Get("HDataReco")->Clone();
   HDataReco->Reset();

   cout << HResponse->GetNbinsX() << " " << HMCTruth->GetNbinsX() << " " << HResponse->GetNbinsY() << endl;

   for(int iG = 1; iG <= HMCTruth->GetNbinsX(); iG++)
   {
      double V = HMCTruth->GetBinContent(iG);

      double N = 0;
      for(int iR = 1; iR <= HResponse->GetNbinsX(); iR++)
         N = N + HResponse->GetBinContent(iR, iG);
   
      if(N == 0)
      {
         cout << "Attention: N = " << N << ", V = " << V << endl;
         continue;
      }

      for(int iR = 1; iR <= HResponse->GetNbinsX(); iR++)
      {
         double R = HResponse->GetBinContent(iR, iG);
         HDataReco->AddBinContent(iR, V * R / N);

         HNormalizedResponse->SetBinContent(iR, iG, R / N);
      }
   }
   HDataReco->Scale(TargetEventCount / HDataReco->Integral());

   HDataReco->Write();
   HNormalizedResponse->Write();

   GenFile.Close();
   MCFile.Close();

   OutputFile.Close();

   return 0;
}






#include <vector>
using namespace std;

#include "TH1D.h"
#include "TH2D.h"
#include "TTree.h"
#include "TFile.h"

#include "CustomAssert.h"
#include "CommandLine.h"

enum ObservableType {ObservableNone, ObservableJetP, ObservableZG, ObservableRG, ObservableThrust};
enum ObservableStep {Gen, Reco, Matched};

class Messenger;
int main(int argc, char *argv[]);
void FillMinMax(TH1D &HMin1, TH1D &HMax1, TH1D &HMin2, TH1D &HMax2, vector<double> &Bin1, vector<double> &Bin2);

class Messenger
{
private:
   TTree *Tree;
   int NSD;
   vector<float>         *RecoJetP;
   vector<float>         *RecoJetTheta;
   vector<float>         *RecoJetJEC;
   vector<float>         *RecoJetJEU;
   vector<vector<float>> *RecoJetZG;
   vector<vector<float>> *RecoJetRG;
   float                  RecoThrust;
   vector<float>         *GenJetP;
   vector<float>         *GenJetTheta;
   vector<vector<float>> *GenJetZG;
   vector<vector<float>> *GenJetRG;
   float                  GenThrust;
   vector<float>         *MatchedJetP;
   vector<float>         *MatchedJetTheta;
   vector<float>         *MatchedJetJEC;
   vector<float>         *MatchedJetJEU;
   vector<vector<float>> *MatchedJetZG;
   vector<vector<float>> *MatchedJetRG;
   vector<float>         *MatchedJetAngle;
   float                  MatchedThrust;
public:
   Messenger()              { Initialize(nullptr); }
   Messenger(TTree *Tree)   { Initialize(Tree); }
   Messenger(TFile &File, string TreeName = "UnfoldingTree")
   {
      TTree *Tree = (TTree *)File.Get(TreeName.c_str());
      Initialize(Tree);
   }
   ~Messenger() {}
   void Initialize(TTree *InputTree = nullptr)
   {
      RecoJetP = nullptr;
      RecoJetTheta = nullptr;
      RecoJetJEC = nullptr;
      RecoJetJEU = nullptr;
      RecoJetZG = nullptr;
      RecoJetRG = nullptr;
      GenJetP = nullptr;
      GenJetTheta = nullptr;
      GenJetZG = nullptr;
      GenJetRG = nullptr;
      MatchedJetP = nullptr;
      MatchedJetTheta = nullptr;
      MatchedJetJEC = nullptr;
      MatchedJetJEU = nullptr;
      MatchedJetZG = nullptr;
      MatchedJetRG = nullptr;
      MatchedJetAngle = nullptr;

      Tree = InputTree;
      if(Tree == nullptr)
         return;

      Tree->SetBranchAddress("NSD", &NSD);
      Tree->SetBranchAddress("RecoJetP", &RecoJetP);
      Tree->SetBranchAddress("RecoJetTheta", &RecoJetTheta);
      Tree->SetBranchAddress("RecoJetJEC", &RecoJetJEC);
      Tree->SetBranchAddress("RecoJetJEU", &RecoJetJEU);
      Tree->SetBranchAddress("RecoJetZG", &RecoJetZG);
      Tree->SetBranchAddress("RecoJetRG", &RecoJetRG);
      Tree->SetBranchAddress("RecoThrust", &RecoThrust);
      Tree->SetBranchAddress("GenJetP", &GenJetP);
      Tree->SetBranchAddress("GenJetTheta", &GenJetTheta);
      Tree->SetBranchAddress("GenJetZG", &GenJetZG);
      Tree->SetBranchAddress("GenJetRG", &GenJetRG);
      Tree->SetBranchAddress("GenThrust", &GenThrust);
      Tree->SetBranchAddress("MatchedJetP", &MatchedJetP);
      Tree->SetBranchAddress("MatchedJetTheta", &MatchedJetTheta);
      Tree->SetBranchAddress("MatchedJetJEC", &MatchedJetJEC);
      Tree->SetBranchAddress("MatchedJetJEU", &MatchedJetJEU);
      Tree->SetBranchAddress("MatchedJetZG", &MatchedJetZG);
      Tree->SetBranchAddress("MatchedJetRG", &MatchedJetRG);
      Tree->SetBranchAddress("MatchedJetAngle", &MatchedJetAngle);
      Tree->SetBranchAddress("MatchedThrust", &MatchedThrust);
   }
   void GetEntry(int Entry)   { if(Tree != nullptr) Tree->GetEntry(Entry); }
   int GetEntries()           { if(Tree != nullptr) return Tree->GetEntries(); return 0;}
   double GetItemCount(ObservableStep Step, ObservableType &Type)
   {
      if(Type == ObservableThrust && Step == Gen)
         return 1;
      if(Type == ObservableThrust && Step == Reco)
         return 1;
      if(Type == ObservableThrust && Step == Matched)
         return 1;
      
      if(Type == ObservableJetP && Step == Gen)
         return GenJetP->size();
      if(Type == ObservableJetP && Step == Reco)
         return RecoJetP->size();
      if(Type == ObservableJetP && Step == Matched)
         return MatchedJetP->size();
      
      if(Type == ObservableZG && Step == Gen)
         return GenJetZG->size();
      if(Type == ObservableZG && Step == Reco)
         return RecoJetZG->size();
      if(Type == ObservableZG && Step == Matched)
         return MatchedJetZG->size();

      if(Type == ObservableRG && Step == Gen)
         return GenJetRG->size();
      if(Type == ObservableRG && Step == Reco)
         return RecoJetRG->size();
      if(Type == ObservableRG && Step == Matched)
         return MatchedJetRG->size();

      return 0;
   }
   double GetValue(ObservableStep Step, ObservableType &Type, int Index, int Item,
      double Shift = 0, double Smear = 1)
   {
      if(Type == ObservableThrust && Step == Gen)
         return GenThrust;
      if(Type == ObservableThrust && Step == Reco)
         return RecoThrust;
      if(Type == ObservableThrust && Step == Matched)
         return MatchedThrust;

      if(Type == ObservableJetP && Step == Gen && Item < GenJetP->size())
         return (*GenJetP)[Item];
      if(Type == ObservableJetP && Step == Reco && Item < RecoJetP->size())
      {
         double Value = (*RecoJetP)[Item];
         Value = Value * (1 + Shift * (*RecoJetJEU)[Item] / (*RecoJetJEC)[Item]);
         return Value;
      }
      if(Type == ObservableJetP && Step == Matched && Item < MatchedJetP->size())
      {
         double Value = (*MatchedJetP)[Item];
         Value = Value * (1 + Shift * (*MatchedJetJEU)[Item] / (*MatchedJetJEC)[Item]);
         Value = (Value - (*GenJetP)[Item]) * Smear + (*GenJetP)[Item];
         return Value;
      }
      
      if(Type == ObservableZG)
      {
         if(Step == Gen && Item < GenJetZG->size() && Index >= 0 && Index < (*GenJetZG)[Item].size())
            return (*GenJetZG)[Item][Index];
         if(Step == Reco && Item < RecoJetZG->size() && Index >= 0 && Index < (*RecoJetZG)[Item].size())
            return (*RecoJetZG)[Item][Index];
         if(Step == Matched && Item < MatchedJetZG->size() && Index >= 0 && Index < (*MatchedJetZG)[Item].size())
            return (*MatchedJetZG)[Item][Index];
      }

      if(Type == ObservableRG)
      {
         if(Step == Gen && Item < GenJetRG->size() && Index >= 0 && Index < (*GenJetRG)[Item].size())
            return (*GenJetRG)[Item][Index];
         if(Step == Reco && Item < RecoJetRG->size() && Index >= 0 && Index < (*RecoJetRG)[Item].size())
            return (*RecoJetRG)[Item][Index];
         if(Step == Matched && Item < MatchedJetRG->size() && Index >= 0 && Index < (*MatchedJetRG)[Item].size())
            return (*MatchedJetRG)[Item][Index];
      }

      return -1;
   }
   int GetSimpleBin(ObservableStep Step, ObservableType &Type, int Index, int Item, vector<double> &Bins,
      double Shift = 0, double Smear = 1)
   {
      if(Bins.size() == 0)
         return 0;

      double Value = GetValue(Step, Type, Index, Item, Shift, Smear);
      for(int i = 0; i < (int)Bins.size(); i++)
         if(Value < Bins[i])
            return i;

      return Bins.size();
   }
   int GetCompositeBin(ObservableStep Step,
      ObservableType &Type1, int Index1, int Item1, vector<double> &Bins1, double Shift1, double Smear1,
      ObservableType &Type2, int Index2, int Item2, vector<double> &Bins2, double Shift2, double Smear2)
   {
      // #1 is the primary binning, and #2 is the additional binning

      int SimpleBin1 = GetSimpleBin(Step, Type1, Index1, Item1, Bins1, Shift1, Smear1);
      int SimpleBin2 = GetSimpleBin(Step, Type2, Index2, Item2, Bins2, Shift2, Smear2);

      if(Type2 == ObservableNone)
         return SimpleBin1;

      return SimpleBin2 * (Bins1.size() + 1) + SimpleBin1;
   }
   double GetMatchedAngle(int Item)
   {
      if(Item < 0)                          return 999;
      if(Item >= MatchedJetAngle->size())   return 999;
      return (*MatchedJetAngle)[Item];
   }
};

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);
   string MCFileName     = CL.Get("MC");
   string DataFileName   = CL.Get("Data");
   string OutputFileName = CL.Get("Output");

   vector<double> Default{0.0, 1.0};
   string Primary                 = CL.Get("Observable", "JetP");
   int PrimaryIndex               = CL.GetInt("ObservableIndex", -1);
   vector<double> PrimaryGenBins  = CL.GetDoubleVector("ObservableGenBins", Default);
   vector<double> PrimaryRecoBins = CL.GetDoubleVector("ObservableRecoBins", Default);
   double PrimaryUncertaintyShift = CL.GetDouble("ObservableUncertaintyShift", 0);
   double PrimaryUncertaintySmear = CL.GetDouble("ObservableUncertaintySmear", 1);
   string Binning                 = CL.Get("Binning", "None");
   int BinningIndex               = CL.GetInt("BinningIndex", -1);
   vector<double> BinningGenBins  = CL.GetDoubleVector("BinningGenBins", Default);
   vector<double> BinningRecoBins = CL.GetDoubleVector("BinningRecoBins", Default);
   double BinningUncertaintyShift = CL.GetDouble("BinningUncertaintyShift", 0);
   double BinningUncertaintySmear = CL.GetDouble("BinningUncertaintySmear", 1);
   bool CheckMatchAngle           = CL.GetBool("CheckMatchAngle", true);

   sort(PrimaryGenBins.begin(), PrimaryGenBins.end());
   sort(PrimaryRecoBins.begin(), PrimaryRecoBins.end());
   sort(BinningGenBins.begin(), BinningGenBins.end());
   sort(BinningRecoBins.begin(), BinningRecoBins.end());

   ObservableType PrimaryType = ObservableNone;
   if(Primary == "JetP")   PrimaryType = ObservableJetP;
   if(Primary == "JetZG")  PrimaryType = ObservableZG;
   if(Primary == "ZG")     PrimaryType = ObservableZG;
   if(Primary == "JetRG")  PrimaryType = ObservableRG;
   if(Primary == "RG")     PrimaryType = ObservableRG;
   if(Primary == "Thrust") PrimaryType = ObservableThrust;
   ObservableType BinningType = ObservableNone;
   if(Binning == "JetP")   BinningType = ObservableJetP;
   if(Binning == "JetZG")  BinningType = ObservableZG;
   if(Binning == "ZG")     BinningType = ObservableZG;
   if(Binning == "JetRG")  BinningType = ObservableRG;
   if(Binning == "RG")     BinningType = ObservableRG;
   if(Binning == "Thrust") BinningType = ObservableThrust;

   if(BinningType == ObservableNone)
   {
      BinningGenBins.clear();
      BinningRecoBins.clear();
   }

   Assert(PrimaryType != ObservableNone, "Primary observable type is none");
   Assert(PrimaryType != ObservableZG || PrimaryIndex >= 0, "ZG chosen but index < 0");
   Assert(PrimaryType != ObservableRG || PrimaryIndex >= 0, "RG chosen but index < 0");
   Assert(BinningType != ObservableZG || BinningIndex >= 0, "ZG chosen but index < 0");
   Assert(BinningType != ObservableRG || BinningIndex >= 0, "RG chosen but index < 0");

   TFile FMC(MCFileName.c_str());
   TFile FData(DataFileName.c_str());
   TFile FOutput(OutputFileName.c_str(), "RECREATE");

   int GenBinCount = PrimaryGenBins.size() + 1;
   if(BinningType != ObservableNone)
      GenBinCount = GenBinCount * (BinningGenBins.size() + 1);
   int RecoBinCount = PrimaryRecoBins.size() + 1;
   if(BinningType != ObservableNone)
      RecoBinCount = RecoBinCount * (BinningRecoBins.size() + 1);
   int MatchedBinCount = PrimaryRecoBins.size() + 1;
   if(BinningType != ObservableNone)
      MatchedBinCount = MatchedBinCount * (BinningRecoBins.size() + 1);

   TH1D HMCGen("HMCGen", ";Gen", GenBinCount, 0, GenBinCount);
   TH1D HMCMatched("HMCMatched", ";Matched", MatchedBinCount, 0, MatchedBinCount);
   TH1D HMCReco("HMCReco", ";Reco", RecoBinCount, 0, RecoBinCount);
   TH2D HResponse("HResponse", ";Matched;Gen", MatchedBinCount, 0, MatchedBinCount, GenBinCount, 0, GenBinCount);
   TH1D HDataReco("HDataReco", ";Reco", RecoBinCount, 0, RecoBinCount);

   TH1D HGenPrimaryBinMin("HGenPrimaryBinMin", ";Gen;Min", GenBinCount, 0, GenBinCount);
   TH1D HGenPrimaryBinMax("HGenPrimaryBinMax", ";Gen;Max", GenBinCount, 0, GenBinCount);
   TH1D HGenBinningBinMin("HGenBinningBinMin", ";Gen;Min", GenBinCount, 0, GenBinCount);
   TH1D HGenBinningBinMax("HGenBinningBinMax", ";Gen;Max", GenBinCount, 0, GenBinCount);
   TH1D HRecoPrimaryBinMin("HRecoPrimaryBinMin", ";Reco;Min", RecoBinCount, 0, RecoBinCount);
   TH1D HRecoPrimaryBinMax("HRecoPrimaryBinMax", ";Reco;Max", RecoBinCount, 0, RecoBinCount);
   TH1D HRecoBinningBinMin("HRecoBinningBinMin", ";Reco;Min", RecoBinCount, 0, RecoBinCount);
   TH1D HRecoBinningBinMax("HRecoBinningBinMax", ";Reco;Max", RecoBinCount, 0, RecoBinCount);
   TH1D HMatchedPrimaryBinMin("HMatchedPrimaryBinMin", ";Matched;Min", MatchedBinCount, 0, MatchedBinCount);
   TH1D HMatchedPrimaryBinMax("HMatchedPrimaryBinMax", ";Matched;Max", MatchedBinCount, 0, MatchedBinCount);
   TH1D HMatchedBinningBinMin("HMatchedBinningBinMin", ";Matched;Min", MatchedBinCount, 0, MatchedBinCount);
   TH1D HMatchedBinningBinMax("HMatchedBinningBinMax", ";Matched;Max", MatchedBinCount, 0, MatchedBinCount);

   FillMinMax(HGenPrimaryBinMin, HGenPrimaryBinMax, HGenBinningBinMin,
      HGenBinningBinMax, PrimaryGenBins, BinningGenBins);
   FillMinMax(HRecoPrimaryBinMin, HRecoPrimaryBinMax, HRecoBinningBinMin,
      HRecoBinningBinMax, PrimaryRecoBins, BinningRecoBins);
   FillMinMax(HMatchedPrimaryBinMin, HMatchedPrimaryBinMax, HMatchedBinningBinMin,
      HMatchedBinningBinMax, PrimaryRecoBins, BinningRecoBins);

   Messenger MMC(FMC);
   int EntryCount = MMC.GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      MMC.GetEntry(iE);

      int NJet = MMC.GetItemCount(Gen, PrimaryType);
      for(int iJ = 0; iJ < NJet; iJ++)
      {
         int GenBin = MMC.GetCompositeBin(Gen,
            PrimaryType, PrimaryIndex, iJ, PrimaryGenBins, 0, 1,
            BinningType, BinningIndex, iJ, BinningGenBins, 0, 1);
         HMCGen.Fill(GenBin);
      }

      NJet = MMC.GetItemCount(Gen, PrimaryType);
      for(int iJ = 0; iJ < NJet; iJ++)
      {
         double Angle = MMC.GetMatchedAngle(iJ);
         if(CheckMatchAngle == true && (Angle > 0.2 || Angle < 0))
            continue;

         int GenBin = MMC.GetCompositeBin(Gen,
            PrimaryType, PrimaryIndex, iJ, PrimaryGenBins, 0, 1,
            BinningType, BinningIndex, iJ, BinningGenBins, 0, 1);
         int MatchedBin = MMC.GetCompositeBin(Matched,
            PrimaryType, PrimaryIndex, iJ, PrimaryRecoBins, PrimaryUncertaintyShift, PrimaryUncertaintySmear,
            BinningType, BinningIndex, iJ, BinningRecoBins, BinningUncertaintyShift, BinningUncertaintySmear);

         HMCMatched.Fill(MatchedBin);
         HResponse.Fill(MatchedBin, GenBin);
      }

      NJet = MMC.GetItemCount(Reco, PrimaryType);
      for(int iJ = 0; iJ < NJet; iJ++)
      {
         int RecoBin = MMC.GetCompositeBin(Reco,
            PrimaryType, PrimaryIndex, iJ, PrimaryRecoBins, 0, 1,
            BinningType, BinningIndex, iJ, BinningRecoBins, 0, 1);
         HMCReco.Fill(RecoBin);
      }
   }

   Messenger MData(FData);
   EntryCount = MData.GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      MData.GetEntry(iE);

      int NJet = MData.GetItemCount(Reco, PrimaryType);
      for(int iJ = 0; iJ < NJet; iJ++)
      {
         int RecoBin = MData.GetCompositeBin(Reco,
            PrimaryType, PrimaryIndex, iJ, PrimaryRecoBins, 0, 1,
            BinningType, BinningIndex, iJ, BinningRecoBins, 0, 1);
         HDataReco.Fill(RecoBin);
      }
   }

   FOutput.cd();
   HMCGen.Write();
   HMCMatched.Write();
   HMCReco.Write();
   HResponse.Write();
   HDataReco.Write();
   HGenPrimaryBinMin.Write();
   HGenPrimaryBinMax.Write();
   HGenBinningBinMin.Write();
   HGenBinningBinMax.Write();
   HRecoPrimaryBinMin.Write();
   HRecoPrimaryBinMax.Write();
   HRecoBinningBinMin.Write();
   HRecoBinningBinMax.Write();
   HMatchedPrimaryBinMin.Write();
   HMatchedPrimaryBinMax.Write();
   HMatchedBinningBinMin.Write();
   HMatchedBinningBinMax.Write();

   FOutput.Close();
   FData.Close();
   FMC.Close();

   return 0;
}

void FillMinMax(TH1D &HMin1, TH1D &HMax1, TH1D &HMin2, TH1D &HMax2, vector<double> &Bin1, vector<double> &Bin2)
{
   for(int iP = 0; iP <= Bin1.size(); iP++)
   {
      for(int iB = 0; iB <= Bin2.size(); iB++)
      {
         int Bin = iB * (Bin1.size() + 1) + iP + 1;

         if(iP == 0)
            HMin1.SetBinContent(Bin, -999);
         else
            HMin1.SetBinContent(Bin, Bin1[iP-1]);
         
         if(iP >= Bin1.size())
            HMax1.SetBinContent(Bin, 999);
         else
            HMax1.SetBinContent(Bin, Bin1[iP]);

         if(iB == 0)
            HMin2.SetBinContent(Bin, -999);
         else
            HMin2.SetBinContent(Bin, Bin2[iB-1]);
         
         if(iB >= Bin2.size())
            HMax2.SetBinContent(Bin, 999);
         else
            HMax2.SetBinContent(Bin, Bin2[iB]);
      }
   }
}




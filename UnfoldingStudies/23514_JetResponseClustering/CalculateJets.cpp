#include <map>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

#include "fastjet/ClusterSequence.hh"
using namespace fastjet;

#include "TH1D.h"
#include "TH2D.h"
#include "TTree.h"
#include "TFile.h"

#include "Code/DrawRandom.h"
#include "Code/TauHelperFunctions3.h"
#include "CommandLine.h"
#include "ProgressBar.h"
#include "CustomAssert.h"

#include "JetCorrector.h"
#include "CATree.h"

#define MAX 1000

int main(int argc, char *argv[]);
int FindBin(int N, double Bins[], double X);
bool DecreasingEnergy(pair<FourVector, PseudoJet> &V1, pair<FourVector, PseudoJet> &V2);
FourVector SmearAngle(FourVector P, double AngleSigma);

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);

   vector<string> InputFileName  = CL.GetStringVector("Input");
   string OutputFileName         = CL.Get("Output");
   bool IsMC                     = CL.GetBool("MC", false);
   bool BaselineCut              = CL.GetBool("BaselineCut", false);
   bool TighterChargedHadronCut  = CL.GetBool("TighterChargedHadronCut", false);
   bool UseStored                = CL.GetBool("UseStored", false);
   double ThetaMin               = CL.GetDouble("ThetaMin", 0.2 * M_PI);
   double ThetaMax               = CL.GetDouble("ThetaMax", 0.8 * M_PI);
   bool DoHybridSumE             = CL.GetBool("DoHybridSumE", false);
   double HybridJetMin           = CL.GetDouble("HybridJetMin", 5);
   double GenSumECut             = CL.GetDouble("GenSumECut", -99999);
   double RecoSumECut            = CL.GetDouble("RecoSumECut", -99999);
   bool DoSumESmear              = CL.GetBool("DoSumESmear", false);
   double SumESmear              = CL.GetDouble("SumESmear", 0.02);
   bool DoSJSmear                = CL.GetBool("DoSJSmear", false);
   vector<string> JECFiles       = CL.GetStringVector("JEC", vector<string>{});
   double Fraction               = CL.GetDouble("Fraction", 1.00);
   double JetR                   = CL.GetDouble("JetR", 0.4);
   string RecoTreeName           = CL.Get("RecoTreeName", "t");
   string GenTreeName            = CL.Get("GenTreeName", "tgenBefore");
   bool CheckLeadingGenDiJet     = CL.GetBool("CheckLeadingGenDiJet", false);
   bool IgnoreNeutral            = CL.GetBool("IgnoreNeutral", false);
   double MultiplicityEMin       = CL.GetDouble("MultiplicityEMin", 0);
   double MultiplicityThetaMin   = CL.GetDouble("MultiplicityThetaMin", ThetaMin);
   double MultiplicityThetaMax   = CL.GetDouble("MultiplicityThetaMax", ThetaMax);
   int GenMultiplicityMin        = CL.GetInt("GenMultiplicityMin", -1);
   int GenMultiplicityMax        = CL.GetInt("GenMultiplicityMax", -1);
   int RecoMultiplicityMin       = CL.GetInt("RecoMultiplicityMin", -1);
   int RecoMultiplicityMax       = CL.GetInt("RecoMultiplicityMax", -1);
   bool DoAuxiliary              = CL.GetBool("DoAuxiliary", true);

   Assert(!(UseStored && IgnoreNeutral), "Can't ignore neutral hadron if we use stored jets!");

   JetCorrector JEC(JECFiles);

   TFile OutputFile(OutputFileName.c_str(), "RECREATE");

   TTree OutputTree("UnfoldingTree", "Trees for unfolding studies");

   int NSD = 2;
   vector<float> SDZCut{0.1, 0.5};
   vector<float> SDBeta{0.0, 1.5};
   float RecoSumE;
   float RecoHybridE;
   int RecoMultiplicity;
   int GenMultiplicity;
   int NRecoJets;
   vector<float> RecoJetPX;
   vector<float> RecoJetPY;
   vector<float> RecoJetPZ;
   vector<float> RecoJetP;
   vector<float> RecoJetTheta;
   vector<float> RecoJetPhi;
   vector<float> RecoJetM;
   vector<float> RecoJetE;
   vector<float> RecoJetJEC;
   vector<float> RecoJetJEU;
   vector<int>   RecoJetN00;
   vector<int>   RecoJetN05;
   vector<int>   RecoJetN10;
   vector<int>   RecoJetN15;
   vector<vector<float>> RecoJetSJ1PX;
   vector<vector<float>> RecoJetSJ1PY;
   vector<vector<float>> RecoJetSJ1PZ;
   vector<vector<float>> RecoJetSJ1E;
   vector<vector<float>> RecoJetSJ2PX;
   vector<vector<float>> RecoJetSJ2PY;
   vector<vector<float>> RecoJetSJ2PZ;
   vector<vector<float>> RecoJetSJ2E;
   vector<vector<float>> RecoJetZG;   // first index is SD index, second index is jet
   vector<vector<float>> RecoJetRG;
   vector<vector<float>> RecoJetPG;
   vector<vector<float>> RecoJetMG;
   vector<vector<float>> RecoJetNG;
   float RecoThrust;
   float GenSumE;
   float GenHybridE;
   int NGenJets;
   vector<float> GenJetPX;
   vector<float> GenJetPY;
   vector<float> GenJetPZ;
   vector<float> GenJetP;
   vector<float> GenJetTheta;
   vector<float> GenJetPhi;
   vector<float> GenJetM;
   vector<float> GenJetE;
   vector<int>   GenJetN00;
   vector<int>   GenJetN05;
   vector<int>   GenJetN10;
   vector<int>   GenJetN15;
   vector<vector<float>> GenJetSJ1PX;
   vector<vector<float>> GenJetSJ1PY;
   vector<vector<float>> GenJetSJ1PZ;
   vector<vector<float>> GenJetSJ1E;
   vector<vector<float>> GenJetSJ2PX;
   vector<vector<float>> GenJetSJ2PY;
   vector<vector<float>> GenJetSJ2PZ;
   vector<vector<float>> GenJetSJ2E;
   vector<vector<float>> GenJetZG;
   vector<vector<float>> GenJetRG;
   vector<vector<float>> GenJetPG;
   vector<vector<float>> GenJetMG;
   vector<vector<float>> GenJetNG;
   float GenThrust;
   vector<float> MatchedJetPX;
   vector<float> MatchedJetPY;
   vector<float> MatchedJetPZ;
   vector<float> MatchedJetP;
   vector<float> MatchedJetTheta;
   vector<float> MatchedJetPhi;
   vector<float> MatchedJetM;
   vector<float> MatchedJetE;
   vector<int>   MatchedJetN00;
   vector<int>   MatchedJetN05;
   vector<int>   MatchedJetN10;
   vector<int>   MatchedJetN15;
   vector<vector<float>> MatchedJetSJ1PX;
   vector<vector<float>> MatchedJetSJ1PY;
   vector<vector<float>> MatchedJetSJ1PZ;
   vector<vector<float>> MatchedJetSJ1E;
   vector<vector<float>> MatchedJetSJ2PX;
   vector<vector<float>> MatchedJetSJ2PY;
   vector<vector<float>> MatchedJetSJ2PZ;
   vector<vector<float>> MatchedJetSJ2E;
   vector<vector<float>> MatchedJetZG;
   vector<vector<float>> MatchedJetRG;
   vector<vector<float>> MatchedJetPG;
   vector<vector<float>> MatchedJetMG;
   vector<vector<float>> MatchedJetNG;
   vector<float> MatchedJetJEC;
   vector<float> MatchedJetJEU;
   vector<float> MatchedJetAngle;

   OutputTree.Branch("NSD",                 &NSD,                 "NSD/I");
   OutputTree.Branch("SDZCut",              &SDZCut);
   OutputTree.Branch("SDBeta",              &SDBeta);
   OutputTree.Branch("RecoMultiplicity",    &RecoMultiplicity,    "RecoMultiplicity/I");
   OutputTree.Branch("GenMultiplicity",     &GenMultiplicity,     "GenMultiplicity/I");
   OutputTree.Branch("MatchedMultiplicity", &RecoMultiplicity,    "MatchedMultiplicity/I");
   OutputTree.Branch("RecoSumE",            &RecoSumE,            "RecoSumE/F");
   OutputTree.Branch("RecoHybridE",         &RecoHybridE,         "RecoHybridE/F");
   OutputTree.Branch("NRecoJets",           &NRecoJets,           "NRecoJets/I");
   OutputTree.Branch("RecoJetPX",           &RecoJetPX);
   OutputTree.Branch("RecoJetPY",           &RecoJetPY);
   OutputTree.Branch("RecoJetPZ",           &RecoJetPZ);
   OutputTree.Branch("RecoJetP",            &RecoJetP);
   OutputTree.Branch("RecoJetTheta",        &RecoJetTheta);
   OutputTree.Branch("RecoJetPhi",          &RecoJetPhi);
   OutputTree.Branch("RecoJetM",            &RecoJetM);
   OutputTree.Branch("RecoJetE",            &RecoJetE);
   OutputTree.Branch("RecoJetJEC",          &RecoJetJEC);
   OutputTree.Branch("RecoJetJEU",          &RecoJetJEU);
   if(DoAuxiliary == true)
   {
      OutputTree.Branch("RecoJetN00",          &RecoJetN00);
      OutputTree.Branch("RecoJetN05",          &RecoJetN05);
      OutputTree.Branch("RecoJetN10",          &RecoJetN10);
      OutputTree.Branch("RecoJetN15",          &RecoJetN15);
   }
   OutputTree.Branch("RecoJetSJ1PX",         &RecoJetSJ1PX);
   OutputTree.Branch("RecoJetSJ1PY",         &RecoJetSJ1PY);
   OutputTree.Branch("RecoJetSJ1PZ",         &RecoJetSJ1PZ);
   OutputTree.Branch("RecoJetSJ1E",         &RecoJetSJ1E);
   OutputTree.Branch("RecoJetSJ2PX",         &RecoJetSJ2PX);
   OutputTree.Branch("RecoJetSJ2PY",         &RecoJetSJ2PY);
   OutputTree.Branch("RecoJetSJ2PZ",         &RecoJetSJ2PZ);
   OutputTree.Branch("RecoJetSJ2E",         &RecoJetSJ2E);
   OutputTree.Branch("RecoJetZG",           &RecoJetZG);
   OutputTree.Branch("RecoJetRG",           &RecoJetRG);
   OutputTree.Branch("RecoJetPG",           &RecoJetPG);
   OutputTree.Branch("RecoJetMG",           &RecoJetMG);
   OutputTree.Branch("RecoJetNG",           &RecoJetNG);
   OutputTree.Branch("RecoThrust",          &RecoThrust);
   OutputTree.Branch("GenSumE",             &GenSumE,            "GenSumE/F");
   OutputTree.Branch("GenHybridE",          &GenHybridE,         "GenHybridE/F");
   OutputTree.Branch("NGenJets",            &NGenJets,           "NGenJets/I");
   OutputTree.Branch("GenJetPX",            &GenJetPX);
   OutputTree.Branch("GenJetPY",            &GenJetPY);
   OutputTree.Branch("GenJetPZ",            &GenJetPZ);
   OutputTree.Branch("GenJetP",             &GenJetP);
   OutputTree.Branch("GenJetTheta",         &GenJetTheta);
   OutputTree.Branch("GenJetPhi",           &GenJetPhi);
   OutputTree.Branch("GenJetM",             &GenJetM);
   OutputTree.Branch("GenJetE",             &GenJetE);
   if(DoAuxiliary == true)
   {
      OutputTree.Branch("GenJetN00",          &GenJetN00);
      OutputTree.Branch("GenJetN05",          &GenJetN05);
      OutputTree.Branch("GenJetN10",          &GenJetN10);
      OutputTree.Branch("GenJetN15",          &GenJetN15);
   }
   OutputTree.Branch("GenJetSJ1PX",          &GenJetSJ1PX);
   OutputTree.Branch("GenJetSJ1PY",          &GenJetSJ1PY);
   OutputTree.Branch("GenJetSJ1PZ",          &GenJetSJ1PZ);
   OutputTree.Branch("GenJetSJ1E",          &GenJetSJ1E);
   OutputTree.Branch("GenJetSJ2PX",          &GenJetSJ2PX);
   OutputTree.Branch("GenJetSJ2PY",          &GenJetSJ2PY);
   OutputTree.Branch("GenJetSJ2PZ",          &GenJetSJ2PZ);
   OutputTree.Branch("GenJetSJ2E",          &GenJetSJ2E);
   OutputTree.Branch("GenJetZG",            &GenJetZG);
   OutputTree.Branch("GenJetRG",            &GenJetRG);
   OutputTree.Branch("GenJetPG",            &GenJetPG);
   OutputTree.Branch("GenJetMG",            &GenJetMG);
   OutputTree.Branch("GenJetNG",            &GenJetNG);
   OutputTree.Branch("GenThrust",           &GenThrust);
   OutputTree.Branch("MatchedJetPX",        &MatchedJetPX);
   OutputTree.Branch("MatchedJetPY",        &MatchedJetPY);
   OutputTree.Branch("MatchedJetPZ",        &MatchedJetPZ);
   OutputTree.Branch("MatchedJetP",         &MatchedJetP);
   OutputTree.Branch("MatchedJetTheta",     &MatchedJetTheta);
   OutputTree.Branch("MatchedJetPhi",       &MatchedJetPhi);
   OutputTree.Branch("MatchedJetM",         &MatchedJetM);
   OutputTree.Branch("MatchedJetE",         &MatchedJetE);
   if(DoAuxiliary == true)
   {
      OutputTree.Branch("MatchedJetN00",          &MatchedJetN00);
      OutputTree.Branch("MatchedJetN05",          &MatchedJetN05);
      OutputTree.Branch("MatchedJetN10",          &MatchedJetN10);
      OutputTree.Branch("MatchedJetN15",          &MatchedJetN15);
   }
   OutputTree.Branch("MatchedJetSJ1PX",      &MatchedJetSJ1PX);
   OutputTree.Branch("MatchedJetSJ1PY",      &MatchedJetSJ1PY);
   OutputTree.Branch("MatchedJetSJ1PZ",      &MatchedJetSJ1PZ);
   OutputTree.Branch("MatchedJetSJ1E",      &MatchedJetSJ1E);
   OutputTree.Branch("MatchedJetSJ2PX",      &MatchedJetSJ2PX);
   OutputTree.Branch("MatchedJetSJ2PY",      &MatchedJetSJ2PY);
   OutputTree.Branch("MatchedJetSJ2PZ",      &MatchedJetSJ2PZ);
   OutputTree.Branch("MatchedJetSJ2E",      &MatchedJetSJ2E);
   OutputTree.Branch("MatchedJetZG",        &MatchedJetZG);
   OutputTree.Branch("MatchedJetRG",        &MatchedJetRG);
   OutputTree.Branch("MatchedJetPG",        &MatchedJetPG);
   OutputTree.Branch("MatchedJetMG",        &MatchedJetMG);
   OutputTree.Branch("MatchedJetNG",        &MatchedJetNG);
   OutputTree.Branch("MatchedJetAngle",     &MatchedJetAngle);
   OutputTree.Branch("MatchedJetJEC",       &MatchedJetJEC);
   OutputTree.Branch("MatchedJetJEU",       &MatchedJetJEU);
   OutputTree.Branch("MatchedThrust",       &RecoThrust);

   int PassedEventCount = 0;
   int AllEventCount = 0;
   int BaselineEventCount = 0;

   for(string FileName : InputFileName)
   {
      TFile InputFile(FileName.c_str());

      TTree *RecoTree    = (TTree *)InputFile.Get(RecoTreeName.c_str());
      TTree *GenTree     = (TTree *)InputFile.Get(GenTreeName.c_str());
      TTree *RecoJetTree = (TTree *)InputFile.Get("akR4ESchemeJetTree");
      TTree *GenJetTree  = (TTree *)InputFile.Get("akR4ESchemeGenJetTree");

      if(RecoTree == nullptr && GenTree == nullptr)
         continue;
      if(IsMC == true && GenTree == nullptr)
         continue;

      int RecoEventNumber;
      int NReco;
      float RecoPX[MAX];
      float RecoPY[MAX];
      float RecoPZ[MAX];
      float RecoP[MAX];
      float RecoMass[MAX];
      bool RecoHighPurity[MAX];
      short RecoCharge[MAX];
      short RecoType[MAX];
      bool RecoPassSTheta = true;
      bool RecoPassAll = true;
      int RecoChargedHadronsHP = 1000;
      int GenEventNumber;
      int NGen;
      float GenPX[MAX];
      float GenPY[MAX];
      float GenPZ[MAX];
      float GenMass[MAX];
      int GenStatus[MAX];
      bool GenPassSTheta = true;

      for(int i = 0; i < MAX; i++)
         GenStatus[i] = 1;
      
      if(GenTree != nullptr)
      {
         GenTree->SetBranchAddress("EventNo",      &GenEventNumber);
         GenTree->SetBranchAddress("nParticle",    &NGen);
         GenTree->SetBranchAddress("px",           &GenPX);
         GenTree->SetBranchAddress("py",           &GenPY);
         GenTree->SetBranchAddress("pz",           &GenPZ);
         GenTree->SetBranchAddress("mass",         &GenMass);
         if(GenTree->GetBranch("status") != nullptr)
            GenTree->SetBranchAddress("status",       &GenStatus);
         if(GenTree->GetBranch("Thrust") != nullptr)
            GenTree->SetBranchAddress("Thrust",       &GenThrust);
         if(GenTree->GetBranch("passSTheta") != nullptr)
            GenTree->SetBranchAddress("passesSTheta", &GenPassSTheta);
      }
      if(RecoTree != nullptr)
      {
         RecoTree->SetBranchAddress("EventNo",           &RecoEventNumber);
         RecoTree->SetBranchAddress("nParticle",         &NReco);
         RecoTree->SetBranchAddress("px",                &RecoPX);
         RecoTree->SetBranchAddress("py",                &RecoPY);
         RecoTree->SetBranchAddress("pz",                &RecoPZ);
         RecoTree->SetBranchAddress("pmag",              &RecoP);
         RecoTree->SetBranchAddress("mass",              &RecoMass);
         RecoTree->SetBranchAddress("highPurity",        &RecoHighPurity);
         RecoTree->SetBranchAddress("charge",            &RecoCharge);
         RecoTree->SetBranchAddress("pwflag",            &RecoType);
         RecoTree->SetBranchAddress("Thrust",            &RecoThrust);
         RecoTree->SetBranchAddress("passesAll",         &RecoPassAll);
         RecoTree->SetBranchAddress("passesSTheta",      &RecoPassSTheta);
         RecoTree->SetBranchAddress("nChargedHadronsHP", &RecoChargedHadronsHP);
      }
      
      int NStoredRecoJet;
      float StoredRecoJetPT[MAX];
      float StoredRecoJetEta[MAX];
      float StoredRecoJetPhi[MAX];
      float StoredRecoJetM[MAX];
      if(RecoJetTree != nullptr)
      {
         RecoJetTree->SetBranchAddress("nref",  &NStoredRecoJet);
         RecoJetTree->SetBranchAddress("jtpt",  &StoredRecoJetPT);
         RecoJetTree->SetBranchAddress("jteta", &StoredRecoJetEta);
         RecoJetTree->SetBranchAddress("jtphi", &StoredRecoJetPhi);
         RecoJetTree->SetBranchAddress("jtm",   &StoredRecoJetM);
      }

      int NStoredGenJet;
      float StoredGenJetPT[MAX];
      float StoredGenJetEta[MAX];
      float StoredGenJetPhi[MAX];
      float StoredGenJetM[MAX];
      if(GenJetTree != nullptr)
      {
         GenJetTree->SetBranchAddress("nref",  &NStoredGenJet);
         GenJetTree->SetBranchAddress("jtpt",  &StoredGenJetPT);
         GenJetTree->SetBranchAddress("jteta", &StoredGenJetEta);
         GenJetTree->SetBranchAddress("jtphi", &StoredGenJetPhi);
         GenJetTree->SetBranchAddress("jtm",   &StoredGenJetM);
      }

      int GenEntryShift = 0;

      int EntryCount = 0;
      if(RecoTree != nullptr)
         EntryCount = RecoTree->GetEntries() * Fraction;
      else if(GenTree != nullptr)
         EntryCount = GenTree->GetEntries() * Fraction;

      ProgressBar Bar(cout, EntryCount);
      Bar.SetStyle(2);

      for(int iE = 0; iE < EntryCount; iE++)
      {
         Bar.Update(iE);
         if(EntryCount < 1000 || iE % (EntryCount / 300) == 0)
            Bar.Print();

         // This is the number of events before doing anything!
         AllEventCount = AllEventCount + 1;

         // Reset things before getting data from the trees
         NGen = 0;
         NReco = 0;
         NStoredGenJet = 0;
         NStoredRecoJet = 0;

         if(GenTree != nullptr)       GenTree->GetEntry(iE + GenEntryShift);
         if(RecoTree != nullptr)      RecoTree->GetEntry(iE);

         if(GenTree != nullptr && RecoTree != nullptr)
         {
            while(GenEventNumber != RecoEventNumber)
            {
               GenEntryShift = GenEntryShift + 1;
               GenTree->GetEntry(iE + GenEntryShift);
            }
         }

         if(RecoJetTree != nullptr)   RecoJetTree->GetEntry(iE);
         if(GenJetTree != nullptr)    GenJetTree->GetEntry(iE);

         // Baseline cuts
         if(BaselineCut == true)
         {
            if(RecoPassAll == false)
               continue;
            if(TighterChargedHadronCut == true && RecoChargedHadronsHP <= 5)
               continue;
            // if(IsMC == true && GenPassSTheta == false)
            //    continue;
         }

         // Mercedes Benz rejection
         double PSum = 0;
         for(int i = 0; i < NReco; i++)
            PSum = PSum + RecoP[i];
         if(PSum > 200)
            continue;

         BaselineEventCount = BaselineEventCount + 1;

         // Calculate SumE and cut if needed
         GenSumE = 0;
         GenMultiplicity = 0;
         for(int i = 0; i < NGen; i++)
         {
            if(GenStatus[i] != 1)   // we want only final state particles
               continue;
            FourVector P(0, GenPX[i], GenPY[i], GenPZ[i]);
            P[0] = sqrt(P.GetP() * P.GetP() + GenMass[i] * GenMass[i]);
            if(P.GetTheta() < ThetaMin || P.GetTheta() > ThetaMax)
               continue;
            if(P[0] > MultiplicityEMin)
               GenMultiplicity = GenMultiplicity + 1;
            GenSumE = GenSumE + P[0];
         }
         if(DoHybridSumE == false && GenSumECut > 0 && GenSumE < GenSumECut)
            continue;
         if(GenMultiplicityMin >= 0 && GenMultiplicity < GenMultiplicityMin)
            continue;
         if(GenMultiplicityMax >= 0 && GenMultiplicity > GenMultiplicityMax)
            continue;
         
         RecoSumE = 0;
         RecoMultiplicity = 0;
         for(int i = 0; i < NReco; i++)
         {
            FourVector P(0, RecoPX[i], RecoPY[i], RecoPZ[i]);
            P[0] = sqrt(P.GetP() * P.GetP() + RecoMass[i] * RecoMass[i]);
            if(P.GetTheta() < ThetaMin || P.GetTheta() > ThetaMax)
               continue;
            if(P[0] > MultiplicityEMin)
               RecoMultiplicity = RecoMultiplicity + 1;
            RecoSumE = RecoSumE + P[0];
         }
         if(DoSumESmear == false)
         {
            if(DoHybridSumE == false && RecoSumECut > 0 && RecoSumE < RecoSumECut)
               continue;
         }
         else
         {
            if(DoHybridSumE == false && RecoSumECut > 0 && RecoSumE * DrawGaussian(1, SumESmear) < RecoSumECut)
               continue;
         }
         if(RecoMultiplicityMin >= 0 && RecoMultiplicity < RecoMultiplicityMin)
            continue;
         if(RecoMultiplicityMax >= 0 && RecoMultiplicity > RecoMultiplicityMax)
            continue;

         // Collect particles for jet clustering and other usages
         vector<FourVector> GenParticles;
         vector<PseudoJet> GenFJParticles;
         for(int i = 0; i < NGen; i++)
         {
            if(GenStatus[i] != 1 && GenStatus[i] != 0)
               continue;
            FourVector P(0, GenPX[i], GenPY[i], GenPZ[i]);
            P[0] = sqrt(P.GetP() * P.GetP() + GenMass[i] * GenMass[i]);
            GenParticles.emplace_back(P);
            GenFJParticles.emplace_back(P[1], P[2], P[3], P[0]);
         }

         vector<FourVector> RecoParticles;
         vector<PseudoJet> RecoFJParticles;
         for(int i = 0; i < NReco; i++)
         {
            FourVector P(0, RecoPX[i], RecoPY[i], RecoPZ[i]);
            P[0] = sqrt(P.GetP() * P.GetP() + RecoMass[i] * RecoMass[i]);
            RecoParticles.emplace_back(P);
            if(IgnoreNeutral == true && RecoCharge[i] == 0 && RecoType[i] == 5)
               continue;
            RecoFJParticles.emplace_back(P[1], P[2], P[3], P[0]);
         }

         // Cluster, or copy the jets from the trees
         vector<pair<FourVector, PseudoJet>> GenJets;
         vector<pair<FourVector, PseudoJet>> RecoJets;

         JetDefinition Definition(ee_genkt_algorithm, JetR, -1);
         ClusterSequence GenSequence(GenFJParticles, Definition);
         vector<PseudoJet> GenFastJets = GenSequence.inclusive_jets(0.5);
         ClusterSequence RecoSequence(RecoFJParticles, Definition);
         vector<PseudoJet> RecoFastJets = RecoSequence.inclusive_jets(0.5);

         if(UseStored == true)
         {
            GenJets.resize(NStoredGenJet);
            for(int i = 0; i < NStoredGenJet; i++)
            {
               GenJets[i].first.SetPtEtaPhiMass(StoredGenJetPT[i], StoredGenJetEta[i], StoredGenJetPhi[i], StoredGenJetM[i]);
               FourVector &J = GenJets[i].first;
               GenJets[i].second.reset_momentum(J[1], J[2], J[3], J[0]);
            }

            RecoJets.resize(NStoredRecoJet);
            for(int i = 0; i < NStoredRecoJet; i++)
            {
               RecoJets[i].first.SetPtEtaPhiMass(StoredRecoJetPT[i], StoredRecoJetEta[i], StoredRecoJetPhi[i], StoredRecoJetM[i]);
               FourVector &J = RecoJets[i].first;
               RecoJets[i].second.reset_momentum(J[1], J[2], J[3], J[0]);
            }
         }
         else
         {
            for(int i = 0 ; i < (int)GenFastJets.size(); i++)
            {
               FourVector P(GenFastJets[i].e(), GenFastJets[i].px(), GenFastJets[i].py(), GenFastJets[i].pz());
               GenJets.emplace_back(pair<FourVector, PseudoJet>(P, GenFastJets[i]));
            }

            for(int i = 0 ; i < (int)RecoFastJets.size(); i++)
            {
               FourVector P(RecoFastJets[i].e(), RecoFastJets[i].px(), RecoFastJets[i].py(), RecoFastJets[i].pz());
               RecoJets.emplace_back(pair<FourVector, PseudoJet>(P, RecoFastJets[i]));
            }
         }
         
         // cout << NGen << endl;
            
         // Apply JEC to reco jets
         for(int iR = 0; iR < (int)RecoJets.size(); iR++)
         {
            JEC.SetJetP(RecoJets[iR].first.GetP());
            JEC.SetJetE(RecoJets[iR].first[0]);
            JEC.SetJetTheta(RecoJets[iR].first.GetTheta());
            JEC.SetJetPhi(RecoJets[iR].first.GetPhi());
            double Correction = JEC.GetCorrection();
            if(Correction < 0)
               Correction = 1;
            RecoJets[iR].first = RecoJets[iR].first * Correction;
         }

         // Sort jets according to energy
         sort(GenJets.begin(), GenJets.end(), DecreasingEnergy);
         sort(RecoJets.begin(), RecoJets.end(), DecreasingEnergy);

         // What?
         // if(GenJets.size() > 0 && GenJets[0].first[0] < 10)
         // {
         //    for(int iJ = 0; iJ < GenJets.size(); iJ++)
         //       cout << iJ << " " << GenJets[iJ].first[0] << " " << GenJets[iJ].first.GetTheta() << endl;
         // }

         // Check leading jet if applicable
         if(CheckLeadingGenDiJet == true)
         {
            if(GenJets.size() >= 1 && GenJets[0].first.GetTheta() < ThetaMin)
               continue;
            if(GenJets.size() >= 1 && GenJets[0].first.GetTheta() > ThetaMax)
               continue;
            if(GenJets.size() >= 2 && GenJets[1].first.GetTheta() < ThetaMin)
               continue;
            if(GenJets.size() >= 2 && GenJets[1].first.GetTheta() > ThetaMax)
               continue;
         }

         // Remove jets out of the acceptance
         for(int i = 0; i < (int)GenJets.size(); i++)
         {
            if(GenJets[i].first.GetTheta() < ThetaMin || GenJets[i].first.GetTheta() > ThetaMax)
            {
               GenJets.erase(GenJets.begin() + i);
               i = i - 1;
            }
         }
         for(int i = 0; i < (int)RecoJets.size(); i++)
         {
            if(RecoJets[i].first.GetTheta() < ThetaMin || RecoJets[i].first.GetTheta() > ThetaMax)
            {
               RecoJets.erase(RecoJets.begin() + i);
               i = i - 1;
            }
         }

         // Now calculate hybrid E
         GenHybridE = 0;
         for(FourVector &P : GenParticles)
         {
            bool Include = false;

            if(P.GetTheta() > ThetaMin && P.GetTheta() < ThetaMax)
               Include = true;
            else
            {
               for(pair<FourVector, PseudoJet> &Pair : GenJets)
               {
                  FourVector &J = Pair.first;
                  if(J[0] < HybridJetMin)   continue;
                  if(GetAngle(P, J) > JetR) continue;
                  Include = true;
                  break;
               }
            }

            if(Include == true)
               GenHybridE = GenHybridE + P[0];
         }
         if(DoHybridSumE == true && GenSumECut > 0 && GenHybridE < GenSumECut)
            continue;

         RecoHybridE = 0;
         for(FourVector &P : RecoParticles)
         {
            bool Include = false;

            if(P.GetTheta() > ThetaMin && P.GetTheta() < ThetaMax)
               Include = true;
            else
            {
               for(pair<FourVector, PseudoJet> &Pair : RecoJets)
               {
                  FourVector &J = Pair.first;
                  if(J[0] < HybridJetMin)     continue;
                  if(GetAngle(P, J) > JetR)   continue;
                  Include = true;
                  break;
               }
            }

            if(Include == true)
               RecoHybridE = RecoHybridE + P[0];
         }
         if(DoSumESmear == false)
         {
            if(DoHybridSumE == true && RecoHybridE < RecoSumECut)
               continue;
         }
         else
         {
            if(DoHybridSumE == true && RecoHybridE * DrawGaussian(1, SumESmear) < RecoSumECut)
               continue;
         }
         
         // Now that all the preparation work is done, increment the event count by one
         PassedEventCount = PassedEventCount + 1;
 
         // Calculate groomed and auxiliary quantities for gen jets
         GenJetN00.clear();
         GenJetN05.clear();
         GenJetN10.clear();
         GenJetN15.clear();
         GenJetN00.resize(GenJets.size());
         GenJetN05.resize(GenJets.size());
         GenJetN10.resize(GenJets.size());
         GenJetN15.resize(GenJets.size());
         GenJetSJ1PX.resize(GenJets.size());
         GenJetSJ1PY.resize(GenJets.size());
         GenJetSJ1PZ.resize(GenJets.size());
         GenJetSJ1E.resize(GenJets.size());
         GenJetSJ2PX.resize(GenJets.size());
         GenJetSJ2PY.resize(GenJets.size());
         GenJetSJ2PZ.resize(GenJets.size());
         GenJetSJ2E.resize(GenJets.size());
         GenJetZG.resize(GenJets.size());
         GenJetRG.resize(GenJets.size());
         GenJetPG.resize(GenJets.size());
         GenJetMG.resize(GenJets.size());
         GenJetNG.resize(GenJets.size());
         for(int i = 0; i < (int)GenJets.size(); i++)
         {
            vector<Node *> Nodes;
            if(UseStored == true || GenJets[i].second.has_constituents() == false)
            {
               for(FourVector V : GenParticles)
               {
                  if(GetAngle(GenJets[i].first, V) < JetR)
                  {
                     Nodes.push_back(new Node(V));

                     if(V[0] > 0.0)   GenJetN00[i] = GenJetN00[i] + 1;
                     if(V[0] > 0.5)   GenJetN05[i] = GenJetN05[i] + 1;
                     if(V[0] > 1.0)   GenJetN10[i] = GenJetN10[i] + 1;
                     if(V[0] > 1.5)   GenJetN15[i] = GenJetN15[i] + 1;
                  }
               }
            }
            else   // we cluster jets ourselves.  We get the constituents!
            {
               vector<PseudoJet> Constituents = GenJets[i].second.constituents();
               for(PseudoJet &P : Constituents)
               {
                  FourVector V(P.e(), P.px(), P.py(), P.pz());
                  Nodes.push_back(new Node(V));

                  if(V[0] > 0.0)   GenJetN00[i] = GenJetN00[i] + 1;
                  if(V[0] > 0.5)   GenJetN05[i] = GenJetN05[i] + 1;
                  if(V[0] > 1.0)   GenJetN10[i] = GenJetN10[i] + 1;
                  if(V[0] > 1.5)   GenJetN15[i] = GenJetN15[i] + 1;
               }
            }
            BuildCATree(Nodes);
         
            GenJetSJ1PX[i].resize(NSD);
            GenJetSJ1PY[i].resize(NSD);
            GenJetSJ1PZ[i].resize(NSD);
            GenJetSJ1E[i].resize(NSD);
            GenJetSJ2PX[i].resize(NSD);
            GenJetSJ2PY[i].resize(NSD);
            GenJetSJ2PZ[i].resize(NSD);
            GenJetSJ2E[i].resize(NSD);
            GenJetZG[i].resize(NSD);
            GenJetRG[i].resize(NSD);
            GenJetPG[i].resize(NSD);
            GenJetMG[i].resize(NSD);
            GenJetNG[i].resize(NSD);

            if(Nodes.size() > 0)
            {
               for(int iSD = 0; iSD < NSD; iSD++)
               {
                  Node *SDNode = FindSDNodeE(Nodes[0], SDZCut[iSD], SDBeta[iSD]);
                  if(SDNode != nullptr && SDNode->Child1 != nullptr && SDNode->Child2 != nullptr)
                  {
                     FourVector &P1 = SDNode->Child1->P;
                     FourVector &P2 = SDNode->Child2->P;

                     GenJetSJ1PX[i][iSD] = P1[1];
                     GenJetSJ1PY[i][iSD] = P1[2];
                     GenJetSJ1PZ[i][iSD] = P1[3];
                     GenJetSJ1E[i][iSD] = P1[0];
                     GenJetSJ2PX[i][iSD] = P2[1];
                     GenJetSJ2PY[i][iSD] = P2[2];
                     GenJetSJ2PZ[i][iSD] = P2[3];
                     GenJetSJ2E[i][iSD] = P2[0];

                     // GenJetZG[i][iSD] = P2.GetP() / (P1.GetP() + P2.GetP());
                     GenJetZG[i][iSD] = min(P1[0], P2[0]) / (P1[0] + P2[0]);
                     GenJetRG[i][iSD] = GetAngle(P1, P2);
                     GenJetPG[i][iSD] = (P1 + P2).GetP();
                     GenJetMG[i][iSD] = (P1 + P2).GetMass();
                     GenJetNG[i][iSD] = CountFinalNode(SDNode);
                  }
                  else
                  {
                     GenJetSJ1PX[i][iSD] = 0;
                     GenJetSJ1PY[i][iSD] = 0;
                     GenJetSJ1PZ[i][iSD] = 0;
                     GenJetSJ1E[i][iSD] = 0;
                     GenJetSJ2PX[i][iSD] = 0;
                     GenJetSJ2PY[i][iSD] = 0;
                     GenJetSJ2PZ[i][iSD] = 0;
                     GenJetSJ2E[i][iSD] = 0;

                     GenJetZG[i][iSD] = -1;
                     GenJetRG[i][iSD] = -1;
                     GenJetPG[i][iSD] = -1;
                     GenJetMG[i][iSD] = -1;
                     GenJetNG[i][iSD] = -1;
                  }
               }
            }
         }

         // Groomed quantities and auxiliary stuff for reco jets
         RecoJetN00.clear();
         RecoJetN05.clear();
         RecoJetN10.clear();
         RecoJetN15.clear();
         RecoJetSJ1PX.resize(RecoJets.size());
         RecoJetSJ1PY.resize(RecoJets.size());
         RecoJetSJ1PZ.resize(RecoJets.size());
         RecoJetSJ1E.resize(RecoJets.size());
         RecoJetSJ2PX.resize(RecoJets.size());
         RecoJetSJ2PY.resize(RecoJets.size());
         RecoJetSJ2PZ.resize(RecoJets.size());
         RecoJetSJ2E.resize(RecoJets.size());
         RecoJetN00.resize(RecoJets.size());
         RecoJetN05.resize(RecoJets.size());
         RecoJetN10.resize(RecoJets.size());
         RecoJetN15.resize(RecoJets.size());
         RecoJetZG.resize(RecoJets.size());
         RecoJetRG.resize(RecoJets.size());
         RecoJetPG.resize(RecoJets.size());
         RecoJetMG.resize(RecoJets.size());
         RecoJetNG.resize(RecoJets.size());
         for(int i = 0; i < (int)RecoJets.size(); i++)
         {
            vector<Node *> Nodes;
            if(UseStored == true || RecoJets[i].second.has_constituents() == false)
            {
               for(FourVector V : RecoParticles)
               {
                  if(GetAngle(RecoJets[i].first, V) < JetR)
                  {
                     Nodes.push_back(new Node(V));

                     if(V[0] > 0.0)   RecoJetN00[i] = RecoJetN00[i] + 1;
                     if(V[0] > 0.5)   RecoJetN05[i] = RecoJetN05[i] + 1;
                     if(V[0] > 1.0)   RecoJetN10[i] = RecoJetN10[i] + 1;
                     if(V[0] > 1.5)   RecoJetN15[i] = RecoJetN15[i] + 1;
                  }
               }
            }
            else   // we cluster jets ourselves.  We get the constituents!
            {
               vector<PseudoJet> Constituents = RecoJets[i].second.constituents();
               for(PseudoJet &P : Constituents)
               {
                  FourVector V(P.e(), P.px(), P.py(), P.pz());
                  Nodes.push_back(new Node(V));

                  if(V[0] > 0.0)   RecoJetN00[i] = RecoJetN00[i] + 1;
                  if(V[0] > 0.5)   RecoJetN05[i] = RecoJetN05[i] + 1;
                  if(V[0] > 1.0)   RecoJetN10[i] = RecoJetN10[i] + 1;
                  if(V[0] > 1.5)   RecoJetN15[i] = RecoJetN15[i] + 1;
               }
            }
            BuildCATree(Nodes);
            
            RecoJetSJ1PX[i].resize(NSD);
            RecoJetSJ1PY[i].resize(NSD);
            RecoJetSJ1PZ[i].resize(NSD);
            RecoJetSJ1E[i].resize(NSD);
            RecoJetSJ2PX[i].resize(NSD);
            RecoJetSJ2PY[i].resize(NSD);
            RecoJetSJ2PZ[i].resize(NSD);
            RecoJetSJ2E[i].resize(NSD);
            RecoJetZG[i].resize(NSD);
            RecoJetRG[i].resize(NSD);
            RecoJetPG[i].resize(NSD);
            RecoJetMG[i].resize(NSD);
            RecoJetNG[i].resize(NSD);

            if(Nodes.size() > 0)
            {
               for(int iSD = 0; iSD < NSD; iSD++)
               {
                  double SC1 = 1, SC2 = 1;
                  Node *SDNode = nullptr;
                  if(DoSJSmear == false)
                     SDNode = FindSDNodeE(Nodes[0], SDZCut[iSD], SDBeta[iSD]);
                  else
                     SDNode = FindSDNodeESmear(Nodes[0], SC1, SC2, SDZCut[iSD], SDBeta[iSD], 0.03, 0.06);

                  if(SDNode != nullptr && SDNode->Child1 != nullptr && SDNode->Child2 != nullptr)
                  {
                     FourVector P1 = SDNode->Child1->P * SC1;
                     FourVector P2 = SDNode->Child2->P * SC2;

                     if(DoSJSmear == true)
                     {
                        P1 = SmearAngle(P1, 0.002);
                        P2 = SmearAngle(P2, 0.002);
                     }

                     RecoJetSJ1PX[i][iSD] = P1[1];
                     RecoJetSJ1PY[i][iSD] = P1[2];
                     RecoJetSJ1PZ[i][iSD] = P1[3];
                     RecoJetSJ1E[i][iSD] = P1[0];
                     RecoJetSJ2PX[i][iSD] = P2[1];
                     RecoJetSJ2PY[i][iSD] = P2[2];
                     RecoJetSJ2PZ[i][iSD] = P2[3];
                     RecoJetSJ2E[i][iSD] = P2[0];

                     // RecoJetZG[i][iSD] = P2.GetP() / (P1.GetP() + P2.GetP());
                     RecoJetZG[i][iSD] = min(P1[0], P2[0]) / (P1[0] + P2[0]);
                     RecoJetRG[i][iSD] = GetAngle(P1, P2);
                     RecoJetPG[i][iSD] = (P1 + P2).GetP();
                     RecoJetMG[i][iSD] = (P1 + P2).GetMass();
                     RecoJetNG[i][iSD] = CountFinalNode(SDNode);
                  }
                  else
                  {
                     RecoJetSJ1PX[i][iSD] = 0;
                     RecoJetSJ1PY[i][iSD] = 0;
                     RecoJetSJ1PZ[i][iSD] = 0;
                     RecoJetSJ1E[i][iSD] = 0;
                     RecoJetSJ2PX[i][iSD] = 0;
                     RecoJetSJ2PY[i][iSD] = 0;
                     RecoJetSJ2PZ[i][iSD] = 0;
                     RecoJetSJ2E[i][iSD] = 0;

                     RecoJetZG[i][iSD] = -1;
                     RecoJetRG[i][iSD] = -1;
                     RecoJetPG[i][iSD] = -1;
                     RecoJetMG[i][iSD] = -1;
                     RecoJetNG[i][iSD] = -1;
                  }
               }
            }
         }

         // Gen & reco jets: output
         NRecoJets = RecoJets.size();
         RecoJetPX.resize(NRecoJets);
         RecoJetPY.resize(NRecoJets);
         RecoJetPZ.resize(NRecoJets);
         RecoJetM.resize(NRecoJets);
         RecoJetE.resize(NRecoJets);
         RecoJetP.resize(NRecoJets);
         RecoJetTheta.resize(NRecoJets);
         RecoJetPhi.resize(NRecoJets);
         RecoJetJEC.resize(NRecoJets);
         RecoJetJEU.resize(NRecoJets);
         for(int iR = 0; iR < NRecoJets; iR++)
         {
            double Correction = RecoJets[iR].first[0] / RecoJets[iR].second.e();
            // double Correction = 1;
            double Uncertainty = 0.005;
            
            RecoJetPX[iR]    = RecoJets[iR].first[1];
            RecoJetPY[iR]    = RecoJets[iR].first[2];
            RecoJetPZ[iR]    = RecoJets[iR].first[3];
            RecoJetM[iR]     = RecoJets[iR].first.GetMass();
            RecoJetE[iR]     = RecoJets[iR].first[0];
            RecoJetP[iR]     = RecoJets[iR].first.GetP();
            RecoJetTheta[iR] = RecoJets[iR].first.GetTheta();
            RecoJetPhi[iR]   = RecoJets[iR].first.GetPhi();
            RecoJetJEC[iR]   = Correction;
            RecoJetJEU[iR]   = Uncertainty;
            
            for(int iSD = 0; iSD < NSD; iSD++)
            {
               RecoJetPG[iR][iSD] = RecoJetPG[iR][iSD] * Correction;
               RecoJetMG[iR][iSD] = RecoJetMG[iR][iSD] * Correction;
            }
         }
         
         NGenJets = GenJets.size();
         GenJetPX.resize(NGenJets);
         GenJetPY.resize(NGenJets);
         GenJetPZ.resize(NGenJets);
         GenJetM.resize(NGenJets);
         GenJetE.resize(NGenJets);
         GenJetP.resize(NGenJets);
         GenJetTheta.resize(NGenJets);
         GenJetPhi.resize(NGenJets);
         for(int iR = 0; iR < NGenJets; iR++)
         {
            GenJetPX[iR]    = GenJets[iR].first[1];
            GenJetPY[iR]    = GenJets[iR].first[2];
            GenJetPZ[iR]    = GenJets[iR].first[3];
            GenJetM[iR]     = GenJets[iR].first.GetMass();
            GenJetE[iR]     = GenJets[iR].first[0];
            GenJetP[iR]     = GenJets[iR].first.GetP();
            GenJetTheta[iR] = GenJets[iR].first.GetTheta();
            GenJetPhi[iR]   = GenJets[iR].first.GetPhi();
         }

         // Match reco to gen jets
         MatchedJetPX.resize(NGenJets);
         MatchedJetPY.resize(NGenJets);
         MatchedJetPZ.resize(NGenJets);
         MatchedJetM.resize(NGenJets);
         MatchedJetE.resize(NGenJets);
         MatchedJetP.resize(NGenJets);
         MatchedJetTheta.resize(NGenJets);
         MatchedJetPhi.resize(NGenJets);
         MatchedJetAngle.resize(NGenJets);
         MatchedJetJEC.resize(NGenJets);
         MatchedJetJEU.resize(NGenJets);
         MatchedJetN00.resize(NGenJets);
         MatchedJetN05.resize(NGenJets);
         MatchedJetN10.resize(NGenJets);
         MatchedJetN15.resize(NGenJets);
         MatchedJetSJ1PX.resize(NGenJets);
         MatchedJetSJ1PY.resize(NGenJets);
         MatchedJetSJ1PZ.resize(NGenJets);
         MatchedJetSJ1E.resize(NGenJets);
         MatchedJetSJ2PX.resize(NGenJets);
         MatchedJetSJ2PY.resize(NGenJets);
         MatchedJetSJ2PZ.resize(NGenJets);
         MatchedJetSJ2E.resize(NGenJets);
         MatchedJetZG.resize(NGenJets);
         MatchedJetRG.resize(NGenJets);
         MatchedJetPG.resize(NGenJets);
         MatchedJetMG.resize(NGenJets);
         MatchedJetNG.resize(NGenJets);
         for(int iG = 0; iG < NGenJets; iG++)
         {
            MatchedJetAngle[iG] = -1;

            int BestIndex = -1;
            double BestAngle = -1;
            for(int iR = 0; iR < NRecoJets; iR++)
            {
               double Angle = GetAngle(GenJets[iG].first, RecoJets[iR].first);
               if(BestAngle < 0 || Angle < BestAngle)
               {
                  BestIndex = iR;
                  BestAngle = Angle;
               }
            }

            MatchedJetSJ1PX[iG].resize(NSD, -1);
            MatchedJetSJ1PY[iG].resize(NSD, -1);
            MatchedJetSJ1PZ[iG].resize(NSD, -1);
            MatchedJetSJ1E[iG].resize(NSD, -1);
            MatchedJetSJ2PX[iG].resize(NSD, -1);
            MatchedJetSJ2PY[iG].resize(NSD, -1);
            MatchedJetSJ2PZ[iG].resize(NSD, -1);
            MatchedJetSJ2E[iG].resize(NSD, -1);
            MatchedJetZG[iG].resize(NSD, -1);
            MatchedJetRG[iG].resize(NSD, -1);
            MatchedJetPG[iG].resize(NSD, -1);
            MatchedJetMG[iG].resize(NSD, -1);
            MatchedJetNG[iG].resize(NSD, -1);

            if(BestIndex < 0)   // WTF
               continue;

            // Fill output tree with matched jets
            MatchedJetPX[iG]    = RecoJets[BestIndex].first[1];
            MatchedJetPY[iG]    = RecoJets[BestIndex].first[2];
            MatchedJetPZ[iG]    = RecoJets[BestIndex].first[3];
            MatchedJetM[iG]     = RecoJets[BestIndex].first.GetMass();
            MatchedJetE[iG]     = RecoJets[BestIndex].first[0];
            MatchedJetP[iG]     = RecoJets[BestIndex].first.GetP();
            MatchedJetTheta[iG] = RecoJets[BestIndex].first.GetTheta();
            MatchedJetPhi[iG]   = RecoJets[BestIndex].first.GetPhi();
            MatchedJetAngle[iG] = BestAngle;
            MatchedJetJEC[iG]   = RecoJetJEC[BestIndex];
            MatchedJetJEU[iG]   = RecoJetJEU[BestIndex];
            MatchedJetN00[iG]   = RecoJetN00[BestIndex];
            MatchedJetN05[iG]   = RecoJetN05[BestIndex];
            MatchedJetN10[iG]   = RecoJetN10[BestIndex];
            MatchedJetN15[iG]   = RecoJetN15[BestIndex];
            for(int iSD = 0; iSD < NSD; iSD++)
            {
               MatchedJetSJ1PX[iG][iSD] = RecoJetSJ1PX[BestIndex][iSD];
               MatchedJetSJ1PY[iG][iSD] = RecoJetSJ1PY[BestIndex][iSD];
               MatchedJetSJ1PZ[iG][iSD] = RecoJetSJ1PZ[BestIndex][iSD];
               MatchedJetSJ1E[iG][iSD] = RecoJetSJ1E[BestIndex][iSD];
               MatchedJetSJ2PX[iG][iSD] = RecoJetSJ2PX[BestIndex][iSD];
               MatchedJetSJ2PY[iG][iSD] = RecoJetSJ2PY[BestIndex][iSD];
               MatchedJetSJ2PZ[iG][iSD] = RecoJetSJ2PZ[BestIndex][iSD];
               MatchedJetSJ2E[iG][iSD] = RecoJetSJ2E[BestIndex][iSD];

               MatchedJetZG[iG][iSD] = RecoJetZG[BestIndex][iSD];
               MatchedJetRG[iG][iSD] = RecoJetRG[BestIndex][iSD];
               MatchedJetPG[iG][iSD] = RecoJetPG[BestIndex][iSD];
               MatchedJetMG[iG][iSD] = RecoJetMG[BestIndex][iSD];
               MatchedJetNG[iG][iSD] = RecoJetNG[BestIndex][iSD];
            }
         }

         OutputTree.Fill();
      }

      Bar.Update(EntryCount);
      Bar.Print();
      Bar.PrintLine();

      InputFile.Close();
   }

   OutputFile.cd();
   OutputTree.Write();

   TNamed Count;
   Count.SetNameTitle("EventCount", Form("%d", PassedEventCount));
   Count.Write();
   
   TNamed BaselineCount;
   BaselineCount.SetNameTitle("BaselineEventCount", Form("%d", BaselineEventCount));
   BaselineCount.Write();
   
   TNamed AllCount;
   AllCount.SetNameTitle("AllEventCount", Form("%d", AllEventCount));
   AllCount.Write();

   OutputFile.Close();

   return 0;
}

int FindBin(int N, double Bins[], double X)
{
   if(X < Bins[0])
      return -1;
   for(int i = 1; i <= N; i++)
      if(X < Bins[i])
         return i - 1;
   return N - 1;
}

bool DecreasingEnergy(pair<FourVector, PseudoJet> &V1, pair<FourVector, PseudoJet> &V2)
{
   return V1.first[0] > V2.first[0];
}

FourVector SmearAngle(FourVector P, double AngleSigma)
{
   // We assume sigma is small in this version of the code.
   // If it's too big we need (a bit) more sophistication

   FourVector PHat = P / P.GetP();

   FourVector PZ(1, 0, 0, 1);
   if(P[1] == 0 && P[2] == 0)
      PZ = FourVector(1, 1, 0, 0);
   FourVector A = PHat.SpatialCross(PZ);
   A = A / A.GetP();
   FourVector B = PHat.SpatialCross(A);
   B = B / B.GetP();

   PHat = PHat + A * DrawGaussian(AngleSigma) + B * DrawGaussian(AngleSigma);
   PHat = PHat / PHat.GetP();

   P[1] = PHat[1] * P.GetP();
   P[2] = PHat[2] * P.GetP();
   P[3] = PHat[3] * P.GetP();

   return P;
}










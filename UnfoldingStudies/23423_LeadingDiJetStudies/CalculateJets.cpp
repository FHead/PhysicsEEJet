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

#include "JetCorrector.h"
#include "CATree.h"

#define MAX 1000

int main(int argc, char *argv[]);
int FindBin(int N, double Bins[], double X);
bool DecreasingEnergy(FourVector &V1, FourVector &V2);

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);

   vector<string> InputFileName  = CL.GetStringVector("Input");
   string OutputFileName         = CL.Get("Output");
   bool IsMC                     = CL.GetBool("MC", false);
   bool BaselineCut              = CL.GetBool("BaselineCut", false);
   bool UseStored                = CL.GetBool("UseStored", false);
   double ThetaMin               = CL.GetDouble("ThetaMin", 0.2 * M_PI);
   double ThetaMax               = CL.GetDouble("ThetaMax", 0.8 * M_PI);
   vector<string> JECFiles       = CL.GetStringVector("JEC", vector<string>{});
   double Fraction               = CL.GetDouble("Fraction", 1.00);
   double JetR                   = CL.GetDouble("JetR", 0.4);
   string RecoTreeName           = CL.Get("RecoTreeName", "t");
   string GenTreeName            = CL.Get("GenTreeName", "tgenBefore");

   JetCorrector JEC(JECFiles);

   TFile OutputFile(OutputFileName.c_str(), "RECREATE");

   TTree OutputTree("UnfoldingTree", "Trees for unfolding studies");

   int NSD = 2;
   vector<float> SDZCut{0.1, 0.5};
   vector<float> SDBeta{0.0, 1.5};
   int NSumE = 5;
   vector<float> SumECut{0.08, 0.10, 0.12, 0.15, 0.20};
   float RecoSumE;
   float RecoSumE008;
   float RecoSumE010;
   float RecoSumE012;
   float RecoSumE015;
   float RecoSumE020;
   float RecoHybridE008;
   float RecoHybridE010;
   float RecoHybridE012;
   float RecoHybridE015;
   float RecoHybridE020;
   int NRecoJets;
   vector<float> RecoJetPX;
   vector<float> RecoJetPY;
   vector<float> RecoJetPZ;
   vector<float> RecoJetP;
   vector<float> RecoJetTheta;
   vector<float> RecoJetPhi;
   vector<float> RecoJetE;
   vector<float> RecoJetJEC;
   vector<float> RecoJetJEU;
   vector<vector<float>> RecoJetZG;   // first index is SD index, second index is jet
   vector<vector<float>> RecoJetRG;
   vector<vector<float>> RecoJetPG;
   vector<vector<float>> RecoJetMG;
   vector<vector<float>> RecoJetNG;
   float RecoThrust;
   float GenSumE;
   float GenSumE008;
   float GenSumE010;
   float GenSumE012;
   float GenSumE015;
   float GenSumE020;
   float GenHybridE008;
   float GenHybridE010;
   float GenHybridE012;
   float GenHybridE015;
   float GenHybridE020;
   int NGenJets;
   vector<float> GenJetPX;
   vector<float> GenJetPY;
   vector<float> GenJetPZ;
   vector<float> GenJetP;
   vector<float> GenJetTheta;
   vector<float> GenJetPhi;
   vector<float> GenJetE;
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
   vector<float> MatchedJetE;
   vector<vector<float>> MatchedJetZG;
   vector<vector<float>> MatchedJetRG;
   vector<vector<float>> MatchedJetPG;
   vector<vector<float>> MatchedJetMG;
   vector<vector<float>> MatchedJetNG;
   vector<float> MatchedJetJEC;
   vector<float> MatchedJetJEU;
   vector<float> MatchedJetAngle;

   OutputTree.Branch("NSD",             &NSD, "NSD/I");
   OutputTree.Branch("SDZCut",          &SDZCut);
   OutputTree.Branch("SDBeta",          &SDBeta);
   OutputTree.Branch("NSumE",           &NSumE, "NSumE/I");
   OutputTree.Branch("SumECut",         &SumECut);
   OutputTree.Branch("RecoSumE",        &RecoSumE);
   OutputTree.Branch("RecoSumE008",     &RecoSumE008);
   OutputTree.Branch("RecoSumE010",     &RecoSumE010);
   OutputTree.Branch("RecoSumE012",     &RecoSumE012);
   OutputTree.Branch("RecoSumE015",     &RecoSumE015);
   OutputTree.Branch("RecoSumE020",     &RecoSumE020);
   OutputTree.Branch("NRecoJets",       &NRecoJets, "NRecoJets/I");
   OutputTree.Branch("RecoJetPX",       &RecoJetPX);
   OutputTree.Branch("RecoJetPY",       &RecoJetPY);
   OutputTree.Branch("RecoJetPZ",       &RecoJetPZ);
   OutputTree.Branch("RecoJetP",        &RecoJetP);
   OutputTree.Branch("RecoJetTheta",    &RecoJetTheta);
   OutputTree.Branch("RecoJetPhi",      &RecoJetPhi);
   OutputTree.Branch("RecoJetE",        &RecoJetE);
   OutputTree.Branch("RecoJetJEC",      &RecoJetJEC);
   OutputTree.Branch("RecoJetJEU",      &RecoJetJEU);
   OutputTree.Branch("RecoJetZG",       &RecoJetZG);
   OutputTree.Branch("RecoJetRG",       &RecoJetRG);
   OutputTree.Branch("RecoJetPG",       &RecoJetPG);
   OutputTree.Branch("RecoJetMG",       &RecoJetMG);
   OutputTree.Branch("RecoJetNG",       &RecoJetNG);
   OutputTree.Branch("RecoThrust",      &RecoThrust);
   OutputTree.Branch("GenSumE",         &GenSumE);
   OutputTree.Branch("GenSumE008",      &GenSumE008);
   OutputTree.Branch("GenSumE010",      &GenSumE010);
   OutputTree.Branch("GenSumE012",      &GenSumE012);
   OutputTree.Branch("GenSumE015",      &GenSumE015);
   OutputTree.Branch("GenSumE020",      &GenSumE020);
   OutputTree.Branch("GenHybridE020",   &GenHybridE020);
   OutputTree.Branch("NGenJets",        &NGenJets, "NGenJets/I");
   OutputTree.Branch("GenJetPX",        &GenJetPX);
   OutputTree.Branch("GenJetPY",        &GenJetPY);
   OutputTree.Branch("GenJetPZ",        &GenJetPZ);
   OutputTree.Branch("GenJetP",         &GenJetP);
   OutputTree.Branch("GenJetTheta",     &GenJetTheta);
   OutputTree.Branch("GenJetPhi",       &GenJetPhi);
   OutputTree.Branch("GenJetE",         &GenJetE);
   OutputTree.Branch("GenJetZG",        &GenJetZG);
   OutputTree.Branch("GenJetRG",        &GenJetRG);
   OutputTree.Branch("GenJetPG",        &GenJetPG);
   OutputTree.Branch("GenJetMG",        &GenJetMG);
   OutputTree.Branch("GenJetNG",        &GenJetNG);
   OutputTree.Branch("GenThrust",       &GenThrust);
   OutputTree.Branch("MatchedJetPX",    &MatchedJetPX);
   OutputTree.Branch("MatchedJetPY",    &MatchedJetPY);
   OutputTree.Branch("MatchedJetPZ",    &MatchedJetPZ);
   OutputTree.Branch("MatchedJetP",     &MatchedJetP);
   OutputTree.Branch("MatchedJetTheta", &MatchedJetTheta);
   OutputTree.Branch("MatchedJetPhi",   &MatchedJetPhi);
   OutputTree.Branch("MatchedJetE",     &MatchedJetE);
   OutputTree.Branch("MatchedJetZG",    &MatchedJetZG);
   OutputTree.Branch("MatchedJetRG",    &MatchedJetRG);
   OutputTree.Branch("MatchedJetPG",    &MatchedJetPG);
   OutputTree.Branch("MatchedJetMG",    &MatchedJetMG);
   OutputTree.Branch("MatchedJetNG",    &MatchedJetNG);
   OutputTree.Branch("MatchedJetAngle", &MatchedJetAngle);
   OutputTree.Branch("MatchedJetJEC",   &MatchedJetJEC);
   OutputTree.Branch("MatchedJetJEU",   &MatchedJetJEU);
   OutputTree.Branch("MatchedThrust",   &RecoThrust);

   int PassedEventCount = 0;

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

      int NReco;
      float RecoPX[MAX];
      float RecoPY[MAX];
      float RecoPZ[MAX];
      float RecoP[MAX];
      float RecoMass[MAX];
      bool RecoHighPurity[MAX];
      bool RecoPassSTheta = true;
      bool RecoPassAll = true;
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
         GenTree->SetBranchAddress("nParticle",    &NGen);
         GenTree->SetBranchAddress("px",           &GenPX);
         GenTree->SetBranchAddress("py",           &GenPY);
         GenTree->SetBranchAddress("pz",           &GenPZ);
         GenTree->SetBranchAddress("mass",         &GenMass);
         if(GenTree->GetBranch("status") != nullptr)
            GenTree->SetBranchAddress("status",       &GenStatus);
         GenTree->SetBranchAddress("Thrust",       &GenThrust);
         GenTree->SetBranchAddress("passesSTheta", &GenPassSTheta);
      }
      if(RecoTree != nullptr)
      {
         RecoTree->SetBranchAddress("nParticle",    &NReco);
         RecoTree->SetBranchAddress("px",           &RecoPX);
         RecoTree->SetBranchAddress("py",           &RecoPY);
         RecoTree->SetBranchAddress("pz",           &RecoPZ);
         RecoTree->SetBranchAddress("pmag",         &RecoP);
         RecoTree->SetBranchAddress("mass",         &RecoMass);
         RecoTree->SetBranchAddress("highPurity",   &RecoHighPurity);
         RecoTree->SetBranchAddress("Thrust",       &RecoThrust);
         RecoTree->SetBranchAddress("passesAll",    &RecoPassAll);
         RecoTree->SetBranchAddress("passesSTheta", &RecoPassSTheta);
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

      int EntryCount = 0;
      if(RecoTree != nullptr)
         EntryCount = RecoTree->GetEntries() * Fraction;
      else if(GenTree != nullptr)
         EntryCount = GenTree->GetEntries() * Fraction;
      for(int iE = 0; iE < EntryCount; iE++)
      {
         NGen = 0;
         NReco = 0;
         NStoredGenJet = 0;
         NStoredRecoJet = 0;

         if(GenTree != nullptr)       GenTree->GetEntry(iE);
         if(RecoTree != nullptr)      RecoTree->GetEntry(iE);

         if(RecoJetTree != nullptr)   RecoJetTree->GetEntry(iE);
         if(GenJetTree != nullptr)    GenJetTree->GetEntry(iE);

         if(BaselineCut == true)
         {
            if(RecoPassAll == false)
               continue;
            if(IsMC == true && GenPassSTheta == false)
               continue;
         }

         // if(fabs(cos(RecoSTheta)) > 0.8)
         //    continue;
         // if(IsMC == true && fabs(cos(GenSTheta)) > 0.8)
         //    continue;

         double PSum = 0;
         for(int i = 0; i < NReco; i++)
            PSum = PSum + RecoP[i];
         if(PSum > 200)   // Mercedes Benz rejection
            continue;

         GenSumE = 0;
         GenSumE008 = 0;
         GenSumE010 = 0;
         GenSumE012 = 0;
         GenSumE015 = 0;
         GenSumE020 = 0;
         for(int i = 0; i < NGen; i++)
         {
            if(GenStatus[i] != 1)   // we want only final state particles
               continue;
            FourVector P(0, GenPX[i], GenPY[i], GenPZ[i]);
            P[0] = sqrt(P.GetP() * P.GetP() + GenMass[i] * GenMass[i]);

            if(P.GetTheta() > 0.08 * M_PI && P.GetTheta() < 0.92 * M_PI)
               GenSumE008 = GenSumE008 + P[0];
            if(P.GetTheta() > 0.10 * M_PI && P.GetTheta() < 0.90 * M_PI)
               GenSumE010 = GenSumE010 + P[0];
            if(P.GetTheta() > 0.12 * M_PI && P.GetTheta() < 0.88 * M_PI)
               GenSumE012 = GenSumE012 + P[0];
            if(P.GetTheta() > 0.15 * M_PI && P.GetTheta() < 0.85 * M_PI)
               GenSumE015 = GenSumE015 + P[0];
            if(P.GetTheta() > 0.20 * M_PI && P.GetTheta() < 0.80 * M_PI)
               GenSumE020 = GenSumE020 + P[0];
            
            if(P.GetTheta() < ThetaMin || P.GetTheta() > ThetaMax)
               continue;
            GenSumE = GenSumE + P[0];
         }

         RecoSumE = 0;
         RecoSumE008 = 0;
         RecoSumE010 = 0;
         RecoSumE012 = 0;
         RecoSumE015 = 0;
         RecoSumE020 = 0;
         for(int i = 0; i < NReco; i++)
         {
            FourVector P(0, RecoPX[i], RecoPY[i], RecoPZ[i]);
            P[0] = sqrt(P.GetP() * P.GetP() + RecoMass[i] * RecoMass[i]);
            
            if(P.GetTheta() > 0.08 * M_PI && P.GetTheta() < 0.92 * M_PI)
               RecoSumE008 = RecoSumE008 + P[0];
            if(P.GetTheta() > 0.10 * M_PI && P.GetTheta() < 0.90 * M_PI)
               RecoSumE010 = RecoSumE010 + P[0];
            if(P.GetTheta() > 0.12 * M_PI && P.GetTheta() < 0.88 * M_PI)
               RecoSumE012 = RecoSumE012 + P[0];
            if(P.GetTheta() > 0.15 * M_PI && P.GetTheta() < 0.85 * M_PI)
               RecoSumE015 = RecoSumE015 + P[0];
            if(P.GetTheta() > 0.20 * M_PI && P.GetTheta() < 0.80 * M_PI)
               RecoSumE020 = RecoSumE020 + P[0];
            
            if(P.GetTheta() < ThetaMin || P.GetTheta() > ThetaMax)
               continue;
            RecoSumE = RecoSumE + P[0];
         }

         PassedEventCount = PassedEventCount + 1;

         vector<FourVector> GenParticles;
         vector<PseudoJet> GenFJParticles;
         for(int i = 0; i < NGen; i++)
         {
            if(GenStatus[i] != 1)
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
            RecoFJParticles.emplace_back(P[1], P[2], P[3], P[0]);
         }

         vector<FourVector> GenJets;
         vector<FourVector> RecoJets;

         if(UseStored == true)
         {
            GenJets.resize(NStoredGenJet);
            for(int i = 0; i < NStoredGenJet; i++)
               GenJets[i].SetPtEtaPhiMass(StoredGenJetPT[i], StoredGenJetEta[i], StoredGenJetPhi[i], StoredGenJetM[i]);

            RecoJets.resize(NStoredRecoJet);
            for(int i = 0; i < NStoredRecoJet; i++)
               RecoJets[i].SetPtEtaPhiMass(StoredRecoJetPT[i], StoredRecoJetEta[i], StoredRecoJetPhi[i], StoredRecoJetM[i]);
         }
         else
         {
            JetDefinition Definition(ee_genkt_algorithm, JetR, -1);
            ClusterSequence GenSequence(GenFJParticles, Definition);
            vector<PseudoJet> GenFastJets = GenSequence.inclusive_jets(0.5);
            ClusterSequence RecoSequence(RecoFJParticles, Definition);
            vector<PseudoJet> RecoFastJets = RecoSequence.inclusive_jets(0.5);

            for(int i = 0 ; i < (int)GenFastJets.size(); i++)
            {
               FourVector P(GenFastJets[i].e(), GenFastJets[i].px(), GenFastJets[i].py(), GenFastJets[i].pz());
               // if(P.GetTheta() < ThetaMin || P.GetTheta() > ThetaMax)
               //    continue;
               GenJets.emplace_back(P);
            }

            for(int i = 0 ; i < (int)RecoFastJets.size(); i++)
            {
               FourVector P(RecoFastJets[i].e(), RecoFastJets[i].px(), RecoFastJets[i].py(), RecoFastJets[i].pz());
               // if(P.GetTheta() < ThetaMin || P.GetTheta() > ThetaMax)
               //    continue;
               RecoJets.emplace_back(P);
            }
         }
            
         sort(GenJets.begin(), GenJets.end(), DecreasingEnergy);
         sort(RecoJets.begin(), RecoJets.end(), DecreasingEnergy);

         double HybridJetMin = 5;
         GenHybridE008 = 0;
         GenHybridE010 = 0;
         GenHybridE012 = 0;
         GenHybridE015 = 0;
         GenHybridE020 = 0;
         for(FourVector &P : GenParticles)
         {
            bool Include008 = false;
            bool Include010 = false;
            bool Include012 = false;
            bool Include015 = false;
            bool Include020 = false;

            if(P.GetTheta() > 0.08 * M_PI && P.GetTheta() < 0.92 * M_PI)   Include008 = true;
            if(P.GetTheta() > 0.10 * M_PI && P.GetTheta() < 0.90 * M_PI)   Include010 = true;
            if(P.GetTheta() > 0.12 * M_PI && P.GetTheta() < 0.88 * M_PI)   Include012 = true;
            if(P.GetTheta() > 0.15 * M_PI && P.GetTheta() < 0.85 * M_PI)   Include015 = true;
            if(P.GetTheta() > 0.20 * M_PI && P.GetTheta() < 0.80 * M_PI)   Include020 = true;

            for(FourVector &J : GenJets)
            {
               if(J[0] < HybridJetMin)
                  continue;

               if(Include008 == false && J.GetTheta() > 0.08 * M_PI && J.GetTheta() < 0.92 * M_PI && GetAngle(P, J) < JetR)
                  Include008 = true;
               if(Include010 == false && J.GetTheta() > 0.10 * M_PI && J.GetTheta() < 0.90 * M_PI && GetAngle(P, J) < JetR)
                  Include010 = true;
               if(Include012 == false && J.GetTheta() > 0.12 * M_PI && J.GetTheta() < 0.88 * M_PI && GetAngle(P, J) < JetR)
                  Include012 = true;
               if(Include015 == false && J.GetTheta() > 0.15 * M_PI && J.GetTheta() < 0.85 * M_PI && GetAngle(P, J) < JetR)
                  Include015 = true;
               if(Include020 == false && J.GetTheta() > 0.20 * M_PI && J.GetTheta() < 0.80 * M_PI && GetAngle(P, J) < JetR)
                  Include020 = true;
            }

            if(Include008 == true)   GenHybridE008 = GenHybridE008 + P[0];
            if(Include010 == true)   GenHybridE010 = GenHybridE010 + P[0];
            if(Include012 == true)   GenHybridE012 = GenHybridE012 + P[0];
            if(Include015 == true)   GenHybridE015 = GenHybridE015 + P[0];
            if(Include020 == true)   GenHybridE020 = GenHybridE020 + P[0];
         }

         GenJetZG.resize(GenJets.size());
         GenJetRG.resize(GenJets.size());
         GenJetPG.resize(GenJets.size());
         GenJetMG.resize(GenJets.size());
         GenJetNG.resize(GenJets.size());
         for(int i = 0; i < (int)GenJets.size(); i++)
         {
            vector<Node *> Nodes;
            for(FourVector V : GenParticles)
               if(GetAngle(GenJets[i], V) < JetR)
                  Nodes.push_back(new Node(V));
            BuildCATree(Nodes);
         
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
                     GenJetZG[i][iSD] = P2.GetP() / (P1.GetP() + P2.GetP());
                     GenJetRG[i][iSD] = GetAngle(P1, P2);
                     GenJetPG[i][iSD] = SDNode->P.GetP();
                     GenJetMG[i][iSD] = SDNode->P.GetMass();
                     GenJetNG[i][iSD] = CountFinalNode(SDNode);
                  }
                  else
                  {
                     GenJetZG[i][iSD] = -1;
                     GenJetRG[i][iSD] = -1;
                     GenJetPG[i][iSD] = -1;
                     GenJetMG[i][iSD] = -1;
                     GenJetNG[i][iSD] = -1;
                  }
               }
            }
         }

         RecoJetZG.resize(RecoJets.size());
         RecoJetRG.resize(RecoJets.size());
         RecoJetPG.resize(RecoJets.size());
         RecoJetMG.resize(RecoJets.size());
         RecoJetNG.resize(RecoJets.size());
         for(int i = 0; i < (int)RecoJets.size(); i++)
         {
            vector<Node *> Nodes;
            for(FourVector V : RecoParticles)
               if(GetAngle(RecoJets[i], V) < JetR)
                  Nodes.push_back(new Node(V));
            BuildCATree(Nodes);
            
            RecoJetZG[i].resize(NSD);
            RecoJetRG[i].resize(NSD);
            RecoJetPG[i].resize(NSD);
            RecoJetMG[i].resize(NSD);
            RecoJetNG[i].resize(NSD);

            if(Nodes.size() > 0)
            {
               for(int iSD = 0; iSD < NSD; iSD++)
               {
                  Node *SDNode = FindSDNodeE(Nodes[0], SDZCut[iSD], SDBeta[iSD]);
                  if(SDNode != nullptr && SDNode->Child1 != nullptr && SDNode->Child2 != nullptr)
                  {
                     FourVector &P1 = SDNode->Child1->P;
                     FourVector &P2 = SDNode->Child2->P;
                     RecoJetZG[i][iSD] = P2.GetP() / (P1.GetP() + P2.GetP());
                     RecoJetRG[i][iSD] = GetAngle(P1, P2);
                     RecoJetPG[i][iSD] = SDNode->P.GetP();
                     RecoJetMG[i][iSD] = SDNode->P.GetMass();
                     RecoJetNG[i][iSD] = CountFinalNode(SDNode);
                  }
                  else
                  {
                     RecoJetZG[i][iSD] = -1;
                     RecoJetRG[i][iSD] = -1;
                     RecoJetPG[i][iSD] = -1;
                     RecoJetMG[i][iSD] = -1;
                     RecoJetNG[i][iSD] = -1;
                  }
               }
            }
         }

         // Gen & reco jets
         NRecoJets = RecoJets.size();
         RecoJetPX.resize(NRecoJets);
         RecoJetPY.resize(NRecoJets);
         RecoJetPZ.resize(NRecoJets);
         RecoJetE.resize(NRecoJets);
         RecoJetP.resize(NRecoJets);
         RecoJetTheta.resize(NRecoJets);
         RecoJetPhi.resize(NRecoJets);
         RecoJetJEC.resize(NRecoJets);
         RecoJetJEU.resize(NRecoJets);
         for(int iR = 0; iR < NRecoJets; iR++)
         {
            JEC.SetJetP(RecoJets[iR].GetP());
            JEC.SetJetTheta(RecoJets[iR].GetTheta());
            JEC.SetJetPhi(RecoJets[iR].GetPhi());
            double Correction = JEC.GetCorrection();
            if(Correction < 0)
               Correction = 1;

            RecoJets[iR] = RecoJets[iR] * Correction;

            double Uncertainty = 0.005;
            
            RecoJetPX[iR]    = RecoJets[iR][1];
            RecoJetPY[iR]    = RecoJets[iR][2];
            RecoJetPZ[iR]    = RecoJets[iR][3];
            RecoJetE[iR]     = RecoJets[iR][0];
            RecoJetP[iR]     = RecoJets[iR].GetP();
            RecoJetTheta[iR] = RecoJets[iR].GetTheta();
            RecoJetPhi[iR]   = RecoJets[iR].GetPhi();
            RecoJetJEC[iR]   = Correction;
            RecoJetJEU[iR]   = Uncertainty;
         }
         
         NGenJets = GenJets.size();
         GenJetPX.resize(NGenJets);
         GenJetPY.resize(NGenJets);
         GenJetPZ.resize(NGenJets);
         GenJetE.resize(NGenJets);
         GenJetP.resize(NGenJets);
         GenJetTheta.resize(NGenJets);
         GenJetPhi.resize(NGenJets);
         for(int iR = 0; iR < NGenJets; iR++)
         {
            GenJetPX[iR]    = GenJets[iR][1];
            GenJetPY[iR]    = GenJets[iR][2];
            GenJetPZ[iR]    = GenJets[iR][3];
            GenJetE[iR]     = GenJets[iR][0];
            GenJetP[iR]     = GenJets[iR].GetP();
            GenJetTheta[iR] = GenJets[iR].GetTheta();
            GenJetPhi[iR]   = GenJets[iR].GetPhi();
         }

         // Match reco to gen jets
         MatchedJetPX.resize(NGenJets);
         MatchedJetPY.resize(NGenJets);
         MatchedJetPZ.resize(NGenJets);
         MatchedJetE.resize(NGenJets);
         MatchedJetP.resize(NGenJets);
         MatchedJetTheta.resize(NGenJets);
         MatchedJetPhi.resize(NGenJets);
         MatchedJetAngle.resize(NGenJets);
         MatchedJetJEC.resize(NGenJets);
         MatchedJetJEU.resize(NGenJets);
         MatchedJetZG.resize(NGenJets);
         MatchedJetRG.resize(NGenJets);
         MatchedJetPG.resize(NGenJets);
         MatchedJetMG.resize(NGenJets);
         MatchedJetNG.resize(NGenJets);
         for(int iG = 0; iG < (int)GenJets.size(); iG++)
         {
            MatchedJetAngle[iG] = -1;

            int BestIndex = -1;
            double BestAngle = -1;
            for(int iR = 0; iR < (int)RecoJets.size(); iR++)
            {
               double Angle = GetAngle(GenJets[iG], RecoJets[iR]);
               if(BestAngle < 0 || Angle < BestAngle)
               {
                  BestIndex = iR;
                  BestAngle = Angle;
               }
            }

            MatchedJetZG[iG].resize(NSD, -1);
            MatchedJetRG[iG].resize(NSD, -1);
            MatchedJetPG[iG].resize(NSD, -1);
            MatchedJetMG[iG].resize(NSD, -1);
            MatchedJetNG[iG].resize(NSD, -1);

            if(BestIndex < 0)   // WTF
               continue;

            // Fill output tree with matched jets
            MatchedJetPX[iG]    = RecoJets[BestIndex][1];
            MatchedJetPY[iG]    = RecoJets[BestIndex][2];
            MatchedJetPZ[iG]    = RecoJets[BestIndex][3];
            MatchedJetE[iG]     = RecoJets[BestIndex][0];
            MatchedJetP[iG]     = RecoJets[BestIndex].GetP();
            MatchedJetTheta[iG] = RecoJets[BestIndex].GetTheta();
            MatchedJetPhi[iG]   = RecoJets[BestIndex].GetPhi();
            MatchedJetAngle[iG] = BestAngle;
            MatchedJetJEC[iG]   = RecoJetJEC[BestIndex];
            MatchedJetJEU[iG]   = RecoJetJEU[BestIndex];
            for(int iSD = 0; iSD < NSD; iSD++)
            {
               MatchedJetZG[iG][iSD] = RecoJetZG[BestIndex][iSD];
               MatchedJetRG[iG][iSD] = RecoJetRG[BestIndex][iSD];
               MatchedJetPG[iG][iSD] = RecoJetPG[BestIndex][iSD];
               MatchedJetMG[iG][iSD] = RecoJetMG[BestIndex][iSD];
               MatchedJetNG[iG][iSD] = RecoJetNG[BestIndex][iSD];
            }
         }

         OutputTree.Fill();
      }

      InputFile.Close();
   }

   OutputFile.cd();
   OutputTree.Write();

   TNamed Count;
   Count.SetNameTitle("EventCount", Form("%d", PassedEventCount));
   Count.Write();

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

bool DecreasingEnergy(FourVector &V1, FourVector &V2)
{
   return V1[0] > V2[0];
}











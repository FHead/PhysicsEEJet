#include <map>
#include <vector>
#include <iostream>
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

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);

   vector<string> InputFileName  = CL.GetStringVector("Input");
   string OutputFileName         = CL.Get("Output");
   bool IsMC                     = CL.GetBool("MC", false);
   double ThetaGap               = CL.GetDouble("ThetaGap", 0.2 * M_PI);
   double MinAngle               = CL.GetDouble("MinAngle", 0.2);
   vector<string> JEC            = CL.GetStringVector("JEC", vector<string>{});
   double Fraction               = CL.GetDouble("Fraction", 1.00);
   double JetR                   = CL.GetDouble("JetR", 0.4);

   TFile OutputFile(OutputFileName.c_str(), "RECREATE");

   map<string, TH1D *> HGen;
   map<string, TH1D *> HReco;
   map<string, TH2D *> HRecoGen;

   const int GenJetPBin = 46;
   double GenJetPBins[GenJetPBin+1] =
      {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11,
      12, 13, 14, 15, 16, 17, 18, 19, 20, 21,
      22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
      32, 33, 34, 35, 36, 37, 38, 39, 40, 41,
      42, 43, 44, 45, 50};
   const int RecoJetPBin = 53;
   double RecoJetPBins[RecoJetPBin+1] =
      {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11,
      12, 13, 14, 15, 16, 17, 18, 19, 20, 21,
      22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
      32, 33, 34, 35, 36, 37, 38, 39, 40, 41,
      42, 43, 44, 45, 50, 55, 60, 65, 70, 80, 90, 100};

   HGen["JetP"] = new TH1D("HGenJetP", ";;", 100, 0, 100);
   HGen["JetPBinnedHuman"] = new TH1D("HGenJetPBinnedHuman", ";;", GenJetPBin, GenJetPBins);
   HGen["JetPBinned"] = new TH1D("HGenJetPBinned", ";;", GenJetPBin, 0, GenJetPBin);
   HGen["JetTheta"] = new TH1D("HGenJetTheta", ";;", 100, 0, M_PI);
   HGen["JetPhi"] = new TH1D("HGenJetPhi", ";;", 100, -M_PI, M_PI);
   HGen["JetRG"] = new TH1D("HGenJetRG", ";;", 55, 0, 55);
   HGen["JetZG"] = new TH1D("HGenJetZG", ";;", 50, 0, 50);
   HGen["JetRG_P1020"] = new TH1D("HGenJetRG_P1020", ";;", 100, 0, 0.6);
   HGen["JetZG_P1020"] = new TH1D("HGenJetZG_P1020", ";;", 100, 0, 0.5);
   HGen["JetRG_P2030"] = new TH1D("HGenJetRG_P2030", ";;", 100, 0, 0.6);
   HGen["JetZG_P2030"] = new TH1D("HGenJetZG_P2030", ";;", 100, 0, 0.5);
   HGen["JetRG_P3040"] = new TH1D("HGenJetRG_P3040", ";;", 100, 0, 0.6);
   HGen["JetZG_P3040"] = new TH1D("HGenJetZG_P3040", ";;", 100, 0, 0.5);
   HGen["JetRG_P4050"] = new TH1D("HGenJetRG_P4050", ";;", 100, 0, 0.6);
   HGen["JetZG_P4050"] = new TH1D("HGenJetZG_P4050", ";;", 100, 0, 0.5);
   HReco["JetP"] = new TH1D("HRecoJetP", ";;", 100, 0, 100);
   HReco["JetPBinnedHuman"] = new TH1D("HRecoJetPBinnedHuman", ";;", RecoJetPBin, RecoJetPBins);
   HReco["JetPBinned"] = new TH1D("HRecoJetPBinned", ";;", RecoJetPBin, 0, RecoJetPBin);
   HReco["JetPBinnedSmearedHuman"] = new TH1D("HRecoJetPBinnedSmearedHuman", ";;", RecoJetPBin, RecoJetPBins);
   HReco["JetPBinnedSmeared"] = new TH1D("HRecoJetPBinnedSmeared", ";;", RecoJetPBin, 0, RecoJetPBin);
   HReco["JetTheta"] = new TH1D("HRecoJetTheta", ";;", 100, 0, M_PI);
   HReco["JetPhi"] = new TH1D("HRecoJetPhi", ";;", 100, -M_PI, M_PI);
   HReco["JetRG"] = new TH1D("HRecoJetRG", ";;", 66, 0, 66);
   HReco["JetRGSmeared"] = new TH1D("HRecoJetRGSmeared", ";;", 66, 0, 66);
   HReco["JetZG"] = new TH1D("HRecoJetZG", ";;", 60, 0, 60);
   HReco["JetZGSmeared"] = new TH1D("HRecoJetZGSmeared", ";;", 60, 0, 60);
   HReco["JetRG_P1020"] = new TH1D("HRecoJetRG_P1020", ";;", 100, 0, 0.6);
   HReco["JetZG_P1020"] = new TH1D("HRecoJetZG_P1020", ";;", 100, 0, 0.5);
   HReco["JetRG_P2030"] = new TH1D("HRecoJetRG_P2030", ";;", 100, 0, 0.6);
   HReco["JetZG_P2030"] = new TH1D("HRecoJetZG_P2030", ";;", 100, 0, 0.5);
   HReco["JetRG_P3040"] = new TH1D("HRecoJetRG_P3040", ";;", 100, 0, 0.6);
   HReco["JetZG_P3040"] = new TH1D("HRecoJetZG_P3040", ";;", 100, 0, 0.5);
   HReco["JetRG_P4050"] = new TH1D("HRecoJetRG_P4050", ";;", 100, 0, 0.6);
   HReco["JetZG_P4050"] = new TH1D("HRecoJetZG_P4050", ";;", 100, 0, 0.5);
   HRecoGen["JetP"] = new TH2D("H2DJetP", ";Reco P;Gen P", 100, 0, 75, 100, 0, 100);
   HRecoGen["JetPBinnedHuman"] = new TH2D("H2DJetPBinnedHuman", ";Reco P;Gen P",
      RecoJetPBin, RecoJetPBins, GenJetPBin, GenJetPBins);
   HRecoGen["JetPBinned"] = new TH2D("H2DJetPBinned", ";Reco P;Gen P",
      RecoJetPBin, 0, RecoJetPBin, GenJetPBin, 0, GenJetPBin);
   HRecoGen["JetRG_P1020"] = new TH2D("H2DJetRG_P1020", ";Reco;Gen", 100, 0, 0.6, 100, 0, 0.6);
   HRecoGen["JetZG_P1020"] = new TH2D("H2DJetZG_P1020", ";Reco;Gen", 100, 0, 0.5, 100, 0, 0.5);
   HRecoGen["JetRG_P2030"] = new TH2D("H2DJetRG_P2030", ";Reco;Gen", 100, 0, 0.6, 100, 0, 0.6);
   HRecoGen["JetZG_P2030"] = new TH2D("H2DJetZG_P2030", ";Reco;Gen", 100, 0, 0.5, 100, 0, 0.5);
   HRecoGen["JetRG_P3040"] = new TH2D("H2DJetRG_P3040", ";Reco;Gen", 100, 0, 0.6, 100, 0, 0.6);
   HRecoGen["JetZG_P3040"] = new TH2D("H2DJetZG_P3040", ";Reco;Gen", 100, 0, 0.5, 100, 0, 0.5);
   HRecoGen["JetRG_P4050"] = new TH2D("H2DJetRG_P4050", ";Reco;Gen", 100, 0, 0.6, 100, 0, 0.6);
   HRecoGen["JetZG_P4050"] = new TH2D("H2DJetZG_P4050", ";Reco;Gen", 100, 0, 0.5, 100, 0, 0.5);
   HRecoGen["JetRG"] = new TH2D("H2DJetRG", ";Reco Index;Gen Index", 66, 0, 66, 55, 0, 55);
   HRecoGen["JetZG"] = new TH2D("H2DJetZG", ";Reco Index;Gen Index", 60, 0, 60, 50, 0, 50);

   HRecoGen["JetRG"]->Fill(0.0, 0.0, 0.0);
   HRecoGen["JetZG"]->Fill(0.0, 0.0, 0.0);

   for(string FileName : InputFileName)
   {
      TFile InputFile(FileName.c_str());

      TTree *RecoTree = (TTree *)InputFile.Get("t");
      TTree *GenTree = (TTree *)InputFile.Get("tgen");

      if(RecoTree == nullptr)
         continue;
      if(IsMC == true && GenTree == nullptr)
         continue;

      int NReco;
      float RecoPX[MAX];
      float RecoPY[MAX];
      float RecoPZ[MAX];
      float RecoMass[MAX];
      bool RecoHighPurity[MAX];
      int NGen;
      float GenPX[MAX];
      float GenPY[MAX];
      float GenPZ[MAX];
      float GenMass[MAX];

      if(IsMC == true)
      {
         GenTree->SetBranchAddress("nParticle", &NGen);
         GenTree->SetBranchAddress("px", &GenPX);
         GenTree->SetBranchAddress("py", &GenPY);
         GenTree->SetBranchAddress("pz", &GenPZ);
         GenTree->SetBranchAddress("mass", &GenMass);
      }
      RecoTree->SetBranchAddress("nParticle", &NReco);
      RecoTree->SetBranchAddress("px", &RecoPX);
      RecoTree->SetBranchAddress("py", &RecoPY);
      RecoTree->SetBranchAddress("pz", &RecoPZ);
      RecoTree->SetBranchAddress("mass", &RecoMass);
      RecoTree->SetBranchAddress("highPurity", &RecoHighPurity);

      int EntryCount = RecoTree->GetEntries() * Fraction;
      for(int iE = 0; iE < EntryCount; iE++)
      {
         NGen = 0;
         NReco = 0;

         if(IsMC == true)
            GenTree->GetEntry(iE);
         RecoTree->GetEntry(iE);

         vector<FourVector> GenParticles;
         vector<PseudoJet> GenFJParticles;
         for(int i = 0; i < NGen; i++)
         {
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

         JetDefinition Definition(ee_genkt_algorithm, JetR, -1);
         ClusterSequence GenSequence(GenFJParticles, Definition);
         vector<PseudoJet> GenFastJets = GenSequence.inclusive_jets(0.5);
         ClusterSequence RecoSequence(RecoFJParticles, Definition);
         vector<PseudoJet> RecoFastJets = RecoSequence.inclusive_jets(0.5);

         vector<FourVector> GenJets;
         for(int i = 0 ; i < (int)GenFastJets.size(); i++)
         {
            FourVector P(GenFastJets[i].e(), GenFastJets[i].px(), GenFastJets[i].py(), GenFastJets[i].pz());
            if(P.GetTheta() < ThetaGap || P.GetTheta() > M_PI - ThetaGap)
               continue;
            GenJets.emplace_back(P);
         }

         vector<FourVector> RecoJets;
         for(int i = 0 ; i < (int)RecoFastJets.size(); i++)
         {
            FourVector P(RecoFastJets[i].e(), RecoFastJets[i].px(), RecoFastJets[i].py(), RecoFastJets[i].pz());
            if(P.GetTheta() < ThetaGap || P.GetTheta() > M_PI - ThetaGap)
               continue;
            RecoJets.emplace_back(P);
         }

         vector<double> GenZG0(GenJets.size(), -1), GenRG0(GenJets.size(), -1);
         for(int i = 0; i < (int)GenJets.size(); i++)
         {
            vector<Node *> Nodes;
            for(FourVector V : GenParticles)
               if(GetAngle(GenJets[i], V) < JetR)
                  Nodes.push_back(new Node(V));
            BuildCATree(Nodes);

            if(Nodes.size() > 0)
            {
               Node *SDNode = FindSDNode(Nodes[0], 0.1, 0.0);
               if(SDNode != nullptr && SDNode->Child1 != nullptr && SDNode->Child2 != nullptr)
               {
                  GenZG0[i] = SDNode->Child2->P.GetP() / (SDNode->Child1->P.GetP() + SDNode->Child2->P.GetP());
                  GenRG0[i] = GetAngle(SDNode->Child1->P, SDNode->Child2->P);
               }
            }
         }

         vector<double> RecoZG0(RecoJets.size(), -1), RecoRG0(RecoJets.size(), -1);
         for(int i = 0; i < (int)RecoJets.size(); i++)
         {
            vector<Node *> Nodes;
            for(FourVector V : RecoParticles)
               if(GetAngle(RecoJets[i], V) < JetR)
                  Nodes.push_back(new Node(V));
            BuildCATree(Nodes);

            if(Nodes.size() > 0)
            {
               Node *SDNode = FindSDNode(Nodes[0], 0.1, 0.0);
               if(SDNode != nullptr && SDNode->Child1 != nullptr && SDNode->Child2 != nullptr)
               {
                  RecoZG0[i] = SDNode->Child2->P.GetP() / (SDNode->Child1->P.GetP() + SDNode->Child2->P.GetP());
                  RecoRG0[i] = GetAngle(SDNode->Child1->P, SDNode->Child2->P);
               }
            }
         }

         // Gen & reco distributions
         for(int i = 0; i < (int)GenJets.size(); i++)
         {
            FourVector &P = GenJets[i];
            HGen["JetP"]->Fill(P.GetP());
            HGen["JetPBinnedHuman"]->Fill(P.GetP());
            HGen["JetPBinned"]->Fill(FindBin(GenJetPBin, GenJetPBins, P.GetP()));
            HGen["JetTheta"]->Fill(P.GetTheta());
            HGen["JetPhi"]->Fill(P.GetPhi());
            
            int GenPBin = -1;
            if(GenJets[i].GetP() >= 40)        GenPBin = 4;
            else if(GenJets[i].GetP() >= 30)   GenPBin = 3;
            else if(GenJets[i].GetP() >= 20)   GenPBin = 2;
            else if(GenJets[i].GetP() >= 10)   GenPBin = 1;
            else                              GenPBin = 0;
            int GenZGBin = GenZG0[i] / 0.05;
            int GenRGBin = GenRG0[i] / 0.06 + 1;
            if(GenZGBin >= 10)    GenZGBin = 9;
            if(GenRGBin >= 11)    GenRGBin = 10;
            if(GenZGBin < 0)      GenZGBin = 0;
            if(GenRGBin < 0)      GenRGBin = 0;
            
            HGen["JetZG"]->Fill(GenPBin * 10 + GenZGBin);
            HGen["JetRG"]->Fill(GenPBin * 11 + GenRGBin);
            
            if(P.GetP() >= 10 && P.GetP() < 20)
            {
               HGen["JetZG_P1020"]->Fill(GenZG0[i]);
               HGen["JetRG_P1020"]->Fill(GenRG0[i]);
            }
            if(P.GetP() >= 20 && P.GetP() < 30)
            {
               HGen["JetZG_P2030"]->Fill(GenZG0[i]);
               HGen["JetRG_P2030"]->Fill(GenRG0[i]);
            }
            if(P.GetP() >= 30 && P.GetP() < 40)
            {
               HGen["JetZG_P3040"]->Fill(GenZG0[i]);
               HGen["JetRG_P3040"]->Fill(GenRG0[i]);
            }
            if(P.GetP() >= 40 && P.GetP() < 50)
            {
               HGen["JetZG_P4050"]->Fill(GenZG0[i]);
               HGen["JetRG_P4050"]->Fill(GenRG0[i]);
            }
         }
         for(int i = 0; i < (int)RecoJets.size(); i++)
         {
            FourVector &P = RecoJets[i];
            HReco["JetP"]->Fill(P.GetP());
            HReco["JetPBinnedHuman"]->Fill(P.GetP());
            HReco["JetPBinned"]->Fill(FindBin(RecoJetPBin, RecoJetPBins, P.GetP()));
            HReco["JetTheta"]->Fill(P.GetTheta());
            HReco["JetPhi"]->Fill(P.GetPhi());

            int RecoPBin = -1;
            if(RecoJets[i].GetP() >= 50)        RecoPBin = 5;
            else if(RecoJets[i].GetP() >= 40)   RecoPBin = 4;
            else if(RecoJets[i].GetP() >= 30)   RecoPBin = 3;
            else if(RecoJets[i].GetP() >= 20)   RecoPBin = 2;
            else if(RecoJets[i].GetP() >= 10)   RecoPBin = 1;
            else                               RecoPBin = 0;
            int RecoZGBin = RecoZG0[i] / 0.05;
            int RecoRGBin = RecoRG0[i] / 0.06 + 1;
            if(RecoZGBin >= 10)    RecoZGBin = 9;
            if(RecoRGBin >= 11)    RecoRGBin = 10;
            if(RecoZGBin < 0)      RecoZGBin = 0;
            if(RecoRGBin < 0)      RecoRGBin = 0;

            HReco["JetZG"]->Fill(RecoPBin * 10 + RecoZGBin);
            HReco["JetRG"]->Fill(RecoPBin * 11 + RecoRGBin);
            
            double Check = DrawRandom(0, 1);
            if(Check > 0.25)
            {
               HReco["JetPBinnedSmearedHuman"]->Fill(P.GetP());
               HReco["JetPBinnedSmeared"]->Fill(FindBin(RecoJetPBin, RecoJetPBins, P.GetP()));
               HReco["JetZGSmeared"]->Fill(RecoPBin * 10 + RecoZGBin);
               HReco["JetRGSmeared"]->Fill(RecoPBin * 11 + RecoRGBin);
            }
            if(Check > 0.75)
            {
               HReco["JetPBinnedSmearedHuman"]->Fill(P.GetP());
               HReco["JetPBinnedSmeared"]->Fill(FindBin(RecoJetPBin, RecoJetPBins, P.GetP()));
               HReco["JetZGSmeared"]->Fill(RecoPBin * 10 + RecoZGBin);
               HReco["JetRGSmeared"]->Fill(RecoPBin * 11 + RecoRGBin);
            }
            
            if(P.GetP() >= 10 && P.GetP() < 20)
            {
               HReco["JetZG_P1020"]->Fill(RecoZG0[i]);
               HReco["JetRG_P1020"]->Fill(RecoRG0[i]);
            }
            if(P.GetP() >= 20 && P.GetP() < 30)
            {
               HReco["JetZG_P2030"]->Fill(RecoZG0[i]);
               HReco["JetRG_P2030"]->Fill(RecoRG0[i]);
            }
            if(P.GetP() >= 30 && P.GetP() < 40)
            {
               HReco["JetZG_P3040"]->Fill(RecoZG0[i]);
               HReco["JetRG_P3040"]->Fill(RecoRG0[i]);
            }
            if(P.GetP() >= 40 && P.GetP() < 50)
            {
               HReco["JetZG_P4050"]->Fill(RecoZG0[i]);
               HReco["JetRG_P4050"]->Fill(RecoRG0[i]);
            }
         }

         // Match reco to gen jets
         for(int iG = 0; iG < (int)GenJets.size(); iG++)
         {
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

            if(BestIndex < 0)   // WTF
               continue;

            if(BestAngle > MinAngle)
               continue;
               
            HRecoGen["JetP"]->Fill(RecoJets[BestIndex].GetP(), GenJets[iG].GetP());
            HRecoGen["JetPBinnedHuman"]->Fill(RecoJets[BestIndex].GetP(), GenJets[iG].GetP());
            HRecoGen["JetPBinned"]->AddBinContent(HRecoGen["JetPBinned"]->FindBin(
               FindBin(RecoJetPBin, RecoJetPBins, RecoJets[BestIndex].GetP()),
               FindBin(GenJetPBin, GenJetPBins, GenJets[iG].GetP())), 1);

            if(GenJets[iG].GetP() >= 10 && GenJets[iG].GetP() < 20)
            {
               HRecoGen["JetZG_P1020"]->Fill(RecoZG0[BestIndex], GenZG0[iG]);
               HRecoGen["JetRG_P1020"]->Fill(RecoRG0[BestIndex], GenRG0[iG]);
            }
            if(GenJets[iG].GetP() >= 20 && GenJets[iG].GetP() < 30)
            {
               HRecoGen["JetZG_P2030"]->Fill(RecoZG0[BestIndex], GenZG0[iG]);
               HRecoGen["JetRG_P2030"]->Fill(RecoRG0[BestIndex], GenRG0[iG]);
            }
            if(GenJets[iG].GetP() >= 30 && GenJets[iG].GetP() < 40)
            {
               HRecoGen["JetZG_P3040"]->Fill(RecoZG0[BestIndex], GenZG0[iG]);
               HRecoGen["JetRG_P3040"]->Fill(RecoRG0[BestIndex], GenRG0[iG]);
            }
            if(GenJets[iG].GetP() >= 40 && GenJets[iG].GetP() < 50)
            {
               HRecoGen["JetZG_P4050"]->Fill(RecoZG0[BestIndex], GenZG0[iG]);
               HRecoGen["JetRG_P4050"]->Fill(RecoRG0[BestIndex], GenRG0[iG]);
            }

            int GenPBin = -1;
            if(GenJets[iG].GetP() >= 40)        GenPBin = 4;
            else if(GenJets[iG].GetP() >= 30)   GenPBin = 3;
            else if(GenJets[iG].GetP() >= 20)   GenPBin = 2;
            else if(GenJets[iG].GetP() >= 10)   GenPBin = 1;
            else                               GenPBin = 0;
           
            int RecoPBin = -1;
            if(RecoJets[BestIndex].GetP() >= 50)        RecoPBin = 5;
            else if(RecoJets[BestIndex].GetP() >= 40)   RecoPBin = 4;
            else if(RecoJets[BestIndex].GetP() >= 30)   RecoPBin = 3;
            else if(RecoJets[BestIndex].GetP() >= 20)   RecoPBin = 2;
            else if(RecoJets[BestIndex].GetP() >= 10)   RecoPBin = 1;
            else                                       RecoPBin = 0;

            if(GenPBin >= 0 && RecoPBin >= 0)
            {
               int GenZGBin = GenZG0[iG] / 0.05;
               int GenRGBin = GenRG0[iG] / 0.06 + 1;
               int RecoZGBin = RecoZG0[BestIndex] / 0.05;
               int RecoRGBin = RecoRG0[BestIndex] / 0.06 + 1;

               if(GenZGBin >= 10)    GenZGBin = 9;
               if(RecoZGBin >= 10)   RecoZGBin = 9;
               if(GenRGBin >= 11)    GenRGBin = 10;
               if(RecoRGBin >= 11)   RecoRGBin = 10;
               if(GenZGBin < 0)      GenZGBin = 0;
               if(RecoZGBin < 0)     RecoZGBin = 0;
               if(GenRGBin < 0)      GenRGBin = 0;
               if(RecoRGBin < 0)     RecoRGBin = 0;

               int ZGBin = HRecoGen["JetZG"]->FindBin(RecoPBin * 10 + RecoZGBin, GenPBin * 10 + GenZGBin);
               HRecoGen["JetZG"]->AddBinContent(ZGBin, 1);
               
               int RGBin = HRecoGen["JetRG"]->FindBin(RecoPBin * 11 + RecoRGBin, GenPBin * 11 + GenRGBin);
               HRecoGen["JetRG"]->AddBinContent(RGBin, 1);
            }
         }
      }

      InputFile.Close();
   }

   OutputFile.cd();
   for(auto item : HGen)       item.second->Write();
   for(auto item : HReco)      item.second->Write();
   for(auto item : HRecoGen)   item.second->Write();

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












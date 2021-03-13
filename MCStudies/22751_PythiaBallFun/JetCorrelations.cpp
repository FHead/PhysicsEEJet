#include <iostream>
using namespace std;

#include "fastjet/ClusterSequence.hh"
using namespace fastjet;

#include "TFile.h"
#include "TTree.h"

#include "Code/TauHelperFunctions3.h"
#include "CustomAssert.h"
#include "CommandLine.h"

#include "CATree.h"

#define MAX 1000
#define NMAX 200
#define SDMAX 5

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);

   string InputFileName = CL.Get("Input");
   string OutputFileName = CL.Get("Output");
   double Fraction = CL.GetDouble("Fraction", 1.00);
   double R = CL.GetDouble("R", 0.4);
   bool RequirePythia = CL.GetBool("RequirePythia", false);

   TFile InputFile(InputFileName.c_str());
   TFile OutputFile(OutputFileName.c_str(), "RECREATE");

   TTree *InputTree = (TTree *)InputFile.Get("tgen");
   Assert(InputTree != nullptr, "Error getting input tree");
   
   double EPythia;
   int nParticle;
   float e[MAX], px[MAX], py[MAX], pz[MAX];
   int pid[MAX];
   int status[MAX];
   int subevent[MAX];

   InputTree->SetBranchAddress("EPythia", &EPythia);
   InputTree->SetBranchAddress("nParticle", &nParticle);
   InputTree->SetBranchAddress("e", &e);
   InputTree->SetBranchAddress("px", &px);
   InputTree->SetBranchAddress("py", &py);
   InputTree->SetBranchAddress("pz", &pz);
   InputTree->SetBranchAddress("pid", &pid);
   InputTree->SetBranchAddress("status", &status);
   InputTree->SetBranchAddress("subevent", &subevent);

   TTree JetTree("JetTree", "JetTree");

   int EventType;
   int NJet;
   double JetPx[100], JetPy[100], JetPz[100], JetE[100];
   double JetP[100], JetTheta[100], JetPhi[100];
   double JetElectronFraction[100];
   double JetMuonFraction[100];
   int JetN[100];
   double JetXi[100][200];
   int JetSubEvent[100][200];
   double JetSDZG[100][5];
   double JetSDRG[100][5];
   double JetSDP[100][5];
   int JetSDDepth[100][5];

   JetTree.Branch("EventType",           &EventType,           "EventType/I");
   JetTree.Branch("NJet",                &NJet,                "NJet/I");
   JetTree.Branch("JetPx",               &JetPx,               "JetPx[100]/D");
   JetTree.Branch("JetPy",               &JetPy,               "JetPy[100]/D");
   JetTree.Branch("JetPz",               &JetPz,               "JetPz[100]/D");
   JetTree.Branch("JetE",                &JetE,                "JetE[100]/D");
   JetTree.Branch("JetP",                &JetP,                "JetP[100]/D");
   JetTree.Branch("JetTheta",            &JetTheta,            "JetTheta[100]/D");
   JetTree.Branch("JetPhi",              &JetPhi,              "JetPhi[100]/D");
   JetTree.Branch("JetElectronFraction", &JetElectronFraction, "JetElectronFraction[100]/D");
   JetTree.Branch("JetMuonFraction",     &JetMuonFraction,     "JetMuonFraction[100]/D");
   JetTree.Branch("JetN",                &JetN,                "JetN[100]/I");
   JetTree.Branch("JetXi",               &JetXi,               "JetXi[100][200]/D");
   JetTree.Branch("JetSubEvent",         &JetSubEvent,         "JetSubEvent[100][200]/I");
   JetTree.Branch("JetSDZG",             &JetSDZG,             "JetSDZG[100][5]/D");
   JetTree.Branch("JetSDRG",             &JetSDRG,             "JetSDRG[100][5]/D");
   JetTree.Branch("JetSDP",              &JetSDP,              "JetSDP[100][5]/D");
   JetTree.Branch("JetSDDepth",          &JetSDDepth,          "JetSDDepth[100][5]/D");

   int SDCount = 5;
   double Zs[] = {0.1, 0.5, 0.2, 5.0, 0.4};
   double Betas[] = {0.0, 1.5, 0.0, 5.0, 0.0};

   int EntryCount = InputTree->GetEntries() * Fraction;
   for(int iE = 0; iE < EntryCount; iE++)
   {
      InputTree->GetEntry(iE);

      vector<int> Strong;
      vector<int> Final;
      vector<FourVector> VisibleParticles;
      vector<int> VisibleParticleSubEvent;
      vector<FourVector> Electrons;
      vector<FourVector> Muons;
      vector<PseudoJet> FastJetParticles;
      for(int i = 0; i < nParticle; i++)
      {
         FourVector P(e[i], px[i], py[i], pz[i]);
         
         if(RequirePythia == true && subevent[i] == 1)
            continue;

         if(P.GetP() > EPythia * 0.5 * 0.90)
            if(P.GetTheta() > 0.01 * M_PI && P.GetTheta() < 0.99 * M_PI)
               Strong.push_back(abs(pid[i]));
         if(status[i] == 1 && subevent[i] == 0)
            Final.push_back(abs(pid[i]));

         if(status[i] != 1)                  continue;
         if(pid[i] == 12 || pid[i] == -12)   continue;
         if(pid[i] == 14 || pid[i] == -14)   continue;
         if(pid[i] == 16 || pid[i] == -16)   continue;

         VisibleParticles.push_back(P);
         VisibleParticleSubEvent.push_back(subevent[i]);
         if(pid[i] == 11 || pid[i] == -11)
            Electrons.push_back(P);
         if(pid[i] == 13 || pid[i] == -13)
            Muons.push_back(P);
         FastJetParticles.push_back(PseudoJet(px[i], py[i], pz[i], e[i]));
      }
      JetDefinition Definition(ee_genkt_algorithm, R, -1);
      ClusterSequence Sequence(FastJetParticles, Definition);
      vector<PseudoJet> FastJets = Sequence.inclusive_jets(0.5);

      sort(Strong.begin(), Strong.end());
      Strong.erase(unique(Strong.begin(), Strong.end()), Strong.end());
      sort(Final.begin(), Final.end());
      Final.erase(unique(Final.begin(), Final.end()), Final.end());

      EventType = -1;
      if(Final.size() == 2 && Final[0] == 11 && Final[1] == 22)
         EventType = 11;
      else
      {
         if(Strong.size() == 1)
            EventType = Strong[0];
         else if(Strong.size() > 1)
            EventType = Strong[0];
      }

      vector<FourVector> Jets;
      for(int i = 0; i < (int)FastJets.size(); i++)
         Jets.push_back(FourVector(FastJets[i].e(), FastJets[i].px(), FastJets[i].py(), FastJets[i].pz()));

      NJet = Jets.size();
      for(int i = 0; i < NJet; i++)
      {
         JetE[i] = Jets[i][0];
         JetPx[i] = Jets[i][1];
         JetPy[i] = Jets[i][2];
         JetPz[i] = Jets[i][3];

         JetP[i] = Jets[i].GetP();
         JetTheta[i] = Jets[i].GetTheta();
         JetPhi[i] = Jets[i].GetPhi();
      }

      for(int i = 0; i < NJet; i++)
      {
         FourVector ElectronsNearJet = FourVector(0, 0, 0, 0);
         for(int j = 0; j < (int)Electrons.size(); j++)
         {
            double Angle = GetAngle(Electrons[j], Jets[i]);
            if(Angle < R)
               ElectronsNearJet = ElectronsNearJet + Electrons[j];
         }
         JetElectronFraction[i] = ElectronsNearJet.GetP() / Jets[i].GetP();
         
         FourVector MuonsNearJet = FourVector(0, 0, 0, 0);
         for(int j = 0; j < (int)Muons.size(); j++)
         {
            double Angle = GetAngle(Muons[j], Jets[i]);
            if(Angle < R)
               MuonsNearJet = MuonsNearJet + Muons[j];
         }
         JetMuonFraction[i] = MuonsNearJet.GetP() / Jets[i].GetP();

         vector<Node *> Nodes;

         JetN[i] = 0;
         for(int j = 0; j < NMAX; j++)
            JetXi[i][j] = -1;
         for(int j = 0; j < NMAX; j++)
            JetSubEvent[i][j] = -1;
         for(int j = 0; j < (int)VisibleParticles.size(); j++)
         {
            if(GetAngle(VisibleParticles[j], Jets[i]) < R)
            {
               JetXi[i][JetN[i]] = VisibleParticles[j].SpatialDot(Jets[i]) / Jets[i].GetP() / Jets[i].GetP();
               JetSubEvent[i][JetN[i]] = VisibleParticleSubEvent[j];
               JetN[i] = JetN[i] + 1;

               Nodes.push_back(new Node(VisibleParticles[j]));
            }
         }
         
         for(int iSD = 0; iSD < SDCount; iSD++)
         {
            JetSDZG[i][iSD] = -1;
            JetSDRG[i][iSD] = -1;
            JetSDP[i][iSD] = -1;
            JetSDDepth[i][iSD] = -1;
         }

         if(Nodes.size() > 0 && Jets[i].GetP() > 10)
         {
            BuildCATree(Nodes);

            for(int iSD = 0; iSD < SDCount; iSD++)
            {
               Node *SDNode = FindSDNode(Nodes[0], Zs[iSD], Betas[iSD], R);

               if(SDNode != nullptr && SDNode->N > 1)
               {
                  FourVector P1 = SDNode->Child1->P;
                  FourVector P2 = SDNode->Child2->P;

                  JetSDZG[i][iSD] = P2.GetP() / (P1.GetP() + P2.GetP());
                  JetSDRG[i][iSD] = GetAngle(P1, P2);
                  JetSDP[i][iSD] = (P1 + P2).GetP();
                  JetSDDepth[i][iSD] = NodeDistance(SDNode, Nodes[0]);
               }
            }

            delete Nodes[0];
         }
      }

      JetTree.Fill();
   }

   JetTree.Write();

   OutputFile.Close();
   InputFile.Close();
}







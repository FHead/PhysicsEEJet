#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

#include "fastjet/ClusterSequence.hh"
using namespace fastjet;

#include "TFile.h"
#include "TTree.h"

#include "Code/TauHelperFunctions3.h"
#include "CommandLine.h"

#include "CATree.h"

#define MAX 1000

int main(int argc, char *argv[]);
double GetMoment(FourVector &J, vector<FourVector> &P, double Alpha, double Beta, double MaxAngle, bool Scaled);

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);

   vector<string> InputFileNames = CL.GetStringVector("input");
   string InputTreeName = CL.Get("tree", "tgen");
   string OutputFileName = CL.Get("output", "meow.root");
   double JetR = CL.GetDouble("r", 0.8);
   double MaxAngle = CL.GetDouble("maxangle", JetR);
   double Fraction = CL.GetDouble("fraction", 1.00);
   double MinParticleP = CL.GetDouble("minp", 1);
   bool NoBall = CL.GetBool("noball", false);

   TFile OutputFile(OutputFileName.c_str(), "RECREATE");

   TTree OutputTree("Tree", "Tree");

   int JetCount;
   double J1P, J1Theta, J1Phi;
   double J2P, J2Theta, J2Phi;
   OutputTree.Branch("JetCount", &JetCount, "JetCount/I");
   OutputTree.Branch("J1P",      &J1P,      "J1P/D");
   OutputTree.Branch("J1Theta",  &J1Theta,  "J1Theta/D");
   OutputTree.Branch("J1Phi",    &J1Phi,    "J1Phi/D");
   OutputTree.Branch("J2P",      &J2P,      "J2P/D");
   OutputTree.Branch("J2Theta",  &J2Theta,  "J2Theta/D");
   OutputTree.Branch("J2Phi",    &J2Phi,    "J2Phi/D");

   int NMoment = 15;
   double Alpha[MAX] = {0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 5, 5, 5};
   double Beta[MAX]  = {0, 0, 0, 0, 1, 1, 1, 1, -1, -1, -1, -1, 0, 1, -1};
   double J1M[MAX];
   double J2M[MAX];
   OutputTree.Branch("NMoment", &NMoment, "NMoment/I");
   OutputTree.Branch("Alpha",   &Alpha,   "Alpha[NMoment]/D");
   OutputTree.Branch("Beta",    &Beta,    "Beta[NMoment]/D");
   OutputTree.Branch("J1M",     &J1M,     "J1M[NMoment]/D");
   OutputTree.Branch("J2M",     &J2M,     "J2M[NMoment]/D");

   int NSD = 10;
   double SDZCut[MAX] = {0.1, 0.5};
   double SDBeta[MAX] = {0.0, 1.5};
   double J1SDZG[MAX];
   double J2SDZG[MAX];
   double J1SDDR[MAX];
   double J2SDDR[MAX];
   double J1SDP[MAX];
   double J2SDP[MAX];
   OutputTree.Branch("NSD",     &NSD,     "NSD/I");
   OutputTree.Branch("SDZCut",  &SDZCut,  "SDZCut[NSD]/D");
   OutputTree.Branch("SDBeta",  &SDBeta,  "SDBeta[NSD]/D");
   OutputTree.Branch("J1SDZG",  &J1SDZG,  "J1SDZG[NSD]/D");
   OutputTree.Branch("J2SDZG",  &J2SDZG,  "J2SDZG[NSD]/D");
   OutputTree.Branch("J1SDDR",  &J1SDDR,  "J1SDDR[NSD]/D");
   OutputTree.Branch("J2SDDR",  &J2SDDR,  "J2SDDR[NSD]/D");
   OutputTree.Branch("J1SDP",   &J1SDP,   "J1SDP[NSD]/D");
   OutputTree.Branch("J2SDP",   &J2SDP,   "J2SDP[NSD]/D");

   int EventType;
   OutputTree.Branch("EventType", &EventType, "EventType/I");

   for(string FileName : InputFileNames)
   {
      cout << "Processing file " << FileName << endl;

      TFile InputFile(FileName.c_str());

      TTree *InputTree = (TTree *)InputFile.Get(InputTreeName.c_str());
      if(InputTree == nullptr)
         continue;

      int NParticle;
      float PX[MAX], PY[MAX], PZ[MAX], Mass[MAX], PMag[MAX], E[MAX];
      int pid[MAX], status[MAX], SubEvent[MAX];
      InputTree->SetBranchAddress("nParticle", &NParticle);
      InputTree->SetBranchAddress("px", &PX);
      InputTree->SetBranchAddress("py", &PY);
      InputTree->SetBranchAddress("pz", &PZ);
      InputTree->SetBranchAddress("e", &E);
      InputTree->SetBranchAddress("pmag", &PMag);
      InputTree->SetBranchAddress("mass", &Mass);
      InputTree->SetBranchAddress("pid", &pid);
      InputTree->SetBranchAddress("status", &status);
      InputTree->SetBranchAddress("subevent", &SubEvent);

      int NJet;
      float JetPT[MAX], JetEta[MAX], JetPhi[MAX];
      // InputTree->SetBranchAddress("nref", &NJet);
      // InputTree->SetBranchAddress("jtpt", &JetPT);
      // InputTree->SetBranchAddress("jteta", &JetEta);
      // InputTree->SetBranchAddress("jtphi", &JetPhi);

      int EntryCount = InputTree->GetEntries() * Fraction;
      for(int iE = 0; iE < EntryCount; iE++)
      {
         InputTree->GetEntry(iE);

         bool TauFound = false;
         bool AntiTauFound = false;
         for(int i = 0; i < NParticle; i++)
         {
            if(pid[i] == 15)   TauFound = true;
            if(pid[i] == -15)  AntiTauFound = true;
         }

         EventType = 0;
         if(TauFound && AntiTauFound)
            EventType = 1;
         if(TauFound == true && AntiTauFound == false)
            EventType = 2;
         if(TauFound == false && AntiTauFound == true)
            EventType = 2;

         // Cluster jets: in this gen tree we do not have jets pre-calculated
         vector<PseudoJet> FastJetParticles;
         for(int i = 0; i < NParticle; i++)
         {
            if(NoBall == true && SubEvent[i] != 0)
               continue;

            FourVector P(E[i], PX[i], PY[i], PZ[i]);

            if(status[i] != 1)                  continue;
            if(pid[i] == 12 || pid[i] == -12)   continue;
            if(pid[i] == 14 || pid[i] == -14)   continue;
            if(pid[i] == 16 || pid[i] == -16)   continue;

            FastJetParticles.push_back(PseudoJet(PX[i], PY[i], PZ[i], E[i]));
         }
         JetDefinition Definition(ee_genkt_algorithm, JetR, -1);
         ClusterSequence Sequence(FastJetParticles, Definition);
         vector<PseudoJet> FastJets = Sequence.inclusive_jets(0.5);

         NJet = FastJets.size();
         for(int i = 0; i < NJet; i++)
         {
            JetPT[i] = FastJets[i].perp();
            JetEta[i] = FastJets[i].eta();
            JetPhi[i] = FastJets[i].phi();
         }

         vector<FourVector> Particles;
         for(int iP = 0; iP < NParticle; iP++)
         {
            if(PMag[iP] < MinParticleP)
               continue;
            if(NoBall == true && SubEvent[iP] != 0)
               continue;
            double Energy = sqrt(PX[iP] * PX[iP] + PY[iP] * PY[iP] + PZ[iP] * PZ[iP] + Mass[iP] * Mass[iP]);
            Particles.emplace_back(Energy, PX[iP], PY[iP], PZ[iP]);
         }

         map<double, int, greater<double>> Jets;
         for(int iJ = 0; iJ < NJet; iJ++)
         {
            FourVector P;
            P.SetPtEtaPhi(JetPT[iJ], JetEta[iJ], JetPhi[iJ]);

            if(P.GetTheta() < 0.2 * M_PI)
               continue;
            if(P.GetTheta() > 0.8 * M_PI)
               continue;

            Jets.insert({P.GetP(), iJ});
         }

         if(Jets.size() < 2)
            continue;

         JetCount = NJet;

         auto iter = Jets.begin();
         int IJ1 = iter->second;
         iter++;
         int IJ2 = iter->second;

         FourVector J1, J2;
         J1.SetPtEtaPhi(JetPT[IJ1], JetEta[IJ1], JetPhi[IJ1]);
         J2.SetPtEtaPhi(JetPT[IJ2], JetEta[IJ2], JetPhi[IJ2]);

         J1P     = J1.GetP();
         J1Theta = J1.GetTheta();
         J1Phi   = J1.GetPhi();

         J2P     = J2.GetP();
         J2Theta = J2.GetTheta();
         J2Phi   = J2.GetPhi();

         for(int iM = 0; iM < NMoment; iM++)
         {
            J1M[iM] = GetMoment(J1, Particles, Alpha[iM], Beta[iM], MaxAngle, true);
            J2M[iM] = GetMoment(J2, Particles, Alpha[iM], Beta[iM], MaxAngle, true);
         }

         vector<Node *> Node1, Node2;
         for(FourVector V : Particles)
         {
            double Angle1 = GetAngle(J1, V);
            if(Angle1 < MaxAngle)
               Node1.push_back(new Node(V));
            
            double Angle2 = GetAngle(J2, V);
            if(Angle2 < MaxAngle)
               Node2.push_back(new Node(V));
         }

         BuildCATree(Node1);
         BuildCATree(Node2);

         for(int iSD = 0; iSD < NSD; iSD++)
         {
            J1SDP[iSD] = -1;
            J1SDZG[iSD] = -1;
            J2SDP[iSD] = -1;
            J2SDZG[iSD] = -1;
            
            if(Node1.size() > 0)
            {
               Node *SD1 = FindSDNode(Node1[0], SDZCut[iSD], SDBeta[iSD]);
               if(SD1 != nullptr)
                  J1SDP[iSD] = SD1->P.GetP();
               if(SD1 != nullptr && SD1->Child1 != nullptr && SD1->Child2 != nullptr)
               {
                  J1SDZG[iSD] = SD1->Child2->P.GetP() / (SD1->Child1->P.GetP() + SD1->Child2->P.GetP());
                  J1SDDR[iSD] = GetAngle(SD1->Child1->P, SD1->Child2->P);
               }
            }

            if(Node2.size() > 0)
            {
               Node *SD2 = FindSDNode(Node2[0], SDZCut[iSD], SDBeta[iSD]);
               if(SD2 != nullptr)
                  J2SDP[iSD] = SD2->P.GetP();
               if(SD2 != nullptr && SD2->Child1 != nullptr && SD2->Child2 != nullptr)
               {
                  J2SDZG[iSD] = SD2->Child2->P.GetP() / (SD2->Child1->P.GetP() + SD2->Child2->P.GetP());
                  J2SDDR[iSD] = GetAngle(SD2->Child1->P, SD2->Child2->P);
               }
            }
         }

         if(Node1.size() > 0)
         {
            delete Node1[0];
            Node1.clear();
         }
         if(Node2.size() > 0)
         {
            delete Node2[0];
            Node2.clear();
         }

         OutputTree.Fill();
      }

      InputFile.Close();
   }

   OutputFile.cd();
   OutputTree.Write();
   OutputFile.Close();

   return 0;
}

double GetMoment(FourVector &J, vector<FourVector> &P, double Alpha, double Beta, double MaxAngle, bool Scaled)
{
   double Result = 0;

   for(FourVector V : P)
   {
      double Angle = GetAngle(J, V);
      if(Angle > MaxAngle)
         continue;

      Result = Result + pow(Angle, Alpha) * pow(V.GetP(), Beta);
   }

   if(Scaled == true)
      Result = Result / pow(J.GetP(), Beta);

   return Result;
}



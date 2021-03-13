#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

#include "TFile.h"
#include "TTree.h"

#include "Code/TauHelperFunctions3.h"
#include "CommandLine.h"

#define MAX 1000

int main(int argc, char *argv[]);
double GetMoment(FourVector &J, vector<FourVector> &P, double Alpha, double Beta, double MaxAngle, bool Scaled);

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);

   vector<string> InputFileNames = CL.GetStringVector("input");
   string InputTreeName = CL.Get("tree", "akR8ESchemeJetTree");
   string OutputFileName = CL.Get("output", "meow.root");
   double MaxAngle = CL.GetDouble("maxangle", 0.8);
   double Fraction = CL.GetDouble("fraction", 1.00);
   double MinParticleP = CL.GetDouble("minp", 1);

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

   for(string FileName : InputFileNames)
   {
      cout << "Processing file " << FileName << endl;

      TFile InputFile(FileName.c_str());

      TTree *Tree = (TTree *)InputFile.Get("t");
      TTree *InputTree = (TTree *)InputFile.Get(InputTreeName.c_str());
      if(Tree == nullptr || InputTree == nullptr)
         continue;

      int NParticle;
      float PX[MAX], PY[MAX], PZ[MAX], Mass[MAX], PMag[MAX];
      Tree->SetBranchAddress("nParticle", &NParticle);
      Tree->SetBranchAddress("px", &PX);
      Tree->SetBranchAddress("py", &PY);
      Tree->SetBranchAddress("pz", &PZ);
      Tree->SetBranchAddress("pmag", &PMag);
      Tree->SetBranchAddress("mass", &Mass);

      int NJet;
      float JetPT[MAX], JetEta[MAX], JetPhi[MAX];
      InputTree->SetBranchAddress("nref", &NJet);
      InputTree->SetBranchAddress("jtpt", &JetPT);
      InputTree->SetBranchAddress("jteta", &JetEta);
      InputTree->SetBranchAddress("jtphi", &JetPhi);

      int EntryCount = InputTree->GetEntries() * Fraction;
      for(int iE = 0; iE < EntryCount; iE++)
      {
         Tree->GetEntry(iE);
         InputTree->GetEntry(iE);
      
         vector<FourVector> Particles;
         for(int iP = 0; iP < NParticle; iP++)
         {
            if(PMag[iP] < MinParticleP)
               continue;
            double E = sqrt(PX[iP] * PX[iP] + PY[iP] * PY[iP] + PZ[iP] * PZ[iP] + Mass[iP] * Mass[iP]);
            Particles.emplace_back(E, PX[iP], PY[iP], PZ[iP]);
         }

         map<double, FourVector, greater<double>> Jets;
         for(int iJ = 0; iJ < NJet; iJ++)
         {
            FourVector P;
            P.SetPtEtaPhi(JetPT[iJ], JetEta[iJ], JetPhi[iJ]);

            if(P.GetTheta() < 0.2 * M_PI)
               continue;
            if(P.GetTheta() > 0.8 * M_PI)
               continue;

            Jets.insert({P.GetP(), P});
         }

         if(Jets.size() < 2)
            continue;

         JetCount = NJet;

         auto iter = Jets.begin();
         FourVector J1 = iter->second;
         iter++;
         FourVector J2 = iter->second;

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



#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
using namespace std;

#include "TH1D.h"
#include "TFile.h"
#include "TTree.h"

#include "Code/TauHelperFunctions3.h"
#include "CommandLine.h"

#define MAX 1000

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);

   string InputFileName = CL.Get("Input");
   string OutputFileName = CL.Get("Output", "Skim.root");
   double Fraction = CL.GetDouble("Fraction", 0.1);
   double JetR = CL.GetDouble("JetR", 0.4);
   double TrackDA = CL.GetDouble("TrackDA", 0.4);

   TFile InputFile(InputFileName.c_str());
   TFile OutputFile(OutputFileName.c_str(), "RECREATE");

   TTree *T = (TTree *)InputFile.Get("t");
   TTree *J = (TTree *)InputFile.Get("akR4ESchemeJetTree");

   int nParticle;
   float px[MAX], py[MAX], pz[MAX], pmag[MAX], theta[MAX], mass[MAX], phi[MAX];
   T->SetBranchAddress("nParticle", &nParticle);
   T->SetBranchAddress("px", &px);
   T->SetBranchAddress("py", &py);
   T->SetBranchAddress("pz", &pz);
   T->SetBranchAddress("pmag", &pmag);
   T->SetBranchAddress("theta", &theta);
   T->SetBranchAddress("phi", &phi);
   T->SetBranchAddress("mass", &mass);

   int nref;
   float jtpt[MAX], jteta[MAX], jtphi[MAX], jtm[MAX];
   J->SetBranchAddress("nref", &nref);
   J->SetBranchAddress("jtpt", &jtpt);
   J->SetBranchAddress("jteta", &jteta);
   J->SetBranchAddress("jtphi", &jtphi);
   J->SetBranchAddress("jtm", &jtm);

   TTree OutputTree("T", "Skimmed tree");

   int Group[MAX];   // 0 = outside, 1 = J1, 2 = J2
   int N08, N10, N15, N20, N30, N50;
   int O08, O10, O15, O20, O30, O50;
   int J108, J110, J115, J120, J130, J150;
   int J208, J210, J215, J220, J230, J250;
   double J1Px, J1Py, J1Pz, J1P, J1Theta, J1Phi, J1Mass;
   double J2Px, J2Py, J2Pz, J2P, J2Theta, J2Phi, J2Mass;

   OutputTree.Branch("NP", &nParticle, "NP/I");
   OutputTree.Branch("Px", &px, "Px[NP]/F");
   OutputTree.Branch("Py", &py, "Py[NP]/F");
   OutputTree.Branch("Pz", &pz, "Pz[NP]/F");
   OutputTree.Branch("P", &pmag, "P[NP]/F");
   OutputTree.Branch("Theta", &theta, "Theta[NP]/F");
   OutputTree.Branch("Phi", &phi, "Phi[NP]/F");
   OutputTree.Branch("Mass", &mass, "Mass[NP]/F");
   OutputTree.Branch("Group", &Group, "Group[NP]/I");

   OutputTree.Branch("N08", &N08, "N08/I");
   OutputTree.Branch("N10", &N10, "N10/I");
   OutputTree.Branch("N15", &N15, "N15/I");
   OutputTree.Branch("N20", &N20, "N20/I");
   OutputTree.Branch("N30", &N30, "N30/I");
   OutputTree.Branch("N50", &N50, "N50/I");
   OutputTree.Branch("O08", &O08, "O08/I");
   OutputTree.Branch("O10", &O10, "O10/I");
   OutputTree.Branch("O15", &O15, "O15/I");
   OutputTree.Branch("O20", &O20, "O20/I");
   OutputTree.Branch("O30", &O30, "O30/I");
   OutputTree.Branch("O50", &O50, "O50/I");
   OutputTree.Branch("J108", &J108, "J108/I");
   OutputTree.Branch("J110", &J110, "J110/I");
   OutputTree.Branch("J115", &J115, "J115/I");
   OutputTree.Branch("J120", &J120, "J120/I");
   OutputTree.Branch("J130", &J130, "J130/I");
   OutputTree.Branch("J150", &J150, "J150/I");
   OutputTree.Branch("J208", &J208, "J208/I");
   OutputTree.Branch("J210", &J210, "J210/I");
   OutputTree.Branch("J215", &J215, "J215/I");
   OutputTree.Branch("J220", &J220, "J220/I");
   OutputTree.Branch("J230", &J230, "J230/I");
   OutputTree.Branch("J250", &J250, "J250/I");

   OutputTree.Branch("J1Px", &J1Px, "J1Px/D");
   OutputTree.Branch("J1Py", &J1Py, "J1Py/D");
   OutputTree.Branch("J1Pz", &J1Pz, "J1Pz/D");
   OutputTree.Branch("J1P", &J1P, "J1P/D");
   OutputTree.Branch("J1Theta", &J1Theta, "J1Theta/D");
   OutputTree.Branch("J1Phi", &J1Phi, "J1Phi/D");
   OutputTree.Branch("J1Mass", &J1Mass, "J1Mass/D");

   OutputTree.Branch("J2Px", &J2Px, "J2Px/D");
   OutputTree.Branch("J2Py", &J2Py, "J2Py/D");
   OutputTree.Branch("J2Pz", &J2Pz, "J2Pz/D");
   OutputTree.Branch("J2P", &J2P, "J2P/D");
   OutputTree.Branch("J2Theta", &J2Theta, "J2Theta/D");
   OutputTree.Branch("J2Phi", &J2Phi, "J2Phi/D");
   OutputTree.Branch("J2Mass", &J2Mass, "J2Mass/D");

   int EntryCount = T->GetEntries() * Fraction;
   for(int iE = 0; iE < EntryCount; iE++)
   {
      T->GetEntry(iE);
      J->GetEntry(iE);

      J1Px = 0, J1Py = 0, J1Pz = 0, J1P = 0, J1Mass = 0, J1Theta = 0, J1Phi = 0;
      J2Px = 0, J2Py = 0, J2Pz = 0, J2P = 0, J2Mass = 0, J2Theta = 0, J2Phi = 0;

      vector<pair<double, FourVector>> Jets;
      for(int i = 0; i < nref; i++)
      {
         FourVector Jet;
         Jet.SetPtEtaPhiMass(jtpt[i], jteta[i], jtphi[i], jtm[i]);
         Jets.push_back(pair<double, FourVector>(-Jet.GetP(), Jet));
      }
      sort(Jets.begin(), Jets.end());

      FourVector J1(0, 0, 0, 0), J2(0, 0, 0, 0);

      if(Jets.size() > 0)
      {
         J1      = Jets[0].second;
         J1Px    = J1[1];
         J1Py    = J1[2];
         J1Pz    = J1[3];
         J1P     = J1.GetP();
         J1Theta = J1.GetTheta();
         J1Mass  = J1.GetMass();
         J1Phi   = J1.GetPhi();
      }
      if(Jets.size() > 1)
      {
         J2      = Jets[1].second;
         J2Px    = J2[1];
         J2Py    = J2[2];
         J2Pz    = J2[3];
         J2P     = J2.GetP();
         J2Theta = J2.GetTheta();
         J2Mass  = J2.GetMass();
         J2Phi   = J2.GetPhi();
      }

      N08 = 0, N10 = 0, N15 = 0, N20 = 0, N30 = 0, N50 = 0;
      O08 = 0, O10 = 0, O15 = 0, O20 = 0, O30 = 0, O50 = 0;
      J108 = 0, J110 = 0, J115 = 0, J120 = 0, J130 = 0, J150 = 0;
      J208 = 0, J210 = 0, J215 = 0, J220 = 0, J230 = 0, J250 = 0;
      for(int i = 0; i < nParticle; i++)
      {
         Group[i] = 0;

         double DA1 = 9999, DA2 = 9999;
         FourVector PTrack(pmag[i], px[i], py[i], pz[i]);

         if(J1[0] > 0)   DA1 = GetAngle(J1, PTrack);
         if(J2[0] > 0)   DA2 = GetAngle(J2, PTrack);

         if(DA1 < DA2 && DA1 < TrackDA)  Group[i] = 1;
         if(DA2 < DA1 && DA2 < TrackDA)  Group[i] = 2;

         if(theta[i] < 0.1 * M_PI)   continue;
         if(theta[i] > 0.9 * M_PI)   continue;

         if(pmag[i] > 0.8)  N08++;
         if(pmag[i] > 1.0)  N10++;
         if(pmag[i] > 1.5)  N15++;
         if(pmag[i] > 2.0)  N20++;
         if(pmag[i] > 3.0)  N30++;
         if(pmag[i] > 5.0)  N50++;

         if(Group[i] == 0 && pmag[i] > 0.8)  O08++;
         if(Group[i] == 0 && pmag[i] > 1.0)  O10++;
         if(Group[i] == 0 && pmag[i] > 1.5)  O15++;
         if(Group[i] == 0 && pmag[i] > 2.0)  O20++;
         if(Group[i] == 0 && pmag[i] > 3.0)  O30++;
         if(Group[i] == 0 && pmag[i] > 5.0)  O50++;

         if(Group[i] == 1 && pmag[i] > 0.8)  J108++;
         if(Group[i] == 1 && pmag[i] > 1.0)  J110++;
         if(Group[i] == 1 && pmag[i] > 1.5)  J115++;
         if(Group[i] == 1 && pmag[i] > 2.0)  J120++;
         if(Group[i] == 1 && pmag[i] > 3.0)  J130++;
         if(Group[i] == 1 && pmag[i] > 5.0)  J150++;

         if(Group[i] == 2 && pmag[i] > 0.8)  J208++;
         if(Group[i] == 2 && pmag[i] > 1.0)  J210++;
         if(Group[i] == 2 && pmag[i] > 1.5)  J215++;
         if(Group[i] == 2 && pmag[i] > 2.0)  J220++;
         if(Group[i] == 2 && pmag[i] > 3.0)  J230++;
         if(Group[i] == 2 && pmag[i] > 5.0)  J250++;
      }

      OutputTree.Fill();
   }

   OutputTree.Write();

   OutputFile.Close();
   InputFile.Close();

   return 0;
}






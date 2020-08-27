#include <iostream>
#include <cmath>
using namespace std;

#include "TFile.h"
#include "TTree.h"

#include "CommandLine.h"
#include "Code/TauHelperFunctions3.h"

#define MAX 1000

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);

   string InputFileName = CL.Get("Input");
   string OutputFileName = CL.Get("Output");

   TFile InputFile(InputFileName.c_str());
   TFile OutputFile(OutputFileName.c_str(), "RECREATE");

   int N;
   float JetPT[MAX], JetEta[MAX], JetTheta[MAX], JetPhi[MAX], JetM[MAX];

   TTree *InputTree = (TTree *)InputFile.Get("Tree");
   InputTree->SetBranchAddress("N", &N);
   InputTree->SetBranchAddress("JetPT", &JetPT);
   InputTree->SetBranchAddress("JetEta", &JetEta);
   InputTree->SetBranchAddress("JetTheta", &JetTheta);
   InputTree->SetBranchAddress("JetPhi", &JetPhi);
   InputTree->SetBranchAddress("JetM", &JetM);

   float J1PT, J1Eta, J1Theta, J1Phi, J1M;
   float J2PT, J2Eta, J2Theta, J2Phi, J2M;
   float J3PT, J3Eta, J3Theta, J3Phi, J3M;
   float J4PT, J4Eta, J4Theta, J4Phi, J4M;
   float M12, M123;

   TTree OutputTree("SkimmedTree", "");
   OutputTree.Branch("J1PT", &J1PT, "J1PT/F");
   OutputTree.Branch("J1Eta", &J1Eta, "J1Eta/F");
   OutputTree.Branch("J1Theta", &J1Theta, "J1Theta/F");
   OutputTree.Branch("J1Phi", &J1Phi, "J1Phi/F");
   OutputTree.Branch("J1M", &J1M, "J1M/F");
   OutputTree.Branch("J2PT", &J2PT, "J2PT/F");
   OutputTree.Branch("J2Eta", &J2Eta, "J2Eta/F");
   OutputTree.Branch("J2Theta", &J2Theta, "J2Theta/F");
   OutputTree.Branch("J2Phi", &J2Phi, "J2Phi/F");
   OutputTree.Branch("J2M", &J2M, "J2M/F");
   OutputTree.Branch("J3PT", &J3PT, "J3PT/F");
   OutputTree.Branch("J3Eta", &J3Eta, "J3Eta/F");
   OutputTree.Branch("J3Theta", &J3Theta, "J3Theta/F");
   OutputTree.Branch("J3Phi", &J3Phi, "J3Phi/F");
   OutputTree.Branch("J3M", &J3M, "J3M/F");
   OutputTree.Branch("J4PT", &J4PT, "J4PT/F");
   OutputTree.Branch("J4Eta", &J4Eta, "J4Eta/F");
   OutputTree.Branch("J4Theta", &J4Theta, "J4Theta/F");
   OutputTree.Branch("J4Phi", &J4Phi, "J4Phi/F");
   OutputTree.Branch("J4M", &J4M, "J4M/F");
   OutputTree.Branch("M12", &M12, "M12/F");
   OutputTree.Branch("M123", &M123, "M123/F");

   double ThetaMin = 0.00 * M_PI;
   double ThetaMax = 1.00 * M_PI;

   int EntryCount = InputTree->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      InputTree->GetEntry(iE);

      if(N < 2)
         continue;

      if(JetTheta[0] < ThetaMin || JetTheta[0] > ThetaMax)
         continue;
      if(JetTheta[1] < ThetaMin || JetTheta[1] > ThetaMax)
         continue;
      // if(JetTheta[2] < ThetaMin || JetTheta[2] > ThetaMax)
      //    continue;

      J1PT = JetPT[0];
      J1Eta = JetEta[0];
      J1Theta = JetTheta[0];
      J1Phi = JetPhi[0];
      J1M = JetM[0];
      J2PT = JetPT[1];
      J2Eta = JetEta[1];
      J2Theta = JetTheta[1];
      J2Phi = JetPhi[1];
      J2M = JetM[1];
      if(N >= 3)
      {
         J3PT = JetPT[2];
         J3Eta = JetEta[2];
         J3Theta = JetTheta[2];
         J3Phi = JetPhi[2];
         J3M = JetM[2];
      }
      else
         J3PT = 0;
      if(N >= 4)
      {
         J4PT = JetPT[3];
         J4Eta = JetEta[3];
         J4Theta = JetTheta[3];
         J4Phi = JetPhi[3];
         J4M = JetM[3];
      }
      else
         J4PT = 0;
      
      FourVector J1, J2, J3;
      J1.SetPtEtaPhiMass(J1PT, J1Eta, J1Phi, J1M);
      J2.SetPtEtaPhiMass(J2PT, J2Eta, J2Phi, J2M);
      J3.SetPtEtaPhiMass(J3PT, J3Eta, J3Phi, J3M);

      M12 = (J1 + J2).GetMass();
      M123 = (J1 + J2 + J3).GetMass();

      OutputTree.Fill();
   }

   OutputTree.Write();

   OutputFile.Close();
   InputFile.Close();

   return 0;
}




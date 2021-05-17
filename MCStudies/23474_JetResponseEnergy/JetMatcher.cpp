#include <iostream>
#include <vector>
using namespace std;

#include "TFile.h"
#include "TH1D.h"
#include "TTree.h"

#include "CommandLine.h"
#include "Code/TauHelperFunctions3.h"

#include "JetCorrector.h"

#define MAX 1000

int main(int argc, char *argv[]);
double EtaToTheta(double Eta);

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);

   string FileName       = CL.Get("FileName");
   string OutputFileName = CL.Get("Output");
   string RecoTreeName   = CL.Get("RecoTree");
   string GenTreeName    = CL.Get("GenTree");
   double Fraction       = CL.GetDouble("Fraction", 1.00);
   string JECFile        = CL.Get("JEC", "");

   TFile File(FileName.c_str());

   TTree *RecoTree = (TTree *)File.Get(RecoTreeName.c_str());
   TTree *GenTree  = (TTree *)File.Get(GenTreeName.c_str());

   int GenNJet;
   float GenJetPT[MAX], GenJetEta[MAX], GenJetPhi[MAX], GenJetM[MAX];
   int GenJetN[MAX];
   int RecoNJet;
   float RecoJetPT[MAX], RecoJetEta[MAX], RecoJetPhi[MAX], RecoJetM[MAX];
   int RecoJetN[MAX];

   GenTree->SetBranchAddress("nref",   &GenNJet);
   GenTree->SetBranchAddress("jtpt",   &GenJetPT);
   GenTree->SetBranchAddress("jteta",  &GenJetEta);
   GenTree->SetBranchAddress("jtphi",  &GenJetPhi);
   GenTree->SetBranchAddress("jtm",    &GenJetM);
   GenTree->SetBranchAddress("jtN",    &GenJetN);
   RecoTree->SetBranchAddress("nref",  &RecoNJet);
   RecoTree->SetBranchAddress("jtpt",  &RecoJetPT);
   RecoTree->SetBranchAddress("jtm",   &RecoJetM);
   RecoTree->SetBranchAddress("jteta", &RecoJetEta);
   RecoTree->SetBranchAddress("jtphi", &RecoJetPhi);
   RecoTree->SetBranchAddress("jtN",   &RecoJetN);

   TFile OutputFile(OutputFileName.c_str(), "RECREATE");

   TTree OutputTree("MatchedTree", "Meow");

   double MatchedGenE, MatchedGenPT, MatchedGenEta, MatchedGenTheta, MatchedGenPhi;       int MatchedGenN;
   double MatchedRecoE, MatchedRecoPT, MatchedRecoEta, MatchedRecoTheta, MatchedRecoPhi;   int MatchedRecoN;
   double MatchedAngle, MatchedCorrectedPT, MatchedCorrectedE;

   OutputTree.Branch("GenE",        &MatchedGenE,        "GenE/D");
   OutputTree.Branch("GenPT",       &MatchedGenPT,       "GenPT/D");
   OutputTree.Branch("GenEta",      &MatchedGenEta,      "GenEta/D");
   OutputTree.Branch("GenTheta",    &MatchedGenTheta,    "GenTheta/D");
   OutputTree.Branch("GenPhi",      &MatchedGenPhi,      "GenPhi/D");
   OutputTree.Branch("GenN",        &MatchedGenN,        "GenN/I");
   OutputTree.Branch("RecoE",       &MatchedRecoE,       "RecoE/D");
   OutputTree.Branch("CorrectedE",  &MatchedCorrectedE,  "CorrectedE/D");
   OutputTree.Branch("RecoPT",      &MatchedRecoPT,      "RecoPT/D");
   OutputTree.Branch("CorrectedPT", &MatchedCorrectedPT, "CorrectedPT/D");
   OutputTree.Branch("RecoEta",     &MatchedRecoEta,     "RecoEta/D");
   OutputTree.Branch("RecoTheta",   &MatchedRecoTheta,   "RecoTheta/D");
   OutputTree.Branch("RecoPhi",     &MatchedRecoPhi,     "RecoPhi/D");
   OutputTree.Branch("RecoN",       &MatchedRecoN,       "RecoN/I");
   OutputTree.Branch("Angle",       &MatchedAngle,       "Angle/D");

   JetCorrector JEC(JECFile);

   int EntryCount = RecoTree->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      GenTree->GetEntry(iE);
      RecoTree->GetEntry(iE);

      vector<bool> RecoUsed(RecoNJet, false);

      for(int iJ = 0; iJ < GenNJet; iJ++)
      {
         int Best = -1;
         double BestAngle = -1;
         FourVector BestP;

         FourVector Gen;
         Gen.SetPtEtaPhiMass(GenJetPT[iJ], GenJetEta[iJ], GenJetPhi[iJ], GenJetM[iJ]);

         for(int i = 0; i < RecoNJet; i++)
         {
            if(RecoUsed[i] == true)
               continue;

            FourVector Reco;
            Reco.SetPtEtaPhiMass(RecoJetPT[i], RecoJetEta[i], RecoJetPhi[i], RecoJetM[i]);

            double Angle = GetAngle(Gen, Reco);

            if(Best < 0 || BestAngle > Angle)
            {
               Best = i;
               BestAngle = Angle;
               BestP = Reco;
            }
         }

         if(Best < 0)   // no match
            continue;

         JEC.SetJetE(BestP[0]);
         JEC.SetJetP(BestP.GetP());
         JEC.SetJetTheta(BestP.GetTheta());
         JEC.SetJetPhi(BestP.GetPhi());

         MatchedGenE        = Gen[0];
         MatchedGenPT       = Gen.GetPT();
         MatchedGenEta      = Gen.GetEta();
         MatchedGenTheta    = Gen.GetTheta();
         MatchedGenPhi      = Gen.GetPhi();
         MatchedGenN        = GenJetN[iJ];
         MatchedRecoE       = BestP[0];
         MatchedCorrectedE  = BestP[0] * JEC.GetCorrection();
         MatchedRecoPT      = BestP.GetPT();
         MatchedCorrectedPT = BestP.GetPT() * JEC.GetCorrection();
         MatchedRecoEta     = BestP.GetEta();
         MatchedRecoTheta   = BestP.GetTheta();
         MatchedRecoPhi     = BestP.GetPhi();
         MatchedRecoN       = RecoJetN[Best];
         MatchedAngle       = sqrt(BestAngle);

         RecoUsed[Best] = true;

         OutputTree.Fill();
      }
   }

   OutputTree.Write();

   OutputFile.Close();

   File.Close();

   return 0;
}

double EtaToTheta(double Eta)
{
   double x = exp(-2 * fabs(Eta));

   double y = (1 - x) / (1 + x);

   double Theta = acos(y);

   if(Eta < 0)
      Theta = M_PI - Theta;

   return Theta;
}






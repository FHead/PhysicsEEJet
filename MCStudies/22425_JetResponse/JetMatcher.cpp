#include <iostream>
#include <vector>
using namespace std;

#include "TFile.h"
#include "TH1D.h"
#include "TTree.h"

#include "CommandLine.h"

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

   TFile File(FileName.c_str());

   TTree *RecoTree = (TTree *)File.Get(RecoTreeName.c_str());
   TTree *GenTree  = (TTree *)File.Get(GenTreeName.c_str());

   int GenNJet;
   float GenJetPT[MAX], GenJetEta[MAX], GenJetPhi[MAX];
   int GenJetN[MAX];
   int RecoNJet;
   float RecoJetPT[MAX], RecoJetEta[MAX], RecoJetPhi[MAX];
   int RecoJetN[MAX];

   GenTree->SetBranchAddress("nref",   &GenNJet);
   GenTree->SetBranchAddress("jtpt",   &GenJetPT);
   GenTree->SetBranchAddress("jteta",  &GenJetEta);
   GenTree->SetBranchAddress("jtphi",  &GenJetPhi);
   GenTree->SetBranchAddress("jtN",    &GenJetN);
   RecoTree->SetBranchAddress("nref",  &RecoNJet);
   RecoTree->SetBranchAddress("jtpt",  &RecoJetPT);
   RecoTree->SetBranchAddress("jteta", &RecoJetEta);
   RecoTree->SetBranchAddress("jtphi", &RecoJetPhi);
   RecoTree->SetBranchAddress("jtN",   &RecoJetN);

   TFile OutputFile(OutputFileName.c_str(), "RECREATE");

   TTree OutputTree("MatchedTree", "Meow");

   double MatchedGenPT, MatchedGenEta, MatchedGenTheta, MatchedGenPhi;       int MatchedGenN;
   double MatchedRecoPT, MatchedRecoEta, MatchedRecoTheta, MatchedRecoPhi;   int MatchedRecoN;
   double MatchedDR;

   OutputTree.Branch("GenPT",     &MatchedGenPT,     "GenPT/D");
   OutputTree.Branch("GenEta",    &MatchedGenEta,    "GenEta/D");
   OutputTree.Branch("GenTheta",  &MatchedGenTheta,  "GenTheta/D");
   OutputTree.Branch("GenPhi",    &MatchedGenPhi,    "GenPhi/D");
   OutputTree.Branch("GenN",      &MatchedGenN,      "GenN/I");
   OutputTree.Branch("RecoPT",    &MatchedRecoPT,    "RecoPT/D");
   OutputTree.Branch("RecoEta",   &MatchedRecoEta,   "RecoEta/D");
   OutputTree.Branch("RecoTheta", &MatchedRecoTheta, "RecoTheta/D");
   OutputTree.Branch("RecoPhi",   &MatchedRecoPhi,   "RecoPhi/D");
   OutputTree.Branch("RecoN",     &MatchedRecoN,     "RecoN/I");
   OutputTree.Branch("DR",        &MatchedDR,        "DR/D");

   int EntryCount = RecoTree->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      GenTree->GetEntry(iE);
      RecoTree->GetEntry(iE);

      vector<bool> RecoUsed(RecoNJet, false);

      for(int iJ = 0; iJ < GenNJet; iJ++)
      {
         int Best = -1;
         double BestDR2 = -1;

         for(int i = 0; i < RecoNJet; i++)
         {
            if(RecoUsed[i] == true)
               continue;

            double DEta = GenJetEta[iJ] - RecoJetEta[i];
            double DPhi = GenJetPhi[iJ] - RecoJetPhi[i];
            if(DPhi < -M_PI)   DPhi = DPhi + 2 * M_PI;
            if(DPhi > +M_PI)   DPhi = DPhi - 2 * M_PI;

            double DR2 = DEta * DEta + DPhi * DPhi;

            if(Best < 0 || BestDR2 > DR2)
            {
               Best = i;
               BestDR2 = DR2;
            }
         }

         if(Best < 0)   // no match
            continue;

         MatchedGenPT     = GenJetPT[iJ];
         MatchedGenEta    = GenJetEta[iJ];
         MatchedGenTheta  = EtaToTheta(GenJetEta[iJ]);
         MatchedGenPhi    = GenJetPhi[iJ];
         MatchedGenN      = GenJetN[iJ];
         MatchedRecoPT    = RecoJetPT[Best];
         MatchedRecoEta   = RecoJetEta[Best];
         MatchedRecoTheta = EtaToTheta(RecoJetEta[Best]);
         MatchedRecoPhi   = RecoJetPhi[Best];
         MatchedRecoN     = RecoJetN[Best];
         MatchedDR        = sqrt(BestDR2);

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






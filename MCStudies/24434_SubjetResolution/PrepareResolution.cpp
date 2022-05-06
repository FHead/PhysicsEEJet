#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

#include "TFile.h"
#include "TTree.h"

#include "PlotHelper4.h"
#include "Code/TauHelperFunctions3.h"
#include "CommandLine.h"
#include "ProgressBar.h"

int main(int argc, char *argv[]);

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);

   string InputFileName = CL.Get("Input");
   double Fraction = CL.GetDouble("Fraction", 1.00); 
   string OutputFileName = CL.Get("Output");

   double MinTheta = CL.GetDouble("MinTheta", 0.2 * M_PI);
   double MaxTheta = CL.GetDouble("MaxTheta", 0.8 * M_PI);
   double MinE = CL.GetDouble("MinE", 10);
   double MaxAngle = CL.GetDouble("MaxAngle", 0.2);

   TFile File(InputFileName.c_str());

   TTree *Tree = (TTree *)File.Get("UnfoldingTree");

   int NJet = 0;
   vector<float> *GenJetE = nullptr;
   vector<float> *GenJetPX = nullptr;
   vector<float> *GenJetPY = nullptr;
   vector<float> *GenJetPZ = nullptr;
   vector<vector<float>> *GenJetSJ1E = nullptr;
   vector<vector<float>> *GenJetSJ1PX = nullptr;
   vector<vector<float>> *GenJetSJ1PY = nullptr;
   vector<vector<float>> *GenJetSJ1PZ = nullptr;
   vector<vector<float>> *GenJetSJ2E = nullptr;
   vector<vector<float>> *GenJetSJ2PX = nullptr;
   vector<vector<float>> *GenJetSJ2PY = nullptr;
   vector<vector<float>> *GenJetSJ2PZ = nullptr;
   vector<float> *MatchedJetE = nullptr;
   vector<float> *MatchedJetPX = nullptr;
   vector<float> *MatchedJetPY = nullptr;
   vector<float> *MatchedJetPZ = nullptr;
   vector<vector<float>> *MatchedJetSJ1E = nullptr;
   vector<vector<float>> *MatchedJetSJ1PX = nullptr;
   vector<vector<float>> *MatchedJetSJ1PY = nullptr;
   vector<vector<float>> *MatchedJetSJ1PZ = nullptr;
   vector<vector<float>> *MatchedJetSJ2E = nullptr;
   vector<vector<float>> *MatchedJetSJ2PX = nullptr;
   vector<vector<float>> *MatchedJetSJ2PY = nullptr;
   vector<vector<float>> *MatchedJetSJ2PZ = nullptr;
   vector<float> *MatchedJetAngle = nullptr;

   Tree->SetBranchAddress("NGenJets", &NJet);
   Tree->SetBranchAddress("GenJetE", &GenJetE);
   Tree->SetBranchAddress("GenJetPX", &GenJetPX);
   Tree->SetBranchAddress("GenJetPY", &GenJetPY);
   Tree->SetBranchAddress("GenJetPZ", &GenJetPZ);
   Tree->SetBranchAddress("GenJetSJ1E", &GenJetSJ1E);
   Tree->SetBranchAddress("GenJetSJ1PX", &GenJetSJ1PX);
   Tree->SetBranchAddress("GenJetSJ1PY", &GenJetSJ1PY);
   Tree->SetBranchAddress("GenJetSJ1PZ", &GenJetSJ1PZ);
   Tree->SetBranchAddress("GenJetSJ2E", &GenJetSJ2E);
   Tree->SetBranchAddress("GenJetSJ2PX", &GenJetSJ2PX);
   Tree->SetBranchAddress("GenJetSJ2PY", &GenJetSJ2PY);
   Tree->SetBranchAddress("GenJetSJ2PZ", &GenJetSJ2PZ);
   Tree->SetBranchAddress("MatchedJetE", &MatchedJetE);
   Tree->SetBranchAddress("MatchedJetPX", &MatchedJetPX);
   Tree->SetBranchAddress("MatchedJetPY", &MatchedJetPY);
   Tree->SetBranchAddress("MatchedJetPZ", &MatchedJetPZ);
   Tree->SetBranchAddress("MatchedJetSJ1E", &MatchedJetSJ1E);
   Tree->SetBranchAddress("MatchedJetSJ1PX", &MatchedJetSJ1PX);
   Tree->SetBranchAddress("MatchedJetSJ1PY", &MatchedJetSJ1PY);
   Tree->SetBranchAddress("MatchedJetSJ1PZ", &MatchedJetSJ1PZ);
   Tree->SetBranchAddress("MatchedJetSJ2E", &MatchedJetSJ2E);
   Tree->SetBranchAddress("MatchedJetSJ2PX", &MatchedJetSJ2PX);
   Tree->SetBranchAddress("MatchedJetSJ2PY", &MatchedJetSJ2PY);
   Tree->SetBranchAddress("MatchedJetSJ2PZ", &MatchedJetSJ2PZ);
   Tree->SetBranchAddress("MatchedJetAngle", &MatchedJetAngle);

   double TreeGenE;
   double TreeRecoE;
   double TreeSJ1GenE;
   double TreeSJ1RecoE;
   double TreeSJ1Angle;
   double TreeSJ2GenE;
   double TreeSJ2RecoE;
   double TreeSJ2Angle;

   TFile OutputFile(OutputFileName.c_str(), "RECREATE");

   TTree OutputTree("Tree", "Tree");

   OutputTree.Branch("GenE", &TreeGenE);
   OutputTree.Branch("RecoE", &TreeRecoE);
   OutputTree.Branch("SJ1GenE", &TreeSJ1GenE);
   OutputTree.Branch("SJ1RecoE", &TreeSJ1RecoE);
   OutputTree.Branch("SJ1Angle", &TreeSJ1Angle);
   OutputTree.Branch("SJ2GenE", &TreeSJ2GenE);
   OutputTree.Branch("SJ2RecoE", &TreeSJ2RecoE);
   OutputTree.Branch("SJ2Angle", &TreeSJ2Angle);

   int EntryCount = Tree->GetEntries() * Fraction;
   ProgressBar Bar(cout, EntryCount);
   Bar.SetStyle(-1);

   for(int iE = 0; iE < EntryCount; iE++)
   {
      if(EntryCount < 500 || (iE % (EntryCount / 250)) == 0)
      {
         Bar.Update(iE);
         Bar.Print();
      }

      Tree->GetEntry(iE);

      for(int iJ = 0; iJ < NJet; iJ++)
      {
         if((*MatchedJetAngle)[iJ] < 0)          continue;
         if((*MatchedJetAngle)[iJ] > MaxAngle)   continue;

         FourVector PGen((*GenJetE)[iJ], (*GenJetPX)[iJ], (*GenJetPY)[iJ], (*GenJetPZ)[iJ]);
         FourVector PMatched((*MatchedJetE)[iJ], (*MatchedJetPX)[iJ], (*MatchedJetPY)[iJ], (*MatchedJetPZ)[iJ]);

         if(PGen[0] < MinE)                    continue;
         if(PGen.GetTheta() < MinTheta)        continue;
         if(PGen.GetTheta() > MaxTheta)        continue;
         if(PMatched.GetTheta() < MinTheta)    continue;
         if(PMatched.GetTheta() > MaxTheta)    continue;

         if((*GenJetSJ1E)[iJ][0] < 1e-3)       continue;
         if((*GenJetSJ2E)[iJ][0] < 1e-3)       continue;
         if((*MatchedJetSJ1E)[iJ][0] < 1e-3)   continue;
         if((*MatchedJetSJ2E)[iJ][0] < 1e-3)   continue;

         FourVector PGenSJ1((*GenJetSJ1E)[iJ][0], (*GenJetSJ1PX)[iJ][0],
            (*GenJetSJ1PY)[iJ][0], (*GenJetSJ1PZ)[iJ][0]);
         FourVector PGenSJ2((*GenJetSJ2E)[iJ][0], (*GenJetSJ2PX)[iJ][0],
            (*GenJetSJ2PY)[iJ][0], (*GenJetSJ2PZ)[iJ][0]);
         FourVector PMatchedSJ1((*MatchedJetSJ1E)[iJ][0], (*MatchedJetSJ1PX)[iJ][0],
            (*MatchedJetSJ1PY)[iJ][0], (*MatchedJetSJ1PZ)[iJ][0]);
         FourVector PMatchedSJ2((*MatchedJetSJ2E)[iJ][0], (*MatchedJetSJ2PX)[iJ][0],
            (*MatchedJetSJ2PY)[iJ][0], (*MatchedJetSJ2PZ)[iJ][0]);

         double Angle11 = GetAngle(PGenSJ1, PMatchedSJ1);
         double Angle12 = GetAngle(PGenSJ1, PMatchedSJ2);
         double Angle21 = GetAngle(PGenSJ2, PMatchedSJ1);
         double Angle22 = GetAngle(PGenSJ2, PMatchedSJ2);

         if(Angle11 + Angle22 > Angle12 + Angle21)   // check if we match the right one based on angle
            swap(PMatchedSJ1, PMatchedSJ2);

         double Angle1 = GetAngle(PGenSJ1, PMatchedSJ1);
         double Angle2 = GetAngle(PGenSJ2, PMatchedSJ2);

         TreeGenE     = (*GenJetE)[iJ];
         TreeRecoE    = (*MatchedJetE)[iJ];
         TreeSJ1GenE  = PGenSJ1[0];
         TreeSJ1RecoE = PMatchedSJ1[0];
         TreeSJ1Angle = Angle1;
         TreeSJ2GenE  = PGenSJ2[0];
         TreeSJ2RecoE = PMatchedSJ2[0];
         TreeSJ2Angle = Angle2;

         OutputTree.Fill();
      }
   }

   Bar.Update(EntryCount);
   Bar.Print();
   Bar.PrintLine();

   OutputTree.Write();
   OutputFile.Close();

   File.Close();

   return 0;
}





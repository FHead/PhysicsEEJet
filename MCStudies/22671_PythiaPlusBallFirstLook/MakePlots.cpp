#include <iostream>
#include <vector>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TH2D.h"

#include "CommandLine.h"
#include "CustomAssert.h"
#include "SetStyle.h"
#include "Code/TauHelperFunctions3.h"

#define MAX 200

int main(int argc, char *argv[]);

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   string InputFileName = CL.Get("Input");
   string OutputFileName = CL.Get("Output");
   string TreeName = CL.Get("Tree", "JetTree");

   TFile InputFile(InputFileName.c_str());
   TFile OutputFile(OutputFileName.c_str(), "RECREATE");

   TH1D HJetP("HJetP", "Jet P, theta = 0.2-0.8 pi", 100, 0, 50);
   TH1D HJetTheta("HJetTheta", "Jet theta, theta = 0.2-0.8 pi", 100, 0, 1);
   TH1D HJetXi("HJetXi", ";#xi;#frac{1}{N_{jet}}#frac{dN}{d#xi}", 100, 0, 5.5);
   TH1D HJetXi_20_25("HJetXi_20_25", "JetP = 20-25;#xi;#frac{1}{N_{jet}}#frac{dN}{d#xi}", 100, 0, 5.5);
   TH1D HJetXi_25_30("HJetXi_25_30", "JetP = 25-30;#xi;#frac{1}{N_{jet}}#frac{dN}{d#xi}", 100, 0, 5.5);
   TH1D HJetXi_30_35("HJetXi_30_35", "JetP = 30-35;#xi;#frac{1}{N_{jet}}#frac{dN}{d#xi}", 100, 0, 5.5);
   TH1D HJetXi_35_40("HJetXi_35_40", "JetP = 35-40;#xi;#frac{1}{N_{jet}}#frac{dN}{d#xi}", 100, 0, 5.5);

   TTree *Tree = (TTree *)InputFile.Get(TreeName.c_str());
   Assert(Tree != nullptr, "Error retrieving input tree");

   int NJet;
   double JetPx[MAX], JetPy[MAX], JetPz[MAX], JetE[MAX];
   double JetElectronFraction[MAX], JetMuonFraction[MAX];
   int JetN[MAX];
   double JetXi[MAX][MAX];

   Tree->SetBranchAddress("NJet", &NJet);
   Tree->SetBranchAddress("JetPx", &JetPx);
   Tree->SetBranchAddress("JetPy", &JetPy);
   Tree->SetBranchAddress("JetPz", &JetPz);
   Tree->SetBranchAddress("JetE", &JetE);
   Tree->SetBranchAddress("JetElectronFraction", &JetElectronFraction);
   Tree->SetBranchAddress("JetMuonFraction", &JetMuonFraction);
   Tree->SetBranchAddress("JetN", &JetN);
   Tree->SetBranchAddress("JetXi", &JetXi);

   double JetCount = 0;
   double JetCount_20_25 = 0;
   double JetCount_25_30 = 0;
   double JetCount_30_35 = 0;
   double JetCount_35_40 = 0;

   int EntryCount = Tree->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      Tree->GetEntry(iE);

      vector<FourVector> Jet;
      vector<bool> PassCut;
      for(int i = 0; i < NJet; i++)
      {
         FourVector P(JetE[i], JetPx[i], JetPy[i], JetPz[i]);
         Jet.push_back(P);

         bool Pass = true;

         if(JetElectronFraction[i] + JetMuonFraction[i] > 2 / P.GetP())
            Pass = false;
         if(P.GetTheta() < 0.2 * M_PI || P.GetTheta() > 0.8 * M_PI)
            Pass = false;

         PassCut.push_back(Pass);
      }

      for(int i = 0; i < NJet; i++)
      {
         if(PassCut[i] == false)
            continue;

         HJetP.Fill(Jet[i].GetP());
         HJetTheta.Fill(Jet[i].GetTheta() / M_PI);

         for(int j = 0; j < JetN[i]; j++)
         {
            if(JetXi[i][j] * Jet[i].GetP() < 0.2)
               continue;

            double Xi = -log(JetXi[i][j]);
            HJetXi.Fill(Xi);
            if(Jet[i].GetP() > 20 && Jet[i].GetP() < 25)   HJetXi_20_25.Fill(Xi);
            if(Jet[i].GetP() > 25 && Jet[i].GetP() < 30)   HJetXi_25_30.Fill(Xi);
            if(Jet[i].GetP() > 30 && Jet[i].GetP() < 35)   HJetXi_30_35.Fill(Xi);
            if(Jet[i].GetP() > 35 && Jet[i].GetP() < 40)   HJetXi_35_40.Fill(Xi);
         }
            
         JetCount = JetCount + 1;
         if(Jet[i].GetP() > 20 && Jet[i].GetP() < 25)      JetCount_20_25 = JetCount_20_25 + 1;
         if(Jet[i].GetP() > 25 && Jet[i].GetP() < 30)      JetCount_25_30 = JetCount_25_30 + 1;
         if(Jet[i].GetP() > 30 && Jet[i].GetP() < 35)      JetCount_30_35 = JetCount_30_35 + 1;
         if(Jet[i].GetP() > 35 && Jet[i].GetP() < 40)      JetCount_35_40 = JetCount_35_40 + 1;
      }
   }

   double BinWidth = double(HJetXi.GetXaxis()->GetBinUpEdge(HJetXi.GetNbinsX()) - 0) / HJetXi.GetNbinsX();

   HJetXi.Scale(1 / JetCount / BinWidth);
   HJetXi_20_25.Scale(1 / JetCount_20_25 / BinWidth);
   HJetXi_25_30.Scale(1 / JetCount_25_30 / BinWidth);
   HJetXi_30_35.Scale(1 / JetCount_30_35 / BinWidth);
   HJetXi_35_40.Scale(1 / JetCount_35_40 / BinWidth);

   HJetP.Write();
   HJetTheta.Write();
   HJetXi.Write();
   HJetXi_20_25.Write();
   HJetXi_25_30.Write();
   HJetXi_30_35.Write();
   HJetXi_35_40.Write();

   OutputFile.Close();
   InputFile.Close();

   return 0;
}



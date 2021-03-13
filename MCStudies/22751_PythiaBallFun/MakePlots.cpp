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

#define MAX 100
#define SDMAX 5

int main(int argc, char *argv[]);

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   string InputFileName  = CL.Get("Input");
   string OutputFileName = CL.Get("Output");
   string TreeName       = CL.Get("Tree", "JetTree");
   bool RequirePythia    = CL.GetBool("RequirePythia", false);

   TFile InputFile(InputFileName.c_str());
   TFile OutputFile(OutputFileName.c_str(), "RECREATE");

   TH1D HJetP("HJetP", "Jet P, theta = 0.2-0.8 pi", 100, 0, 50);
   TH1D HJetTheta("HJetTheta", "Jet theta, theta = 0.2-0.8 pi", 100, 0, 1);
   TH1D HJetXi("HJetXi", ";#xi;#frac{1}{N_{jet}}#frac{dN}{d#xi}", 30, 0, 5.5);
   TH1D HJetXi_20_25("HJetXi_20_25", "JetP = 20-25;#xi;#frac{1}{N_{jet}}#frac{dN}{d#xi}", 30, 0, 5.5);
   TH1D HJetXi_25_30("HJetXi_25_30", "JetP = 25-30;#xi;#frac{1}{N_{jet}}#frac{dN}{d#xi}", 30, 0, 5.5);
   TH1D HJetXi_30_35("HJetXi_30_35", "JetP = 30-35;#xi;#frac{1}{N_{jet}}#frac{dN}{d#xi}", 30, 0, 5.5);
   TH1D HJetXi_35_40("HJetXi_35_40", "JetP = 35-40;#xi;#frac{1}{N_{jet}}#frac{dN}{d#xi}", 30, 0, 5.5);
   TH1D HJetXi_35_37("HJetXi_35_37", "JetP = 35-37;#xi;#frac{1}{N_{jet}}#frac{dN}{d#xi}", 30, 0, 5.5);
   TH1D HJetXi_37_40("HJetXi_37_40", "JetP = 37-40;#xi;#frac{1}{N_{jet}}#frac{dN}{d#xi}", 30, 0, 5.5);
   TH1D HJetSD0ZG_35_40("HJetSD0ZG_35_40", "Jet P = 35-40, SD (0.1, 0.0);ZG;", 25, 0, 0.5);
   TH1D HJetSD0RG_35_40("HJetSD0RG_35_40", "Jet P = 35-40, SD (0.1, 0.0);RG;", 25, 0, 0.4);
   TH1D HJetSD0PF_35_40("HJetSD0PF_35_40", "Jet P = 35-40, SD (0.1, 0.0);Guu P / P;", 25, 0.5, 1.0);
   TH1D HJetSD1ZG_35_40("HJetSD1ZG_35_40", "Jet P = 35-40, SD (0.5, 1.5);ZG;", 25, 0, 0.5);
   TH1D HJetSD1RG_35_40("HJetSD1RG_35_40", "Jet P = 35-40, SD (0.5, 1.5);RG;", 25, 0, 0.4);
   TH1D HJetSD1PF_35_40("HJetSD1PF_35_40", "Jet P = 35-40, SD (0.5, 1.5);Guu P / P;", 25, 0.25, 1.0);

   HJetSD0ZG_35_40.Sumw2();
   HJetSD0RG_35_40.Sumw2();
   HJetSD0PF_35_40.Sumw2();
   HJetSD1ZG_35_40.Sumw2();
   HJetSD1RG_35_40.Sumw2();
   HJetSD1PF_35_40.Sumw2();

   TTree *Tree = (TTree *)InputFile.Get(TreeName.c_str());
   Assert(Tree != nullptr, "Error retrieving input tree");

   int NJet;
   double JetPx[100], JetPy[100], JetPz[100], JetE[100];
   double JetElectronFraction[100], JetMuonFraction[100];
   int JetN[100];
   int JetSubEvent[100][200];
   double JetXi[100][200];
   double JetSDZG[100][5];
   double JetSDRG[100][5];
   double JetSDP[100][5] = {{-1}};
   int JetSDDepth[100][5];

   Tree->SetBranchAddress("NJet", &NJet);
   Tree->SetBranchAddress("JetPx", &JetPx);
   Tree->SetBranchAddress("JetPy", &JetPy);
   Tree->SetBranchAddress("JetPz", &JetPz);
   Tree->SetBranchAddress("JetE", &JetE);
   Tree->SetBranchAddress("JetElectronFraction", &JetElectronFraction);
   Tree->SetBranchAddress("JetMuonFraction", &JetMuonFraction);
   Tree->SetBranchAddress("JetN", &JetN);
   Tree->SetBranchAddress("JetXi", &JetXi);
   Tree->SetBranchAddress("JetSubEvent", &JetSubEvent);
   Tree->SetBranchAddress("JetSDZG", &JetSDZG);
   Tree->SetBranchAddress("JetSDRG", &JetSDRG);
   Tree->SetBranchAddress("JetSDP", &JetSDP);
   Tree->SetBranchAddress("JetSDDepth", &JetSDDepth);

   double JetCount = 0;
   double JetCount_20_25 = 0;
   double JetCount_25_30 = 0;
   double JetCount_30_35 = 0;
   double JetCount_35_40 = 0;
   double JetCount_35_37 = 0;
   double JetCount_37_40 = 0;

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
            if(RequirePythia && JetSubEvent[i][j] == 1)
               continue;

            double Xi = -log(JetXi[i][j]);
            HJetXi.Fill(Xi);
            if(Jet[i].GetP() > 20 && Jet[i].GetP() < 25)   HJetXi_20_25.Fill(Xi);
            if(Jet[i].GetP() > 25 && Jet[i].GetP() < 30)   HJetXi_25_30.Fill(Xi);
            if(Jet[i].GetP() > 30 && Jet[i].GetP() < 35)   HJetXi_30_35.Fill(Xi);
            if(Jet[i].GetP() > 35 && Jet[i].GetP() < 40)   HJetXi_35_40.Fill(Xi);
            if(Jet[i].GetP() > 35 && Jet[i].GetP() < 37)   HJetXi_35_37.Fill(Xi);
            if(Jet[i].GetP() > 37 && Jet[i].GetP() < 40)   HJetXi_37_40.Fill(Xi);
            
            if(Jet[i].GetP() > 35 && Jet[i].GetP() < 40)
            {
               // cout << JetSDP[i][0] << " " << Jet[i].GetP() << endl;

               if(JetSDZG[i][0] > 0)
               {
                  HJetSD0ZG_35_40.Fill(JetSDZG[i][0]);
                  HJetSD0RG_35_40.Fill(JetSDRG[i][0]);
                  HJetSD0PF_35_40.Fill(JetSDP[i][0] / Jet[i].GetP());
               }
               if(JetSDZG[i][1] > 0)
               {
                  HJetSD1ZG_35_40.Fill(JetSDZG[i][1]);
                  HJetSD1RG_35_40.Fill(JetSDRG[i][1]);
                  HJetSD1PF_35_40.Fill(JetSDP[i][1] / Jet[i].GetP());
               }
            }
         }

         JetCount = JetCount + 1;
         if(Jet[i].GetP() > 20 && Jet[i].GetP() < 25)      JetCount_20_25 = JetCount_20_25 + 1;
         if(Jet[i].GetP() > 25 && Jet[i].GetP() < 30)      JetCount_25_30 = JetCount_25_30 + 1;
         if(Jet[i].GetP() > 30 && Jet[i].GetP() < 35)      JetCount_30_35 = JetCount_30_35 + 1;
         if(Jet[i].GetP() > 35 && Jet[i].GetP() < 40)      JetCount_35_40 = JetCount_35_40 + 1;
         if(Jet[i].GetP() > 35 && Jet[i].GetP() < 37)      JetCount_35_37 = JetCount_35_37 + 1;
         if(Jet[i].GetP() > 37 && Jet[i].GetP() < 40)      JetCount_37_40 = JetCount_37_40 + 1;
      }
   }

   double BinWidth = double(HJetXi.GetXaxis()->GetBinUpEdge(HJetXi.GetNbinsX()) - 0) / HJetXi.GetNbinsX();

   HJetXi.Scale(1 / JetCount / BinWidth);
   HJetXi_20_25.Scale(1 / JetCount_20_25 / BinWidth);
   HJetXi_25_30.Scale(1 / JetCount_25_30 / BinWidth);
   HJetXi_30_35.Scale(1 / JetCount_30_35 / BinWidth);
   HJetXi_35_40.Scale(1 / JetCount_35_40 / BinWidth);
   HJetXi_35_37.Scale(1 / JetCount_35_37 / BinWidth);
   HJetXi_37_40.Scale(1 / JetCount_37_40 / BinWidth);

   HJetSD0ZG_35_40.Scale(1 / JetCount_35_40);
   HJetSD0RG_35_40.Scale(1 / JetCount_35_40);
   HJetSD0PF_35_40.Scale(1 / JetCount_35_40);
   HJetSD1ZG_35_40.Scale(1 / JetCount_35_40);
   HJetSD1RG_35_40.Scale(1 / JetCount_35_40);
   HJetSD1PF_35_40.Scale(1 / JetCount_35_40);

   HJetP.Write();
   HJetTheta.Write();
   HJetXi.Write();
   HJetXi_20_25.Write();
   HJetXi_25_30.Write();
   HJetXi_30_35.Write();
   HJetXi_35_40.Write();
   HJetXi_35_37.Write();
   HJetXi_37_40.Write();

   HJetSD0ZG_35_40.Write();
   HJetSD0RG_35_40.Write();
   HJetSD0PF_35_40.Write();
   HJetSD1ZG_35_40.Write();
   HJetSD1RG_35_40.Write();
   HJetSD1PF_35_40.Write();
   
   OutputFile.Close();
   InputFile.Close();

   return 0;
}



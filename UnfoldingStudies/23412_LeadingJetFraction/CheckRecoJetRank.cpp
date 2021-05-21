#include <iostream>
#include <vector>
#include <map>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TH2D.h"

#include "CommandLine.h"
#include "PlotHelper4.h"
#include "SetStyle.h"

int main(int argc, char *argv[]);
void SetAxis(TH2D &H);

int main(int argc, char *argv[])
{
   SetThumbStyle();

   CommandLine CL(argc, argv);

   double Fraction = 1.00;

   TFile File("MC.root");

   TTree *Tree = (TTree *)File.Get("UnfoldingTree");

   vector<float> *GenJetE = nullptr;
   vector<float> *MatchedJetE = nullptr;
   vector<float> *MatchedJetAngle = nullptr;

   Tree->SetBranchAddress("GenJetE", &GenJetE);
   Tree->SetBranchAddress("MatchedJetE", &MatchedJetE);
   Tree->SetBranchAddress("MatchedJetAngle", &MatchedJetAngle);

   int MaxGenRank = 7, MaxRecoRank = 7;
   TH2D HCounts("HCounts", "Counts;Reco Jet Rank;Gen Jet Rank", MaxRecoRank, 0, MaxRecoRank, MaxGenRank, 0, MaxGenRank);
   SetAxis(HCounts);

   int EntryCount = Tree->GetEntries() * Fraction;
   for(int iE = 0; iE < EntryCount; iE++)
   {
      Tree->GetEntry(iE);

      int NJet = GenJetE->size();

      vector<pair<double, int>> MatchedJetSorting;
      for(int iJ = 0; iJ < NJet; iJ++)
      {
         if((*MatchedJetAngle)[iJ] > 0 && (*MatchedJetAngle)[iJ] < 0.2)
            MatchedJetSorting.push_back(pair<double, int>(-(*MatchedJetE)[iJ], iJ));
         else
            MatchedJetSorting.push_back(pair<double, int>(0, iJ));
      }
      sort(MatchedJetSorting.begin(), MatchedJetSorting.end());

      vector<int> MatchedJetRanks(NJet);
      for(int i = 0; i < (int)MatchedJetSorting.size(); i++)
         MatchedJetRanks[MatchedJetSorting[i].second] = i;

      for(int iJ = 0; iJ < NJet && iJ < MaxGenRank; iJ++)
      {
         int GenRank = iJ;

         int RecoRank = MatchedJetRanks[iJ];
         if(RecoRank >= MaxRecoRank)
            RecoRank = MaxRecoRank;

         if(GenRank == 3 && RecoRank == 0)
         {
            cout << "Gen";
            for(int i = 0; i < NJet; i++)
               cout << " " << (*GenJetE)[i];
            cout << endl;
            cout << "Matched";
            for(int i = 0; i < NJet; i++)
               cout << " " << (*MatchedJetE)[i];
            cout << endl;
            cout << "Matched angle";
            for(int i = 0; i < NJet; i++)
               cout << " " << (*MatchedJetAngle)[i];
            cout << endl;
            cout << "Matched rank";
            for(int i = 0; i < NJet; i++)
               cout << " " << MatchedJetRanks[i];
            cout << endl;
            cout << endl;
         }

         HCounts.Fill(RecoRank, GenRank);
      }
   }

   TH2D HRowNormalize("HRowNormalize", "Row-normalized;Reco Jet Rank;Gen Jet Rank", MaxRecoRank, 0, MaxRecoRank, MaxGenRank, 0, MaxGenRank);
   SetAxis(HRowNormalize);
   HRowNormalize.Fill(0.0, 0.0, 0.0);

   for(int iY = 1; iY <= HCounts.GetNbinsY(); iY++)
   {
      double Total = 0;
      for(int iX = 1; iX <= HCounts.GetNbinsX(); iX++)
         Total = Total + HCounts.GetBinContent(iX, iY);
      for(int iX = 1; iX <= HCounts.GetNbinsX(); iX++)
         HRowNormalize.SetBinContent(iX, iY, HCounts.GetBinContent(iX, iY) / Total);
   }
   
   TH2D HColumnNormalize("HColumnNormalize", "Column-normalized;Reco Jet Rank;Gen Jet Rank", MaxRecoRank, 0, MaxRecoRank, MaxGenRank, 0, MaxGenRank);
   SetAxis(HColumnNormalize);
   HColumnNormalize.Fill(0.0, 0.0, 0.0);
   
   for(int iX = 1; iX <= HCounts.GetNbinsX(); iX++)
   {
      double Total = 0;
      for(int iY = 1; iY <= HCounts.GetNbinsY(); iY++)
         Total = Total + HCounts.GetBinContent(iX, iY);
      for(int iY = 1; iY <= HCounts.GetNbinsY(); iY++)
         HColumnNormalize.SetBinContent(iX, iY, HCounts.GetBinContent(iX, iY) / Total);
   }

   PdfFileHelper PdfFile("Ranking.pdf");
   PdfFile.AddTextPage("Jet ranking");

   PdfFile.AddPlot(HCounts, "col text00");
   PdfFile.AddPlot(HRowNormalize, "col text00");
   PdfFile.AddPlot(HColumnNormalize, "col text00");

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   File.Close();

   return 0;
}

void SetAxis(TH2D &H)
{
   H.SetStats(0);

   for(int i = 1; i <= H.GetNbinsX(); i++)
   {
      if(i != H.GetNbinsX())
         H.GetXaxis()->SetBinLabel(i, Form("%d", i));
      else
         H.GetXaxis()->SetBinLabel(i, Form("#geq %d", i));
   }
   for(int i = 1; i <= H.GetNbinsY(); i++)
      H.GetYaxis()->SetBinLabel(i, Form("%d", i));
}



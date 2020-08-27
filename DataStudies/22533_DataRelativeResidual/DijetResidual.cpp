#include <iostream>
#include <map>
using namespace std;

#include "TCanvas.h"
#include "TGraph.h"
#include "TTree.h"
#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"

#include "CommandLine.h"
#include "Code/TauHelperFunctions3.h"
#include "SetStyle.h"
#include "PlotHelper4.h"
#include "DataHelper.h"

#define MAX 200

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   string FileName    = CL.Get("File");
   double P3Cut       = CL.GetDouble("P3Cut", 5);
   string PdfFileName = CL.Get("PdfFile", "CheckDijet.pdf");
   string DHFileName  = CL.Get("DHFile", "DijetResult.dh");
   string State       = CL.Get("State", "DefaultState");

   // int NBins = 12;
   // double Bin[] = {0.5, 0.525, 0.55, 0.575, 0.6, 0.625, 0.65, 0.675, 0.7, 0.725, 0.75, 0.775, 0.80};
   int NBins = 6;
   double Bin[] = {0.5, 0.55, 0.6, 0.65, 0.7, 0.75, 0.80};

   PdfFileHelper PdfFile(PdfFileName);
   PdfFile.AddTextPage("Check dijet residual");

   DataHelper DHFile(DHFileName);

   vector<vector<pair<double, double>>> JetPair(NBins);

   TFile File(FileName.c_str());

   TTree *Tree = (TTree *)File.Get("Tree");

   int N;
   float JetPT[MAX], JetEta[MAX], JetTheta[MAX], JetPhi[MAX], JetM[MAX];
   Tree->SetBranchAddress("N",        &N);
   Tree->SetBranchAddress("JetPT",    &JetPT);
   Tree->SetBranchAddress("JetEta",   &JetEta);
   Tree->SetBranchAddress("JetTheta", &JetTheta);
   Tree->SetBranchAddress("JetPhi",   &JetPhi);
   Tree->SetBranchAddress("JetM",     &JetM);

   int EntryCount = Tree->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      Tree->GetEntry(iE);

      if(N < 2)   // no jet, or monojet - not our concern here!
         continue;
      
      map<double, FourVector, greater<double>> Jets;

      for(int i = 0; i < N; i++)
      {
         FourVector J;
         J.SetPtEtaPhiMass(JetPT[i], JetEta[i], JetPhi[i], JetM[i]);

         Jets.insert(pair<double, FourVector>(J.GetP(), J));
      }

      double J1P, J2P, J3P = 0;
      FourVector J1, J2;
      
      {
         auto iter = Jets.begin();
         J1P = iter->first;
         J1 = iter->second;
         iter++;
         J2P = iter->first;
         J2 = iter->second;
         if(N > 2)
         {
            iter++;
            J3P = iter->first;
         }
      }

      if(J3P > P3Cut)   // remove events with significant third jet
         continue;

      FourVector JP, JM;
      if(J1.GetTheta() > J2.GetTheta())
         JP = J1, JM = J2;
      else
         JP = J2, JM = J1;

      for(int i = 0; i < NBins; i++)
      {
         if(JP.GetTheta() <= Bin[i] * M_PI || JP.GetTheta() > Bin[i+1] * M_PI)
            continue;
         if(JM.GetTheta() <= (1 - Bin[i+1]) * M_PI || JM.GetTheta() > (1 - Bin[i]) * M_PI)
            continue;

         JetPair[i].push_back(pair<double, double>(JP.GetP(), JM.GetP()));
         break;
      }
   }

   File.Close();

   TH1D HNJet("HNJet", ";#theta (#pi);Count", NBins, Bin);
   HNJet.SetStats(0);
   for(int i = 0; i < NBins; i++)
      HNJet.SetBinContent(i + 1, JetPair[i].size());
   PdfFile.AddPlot(HNJet, "hist text00");

   TH1D HPMRatio("HPMRatio", ";#theta (#pi);P+/P-", NBins, Bin);
   HPMRatio.SetStats(0);

   DHFile[State]["NBins"] = NBins;

   for(int iB = 0; iB < NBins; iB++)
   {
      PdfFile.AddTextPage(Form("Bin: %.3f-%.3f #pi", Bin[iB], Bin[iB+1]));

      TH1D HP("HP", "Blue (+), Red (-);Jet P;", 100, 0, 100);
      TH1D HM("HM", "Blue (+), Red (-);Jet P;", 100, 0, 100);

      HP.SetStats(0);
      HM.SetStats(0);

      for(int i = 0; i < (int)JetPair[iB].size(); i++)
      {
         HP.Fill(JetPair[iB][i].first);
         HM.Fill(JetPair[iB][i].second);
      }

      HP.SetLineColor(kBlue);
      HM.SetLineColor(kRed);

      TCanvas Canvas;
      HP.Draw();
      HM.Draw("same");
      PdfFile.AddCanvas(Canvas);

      double PMRatio = HP.GetMean() / HM.GetMean();
      double PError = HP.GetMeanError() / HP.GetMean();
      double MError = HM.GetMeanError() / HM.GetMean();
      double PMError = PMRatio * sqrt(PError * PError + MError * MError);
      HPMRatio.SetBinContent(iB + 1, PMRatio);
      HPMRatio.SetBinError(iB + 1, PMError);

      DHFile[State][Form("B%dMin",iB)] = Bin[iB];
      DHFile[State][Form("B%dMax",iB)] = Bin[iB+1];
      DHFile[State][Form("B%dPMR",iB)] = PMRatio;
      DHFile[State][Form("B%dPME",iB)] = PMError;
      DHFile[State][Form("B%dP",iB)]   = HP.GetMean();
      DHFile[State][Form("B%dPE",iB)]  = HP.GetMeanError();
      DHFile[State][Form("B%dM",iB)]   = HP.GetMean();
      DHFile[State][Form("B%dME",iB)]  = HP.GetMeanError();
      DHFile[State][Form("B%dN",iB)]   = (int)JetPair[iB].size();
   }

   DHFile.SaveToFile(DHFileName);

   PdfFile.AddTextPage("Summary plots");

   TGraph GLine;
   GLine.SetPoint(0, 0, 1);
   GLine.SetPoint(1, 10000, 1);

   TCanvas Canvas;
   TH2D HWorld("HWorld", ";#theta (#pi);<P+>/<P->", NBins, Bin, 100, 0.98, 1.02);
   HWorld.SetStats(0);
   HWorld.Draw("axis");
   HPMRatio.Draw("same");
   GLine.Draw("l");
   PdfFile.AddCanvas(Canvas);

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}





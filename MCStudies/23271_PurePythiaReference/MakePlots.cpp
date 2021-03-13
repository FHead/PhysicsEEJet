#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

#include "TFile.h"
#include "TTree.h"

#include "CommandLine.h"
#include "SetStyle.h"
#include "PlotHelper4.h"

#define TYPE_ZG 0
#define TYPE_DR 1
#define TYPE_PP 2

struct Configuration;
int main(int argc, char *argv[]);

struct Configuration
{
   string Label;
   int Bin;
   double Min;
   double Max;
   bool IsMoment;
   int Index;
   int Type;
};

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   vector<string> Inputs = CL.GetStringVector("input");
   vector<string> Labels = CL.GetStringVector("label");
   string Output         = CL.Get("output", "Plots.pdf");
   double MinTheta       = CL.GetDouble("mintheta", 0.25 * M_PI);

   int NF = Inputs.size();
   if(Labels.size() < NF)
      Labels.insert(Labels.end(), NF - (int)Labels.size(), "No label");

   vector<Configuration> Configurations;
   Configurations.push_back({"Moment (0, 0)",  60, 0,   60,   true,  0,  -1});
   Configurations.push_back({"Moment (1, 0)",  25, 0,   10,   true,  1,  -1});
   Configurations.push_back({"Moment (2, 0)",  25, 0,   5,    true,  2,  -1});
   Configurations.push_back({"Moment (3, 0)",  25, 0,   3.5,  true,  3,  -1});
   // Configurations.push_back({"Moment (0, 1)",  25, 1,   1.08, true,  4,  -1});
   Configurations.push_back({"Moment (1, 1)",  25, 0,   1.2,  true,  5,  -1});
   Configurations.push_back({"Moment (2, 1)",  25, 0,   0.3,  true,  6,  -1});
   Configurations.push_back({"Moment (3, 1)",  25, 0,   0.15, true,  7,  -1});
   Configurations.push_back({"Moment (0, -1)", 25, 0,   600,  true,  8,  -1});
   Configurations.push_back({"Moment (1, -1)", 25, 0,   200,  true,  9,  -1});
   Configurations.push_back({"Moment (2, -1)", 25, 0,   120,  true,  10, -1});
   Configurations.push_back({"Moment (3, -1)", 25, 0,   90,   true,  11, -1});
   Configurations.push_back({"Moment (5, 0)",  25, 0,   1,    true,  12, -1});
   Configurations.push_back({"Moment (5, 1)",  25, 0,   0.05, true,  13, -1});
   Configurations.push_back({"Moment (5, -1)", 25, 0,   25,   true,  14, -1});
   Configurations.push_back({"ZG (0.0, 0.1)",  25, 0.1, 0.5,  false, 0,  TYPE_ZG});
   Configurations.push_back({"DR (0.0, 0.1)",  25, 0.0, 0.5,  false, 0,  TYPE_DR});
   Configurations.push_back({"ZG (0.5, 1.5)",  25, 0.0, 0.5,  false, 1,  TYPE_ZG});
   Configurations.push_back({"DR (0.5, 1.5)",  25, 0.0, 0.5,  false, 1,  TYPE_DR});
   int NC = Configurations.size();

   vector<vector<TH1D>> HJ1(NC);
   vector<vector<TH1D>> HJ2(NC);
   for(int iC = 0; iC < NC; iC++)
   {
      Configuration &C = Configurations[iC];

      for(int iF = 0; iF < NF; iF++)
      {
         HJ1[iC].emplace_back(TH1D(Form("HJ1_%d_%d", iC, iF), "", C.Bin, C.Min, C.Max));
         // HJ1[iC][iF].SetTitle(Labels[iF].c_str());
         HJ1[iC][iF].GetXaxis()->SetTitle(C.Label.c_str());
         HJ2[iC].emplace_back(TH1D(Form("HJ2_%d_%d", iC, iF), "", C.Bin, C.Min, C.Max));
         // HJ2[iC][iF].SetTitle(Labels[iF].c_str());
         HJ2[iC][iF].GetXaxis()->SetTitle(C.Label.c_str());
      }
   }

   for(int iF = 0; iF < NF; iF++)
   {
      TFile File(Inputs[iF].c_str());

      TTree *Tree = (TTree *)File.Get("Tree");
      if(Tree == nullptr)
         continue;

      double J1P, J1Theta, J1Phi;
      double J2P, J2Theta, J2Phi;
      int NMoment;
      double Alpha[100], Beta[100];
      double J1M[100], J2M[100];
      int NSD;
      double SDZCut[100], SDBeta[100];
      double J1SDZG[100], J2SDZG[100];
      double J1SDDR[100], J2SDDR[100];
      int EventType = 0;

      Tree->SetBranchAddress("J1P", &J1P);
      Tree->SetBranchAddress("J1Theta", &J1Theta);
      Tree->SetBranchAddress("J1Phi", &J1Phi);
      Tree->SetBranchAddress("J2P", &J2P);
      Tree->SetBranchAddress("J2Theta", &J2Theta);
      Tree->SetBranchAddress("J2Phi", &J2Phi);
      Tree->SetBranchAddress("NMoment", &NMoment);
      Tree->SetBranchAddress("Alpha", &Alpha);
      Tree->SetBranchAddress("Beta", &Beta);
      Tree->SetBranchAddress("J1M", &J1M);
      Tree->SetBranchAddress("J2M", &J2M);
      Tree->SetBranchAddress("NSD", &NSD);
      Tree->SetBranchAddress("SDZCut", &SDZCut);
      Tree->SetBranchAddress("SDBeta", &SDBeta);
      Tree->SetBranchAddress("J1SDZG", &J1SDZG);
      Tree->SetBranchAddress("J2SDZG", &J2SDZG);
      Tree->SetBranchAddress("J1SDDR", &J1SDDR);
      Tree->SetBranchAddress("J2SDDR", &J2SDDR);
      Tree->SetBranchAddress("EventType", &EventType);

      int EntryCount = Tree->GetEntries();
      for(int iE = 0; iE < EntryCount; iE++)
      {
         Tree->GetEntry(iE);

         if(EventType == 1)   // tau-tau
            continue;
         if(EventType == 2)   // tau somewhere
            continue;

         // if(J1M[0] < 6)
         //    continue;

         for(int iC = 0; iC < NC; iC++)
         {
            Configuration &C = Configurations[iC];

            double M1 = -1;
            if(C.IsMoment == true && C.Index < NMoment && C.Index >= 0)
               M1 = J1M[C.Index];
            if(C.IsMoment == false && C.Index < NSD && C.Index >= 0)
            {
               if(C.Type == TYPE_ZG)   M1 = J1SDZG[C.Index];
               if(C.Type == TYPE_DR)   M1 = J1SDDR[C.Index];
            }

            double M2 = -1;
            if(C.IsMoment == true && C.Index < NMoment && C.Index >= 0)
               M2 = J2M[C.Index];
            if(C.IsMoment == false && C.Index < NSD && C.Index >= 0)
            {
               if(C.Type == TYPE_ZG)   M2 = J2SDZG[C.Index];
               if(C.Type == TYPE_DR)   M2 = J2SDDR[C.Index];
            }

            if(J1Theta > MinTheta && J1Theta < M_PI - MinTheta)    HJ1[iC][iF].Fill(M1);
            if(J2Theta > MinTheta && J2Theta < M_PI - MinTheta)    HJ2[iC][iF].Fill(M1);
         }
      }

      File.Close();
   }

   PdfFileHelper PdfFile(Output);
   PdfFile.AddTextPage("Jet plots");

   int Color[] = {kBlack, kRed, kBlue, kGreen + 3, kMagenta};

   for(int iC = 0; iC < NC; iC++)
   {
      TCanvas Canvas;

      for(int iF = 0; iF < NF; iF++)
      {
         HJ1[iC][iF].SetStats(0);
         HJ1[iC][iF].SetLineColor(Color[iF]);
         HJ1[iC][iF].SetMinimum(0);

         if(iF == 0)
            HJ1[iC][iF].Draw();
         else
            HJ1[iC][iF].Draw("same");
      }

      PdfFile.AddCanvas(Canvas);

      for(int iF = 0; iF < NF; iF++)
      {
         HJ1[iC][iF].SetStats(0);
         HJ1[iC][iF].SetLineColor(Color[iF]);
         HJ1[iC][iF].SetMinimum(HJ1[iC][iF].GetMaximum() * 0.0001);

         if(iF == 0)
            HJ1[iC][iF].Draw();
         else
            HJ1[iC][iF].Draw("same");
      }

      Canvas.SetLogy();
      PdfFile.AddCanvas(Canvas);
   }

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}





#include <iostream>
#include <vector>
using namespace std;

#include "TH2D.h"
#include "TH1D.h"
#include "TCanvas.h"

#include "CommandLine.h"
#include "PlotHelper4.h"
#include "SetStyle.h"

#define TYPE_ZG 0
#define TYPE_DR 1
#define TYPE_PP 2

struct Configuration;
int main(int argc, char *argv[]);
void PlotCorrelations(PdfFileHelper &PdfFile, string FileName,
   vector<Configuration> Configurations, double MinTheta, double MinP, vector<vector<TH2D *>> HM12Corr);
double GetPullRMS(TH2D *H);

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

   string InputData = CL.Get("data");
   string InputMC   = CL.Get("mc");
   string Output    = CL.Get("output");

   PdfFileHelper PdfFile(Output);
   PdfFile.AddTextPage("Correlation plots");

   vector<Configuration> Configurations;
   Configurations.push_back({"Moment (0, 0)",  30, 0,   30,   true,  0,  -1});
   Configurations.push_back({"Moment (1, 0)",  25, 0,   10,   true,  1,  -1});
   Configurations.push_back({"Moment (2, 0)",  25, 0,   5,    true,  2,  -1});
   Configurations.push_back({"Moment (3, 0)",  25, 0,   3.5,  true,  3,  -1});
   // Configurations.push_back({"Moment (0, 1)",  25, 1,   1.08, true,  4,  -1});
   Configurations.push_back({"Moment (1, 1)",  25, 0,   0.5,  true,  5,  -1});
   Configurations.push_back({"Moment (2, 1)",  25, 0,   0.3,  true,  6,  -1});
   Configurations.push_back({"Moment (3, 1)",  25, 0,   0.15, true,  7,  -1});
   Configurations.push_back({"Moment (0, -1)", 10, 0,   200,  true,  8,  -1});
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
   int N = Configurations.size();

   vector<vector<TH2D *>> HM12CorrData(Configurations.size()), HM12CorrMC(Configurations.size());
   vector<vector<TH2D *>> HM12CorrRatio(Configurations.size());

   for(int i1 = 0; i1 < (int)Configurations.size(); i1++)
   {
      HM12CorrData[i1].resize(Configurations.size(), nullptr);
      HM12CorrMC[i1].resize(Configurations.size(), nullptr);
      HM12CorrRatio[i1].resize(Configurations.size(), nullptr);

      for(int i2 = 0; i2 < (int)Configurations.size(); i2++)
      {
         Configuration &C1 = Configurations[i1];
         Configuration &C2 = Configurations[i2];

         HM12CorrData[i1][i2] = new TH2D(Form("HM12CorrData_%d_%d", i1, i2),
            Form("Data;J1 %s;J2 %s", C1.Label.c_str(), C2.Label.c_str()),
            C1.Bin, C1.Min, C1.Max, C2.Bin, C2.Min, C2.Max);
         HM12CorrMC[i1][i2] = new TH2D(Form("HM12CorrMC_%d_%d", i1, i2),
            Form("MC;J1 %s;J2 %s", C1.Label.c_str(), C2.Label.c_str()),
            C1.Bin, C1.Min, C1.Max, C2.Bin, C2.Min, C2.Max);
         HM12CorrRatio[i1][i2] = new TH2D(Form("HM12CorrRatio_%d_%d", i1, i2),
            Form("Ratio;J1 %s;J2 %s", C1.Label.c_str(), C2.Label.c_str()),
            C1.Bin, C1.Min, C1.Max, C2.Bin, C2.Min, C2.Max);
      }
   }

   PlotCorrelations(PdfFile, InputData, Configurations, 0.25 * M_PI, 30, HM12CorrData);
   PlotCorrelations(PdfFile, InputMC, Configurations, 0.25 * M_PI, 30, HM12CorrMC);

   PdfFile.AddTextPage("Data/MC ratios");

   for(int i = 0; i < N; i++)
   {
      for(int j = 0; j < N; j++)
      {
         for(int i1 = 1; i1 <= HM12CorrData[i][j]->GetNbinsX(); i1++)
         {
            for(int i2 = 1; i2 <= HM12CorrData[i][j]->GetNbinsY(); i2++)
            {
               double V1 = HM12CorrData[i][j]->GetBinContent(i1, i2);
               double V2 = HM12CorrMC[i][j]->GetBinContent(i1, i2);
               double E1 = HM12CorrData[i][j]->GetBinError(i1, i2);
               double E2 = HM12CorrMC[i][j]->GetBinError(i1, i2);

               double RE1 = E1 / V1;
               double RE2 = E2 / V2;
               double RE = sqrt(RE1 * RE1 + RE2 * RE2);

               double V = V1 / V2;
               double E = V * RE;

               HM12CorrRatio[i][j]->SetBinContent(i1, i2, V);
               HM12CorrRatio[i][j]->SetBinError(i1, i2, E);
            }
         }

         HM12CorrRatio[i][j]->SetStats(0);
         HM12CorrRatio[i][j]->SetMinimum(0);
         HM12CorrRatio[i][j]->SetMaximum(2);
         PdfFile.AddPlot(HM12CorrRatio[i][j], "colz");
      }
   }

   TH2D HPullRMSMC("HPullRMSMC", "MC Pull RMS;;", N, 0, N, N, 0, N);
   TH2D HPullRMSData("HPullRMSData", "Data Pull RMS;;", N, 0, N, N, 0, N);
   TH2D HPullRMSRatio("HPullRMSRatio", "Ratio Pull RMS;;", N, 0, N, N, 0, N);
   for(int i = 1; i <= N; i++)
   {
      HPullRMSMC.GetXaxis()->SetBinLabel(i, Configurations[i-1].Label.c_str());
      HPullRMSMC.GetYaxis()->SetBinLabel(i, Configurations[i-1].Label.c_str());
      HPullRMSData.GetXaxis()->SetBinLabel(i, Configurations[i-1].Label.c_str());
      HPullRMSData.GetYaxis()->SetBinLabel(i, Configurations[i-1].Label.c_str());
      HPullRMSRatio.GetXaxis()->SetBinLabel(i, Configurations[i-1].Label.c_str());
      HPullRMSRatio.GetYaxis()->SetBinLabel(i, Configurations[i-1].Label.c_str());
   }

   for(int i = 1; i <= N; i++)
   {
      for(int j = 1; j <= N; j++)
      {
         HPullRMSMC.SetBinContent(i, j, GetPullRMS(HM12CorrMC[i-1][j-1]));
         HPullRMSData.SetBinContent(i, j, GetPullRMS(HM12CorrData[i-1][j-1]));
         HPullRMSRatio.SetBinContent(i, j, GetPullRMS(HM12CorrRatio[i-1][j-1]));
      }
   }
   HPullRMSMC.SetStats(0);
   HPullRMSData.SetStats(0);
   HPullRMSRatio.SetStats(0);

   HPullRMSMC.SetMinimum(0.0);
   HPullRMSMC.SetMaximum(2.0);
   HPullRMSData.SetMinimum(0.0);
   HPullRMSData.SetMaximum(2.0);
   HPullRMSRatio.SetMinimum(0.0);
   HPullRMSRatio.SetMaximum(2.0);

   PdfFile.AddTextPage("Summary plots");

   PdfFile.AddPlot(HPullRMSMC, "colz");
   PdfFile.AddPlot(HPullRMSData, "colz");
   PdfFile.AddPlot(HPullRMSRatio, "colz");

   for(auto v : HM12CorrData)
      for(auto h : v)
         if(h != nullptr)
            delete h;
   for(auto v : HM12CorrMC)
      for(auto h : v)
         if(h != nullptr)
            delete h;
   for(auto v : HM12CorrRatio)
      for(auto h : v)
         if(h != nullptr)
            delete h;

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

void PlotCorrelations(PdfFileHelper &PdfFile, string FileName,
   vector<Configuration> Configurations, double MinTheta, double MinP, vector<vector<TH2D *>> HM12Corr)
{
   TFile File(FileName.c_str());

   TTree *Tree = (TTree *)File.Get("Tree");
   if(Tree == nullptr)
      return;

   double J1P, J1Theta, J1Phi;
   double J2P, J2Theta, J2Phi;
   int NMoment;
   double Alpha[100], Beta[100];
   double J1M[100], J2M[100];
   int NSD;
   double SDZCut[100], SDBeta[100];
   double J1SDZG[100], J2SDZG[100];
   double J1SDDR[100], J2SDDR[100];

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

   TH1D HTheta1("HTheta1", ";#theta_{1};", 100, 0, M_PI);
   TH1D HTheta2("HTheta2", ";#theta_{2};", 100, 0, M_PI);
   TH2D HTheta12("HTheta12", ";#theta_{1};#theta_{2}", 100, 0, M_PI, 100, 0, M_PI);
   TH2D HPhi12("HPhi12", ";#Phi_{1};#Phi_{2}", 100, -M_PI, M_PI, 100, -M_PI, M_PI);
   
   int N = Configurations.size();
   vector<TH1D *> HM1(N);
   vector<TH1D *> HM2(N);
   vector<vector<TH2D *>> HM12(N);
   vector<vector<TH2D *>> HM12CorrPull(N);

   for(int i = 0; i < N; i++)
   {
      Configuration &C1 = Configurations[i];
      HM1[i] = new TH1D(Form("HM1_%d", i), Form(";Jet 1 %s;", C1.Label.c_str()), C1.Bin, C1.Min, C1.Max);
      HM2[i] = new TH1D(Form("HM2_%d", i), Form(";Jet 2 %s;", C1.Label.c_str()), C1.Bin, C1.Min, C1.Max);

      HM12[i].resize(N, nullptr);
      HM12CorrPull[i].resize(N, nullptr);

      for(int j = 0; j < N; j++)
      {
         Configuration &C2 = Configurations[j];
         HM12[i][j] = new TH2D(Form("HM12_%d_%d", i, j),
            Form(";Jet 1 %s;Jet 2 %s", C1.Label.c_str(), C2.Label.c_str()),
            C1.Bin, C1.Min, C1.Max, C2.Bin, C2.Min, C2.Max);
         HM12CorrPull[i][j] = new TH2D(Form("HM12CorrPull_%d_%d", i, j),
            Form("Pull;Jet 1 %s;Jet 2 %s", C1.Label.c_str(), C2.Label.c_str()),
            C1.Bin, C1.Min, C1.Max, C2.Bin, C2.Min, C2.Max);
      }
   }

   int EntryCount = Tree->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      Tree->GetEntry(iE);

      if(J1Theta < MinTheta)          continue;
      if(J1Theta > M_PI - MinTheta)   continue;
      if(J2Theta < MinTheta)          continue;
      if(J2Theta > M_PI - MinTheta)   continue;

      if(J1P < MinP)   continue;
      if(J2P < MinP)   continue;
      if(J1P > 42.5)   continue;
      if(J2P > 42.5)   continue;

      HTheta1.Fill(J1Theta);
      HTheta2.Fill(J2Theta);
      HTheta12.Fill(J1Theta, J2Theta);
      HPhi12.Fill(J1Phi, J2Phi);
      
      for(int i = 0; i < N; i++)
      {
         Configuration &C1 = Configurations[i];

         double M1 = -1;
         if(C1.IsMoment == true && C1.Index < NMoment && C1.Index >= 0)
             M1 = J1M[C1.Index];
         if(C1.IsMoment == false && C1.Index < NSD && C1.Index >= 0)
         {
            if(C1.Type == TYPE_ZG)   M1 = J1SDZG[C1.Index];
            if(C1.Type == TYPE_DR)   M1 = J1SDDR[C1.Index];
         }
      
         for(int j = 0; j < N; j++)
         {
            Configuration &C2 = Configurations[j];

            double M2 = -1;
            if(C2.IsMoment == true && C2.Index < NMoment && C2.Index >= 0)
               M2 = J2M[C2.Index];
            if(C2.IsMoment == false && C2.Index < NSD && C2.Index >= 0)
            {
               if(C2.Type == TYPE_ZG)   M2 = J2SDZG[C2.Index];
               if(C2.Type == TYPE_DR)   M2 = J2SDDR[C2.Index];
            }

            if(j == 0)
               HM1[i]->Fill(M1);
            if(i == 0)
               HM2[j]->Fill(M2);
            HM12[i][j]->Fill(M1, M2);
         }
      }
   }

   PdfFile.AddTextPage("File: " + FileName);
   PdfFile.AddPlot(HTheta1);
   PdfFile.AddPlot(HTheta2);
   PdfFile.AddPlot(HTheta12, "colz");
   PdfFile.AddPlot(HPhi12, "colz");
   
   for(int i = 0; i < N; i++)
   {
      for(int j = 0; j < N; j++)
      {
         Configuration &C1 = Configurations[i];
         Configuration &C2 = Configurations[j];

         for(int i1 = 1; i1 <= C1.Bin; i1++)
         {
            for(int i2 = 1; i2 <= C2.Bin; i2++)
            {
               double M1 = HM1[i]->GetBinContent(i1);
               double M2 = HM2[j]->GetBinContent(i2);
               double M12 = HM12[i][j]->GetBinContent(i1, i2);
               double E1 = HM1[i]->GetBinError(i1);
               double E2 = HM2[j]->GetBinError(i2);
               double E12 = HM12[i][j]->GetBinError(i1, i2);
               if(M1 > 1e-10 && M2 > 1e-10)
               {
                  double Corr = M12 / M1 / M2;
                  double RE1 = E1 / M1;
                  double RE2 = E2 / M2;
                  double RE12 = E12 / M12;
                  double RE = sqrt(RE1 * RE1 + RE2 * RE2 + RE12 * RE12);
                  double Error = RE * Corr;

                  HM12Corr[i][j]->SetBinContent(i1, i2, Corr);
                  HM12Corr[i][j]->SetBinError(i1, i2, Error);
                  HM12CorrPull[i][j]->SetBinContent(i1, i2, (Corr - HM1[i]->GetEntries()) / Error);
               }
            }
         }
         HM12Corr[i][j]->Scale(HM1[i]->GetEntries());
         HM12Corr[i][j]->SetMinimum(0.0);
         HM12Corr[i][j]->SetMaximum(2.0);
 
         for(int i1 = 1; i1 <= C1.Bin; i1++)
         {
            for(int i2 = 1; i2 <= C2.Bin; i2++)
            {
               double V = HM12Corr[i][j]->GetBinContent(i1, i2);
               double E = HM12Corr[i][j]->GetBinError(i1, i2);
               if(V > 0 && E > 1e-10)
                  HM12CorrPull[i][j]->SetBinContent(i1, i2, (V - 1) / E);
            }
         }

         HM12[i][j]->SetStats(0);
         HM12Corr[i][j]->SetStats(0);
         HM12CorrPull[i][j]->SetStats(0);
         
         HM12CorrPull[i][j]->SetMinimum(-3);
         HM12CorrPull[i][j]->SetMaximum(3);

         // PdfFile.AddTextPage({"Correlations", "Jet 1: " + C1.Label, "Jet 2: " + C2.Label});
         // PdfFile.AddPlot(HM1[i]);
         // PdfFile.AddPlot(HM2[j]);
         // PdfFile.AddPlot(HM12[i][j], "colz");
         // PdfFile.AddPlot(HM12[i][j], "colz", false, true);
         PdfFile.AddPlot(HM12Corr[i][j], "colz");
         PdfFile.AddPlot(HM12CorrPull[i][j], "colz");
      }
   }

   // PS: no need to delete the histograms, they should be cleaned up with the file closing

   File.Close();
}

double GetPullRMS(TH2D *H)
{
   if(H == nullptr)
      return 0;

   vector<double> Pull;

   for(int i = 1; i <= H->GetNbinsX(); i++)
   {
      for(int j = 1; j <= H->GetNbinsY(); j++)
      {
         double V = H->GetBinContent(i, j);
         double E = H->GetBinError(i, j);

         if(E > 1e-10 && V > 0)
            Pull.push_back((V - 1) / E);
      }
   }

   double Sum0 = 0;
   double Sum1 = 0;
   double Sum2 = 0;

   for(double X : Pull)
   {
      Sum0 = Sum0 + 1;
      Sum1 = Sum1 + X;
      Sum2 = Sum2 + X * X;
   }

   if(Sum0 == 0)
      return 0;
   
   cout << Sum0 << " " << Sum1 << " " <<Sum2 << endl;

   return sqrt((Sum2 - Sum1 * Sum1 / Sum0) / Sum0);
}



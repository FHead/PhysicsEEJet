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
void PlotCorrelation(PdfFileHelper &PdfFile, string FileNameMC, string FileNameData,
   Configuration C1, Configuration C2, double MinTheta, double MinP);
void PlotCorrelation(PdfFileHelper &PdfFile, string FileName,
   Configuration C1, Configuration C2, double MinTheta, double MinP, TH2D &HM12Corr);

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
   Configurations.push_back({"Moment 0 0",    30, 0,   30,   true,  0,  -1});
   Configurations.push_back({"Moment 1 0",    25, 0,   10,   true,  1,  -1});
   Configurations.push_back({"Moment 2 0",    25, 0,   5,    true,  2,  -1});
   Configurations.push_back({"Moment 3 0",    25, 0,   3.5,  true,  3,  -1});
   Configurations.push_back({"Moment 0 1",    25, 1,   1.08, true,  4,  -1});
   Configurations.push_back({"Moment 1 1",    25, 0,   0.5,  true,  5,  -1});
   Configurations.push_back({"Moment 2 1",    25, 0,   0.3,  true,  6,  -1});
   Configurations.push_back({"Moment 3 1",    25, 0,   0.15, true,  7,  -1});
   Configurations.push_back({"Moment 0 -1",   10, 0,   200,  true,  8,  -1});
   Configurations.push_back({"Moment 1 -1",   25, 0,   200,  true,  9,  -1});
   Configurations.push_back({"Moment 2 -1",   25, 0,   120,  true,  10, -1});
   Configurations.push_back({"Moment 3 -1",   25, 0,   90,   true,  11, -1});
   Configurations.push_back({"Moment 5 0",    25, 0,   1,    true,  12, -1});
   Configurations.push_back({"Moment 5 1",    25, 0,   0.05, true,  13, -1});
   Configurations.push_back({"Moment 5 -1",   25, 0,   25,   true,  14, -1});
   Configurations.push_back({"ZG (0.0, 0.1)", 25, 0.1, 0.5,  false, 0,  TYPE_ZG});
   Configurations.push_back({"DR (0.0, 0.1)", 25, 0.0, 0.5,  false, 0,  TYPE_DR});
   Configurations.push_back({"ZG (0.5, 1.5)", 25, 0.1, 0.5,  false, 1,  TYPE_ZG});
   Configurations.push_back({"DR (0.5, 1.5)", 25, 0.0, 0.5,  false, 1,  TYPE_DR});

   for(int i1 = 0; i1 < (int)Configurations.size(); i1++)
   {
      for(int i2 = 0; i2 < (int)Configurations.size(); i2++)
      {
         PlotCorrelation(PdfFile, InputMC, InputData, Configurations[i1], Configurations[i2], 0.25 * M_PI, 30);
         break;
      }
   }

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

void PlotCorrelation(PdfFileHelper &PdfFile, string FileNameMC, string FileNameData,
   Configuration C1, Configuration C2, double MinTheta, double MinP)
{
   TH2D HM12CorrData("HM12CorrData", Form("Data;J1 %s;J2 %s", C1.Label.c_str(), C2.Label.c_str()),
      C1.Bin, C1.Min, C1.Max, C2.Bin, C2.Min, C2.Max);
   TH2D HM12CorrMC("HM12CorrMC", Form("MC;J1 %s;J2 %s", C1.Label.c_str(), C2.Label.c_str()),
      C1.Bin, C1.Min, C1.Max, C2.Bin, C2.Min, C2.Max);
   
   PlotCorrelation(PdfFile, FileNameData, C1, C2, MinTheta, MinP, HM12CorrData);
   PlotCorrelation(PdfFile, FileNameMC, C1, C2, MinTheta, MinP, HM12CorrMC);
}

void PlotCorrelation(PdfFileHelper &PdfFile, string FileName,
   Configuration C1, Configuration C2, double MinTheta, double MinP, TH2D &HM12Corr)
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
   TH1D HM1("HM1", Form(";J1 %s;", C1.Label.c_str()), C1.Bin, C1.Min, C1.Max);
   TH1D HM2("HM2", Form(";J2 %s;", C2.Label.c_str()), C2.Bin, C2.Min, C2.Max);
   TH2D HM12("HM12", Form(";J1 %s;J2 %s", C1.Label.c_str(), C2.Label.c_str()),
      C1.Bin, C1.Min, C1.Max, C2.Bin, C2.Min, C2.Max);

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

      double M1 = -1;
      if(C1.IsMoment == true && C1.Index < NMoment && C1.Index >= 0)
         M1 = J1M[C1.Index];
      if(C1.IsMoment == false && C1.Index < NSD && C1.Index >= 0)
      {
         if(C1.Type == TYPE_ZG)   M1 = J1SDZG[C1.Index];
         if(C1.Type == TYPE_DR)   M1 = J1SDDR[C1.Index];
      }
      
      double M2 = -1;
      if(C2.IsMoment == true && C2.Index < NMoment && C2.Index >= 0)
         M2 = J2M[C2.Index];
      if(C2.IsMoment == false && C2.Index < NSD && C2.Index >= 0)
      {
         if(C2.Type == TYPE_ZG)   M2 = J2SDZG[C2.Index];
         if(C2.Type == TYPE_DR)   M2 = J2SDDR[C2.Index];
      }

      HTheta1.Fill(J1Theta);
      HTheta2.Fill(J2Theta);
      HTheta12.Fill(J1Theta, J2Theta);
      HPhi12.Fill(J1Phi, J2Phi);
      HM1.Fill(M1);
      HM2.Fill(M2);
      HM12.Fill(M1, M2);
   }

   for(int i1 = 1; i1 <= C1.Bin; i1++)
   {
      for(int i2 = 1; i2 <= C2.Bin; i2++)
      {
         double M1 = HM1.GetBinContent(i1);
         double M2 = HM2.GetBinContent(i2);
         double M12 = HM12.GetBinContent(i1, i2);
         if(M1 > 1e-10 && M2 > 1e-10)
            HM12Corr.SetBinContent(i1, i2, M12 / M1 / M2);
      }
   }
   HM12Corr.Scale(HM1.GetEntries());
   HM12Corr.SetMinimum(0.0);
   HM12Corr.SetMaximum(2.0);

   PdfFile.AddTextPage(C1.Label + " vs " + C2.Label);

   HM12.SetStats(0);
   HM12Corr.SetStats(0);

   PdfFile.AddPlot(HTheta1);
   PdfFile.AddPlot(HTheta2);
   PdfFile.AddPlot(HTheta12, "colz");
   PdfFile.AddPlot(HPhi12, "colz");
   PdfFile.AddPlot(HM1);
   PdfFile.AddPlot(HM2);
   PdfFile.AddPlot(HM12, "colz");
   PdfFile.AddPlot(HM12, "colz", false, true);
   PdfFile.AddPlot(HM12Corr, "colz");

   File.Close();
}




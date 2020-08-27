#include <iostream>
#include <cmath>
using namespace std;

#include "TTree.h"
#include "TFile.h"
#include "TF1.h"
#include "TProfile.h"
#include "TGraphErrors.h"

#include "SetStyle.h"
#include "CommandLine.h"
#include "PlotHelper4.h"

int main(int argc, char *argv[]);
pair<double, double> GetR(PdfFileHelper &PdfFile, TTree *TData, TTree *TMC, double MinJ2PT, double MaxJ2PT, double MaxJ3PT);

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   string DataFileName = CL.Get("Data", "DataSkimmed.root");
   string MCFileName = CL.Get("MC", "MCSkimmed.root");
   string OutputFileName = CL.Get("Output", "ZResidualL2Rel.pdf");

   PdfFileHelper PdfFile(OutputFileName);
   PdfFile.AddTextPage("Residual from Z's");

   TFile DataFile(DataFileName.c_str());
   TFile MCFile(MCFileName.c_str());

   TTree *DataTree = (TTree *)DataFile.Get("SkimmedTree");
   TTree *MCTree = (TTree *)MCFile.Get("SkimmedTree");

   TGraphErrors G;

   G.GetXaxis()->SetTitle("J2Theta");
   G.GetYaxis()->SetTitle("MC/Data");

   for(int i = 0; i < 10; i++)
   {
      double Min = M_PI / 10 * i;
      double Max = M_PI / 10 * (i + 1);

      pair<double, double> R = GetR(PdfFile, DataTree, MCTree, Min, Max, 5);

      int N = G.GetN();
      G.SetPoint(N, (Max + Min) / 2, R.first);
      G.SetPointError(N, (Max - Min) / 2, R.second);
   }

   PdfFile.AddPlot(G, "ap");

   MCFile.Close();
   DataFile.Close();

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

pair<double, double> GetR(PdfFileHelper &PdfFile, TTree *TData, TTree *TMC, double MinJ2Theta, double MaxJ2Theta, double MaxJ3PT)
{
   TProfile PData("PData", Form("%.4f ~ %.4f;J3PT;", MinJ2Theta, MaxJ2Theta), 8, 0.2, MaxJ3PT);
   TProfile PMC("PMC", Form("%.4f ~ %.4f;J3PT;", MinJ2Theta, MaxJ2Theta), 8, 0.2, MaxJ3PT);

   PMC.SetLineColor(kRed);
   PMC.SetMarkerColor(kRed);

   PData.SetStats(0);
   PMC.SetStats(0);

   char Cut[] = "J1Theta > 0.45*3.14159 && J1Theta < 0.55*3.14159";
   TData->Draw("J1PT/J2PT:J3PT>>PData", Form("%s && J2Theta > %f && J2Theta < %f", Cut, MinJ2Theta, MaxJ2Theta), "prof");
   TMC->Draw("J1PT/J2PT:J3PT>>PMC",     Form("%s && J2Theta > %f && J2Theta < %f", Cut, MinJ2Theta, MaxJ2Theta), "prof");

   TF1 FData("FData", "pol1");
   TF1 FMC("FMC", "pol1");

   FData.SetLineColor(kBlack);
   FMC.SetLineColor(kRed);

   PData.Fit(&FData);
   PMC.Fit(&FMC);

   TCanvas Canvas;

   PData.Draw("");
   PMC.Draw("same");

   PdfFile.AddCanvas(Canvas);

   double R = FMC.GetParameter(0) / FData.GetParameter(0);
   double MCRel = FMC.GetParError(0) / FMC.GetParameter(0);
   double DataRel = FData.GetParError(0) / FData.GetParameter(0);
   double Rel = sqrt(MCRel * MCRel + DataRel * DataRel);
   double Error = R * Rel;

   return pair<double, double>(R, Error);
}


